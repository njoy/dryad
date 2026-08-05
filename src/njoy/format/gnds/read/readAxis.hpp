#ifndef NJOY_FORMAT_GNDS_READ_READAXIS
#define NJOY_FORMAT_GNDS_READ_READAXIS

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  using Axis = std::pair< std::optional< int >, std::optional< std::string > >;

  /**
   *  @brief Read data from a GNDS axis node
   *
   *  @param[in] axis   the gnds axis node
   */
  inline Axis readAxis( const pugi::xml_node& axis ) {

    throwExceptionOnWrongNode( axis, "axis" );

    auto index = axis.attribute( "index" );
    auto unit = axis.attribute( "unit" );

    Axis data;
    if ( index ) {

      data.first = index.as_int();
    }
    if ( unit ) {

      std::string value = unit.as_string();
      if ( value.size() != 0 ) {

        data.second = std::move( value );
      }
    }

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
