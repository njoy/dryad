#ifndef NJOY_DRYAD_THERMAL_INCOHERENTELASTICANGULARCDF
#define NJOY_DRYAD_THERMAL_INCOHERENTELASTICANGULARCDF

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
   *  @brief Incoherent elastic thermal scattering angular distribution cdf
   */
  class IncoherentElasticAngularCdf :
      protected scion::math::OneDimensionalFunctionBase< IncoherentElasticAngularCdf,
                                                         double, double > {

    /* friend declarations */
    friend class scion::math::OneDimensionalFunctionBase< IncoherentElasticAngularCdf,
                                                          double, double >;

    /* type aliases */

    using Parent = scion::math::OneDimensionalFunctionBase< IncoherentElasticAngularCdf,
                                                            double, double >;

    /* fields */

    double incident_;
    double debye_waller_;

    //! @todo we may need to add natom (number of principle scatterers) for older evaluations

    /* auxiliary functions */

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
     *  @brief Evaluate the angular distribution cdf for a given cosine value
     *
     *  The integral of the pdf between -1 and x is given by:
     *
     *  \frac{e^{2 w E \left( \mu + 1 \right)} - 1}{e^{4 w E} - 1}
     *
     *  as calculated by Wolfram alpha
     *
     *  @param[in] cosine   the cosine value
     */
    double evaluate( double cosine ) const {

      double product = this->incidentEnergy() * this->debyeWallerIntegral();
      return ( std::exp( 2. * product * ( cosine + 1. ) ) - 1. )
             / ( std::exp( 4. * product ) - 1. );
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
    IncoherentElasticAngularCdf() = default;

    IncoherentElasticAngularCdf( const IncoherentElasticAngularCdf& ) = default;
    IncoherentElasticAngularCdf( IncoherentElasticAngularCdf&& ) = default;

    IncoherentElasticAngularCdf& operator=( const IncoherentElasticAngularCdf& ) = default;
    IncoherentElasticAngularCdf& operator=( IncoherentElasticAngularCdf&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] incident              the incident energy
     *  @param[in] debyeWallerIntegral   the Debye-Waller integral value
     */
    IncoherentElasticAngularCdf( double incident,
                                 double debyeWallerIntegral ) :
      Parent( scion::math::IntervalDomain< double >( -1., 1. ) ),
      incident_( incident ),
      debye_waller_( debyeWallerIntegral ) {}

    /* methods */

    /**
     *  @brief Return the lower cosine limit
     */
    double lowerCosineLimit() const {

      return std::get< scion::math::IntervalDomain< double > >( this->domain() ).lowerLimit();
    }

    /**
     *  @brief Return the upper cosine limit
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
     *  @brief Return the Debye-Waller integral value
     */
    double debyeWallerIntegral() const {

      return this->debye_waller_;
    }

    using Parent::operator();

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
    bool operator==( const IncoherentElasticAngularCdf& right ) const {

      return std::tie( this->incident_, this->debye_waller_ ) ==
             std::tie( right.incident_, right.debye_waller_ );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentElasticAngularCdf& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
