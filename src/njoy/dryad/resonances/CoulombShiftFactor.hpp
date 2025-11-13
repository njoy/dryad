#ifndef NJOY_DRYAD_RESONANCES_COULOMBSHIFTFACTOR
#define NJOY_DRYAD_RESONANCES_COULOMBSHIFTFACTOR

// system includes

// other includes
#include "njoy/dryad/resonances/coulomb/coh3-coulomb.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Coulomb shift factor functions

   *  @todo c++20 : use defaulted comparison operators
   */
  class CoulombShiftFactor {

    /* fields */
    unsigned int orbital_momentum_;

    /* auxiliary functions */

  public:

    /* constructor */

    #include "njoy/dryad/resonances/CoulombShiftFactor/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->orbital_momentum_;
    }

    /**
     *  @brief Evaluate the shift factor for a given ratio and eta
     *
     *  @param[in] ratio   the ratio value
     *  @param[in] eta     the eta value
     */
    double operator()( double ratio, double eta ) const {

      std::complex< double > gf, dgf;
      coulombWaveFunctions( this->orbitalAngularMomentum(), ratio, eta, gf, dgf );

      double F = gf.imag();
      double G = gf.real();
      double dF = dgf.imag();
      double dG = dgf.real();
      return F == 0. && G == 0.
             ? 0.
             : ratio / ( F * F + G * G ) * ( F * dF + G * dG );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const CoulombShiftFactor& left,
                            const CoulombShiftFactor& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const CoulombShiftFactor& left,
                            const CoulombShiftFactor& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
