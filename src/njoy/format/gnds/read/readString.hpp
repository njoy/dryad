#ifndef NJOY_FORMAT_GNDS_READ_READSTRING
#define NJOY_FORMAT_GNDS_READ_READSTRING

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief A string value and optional unit
   */
  struct String {

    std::string value;
    std::optional< std::string > unit = std::nullopt;
  };

  /**
   *  @brief Read data from a GNDS string node
   *
   *  @param[in] node   the gnds string node
   */
  inline String readString( const pugi::xml_node& node ) {

    throwExceptionOnWrongNode( node, "string" );

    String data;

    // get the value (required)
    auto value = node.attribute( "value" );
    if ( value ) {

      data.value = value.as_string();
    }
    else {

      Log::error( "Did not find the required \'value\' attribute in the string node "
                  "with label \'{}\'", node.attribute( "label" ).as_string() );
      throw std::exception();
    }

    // get the unit (optional)
    auto unit = node.attribute( "unit" );
    if ( unit ) {

      data.unit = unit.as_string();
    }

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
