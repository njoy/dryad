#ifndef NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS
#define NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS

// system includes
#include <variant>
#include <vector>

// other includes
#include "dryad/resonances/CompoundSystem.hpp"

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

    std::vector< CompoundSystem > resolved_;

  public:

    /* constructor */

    #include "dryad/resonances/ResonanceParameters/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the compound systems that make up the resolved resonance data
     */
    const std::vector< CompoundSystem >& resolved() const {

      return this->resolved_;
    }

    /**
     *  @brief Return the compound systems that make up the resolved resonance data
     */
    std::vector< CompoundSystem >& resolved() {

      return this->resolved_;
    }

    /**
     *  @brief Set the compound systems that make up resolved resonance data
     *
     *  @param[in] resolved   the resolved resonance compound systems
     */
    void resolved( std::vector< CompoundSystem > resolved ) {

      this->resolved_ = std::move( resolved );
    }

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
