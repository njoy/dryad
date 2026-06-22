#ifndef NJOY_FORMAT_ENDF_READ_CREATELEGENDREANGULARDISTRIBUTION
#define NJOY_FORMAT_ENDF_READ_CREATELEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/LegendreAngularDistribution.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/convertLegendreMoments.hpp"
#include "ENDFtk/section/6.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a LegendreAngularDistribution from a range of moments
   */
  template < typename Range >
  dryad::LegendreAngularDistribution
  createLegendreAngularDistribution( const Range& range, bool addOrderZero,
                                     bool normalise ) {

    try {

      auto coefficients = createVector( range );
      if ( addOrderZero ) {

        coefficients.insert( coefficients.begin(), 1. );
      }
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
