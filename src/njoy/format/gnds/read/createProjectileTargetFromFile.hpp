#ifndef NJOY_FORMAT_GNDS_READ_CREATEPROJECTILETARGETFROMFILE
#define NJOY_FORMAT_GNDS_READ_CREATEPROJECTILETARGETFROMFILE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/format/gnds/read/createProjectileTarget.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create an ProjectileTarget from a GNDS file
   *
   *  @param[in] filename    the GNDS file name
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline dryad::ProjectileTarget
  createProjectileTargetFromFile( const std::string& filename, bool normalise ) {

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
    document.load_file( filename.c_str() );
    if ( document ) {

      return createProjectileTarget( document, path, normalise );
    }
    else {

      Log::error( "The GNDS file \'{}\' does not exist or is not an XML file",
                  filename );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
