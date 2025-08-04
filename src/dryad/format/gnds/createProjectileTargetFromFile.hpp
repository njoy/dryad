#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEPROJECTILETARGETFROMFILE
#define NJOY_DRYAD_FORMAT_GNDS_CREATEPROJECTILETARGETFROMFILE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/ProjectileTarget.hpp"
#include "dryad/format/gnds/createProjectileTarget.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create an ProjectileTarget from a GNDS file
   *
   *  @param[in] filename   the GNDS file name
   */
  static ProjectileTarget createProjectileTargetFromFile( const std::string& filename,
                                                          bool normalise ) {

    Log::info( "Reading GNDS file \'{}\'", filename );

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( filename.c_str() );
    if ( document ) {

      return createProjectileTarget( document, normalise );
    }
    else {

      Log::error( "The GNDS file \'{}\' does not exist or is not an XML file",
                  filename );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
