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

  /**
   *  @brief Create an index from a one-based index
   */
  std::size_t createIndex( int boundary ) {

    if ( boundary < 1 ) {

      Log::error( "This is not a one-based index, found {}", boundary );
      throw std::exception();
    }
    return static_cast< std::size_t >( boundary ) - 1;
  }

} // format namespace
} // dryad namespace
} // njoy namespace

#endif
