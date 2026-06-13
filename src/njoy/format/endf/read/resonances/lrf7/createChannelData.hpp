#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATECHANNELDATA
#define NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATECHANNELDATA

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createChannels.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the channel data for a spin group
   *
   *  @param[in] projectile           the projectile identifier
   *  @param[in] target               the target identifier
   *  @param[in] boundary_condition   the boundary condition option
   *  @param[in] kinematics           the kinematics type to be applied
   *  @param[in] reduced_amplitudes   flag to indicate whether or not the widths are reduced or not
   *  @param[in] endfPairs            the parsed ENDF particle pairs
   *  @param[in] endfSpinGroup        the parsed ENDF spin group
   */
  inline auto createChannelData(
                  const dryad::id::ParticleID& projectile,
                  const dryad::id::ParticleID& target,
                  const dryad::resonances::BoundaryCondition& boundary_condition,
                  const dryad::resonances::Kinematics& kinematics,
                  bool reduced_amplitudes,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& endfPairs,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SpinGroup& endfSpinGroup ) {

    std::vector< dryad::resonances::SpinGroup::ChannelData > channel_data;

    // get the channels
    auto channels = lrf7::createChannels( projectile, target, boundary_condition,
                                          kinematics, endfPairs, endfSpinGroup.channels(),
                                          endfSpinGroup.background() );

    // go over all channels
    for ( unsigned int i = 0; i < channels.size(); ++i ) {

      // get the energies and amplitudes
      std::vector< double > energies;
      std::vector< double > amplitudes;
      if ( endfSpinGroup.parameters().numberResonances() != 0 ) {

        // get the data
        energies = format::createVector( endfSpinGroup.parameters().resonanceEnergies() );
        amplitudes = format::createVector( endfSpinGroup.parameters().GAM(i) );

        // remove zero widths
        auto is_zero= [] ( auto&& value ) { return value == 0.; };
        auto amplitude = std::find_if( amplitudes.begin(), amplitudes.end(), is_zero );
        while ( amplitude != amplitudes.end() ) {

          auto index = std::distance( amplitudes.begin(), amplitude );
          amplitude = amplitudes.erase( amplitude );
          energies.erase( energies.begin() + index );
          amplitude = std::find_if( amplitude, amplitudes.end(), is_zero );
        }

        // if there are non-zero widths left
        if ( amplitudes.size() != 0 ) {

          // transform into reduced width if required
          if ( ! reduced_amplitudes ) {

            auto to_reduced_width = [&] ( auto&& width, auto&& energy ) {

              double penetrability = channels[i].penetrability( energy );
              return ( width < 0. ? -1. : +1. ) *
                     std::sqrt( 0.5 * std::abs( width ) / penetrability );
            };

            std::transform( amplitudes.begin(), amplitudes.end(),
                            energies.begin(), amplitudes.begin(), to_reduced_width );
          }
        }
      }

      auto id = channels[i].identifier();
      auto is_elastic = id.reaction().target() == id.reaction().residual();
      auto is_capture = id.reaction().reactionType() == dryad::id::ReactionType( "capture" );

      if ( amplitudes.size() > 0 || is_elastic || is_capture ) {

        dryad::resonances::ResonanceTable table( id, std::move( energies ), std::move( amplitudes ) );
        channel_data.emplace_back( std::move( channels[i] ), std::move( table ) );
      }
    }

    return channel_data;
  }

} // lrf7 namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
