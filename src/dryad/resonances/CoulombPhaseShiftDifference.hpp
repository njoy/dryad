#ifndef NJOY_DRYAD_RESONANCES_COULOMBPHASESHIFTDIFFERENCE
#define NJOY_DRYAD_RESONANCES_COULOMBPHASESHIFTDIFFERENCE

// system includes

// other includes

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Coulomb phase shift difference functions
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
     *  @brief Return the value of the orbital momentum
     */
    unsigned int orbitalMomentum() const {

      return this->orbital_momentum_;
    }

    /**
     *  @brief Evaluate the Coulomb phase shift difference for a given eta
     *
     *  @param[in] eta   the eta value
     */
    double operator()( double eta ) const {

      double w = 0;
      for ( unsigned int i = 1; i < this->orbitalMomentum() + 1; ++i ) {

        w += std::atan( eta / i );
      }
      return w;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CoulombPhaseShiftDifference& right ) const {

      return this->orbitalMomentum() == right.orbitalMomentum();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CoulombPhaseShiftDifference& right ) const {

      return ! this->operator==( right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
