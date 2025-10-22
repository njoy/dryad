#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATESPINGROUP
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATESPINGROUP

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/resonances/SpinGroup.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/resonances/lrf7/createBoundaryCondition.hpp"
#include "dryad/format/endf/resonances/lrf7/createChannelData.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the spin groups for LRF7 resonance parameters
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] endf         the parsed ENDF LRF7 data
   */
  auto createSpinGroups( const id::ParticleID& projectile,
                         const id::ParticleID& target,
                         const ENDFtk::section::Type< 2, 151 >::RMatrixLimited& endf ) {

    std::vector< dryad::resonances::SpinGroup > groups;

    // check the type of resonances
    bool reduced_amplitudes = endf.reducedWidths();

    // determine the boundary condition
    auto boundary_condition = lrf7::createBoundaryCondition( endf.particlePairs() );

    // go over each spin group and collect all channel data
    std::vector< dryad::resonances::SpinGroup::ChannelData > channel_data;
    for ( const auto& group : endf.spinGroups() ) {

      // get the channel data in this spin group
      auto data = lrf7::createChannelData( projectile, target,
                                           boundary_condition, reduced_amplitudes,
                                           endf.particlePairs(), group );

      // add each to the final channel data
      for ( auto&& channel : data ) {

        auto iter = std::lower_bound( channel_data.begin(), channel_data.end(),
                                      channel.first.identifier(),
                                      [] ( auto&& left, auto&& right )
                                         { return left.first.identifier() < right; } );
        if ( iter != channel_data.end() ) {

          // if the channel is already present: consolidate
          if ( iter->first.identifier() == channel.first.identifier() ) {

            if ( channel.first == iter->first ) {

              // add the resonances to the table
              for ( unsigned int i = 0; i < channel.second.numberEnergies(); ++i ) {

                auto energy = std::lower_bound( iter->second.energies().begin(), iter->second.energies().end(),
                                                channel.second.energies()[i] );
                auto amplitude = iter->second.reducedWidthAmplitudes().front().begin() +
                                 std::distance( iter->second.energies().begin(), energy );
                if ( energy != iter->second.energies().end() ) {

                  // if the energies are equal: throw exception
                  if ( *energy == channel.second.energies()[i] ) {

                    Log::error( "Found the same channel in two spin groups with overlapping resonance energies" );
                    Log::info( "Channel: {}", channel.first.identifier().symbol() );
                    throw std::exception();
                  }
                }
                iter->second.energies().insert( energy, channel.second.energies()[i] );
                iter->second.reducedWidthAmplitudes().front().insert( amplitude, channel.second.reducedWidthAmplitudes().front()[i] );
              }

              continue;
            }
            else {

              Log::error( "Found at least two channels with equal quantum numbers but with "
                          "differences in other channel data" );
              Log::info( "Quantum numbers: {}", channel.first.quantumNumbers().symbol() );
              Log::info( "Equal incident particle pair: {}", channel.first.incidentParticlePair() == iter->first.incidentParticlePair() );
              Log::info( "Equal outgoing particle pair: {}", channel.first.outgoingParticlePair() == iter->first.outgoingParticlePair() );
              Log::info( "Equal boundary condition: {}", channel.first.boundaryCondition() == iter->first.boundaryCondition() );
              Log::info( "Equal Q value: {}", channel.first.qValue() == iter->first.qValue() );
              throw std::exception();
            }
          }
        }
        channel_data.insert( iter, std::move( channel ) );
      }
    }

    // lexographical sort by Jpi,l,s,reaction
    const auto getSortingOrder = [] ( const auto& data ) {

      return std::make_tuple( data.first.quantumNumbers().totalAngularMomentum(),
                              data.first.quantumNumbers().parity(),
                              data.first.quantumNumbers().orbitalAngularMomentum(),
                              data.first.quantumNumbers().spin(),
                              data.first.reaction() );
    };
    std::sort( channel_data.begin(), channel_data.end(),
               [&] ( auto&& left, auto&& right )
                   { return getSortingOrder( left ) < getSortingOrder( right ); } );

    // create the spin groups
    const auto getJpi = [] ( const auto& data ) {

      return std::make_tuple( data.first.quantumNumbers().totalAngularMomentum(),
                              data.first.quantumNumbers().parity() );
    };
    auto iter = channel_data.begin();
    while ( iter != channel_data.end() ) {

      auto begin = iter;
      iter = std::upper_bound( begin, channel_data.end(),
                               getJpi( *begin ),
                               [&] ( auto&& left, auto&& right )
                                   { return left < getJpi( right ); } );
      groups.emplace_back( std::vector< dryad::resonances::SpinGroup::ChannelData >{ begin, iter } );
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
