#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDANGULARDISTRIBUTIONS
#define NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDANGULARDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/createBoundaries.hpp"
#include "njoy/dryad/format/endf/createInterpolants.hpp"
#include "njoy/dryad/format/endf/createTabulatedAngularDistribution.hpp"
#include "njoy/dryad/TabulatedAngularDistributions.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedAngularDistributions instance from a parsed
   *         ENDF MF4 TabulatedDistributions or MF6 DiscreteTwoBodyScattering component
   */
  template < typename TabulatedDistributions >
  auto createTabulatedAngularDistributions( const TabulatedDistributions& distribution,
                                            bool normalise )
  -> std::enable_if_t< ( std::is_same_v< TabulatedDistributions,
                                         ENDFtk::section::Type< 4 >::TabulatedDistributions > ||
                         std::is_same_v< TabulatedDistributions,
                                         ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering > ),
                       TabulatedAngularDistributions >{

    try {

      auto energies = createVector( distribution.incidentEnergies() );
      std::vector< TabulatedAngularDistribution > distributions;
      distributions.reserve( energies.size() );
      for ( auto&& table : distribution.distributions() ) {

        distributions.emplace_back( createTabulatedAngularDistribution( table, normalise ) );
      }
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return TabulatedAngularDistributions(
               std::move( energies ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an average reaction product energy table" );
      throw;
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
