#ifndef NJOY_FORMAT_ENDF_READ_CREATETABULATEDANGULARDISTRIBUTION
#define NJOY_FORMAT_ENDF_READ_CREATETABULATEDANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedAngularDistribution.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/4.hpp"
#include "ENDFtk/section/6.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a TabulatedAngularDistribution from a parsed ENDF MF4 LTT = 2 or 2,
   *         MF6 or MF26 LAW = 2 TabulatedDistribution
   *
   *  @param[in] distribution   the parsed ENDF tabulated distribution
   *  @param[in] normalise      the flag to indicate whether or not distributions
   *                            need to be normalised
   */
  template < typename TabulatedDistribution >
  auto createTabulatedAngularDistribution( const TabulatedDistribution& distribution,
                                           bool normalise )
  -> std::enable_if_t< ( std::is_same_v< TabulatedDistribution,
                                         ENDFtk::section::Type< 4 >::TabulatedDistribution > ||
                         std::is_same_v< TabulatedDistribution,
                                         ENDFtk::section::Type< 6 >::DiscreteTwoBodyScattering::TabulatedDistribution > ||
                         std::is_same_v< TabulatedDistribution,
                                         ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering::TabulatedDistribution > ),
                       dryad::TabulatedAngularDistribution > {

    try {

      auto cosines = createVector( distribution.cosines() );
      auto values = createVector( distribution.probabilities() );
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return dryad::TabulatedAngularDistribution(
               std::move( cosines ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ),
               normalise );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an angular distribution table" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
