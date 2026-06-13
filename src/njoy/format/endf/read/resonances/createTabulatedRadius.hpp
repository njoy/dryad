#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_CREATETABULATEDRADIUS
#define NJOY_FORMAT_ENDF_READ_RESONANCES_CREATETABULATEDRADIUS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/resonances/TabulatedRadius.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {

  /**
   *  @brief Create a TabulatedCrossSection from a parsed ENDF section
   *
   *  @param[in] radius   the energy dependent scattering radius record
   */
  inline auto createTabulatedRadius( const ENDFtk::section::Type< 2, 151 >::ScatteringRadius& radius ) {

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
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
