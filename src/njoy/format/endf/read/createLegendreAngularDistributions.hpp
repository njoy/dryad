#ifndef NJOY_FORMAT_ENDF_READ_CREATELEGENDREANGULARDISTRIBUTIONS
#define NJOY_FORMAT_ENDF_READ_CREATELEGENDREANGULARDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/LegendreAngularDistributions.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "njoy/format/endf/read/createLegendreAngularDistribution.hpp"
#include "ENDFtk/section/4.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a LegendreAngularDistributions instance from a parsed
   *         ENDF MF4 section
   */
  inline dryad::LegendreAngularDistributions
  createLegendreAngularDistributions(
      const ENDFtk::section::Type< 4 >::LegendreDistributions& distribution,
      bool ) {

    // MF4 sections assume that the first coefficient is 0.5 so it is always normalised.
    // As such, we can read the distributions with normalise = false directly.

    try {

      auto energies = createVector( distribution.incidentEnergies() );
      std::vector< dryad::LegendreAngularDistribution > distributions;
      distributions.reserve( energies.size() );
      for ( auto&& entry : distribution.angularDistributions() ) {

        distributions.emplace_back( createLegendreAngularDistribution( entry, false ) );
      }
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return dryad::LegendreAngularDistributions(
               std::move( energies ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a Legendre angular distribution table" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
