#ifndef NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATECHANNELDATA
#define NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATECHANNELDATA

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/convertEnergies.hpp"
#include "njoy/format/gnds/read/convertSquareRootEnergies.hpp"
#include "njoy/format/gnds/read/readTable.hpp"
#include "njoy/format/gnds/read/readFractionFromString.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createChannels.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create the channel data for a spin group
   *
   *  @param[in] formalism            the formalism to be applied
   *  @param[in] boundary_condition   the gnds boundary condition option
   *  @param[in] kinematics           the kinematics type to be applied
   *  @param[in] reduced_amplitudes   flag to indicate whether or not the widths are reduced or not
   *  @param[in] reactions            the resonance reaction information from the GNDS file
   *  @param[in] group                the GNDS spin group xml node
   */
  inline auto createChannelData(
                  const dryad::resonances::Formalism& formalism,
                  const BoundaryCondition& boundary_condition,
                  const dryad::resonances::Kinematics& kinematics,
                  bool reduced_amplitudes,
                  const ResonanceReactions& reactions,
                  const pugi::xml_node& group ) {

    // check that this is a valid resonanceReaction node
    throwExceptionOnWrongNode( group, "spinGroup" );

    std::vector< dryad::resonances::SpinGroup::ChannelData > channel_data;

    // get Jpi from the spin group attributes
    double spin = readFractionFromString( group.attribute( "spin" ).as_string() );
    short parity = group.attribute( "parity" ).as_int();

    // read the resonance parameter table
    auto channels = createChannels( boundary_condition, kinematics, reactions,
                                    spin, parity, group.child( "channels" ) );

    // read the resonance parameter table
    auto parameters = readTable( group.child( "resonanceParameters" ).child( "table" ) );
    convertEnergies( std::get< 1 >( parameters[0] ), std::get< 2 >( parameters[0] ).value() );

    for ( std::size_t i = 1; i < parameters.size(); ++i ) {

      if ( reduced_amplitudes ) {

        convertSquareRootEnergies( std::get< 1 >( parameters[i] ), std::get< 2 >( parameters[i] ).value() );
      }
      else {

        convertEnergies( std::get< 1 >( parameters[i] ), std::get< 2 >( parameters[i] ).value() );
      }
    }

    // loop over the channels
    std::size_t current = 0;
    for ( pugi::xml_node channel = group.child( "channels" ).child( "channel" );
          channel; channel = channel.next_sibling( "channel" ) ) {

      // get the column index in the table
      std::size_t column = channel.attribute( "columnIndex" ).as_int();

      // get the data
      std::vector< double > energies = std::get< 1 >( parameters[0] );
      std::vector< double > amplitudes = std::move( std::get< 1 >( parameters[column] ) );

      // remove zero widths
      auto is_zero = [] ( auto&& value ) { return value == 0.; };
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

            double penetrability = channels[current].penetrability( energy );
            return ( width < 0. ? -1. : +1. ) *
                   std::sqrt( 0.5 * std::abs( width ) / penetrability );
          };

          std::transform( amplitudes.begin(), amplitudes.end(),
                          energies.begin(), amplitudes.begin(), to_reduced_width );
        }
      }

      auto id = channels[current].identifier();
      auto is_elastic = id.reaction().target() == id.reaction().residual();
      auto is_capture = id.reaction().reactionType() == dryad::id::ReactionType( "capture" );
      auto is_reichmoore = formalism == dryad::resonances::Formalism::ReichMoore;

      if ( amplitudes.size() > 0 || is_elastic || ( is_capture && is_reichmoore ) ) {

        dryad::resonances::ResonanceTable table( id, std::move( energies ), std::move( amplitudes ) );
        channel_data.emplace_back( std::move( channels[current] ), std::move( table ) );
      }

      ++current;
    }

    return channel_data;
  }

} // rmatrix namespace
} // resonances namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
