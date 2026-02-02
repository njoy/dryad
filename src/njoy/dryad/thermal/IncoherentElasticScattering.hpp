#ifndef NJOY_DRYAD_THERMAL_INCOHERENTELASTICSCATTERING
#define NJOY_DRYAD_THERMAL_INCOHERENTELASTICSCATTERING

// system includes
#include <optional>
#include <variant>

// other includes
#include "njoy/dryad/thermal/TabulatedDebyeWallerIntegral.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Incoherent elastic thermal scattering data
   */
  class IncoherentElasticScattering {

    /* fields */

    double bound_xs_;
    TabulatedDebyeWallerIntegral debye_waller_;

  public:

    /* constructor */
    #include "njoy/dryad/thermal/IncoherentElasticScattering/src/ctor.hpp"

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
     *  @param xs   the reaction product identifier
     */
    void boundCrossSection( double xs ) {

      this->bound_xs_ = xs;
    }

    /**
     *  @brief Return the Debye-Waller integral data
     */
    const TabulatedDebyeWallerIntegral& debyeWallerIntegral() const {

      return this->debye_waller_;
    }

    /**
     *  @brief Set the Debye-Waller integral data
     *
     *  @param debyeWaller   the Debye-Waller integral data
     */
    void debyeWallerIntegral( TabulatedDebyeWallerIntegral debyeWaller ) {

      this->debye_waller_ = std::move( debyeWaller );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentElasticScattering& right ) const {

      return std::tie( this->bound_xs_, this->debyeWallerIntegral() ) ==
             std::tie( right.bound_xs_, right.debyeWallerIntegral() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentElasticScattering& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
