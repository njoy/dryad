#ifndef NJOY_FORMAT_GNDS_READ_CREATEATOMICRELAXATIONFROMFILE
#define NJOY_FORMAT_GNDS_READ_CREATEATOMICRELAXATIONFROMFILE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "njoy/format/gnds/read/createAtomicRelaxation.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create an AtomicRelaxation from a GNDS xml file
   *
   *  @param[in] filename    the GNDS file name
   *  @param[in] normalise   option to indicate whether or not to normalise
   *                         all probability data
   */
  inline dryad::AtomicRelaxation
  createAtomicRelaxationFromFile( const std::string& filename, bool normalise ) {

    Log::info( "Reading GNDS file \'{}\'", filename );

    pugi::xml_document document;
    document.load_file( filename.c_str() );
    if ( document ) {

      return createAtomicRelaxation( document, normalise );
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
