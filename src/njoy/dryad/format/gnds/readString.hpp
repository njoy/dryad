#ifndef NJOY_DRYAD_FORMAT_GNDS_READSTRING
#define NJOY_DRYAD_FORMAT_GNDS_READSTRING

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

  using String = std::pair< std::string, std::optional< std::string > >;

  /**
   *  @brief Read data from a GNDS string node
   */
  inline String readString( const pugi::xml_node& node ) {

    throwExceptionOnWrongNode( node, "string" );

    String data;
    data.second = std::nullopt;

    // get the value (required)
    auto value = node.attribute( "value" );
    if ( value ) {

      data.first = value.as_string();
    }
    else {

      Log::error( "Did not find the required \'value\' attribute in the string node "
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
