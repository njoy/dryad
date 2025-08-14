#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEPROJECTILETARGET
#define NJOY_DRYAD_FORMAT_GNDS_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/createParticleIdentifier.hpp"
#include "dryad/format/gnds/createInteractionType.hpp"
#include "dryad/format/gnds/createReactions.hpp"
#include "dryad/ProjectileTarget.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a ProjectileTarget from a GNDS xml document
   *
   *  @param[in] document     the gnds xml document
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   *  @param[in] style        the gnds style to process (default is eval)
   */
  static ProjectileTarget
  createProjectileTarget( const pugi::xml_document& document,
                          bool normalise,
                          const std::string& style = "eval" ) {

    auto suite = document.child( "reactionSuite" );

    if ( suite ) {

      id::ParticleID projectile = createParticleIdentifier( suite.attribute( "projectile" ).as_string() );
      id::ParticleID target( suite.attribute( "target" ).as_string() );
      InteractionType type = createInteractionType( suite.attribute( "interaction" ).as_string() );

      std::vector< Reaction > reactions = createReactions( projectile, target, suite, normalise, style );

      return ProjectileTarget( std::move( projectile ), std::move( target ),
                               type, std::move( reactions ) );
    }
    else {

      Log::error( "The GNDS file does not contain projectile-target data" );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
