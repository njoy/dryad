#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDFORMFACTOR
#define NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDFORMFACTOR

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/TabulatedFormFactor.hpp"
#include "ENDFtk/section/27.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedFormFactor from a parsed ENDF section
   */
  TabulatedFormFactor
  createTabulatedFormFactor( const ENDFtk::section::Type< 27 >& section ) {

    if ( ( section.sectionNumber() != 505 ) && ( section.sectionNumber() != 506 ) ) {

      Log::error( "Tabulated form factors are only defined in MF27 MT505 and MT506, "
                  "got MT{} instead", section.sectionNumber() );
      throw std::exception();
    }

    try {

      Log::info( "Reading form factor data" );
      auto energies = createVector( section.X() );
      auto values = createVector( section.H() );
      auto boundaries = createBoundaries( section.boundaries() );
      auto interpolants = createInterpolants( section.interpolants() );
      return TabulatedFormFactor(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated scattering function" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedFormFactor from an unparsed ENDF section
   */
  TabulatedFormFactor
  createTabulatedFormFactor( const ENDFtk::tree::Section& tree ) {

    if ( tree.fileNumber() == 27 ) {

      return createTabulatedFormFactor( tree.parse< 27 >() );
    }
    else {

      Log::error( "The MAT{} MF{} MT{} section does not define a "
                  "tabulated form factor", tree.materialNumber(),
                  tree.fileNumber(), tree.sectionNumber() );
      throw std::exception();
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
