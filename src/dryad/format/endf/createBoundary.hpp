#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEBOUNDARY
#define NJOY_DRYAD_FORMAT_ENDF_CREATEBOUNDARY

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
   *  @brief Create a boundary index from an ENDF boundary index
   */
  std::size_t createBoundary( int boundary ) {

    if ( boundary < 1 ) {

      Log::error( "An ENDF boundary index must be equal to or greater than 1, "
                  "found {}", boundary );
      throw std::exception();
    }
    return static_cast< std::size_t >( boundary ) - 1;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
