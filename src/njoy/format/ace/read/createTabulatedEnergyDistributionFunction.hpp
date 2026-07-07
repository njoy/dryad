#ifndef NJOY_FORMAT_ACE_READ_CREATETABULATEDENERGYDISTRIBUTIONFUNCTION
#define NJOY_FORMAT_ACE_READ_CREATETABULATEDENERGYDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/TabulatedEnergyDistributionFunction.hpp"
#include "njoy/format/createVector.hpp"
#include "ACEtk/electroatomic/TabulatedEnergyDistribution.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {

  /**
   *  @brief Create a TabulatedEnergyDistributionFunction from ACE data
   *
   *  @param[in] distribution   the electroatomic tabulated energy distribution
   */
  inline dryad::TabulatedEnergyDistributionFunction
  createTabulatedEnergyDistributionFunction(
      const njoy::ACEtk::electroatomic::TabulatedEnergyDistribution& distribution ) {

    try {

      auto convertEnergy = [] ( auto&& energy ) {

        return energy * constants::mega;
      };

      auto energies = createVector( distribution.outgoingEnergies() );
      std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );
      auto values = createVector( distribution.cdf() );
      std::vector< std::size_t > boundaries = { energies.size() - 1 };
      std::vector< dryad::InterpolationType > interpolants = { dryad::InterpolationType::LinearLinear };
      return dryad::TabulatedEnergyDistributionFunction(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an electroatomic tabulated energy "
                 "cumulative distribution function" );
      throw;
    }
  }

} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
