#ifndef NJOY_FORMAT_ACE_READ_CREATETABULATEDENERGYDISTRIBUTIONS
#define NJOY_FORMAT_ACE_READ_CREATETABULATEDENERGYDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedEnergyDistributions.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/ace/read/createTabulatedEnergyDistributionFunction.hpp"
#include "njoy/format/ace/read/electroatomic/createPdfFromCdf.hpp"
#include "ACEtk/electroatomic/EnergyDistributionBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {

  /**
   *  @brief Create a TabulatedEnergyDistributions from an ACE energy distribution block
   *
   *  @param[in] distribution   the electroatomic energy distribution block
   */
  inline dryad::TabulatedEnergyDistributions
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
      std::vector< dryad::InterpolationType > interpolants = { dryad::InterpolationType::LinearLinear };
      std::vector< dryad::TabulatedEnergyDistribution > distributions;
      distributions.reserve( grid.size() );
      for ( auto&& distribution : block.distributions() ) {

        auto cdf = createTabulatedEnergyDistributionFunction( distribution );
        auto pdf = electroatomic::createPdfFromCdf( cdf );
        distributions.emplace_back( std::move( pdf ), std::move( cdf ) );
      }
      return dryad::TabulatedEnergyDistributions(
               std::move( grid ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating tabulated angular distributions" );
      throw;
    }
  }

} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
