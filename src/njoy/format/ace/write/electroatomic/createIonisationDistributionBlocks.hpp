#ifndef NJOY_FORMAT_ACE_WRITE_ELECTROATOMIC_CREATEIONISATIONDISTRIBUTIONBLOCKS
#define NJOY_FORMAT_ACE_WRITE_ELECTROATOMIC_CREATEIONISATIONDISTRIBUTIONBLOCKS

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/electroatomic/EnergyDistributionBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
namespace electroatomic {

  /**
   *  @brief Create the ionisation electron energy distribution block for electroatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid electroatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] electroatomic   the electroatomic data
   */
  inline std::vector< njoy::ACEtk::electroatomic::EnergyDistributionBlock >
  createIonisationDistributionBlocks( const dryad::ProjectileTarget& electroatomic ) {

    // energy is converted to MeV
    auto convertEnergy = [] ( auto&& energy ) {

      return energy * constants::micro;
    };

    // identifiers
    decltype(auto) projectile = electroatomic.projectileIdentifier();
    decltype(auto) target = electroatomic.targetIdentifier();
    dryad::id::ReactionID totalionisation_id( projectile, target, dryad::id::ReactionType( projectile, 522 ) );

    std::vector< njoy::ACEtk::electroatomic::EnergyDistributionBlock > ionisonisation;
    for ( auto&& id : electroatomic.reaction( totalionisation_id ).partialReactionIdentifiers().value() ) {

      decltype(auto) ionisation = electroatomic.reaction( id );
      decltype(auto) electron = ionisation.product( dryad::id::ParticleID::electron() ).distributionData().value();
      decltype(auto) data = std::get< dryad::TabulatedEnergyDistributions >( std::get< dryad::UncorrelatedDistributionData >( electron ).energy() );

      std::vector< njoy::ACEtk::electroatomic::TabulatedEnergyDistribution > distributions;
      for ( unsigned int i = 0; i < data.numberPoints(); ++i ) {

        double incident = data.grid()[i];
        decltype(auto) distribution = data.distributions()[i];

        std::vector< double > energies;
        std::vector< double > values;
        if ( ! distribution.cdf().isLinearised() ) {

          auto linearised = distribution.linearise();
          linearised.normalise();
          energies = linearised.cdf().energies();
          values = linearised.cdf().values();
        }
        else {

          energies = distribution.cdf().energies();
          values = distribution.cdf().values();
        }
        std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );
        distributions.emplace_back( convertEnergy( incident ), std::move( energies ), std::move( values ) );
      }

      ionisonisation.emplace_back( std::move( distributions ) );
    }

    return ionisonisation;
  }

} // electroatomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
