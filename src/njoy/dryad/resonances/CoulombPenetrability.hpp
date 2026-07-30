#ifndef NJOY_DRYAD_RESONANCES_COULOMBPENETRABILITY
#define NJOY_DRYAD_RESONANCES_COULOMBPENETRABILITY

// system includes

// other includes
#include "njoy/dryad/resonances/coulomb/coh3-coulomb.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Coulomb penetrability functions

   *  @todo c++20 : use defaulted comparison operators
   */
  class CoulombPenetrability {

    /* fields */

    unsigned int orbital_momentum_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    CoulombPenetrability() = default;

    CoulombPenetrability( const CoulombPenetrability& ) = default;
    CoulombPenetrability( CoulombPenetrability&& ) = default;

    CoulombPenetrability& operator=( const CoulombPenetrability& ) = default;
    CoulombPenetrability& operator=( CoulombPenetrability&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param orbitalAngularMomentum   the value of the orbital angular momentum
     */
    CoulombPenetrability( unsigned int orbitalAngularMomentum ) :
      orbital_momentum_( orbitalAngularMomentum ) {}

    /* methods */

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->orbital_momentum_;
    }

    /**
     *  @brief Evaluate the penetrability for a given ratio and eta
     *
     *  @param[in] ratio   the ratio value
     *  @param[in] eta     the eta value
     */
    double operator()( double ratio, double eta ) const {

      std::complex< double > gf, dgf;
      coulombWaveFunctions( this->orbitalAngularMomentum(), ratio, eta, gf, dgf );

      double F = gf.imag();
      double G = gf.real();
      return F == 0. && G == 0.
             ? 0.
             : ratio / ( F * F + G * G );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const CoulombPenetrability& left,
                            const CoulombPenetrability& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const CoulombPenetrability& left,
                            const CoulombPenetrability& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
