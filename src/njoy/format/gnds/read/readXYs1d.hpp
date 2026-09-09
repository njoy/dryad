#ifndef NJOY_FORMAT_GNDS_READ_READXYS1D
#define NJOY_FORMAT_GNDS_READ_READXYS1D

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"
#include "njoy/format/gnds/read/readValues.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief The XYs1d information
   */
  struct XYs1d {

    std::optional< double > outer = std::nullopt;
    std::optional< std::string > outer_unit = std::nullopt;
    std::vector< double > x;
    std::optional< std::string > x_unit = std::nullopt;
    std::vector< double > y;
    std::optional< std::string > y_unit = std::nullopt;
    std::string interpolation;
  };


  /**
   *  @brief Read data from a GNDS XYs1D node
   *
   *  @param[in] xys1d   the gnds xys1d node
   */
  inline XYs1d readXYs1D( const pugi::xml_node& xys1d ) {

    throwExceptionOnWrongNode( xys1d, "XYs1d" );

    XYs1d data;

    using namespace njoy::tools;

    // the axes and values nodes
    auto axes = xys1d.child( "axes" );
    auto values = xys1d.child( "values" );

    // get units for tabulated values
    if ( axes ) {

      auto units = readAxes( axes );
      if ( units.size() == 2 ) {

        data.x_unit = units[0].unit;
        data.y_unit = units[1].unit;
      }
      else {

        data.outer_unit = units[0].unit;
        data.x_unit = units[1].unit;
        data.y_unit = units[2].unit;
      }
    }

    // check for the presence of an outerDomainValue
    auto outer = xys1d.attribute( "outerDomainValue" );
    if ( outer ) {

      data.outer = outer.as_double();
    }

    // check for interpolation type
    auto interpolation = xys1d.attribute( "interpolation" );
    if ( interpolation ) {

      data.interpolation = interpolation.as_string();
    }

    // get tabulated values
    std::vector< double > content = readValues( values );
    if ( content.size() == 0 || content.size()%2 == 1 ) {

      Log::error( "The number of values in the tabulated values cannot be zero and has to be even, "
                  "found {} values", content.size() );
      throw std::exception();
    }

    // move data to their respective vectors
    auto x = content | std23::views::stride( 2 );
    auto y = content | std20::views::drop( 1 )| std23::views::stride( 2 );
    data.x.insert( data.x.begin(), x.begin(), x.end() );
    data.y.insert( data.y.begin(), y.begin(), y.end() );

    return data;
  }

  /**
   *  @brief Read data from a GNDS XYs1D node
   */
  inline XYs1d
  readXYs1D( const pugi::xml_node& xys1d, const Axes& units ) {

    XYs1d data = readXYs1D( xys1d );

    // get units for tabulated values
    if ( units.size() > 0 ) {

      if ( units.size() == 2 ) {

        if ( ! data.x_unit.has_value() ) { data.x_unit = units[0].unit; };
        if ( ! data.y_unit.has_value() ) { data.y_unit = units[1].unit; };
      }
      else {

        if ( ! data.outer_unit.has_value() ) { data.outer_unit = units[0].unit; };
        if ( ! data.x_unit.has_value() ) { data.x_unit = units[1].unit; };
        if ( ! data.y_unit.has_value() ) { data.y_unit = units[2].unit; };
      }
    }

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
