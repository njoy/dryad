#ifndef NJOY_DRYAD_FORMAT_GNDS_RESOLVELINK
#define NJOY_DRYAD_FORMAT_GNDS_RESOLVELINK

// system includes
#include <sstream>
#include <string>
#include <algorithm>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Convert the shape
   */
  static pugi::xml_node resolveLink( const pugi::xml_node& link ) {

    pugi::xml_node node = link;

    std::string href = link.attribute( "href" ).as_string();
    std::istringstream list( href );
    std::string entry;
    while ( std::getline( list, entry, '/' ) ) {

      if ( entry == ".." ) {

        // go up one level
        node = node.parent();
      }
      else {

        // this should name a child, with potentially an attribute and value
        auto iter = std::find( entry.begin(), entry.end(), '[' );
        if ( iter == entry.end() ) {

          // just get the first child with the appropriate name
          node = node.child( entry.c_str() );
        }
        else {

          // node and attribute: name[@attribute='value']
          std::string name( entry.begin(), iter );
          entry.erase( entry.begin(), iter + 2 ); // erase up to and including "[@""
          iter = std::find( entry.begin(), entry.end(), '=' );
          std::string attribute( entry.begin(), iter );
          std::string value( iter + 2, entry.end() - 2 ); // the value is in '', and ignore the closing ]"
          node = node.find_child_by_attribute( name.c_str(), attribute.c_str(), value.c_str() );
        }
      }

      if ( !node ) {

        Log::error( "The link could not be resolved properly" );
        Log::info( "Link reference: \'{}\'", href );
        throw std::exception();
      }
    }

    return node;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
