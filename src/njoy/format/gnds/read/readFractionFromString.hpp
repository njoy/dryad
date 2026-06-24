#ifndef NJOY_FORMAT_GNDS_READ_READFRACTIONFROMSTRING
#define NJOY_FORMAT_GNDS_READ_READFRACTIONFROMSTRING

// system includes

// other includes
#include "tools/Log.hpp"
#include "tools/split.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Read a fraction from a string
   *
   *  @param[in] string   the string to read the fraction from
   */
  inline double readFractionFromString( const std::string& string ) {

    double value;
    auto pieces = tools::split( string, '/' );
    if ( pieces.size() > 0 && pieces.size() < 3 ) {

      value = std::stoi( pieces[0].c_str() );
      if ( pieces.size() == 2 ) {

        value /= static_cast< double >( std::stoi( pieces[1].c_str() ) );
      }
      return value;
    }
    else {

      Log::error( "The string does not appear to be a proper fraction: \'{}\'", string );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
