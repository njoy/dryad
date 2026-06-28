#ifndef NJOY_FORMAT_GNDS_READ_CREATETHERMALSCATTERINGFROMFILE
#define NJOY_FORMAT_GNDS_READ_CREATETHERMALSCATTERINGFROMFILE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "njoy/format/gnds/read/createThermalScattering.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a ThermalScattering instance from a GNDS file
   *
   *  @param[in] lower      the lower energy limit
   *  @param[in] upper      the upper energy limit
   *  @param[in] filename   the GNDS file name
   *  @param[in] style      the gnds style to process (default is eval)
   */
  inline dryad::ThermalScattering
  createThermalScatteringFromFile( double lower, double upper,
                                   const std::string& filename,
                                   const std::string& style = "eval" ) {

    Log::info( "Reading GNDS file \'{}\'", filename );

    pugi::xml_document document;
    document.load_file( filename.c_str() );
    if ( document ) {

      return createThermalScattering( lower, upper, document, style );
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
