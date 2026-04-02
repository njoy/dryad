#ifndef NJOY_DRYAD_FORMAT_GNDS_READINTEGER
#define NJOY_DRYAD_FORMAT_GNDS_READINTEGER

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using Integer = std::pair< int, std::optional< std::string > >;

  /**
   *  @brief Read data from a GNDS integer node
   */
  inline Integer readInteger( const pugi::xml_node& node ) {

    throwExceptionOnWrongNode( node, "integer" );

    Integer data;
    data.second = std::nullopt;

    // get the value (required)
    auto value = node.attribute( "value" );
    if ( value ) {

      data.first = value.as_int();
    }
    else {

      Log::error( "Did not find the required \'value\' attribute in the integer node "
                  "with label \'{}\'", node.attribute( "label" ).as_string() );
      throw std::exception();
    }

    // get the unit (optional)
    auto unit = node.attribute( "unit" );
    if ( unit ) {

      data.second = unit.as_string();
    }

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
