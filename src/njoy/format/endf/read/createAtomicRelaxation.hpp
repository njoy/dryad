#ifndef NJOY_FORMAT_ENDF_READ_CREATEATOMICRELAXATION
#define NJOY_FORMAT_ENDF_READ_CREATEATOMICRELAXATION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "njoy/format/endf/read/atomic/createElectronSubshellConfiguration.hpp"
#include "njoy/format/endf/read/createDocumentation.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create an AtomicRelaxation from an unparsed ENDF material
   *
   *  @param[in] material    the unparsed ENDF material
   *  @param[in] normalise   option to indicate whether or not to normalise
   *                         all probability data
   */
  inline dryad::AtomicRelaxation
  createAtomicRelaxation( const ENDFtk::tree::Material& material, bool normalise ) {

    if ( material.hasSection( 28, 533 ) ) {

      auto information = material.section( 1, 451 ).parse< 1, 451 >();
      auto data = material.section( 28, 533 ).parse< 28 >();

      if ( ( data.targetIdentifier() == 0 ) || ( data.targetIdentifier() % 1000 != 0 ) ) {

        Log::error( "Atomic relaxation data should be given for elements, found za = {}",
                    data.targetIdentifier() );
        throw std::exception();
      }

      dryad::Documentation documentation = createDocumentation( information );

      dryad::id::ElementID element( data.targetIdentifier() / 1000 );
      std::vector< dryad::atomic::ElectronSubshellConfiguration > subshells;
      for ( const auto& subshell : data.subshells() ) {

        subshells.emplace_back( atomic::createElectronSubshellConfiguration( subshell, normalise ) );
      }

      return dryad::AtomicRelaxation( std::move( documentation ), std::move( element ),
                                      std::move( subshells ) );
    }
    else {

      Log::error( "The ENDF file does not contain atomic relaxation data" );
      throw std::exception();
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
