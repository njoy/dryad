#ifndef NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATERESONANCEREACTIONS
#define NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATERESONANCEREACTIONS

// system includes
#include <map>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "njoy/dryad/format/gnds/resonances/rmatrix/createResonanceReaction.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace resonances {
namespace rmatrix {

  using ResonanceReactions = std::map< std::string, ResonanceReaction >;

  /**
   *  @brief Create the information for all resonance reactions
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] reactions    the GNDS resonanceReactions node
   *  @param[in] particles    the particle data from the global and local pops
   *  @param[in] radii        the previously read channel radii
   *  @param[in] style        the gnds style to process (default is eval)
   */
  inline ResonanceReactions
  createResonanceReactions( const id::ParticleID& projectile,
                            const id::ParticleID& target,
                            const pugi::xml_node& reactions,
                            const std::vector< Particle >& particles,
                            const dryad::resonances::ChannelRadii& radii,
                            const std::string& style = "eval" ) {

    // check that this is a valid resonanceReactions node
    throwExceptionOnWrongNode( reactions, "resonanceReactions" );

    // the data for the resonance reactions
    ResonanceReactions data;

    // loop over each reaction
    for ( pugi::xml_node reaction = reactions.child( "resonanceReaction" );
          reaction; reaction = reaction.next_sibling( "resonanceReaction" ) ) {

      data[ reaction.attribute( "label" ).as_string() ]
      = createResonanceReaction( projectile, target, reaction, particles, radii, style );
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
