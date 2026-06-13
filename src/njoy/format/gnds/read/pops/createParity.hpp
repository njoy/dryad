#ifndef NJOY_FORMAT_GNDS_READ_POPS_CREATEPARITY
#define NJOY_FORMAT_GNDS_READ_POPS_CREATEPARITY

// system includes
#include <tuple>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/read/readInteger.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace pops {

  /**
   *  @brief Create a parity values from a GNDS parity xml node
   *
   *  @param[in] parity    the GNDS parity node
   *  @param[in] style     the gnds style to process (default is eval)
   */
  inline std::optional< double >
  createParity( const pugi::xml_node& parity, const std::string& style = "eval" ) {

    // check that this is a valid parity node
    throwExceptionOnWrongNode( parity, "parity" );

    // get a double node if it exists, else return nullopt
    auto child = parity.find_child_by_attribute( "integer", "label", style.c_str() );
    if ( child ) {

      auto content = readInteger( child );
      return content.first;
    }

    return std::nullopt;
  }

} // pops namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
