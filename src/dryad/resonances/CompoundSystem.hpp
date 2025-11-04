#ifndef NJOY_DRYAD_RESONANCES_COMPOUNDSYSTEM
#define NJOY_DRYAD_RESONANCES_COMPOUNDSYSTEM

// system includes
#include <vector>

// other includes
#include "dryad/resonances/SpinGroup.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief The compound nucleus system
   */
  class CompoundSystem {

    /* fields */

    std::vector< SpinGroup > spin_groups_;

    /* auxiliary functions */

    #include "dryad/resonances/CompoundSystem/src/processSpinGroups.hpp"

  public:

    /* constructor */

    #include "dryad/resonances/CompoundSystem/src/ctor.hpp"

    /**
     *  @brief Return the spin groups that make up the compound system
     */
    const std::vector< SpinGroup >& spinGroups() const {

      return this->spin_groups_;
    }

    /**
     *  @brief Return the spin groups that make up the compound system
     */
    std::vector< SpinGroup >& spinGroups() {

      return this->spin_groups_;
    }

    /**
     *  @brief Set the spin groups that make up the compound system
     *
     *  @param spinGroups  the spin groups
     */
    void spinGroups( std::vector< SpinGroup > spinGroups ) {

      this->spin_groups_ = std::move( spinGroups );
      this->processSpinGroups();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const CompoundSystem& left, const CompoundSystem& right ) {

      return left.spinGroups() == right.spinGroups();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const CompoundSystem& left, const CompoundSystem& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
