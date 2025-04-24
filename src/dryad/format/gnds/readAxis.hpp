#ifndef NJOY_DRYAD_FORMAT_GNDS_READAXIS
#define NJOY_DRYAD_FORMAT_GNDS_READAXIS

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using Axis = std::pair< std::optional< int >, std::optional< std::string > >;

  /**
   *  @brief Read data from a GNDS axis node
   */
  static Axis readAxis( const pugi::xml_node& axis ) {

    throwExceptionOnWrongNode( axis, "axis" );

    auto index = axis.attribute( "index" );
    auto unit = axis.attribute( "unit" );

    return { index ? std::make_optional( index.as_int() ) : std::nullopt,
             unit ? std::make_optional( unit.as_string() ) : std::nullopt };
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
