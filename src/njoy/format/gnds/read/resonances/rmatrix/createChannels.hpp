#ifndef NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATECHANNELS
#define NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATECHANNELS

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createChannel.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create the channels
   *
   *  @param[in] boundary_condition   the gnds boundary condition option
   *  @param[in] kinematics           the kinematics type to be applied
   *  @param[in] reactions            the resonance reaction information from the GNDS file
   *  @param[in] spin                 the total angular momentum value
   *  @param[in] parity               the parity
   *  @param[in] channels             the GNDS channels xml node
   */
  inline auto createChannels(
                  const BoundaryCondition& boundary_condition,
                  const dryad::resonances::Kinematics& kinematics,
                  const ResonanceReactions& reactions,
                  double spin,
                  short parity,
                  const pugi::xml_node& channels ) {

    // check that this is a valid channel node
    throwExceptionOnWrongNode( channels, "channels" );

    std::vector< dryad::resonances::Channel > data;

    // loop over the channel nodes and create Channel instances
    for ( pugi::xml_node channel = channels.child( "channel" );
          channel; channel = channel.next_sibling( "channel" ) ) {

      data.emplace_back( createChannel( boundary_condition, kinematics, reactions,
                                        spin, parity, std::nullopt, channel ) );
    }

    // loop over the channel instances and look for partials
    for ( std::size_t i = 0; i < data.size(); ++i ) {

      auto counter = [&] ( auto&& channel ) {

        return channel.identifier() == data[i].identifier();
      };

      std::size_t total = std::count_if( data.begin(), data.end(), counter );
      if ( total > 1 ) {

        std::size_t current = std::count_if( data.begin(), std::next( data.begin(), i ) , counter );
        dryad::id::ChannelID id( data[i].identifier().reaction(), data[i].identifier().quantumNumbers(), current );
        data[i].identifier( id );
      }
    }

    return data;
  }

} // rmatrix namespace
} // resonances namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
