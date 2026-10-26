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
   *  @brief Create a TabulatedCrossSection from a parsed ENDF MF3 section
   *
   *  @param[in] section   the parsed ENDF cross section
   *  @param[in] curate    the flag to indicate whether or not tabulated data
   *                       need to be curated
   */
  inline dryad::TabulatedCrossSection
  createTabulatedCrossSection( const ENDFtk::section::Type< 3 >& section, bool curate ) {

    auto is_charged_particle = [] ( auto&& interpolant ) {

      return interpolant == dryad::InterpolationType::CoulombPenetrability;
    };

    try {

      Log::info( "Reading cross section data" );
      auto energies = createVector( section.energies() );
      auto values = createVector( section.crossSections() );
      auto boundaries = createBoundaries( section.boundaries() );
      auto interpolants = createInterpolants( section.interpolants() );

      std::optional< double > threshold = std::nullopt;
      if ( std::any_of( interpolants.begin(), interpolants.end(), is_charged_particle ) ) {

        if ( section.reactionQValue() < 0 ) {

          Log::error( "Found a threshold reaction using Coulomb penetrability interpolation, "
                      "contact an njoy developer" );
          throw std::exception();
        }

        threshold = 0;
      }

      return dryad::TabulatedCrossSection(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ),
               curate, std::move( threshold ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated cross section" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedCrossSection from a parsed ENDF MF23 section
   *
   *  @param[in] section   the parsed ENDF cross section
   *  @param[in] curate    the flag to indicate whether or not tabulated data
   *                       need to be curated
   */
  inline dryad::TabulatedCrossSection
  createTabulatedCrossSection( const ENDFtk::section::Type< 23 >& section, bool curate ) {

    try {

      Log::info( "Reading cross section data" );
      auto energies = createVector( section.energies() );
      auto values = createVector( section.crossSections() );
      auto boundaries = createBoundaries( section.boundaries() );
      auto interpolants = createInterpolants( section.interpolants() );
      return dryad::TabulatedCrossSection(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ),
               curate );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated cross section" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedCrossSection from an unparsed ENDF section
   *
   *  @param[in] section   the unparsed ENDF cross section (MF3 or MF23)
   *  @param[in] curate    the flag to indicate whether or not tabulated data
   *                       need to be curated
   */
  inline dryad::TabulatedCrossSection
  createTabulatedCrossSection( const ENDFtk::tree::Section& tree, bool curate ) {

    switch ( tree.fileNumber() ) {

      case  3 : return createTabulatedCrossSection( tree.parse< 3 >(), curate );
      case 23 : return createTabulatedCrossSection( tree.parse< 23 >(), curate );
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
