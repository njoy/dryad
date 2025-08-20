#ifndef NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDANGULARDISTRIBUTIONFUNCTION
#define NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDANGULARDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/TabulatedAngularDistributionFunction.hpp"
#include "ACEtk/electroatomic/TabulatedAngularDistribution.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a TabulatedAngularDistributionFunction from ACE data
   *
   *  @param[in] distribution   the electroatomic tabulated angular distribution
   */
  TabulatedAngularDistributionFunction
  createTabulatedAngularDistributionFunction(
      const njoy::ACEtk::electroatomic::TabulatedAngularDistribution& distribution ) {

    try {

      auto cosines = createVector( distribution.cosines() );
      auto values = createVector( distribution.cdf() );
      std::vector< std::size_t > boundaries = { cosines.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      return TabulatedAngularDistributionFunction(
               std::move( cosines ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an electroatomic tabulated angular "
                 "cumulative distribution function" );
      throw;
    }
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
