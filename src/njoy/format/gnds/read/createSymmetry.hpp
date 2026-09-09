#ifndef NJOY_FORMAT_GNDS_READ_CREATESYMMETRY
#define NJOY_FORMAT_GNDS_READ_CREATESYMMETRY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  enum class Symmetry : short {

    None,
    Lower,
    Upper
  };

  /**
   *  @brief Create the symmetry type from a GNDS string
   *
   *  @param[in] symmetry   the symmetry type string
   */
  inline Symmetry createSymmetry( const std::string& symmetry ) {

    if ( symmetry == "none" ) {

      return Symmetry::None;
    }
    else if ( symmetry == "upper" ) {

      return Symmetry::Upper;
    }
    else if ( symmetry == "lower" ) {

      return Symmetry::Lower;
    }
    else {

      Log::error( "GNDS symmetry type \'{}\' is not recognised", symmetry );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
