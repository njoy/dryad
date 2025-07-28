#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEATOMICrELAXATION
#define NJOY_DRYAD_FORMAT_ENDF_CREATEATOMICrELAXATION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/atomic/createElectronSubshellConfiguration.hpp"
#include "dryad/format/endf/createDocumentation.hpp"
#include "dryad/AtomicRelaxation.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an AtomicRelaxation from an unparsed ENDF material
   *
   *  @param[in] material    the unparsed ENDF material
   *  @param[in] normalise   option to indicate whether or not to normalise
   *                         all probability data
   */
  AtomicRelaxation createAtomicRelaxation( const ENDFtk::tree::Material& material,
                                           bool normalise ) {

    if ( material.hasSection( 28, 533 ) ) {

      auto information = material.section( 1, 451 ).parse< 1, 451 >();
      auto data = material.section( 28, 533 ).parse< 28 >();

      if ( ( data.targetIdentifier() == 0 ) || ( data.targetIdentifier() % 1000 != 0 ) ) {

        Log::error( "Atomic relaxation data should be given for elements, found za = {}",
                    data.targetIdentifier() );
        throw std::exception();
      }

      id::ElementID element( data.targetIdentifier() / 1000 );
      std::vector< dryad::atomic::ElectronSubshellConfiguration > subshells;
      for ( const auto& subshell : data.subshells() ) {

        subshells.emplace_back( atomic::createElectronSubshellConfiguration( subshell, normalise ) );
      }

      Documentation documentation = createDocumentation( information );

      return AtomicRelaxation( std::move( documentation ), std::move( element ),
                               std::move( subshells ) );
    }
    else {

      Log::error( "The ENDF file does not contain atomic relaxation data" );
      throw std::exception();
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
