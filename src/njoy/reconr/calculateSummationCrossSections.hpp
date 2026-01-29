#ifndef NJOY_RECONR_CALCULATESUMMATIONCROSSSECTIONS
#define NJOY_RECONR_CALCULATESUMMATIONCROSSSECTIONS

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"

namespace njoy {
namespace reconr {

  /**
   *  @brief Calculate summation cross sections
   *
   *  This function recalculates the cross section of all summation reactions of
   *  a ProjectileTarget instance. It does so by linearising the cross sections of
   *  the partials (if required) and summing them together.
   *
   *  @param[in,out] pt          the projectile-target data to be modified
   *  @param[in]     tolerance   the linearisation tolerance (default: 0.1%)
   */
  inline void calculateSummationCrossSections( dryad::ProjectileTarget& pt,
                                               double tolerance = constants::linearisation::tolerance ) {

    pt.calculateSummationCrossSections( tolerance );
  }

} // reconr namespace
} // njoy namespace

#endif
