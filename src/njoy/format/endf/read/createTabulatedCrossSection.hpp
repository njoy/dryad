#ifndef NJOY_FORMAT_ENDF_READ_CREATETABULATEDCROSSSECTION
#define NJOY_FORMAT_ENDF_READ_CREATETABULATEDCROSSSECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/3.hpp"
#include "ENDFtk/section/23.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a TabulatedCrossSection from a parsed ENDF section
   */
  template < typename Section >
  auto createTabulatedCrossSection( const Section& section )
  -> std::enable_if_t< ( std::is_same_v< Section, ENDFtk::section::Type< 3 > > ||
                         std::is_same_v< Section, ENDFtk::section::Type< 23 > > ),
                       dryad::TabulatedCrossSection > {

    try {

      Log::info( "Reading cross section data" );
      auto energies = createVector( section.energies() );
      auto values = createVector( section.crossSections() );
      auto boundaries = createBoundaries( section.boundaries() );
      auto interpolants = createInterpolants( section.interpolants() );
      return dryad::TabulatedCrossSection(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated cross section" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedCrossSection from an unparsed ENDF section
   */
  inline dryad::TabulatedCrossSection
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

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
