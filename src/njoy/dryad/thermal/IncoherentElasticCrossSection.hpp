#ifndef NJOY_DRYAD_THERMAL_INCOHERENTELASTICCROSSSECTION
#define NJOY_DRYAD_THERMAL_INCOHERENTELASTICCROSSSECTION

// system includes
#include <cmath>
#include <tuple>

// other includes
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/linearisation/Lineariser.hpp"
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Incoherent elastic thermal scattering cross section
   */
  class IncoherentElasticCrossSection :
      protected scion::math::OneDimensionalFunctionBase< IncoherentElasticCrossSection,
                                                         double, double > {

    /* friend declarations */
    friend class scion::math::OneDimensionalFunctionBase< IncoherentElasticCrossSection,
                                                          double, double >;

    /* type aliases */

    using Parent = scion::math::OneDimensionalFunctionBase< IncoherentElasticCrossSection,
                                                            double, double >;

    /* fields */

    double bound_xs_;
    double debye_waller_;

    //! @todo we may need to add natom (number of principle scatterers) for older evaluations

    /* auxiliary functions */

    /**
     *  @brief Generate the initial grid for linearisation
     */
    std::vector< double > grid() const {

      // the analytical form of the cross section is continuously decreasing
      // so the minimal grid can be set to the lower and upper energy

      //! @todo should we add a user option to add a point for each decade in
      //!       between the lower and upper energy (ie 1e-5, 1e-4, 1e-3, etc)

      return { this->lowerEnergyLimit(), this->upperEnergyLimit() };
    }

    /* interface imposed function */

    /**
     *  @brief Evaluate the cross section for a given energy value
     *
     *  @param[in] energy   the energy value
     */
    double evaluate( double energy ) const {

      double product = energy * this->debyeWallerIntegral();
      return 0.25 * this->boundCrossSection() * ( 1. - std::exp( -4. * product ) ) / product;
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
    IncoherentElasticCrossSection() = default;

    IncoherentElasticCrossSection( const IncoherentElasticCrossSection& ) = default;
    IncoherentElasticCrossSection( IncoherentElasticCrossSection&& ) = default;

    IncoherentElasticCrossSection& operator=( const IncoherentElasticCrossSection& ) = default;
    IncoherentElasticCrossSection& operator=( IncoherentElasticCrossSection&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] lower                 the lower energy limit
     *  @param[in] upper                 the upper energy limit
     *  @param[in] xs                    the bound atom cross section
     *  @param[in] debyeWallerIntegral   the Debye-Waller integral value
     */
    IncoherentElasticCrossSection( double lower,
                                   double upper,
                                   double xs,
                                   double debyeWallerIntegral ) :
      Parent( scion::math::IntervalDomain< double >( lower, upper ) ),
      bound_xs_( std::move( xs ) ),
      debye_waller_( std::move( debyeWallerIntegral ) ) {}

    /* methods */

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return std::get< scion::math::IntervalDomain< double > >( this->domain() ).lowerLimit();
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return std::get< scion::math::IntervalDomain< double > >( this->domain() ).upperLimit();
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
     *  @brief Return a linearised cross section table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedCrossSection linearise( double tolerance = constants::linearisation::tolerance ) const {

      using MidpointSplit = scion::linearisation::MidpointSplit< double, double >;
      using Tolerance = scion::linearisation::ToleranceConvergence< double, double >;
      using Lineariser = scion::linearisation::Lineariser< std::vector< double >, std::vector< double > >;

      std::vector< double > energies;
      std::vector< double > values;
      Lineariser lineariser( energies, values );
      lineariser( this->grid(),
                  *this,
                  Tolerance( tolerance, constants::linearisation::threshold ),
                  MidpointSplit() );

      return TabulatedCrossSection( std::move( energies ), std::move( values ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentElasticCrossSection& right ) const {

      return std::tie( this->bound_xs_, this->debye_waller_, this->domain() ) ==
             std::tie( right.bound_xs_, right.debye_waller_, right.domain() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentElasticCrossSection& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
