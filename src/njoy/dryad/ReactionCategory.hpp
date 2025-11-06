#ifndef NJOY_DRYAD_REACTIONCATEGORY
#define NJOY_DRYAD_REACTIONCATEGORY

// system includes

// other includes

namespace njoy {
namespace dryad {

/**
 *  @enum
 *  @brief The reaction categories
 *
 *  This enum is used to differentiate reaction categories in the ProjectileTarget.
 *  We currently have two categories: primary and summation. GNDS seems to identify
 *  two additional categories (production and incomplete) which may be added at a
 *  later point if we feel the need.
 */
enum class ReactionCategory : short {

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
