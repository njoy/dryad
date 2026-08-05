#ifndef NJOY_FORMAT_GNDS_READ_READCONSTANT1D
#define NJOY_FORMAT_GNDS_READ_READCONSTANT1D

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  using RealConstant1d = std::pair< double, std::optional< std::string > >;
  using IntegerConstant1d = std::pair< int, std::optional< std::string > >;

  /**
   *  @brief Read data from a GNDS constant1d node as a double
   *
   *  @param[in] constant1d   the gnds constant1d node
   */
  inline RealConstant1d readConstant1dAsDouble( const pugi::xml_node& constant1d ) {

    // check that this is a valid constant1d node
    throwExceptionOnWrongNode( constant1d, "constant1d" );

    // initialise the data
    RealConstant1d data( constant1d.attribute( "value" ).as_double(), "" );

    // get the unit for the constant
    auto axes = constant1d.child( "axes" );
    if ( axes ) {

      auto units = readAxes( axes );
      data.second = std::get< 1 >( units[1] );
    }

    return data;
  }

  /**
   *  @brief Read data from a GNDS constant1d node as an int
   *
   *  @param[in] constant1d   the gnds constant1d node
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
      data.second = std::get< 1 >( units[1] );
    }

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
