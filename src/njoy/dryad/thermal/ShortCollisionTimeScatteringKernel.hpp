#ifndef NJOY_DRYAD_THERMAL_SHORTCOLLISIONTIMESCATTERINGKERNEL
#define NJOY_DRYAD_THERMAL_SHORTCOLLISIONTIMESCATTERINGKERNEL

// system includes
#include <cmath>
#include <tuple>

// other includes
#include "njoy/constants.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief An S(a,b) scattering kernel using the short collision time approximation
   */
  class ShortCollisionTimeScatteringKernel {

    /* fields */

    double moderator_temperature_;
    double effective_temperature_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ShortCollisionTimeScatteringKernel() = default;

    ShortCollisionTimeScatteringKernel( const ShortCollisionTimeScatteringKernel& ) = default;
    ShortCollisionTimeScatteringKernel( ShortCollisionTimeScatteringKernel&& ) = default;

    ShortCollisionTimeScatteringKernel& operator=( const ShortCollisionTimeScatteringKernel& ) = default;
    ShortCollisionTimeScatteringKernel& operator=( ShortCollisionTimeScatteringKernel&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] moderatorTemperature   the moderator temperature
     *  @param[in] effectiveTemperature   the effective temperature
     */
    ShortCollisionTimeScatteringKernel( double moderatorTemperature, double effectiveTemperature ) :
      moderator_temperature_( moderatorTemperature ),
      effective_temperature_( effectiveTemperature ) {}

    /* methods */

    /**
     *  @brief Return the moderator temperature
     */
    double moderatorTemperature() const {

      return this->moderator_temperature_;
    }

    /**
     *  @brief Return the effective temperature
     */
    double effectiveTemperature() const {

      return this->effective_temperature_;
    }

    /**
     *  @brief Evaluate the scattering kernel for a given momentum and energy transfer value
     *
     *  @param[in] a   the momentum transfer value
     *  @param[in] b   the energy transfer value
     */
    double operator()( double a, double b ) const {

      b = b < 0. ? -b : b;
      double delta = a - b;
      double ratio = this->moderatorTemperature() / this->effectiveTemperature();

      return std::exp( -( 0.25 * delta * delta * ratio / a + 0.5 * b ) )
             / std::sqrt( 4. * constants::pi * a / ratio );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ShortCollisionTimeScatteringKernel& right ) const {

      return std::tie( this->moderator_temperature_, this->effective_temperature_ ) ==
             std::tie( right.moderator_temperature_, right.effective_temperature_ );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ShortCollisionTimeScatteringKernel& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
