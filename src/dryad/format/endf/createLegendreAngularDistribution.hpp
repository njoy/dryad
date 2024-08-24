#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATELEGENDREANGULARDISTRIBUTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATELEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/LegendreAngularDistribution.hpp"
#include "ENDFtk/section/6.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a LegendreAngularDistribution from a range of coefficients
   */
  template < typename Range >
  LegendreAngularDistribution createLegendreAngularDistribution( const Range& range, bool addOrderZero ) {

    try {

      auto coefficients = createVector( range );
      if ( addOrderZero ) { coefficients.insert( coefficients.begin(), 1. ); }
      for ( std::size_t index = 0; index < coefficients.size(); ++index ) {

        coefficients[index] *= 0.5 * ( 2 * index + 1 );
      }
      return LegendreAngularDistribution( std::move( coefficients ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an energy distribution table" );
      throw;
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
