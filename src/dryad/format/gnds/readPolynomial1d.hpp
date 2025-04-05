#ifndef NJOY_DRYAD_FORMAT_GNDS_READPOLYNOMIAL1D
#define NJOY_DRYAD_FORMAT_GNDS_READPOLYNOMIAL1D

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/readAxes.hpp"
#include "dryad/format/gnds/readValues.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using Polynomial1d = std::tuple< std::optional< double >, std::optional< std::string >,
                                   double, double, std::vector< double >,
                                   std::string, std::string >;

  /**
   *  @brief Read data from a GNDS polynomial1d node
   */
  static Polynomial1d readPolynomial1d( const pugi::xml_node& polynomial1d ) {

    throwExceptionOnWrongNode( polynomial1d, "polynomial1d" );

    Polynomial1d data;
    std::get< 0 >( data ) = std::nullopt;
    std::get< 1 >( data ) = std::nullopt;

    // the axes and values nodes
    auto axes = polynomial1d.child( "axes" );
    auto values = polynomial1d.child( "values" );

    // get units for tabulated values
    if ( axes ) {

      auto units = readAxes( axes );
      if ( units.size() == 2 ) {

        std::get< 5 >( data ) = std::get< 1 >( units[0] ).value();
        std::get< 6 >( data ) = std::get< 1 >( units[1] ).value();
      }
      else {

        std::get< 1 >( data ) = std::get< 1 >( units[0] ).value();
        std::get< 5 >( data ) = std::get< 1 >( units[1] ).value();
        std::get< 6 >( data ) = std::get< 1 >( units[2] ).value();
      }
    }

    // check for initial zeros
    auto zeros = polynomial1d.attribute( "lowerIndex" );
    if ( zeros ) {

      auto number = zeros.as_int();
      if ( number > 0 ) {

        std::get< 4 >( data ) = std::vector< double >( number, 0 );
      }
    }

    // check for the presence of an outerDomainValue
    auto outer = polynomial1d.attribute( "outerDomainValue" );
    if ( outer ) {

      std::get< 0 >( data ) = outer.as_double();
    }

    // check for domain
    auto lower = polynomial1d.attribute( "domainMin" );
    auto upper = polynomial1d.attribute( "domainMax" );
    if ( lower && upper ) {

      std::get< 2 >( data ) = lower.as_double();
      std::get< 3 >( data ) = upper.as_double();
    }
    else {

      Log::error( "The lower and/or upper domain values are missing in the GNDS polynomial1d node." );
      throw std::exception();
    }

    // get tabulated values
    std::vector< double > content = readValues( values );
    if ( content.size() == 0 ) {

      Log::error( "There should be at least one value in the GNDS polynomial1d node, "
                  "found {} values", content.size() );
      throw std::exception();
    }
    std::get< 4 >( data ).insert( std::get< 4 >( data ).end(),
                                  content.begin(), content.end() );

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
