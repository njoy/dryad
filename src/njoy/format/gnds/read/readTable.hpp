#ifndef NJOY_FORMAT_GNDS_READ_READTABLE
#define NJOY_FORMAT_GNDS_READ_READTABLE

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/gnds/read/createStorageOrder.hpp"
#include "njoy/format/gnds/read/readColumnHeaders.hpp"
#include "njoy/format/gnds/read/readData.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief The column data information
   */
  struct ColumnData {

    std::string name;
    std::vector< double > values;
    std::optional< std::string > unit = std::nullopt;

    // C++-20 : constructor no longer required for emplace/emplace_back
    ColumnData( std::string name, std::vector< double > values, std::optional< std::string > unit ) :
      name( std::move( name ) ), values( std::move( values ) ), unit( std::move( unit ) ) {}
  };

  using Table = std::vector< ColumnData >;

  /**
   *  @brief Read data from a GNDS table node
   *
   *  @param[in] table   the gnds table node
   */
  inline Table readTable( const pugi::xml_node& table ) {

    throwExceptionOnWrongNode( table, "table" );

    Table data;

    using namespace njoy::tools;

    // get the number of rows and columns
    auto columns = table.attribute( "columns" ).as_int();
    auto rows = table.attribute( "rows" ).as_int();

    // get the storage order
    auto order = table.attribute( "storageOrder" );
    StorageOrder storage = order ? createStorageOrder( order.as_string() )
                                 : StorageOrder::RowMajor;

    // the headers and data
    auto headers = readColumnHeaders( table.child( "columnHeaders" ) );
    if ( columns != headers.size() ) {

      Log::error( "The number of columns in the table is incorrect, "
                  "found {} as the number of columns but found {} headers",
                  columns, headers.size() );
      throw std::exception();
    }
    auto content = readData( table.child( "data" ) );
    if ( content.size() != rows * columns ) {

      Log::error( "The number of values in the table data is incorrect, "
                  "found {} values but expected {} values", content.size(), rows * columns );
      throw std::exception();
    }

    // split into columns
    if ( storage == StorageOrder::RowMajor ) {

      // row major
      for ( int i = 0; i < columns; ++i ) {

        auto x = content | std20::views::drop( i ) | std23::views::stride( columns );
        data.emplace_back( headers[i].name,
                           createVector( x ),
                           headers[i].unit );
      }
    }
    else {

      // column major
      auto iter = content.begin();
      for ( int i = 0; i < columns; ++i ) {

        auto end = std::next( iter, rows );
        data.emplace_back( headers[i].name,
                           std::vector< double >( iter, end ),
                           headers[i].unit );
        iter = end;
      }
    }

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
