#ifndef NJOY_DRYAD_FORMAT_ENDF_METADATA
#define NJOY_DRYAD_FORMAT_ENDF_METADATA

// system includes

// other includes
#include "tools/Log.hpp"
#include "dryad/Documentation.hpp"
#include "ENDFtk/section/1/451.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a PolynomialMultiplicity from a parsed ENDF multiplicity
   */
  Documentation
  createDocumentation( const ENDFtk::section::Type< 1, 451 >& information ) {

    Log::info( "Reading documentation" );
    return Documentation( information.atomicWeightRatio(), information.libraryType(),
                          std::make_pair( information.versionNumber(),
                                          information.releaseNumber() ),
                          information.description() );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
