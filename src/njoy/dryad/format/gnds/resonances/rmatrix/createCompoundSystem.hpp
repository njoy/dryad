#ifndef NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATECOMPOUNDSYSTEM
#define NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATECOMPOUNDSYSTEM

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/dryad/format/gnds/pops/createParticleDatabase.hpp"
#include "njoy/dryad/format/gnds/resonances/createParticles.hpp"
#include "njoy/dryad/format/gnds/resonances/rmatrix/createParticleIdentifiers.hpp"
#include "njoy/dryad/format/gnds/resonances/rmatrix/createResonanceReactions.hpp"
#include "njoy/dryad/format/gnds/resonances/rmatrix/createBoundaryCondition.hpp"
#include "njoy/dryad/format/gnds/resonances/rmatrix/createFormalism.hpp"
#include "njoy/dryad/format/gnds/resonances/rmatrix/createSpinGroups.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
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
  inline auto createCompoundSystem( const id::ParticleID& projectile,
                                    const id::ParticleID& target,
                                    double lower,
                                    double upper,
                                    const ParticleDatabase& pops,
                                    const dryad::resonances::ChannelRadii& radii,
                                    const pugi::xml_node& rmatrix,
                                    const std::string& style = "eval" ) {

    // check that this is a valid rmatrix node
    throwExceptionOnWrongNode( rmatrix, "RMatrix" );

    auto formalism = createFormalism( rmatrix.attribute( "approximation" ).as_string() );
    auto kinematics = dryad::resonances::Kinematics::NonRelativistic;
    auto boundary = createBoundaryCondition( rmatrix.attribute( "boundaryCondition" ).as_string() );

    auto identifiers = createParticleIdentifiers( projectile, target, rmatrix.child( "resonanceReactions" ) );
    ParticleDatabase local;
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
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
