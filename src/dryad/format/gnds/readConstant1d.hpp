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

  using Constant1d = std::pair< double, std::string >;

  /**
   *  @brief Read data from a GNDS constant1d node
   */
  Constant1d readConstant1d( const pugi::xml_node& constant1d ) {

    throwExceptionOnWrongNode( constant1d, "constant1d" );

    Constant1d data( constant1d.attribute( "value" ).as_double(), "" );
  
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
