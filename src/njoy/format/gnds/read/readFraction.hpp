#ifndef NJOY_FORMAT_GNDS_READ_READFRACTION
#define NJOY_FORMAT_GNDS_READ_READFRACTION

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/readFractionFromString.hpp"
#include "tools/Log.hpp"
#include "tools/split.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief An fraction value and optional unit
   */
  struct Fraction {

    double value;
    std::optional< std::string > unit = std::nullopt;
  };

  /**
   *  @brief Read data from a GNDS fraction node
   *
   *  @param[in] node   the gnds fraction node
   */
  inline Fraction readFraction( const pugi::xml_node& node ) {

    throwExceptionOnWrongNode( node, "fraction" );

    Fraction data;

    // get the value (required)
    auto value = node.attribute( "value" );
    if ( value ) {

      data.value = readFractionFromString( value.as_string() );
    }
    else {

      Log::error( "Did not find the required \'value\' attribute in the fraction node "
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
