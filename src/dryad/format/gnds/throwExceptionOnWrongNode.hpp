#ifndef NJOY_DRYAD_FORMAT_GNDS_THROWEXCEPTIONONWRONGNODE
#define NJOY_DRYAD_FORMAT_GNDS_THROWEXCEPTIONONWRONGNODE

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Throw a node exception
   */
  static void throwExceptionOnWrongNode( const pugi::xml_node& node, const char* name ) {

    if ( node ) {

      if ( strcmp( node.name(), name ) != 0 ) {

        Log::error( "The XML element does not define a GNDS {} node, found a \'{}\' node", 
                    name, node.name() );
        throw std::exception();
      }
    }
    else {

      Log::error( "The XML element does not define a GNDS axes node, the node is undefined" );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
