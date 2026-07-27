#ifndef NJOY_FORMAT_ACE_WRITE_ELECTROATOMIC_CREATEELASTICCROSSSECTIONBLOCK
#define NJOY_FORMAT_ACE_WRITE_ELECTROATOMIC_CREATEELASTICCROSSSECTIONBLOCK

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/electroatomic/ElasticCrossSectionBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
namespace electroatomic {

  /**
   *  @brief Create the elastic cross section block for electroatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid electroatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] electroatomic   the electroatomic data
   */
  inline std::optional< njoy::ACEtk::electroatomic::ElasticCrossSectionBlock >
  createElasticCrossSectionBlock( const dryad::ProjectileTarget& electroatomic ) {

    // identifiers
    decltype(auto) projectile = electroatomic.projectileIdentifier();
    decltype(auto) target = electroatomic.targetIdentifier();

    // check which eprdata format we want: only total elastic or large angle and total elastic
    dryad::id::ReactionID largeangle_id( projectile, target, dryad::id::ReactionType( projectile, 525 ) );
    if ( electroatomic.hasReaction( largeangle_id ) ) {

      // we need the transport corrected elastic cross section - defined as ( 1 - mubar ) * sigma
      // however, it is better to calculate this as ( 1 - mu )bar * sigma which we do here

      dryad::id::ReactionID elastic_id( projectile, target, dryad::id::ReactionType( projectile, 526 ) );

      decltype(auto) largeangle = electroatomic.reaction( largeangle_id );
      decltype(auto) electron = largeangle.product( dryad::id::ParticleID::electron() ).distributionData().value();
      decltype(auto) data = std::get< dryad::TabulatedAngularDistributions >( std::get< dryad::TwoBodyDistributionData >( electron ).angle() );

      std::vector< double > modified_mu;
      for ( const auto& distribution : data.distributions() ) {

        // get pdf values
        std::vector< double > values = distribution.values();

        // get cosines and transform to 1 - mu
        std::vector< double > mu = distribution.cosines();
        std::transform( mu.begin(), mu.end(), mu.begin(), [] ( auto&& value ) { return 1. - value; } );

        // reverse the vectors to get pdf(1-mu)
        std::reverse( mu.begin(), mu.end() );
        std::reverse( values.begin(), values.end() );

        // create a tabulated angular distirbution and calculate the mean
        dryad::TabulatedAngularDistributionFunction pdf( std::move( mu ), std::move( values ) );
        modified_mu.emplace_back( pdf.mean() );
      }

      // create a modified average cosine table
      dryad::TabulatedAverageCosine mubar( std::move( data.grid() ), std::move( modified_mu ),
                                           dryad::InterpolationType::LogLog );

      // evaluate the transport corrected large angle elastic scattering cross section
      std::vector< double > xs = largeangle.crossSection().values();
      std::vector< double > transport = largeangle.crossSection().energies();
      std::transform( transport.begin(), transport.end(), xs.begin(), transport.begin(),
                      [&] ( auto&& energy, auto&& sigma ) { return mubar( energy ) * sigma; } );

      // get the
      decltype(auto) elastic = electroatomic.reaction( elastic_id );
      xs = elastic.crossSection().values();

      return njoy::ACEtk::electroatomic::ElasticCrossSectionBlock( std::move( transport ), std::move( xs ) );
    }
    else {

      return std::nullopt;
    }
  }

} // electroatomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
