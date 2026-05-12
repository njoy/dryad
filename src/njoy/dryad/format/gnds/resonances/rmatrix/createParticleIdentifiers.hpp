#ifndef NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATEPARTICLEIDENTIFIERS
#define NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATEPARTICLEIDENTIFIERS

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "njoy/dryad/format/adjustScatterLevel.hpp"
#include "njoy/dryad/format/gnds/resolveLink.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create the particle identifiers for resonance particles
   *
   *  @param[in] reactions   the GNDS resonanceReactions node
   */
  inline std::vector< id::ParticleID >
  createParticleIdentifiers( const id::ParticleID& projectile,
                             const id::ParticleID& target,
                             const pugi::xml_node& reactions ) {

    // check that this is a valid resonanceReactions node
    throwExceptionOnWrongNode( reactions, "resonanceReactions" );

    // the data for the resonance reactions
    std::vector< id::ParticleID > identifiers = { projectile, target };

    // loop over each reaction
    for ( pugi::xml_node reaction = reactions.child( "resonanceReaction" );
          reaction; reaction = reaction.next_sibling( "resonanceReaction" ) ) {

      auto link = reaction.child( "link" );
      if ( link ) {

        auto node = resolveLink( link );

        // the reaction identifier
        int mt = adjustScatterLevel( projectile, target, node.attribute( "ENDF_MT" ).as_int() );
        auto id = dryad::id::ReactionID( projectile, target, mt );

        // go over particles - if they are defined
        if ( id.particles().has_value() ) {

          if ( id.particles()->size() == 0 ) {

            identifiers.emplace_back( id::ParticleID::photon() );
          }

          for ( const auto& pair : id.particles().value() ) {

            identifiers.emplace_back( pair.first );
          }
        }

        // add the residual - if is is defined
        if ( id.residual().has_value() ) {

          identifiers.emplace_back( id.residual().value() );
        }
      }
      else {

        Log::error( "Could not find the link to the reaction node for a resonance reaction" );
        throw std::exception();
      }
    }

    std::sort( identifiers.begin(), identifiers.end() );
    identifiers.erase( std::unique( identifiers.begin(), identifiers.end() ), identifiers.end() );

    return identifiers;
  }

} // rmatrix namespace
} // resonances namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
