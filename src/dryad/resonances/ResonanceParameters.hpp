#ifndef NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS
#define NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS

// system includes

// other includes

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief The resonance parameter data
   *
   *  Note: this is currently a placeholder
   */
  class ResonanceParameters {

    /* fields */

  public:

    /* constructor */

    /* methods */

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ResonanceParameters& right ) const {

      return true;
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ResonanceParameters& right ) const {

      return false;
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
