#ifndef NJOY_FORMAT_ACE_READ_CREATETABULATEDANGULARDISTRIBUTIONFUNCTION
#define NJOY_FORMAT_ACE_READ_CREATETABULATEDANGULARDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"
#include "njoy/format/createVector.hpp"
#include "ACEtk/electroatomic/TabulatedAngularDistribution.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {

  /**
   *  @brief Create a TabulatedAngularDistributionFunction from ACE data
   *
   *  @param[in] distribution   the electroatomic tabulated angular distribution
   */
  inline dryad::TabulatedAngularDistributionFunction
  createTabulatedAngularDistributionFunction(
      const njoy::ACEtk::electroatomic::TabulatedAngularDistribution& distribution ) {

    try {

      auto cosines = createVector( distribution.cosines() );
      auto values = createVector( distribution.cdf() );
      std::vector< std::size_t > boundaries = { cosines.size() - 1 };
      std::vector< dryad::InterpolationType > interpolants = { dryad::InterpolationType::LinearLinear };
      return dryad::TabulatedAngularDistributionFunction(
               std::move( cosines ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an electroatomic tabulated angular "
                 "cumulative distribution function" );
      throw;
    }
  }

} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
