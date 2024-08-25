#ifndef NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDANGULARDISTRIBUTIONS
#define NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDANGULARDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/ace/createTabulatedAngularDistributionFunction.hpp"
#include "dryad/format/ace/electroatomic/createPdfFromCdf.hpp"
#include "dryad/TabulatedAngularDistributions.hpp"
#include "ACEtk/electron/ElasticAngularDistributionBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a TabulatedAngularDistributions from an ElasticAngularDistributionBlock
   */
  TabulatedAngularDistributions
  createTabulatedAngularDistributions( const njoy::ACEtk::electron::ElasticAngularDistributionBlock& block ) {

    try {

      Log::info( "Reading elastic scattering data" );
      auto grid = createVector( block.energies() );
      std::vector< std::size_t > boundaries = { grid.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      std::vector< TabulatedAngularDistribution > distributions;
      distributions.reserve( grid.size() );
      for ( auto&& distribution : block.distributions() ) {

        auto cdf = createTabulatedAngularDistributionFunction( distribution );
        auto pdf = electroatomic::createPdfFromCdf( cdf );
        distributions.emplace_back( std::move( pdf ), std::move( cdf ) );
      }
      return TabulatedAngularDistributions(
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
