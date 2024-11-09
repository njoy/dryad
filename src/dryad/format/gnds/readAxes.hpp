#ifndef NJOY_DRYAD_FORMAT_GNDS_READAXES
#define NJOY_DRYAD_FORMAT_GNDS_READAXES

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Read data from a GNDS axes node
   */
  std::vector< std::string > readAxes( const pugi::xml_node& axes ) {

    throwExceptionOnWrongNode( axes, "axes" );

    std::vector< std::string > units;

    pugi::xml_node outer = axes.find_child_by_attribute( "axis", "index", "2" );
    if ( outer ) {

      units.emplace_back( outer.attribute( "unit" ).as_string() );
    }

    units.emplace_back( axes.find_child_by_attribute( "axis", "index", "1" ).attribute( "unit" ).as_string() );
    units.emplace_back( axes.find_child_by_attribute( "axis", "index", "0" ).attribute( "unit" ).as_string() );

    return units;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
