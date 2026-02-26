#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEPROJECTILETARGETFROMFILE
#define NJOY_DRYAD_FORMAT_GNDS_CREATEPROJECTILETARGETFROMFILE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/format/gnds/createProjectileTarget.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create an ProjectileTarget from a GNDS file
   *
   *  @param[in] filename    the GNDS file name
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline ProjectileTarget createProjectileTargetFromFile( const std::string& filename,
                                                          bool normalise ) {

    Log::info( "Reading GNDS file \'{}\'", filename );

    // determine file path
    std::string path = filename;
    auto pos = path.find_last_of( '/' );
    if ( pos != std::string::npos ) {

      path.erase( pos + 1, path.size() );
    }
    else {

      path = "";
    }

    // open the file
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( filename.c_str() );
    if ( document ) {

      return createProjectileTarget( document, path, normalise );
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
