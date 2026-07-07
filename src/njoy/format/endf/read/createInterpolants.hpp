#ifndef NJOY_FORMAT_ENDF_READ_CREATEINTERPOLANTS
#define NJOY_FORMAT_ENDF_READ_CREATEINTERPOLANTS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/format/endf/read/createInterpolant.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Convert a range of ENDF interpolation type
   *
   *  @param[in] interpolant    the ENDF interpolation values
   */
  template < typename Range >
  auto createInterpolants( const Range& interpolants )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< dryad::InterpolationType > > {

    std::vector< dryad::InterpolationType > converted( interpolants.size() );
    std::transform( interpolants.begin(), interpolants.end(),
                    converted.begin(), &createInterpolant );
    return converted;
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
