#ifndef NJOY_DRYAD_FORMAT_ENDF_METADATA
#define NJOY_DRYAD_FORMAT_ENDF_METADATA

// system includes

// other includes
#include "tools/Log.hpp"
#include "dryad/Metadata.hpp"
#include "ENDFtk/section/1/451.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a PolynomialMultiplicity from a parsed ENDF multiplicity
   */
  Metadata
  createMetadata( const ENDFtk::section::Type< 1, 451 >& information ) {

    Log::info( "Reading metadata" );

    std::optional< double > temperature = std::nullopt;
    if ( ( information.subLibrary() != 1 ) && ( information.subLibrary() != 4 ) &&
         ( information.subLibrary() != 5 ) && ( information.subLibrary() != 6 ) &&
         ( information.subLibrary() != 11 ) && ( information.subLibrary() != 12 ) ) {

      temperature = information.temperature();
    }

    return Metadata( information.atomicWeightRatio(), information.libraryType(),
                     std::make_pair( information.versionNumber(),
                                     information.releaseNumber() ),
                     std::move( temperature ),
                     information.description() );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
