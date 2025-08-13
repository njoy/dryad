#ifndef NJOY_DRYAD_FORMAT_CREATEINDEX
#define NJOY_DRYAD_FORMAT_CREATEINDEX

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {

  /**
   *  @brief Create an index from a one-based index
   */
  std::size_t createIndex( int index ) {

    if ( index < 1 ) {

      Log::error( "This is not a one-based index, found {}", index );
      throw std::exception();
    }
    return static_cast< std::size_t >( index ) - 1;
  }

} // format namespace
} // dryad namespace
} // njoy namespace

#endif
