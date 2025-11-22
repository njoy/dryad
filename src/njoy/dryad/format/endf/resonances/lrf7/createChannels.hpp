#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATECHANNELS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATECHANNELS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/BoundaryCondition.hpp"
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createParticlePairs.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
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
                  const id::ParticleID& projectile,
                  const id::ParticleID& target,
                  const dryad::resonances::BoundaryCondition& boundary_condition,
                  const dryad::resonances::Kinematics& kinematics,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& endfPairs,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceChannels& endfChannels ) {

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

    // go over the channel information
    for ( unsigned int i = 0; i < endfChannels.numberChannels(); ++i ) {

      std::size_t index = endfChannels.particlePairNumbers()[i] - 1;

      std::optional< std::size_t > partial = std::nullopt;
      if ( std::count( endfChannels.particlePairNumbers().begin(),
                       endfChannels.particlePairNumbers().end(),
                       endfChannels.particlePairNumbers()[i] ) > 1 ) {

        std::size_t number = 0;
        std::size_t current = 0;
        for ( unsigned int j = 0; j < endfChannels.numberChannels(); ++j ) {

          if ( i != j && endfChannels.particlePairNumbers()[j] == endfChannels.particlePairNumbers()[i]
                      && endfChannels.orbitalMomentumValues()[j] == endfChannels.orbitalMomentumValues()[i]
                      && endfChannels.channelSpinValues()[j] == endfChannels.channelSpinValues()[i] ) {

            number += 1;
            if ( j < i ) {

              current += 1;
            }
          }
        }
        if ( number > 0 ) {

          partial = current;
        }
      }

      std::optional< double > boundary = std::nullopt;
      if ( boundary_condition == dryad::resonances::BoundaryCondition::Constant ) {

        boundary = endfChannels.boundaryConditionValues()[i];
      }

      dryad::resonances::ChannelRadii radii( endfChannels.trueChannelRadii()[i] * constants::deca,
                                             endfChannels.effectiveChannelRadii()[i] * constants::deca );

      channels.emplace_back( id::ChannelID( id::ReactionID( projectile, target, endfPairs.MT()[index] ),
                                            dryad::resonances::ChannelQuantumNumbers( endfChannels.orbitalMomentumValues()[i],
                                                                                      endfChannels.channelSpinValues()[i],
                                                                                      spin, parity ),
                                            std::move( partial ) ),
                             incident,
                             pairs[index],
                             qvalues[index],
                             std::move( boundary ),
                             std::move( radii ),
                             kinematics );
    }

    return channels;
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
