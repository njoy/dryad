#ifndef NJOY_DRYAD_RESONANCES_HARDSPHEREPHASESHIFT
#define NJOY_DRYAD_RESONANCES_HARDSPHEREPHASESHIFT

// system includes
#include <cmath>

// other includes
#include "scion/math/PolynomialSeriesRatio.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Hard sphere phase shift functions
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class HardSpherePhaseShift {

    /* fields */
    scion::math::PolynomialSeriesRatio< double, double > ratio_;
    unsigned int orbital_momentum_;

    /* auxiliary functions */

    #include "dryad/resonances/HardSpherePhaseShift/src/generateFunction.hpp"

  public:

    /* constructor */

    #include "dryad/resonances/HardSpherePhaseShift/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->orbital_momentum_;
    }

    /**
     *  @brief Evaluate the phase shift for a given ratio value
     *
     *  @param[in] ratio   the ratio value
     */
    double operator()( double ratio ) const {

      return ratio - std::atan( this->ratio_( ratio ) );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const HardSpherePhaseShift& left,
                            const HardSpherePhaseShift& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const HardSpherePhaseShift& left,
                            const HardSpherePhaseShift& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
