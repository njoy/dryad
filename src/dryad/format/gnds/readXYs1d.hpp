#ifndef NJOY_DRYAD_FORMAT_GNDS_READXYS1D
#define NJOY_DRYAD_FORMAT_GNDS_READXYS1D

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/readAxes.hpp"
#include "dryad/format/gnds/readValues.hpp"
#include "tools/Log.hpp"
#include "tools/disco/FreeFormatReal.hpp"
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using XYs1d = std::tuple< std::optional< double >, std::optional< std::string >, 
                            std::vector< double >, std::string,
                            std::vector< double >, std::string, 
                            std::string >;
  /**
   *  @brief Read data from a GNDS XYs1D note
   */
  XYs1d readXYs1D( const pugi::xml_node& xys1d ) {

    XYs1d data;
    std::get< 0 >( data ) = std::nullopt;
    std::get< 1 >( data ) = std::nullopt;

    using namespace njoy::tools;

    // the axes and values nodes
    auto axes = xys1d.child( "axes" );
    auto values = xys1d.child( "values" );

    // get units for tabulated values
    if ( axes ) {

      auto units = readAxes( axes );
      if ( units.size() == 2 ) {

        std::get< 3 >( data ) = units[0];
        std::get< 5 >( data ) = units[1];
      }
      else {

        std::get< 1 >( data ) = units[0];
        std::get< 3 >( data ) = units[1];
        std::get< 5 >( data ) = units[2];
      }
    }

    // check for the presence of an outerDomainValue
    auto outer = xys1d.attribute( "outerDomainValue" );
    if ( outer ) {

      std::get< 0 >( data ) = outer.as_double();
    }

    // check for interpolation type
    auto interpolation = xys1d.attribute( "interpolation" );
    if ( interpolation ) {

      std::get< 6 >( data ) = interpolation.as_string();
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
    std::get< 2 >( data ).insert( std::get< 2 >( data ).begin(), x.begin(), x.end() );
    std::get< 4 >( data ).insert( std::get< 4 >( data ).begin(), y.begin(), y.end() );

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
