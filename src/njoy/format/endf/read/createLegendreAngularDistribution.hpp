#ifndef NJOY_FORMAT_ENDF_READ_CREATELEGENDREANGULARDISTRIBUTION
#define NJOY_FORMAT_ENDF_READ_CREATELEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/LegendreAngularDistribution.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/6.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a LegendreAngularDistribution from a range of coefficients
   */
  template < typename Range >
  dryad::LegendreAngularDistribution
  createLegendreAngularDistribution( const Range& range, bool addOrderZero,
                                     bool normalise ) {

    try {

      auto coefficients = createVector( range );
      std::size_t index = 0;
      if ( addOrderZero ) {

        coefficients.insert( coefficients.begin(), 0.5 );
        index = 1;
      }
      for ( ; index < coefficients.size(); ++index ) {

        coefficients[index] *= 0.5 * ( 2 * index + 1 );
      }
      return dryad::LegendreAngularDistribution( std::move( coefficients ), normalise );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an energy distribution table" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
