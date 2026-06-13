#ifndef NJOY_FORMAT_ENDF_READ_CREATETABULATEDENERGYDISTRIBUTIONS
#define NJOY_FORMAT_ENDF_READ_CREATETABULATEDENERGYDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/TabulatedEnergyDistributions.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "njoy/format/endf/read/createTabulatedEnergyDistribution.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a TabulatedEnergyDistributions instance from a parsed
   *         ENDF MF26 ContinuumEnergyAngle component
   */
  inline dryad::TabulatedEnergyDistributions
  createTabulatedEnergyDistributions(
      const ENDFtk::section::Type< 26 >::ContinuumEnergyAngle& distribution,
      bool normalise ) {

    try {

      auto energies = createVector( distribution.incidentEnergies() );
      auto interpolant = createInterpolant( distribution.interpolationScheme() );
      std::vector< dryad::TabulatedEnergyDistribution > distributions;
      distributions.reserve( energies.size() );
      for ( auto&& table : distribution.distributions() ) {

        distributions.emplace_back( createTabulatedEnergyDistribution( table, interpolant, normalise ) );
      }
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return dryad::TabulatedEnergyDistributions(
               std::move( energies ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a reaction product energy distribution" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
