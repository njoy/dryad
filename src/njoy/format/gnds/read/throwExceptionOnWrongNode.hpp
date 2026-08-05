#ifndef NJOY_FORMAT_GNDS_READ_THROWEXCEPTIONONWRONGNODE
#define NJOY_FORMAT_GNDS_READ_THROWEXCEPTIONONWRONGNODE

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Throw a node exception
   *
   *  @param[in] node   the gnds node
   *  @param[in] name   the name to look for
   */
  inline void throwExceptionOnWrongNode( const pugi::xml_node& node, const char* name ) {

    if ( node ) {

      if ( strcmp( node.name(), name ) != 0 ) {

        Log::error( "The XML element does not define a GNDS {} node, found a \'{}\' node",
                    name, node.name() );
        throw std::exception();
      }
    }
    else {

      Log::error( "The XML element does not define a GNDS {} node, the node is undefined",
                  name );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
