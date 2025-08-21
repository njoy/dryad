#ifndef NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDENERGYDISTRIBUTIONFUNCTION
#define NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDENERGYDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/TabulatedEnergyDistributionFunction.hpp"
#include "ACEtk/electroatomic/TabulatedEnergyDistribution.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a TabulatedEnergyDistributionFunction from ACE data
   *
   *  @param[in] distribution   the electroatomic tabulated energy distribution
   */
  TabulatedEnergyDistributionFunction
  createTabulatedEnergyDistributionFunction(
      const njoy::ACEtk::electroatomic::TabulatedEnergyDistribution& distribution ) {

    try {

      auto convertEnergy = [] ( auto&& energy ) {

        return energy * 1e+6;
      };

      auto energies = createVector( distribution.outgoingEnergies() );
      std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );
      auto values = createVector( distribution.cdf() );
      std::vector< std::size_t > boundaries = { energies.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      return TabulatedEnergyDistributionFunction(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an electroatomic tabulated energy "
                 "cumulative distribution function" );
      throw;
    }
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
