#ifndef NJOY_DRYAD_FORMAT_ENDF_TABULATEDCROSSSECTION
#define NJOY_DRYAD_FORMAT_ENDF_TABULATEDCROSSSECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/TabulatedCrossSection.hpp"
#include "ENDFtk/section/3.hpp"
#include "ENDFtk/section/23.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedCrossSection from a parsed ENDF section
   */
  template < typename Section >
  auto createTabulatedCrossSection( const Section& section )
  -> std::enable_if_t< ( std::is_same_v< Section, ENDFtk::section::Type< 3 > > ||
                         std::is_same_v< Section, ENDFtk::section::Type< 23 > > ),
                       TabulatedCrossSection > {

    try {

      Log::info( "Reading cross section data" );
      auto energies = createVector( section.energies() );
      auto values = createVector( section.crossSections() );
      auto boundaries = createBoundaries( section.boundaries() );
      auto interpolants = createInterpolants( section.interpolants() );
      return TabulatedCrossSection(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated "
                 "cross section for MT{}", section.sectionNumber() );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedCrossSection from an unparsed ENDF section
   */
  TabulatedCrossSection
  createTabulatedCrossSection( const ENDFtk::tree::Section& tree ) {

    switch ( tree.fileNumber() ) {

      case  3 : return createTabulatedCrossSection( tree.parse< 3 >() );
      case 23 : return createTabulatedCrossSection( tree.parse< 23 >() );
      default : {

        Log::error( "The MAT{} MF{} MT{} section does not define a "
                    "tabulated cross section", tree.materialNumber(),
                    tree.fileNumber(), tree.sectionNumber() );
        throw std::exception();
      }
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
