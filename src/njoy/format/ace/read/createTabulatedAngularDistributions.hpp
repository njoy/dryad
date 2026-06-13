#ifndef NJOY_FORMAT_ACE_READ_CREATETABULATEDANGULARDISTRIBUTIONS
#define NJOY_FORMAT_ACE_READ_CREATETABULATEDANGULARDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedAngularDistributions.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/ace/read/createTabulatedAngularDistributionFunction.hpp"
#include "njoy/format/ace/read/electroatomic/createPdfFromCdf.hpp"
#include "ACEtk/electroatomic/ElasticAngularDistributionBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {

  /**
   *  @brief Create a TabulatedAngularDistributions from an ACE angular distribution block
   *
   *  @param[in] distribution   the electroatomic angular distribution block
   */
  inline dryad::TabulatedAngularDistributions
  createTabulatedAngularDistributions(
      const njoy::ACEtk::electroatomic::ElasticAngularDistributionBlock& block ) {

    try {

      auto convertEnergy = [] ( auto&& energy ) {

        return energy * 1e+6;
      };

      Log::info( "Reading elastic scattering data" );
      auto grid = createVector( block.energies() );
      std::transform( grid.begin(), grid.end(), grid.begin(), convertEnergy );
      std::vector< std::size_t > boundaries = { grid.size() - 1 };
      std::vector< dryad::InterpolationType > interpolants = { dryad::InterpolationType::LinearLinear };
      std::vector< dryad::TabulatedAngularDistribution > distributions;
      distributions.reserve( grid.size() );
      for ( auto&& distribution : block.distributions() ) {

        auto cdf = createTabulatedAngularDistributionFunction( distribution );
        auto pdf = electroatomic::createPdfFromCdf( cdf );
        distributions.emplace_back( std::move( pdf ), std::move( cdf ) );
      }
      return dryad::TabulatedAngularDistributions(
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
