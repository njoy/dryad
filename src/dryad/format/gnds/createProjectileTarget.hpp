#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEPROJECTILETARGET
#define NJOY_DRYAD_FORMAT_GNDS_CREATEPROJECTILETARGET

// system includes
#include <vector>
#include <iostream>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/createInteractionType.hpp"
#include "dryad/format/gnds/createReactions.hpp"
#include "dryad/ProjectileTarget.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a ProjectileTarget from a GNDS reactionSuite
   */
  static ProjectileTarget 
  createProjectileTarget( const pugi::xml_document& document,
                          const std::string& style = "eval" ) {

    auto suite = document.child( "reactionSuite" );

    id::ParticleID projectile( suite.attribute( "projectile" ).as_string() );
    id::ParticleID target( suite.attribute( "target" ).as_string() );
    InteractionType type = createInteractionType( suite.attribute( "interaction" ).as_string() );

    std::vector< Reaction > reactions = createReactions( projectile, target, suite, style );

    return ProjectileTarget( std::move( projectile ), std::move( target ),
                             type, std::move( reactions ) );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
