#ifndef NJOY_FORMAT_GNDS_WRITE_DETERMINEDEPTH
#define NJOY_FORMAT_GNDS_WRITE_DETERMINEDEPTH

// system includes

// other includes
#include "pugixml.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Determine the current depth of the xml node
   *
   *  @param[in] node   the node
   */
  std::size_t determineDepth( pugi::xml_node node ) {

    std::size_t depth = 0;
    node = node.parent();
    while ( node ) {

      ++depth;
      node = node.parent();
    }

    return depth;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
