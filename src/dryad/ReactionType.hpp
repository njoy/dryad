#ifndef NJOY_DRYAD_REACTIONTYPE
#define NJOY_DRYAD_REACTIONTYPE

// system includes

// other includes

namespace njoy {
namespace dryad {

/**
 *  @enum
 *  @brief The reaction types
 *
 *  This enum is used to differentiate reaction types in the ProjectileTarget.
 *  We currently distinguish two types of reactions: primary and summation.
 */
enum class ReactionType : short {

  Primary = 1,  /**< The reaction is a primary independent reaction */
  Summation = 2 /**< The reaction is a summation reaction */
};

} // dryad namespace
} // njoy namespace

#endif
