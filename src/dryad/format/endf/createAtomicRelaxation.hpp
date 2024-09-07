#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEATOMICrELAXATION
#define NJOY_DRYAD_FORMAT_ENDF_CREATEATOMICrELAXATION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/atomic/createElectronSubshellConfiguration.hpp"
#include "dryad/AtomicRelaxation.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an AtomicRelaxation from an unparsed ENDF material
   */
  AtomicRelaxation createAtomicRelaxation( const ENDFtk::tree::Material& material ) {

    if ( material.hasSection( 28, 533 ) ) {

      auto data = material.section( 28, 533 ).parse< 28 >();

      if ( ( data.targetIdentifier() == 0 ) || ( data.targetIdentifier() % 1000 != 0 ) ) {

        Log::error( "Atomic relaxation data should be given for elements, found za = {}",
                    data.targetIdentifier() );
        throw std::exception();
      }

      id::ElementID element( data.targetIdentifier() / 1000 );
      std::vector< dryad::atomic::ElectronSubshellConfiguration > subshells;
      for ( const auto& subshell : data.subshells() ) {

        subshells.push_back( atomic::createElectronSubshellConfiguration( subshell ) );
      }

      return AtomicRelaxation( std::move( element ), std::move( subshells ) );
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
