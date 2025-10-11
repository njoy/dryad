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
   */
  class HardSphereShiftFactor :
      protected scion::math::PolynomialSeriesRatio< double, double > {

    /* fields */
    unsigned int orbital_momentum_;

    /* auxiliary functions */

    #include "dryad/resonances/HardSphereShiftFactor/src/generateFunction.hpp"

  public:

    /* constructor */

    #include "dryad/resonances/HardSphereShiftFactor/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->orbital_momentum_;
    }

    using PolynomialSeriesRatio::operator();

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const HardSphereShiftFactor& right ) const {

      return this->orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const HardSphereShiftFactor& right ) const {

      return ! this->operator==( right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
