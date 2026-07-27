#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTAXIS
#define NJOY_FORMAT_GNDS_WRITE_INSERTAXIS

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert an axis xml node
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     label    the label
   *  @param[in]     index    the optional index
   *  @param[in]     unit     the optional unit
   */
  inline pugi::xml_node
  insertAxis( pugi::xml_node& parent,
              const Options& options,
              const std::string& label,
              const std::optional< std::size_t >& index = std::nullopt,
              const std::optional< std::string >& unit = std::nullopt ) {

    pugi::xml_node node = parent.append_child( "axis" );
    if ( index.has_value() ) {

      node.append_attribute( "index" ) = std::move( index.value() );
    }
    node.append_attribute( "label" ) = label;
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
