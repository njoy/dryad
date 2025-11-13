#ifndef NJOY_DRYAD_RESONANCES_HARDSPHEREPENETRABILITY
#define NJOY_DRYAD_RESONANCES_HARDSPHEREPENETRABILITY

// system includes

// other includes
#include "scion/math/PolynomialSeriesRatio.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Hard sphere penetrability functions

   *  @todo c++20 : use defaulted comparison operators
   */
  class HardSpherePenetrability :
      protected scion::math::PolynomialSeriesRatio< double, double > {

    /* fields */
    unsigned int orbital_momentum_;

    /* auxiliary functions */

    #include "njoy/dryad/resonances/HardSpherePenetrability/src/generateFunction.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/resonances/HardSpherePenetrability/src/ctor.hpp"

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
    friend bool operator==( const HardSpherePenetrability& left,
                            const HardSpherePenetrability& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const HardSpherePenetrability& left,
                            const HardSpherePenetrability& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
