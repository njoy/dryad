#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEBOUNDARIES
#define NJOY_DRYAD_FORMAT_ENDF_CREATEBOUNDARIES

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "dryad/format/endf/createBoundary.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Convert a range of ENDF boundary indices to normal boundary indeces
   */
  template < typename Range >
  auto createBoundaries( const Range& boundaries )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< std::size_t > > {

    std::vector< std::size_t > converted( boundaries.size() );
    std::transform( boundaries.begin(), boundaries.end(),
                    converted.begin(), &createBoundary );
    return converted;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
