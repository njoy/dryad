#ifndef NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATECHANNEL
#define NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATECHANNEL

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/readFractionFromString.hpp"
#include "njoy/format/gnds/read/resonances/createRadius.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createBackground.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createBoundaryCondition.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createResonanceReactions.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create the channel
   *
   *  @param[in] boundary_condition   the gnds boundary condition option
   *  @param[in] kinematics           the kinematics type to be applied
   *  @param[in] reactions            the resonance reaction information from the GNDS file
   *  @param[in] spin                 the total angular momentum value
   *  @param[in] parity               the parity
   *  @param[in] partial              the optional partial id for a channel
   *  @param[in] channel              the GNDS channel xml node
   */
  inline auto createChannel(
                  const BoundaryCondition& boundary_condition,
                  const dryad::resonances::Kinematics& kinematics,
                  const ResonanceReactions& reactions,
                  double spin,
                  short parity,
                  std::optional< std::size_t > partial,
                  const pugi::xml_node& channel ) {

    // check that this is a valid channel node
    throwExceptionOnWrongNode( channel, "channel" );

    // get the resonance reaction label and the index in the table
    ResonanceReaction reaction = reactions.at( channel.attribute( "resonanceReaction" ).as_string() );

    // get the channel quantum numbers and create the channel ID
    unsigned int l = channel.attribute( "L" ).as_int();
    double s = readFractionFromString( channel.attribute( "channelSpin" ).as_string() );

    // if it is an eliminated capture channel, set l and s to 0
    if ( std::get< 6 >( reaction ) &&
         std::get< 0 >( reaction ).particles().has_value() &&
         std::get< 0 >( reaction ).particles()->size() == 0 ) {

      l = 0;
      s = 0;
    }
    else {

      if ( std::get< 6 >( reaction ) &&
           ( ( std::get< 0 >( reaction ).particles().has_value() &&
               std::get< 0 >( reaction ).particles()->size() == 0 ) ||
             ! std::get< 0 >( reaction ).particles().has_value() ) ) {

        Log::error( "Only capture channels can be eliminated" );
        throw std::exception();
      }
    }

    // create the identifier
    dryad::id::ChannelID id( std::get< 0 >( reaction ),
                             dryad::resonances::ChannelQuantumNumbers( l, s, spin, parity ),
                             std::move( partial ) );

    // optional background element
    std::optional< dryad::resonances::Channel::Background > background = std::nullopt;

    // check for override for the boundary condition value or set the value
    auto boundary = channel.attribute( "boundaryConditionValue" );
    if ( boundary ) {

      if ( boundary_condition == BoundaryCondition::Constant ) {

        std::get< 5 >( reaction ) = boundary.as_double();
      }
      else {

        Log::error( "A boundaryConditionValue attribute is defined for a channel node, but the "
                    "boundary condition type set on the RMatrix node is not constant" );
        throw std::exception();
      }
    }
    if ( boundary_condition == BoundaryCondition::NegativeOrbitalMomentum ) {

      std::get< 5 >( reaction ) = -static_cast< double >( l );
    }

    // check for override for radii
    auto node = channel.child( "scatteringRadius" );
    if ( node ) {

      std::get< 4 >( reaction ).penetrabilityRadius( createRadius( node ) );
    }
    node = channel.child( "hardSphereRadius" );
    if ( node ) {

      std::get< 4 >( reaction ).phaseShiftRadius( createRadius( node ) );
    }

    // check for background
    node = channel.child( "externalRMatrix" );
    if ( node ) {

      background = createBackground( node );
    }

    return dryad::resonances::Channel( std::move( id ),
                                       std::move( std::get< 1 >( reaction ) ),
                                       std::move( std::get< 2 >( reaction ) ),
                                       std::move( std::get< 3 >( reaction ) ),
                                       std::move( std::get< 5 >( reaction ) ),
                                       std::move( std::get< 4 >( reaction ) ),
                                       kinematics,
                                       std::move( background ) );
  }

} // rmatrix namespace
} // resonances namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
