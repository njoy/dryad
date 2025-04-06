#ifndef NJOY_DRYAD_FORMAT_GNDS_READSHAPE
#define NJOY_DRYAD_FORMAT_GNDS_READSHAPE

// system includes
#include <sstream>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Convert the shape
   */
  static std::vector< std::size_t > readShape( const std::string& shape ) {

    std::vector< std::size_t > ints;
    std::istringstream list( shape );

    std::string entry;
    while ( std::getline( list, entry, ',' ) ) {

      try {

        int value = std::stoi( entry );
        if ( value < 0 ) {

          Log::error( "An entry in the comma seperated shape list is negative" );
          Log::info( "shape list : {}", shape );
          Log::info( "entry : {}", entry );
          throw std::exception();
        }
        ints.push_back( static_cast< std::size_t >( value ) );
      }
      catch ( ... ) {

        Log::error( "Cannot convert an entry in the comma seperated shape list into an int" );
        Log::info( "shape list : {}", shape );
        Log::info( "entry : {}", entry );
        throw std::exception();
      }
    }

    return ints;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
