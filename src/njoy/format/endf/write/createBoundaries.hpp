#ifndef NJOY_FORMAT_ENDF_WRITE_CREATEBOUNDARIES
#define NJOY_FORMAT_ENDF_WRITE_CREATEBOUNDARIES

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "njoy/format/endf/write/createIndex.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {

  /**
   *  @brief Create boundary indices for ENDF
   *
   *  @param[in] boundaries   the zero-based boundary index values
   */
  template < typename Range >
  auto createBoundaries( const Range& boundaries )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< long > > {

    std::vector< long > converted( boundaries.size() );
    std::transform( boundaries.begin(), boundaries.end(),
                    converted.begin(), &createIndex );
    return converted;
  }

} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
