#ifndef NJOY_DRYAD_FORMAT_CREATEVECTOR
#define NJOY_DRYAD_FORMAT_CREATEVECTOR

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"

namespace njoy {
namespace dryad {
namespace format {

  /**
   *  @brief Create a vector from a range
   *
   *  The range only need a begin and end iterator associated to it, The vector
   *  that will be produced will use the underlying value type so no conversion
   *  or casting will occur.
   */
  template < typename Range >
  auto createVector( Range&& data )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< njoy::tools::std20::ranges::range_value_t< Range > > > {

    return { data.begin(), data.end() };
  }

} // format namespace
} // dryad namespace
} // njoy namespace

#endif
