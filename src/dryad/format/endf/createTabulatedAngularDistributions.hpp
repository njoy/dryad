#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDANGULARDISTRIBUTIONS
#define NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDANGULARDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/format/endf/createTabulatedAngularDistribution.hpp"
#include "dryad/TabulatedAngularDistributions.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedAngularDistributions instance from a parsed
   *         ENDF MF6 DiscreteTwoBodyScattering component
   */
  TabulatedAngularDistributions
  createTabulatedAngularDistributions(
      const ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering& distribution,
      bool normalise ) {

    try {

      auto energies = createVector( distribution.incidentEnergies() );
      std::vector< TabulatedAngularDistribution > distributions;
      distributions.reserve( energies.size() );
      for ( auto&& table : distribution.distributions() ) {

        distributions.emplace_back( createTabulatedAngularDistribution( table, normalise ) );
      }
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return TabulatedAngularDistributions(
               std::move( energies ), std::move( distributions ),
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
