#ifndef NJOY_DRYAD_PROJECTILETARGET
#define NJOY_DRYAD_PROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/NuclideID.hpp"
#include "dryad/Reaction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The data associated to a given projectile and target
   */
  class ProjectileTarget {

    /* fields */
    NuclideID projectile_id_;
    NuclideID target_id_;

    std::vector< Reaction > reactions_;

    bool linearised_;

  public:

    /* constructor */
    #include "dryad/ProjectileTarget/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the projectile identifier
     */
    const NuclideID& projectileIdentifier() const noexcept {

      return this->projectile_id_;
    }

    /**
     *  @brief Return the target identifier
     */
    const NuclideID& targetIdentifier() const noexcept {

      return this->target_id_;
    }

    /**
     *  @brief Return the reactions
     */
    const std::vector< Reaction >& reactions() const noexcept {

      return this->reactions_;
    }

    /**
     *  @brief Return whether or not the data is linearised
     */
    bool isLinearised() const noexcept {

      return this->linearised_;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
