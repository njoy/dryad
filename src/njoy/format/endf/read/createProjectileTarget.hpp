#ifndef NJOY_FORMAT_ENDF_READ_CREATEPROJECTILETARGET
#define NJOY_FORMAT_ENDF_READ_CREATEPROJECTILETARGET

// system includes
#include <vector>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/format/endf/read/createProjectileIdentifier.hpp"
#include "njoy/format/endf/read/createTargetIdentifier.hpp"
#include "njoy/format/endf/read/createInteractionType.hpp"
#include "njoy/format/endf/read/createReactions.hpp"
#include "njoy/format/endf/read/createDocumentation.hpp"
#include "njoy/format/endf/read/createParticleDatabase.hpp"
#include "njoy/format/endf/read/resonances/createResonanceParameters.hpp"
#include "njoy/format/endf/read/covariance/createCovarianceData.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a ProjectileTarget from an unparsed ENDF material
   *
   *  @param[in] material    the unparsed ENDF material
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline dryad::ProjectileTarget
  createProjectileTarget( const ENDFtk::tree::Material& material, bool normalise ) {

    auto information = material.section( 1, 451 ).parse< 1, 451 >();

    dryad::Documentation documentation = createDocumentation( information );

    dryad::id::ParticleID projectile = createProjectileIdentifier( information.subLibrary() );
    dryad::id::ParticleID target = createTargetIdentifier( information.ZA(), information.excitedLevel() );
    dryad::InteractionType type = createInteractionType( information.subLibrary() );

    std::map< dryad::id::ParticleID, double > masses;
    std::vector< dryad::Reaction > reactions = createReactions( projectile, target, material, normalise, masses );

    std::optional< dryad::resonances::ResonanceParameters > resonances = std::nullopt;
    if ( type == dryad::InteractionType::Nuclear ) {

      resonances = resonances::createResonanceParameters( projectile, target,
                                                          material.section( 2, 151 ).parse< 2, 151 >() );
    }

    dryad::ParticleDatabase particles = createParticleDatabase( projectile, target, reactions, information, masses );

    std::optional< dryad::covariance::CovarianceData > covariances = covariance::createCovarianceData( projectile, target, material );

    return dryad::ProjectileTarget( std::move( documentation ), std::move( projectile ),
                                    std::move( target ), type, std::move( reactions ),
                                    std::move( particles ), std::move( resonances ),
                                    std::move( covariances ) );
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
