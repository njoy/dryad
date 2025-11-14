#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEINCOHERENTSCATTERINGFUNCTIONBLOCK
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEINCOHERENTSCATTERINGFUNCTIONBLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create the incoherent form factorblock for photoatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid photoatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] photoatomic   the photoatomic data
   */
  inline njoy::ACEtk::photoatomic::IncoherentScatteringFunctionBlock
  createAceIncoherentScatteringFunctionBlock( const ProjectileTarget& photoatomic ) {

    decltype(auto) projectile = photoatomic.projectileIdentifier();
    decltype(auto) target = photoatomic.targetIdentifier();
    dryad::id::ReactionID incoherent_id( projectile, target, dryad::id::ReactionType( projectile, 504 ) );

    decltype(auto) incoherent = photoatomic.reaction( incoherent_id );
    decltype(auto) photon = incoherent.product( dryad::id::ParticleID::photon() ).distributionData().value();
    decltype(auto) function = std::get< dryad::IncoherentDistributionData >( photon ).scatteringFunction();

    return njoy::ACEtk::photoatomic::IncoherentScatteringFunctionBlock( function.inverseLengths(), function.values() );
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
