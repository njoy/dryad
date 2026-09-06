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

  /**
   *  @brief The axis information: an optional index, unit and grid values
   */
  struct AxisInformation {

    std::optional< int > index = std::nullopt;
    std::optional< std::string > unit = std::nullopt;
    std::optional< std::vector< double > > values = std::nullopt;

    // C++-20 : constructor no longer required for emplace/emplace_back
    AxisInformation( std::optional< int > index, std::optional< std::string > unit,
                     std::optional< std::vector< double > > values ) :
      index( std::move( index ) ), unit( std::move( unit ) ), values( std::move( values ) ) {}
  };

  using Axes = std::vector< AxisInformation >;

  /**
   *  @brief Read data from a GNDS axes node
   *
   *  @param[in] axes   the gnds axes node
   */
  inline Axes readAxes( const pugi::xml_node& axes ) {

    throwExceptionOnWrongNode( axes, "axes" );

    Axes data;

    for ( pugi::xml_node child = axes.first_child(); child; child = child.next_sibling() ) {

      if ( strcmp( child.name(), "axis" ) == 0 ) {

        auto axis = readAxis( child );
        data.emplace_back( std::move( axis.index ), std::move( axis.unit ), std::nullopt );
      }
      else if ( strcmp( child.name(), "grid" ) == 0 ) {

        auto grid = readGrid( child );
        data.emplace_back( std::move( grid.index ), std::move( grid.unit ), std::move( grid.values ) );
      }
    }
    std::sort( data.begin(), data.end(),
               [] ( auto&& left, auto&& right )
                  { return left.index > right.index; } );

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
