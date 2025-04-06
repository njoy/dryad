#ifndef NJOY_DRYAD_FORMAT_GNDS_READGRID
#define NJOY_DRYAD_FORMAT_GNDS_READGRID

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/readValues.hpp"
#include "dryad/format/gnds/resolveLink.hpp"
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

    auto values = grid.child( "values" );
    if ( ! values ) {

      auto link = grid.child( "link" );
      if ( link ) {

        // the link should point to another values
        values = resolveLink( link );
      }
      else {

        Log::error( "The grid node does not have a values or link node" );
        throw std::exception();
      }
    }

    return { index ? std::make_optional( index.as_int() ) : std::nullopt,
             unit ? std::make_optional( unit.as_string() ) : std::nullopt,
             readValues( values ) };
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
