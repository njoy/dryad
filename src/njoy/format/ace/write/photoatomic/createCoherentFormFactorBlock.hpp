#ifndef NJOY_FORMAT_ACE_WRITE_PHOTOATOMIC_CREATECOHERENTFORMFACTORBLOCK
#define NJOY_FORMAT_ACE_WRITE_PHOTOATOMIC_CREATECOHERENTFORMFACTORBLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/photoatomic/CoherentFormFactorBlock.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
namespace photoatomic {

  /**
   *  @brief Create the coherent form factor block for photoatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid photoatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] photoatomic   the photoatomic data
   */
  inline njoy::ACEtk::photoatomic::CoherentFormFactorBlock
  createCoherentFormFactorBlock( const dryad::ProjectileTarget& photoatomic ) {

    decltype(auto) projectile = photoatomic.projectileIdentifier();
    decltype(auto) target = photoatomic.targetIdentifier();
    dryad::id::ReactionID coherent_id( projectile, target, dryad::id::ReactionType( projectile, 502 ) );

    decltype(auto) coherent = photoatomic.reaction( coherent_id );
    decltype(auto) photon = coherent.product( dryad::id::ParticleID::photon() ).distributionData().value();
    decltype(auto) function = std::get< dryad::CoherentDistributionData >( photon ).scatteringFunction();

    // calculate the integral of the form factor
    auto z = target.z();
    std::vector< double > vsquared = function.inverseLengths();
    std::transform( vsquared.begin(), vsquared.end(), vsquared.begin(),
                    [] ( auto&& value ) { return value * value; } );
    std::vector< double > fsquared = function.values();
    std::transform( fsquared.begin(), fsquared.end(), fsquared.begin(),
                    [&] ( auto&& value ) { return value * value / z / z; } );
    scion::math::InterpolationTable< double, double > table( std::move( vsquared ), std::move( fsquared ) );

    return njoy::ACEtk::photoatomic::CoherentFormFactorBlock(
               function.inverseLengths(), table.cumulativeIntegral(), function.values() );
  }

} // photoatomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
