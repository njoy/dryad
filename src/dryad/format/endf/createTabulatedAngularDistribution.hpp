#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDANGULARDISTRIBUTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/TabulatedAngularDistribution.hpp"
#include "ENDFtk/section/6.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedAngularDistribution from a parsed ENDF MF6 or MF26 LAW = 2
   *         TabulatedDistribution
   */
  template < typename TabulatedDistribution >
  auto createTabulatedAngularDistribution( const TabulatedDistribution& distribution )
  -> std::enable_if_t< ( std::is_same_v< TabulatedDistribution,
                                         ENDFtk::section::Type< 6 >::DiscreteTwoBodyScattering::TabulatedDistribution > ||
                         std::is_same_v< TabulatedDistribution,
                                         ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering::TabulatedDistribution > ),
                       TabulatedAngularDistribution > {

    try {

      auto cosines = createVector( distribution.cosines() );
      auto values = createVector( distribution.probabilities() );
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return TabulatedAngularDistribution(
               std::move( cosines ), std::move( values ),
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
