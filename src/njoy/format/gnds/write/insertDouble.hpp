#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTDOUBLE
#define NJOY_FORMAT_GNDS_WRITE_INSERTDOUBLE

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
   *  @brief Insert a double xml node
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     value    the value
   *  @param[in]     label    the optional label
   *  @param[in]     unit     the optional unit
   */
  inline pugi::xml_node
  insertDouble( pugi::xml_node& parent,
                const Options& options,
                double value,
                const std::optional< std::string >& label = std::nullopt,
                const std::optional< std::string >& unit = std::nullopt ) {

    pugi::xml_node node = parent.append_child( "double" );
    if ( label.has_value() ) {

      node.append_attribute( "label" ) = std::move( label.value() );
    }
    node.append_attribute( "value" ) = toString( options, value );
    if ( unit.has_value() ) {

      node.append_attribute( "unit" ) = std::move( unit.value() );
    }

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
