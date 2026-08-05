#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTCOLUMN
#define NJOY_FORMAT_GNDS_WRITE_INSERTCOLUMN

// system includes
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a column xml node
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     index    the column index
   *  @param[in]     name     the column name
   *  @param[in]     unit     the optional unit
   */
  inline pugi::xml_node
  insertColumn( pugi::xml_node& parent,
                const Options& options,
                std::size_t index,
                const std::string& name,
                const std::optional< std::string >& unit = std::nullopt ) {

    pugi::xml_node node = parent.append_child( "column" );
    node.append_attribute( "index" ) = index;
    node.append_attribute( "name" ) = name;
    if ( unit.has_value() ) {

      node.append_attribute( "unit" ) = unit.value();
    }

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
