#ifndef NJOY_MEDIC_PRUNECROSSECTIONS
#define NJOY_MEDIC_PRUNECROSSECTIONS

// system includes
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/medic/pruneCrossSection.hpp"

namespace njoy {
namespace medic {

  /**
   *  @brief Prune cross section data
   *
   *  @param[in]     lowerEnergy   the new lower energy limit
   *  @param[in]     upperEnergy   the new upper energy limit
   *  @param[in,out] pt            the projectile-target data to be modified
   */
  inline void pruneCrossSections( double lowerEnergy, double upperEnergy,
                                  dryad::ProjectileTarget& pt ) {

    for ( dryad::Reaction& reaction : pt.reactions() ) {

      // prune this cross section data
      pruneCrossSection( lowerEnergy, upperEnergy, reaction.crossSection() );
    }
  }

} // medic namespace
} // njoy namespace

#endif
