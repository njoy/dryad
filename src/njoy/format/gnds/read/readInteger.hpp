#ifndef NJOY_FORMAT_GNDS_READ_READINTEGER
#define NJOY_FORMAT_GNDS_READ_READINTEGER

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
   *  @brief An integer value and optional unit
   */
  struct Integer {

    int value;
    std::optional< std::string > unit = std::nullopt;
  };

  /**
   *  @brief Read data from a GNDS integer node
   *
   *  @param[in] node   the gnds integer node
   */
  inline Integer readInteger( const pugi::xml_node& node ) {

    throwExceptionOnWrongNode( node, "integer" );

    Integer data;

    // get the value (required)
    auto value = node.attribute( "value" );
    if ( value ) {

      data.value = value.as_int();
    }
    else {

      Log::error( "Did not find the required \'value\' attribute in the integer node "
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
