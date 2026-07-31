#ifndef NJOY_FORMAT_GNDS_WRITE_CREATEPROJECTILETARGETFILE
#define NJOY_FORMAT_GNDS_WRITE_CREATEPROJECTILETARGETFILE

// system includes
#include <fstream>
#include <string>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/createInteractionType.hpp"
#include "njoy/format/gnds/write/insertProjectileEnergyDomain.hpp"
#include "njoy/format/gnds/write/insertDocumentation.hpp"
#include "njoy/format/gnds/write/insertParticleDatabase.hpp"
#include "njoy/format/gnds/write/insertReactions.hpp"
#include "njoy/format/gnds/write/insertSums.hpp"
#include "njoy/format/gnds/StyleType.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Create a GNDS incident particle file
   *
   *  @param[in] transport                the projectile-target data
   *  @param[in] filename                 the file name for the GNDS file
   *  @param[in] style                    the gnds style to be used
   *  @param[in] reducedWidthAmplitudes   if there are resonances, use reduced width amplitudes
   */
  inline void createProjectileTargetFile( const dryad::ProjectileTarget& transport,
                                          const std::string& filename,
                                          const StyleType& style = StyleType::Evaluation,
                                          bool reducedWidthAmplitudes = true ) {

    Options options;

    pugi::xml_document gnds;
    pugi::xml_node suite = gnds.append_child( "reactionSuite" );
    suite.append_attribute( "projectile" ) = transport.projectileIdentifier().symbol();
    suite.append_attribute( "target" ) = transport.targetIdentifier().symbol();
    suite.append_attribute( "frame" ) = "lab";
    suite.append_attribute( "interaction" ) = createInteractionType( transport.interactionType() );
    suite.append_attribute( "format" ) = "2.2";
    suite.append_attribute( "evaluation" ) = "justGoofingAround";

    std::string style_label;
    switch ( style ) {

      case StyleType::Evaluation : { style_label = "eval"; break; }
      default : {

        std::runtime_error( "Only the evaluated style is currently supported for GNDS files" );
      }
    }

    pugi::xml_node styles = suite.append_child( "styles" );
    pugi::xml_node evaluated = styles.append_child( "evaluated" );
    evaluated.append_attribute( "label" ) = style_label;
    evaluated.append_attribute( "date" ) = "300BC";
    evaluated.append_attribute( "library" ) = "LibraryOfAlexandria";
    evaluated.append_attribute( "version" ) = "0.0alpha-rc1";
    insertProjectileEnergyDomain( evaluated, options, transport.reactions() );
    insertDocumentation( evaluated, options, transport.documentation() );

    if ( transport.particleData().has_value() ) {

      insertParticleDatabase( suite, options, transport.particleData().value(), style_label );
    }

    pugi::xml_node reactions_node = insertReactions( suite, options, transport.reactions(),
                                                     transport.resonances(), style_label );
    pugi::xml_node sums_node = insertSums( suite, options, transport.reactions(),
                                           transport.resonances(), style_label );

    gnds.save_file( filename.c_str(), "  " );
  }

} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
