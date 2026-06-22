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

      auto energies = createVector( distribution.incidentEnergies() );
      std::vector< dryad::MixedAngularDistribution > distributions;
      distributions.reserve( energies.size() );

      using LegendreCoefficients = std::reference_wrapper< const ENDFtk::section::Type< 4 >::LegendreCoefficients >;
      using TabulatedDistribution = std::reference_wrapper< const ENDFtk::section::Type< 4 >::TabulatedDistribution >;
      auto create = tools::overload{

        [&] ( const LegendreCoefficients& distribution ) -> dryad::MixedAngularDistribution {

          return createMixedAngularDistribution( distribution, normalise );
        },
        [&] ( const TabulatedDistribution& distribution ) -> dryad::MixedAngularDistribution {

          return createMixedAngularDistribution( distribution, normalise );
        }
      };

      for ( auto&& entry : distribution.angularDistributions() ) {

        distributions.emplace_back( std::visit( create, entry ) );
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
