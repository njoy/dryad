#ifndef NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATERESONANCEREACTION
#define NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATERESONANCEREACTION

// system includes
#include <tuple>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/resonances/ChannelRadii.hpp"
#include "njoy/dryad/format/adjustScatterLevel.hpp"
#include "njoy/dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "njoy/dryad/format/gnds/resolveLink.hpp"
#include "njoy/dryad/format/gnds/createQValue.hpp"
#include "njoy/dryad/format/gnds/resonances/createRadius.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace resonances {
namespace rmatrix {

  // reaction id, Q value, radius for P and S, radius for phi
  using ResonanceReaction = std::tuple< dryad::id::ReactionID, double,
                                        dryad::resonances::ChannelRadii >;

  /**
   *  @brief Create the information for a resonance reaction
   *
   *  @param[in] reaction   the GNDS resonanceReaction node
   */
  inline ResonanceReaction
  createResonanceReaction( const id::ParticleID& projectile,
                           const id::ParticleID& target,
                           const pugi::xml_node& reaction,
                           const dryad::resonances::ChannelRadii& radii,
                           const std::string& style = "eval" ) {

    // check that this is a valid resonanceReaction node
    throwExceptionOnWrongNode( reaction, "resonanceReaction" );

    // the data for the resonance reaction
    ResonanceReaction data;

    // go to the reaction and get the information we need: id and Q value
    auto link = reaction.child( "link" );
    if ( link ) {

      auto node = resolveLink( link );

      // the reaction identifier
      int mt = adjustScatterLevel( projectile, target, node.attribute( "ENDF_MT" ).as_int() );
      std::get< 0 >( data ) = dryad::id::ReactionID( projectile, target, mt );

      // the Q value
      auto output = node.child( "outputChannel" );
      std::get< 1 >( data ) = createQValue( output.child( "Q" ), style );

      // assign the default radii
      std::get< 2 >( data ) = radii;
    }
    else {

      Log::error( "Could not find the link to the reaction node for a resonance reaction" );
      throw std::exception();
    }

    // check for a Q value
    auto node = reaction.child( "Q" );
    if ( node ) {

      std::get< 1 >( data ) = createQValue( node, style );
    }

    // check for radii
    node = reaction.child( "scatteringRadius" );
    if ( node ) {

      std::get< 2 >( data ).penetrabilityRadius( createRadius( node ) );
    }
    node = reaction.child( "hardSphereRadius" );
    if ( node ) {

      std::get< 2 >( data ).phaseShiftRadius( createRadius( node ) );
    }

    return data;
  }

} // rmatrix namespace
} // resonances namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
