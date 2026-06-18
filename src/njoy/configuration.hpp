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

static std::string datapath() {

  if ( const char* njoy_datapath = std::getenv( "NJOY_DATAPATH" ) ) {

    return njoy_datapath;
  }
#ifdef NJOY_DATAPATH
  return NJOY_DATAPATH;
#else
  throw std::runtime_error( "NJOY_DATAPATH is not set as an environment variable "
                            "and was not defined at build time." );
#endif
}

/**
 *  @brief Return the NJOY configuration data
 */
static tools::Configuration& configuration() {

  filesystem::path path( datapath() );
  path /= "njoy.config";
  return tools::Configuration::getInstance( path.string() );

  }

} // njoy namespace

#endif
