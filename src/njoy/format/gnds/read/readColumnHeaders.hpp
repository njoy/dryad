#ifndef NJOY_FORMAT_GNDS_READ_READCOLUMNHEADERS
#define NJOY_FORMAT_GNDS_READ_READCOLUMNHEADERS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/readColumn.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  using Headers = std::vector< std::tuple< int,
                                           std::string,
                                           std::optional< std::string > > >;

  /**
   *  @brief Read data from a GNDS column headers node
   *
   *  @param[in] headers   the gnds columnHeaders node
   */
  inline Headers readColumnHeaders( const pugi::xml_node& headers ) {

    throwExceptionOnWrongNode( headers, "columnHeaders" );

    Headers data;

    for ( pugi::xml_node child = headers.child( "column" ); child;
          child = child.next_sibling( "column" ) ) {

      data.emplace_back( readColumn( child ) );
    }
    std::sort( data.begin(), data.end(),
               [] ( auto&& left, auto&& right )
                  { return std::get< 0 >( left ) < std::get< 0 >( right ); } );

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
