#ifndef NJOY_FORMAT_ENDF_WRITE_CREATEINTERPOLANTS
#define NJOY_FORMAT_ENDF_WRITE_CREATEINTERPOLANTS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/format/endf/write/createInterpolant.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {

  /**
   *  @brief Convert a range of interpolation types for ENDF
   */
  template < typename Range >
  auto createInterpolants( const Range& interpolants )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< long > > {

    std::vector< long > converted( interpolants.size() );
    std::transform( interpolants.begin(), interpolants.end(),
                    converted.begin(), &createInterpolant );
    return converted;
  }

} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
