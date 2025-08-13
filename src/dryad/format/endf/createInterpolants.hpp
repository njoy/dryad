#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEINTERPOLANTS
#define NJOY_DRYAD_FORMAT_ENDF_CREATEINTERPOLANTS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "dryad/type-aliases.hpp"
#include "dryad/format/endf/createInterpolant.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Convert a range of ENDF interpolation type
   */
  template < typename Range >
  auto createInterpolants( const Range& interpolants )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< InterpolationType > > {

    std::vector< InterpolationType > converted( interpolants.size() );
    std::transform( interpolants.begin(), interpolants.end(),
                    converted.begin(), &createInterpolant );
    return converted;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
