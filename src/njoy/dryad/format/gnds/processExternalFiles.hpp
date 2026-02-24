#ifndef NJOY_DRYAD_FORMAT_GNDS_PROCESSEXTERNALFILES
#define NJOY_DRYAD_FORMAT_GNDS_PROCESSEXTERNALFILES

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include <iostream>
namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Add the content of external files to the current document
   *
   *  @param[in] document   the gnds xml document
   */
  inline void processExternalFiles( pugi::xml_document& document ) {

    auto files = document.first_child().child( "externalFiles" );

    for ( pugi::xml_node file = files.child( "externalFile" ); file;
          file = file.next_sibling( "externalFile" ) ) {

      std::string filename = file.attribute( "path" ).as_string();

      pugi::xml_document external;
      pugi::xml_parse_result result = external.load_file( filename.c_str() );
      if ( external ) {

        for ( pugi::xml_node node : external.children() ) {

          document.append_copy( node );
        }
      }
      else {

        Log::error( "The GNDS file \'{}\' does not exist or is not an XML file",
                    filename );
        throw std::exception();
      }
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
