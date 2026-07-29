#ifndef NJOY_FORMAT_GNDS_READ_CREATEPROJECTILETARGET
#define NJOY_FORMAT_GNDS_READ_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/format/collectParticleIdentifiers.hpp"
#include "njoy/format/gnds/StyleType.hpp"
#include "njoy/format/gnds/read/createStyleLabel.hpp"
#include "njoy/format/gnds/read/processExternalFiles.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/createParticleIdentifier.hpp"
#include "njoy/format/gnds/read/createInteractionType.hpp"
#include "njoy/format/gnds/read/pops/createParticleDatabase.hpp"
#include "njoy/format/gnds/read/resonances/createResonanceParameters.hpp"
#include "njoy/format/gnds/read/createDocumentation.hpp"
#include "njoy/format/gnds/read/createReactions.hpp"
#include "njoy/format/gnds/read/covariance/createCovarianceData.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a ProjectileTarget from a GNDS xml document
   *
   *  @param[in] document     the gnds xml document
   *  @param[in] path         the common file path
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   *  @param[in] style        the gnds style to process (default is evaluation)
   */
  inline dryad::ProjectileTarget
  createProjectileTarget( pugi::xml_document& document,
                          const std::string& path,
                          bool normalise,
                          const StyleType& style = StyleType::Evaluation ) {

    processExternalFiles( document, path );
    auto suite = document.child( "reactionSuite" );
    auto covsuite = document.child( "covarianceSuite" );

    if ( suite ) {

      auto styles = suite.child( "styles" );
      auto pops = suite.child( "PoPs" );
      auto resonances = suite.child( "resonances" );

      std::string style_label = createStyleLabel( suite.child( "styles" ), style );

      auto documentation = styles.find_child_by_attribute( "label", style_label.c_str() ).child( "documentation" );

      dryad::id::ParticleID projectile = createParticleIdentifier( suite.attribute( "projectile" ).as_string() );
      dryad::id::ParticleID target( suite.attribute( "target" ).as_string() );
      dryad::InteractionType type = createInteractionType( suite.attribute( "interaction" ).as_string() );

      dryad::Documentation docs = createDocumentation( documentation, style_label );

      std::vector< dryad::Reaction > reactions = createReactions( projectile, target, suite, normalise, style_label );

      std::vector< dryad::id::ParticleID > identifiers = collectParticleIdentifiers( reactions );
      std::optional< dryad::ParticleDatabase > particles = pops::createParticleDatabase( pops, identifiers, style_label );

      std::optional< dryad::resonances::ResonanceParameters > parameters = std::nullopt;
      if ( resonances ) {

        parameters = resonances::createResonanceParameters( projectile, target, particles.value(),
                                                            resonances, style_label );
      }

      std::optional< dryad::covariance::CovarianceData > covariances = std::nullopt;
      if ( covsuite ) {

        covariances = covariance::createCovarianceData( projectile, target, covsuite );
      }

      return dryad::ProjectileTarget( std::move( docs ), std::move( projectile ), std::move( target ),
                                      type, std::move( reactions ), std::move( particles ),
                                      std::move( parameters ), std::move( covariances ) );
    }
    else {

      Log::error( "The GNDS file does not contain projectile-target data" );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
