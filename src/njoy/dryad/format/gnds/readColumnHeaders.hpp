#ifndef NJOY_DRYAD_FORMAT_GNDS_READCOLUMNHEADERS
#define NJOY_DRYAD_FORMAT_GNDS_READCOLUMNHEADERS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "njoy/dryad/format/gnds/readColumn.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using Headers = std::vector< std::tuple< int,
                                           std::string,
                                           std::optional< std::string > > >;

  /**
   *  @brief Read data from a GNDS column headers node
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

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
