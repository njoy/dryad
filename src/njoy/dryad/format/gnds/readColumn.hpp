#ifndef NJOY_DRYAD_FORMAT_GNDS_READCOLUMN
#define NJOY_DRYAD_FORMAT_GNDS_READCOLUMN

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

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

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
