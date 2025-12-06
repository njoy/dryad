#ifndef NJOY_RECONR_UNIONISECROSSSECTIONS
#define NJOY_RECONR_UNIONISECROSSSECTIONS

// system includes
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"

namespace njoy {
namespace reconr {

  /**
   *  @brief Unionise cross section data in a ProjectileTarget instance
   *
   *  This function takes all cross section data in the ProjectileTarget
   *  instance and unionises the cross section grids. It does not linearise
   *  the data but reevaluates the data using the proper interpolation types
   *  of the cross section data.
   *
   *  By default, summation cross sections are included in the unionisation process.
   *  unless explicitly excluded by the user. Switching on the exclusion of summation
   *  cross sections may be useful when the user is going to recalculate the summation
   *  cross sections after unionisation.
   *
   *  @param[in,out] pt              the projectile-target data to be modified
   *  @param[in] exclude_summation   option to exclude summation reactions in the
   *                                 unionisation (default: false)
   */
  inline void unioniseCrossSections( dryad::ProjectileTarget& pt,
                                     bool exclude_summation = false ) {

    pt.unioniseCrossSections( exclude_summation );
  }

} // reconr namespace
} // njoy namespace

#endif
