#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDCROSSSECTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDCROSSSECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/resonances/TabulatedRadius.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {

  /**
   *  @brief Create a TabulatedCrossSection from a parsed ENDF section
   *
   *  @param[in] radius   the energy dependent scattering radius record
   */
  auto createTabulatedRadius( const ENDFtk::section::Type< 2, 151 >::ScatteringRadius& radius ) {

    try {

      Log::info( "Reading energy dependent scattering radius" );
      auto energies = createVector( radius.energies() );
      auto values = createVector( radius.radii() );
      auto boundaries = createBoundaries( radius.boundaries() );
      auto interpolants = createInterpolants( radius.interpolants() );
      return dryad::resonances::TabulatedRadius(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated scattering radius" );
      throw;
    }
  }

} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
