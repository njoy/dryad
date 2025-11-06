#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_CREATETABULATEDRADIUS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_CREATETABULATEDRADIUS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/constants.hpp"
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

      // ENDF gives a radius in 1e-12 cm, dryad stores it in fm

      Log::info( "Reading energy dependent scattering radius" );
      auto energies = createVector( radius.energies() );
      auto values = createVector( radius.radii() );
      std::transform( values.begin(), values.end(), values.begin(),
                      [] ( auto&& value ) { return value * constants::deca; } );
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
