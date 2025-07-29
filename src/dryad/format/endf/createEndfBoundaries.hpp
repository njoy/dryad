#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEENDFBOUNDARIES
#define NJOY_DRYAD_FORMAT_ENDF_CREATEENDFBOUNDARIES

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "dryad/format/endf/createEndfIndex.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create boundary indices for ENDF
   */
  template < typename Range >
  auto createEndfBoundaries( const Range& boundaries )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< long > > {

    std::vector< long > converted( boundaries.size() );
    std::transform( boundaries.begin(), boundaries.end(),
                    converted.begin(), &createEndfIndex );
    return converted;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
