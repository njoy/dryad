#ifndef NJOY_FORMAT_ENDF_READ_DOCUMENTATION
#define NJOY_FORMAT_ENDF_READ_DOCUMENTATION

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Documentation.hpp"
#include "ENDFtk/section/1/451.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a Documentation instance from a parsed MF1 MT451 section
   *
   *  @param[in] information   the parsed MF1 MT451 section
   */
  inline dryad::Documentation
  createDocumentation( const ENDFtk::section::Type< 1, 451 >& information ) {

    Log::info( "Reading documentation" );
    return dryad::Documentation( information.libraryType(),
                                 std::make_pair( information.versionNumber(),
                                                 information.releaseNumber() ),
                                 information.description() );
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
