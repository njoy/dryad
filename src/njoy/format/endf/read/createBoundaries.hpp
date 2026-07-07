#ifndef NJOY_FORMAT_ENDF_READ_CREATEBOUNDARIES
#define NJOY_FORMAT_ENDF_READ_CREATEBOUNDARIES

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "njoy/format/createIndex.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create boundary indices from ENDF boundary indices
   *
   *  @param[in] boundaries    the one-based boundary index values
   */
  template < typename Range >
  auto createBoundaries( const Range& boundaries )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< std::size_t > > {

    std::vector< std::size_t > converted( boundaries.size() );
    std::transform( boundaries.begin(), boundaries.end(),
                    converted.begin(), &createIndex );
    return converted;
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
