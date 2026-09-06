#ifndef NJOY_FORMAT_GNDS_READ_POPS_CREATEMASS
#define NJOY_FORMAT_GNDS_READ_POPS_CREATEMASS

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/read/readDouble.hpp"
#include "njoy/format/gnds/read/convertMass.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace pops {

  /**
   *  @brief A mass and associated uncertainty value
   */
  struct Mass {

    std::optional< double > value = std::nullopt;
    std::optional< double > uncertainty = std::nullopt;
  };

  /**
   *  @brief Create a mass and uncertainty value from a GNDS energy xml node
   *
   *  @param[in] mass    the GNDS mass node
   *  @param[in] style   the gnds style to process (default is eval)
   */
  inline Mass
  createMass( const pugi::xml_node& mass, const std::string& style = "eval" ) {

    // check that this is a valid mass node
    throwExceptionOnWrongNode( mass, "mass" );

    Mass data;

    auto child = mass.find_child_by_attribute( "double", "label", style.c_str() );
    if ( child ) {

      auto content = readDouble( child );
      convertMass( content.value, content.unit.value() );
      data.value = content.value;

      auto node = child.child( "uncertainty" ).child( "standard" ).child( "double" );
      if ( node ) {

        auto uncertainty = readDouble( node );
        auto unit = uncertainty.unit.has_value() ? uncertainty.unit.value() : content.unit.value();
        convertMass( uncertainty.value, unit );
        data.uncertainty = uncertainty.value;
      }
    }

    return data;
  }

} // pops namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
