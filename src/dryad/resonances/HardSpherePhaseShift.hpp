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
     *  @brief Return the value of the orbital momentum
     */
    unsigned int orbitalMomentum() const {

      return this->orbital_momentum_;
    }

    /**
     *  @brief Evaluate the phasse shift for a given ratio value
     *
     *  @param[in] ratio   the ratio value
     */
    double operator()( double ratio ) const {

      return ratio - std::atan( this->ratio_( ratio ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const HardSpherePhaseShift& right ) const {

      return this->orbitalMomentum() == right.orbitalMomentum();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const HardSpherePhaseShift& right ) const {

      return ! this->operator==( right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
