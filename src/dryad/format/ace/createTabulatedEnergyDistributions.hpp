#ifndef NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDENERGYDISTRIBUTIONS
#define NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDENERGYDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/ace/createTabulatedEnergyDistributionFunction.hpp"
#include "dryad/format/ace/electroatomic/createPdfFromCdf.hpp"
#include "dryad/TabulatedEnergyDistributions.hpp"
#include "ACEtk/electroatomic/EnergyDistributionBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a TabulatedEnergyDistributions from an ACE energy distribution block
   *
   *  @param[in] distribution   the electroatomic energy distribution block
   */
  TabulatedEnergyDistributions
  createTabulatedEnergyDistributions(
      const njoy::ACEtk::electroatomic::EnergyDistributionBlock& block ) {

    try {

      auto convertEnergy = [] ( auto&& energy ) {

        return energy * 1e+6;
      };

      Log::info( "Reading energy distribution data" );
      auto grid = createVector( block.energies() );
      std::transform( grid.begin(), grid.end(), grid.begin(), convertEnergy );
      std::vector< std::size_t > boundaries = { grid.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      std::vector< TabulatedEnergyDistribution > distributions;
      distributions.reserve( grid.size() );
      for ( auto&& distribution : block.distributions() ) {

        auto cdf = createTabulatedEnergyDistributionFunction( distribution );
        auto pdf = electroatomic::createPdfFromCdf( cdf );
        distributions.emplace_back( std::move( pdf ), std::move( cdf ) );
      }
      return TabulatedEnergyDistributions(
               std::move( grid ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating tabulated angular distributions" );
      throw;
    }
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
