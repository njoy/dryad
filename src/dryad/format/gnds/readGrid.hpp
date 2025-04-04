#ifndef NJOY_DRYAD_FORMAT_GNDS_READGRID
#define NJOY_DRYAD_FORMAT_GNDS_READGRID

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/readValues.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using Grid = std::tuple< std::optional< int >,
                           std::optional< std::string >,
                           std::vector< double > >;

  /**
   *  @brief Read data from a GNDS grid node
   */
  static Grid readGrid( const pugi::xml_node& grid ) {

    throwExceptionOnWrongNode( grid, "grid" );

    auto index = grid.attribute( "index" );
    auto unit = grid.attribute( "unit" );
    auto values = readValues( grid.child( "values" ) );

    return { index ? std::make_optional( index.as_int() ) : std::nullopt,
             unit ? std::make_optional( unit.as_string() ) : std::nullopt,
             std::move( values ) };
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
