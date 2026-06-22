#ifndef NJOY_FORMAT_ENDF_READ_CREATEMIXEDANGULARDISTRIBUTIONS
#define NJOY_FORMAT_ENDF_READ_CREATEMIXEDANGULARDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "njoy/format/endf/read/createMixedAngularDistribution.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a MixedAngularDistributions instance from a parsed
   *         ENDF MF4 MixedDistributions
   *
   *  @param[in] distribution   the parsed ENDF mixed distributions
   *  @param[in] normalise      the flag to indicate whether or not distributions
   *                            need to be normalised
   */
  inline dryad::MixedAngularDistributions
  createMixedAngularDistributions(
      const ENDFtk::section::Type< 4 >::MixedDistributions& distribution,
      bool normalise ) {

    try {

      auto legendre = distribution.legendre();
      auto tabulated = distribution.tabulated();

      auto energies = createVector( legendre.incidentEnergies() );
      energies.insert( energies.end(), tabulated.incidentEnergies().begin(), tabulated.incidentEnergies().end() );

      std::vector< dryad::MixedAngularDistribution > distributions;
      distributions.reserve( energies.size() );

      for ( auto&& entry : legendre.angularDistributions() ) {

        distributions.emplace_back( createMixedAngularDistribution( entry.coefficients(), true, false ) );
      }
      for ( auto&& entry : tabulated.angularDistributions() ) {

        distributions.emplace_back( createMixedAngularDistribution( entry, normalise ) );
      }

      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return dryad::MixedAngularDistributions(
               std::move( energies ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an mixed angular distributions" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
