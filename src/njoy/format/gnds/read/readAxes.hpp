#ifndef NJOY_FORMAT_GNDS_READ_READAXES
#define NJOY_FORMAT_GNDS_READ_READAXES

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/readAxis.hpp"
#include "njoy/format/gnds/read/readGrid.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  using Axes = std::vector< std::tuple< std::optional< int >,
                                        std::optional< std::string >,
                                        std::optional< std::vector< double > > > >;

  /**
   *  @brief Read data from a GNDS axes node
   */
  inline Axes readAxes( const pugi::xml_node& axes ) {

    throwExceptionOnWrongNode( axes, "axes" );

    Axes data;

    for ( pugi::xml_node child = axes.first_child(); child; child = child.next_sibling() ) {

      if ( strcmp( child.name(), "axis" ) == 0 ) {

        auto axis = readAxis( child );
        data.emplace_back( std::move( axis.first ), std::move( axis.second ), std::nullopt );
      }
      else if ( strcmp( child.name(), "grid" ) == 0 ) {

        auto grid = readGrid( child );
        data.emplace_back( std::move( std::get< 0 >( grid ) ),
                           std::move( std::get< 1 >( grid ) ),
                           std::move( std::get< 2 >( grid ) ) );
      }
    }
    std::sort( data.begin(), data.end(),
               [] ( auto&& left, auto&& right )
                  { return std::get< 0 >( left ) > std::get< 0 >( right ); } );

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
