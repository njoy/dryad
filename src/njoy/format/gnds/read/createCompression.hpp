#ifndef NJOY_FORMAT_GNDS_READ_CREATECOMPRESSION
#define NJOY_FORMAT_GNDS_READ_CREATECOMPRESSION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  enum class Compression : short {

    None,
    Diagonal,
    Flattened,
    Embedded
  };

  /**
   *  @brief Create the compression from a GNDS string
   *
   *  @param[in] compression   the compression string
   */
  inline Compression createCompression( const std::string& compression ) {

    if ( compression == "none" ) {

      return Compression::None;
    }
    else if ( compression == "diagonal" ) {

      return Compression::Diagonal;
    }
    else if ( compression == "flattened" ) {

      return Compression::Flattened;
    }
    else if ( compression == "embedded" ) {

      return Compression::Embedded;
    }
    else {

      Log::error( "GNDS storage type \'{}\' is not recognised", compression );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
