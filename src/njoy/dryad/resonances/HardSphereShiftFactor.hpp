#ifndef NJOY_DRYAD_RESONANCES_HARDSPHERESHIFTFACTOR
#define NJOY_DRYAD_RESONANCES_HARDSPHERESHIFTFACTOR

// system includes

// other includes
#include "scion/math/PolynomialSeriesRatio.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Hard sphere shift factor functions
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class HardSphereShiftFactor :
      protected scion::math::PolynomialSeriesRatio< double, double > {

    /* fields */
    unsigned int orbital_momentum_;

    /* auxiliary functions */

    #include "njoy/dryad/resonances/HardSphereShiftFactor/src/generateFunction.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/resonances/HardSphereShiftFactor/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->orbital_momentum_;
    }

    using PolynomialSeriesRatio::operator();

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const HardSphereShiftFactor& left,
                            const HardSphereShiftFactor& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const HardSphereShiftFactor& left,
                            const HardSphereShiftFactor& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
