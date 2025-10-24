#ifndef NJOY_DRYAD_RESONANCES_COULOMBPHASESHIFTDIFFERENCE
#define NJOY_DRYAD_RESONANCES_COULOMBPHASESHIFTDIFFERENCE

// system includes
#include <cmath>

// other includes

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Coulomb phase shift difference functions
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class CoulombPhaseShiftDifference {

    /* fields */
    unsigned int orbital_momentum_;

    /* auxiliary functions */

  public:

    /* constructor */

    #include "dryad/resonances/CoulombPhaseShiftDifference/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->orbital_momentum_;
    }

    /**
     *  @brief Evaluate the Coulomb phase shift difference for a given eta
     *
     *  @param[in] eta   the eta value
     */
    double operator()( double eta ) const {

      double w = 0;
      for ( unsigned int i = 1; i < this->orbitalAngularMomentum() + 1; ++i ) {

        w += std::atan( eta / i );
      }
      return w;
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const CoulombPhaseShiftDifference& left,
                            const CoulombPhaseShiftDifference& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const CoulombPhaseShiftDifference& left,
                            const CoulombPhaseShiftDifference& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
