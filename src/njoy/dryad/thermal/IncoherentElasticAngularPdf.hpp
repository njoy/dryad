#ifndef NJOY_DRYAD_THERMAL_INCOHERENTELASTICANGULARPDF
#define NJOY_DRYAD_THERMAL_INCOHERENTELASTICANGULARPDF

// system includes
#include <cmath>
#include <tuple>

// other includes
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/linearisation/Lineariser.hpp"
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Incoherent elastic thermal scattering angular distribution pdf
   */
  class IncoherentElasticAngularPdf :
      protected scion::math::OneDimensionalFunctionBase< IncoherentElasticAngularPdf,
                                                         double, double > {

    /* friend declarations */
    friend class scion::math::OneDimensionalFunctionBase< IncoherentElasticAngularPdf,
                                                          double, double >;

    /* type aliases */

    using Parent = scion::math::OneDimensionalFunctionBase< IncoherentElasticAngularPdf,
                                                            double, double >;

    /* fields */

    double incident_;
    double bound_xs_;
    double debye_waller_;

    double normalisation_;
    double mean_;

    //! @todo we may need to add natom (number of principle scatterers) for older evaluations

    /* auxiliary functions */

    /**
     *  @brief Return the normalisation value
    */
    double normalisation() const {

      return this->normalisation_;
    }

    /**
     *  @brief Generate the initial grid for linearisation
     */
    std::vector< double > grid() const {

      // the analytical form of the angular distribution is strictly increasing
      // so the minimal grid can be set to the lower and upper cosine limit

      return { this->lowerCosineLimit(), this->upperCosineLimit() };
    }

    /* interface imposed function */

    /**
     *  @brief Evaluate the angular distribution pdf for a given energy value
     *
     *  @param[in] cosine   the cosine value
     */
    double evaluate( double cosine ) const {

      double product = this->incidentEnergy() * this->debyeWallerIntegral();
      return 2. * std::exp( -2. * product * ( 1. - cosine ) ) / this->normalisation();
    }

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    IncoherentElasticAngularPdf() = default;

    IncoherentElasticAngularPdf( const IncoherentElasticAngularPdf& ) = default;
    IncoherentElasticAngularPdf( IncoherentElasticAngularPdf&& ) = default;

    IncoherentElasticAngularPdf& operator=( const IncoherentElasticAngularPdf& ) = default;
    IncoherentElasticAngularPdf& operator=( IncoherentElasticAngularPdf&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] incident              the incident energy
     *  @param[in] debyeWallerIntegral   the Debye-Waller integral value
     */
    IncoherentElasticAngularPdf( double incident,
                                 double debyeWallerIntegral ) :
      Parent( scion::math::IntervalDomain< double >( -1., 1. ) ),
      incident_( incident ),
      debye_waller_( debyeWallerIntegral ),
      normalisation_( [] ( double ew ) {

                        return ( 1. - std::exp( -4. * ew ) ) / ew;
                      }( incident * debyeWallerIntegral ) ),
      mean_( 0. ) {}

    /* methods */

    /**
     *  @brief Return the lower cosine limit
     */
    double lowerCosineLimit() const {

      return std::get< scion::math::IntervalDomain< double > >( this->domain() ).lowerLimit();
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperCosineLimit() const {

      return std::get< scion::math::IntervalDomain< double > >( this->domain() ).upperLimit();
    }

    /**
     *  @brief Return the incident energy value
     */
    double incidentEnergy() const {

      return this->incident_;
    }

    /**
     *  @brief Return the bound atom cross section value
     */
    double boundCrossSection() const {

      return this->bound_xs_;
    }

    /**
     *  @brief Return the Debye-Waller integral value
     */
    double debyeWallerIntegral() const {

      return this->debye_waller_;
    }

    using Parent::operator();

    /**
     *  @brief Calculate the integral over the distribution domain
     */
    constexpr double integral() const {

      return 1.;
    }

    /**
     *  @brief Calculate the mean over the distribution domain
     */
    double mean() const {

      return this->mean_;
    }

    /**
     *  @brief Return a linearised angular distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedAngularDistributionFunction linearise( double tolerance = constants::linearisation::tolerance ) const {

      using MidpointSplit = scion::linearisation::MidpointSplit< double, double >;
      using Tolerance = scion::linearisation::ToleranceConvergence< double, double >;
      using Lineariser = scion::linearisation::Lineariser< std::vector< double >, std::vector< double > >;

      std::vector< double > cosines;
      std::vector< double > values;
      Lineariser lineariser( cosines, values );
      lineariser( this->grid(),
                  *this,
                  Tolerance( tolerance, constants::linearisation::threshold ),
                  MidpointSplit() );

      return TabulatedAngularDistributionFunction( std::move( cosines ), std::move( values ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentElasticAngularPdf& right ) const {

      return std::tie( this->incident_, this->debye_waller_ ) ==
             std::tie( right.incident_, right.debye_waller_ );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentElasticAngularPdf& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
