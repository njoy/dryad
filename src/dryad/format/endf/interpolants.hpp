#ifndef NJOY_DRYAD_FORMAT_ENDF_INTERPOLANTS
#define NJOY_DRYAD_FORMAT_ENDF_INTERPOLANTS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "dryad/type-aliases.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Convert an ENDF interpolation type
   */
  InterpolationType interpolant( int interpolant ) {

    switch ( interpolant ) {

      case 1 : return InterpolationType::Histogram;
      case 2 : return InterpolationType::LinearLinear;
      case 3 : return InterpolationType::LinearLog;
      case 4 : return InterpolationType::LogLinear;
      case 5 : return InterpolationType::LogLog;
      default : {

        Log::error( "Cannot convert or handle ENDF interpolation type {}",
                    interpolant );
        throw std::exception();
      }
    }
  }

  /**
   *  @brief Convert a range of ENDF interpolation type
   */
  template < typename Range >
  auto interpolants( const Range& interpolants )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< InterpolationType > > {

    std::vector< InterpolationType > converted( interpolants.size() );
    std::transform( interpolants.begin(), interpolants.end(),
                    converted.begin(), &interpolant );
    return converted;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
