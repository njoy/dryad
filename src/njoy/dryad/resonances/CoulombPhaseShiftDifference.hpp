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

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    CoulombPhaseShiftDifference() = default;

    CoulombPhaseShiftDifference( const CoulombPhaseShiftDifference& ) = default;
    CoulombPhaseShiftDifference( CoulombPhaseShiftDifference&& ) = default;

    CoulombPhaseShiftDifference& operator=( const CoulombPhaseShiftDifference& ) = default;
    CoulombPhaseShiftDifference& operator=( CoulombPhaseShiftDifference&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] orbitalAngularMomentum   the value of the orbital angular momentum
     */
    CoulombPhaseShiftDifference( unsigned int orbitalAngularMomentum ) :
      orbital_momentum_( orbitalAngularMomentum ) {}

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
