#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDAVERAGEENERGY
#define NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDAVERAGEENERGY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/TabulatedAverageEnergy.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedAverageEnergy from a parsed ENDF MF26
   *         energy transfer component
   */
  TabulatedAverageEnergy
  createTabulatedAverageEnergy( const ENDFtk::section::Type< 26 >::EnergyTransfer& transfer ) {

    try {

      // the average outgoing electron energy is the incident electron energy minus the
      // transfer value

      auto energies = createVector( transfer.energies() );
      auto values = createVector( transfer.energyTransferValues() );
      std::transform( energies.begin(), energies.end(), values.begin(),
                      values.begin(), std::minus{} );
      auto boundaries = createBoundaries( transfer.boundaries() );
      auto interpolants = createInterpolants( transfer.interpolants() );
      return TabulatedAverageEnergy(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an average reaction product energy table" );
      throw;
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
