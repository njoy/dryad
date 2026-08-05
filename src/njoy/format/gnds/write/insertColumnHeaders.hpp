#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTCOLUMNHEADERS
#define NJOY_FORMAT_GNDS_WRITE_INSERTCOLUMNHEADERS

// system includes
#include <optional>
#include <string>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertColumn.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a column xml node
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     names    the column names
   *  @param[in]     units    the optional units
   */
  inline pugi::xml_node
  insertColumnHeaders( pugi::xml_node& parent,
                       const Options& options,
                       const std::vector< std::string >& names,
                       const std::vector< std::optional< std::string > >& units ) {

    pugi::xml_node node = parent.append_child( "columnHeaders" );
    for ( std::size_t index = 0; index < names.size(); ++index ) {

      insertColumn( node, options, index, names[index], units[index] );
    }

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
