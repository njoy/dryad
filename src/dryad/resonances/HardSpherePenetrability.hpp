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
   *  @brief Hardsphere penetrability functions
   */
  class HardSpherePenetrability :
      protected scion::math::PolynomialSeriesRatio< double, double > {

    /* fields */
    unsigned int orbital_momentum_;

    /* auxiliary functions */

    #include "dryad/resonances/HardSpherePenetrability/src/generateFunction.hpp"

  public:

    /* constructor */

    #include "dryad/resonances/HardSpherePenetrability/src/ctor.hpp"

    /* methods */

    using PolynomialSeriesRatio::operator();

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const HardSpherePenetrability& right ) const {

      return PolynomialSeriesRatio::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const HardSpherePenetrability& right ) const {

      return ! this->operator==( right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
