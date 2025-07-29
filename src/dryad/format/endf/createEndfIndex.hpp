#ifndef NJOY_DRYAD_FORMAT_CREATEENDFINDEX
#define NJOY_DRYAD_FORMAT_CREATEENDFINDEX

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {

  /**
   *  @brief Create an one-based index from a zero-based index
   */
  long createEndfIndex( int index ) {

    if ( index < 0 ) {

      Log::error( "This is not a zero-based index, found {}", index );
      throw std::exception();
    }
    return static_cast< long >( index ) + 1;
  }

} // format namespace
} // dryad namespace
} // njoy namespace

#endif
