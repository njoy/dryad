#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTTABLE
#define NJOY_FORMAT_GNDS_WRITE_INSERTTABLE

// system includes
#include <algorithm>
#include <optional>
#include <string>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertColumnHeaders.hpp"
#include "njoy/format/gnds/write/insertData.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a table xml node
   *
   *  @param[in,out] parent    the parent node
   *  @param[in]     option    the gnds write options
   *  @param[in]     names     the column names
   *  @param[in]     units     the optional units
   *  @param[in]     columns   the columns of values
   */
  inline pugi::xml_node
  insertTable( pugi::xml_node& parent,
               const Options& options,
               const std::vector< std::string >& names,
               const std::vector< std::optional< std::string > >& units,
               const std::vector< std::vector< double > >& columns ) {

    std::size_t number_columns = names.size();
    if ( number_columns != units.size() || number_columns != columns.size() ) {

      throw std::runtime_error( "The number of column names, column units and columns is not the same" );
    }
    if ( columns.size() == 0 ) {

      throw std::runtime_error( "The number of columns cannot be zero" );
    }
    std::size_t number_rows = columns.front().size();
    if ( std::any_of( columns.begin(), columns.end(),
                      [&] ( auto&& column ) { return number_rows == columns.size(); } ) ) {

      throw std::runtime_error( "Not every column has the same number of values" );
    }

    pugi::xml_node node = parent.append_child( "table" );
    node.append_attribute( "rows" ) = number_rows;
    node.append_attribute( "columns" ) = number_columns;

    insertColumnHeaders( node, options, names, units );
    insertData( node, options, columns );

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
