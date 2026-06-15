#ifndef NJOY_FORMAT_GNDS_READ_READDOUBLE
#define NJOY_FORMAT_GNDS_READ_READDOUBLE

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

  using Double = std::pair< double, std::optional< std::string > >;

  /**
   *  @brief Read data from a GNDS double node
   */
  inline Double readDouble( const pugi::xml_node& node ) {

    throwExceptionOnWrongNode( node, "double" );

    Double data;
    data.second = std::nullopt;

    // get the value (required)
    auto value = node.attribute( "value" );
    if ( value ) {

      data.first = value.as_double();
    }
    else {

      Log::error( "Did not find the required \'value\' attribute in the double node "
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

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
