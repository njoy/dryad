#ifndef NJOY_FORMAT_GNDS_READ_READGRID
#define NJOY_FORMAT_GNDS_READ_READGRID

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/readValues.hpp"
#include "njoy/format/gnds/read/resolveLink.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief The grid information: an optional index and unit, and grid values
   */
  struct Grid {

    std::optional< int > index = std::nullopt;
    std::optional< std::string > unit = std::nullopt;
    std::string interpolation;
    std::vector< double > values;
  };

  /**
   *  @brief Read data from a GNDS grid node
   *
   *  @param[in] grid   the gnds grid node
   */
  inline Grid readGrid( const pugi::xml_node& grid ) {

    throwExceptionOnWrongNode( grid, "grid" );

    auto index = grid.attribute( "index" );
    auto unit = grid.attribute( "unit" );
    auto interpolation = grid.attribute( "interpolation" );

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
             interpolation.as_string(),
             readValues( values ) };
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
