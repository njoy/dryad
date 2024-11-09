#ifndef NJOY_DRYAD_FORMAT_GNDS_READLEGENDRE
#define NJOY_DRYAD_FORMAT_GNDS_READLEGENDRE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/readValues.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using Legendre = std::pair< std::optional< double >, std::vector< double > >;
  /**
   *  @brief Read data from a GNDS legendre node
   */
  Legendre readLegendre( const pugi::xml_node& legendre ) {

    if ( legendre ) {
  
      Legendre data;
      data.first = std::nullopt;
    
      // check for the presence of an outerDomainValue
      auto outer = legendre.attribute( "outerDomainValue" );
      if ( outer ) {
    
        data.first = outer.as_double();
      }
    
      // get tabulated values
      auto values = legendre.child( "values" );
      data.second = readValues( values );
      if ( data.second.size() == 0 ) {
    
        Log::error( "There should be at least one value in the GNDS Legendre node, "
                    "found {} values", data.second.size() );
        throw std::exception();
      }
    
      return data;
    }
    else {

      Log::error( "The XML element does not define a GNDS Legendre node" );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
