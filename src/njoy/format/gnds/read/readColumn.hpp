#ifndef NJOY_FORMAT_GNDS_READ_READCOLUMN
#define NJOY_FORMAT_GNDS_READ_READCOLUMN

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

  using Column = std::tuple< int, std::string, std::optional< std::string > >;

  /**
   *  @brief Read data from a GNDS column node
   */
  inline Column readColumn( const pugi::xml_node& column ) {

    throwExceptionOnWrongNode( column, "column" );

    auto index = column.attribute( "index" );
    auto name = column.attribute( "name" );
    auto unit = column.attribute( "unit" );

    return { index.as_int(),
             name.as_string(),
             unit ? std::make_optional( unit.as_string() ) : std::nullopt };
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
