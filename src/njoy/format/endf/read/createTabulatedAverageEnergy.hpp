#ifndef NJOY_FORMAT_ENDF_READ_CREATETABULATEDAVERAGEENERGY
#define NJOY_FORMAT_ENDF_READ_CREATETABULATEDAVERAGEENERGY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/TabulatedAverageEnergy.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a TabulatedAverageEnergy from a parsed ENDF MF26
   *         energy transfer component
   *
   *  @param[in] transfer   the parsed ENDF energy transfer data
   */
  inline dryad::TabulatedAverageEnergy
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
      return dryad::TabulatedAverageEnergy(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an average reaction product energy table" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
