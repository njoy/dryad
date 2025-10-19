#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATESPINGROUP
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATESPINGROUP

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/resonances/SpinGroup.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/resonances/lrf7/createParticlePairs.hpp"
#include "dryad/format/endf/resonances/lrf7/createChannels.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the spin groups
   */
  auto createSpinGroups( const id::ParticleID& projectile,
                         const id::ParticleID& target,
                         const ENDFtk::section::Type< 2, 151 >::RMatrixLimited& endf ) {

    std::vector< dryad::resonances::SpinGroup > groups;

    // check the type of resonances
    bool reduced_amplitudes = endf.reducedWidths();

    // get the reaction identifiers for resonance reactions
    std::vector< id::ReactionID > reactions( endf.particlePairs().numberParticlePairs() );
    std::transform( endf.particlePairs().MT().begin(), endf.particlePairs().MT().end(),
                    reactions.begin(),
                    [&] ( int mt ) { return id::ReactionID( projectile, target, mt ); } );

    // get the particle pairs for these reactions
    auto pairs = lrf7::createParticlePairs( reactions, endf.particlePairs() );

    // get the incident particle pair
    auto find_incident = [&] ( auto&& pair ) {

      return pair.has_value() ? ( pair->particle().identifier() == projectile &&
                                  pair->residual().identifier() == target )
                              : false;
    };
    auto iter = std::find_if( pairs.begin(), pairs.end(), find_incident );
    dryad::resonances::ParticlePair incident = iter->value();

    // get the q values
    auto qvalues = format::createVector( endf.particlePairs().Q() );

    // see if we have to read boundary conditions
    bool boundaries = std::any_of( endf.particlePairs().shiftFactorFlag().begin(),
                                   endf.particlePairs().shiftFactorFlag().end(),
                                   [] ( auto&& flag ) { return flag == 1; } );

    // go over each spin group
    for ( const auto& group : endf.spinGroups() ) {

      // get the channels in this spin group
      auto channels = lrf7::createChannels( incident, pairs, reactions, qvalues,
                                            boundaries, group.channels() );

      // get the channel identifiers
      std::vector< id::ChannelID > identifiers( channels.size() );
      std::transform( channels.begin(), channels.end(), identifiers.begin(),
                      [] ( auto&& channel ) { return channel.identifier(); } );

      // get the resonance energies
      auto energies = format::createVector( group.parameters().resonanceEnergies() );

      // get the reduced width amplitudes
      std::vector< std::vector< double > > amplitudes;
      for ( unsigned int i = 0; i < channels.size(); ++i ) {

        amplitudes.emplace_back( format::createVector( group.parameters().GAM(i) ) );
        if ( ! reduced_amplitudes ) {

          auto to_reduced_width = [&] ( auto&& width, auto&& energy ) {

            double penetrability = channels[i].penetrability( energy );
            return ( width < 0. ? -1. : +1. ) *
                   std::sqrt( 0.5 * std::abs( width ) / penetrability );
          };

          std::transform( amplitudes.back().begin(), amplitudes.back().end(),
                          energies.begin(), amplitudes.back().begin(), to_reduced_width );
        }
      }

      dryad::resonances::ResonanceTable table( std::move( identifiers ), std::move( energies ),
                                               std::move( amplitudes ) );
      groups.emplace_back( std::move( channels ), std::move(table ) );
    }

    return groups;
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
