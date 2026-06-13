#ifndef NJOY_FORMAT_ENDF_READ_CREATETABULATEDSCATTERINGFUNCTION
#define NJOY_FORMAT_ENDF_READ_CREATETABULATEDSCATTERINGFUNCTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedScatteringFunction.hpp"
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
   *  @brief Create a TabulatedScatteringFunction from a parsed ENDF section
   */
  inline dryad::TabulatedScatteringFunction
  createTabulatedScatteringFunction( const ENDFtk::section::Type< 27 >& section ) {

    if ( ( section.sectionNumber() != 502 ) && ( section.sectionNumber() != 504 ) ) {

      Log::error( "Tabulated scattering functions are only defined in MF27 MT502 and MT504, "
                  "got MT{} instead", section.sectionNumber() );
      throw std::exception();
    }

    try {

      Log::info( "Reading scattering function data" );
      auto x = createVector( section.X() );
      auto values = createVector( section.H() );
      auto boundaries = createBoundaries( section.boundaries() );
      auto interpolants = createInterpolants( section.interpolants() );
      return dryad::TabulatedScatteringFunction(
               std::move( x ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated scattering function" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedScatteringFunction from an unparsed ENDF section
   */
  inline dryad::TabulatedScatteringFunction
  createTabulatedScatteringFunction( const ENDFtk::tree::Section& tree ) {

    if ( tree.fileNumber() == 27 ) {

      return createTabulatedScatteringFunction( tree.parse< 27 >() );
    }
    else {

      Log::error( "The MAT{} MF{} MT{} section does not define a "
                  "tabulated scattering function", tree.materialNumber(),
                  tree.fileNumber(), tree.sectionNumber() );
      throw std::exception();
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
