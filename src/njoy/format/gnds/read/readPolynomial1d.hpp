#ifndef NJOY_FORMAT_GNDS_READ_READPOLYNOMIAL1D
#define NJOY_FORMAT_GNDS_READ_READPOLYNOMIAL1D

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"
#include "njoy/format/gnds/read/readValues.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief The one dimensional polynomial data
   */
  struct Polynomial1d {

    std::optional< double > outer = std::nullopt;
    std::optional< std::string > outer_unit = std::nullopt;
    double lower;
    double upper;
    std::vector< double > coefficients;
    std::optional< std::string > x_unit = std::nullopt;
    std::optional< std::string > y_unit = std::nullopt;
  };

  /**
   *  @brief Read data from a GNDS polynomial1d node
   *
   *  @param[in] polynomial1d   the gnds polynomial1d node
   */
  inline Polynomial1d readPolynomial1d( const pugi::xml_node& polynomial1d ) {

    throwExceptionOnWrongNode( polynomial1d, "polynomial1d" );

    Polynomial1d data;

    // the axes and values nodes
    auto axes = polynomial1d.child( "axes" );
    auto values = polynomial1d.child( "values" );

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

    // check for initial zeros
    auto zeros = polynomial1d.attribute( "lowerIndex" );
    if ( zeros ) {

      auto number = zeros.as_int();
      if ( number > 0 ) {

        data.coefficients = std::vector< double >( number, 0 );
      }
    }

    // check for the presence of an outerDomainValue
    auto outer = polynomial1d.attribute( "outerDomainValue" );
    if ( outer ) {

      data.outer = outer.as_double();
    }

    // check for domain
    auto lower = polynomial1d.attribute( "domainMin" );
    auto upper = polynomial1d.attribute( "domainMax" );
    if ( lower && upper ) {

      data.lower = lower.as_double();
      data.upper = upper.as_double();
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
    data.coefficients.insert( data.coefficients.end(), content.begin(), content.end() );

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
