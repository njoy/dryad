#ifndef NJOY_DRYAD_RESONANCES_COULOMBPHASESHIFT
#define NJOY_DRYAD_RESONANCES_COULOMBPHASESHIFT

// system includes

// other includes
#include "njoy/dryad/resonances/coulomb/coh3-coulomb.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Coulomb phase shift functions

   *  @todo c++20 : use defaulted comparison operators
   */
  class CoulombPhaseShift {

    /* fields */

    unsigned int orbital_momentum_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    CoulombPhaseShift() = default;

    CoulombPhaseShift( const CoulombPhaseShift& ) = default;
    CoulombPhaseShift( CoulombPhaseShift&& ) = default;

    CoulombPhaseShift& operator=( const CoulombPhaseShift& ) = default;
    CoulombPhaseShift& operator=( CoulombPhaseShift&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] orbitalAngularMomentum   the value of the orbital angular momentum
     */
    CoulombPhaseShift( unsigned int orbitalAngularMomentum ) :
      orbital_momentum_( orbitalAngularMomentum ) {}

    /* methods */

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->orbital_momentum_;
    }

    /**
     *  @brief Evaluate the phase shift for a given ratio and eta
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
             : std::acos( G / std::sqrt( F * F + G * G ) );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const CoulombPhaseShift& left,
                            const CoulombPhaseShift& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const CoulombPhaseShift& left,
                            const CoulombPhaseShift& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
