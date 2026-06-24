#ifndef NJOY_FORMAT_ACE_WRITE_PHOTOATOMIC_CREATECOMPTONPROFILEBLOCK
#define NJOY_FORMAT_ACE_WRITE_PHOTOATOMIC_CREATECOMPTONPROFILEBLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/photoatomic/ComptonProfileBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
namespace photoatomic {

  /**
   *  @brief Create the incoherent compton profile block for photoatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid photoatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.). In particular,
   *  this function assumes that there are Compton profiles and that they have been
   *  normalised.
   *
   *  @param[in] photoatomic   the photoatomic data
   */
  inline njoy::ACEtk::photoatomic::ComptonProfileBlock
  createComptonProfileBlock( const dryad::ProjectileTarget& photoatomic ) {

    decltype(auto) projectile = photoatomic.projectileIdentifier();
    decltype(auto) target = photoatomic.targetIdentifier();
    dryad::id::ReactionID incoherent_id( projectile, target, dryad::id::ReactionType( projectile, 504 ) );

    decltype(auto) incoherent = photoatomic.reaction( incoherent_id );
    decltype(auto) photon = incoherent.product( dryad::id::ParticleID::photon() ).distributionData().value();
    decltype(auto) profiles = std::get< dryad::IncoherentDistributionData >( photon ).comptonProfiles().value();

    std::vector< njoy::ACEtk::photoatomic::ComptonProfile > compton_profiles;
    for ( const auto& profile : profiles ) {

      int interpolation_type = 2; // lin-lin interpolation
      std::vector< double > momentum;
      std::vector< double > pdf;
      std::vector< double > cdf;
      if ( ! profile.cdf().isLinearised() ) {

        auto linearised = profile.linearise();
        linearised.normalise();
        momentum = linearised.pdf().momentum();
        pdf = linearised.pdf().values();
        cdf = linearised.cdf().values();
      }
      else {

        momentum = profile.pdf().momentum();
        pdf = profile.pdf().values();
        cdf = profile.cdf().values();
      }
      compton_profiles.emplace_back( interpolation_type, std::move( momentum ), std::move( pdf ), std::move( cdf ) );
    }

    return njoy::ACEtk::photoatomic::ComptonProfileBlock( std::move( compton_profiles ) );
  }

} // photoatomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
