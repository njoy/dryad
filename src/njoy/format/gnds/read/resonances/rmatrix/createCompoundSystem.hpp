#ifndef NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATECOMPOUNDSYSTEM
#define NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATECOMPOUNDSYSTEM

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/format/gnds/read/pops/createParticleDatabase.hpp"
#include "njoy/format/gnds/read/resonances/createParticles.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createParticleIdentifiers.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createResonanceReactions.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createBoundaryCondition.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createFormalism.hpp"
#include "njoy/format/gnds/read/resonances/rmatrix/createSpinGroups.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create the compound system for rmatrix resonance parameters
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] lower        the lower energy limit
   *  @param[in] upper        the upper energy limit
   *  @param[in] pops         the particle database read from the file
   *  @param[in] radii        the channel radii read from the file
   *  @param[in] rmatrix      the GNDS rmatrix xml node
   *  @param[in] style        the gnds style to process (default is eval)
   */
  inline auto createCompoundSystem( const dryad::id::ParticleID& projectile,
                                    const dryad::id::ParticleID& target,
                                    double lower,
                                    double upper,
                                    const dryad::ParticleDatabase& pops,
                                    const dryad::resonances::ChannelRadii& radii,
                                    const pugi::xml_node& rmatrix,
                                    const std::string& style = "eval" ) {

    // check that this is a valid rmatrix node
    throwExceptionOnWrongNode( rmatrix, "RMatrix" );

    auto formalism = createFormalism( rmatrix.attribute( "approximation" ).as_string() );
    auto kinematics = dryad::resonances::Kinematics::NonRelativistic;
    auto boundary = createBoundaryCondition( rmatrix.attribute( "boundaryCondition" ).as_string() );

    auto identifiers = createParticleIdentifiers( projectile, target, rmatrix.child( "resonanceReactions" ) );
    dryad::ParticleDatabase local;
    auto node = rmatrix.child( "PoPs" );
    if ( node ) {

      local = pops::createParticleDatabase( node, identifiers, style );
    }
    auto particles = createParticles( pops, local, identifiers );

    auto reactions = createResonanceReactions( projectile, target, rmatrix.child( "resonanceReactions" ),
                                               particles, radii, style );

    auto groups = createSpinGroups( formalism, boundary, kinematics, reactions,
                                    rmatrix.child( "spinGroups" ) );

    return dryad::resonances::CompoundSystem( lower, upper, std::move( groups ) );
  }

} // rmatrix namespace
} // resonances namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
