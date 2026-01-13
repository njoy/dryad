#ifndef NJOY_DRYAD_INTERACTIONTYPE
#define NJOY_DRYAD_INTERACTIONTYPE

// system includes

// other includes

namespace njoy {
namespace dryad {

/**
 *  @enum
 *  @brief The interaction types
 *
 *  This enum is used to differentiate between how the projectile interacts with
 *  the target. We currently distinguish nuclear and atomic interactions.
 */
enum class InteractionType : short {

  Nuclear = 1, /**< The projectile-target interaction is nuclear */
  Atomic = 2   /**< The projectile-target interaction is atomic */
};

} // dryad namespace
} // njoy namespace

#endif
