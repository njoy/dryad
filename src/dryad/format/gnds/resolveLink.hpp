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
   *
   *  @param[in] link   the xml node with an href link attribute
   */
  static pugi::xml_node resolveLink( const pugi::xml_node& link ) {

    pugi::xml_node node = link;
    std::string href = link.attribute( "href" ).as_string();

    // lambda that reads the next entry in an href string
    //   - they are split by '/' characters
    //   - when a quote is encountered, skip beyond the closing one
    auto get_entry = [] ( std::string& href, std::string& entry ) {

      if ( href.size() == 0 ) {

        return false;
      }

      auto next_slash_or_quote = [] ( auto&& value ) { return value == '/' || value == '\''; };
      auto next_slash = [] ( auto&& value ) { return value == '/'; };
      auto next_quote = [] ( auto&& value ) { return value == '\''; };

      auto iter = std::find_if( href.begin(), href.end(), next_slash_or_quote );
      if ( iter != href.end() ) {

        // check if we are inside a 'label'
        if ( *iter == '\'' ) {

          iter = std::find_if( iter + 1, href.end(), next_quote );
          iter = std::find_if( iter + 1, href.end(), next_slash );
        }
      }

      if ( iter == href.end() ) {

        entry = href;
        href = "";
      }
      else {

        entry = std::string( href.begin(), iter );
        href = std::string( iter + 1, href.end() );
      }

      return true;
    };

    // move to the top level if this is an absolute path
    if ( href.front() == '/' ) {

      href.erase( href.begin() );
      while ( node.parent() ) {

        node = node.parent();
      }
    }

    // read pieces of the path and act accordingly
    std::string entry;
    while ( get_entry( href, entry ) ) {

      if ( entry == ".." ) {

        // go up one level
        node = node.parent();
      }
      else {

        // this should name a child, with potentially an attribute and value
        // formatted like this: name[@attribute='value']
        auto iter = std::find( entry.begin(), entry.end(), '[' );
        if ( iter == entry.end() ) {

          // name only
          node = node.child( entry.c_str() );
        }
        else {

          // name and attribute with value
          std::string name( entry.begin(), iter );
          entry.erase( entry.begin(), iter + 2 ); // erase up to and including "[@""
          iter = std::find( entry.begin(), entry.end(), '=' );
          std::string attribute( entry.begin(), iter );
          std::string value( iter + 2, entry.end() - 2 ); // the value is in '', and ignore the closing ]"
          node = node.find_child_by_attribute( name.c_str(), attribute.c_str(), value.c_str() );
        }
      }

      if ( !node ) {

        href = link.attribute( "href" ).as_string();
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
