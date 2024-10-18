#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDENERGYDISTRIBUTIONS
#define NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDENERGYDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/format/endf/createTabulatedEnergyDistribution.hpp"
#include "dryad/TabulatedEnergyDistributions.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedEnergyDistributions instance from a parsed
   *         ENDF MF6 ContinuumEnergyAngle component
   */
  TabulatedEnergyDistributions
  createTabulatedEnergyDistributions( const ENDFtk::section::Type< 26 >::ContinuumEnergyAngle& distribution ) {

    try {

      auto energies = createVector( distribution.incidentEnergies() );
      std::vector< TabulatedEnergyDistribution > distributions;
      distributions.reserve( energies.size() );
      for ( auto&& table : distribution.distributions() ) {

        distributions.emplace_back( createTabulatedEnergyDistribution( table ) );
      }
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return TabulatedEnergyDistributions(
               std::move( energies ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a reaction product energy distribution" );
      throw;
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
