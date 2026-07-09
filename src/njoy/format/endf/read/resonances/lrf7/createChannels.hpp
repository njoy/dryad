#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATECHANNELS
#define NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATECHANNELS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/BoundaryCondition.hpp"
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createParticlePairs.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createFrohnerBackground.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createSammyBackground.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createTabulatedBackground.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the channels for a spin group
   *
   *  @param[in] projectile           the projectile identifier
   *  @param[in] target               the target identifier
   *  @param[in] boundary_condition   the boundary condition option
   *  @param[in] kinematics           the kinematics type to be applied
   *  @param[in] endfPairs            the parsed ENDF particle pairs
   *  @param[in] endfChannels         the parsed ENDF channels
   */
  inline auto createChannels(
                  const dryad::id::ParticleID& projectile,
                  const dryad::id::ParticleID& target,
                  const dryad::resonances::BoundaryCondition& boundary_condition,
                  const dryad::resonances::Kinematics& kinematics,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& endfPairs,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceChannels& endfChannels,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundChannels& endfBackground ) {

    std::vector< dryad::resonances::Channel > channels;

    // get spin and parity
    double spin = std::abs( endfChannels.spin() );
    short parity = spin == 0.0 ? endfChannels.parity() >= 0 ? +1 : -1
                               : endfChannels.spin() >= 0 ? +1 : -1;

    // get the particle pairs for these reactions
    auto pairs = lrf7::createParticlePairs( projectile, target, endfPairs );

    // get the incident particle pair
    auto pair = std::find_if( pairs.begin(), pairs.end(),
                              [&] ( auto&& pair ) {

                                return pair.has_value() ? ( pair->lightParticle().identifier() == projectile &&
                                                            pair->heavyParticle().identifier() == target )
                                                        : false;
                              } );
    dryad::resonances::ParticlePair incident = pair->value();

    // get the q values
    auto qvalues = format::createVector( endfPairs.Q() );

    // get the pnt values (whether or not to calculate penetrability)
    std::vector< bool > pnt( endfPairs.numberParticlePairs() );
    std::transform( endfPairs.penetrabilityFlag().begin(), endfPairs.penetrabilityFlag().end(),
                    pnt.begin(),
                    [] ( int pnt ) { return pnt != -1; } );

    // go over the channel information
    for ( unsigned int i = 0; i < endfChannels.numberChannels(); ++i ) {

      std::size_t index = endfChannels.particlePairNumbers()[i] - 1;

      std::optional< double > boundary = std::nullopt;
      if ( boundary_condition == dryad::resonances::BoundaryCondition::Constant ) {

        boundary = endfChannels.boundaryConditionValues()[i];
      }

      dryad::resonances::ChannelRadii radii( endfChannels.trueChannelRadii()[i] * constants::deca,
                                             endfChannels.effectiveChannelRadii()[i] * constants::deca );

      using Background = dryad::resonances::Channel::Background;
      std::optional< Background > background = std::nullopt;
      if ( endfBackground.KBK() > 0 ) {

        if ( endfBackground.backgroundRMatrices()[i].has_value() ) {

          using NoBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::NoBackgroundRMatrix;
          using TabulatedBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::TabulatedBackgroundRMatrix;
          using SammyBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SammyBackgroundRMatrix;
          using FrohnerBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::FrohnerBackgroundRMatrix;

          auto getBackground = tools::overload{

            [&] ( const NoBackgroundRMatrix& ) -> std::optional< Background > {

              return std::nullopt;
            },
            [&] ( const FrohnerBackgroundRMatrix& data ) -> std::optional< Background > {

              return createFrohnerBackground( data );
            },
            [&] ( const SammyBackgroundRMatrix& data ) -> std::optional< Background > {

              return createSammyBackground( data );
            },
            [&] ( const TabulatedBackgroundRMatrix& data ) -> std::optional< Background > {

              return createTabulatedBackground( data );
            }
          };

          background = std::visit( getBackground, endfBackground.backgroundRMatrices()[i].value() );
        }
      }

      channels.emplace_back( dryad::id::ChannelID( dryad::id::ReactionID( projectile, target, endfPairs.MT()[index] ),
                                                   dryad::resonances::ChannelQuantumNumbers( endfChannels.orbitalMomentumValues()[i],
                                                                                             endfChannels.channelSpinValues()[i],
                                                                                             spin, parity ),
                                                   std::nullopt ),
                             incident,
                             pairs[index],
                             qvalues[index],
                             std::move( boundary ),
                             std::move( radii ),
                             pnt[index],
                             kinematics,
                             std::move( background ) );
    }

    // loop over the channel instances and look for partials
    for ( std::size_t i = 0; i < channels.size(); ++i ) {

      auto counter = [&] ( auto&& channel ) {

        return channel.identifier() == channels[i].identifier();
      };

      std::size_t total = std::count_if( channels.begin(), channels.end(), counter );
      if ( total > 1 ) {

        std::size_t current = std::count_if( channels.begin(), std::next( channels.begin(), i ) , counter );
        dryad::id::ChannelID id( channels[i].identifier().reaction(), channels[i].identifier().quantumNumbers(), current );
        channels[i].identifier( id );
      }
    }

    return channels;
  }

} // lrf7 namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
