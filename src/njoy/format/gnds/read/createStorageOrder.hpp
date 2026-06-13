#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATESTORAGEORDER
#define NJOY_DRYAD_FORMAT_GNDS_CREATESTORAGEORDER

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  enum class StorageOrder : short {

    RowMajor,
    ColumnMajor
  };

  /**
   *  @brief Create the storage order from a GNDS string
   */
  inline StorageOrder createStorageOrder( const std::string& order ) {

    if ( order == "row-major" ) {

      return StorageOrder::RowMajor;
    }
    else if ( order == "column-major" ) {

      return StorageOrder::ColumnMajor;
    }
    else {

      Log::error( "GNDS storage frame \'{}\' is not recognised", order );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
