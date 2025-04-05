#ifndef NJOY_DRYAD_FORMAT_GNDS_READCONSTANT1D
#define NJOY_DRYAD_FORMAT_GNDS_READCONSTANT1D

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/readAxes.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using RealConstant1d = std::pair< double, std::string >;
  using IntegerConstant1d = std::pair< int, std::string >;

  /**
   *  @brief Read data from a GNDS constant1d node as a double
   */
  static RealConstant1d readConstant1dAsDouble( const pugi::xml_node& constant1d ) {

    // check that this is a valid constant1d node
    throwExceptionOnWrongNode( constant1d, "constant1d" );

    // initialise the data
    RealConstant1d data( constant1d.attribute( "value" ).as_double(), "" );

    // get the unit for the constant
    auto axes = constant1d.child( "axes" );
    if ( axes ) {

      auto units = readAxes( axes );
      data.second = std::get< 1 >( units[1] ).value();
    }

    return data;
  }

  /**
   *  @brief Read data from a GNDS constant1d node as an int
   */
  IntegerConstant1d readConstant1dAsInteger( const pugi::xml_node& constant1d ) {

    // check that this is a valid constant1d node
    throwExceptionOnWrongNode( constant1d, "constant1d" );

    // initialise the data
    IntegerConstant1d data( constant1d.attribute( "value" ).as_int(), "" );

    // get the unit for the constant
    auto axes = constant1d.child( "axes" );
    if ( axes ) {

      auto units = readAxes( axes );
      data.second = std::get< 1 >( units[1] ).value();
    }

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
