#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEATOMICRELAXATIONFROMFILE
#define NJOY_DRYAD_FORMAT_GNDS_CREATEATOMICRELAXATIONFROMFILE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/AtomicRelaxation.hpp"
#include "dryad/format/gnds/createAtomicRelaxation.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create an AtomicRelaxation from a GNDS file
   *
   *  @param[in] filename   the GNDS file name
   */
  AtomicRelaxation createAtomicRelaxationFromFile( const std::string& filename ) {

    Log::info( "Reading GNDS file \'{}\'", filename );

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( filename.c_str() );
    if ( document ) {

      return createAtomicRelaxation( document );
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
