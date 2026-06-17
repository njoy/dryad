#ifndef NJOY_CONFIGURATION
#define NJOY_CONFIGURATION

// system includes
#include <cstdlib>

#if __has_include(<filesystem>) && (defined(_MSVC_LANG) ? (_MSVC_LANG >= 201703L) : (__cplusplus >= 201703L))
#include <filesystem>
namespace filesystem = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;
#endif

// other includes
#include "tools/Configuration.hpp"

namespace njoy {

/**
 *  @brief Return the NJOY configuration data
 */
static tools::Configuration& configuration() {

  if ( const char* njoy_datapath = std::getenv( "NJOY_DATAPATH" ) ) {

    filesystem::path path( njoy_datapath );
    path /= "njoy.config";
    return tools::Configuration::getInstance( path.string() );
  }
#ifdef NJOY_DATAPATH
  else {

    filesystem::path path( NJOY_DATAPATH );
    path /= "njoy.config";
    return tools::Configuration::getInstance( path.string() );
  }
#else
  else {

    throw std::runtime_error( "The NJOY_DATAPATH environmental variable is not set." );
  }
#endif
}

} // njoy namespace

#endif
