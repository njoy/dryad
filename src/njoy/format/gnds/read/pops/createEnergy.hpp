#ifndef NJOY_FORMAT_GNDS_READ_POPS_CREATEENERGY
#define NJOY_FORMAT_GNDS_READ_POPS_CREATEENERGY

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/read/readDouble.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace pops {

  /**
   *  @brief An energy and associated uncertainty value
   */
  struct Energy {

    std::optional< double > value = std::nullopt;
    std::optional< double > uncertainty = std::nullopt;
  };

  /**
   *  @brief Create an energy and uncertainty value from a GNDS energy xml node
   *
   *  @param[in] energy   the GNDS energy node
   *  @param[in] style    the gnds style to process (default is eval)
   */
  inline Energy
  createEnergy( const pugi::xml_node& energy, const std::string& style = "eval" ) {

    // check that this is a valid energy node
    throwExceptionOnWrongNode( energy, "energy" );

    Energy data;

    auto child = energy.find_child_by_attribute( "double", "label", style.c_str() );
    if ( child ) {

      auto content = readDouble( child );
      convertEnergy( content.value, content.unit.value() );
      data.value = content.value;

      auto node = child.child( "uncertainty" ).child( "standard" ).child( "double" );
      if ( node ) {

        auto uncertainty = readDouble( node );
        auto unit = uncertainty.unit.has_value() ? uncertainty.unit.value() : content.unit.value();
        convertEnergy( uncertainty.value, unit );
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
