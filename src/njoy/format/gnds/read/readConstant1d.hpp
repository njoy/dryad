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

  /**
   *  @brief The axis information: an optional index and unit
   */
  template < typename Type >
  struct Constant1d {

    Type value;
    std::optional< std::string > unit = std::nullopt;
  };

  /**
   *  @brief Read data from a GNDS constant1d node as a double
   *
   *  @param[in] constant1d   the gnds constant1d node
   */
  inline Constant1d< double > readConstant1dAsDouble( const pugi::xml_node& constant1d ) {

    // check that this is a valid constant1d node
    throwExceptionOnWrongNode( constant1d, "constant1d" );

    // initialise the data
    Constant1d< double > data{ constant1d.attribute( "value" ).as_double(), std::nullopt };

    // get the unit for the constant
    auto axes = constant1d.child( "axes" );
    if ( axes ) {

      auto units = readAxes( axes );
      data.unit = units[1].unit;
    }

    return data;
  }

  /**
   *  @brief Read data from a GNDS constant1d node as an int
   *
   *  @param[in] constant1d   the gnds constant1d node
   */
  inline Constant1d< int > readConstant1dAsInteger( const pugi::xml_node& constant1d ) {

    // check that this is a valid constant1d node
    throwExceptionOnWrongNode( constant1d, "constant1d" );

    // initialise the data
    Constant1d< int > data{ constant1d.attribute( "value" ).as_int(), std::nullopt };

    // get the unit for the constant
    auto axes = constant1d.child( "axes" );
    if ( axes ) {

      auto units = readAxes( axes );
      data.unit = units[1].unit;
    }

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
