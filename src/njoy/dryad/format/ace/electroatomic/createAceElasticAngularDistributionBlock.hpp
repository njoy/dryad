#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEACEELASTICANGULARDISTRIBUTIONBLOCK
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEACEELASTICANGULARDISTRIBUTIONBLOCK

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/electroatomic/ElasticAngularDistributionBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create the elastic angular distribution block for electroatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid electroatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] electroatomic   the electroatomic data
   */
  inline njoy::ACEtk::electroatomic::ElasticAngularDistributionBlock
  createAceElasticAngularDistributionBlock( const ProjectileTarget& electroatomic ) {

    // identifiers
    decltype(auto) projectile = electroatomic.projectileIdentifier();
    decltype(auto) target = electroatomic.targetIdentifier();

    // check which eprdata format we want: only total elastic or large angle and total elastic
    dryad::id::ReactionID elastic_id( projectile, target, dryad::id::ReactionType( projectile, 525 ) );
    if ( ! electroatomic.hasReaction( elastic_id ) ) {

      elastic_id = dryad::id::ReactionID( projectile, target, dryad::id::ReactionType( projectile, 526 ) );
    }

    decltype(auto) elastic = electroatomic.reaction( elastic_id );
    decltype(auto) electron = elastic.product( dryad::id::ParticleID::electron() ).distributionData().value();
    decltype(auto) data = std::get< dryad::TabulatedAngularDistributions >( std::get< dryad::TwoBodyDistributionData >( electron ).angle() );

    std::vector< njoy::ACEtk::electroatomic::TabulatedAngularDistribution > distributions;
    for ( unsigned int i = 0; i < data.numberPoints(); ++i ) {

      double incident = data.grid()[i];
      decltype(auto) distribution = data.distributions()[i];

      std::vector< double > cosines;
      std::vector< double > values;
      if ( ! distribution.cdf().isLinearised() ) {

        auto linearised = distribution.linearise();
        linearised.normalise();
        cosines = linearised.cdf().cosines();
        values = linearised.cdf().values();
      }
      else {

        cosines = distribution.cdf().cosines();
        values = distribution.cdf().values();
      }
      distributions.emplace_back( incident * constants::micro, std::move( cosines ), std::move( values ) );
    }
    return njoy::ACEtk::electroatomic::ElasticAngularDistributionBlock( std::move( distributions ) );
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
