#ifndef NJOY_FORMAT_ENDF_READ_CREATELEGENDREANGULARDISTRIBUTION
#define NJOY_FORMAT_ENDF_READ_CREATELEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/LegendreAngularDistribution.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/convertLegendreMoments.hpp"
#include "ENDFtk/section/4.hpp"
#include "ENDFtk/section/6.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a LegendreAngularDistribution from MF4 or MF6 Legendre moments
   *
   *  @param[in] distribution   the parsed MF4 or an MF6 Legendre distribution
   *  @param[in] normalise      the flag to indicate whether or not distributions
   *                            need to be normalised
   */
  template < typename LegendreCoefficients >
  auto createLegendreAngularDistribution( const LegendreCoefficients& distribution,
                                          bool normalise )
  -> std::enable_if_t< ( std::is_same_v< LegendreCoefficients,
                                         ENDFtk::section::Type< 4 >::LegendreCoefficients > ||
                         std::is_same_v< LegendreCoefficients,
                                         ENDFtk::section::Type< 6 >::DiscreteTwoBodyScattering::LegendreCoefficients > ),
                       dryad::LegendreAngularDistribution > {

    try {

      auto coefficients = createVector( distribution.coefficients() );
      coefficients.insert( coefficients.begin(), 1. );
      convertLegendreMoments( coefficients );

      return dryad::LegendreAngularDistribution( std::move( coefficients ), normalise );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a Legendre angular distribution" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
