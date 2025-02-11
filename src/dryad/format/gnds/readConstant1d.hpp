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

  /**
   *  @brief Read data from a GNDS constant1d node as a double
   */
  static std::pair< double, std::string > 
  readConstant1dAsDouble( const pugi::xml_node& constant1d ) {

    // check that this is a valid constant1d node
    throwExceptionOnWrongNode( constant1d, "constant1d" );

    // initialise the data
    std::pair< double, std::string > data( constant1d.attribute( "value" ).as_double(), "" );
  
    // get the unit for the constant
    auto axes = constant1d.child( "axes" );
    if ( axes ) {
  
      auto units = readAxes( axes );
      data.second = units[1];
    }
  
    return data;
  }

  /**
   *  @brief Read data from a GNDS constant1d node as an int
   */
  std::pair< int, std::string > 
  readConstant1dAsInteger( const pugi::xml_node& constant1d ) {

    // check that this is a valid constant1d node
    throwExceptionOnWrongNode( constant1d, "constant1d" );

    // initialise the data
    std::pair< int, std::string > data( constant1d.attribute( "value" ).as_int(), "" );
  
    // get the unit for the constant
    auto axes = constant1d.child( "axes" );
    if ( axes ) {
  
      auto units = readAxes( axes );
      data.second = units[1];
    }
  
    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
