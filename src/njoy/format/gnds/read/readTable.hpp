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

  using Table = std::vector< std::tuple< std::string,
                                         std::vector< double >,
                                         std::optional< std::string > > >;

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
        data.emplace_back( std::get< 1 >( headers[i] ),
                           createVector( x ),
                           std::get< 2 >( headers[i] ) );
      }
    }
    else {

      // column major
      auto iter = content.begin();
      for ( int i = 0; i < columns; ++i ) {

        auto end = std::next( iter, rows );
        data.emplace_back( std::get< 1 >( headers[i] ),
                           std::vector< double >( iter, end ),
                           std::get< 2 >( headers[i] ) );
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
