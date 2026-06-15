#ifndef NJOY_FORMAT_ENDF_WRITE_CREATEINDEX
#define NJOY_FORMAT_ENDF_WRITE_CREATEINDEX

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {

  /**
   *  @brief Create an one-based index from a zero-based index
   */
  inline long createIndex( int index ) {

    if ( index < 0 ) {

      Log::error( "This is not a zero-based index, found {}", index );
      throw std::exception();
    }
    return static_cast< long >( index ) + 1;
  }

} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
