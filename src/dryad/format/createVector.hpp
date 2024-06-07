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
   *  @brief Create an index from a one-based index
   */
  template < typename T, typename Range >
  auto createVector( Range&& data )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >, std::vector< T > > {

    return { data.begin(), data.end() };
  }

} // format namespace
} // dryad namespace
} // njoy namespace

#endif
