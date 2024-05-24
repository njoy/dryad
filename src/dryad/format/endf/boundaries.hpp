#ifndef NJOY_DRYAD_FORMAT_ENDF_BOUNDARIES
#define NJOY_DRYAD_FORMAT_ENDF_BOUNDARIES

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Convert an ENDF boundary index to a normal boundary index
   */
  std::size_t boundary( int boundary ) {

    if ( boundary < 1 ) {

      Log::error( "An ENDF boundary index must be equal to or greater than 1, "
                  "found {}", boundary );
      throw std::exception();
    }
    return static_cast< std::size_t >( boundary ) - 1;
  }

  /**
   *  @brief Convert a range of ENDF boundary indices to normal boundary indeces
   */
  template < typename Range >
  auto boundaries( const Range& boundaries )
  -> std::enable_if_t< njoy::tools::std20::ranges::range< Range >,
                       std::vector< std::size_t > > {

    std::vector< std::size_t > converted( boundaries.size() );
    std::transform( boundaries.begin(), boundaries.end(),
                    converted.begin(), &boundary );
    return converted;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
