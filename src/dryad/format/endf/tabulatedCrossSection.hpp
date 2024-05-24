#ifndef NJOY_DRYAD_FORMAT_ENDF_TABULATEDCROSSSECTION
#define NJOY_DRYAD_FORMAT_ENDF_TABULATEDCROSSSECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/boundaries.hpp"
#include "dryad/format/endf/interpolants.hpp"
#include "dryad/TabulatedCrossSection.hpp"
#include "ENDFtk/section/3.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedCrossSection from a parsed ENDF MF3 section
   */
  TabulatedCrossSection
  tabulatedCrossSection( const ENDFtk::section::Type< 3 >& section ) {

    try {

      auto energies = section.energies();
      auto values = section.crossSections();
      auto interpolants = section.interpolants();
      auto boundaries = section.boundaries();
      return TabulatedCrossSection(
               std::vector< double >( energies.begin(), energies.end() ),
               std::vector< double >( values.begin(), values.end() ),
               endf::boundaries( boundaries ),
               endf::interpolants( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "MF3 MT{} - Error encountered while creating a tabulated "
                 "cross section", section.sectionNumber() );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedCrossSection from an unparsed ENDF MF3 section
   */
  TabulatedCrossSection
  tabulatedCrossSection( const ENDFtk::tree::Section& tree ) {

    if ( tree.sectionNumber() != 3 ) {

      Log::error( "The ENDF MAT{} MF{} MT{} section does not contain a tabulated "
                  "cross section", tree.materialNumber(), tree.fileNumber(),
                  tree.sectionNumber() );
    }

    return tabulatedCrossSection( tree.parse< 3 >() );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
