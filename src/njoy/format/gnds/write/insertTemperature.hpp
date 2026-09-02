#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTTEMPERATURE
#define NJOY_FORMAT_GNDS_WRITE_INSERTTEMPERATURE

// system includes
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/toString.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a temperature xml node
   *
   *  @param[in,out] parent        the parent node
   *  @param[in]     option        the gnds write options
   *  @param[in]     temperature   the temperature value
   *  @param[in]     unit          the unit
   */
  inline pugi::xml_node
  insertTemperature( pugi::xml_node& parent,
                     const Options& options,
                     double temperature,
                     const std::string& unit ) {

    pugi::xml_node node = parent.append_child( "temperature" );
    node.append_attribute( "value" ) = toString( options, temperature ).c_str();
    node.append_attribute( "unit" ) = unit.c_str();

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
