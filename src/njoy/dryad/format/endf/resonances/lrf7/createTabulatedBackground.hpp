#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDBACKGROUND
#define NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDBACKGROUND

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/createBoundaries.hpp"
#include "njoy/dryad/format/endf/createInterpolants.hpp"
#include "njoy/dryad/resonances/TabulatedBackground.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create a TabulatedCrossSection from a parsed ENDF section
   *
   *  @param[in] background   the energy dependent scattering radius record
   */
  inline dryad::resonances::TabulatedBackground
  createTabulatedBackground(
      const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::TabulatedBackgroundRMatrix& background ) {

    try {

      Log::info( "Reading energy dependent tabulated background" );
      auto energies = createVector( background.energies() );
      auto values = createVector( background.rmatrix() );
      auto boundaries = createBoundaries( background.boundaries() );
      auto interpolants = createInterpolants( background.interpolants() );
      return dryad::resonances::TabulatedBackground(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated channel background" );
      throw;
    }
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
