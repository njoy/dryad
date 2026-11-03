#ifndef NJOY_FORMAT_ENDF_READ_CREATETABULATEDFORMFACTOR
#define NJOY_FORMAT_ENDF_READ_CREATETABULATEDFORMFACTOR

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedFormFactor.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/27.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a TabulatedFormFactor from a parsed ENDF section
   *
   *  @param[in] section   the parsed ENDF form factors
   *  @param[in] curate    the flag to indicate whether or not tabulated data
   *                       need to be curated
   */
  inline dryad::TabulatedFormFactor
  createTabulatedFormFactor( const ENDFtk::section::Type< 27 >& section, bool curate ) {

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
      return dryad::TabulatedFormFactor(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ),
               curate );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated scattering function" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedFormFactor from an unparsed ENDF section
   *
   *  @param[in] section   the unparsed ENDF form factors
   *  @param[in] curate    the flag to indicate whether or not tabulated data
   *                       need to be curated
   */
  dryad::TabulatedFormFactor
  createTabulatedFormFactor( const ENDFtk::tree::Section& tree, bool curate ) {

    if ( tree.fileNumber() == 27 ) {

      return createTabulatedFormFactor( tree.parse< 27 >(), curate );
    }
    else {

      Log::error( "The MAT{} MF{} MT{} section does not define a "
                  "tabulated form factor", tree.materialNumber(),
                  tree.fileNumber(), tree.sectionNumber() );
      throw std::exception();
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
