#ifndef NJOY_DRYAD_THERMAL_INELASTICSCATTERING
#define NJOY_DRYAD_THERMAL_INELASTICSCATTERING

// system includes
#include <optional>
#include <variant>

// other includes
#include "njoy/dryad/thermal/TabulatedScatteringKernel.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Inelastic thermal scattering data
   */
  class InelasticScattering {

    /* fields */

    double bound_xs_;
    TabulatedScatteringKernel self_scatter_;

    std::optional< double > incoherent_xs_;
    std::optional< double > coherent_xs_;
    std::optional< TabulatedScatteringKernel > distinct_scatter_;

  public:

    /* constructor */
    #include "njoy/dryad/thermal/InelasticScattering/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return whether or not the incoherent approximation is used
     *
     *  The inelastic scattering data uses the incoherent approximation if the
     *  distinct effect scattering function is neglected.
     */
    bool isIncoherentApproximation() const {

      return ! this->distinct_scatter_.has_value();
    }

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
     *  @brief Return the self-scattering S(a,b) function
     */
    const TabulatedScatteringKernel& selfScatteringFunction() const {

      return this->self_scatter_;
    }

    /**
     *  @brief Set the self-scattering S(a,b) function
     *
     *  @param selfScatter   the self-scattering S(a,b) function
     */
    void selfScatteringFunction( TabulatedScatteringKernel selfScatter ) {

      this->self_scatter_ = std::move( selfScatter );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const InelasticScattering& right ) const {

      return std::tie( this->bound_xs_, this->selfScatteringFunction() ) ==
             std::tie( right.bound_xs_, right.selfScatteringFunction() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const InelasticScattering& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
