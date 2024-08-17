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
 *  We currently distinguish four types of reactions: primary, summation,
 *  production and incomplete
 */
enum class ReactionType : short {

  /**
   *  A primary independent reaction that contributes to the total cross section
   */
  Primary = 1,
  /**
   *  A summation reaction with or without reaction products that does not count
   *  towards the total cross section
   */
  Summation = 2
};

} // dryad namespace
} // njoy namespace

#endif
