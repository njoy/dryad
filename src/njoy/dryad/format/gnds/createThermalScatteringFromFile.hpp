#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATETHERMALSCATTERINGFROMFILE
#define NJOY_DRYAD_FORMAT_GNDS_CREATETHERMALSCATTERINGFROMFILE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "njoy/dryad/format/gnds/createThermalScattering.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a ThermalScattering instance from a GNDS file
   *
   *  @param[in] filename   the GNDS file name
   *  @param[in] style      the gnds style to process (default is eval)
   */
  inline ThermalScattering
  createThermalScatteringFromFile( const std::string& filename,
                                   const std::string& style = "eval" ) {

    Log::info( "Reading GNDS file \'{}\'", filename );

    pugi::xml_document document;
    document.load_file( filename.c_str() );
    if ( document ) {

      return createThermalScattering( document, style );
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
