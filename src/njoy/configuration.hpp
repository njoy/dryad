#ifndef NJOY_CONFIGURATION
#define NJOY_CONFIGURATION

// system includes
#include <cstdlib>
#include <filesystem>

// other includes
#include "tools/Configuration.hpp"

namespace njoy {

/**
 *  @brief Return the NJOY configuration data
 */
static tools::Configuration& configuration() {

  if ( const char* njoy_datapath = std::getenv( "NJOY_DATAPATH" ) ) {

    std::filesystem::path path( njoy_datapath );
    path /= "njoy.config";
    return tools::Configuration::getInstance( path.string() );
  }
  else {

    throw std::runtime_error( "The NJOY_DATAPATH environmental variable is not set." );
  }
}

} // njoy namespace

#endif
