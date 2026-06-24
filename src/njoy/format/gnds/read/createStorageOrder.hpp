#ifndef NJOY_FORMAT_GNDS_READ_CREATESTORAGEORDER
#define NJOY_FORMAT_GNDS_READ_CREATESTORAGEORDER

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

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

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
