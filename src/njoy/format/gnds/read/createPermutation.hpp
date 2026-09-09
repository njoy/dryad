#ifndef NJOY_FORMAT_GNDS_READ_CREATEPERMUTATION
#define NJOY_FORMAT_GNDS_READ_CREATEPERMUTATION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  enum class Permutation : short {

    None,
    Symmetric,
    AntiSymmetric
  };

  /**
   *  @brief Create the symmetry type from a GNDS string
   *
   *  @param[in] symmetry   the symmetry type string
   */
  inline Permutation createPermutation( const std::string& symmetry ) {

    if ( symmetry == "none" ) {

      return Permutation::None;
    }
    else if ( symmetry == "+1" ) {

      return Permutation::Symmetric;
    }
    else if ( symmetry == "-1" ) {

      return Permutation::AntiSymmetric;
    }
    else {

      Log::error( "GNDS permutation type \'{}\' is not recognised", symmetry );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
