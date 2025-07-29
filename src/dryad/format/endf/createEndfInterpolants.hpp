#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEENDFINTERPOLANTS
#define NJOY_DRYAD_FORMAT_ENDF_CREATEENDFINTERPOLANTS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "dryad/type-aliases.hpp"
#include "dryad/format/endf/createEndfInterpolant.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Convert a range of interpolation types for ENDF
   */
  template < typename Range >
  auto createEndfInterpolants( const Range& interpolants )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< std::size_t > > {

    std::vector< std::size_t > converted( interpolants.size() );
    std::transform( interpolants.begin(), interpolants.end(),
                    converted.begin(), &createEndfInterpolant );
    return converted;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
