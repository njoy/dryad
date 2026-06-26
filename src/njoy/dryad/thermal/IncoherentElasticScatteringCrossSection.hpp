#ifndef NJOY_DRYAD_THERMAL_INCOHERENTELASTICSCATTERINGCROSSSECTION
#define NJOY_DRYAD_THERMAL_INCOHERENTELASTICSCATTERINGCROSSSECTION

// system includes
#include <cmath>

// other includes
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Incoherent elastic thermal scattering cross section
   */
  class IncoherentElasticScatteringCrossSection :
      protected scion::math::OneDimensionalFunctionBase< IncoherentElasticScatteringCrossSection,
                                                         double, double > {

    /* fields */

    double bound_xs_;
    double debye_waller_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    IncoherentElasticScatteringCrossSection() = default;

    IncoherentElasticScatteringCrossSection( const IncoherentElasticScatteringCrossSection& ) = default;
    IncoherentElasticScatteringCrossSection( IncoherentElasticScatteringCrossSection&& ) = default;

    IncoherentElasticScatteringCrossSection& operator=( const IncoherentElasticScatteringCrossSection& ) = default;
    IncoherentElasticScatteringCrossSection& operator=( IncoherentElasticScatteringCrossSection&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] xs                    the bound atom cross section
     *  @param[in] debyeWallerIntegral   the Debye-Waller integral value
     */
    IncoherentElasticScatteringCrossSection( double xs,
                                             double debyeWallerIntegral ) :

      bound_xs_( xs ),
      debye_waller_( std::move( debyeWallerIntegral ) ) {}

    /* methods */

    /**
     *  @brief Return the bound atom cross section value
     */
    double boundCrossSection() const {

      return this->bound_xs_;
    }

    /**
     *  @brief Set the bound atom cross section value
     *
     *  @param[in] xs   the reaction product identifier
     */
    void boundCrossSection( double xs ) {

      this->bound_xs_ = xs;
    }

    /**
     *  @brief Return the Debye-Waller integral value
     */
    double debyeWallerIntegral() const {

      return this->debye_waller_;
    }

    /**
     *  @brief Set the Debye-Waller integral value
     *
     *  @param[in] debyeWaller   the Debye-Waller integral value
     */
    void debyeWallerIntegral( double debyeWaller ) {

      this->debye_waller_ = std::move( debyeWaller );
    }

    /**
     *  @brief Evaluate the cross section for a given energy value
     *
     *  @param[in] energy   the energy value
     */
    double operator()( double energy ) const {

      double product = energy * this->debyeWallerIntegral();
      return 0.25 * this->boundCrossSection() * ( 1. - std::exp( -4. * product ) ) / product;
    }

    /**
     *  @brief Return a linearised cross section table
     *
     *  @param[in] lower       the lower energy limit
     *  @param[in] upper       the upper energy limit
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedCrossSection linearise( double lower = 1e-5,
                                     double upper = 10.,
                                     double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;

      std::vector< double > energies;
      std::vector< double > values;
      linearisation::Lineariser lineariser( energies, values );
      lineariser( { lower, upper },
                  *this,
                  Tolerance( tolerance, constants::linearisation::threshold ),
                  linearisation::MidpointSplit< double, double >() );

      return TabulatedCrossSection( std::move( energies ), std::move( values ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentElasticScatteringCrossSection& right ) const {

      return std::tie( this->bound_xs_, this->debyeWallerIntegral() ) ==
             std::tie( right.bound_xs_, right.debyeWallerIntegral() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentElasticScatteringCrossSection& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
