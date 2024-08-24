#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATELEGENDREANGULARDISTRIBUTIONS
#define NJOY_DRYAD_FORMAT_ENDF_CREATELEGENDREANGULARDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/format/endf/createLegendreAngularDistribution.hpp"
#include "dryad/LegendreAngularDistributions.hpp"
#include "ENDFtk/section/4.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a LegendreAngularDistributions instance from a parsed
   *         ENDF MF4 section
   */
  LegendreAngularDistributions
  createLegendreAngularDistributions(
      const ENDFtk::section::Type< 4 >::LegendreDistributions& distribution ) {

    try {

      auto energies = createVector( distribution.incidentEnergies() );
      std::vector< LegendreAngularDistribution > distributions;
      distributions.reserve( energies.size() );
      for ( auto&& entry : distribution.angularDistributions() ) {

        distributions.emplace_back( createLegendreAngularDistribution( entry.coefficients(), true ) );
      }
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return LegendreAngularDistributions(
               std::move( energies ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a Legendre angular distribution table" );
      throw;
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
