#ifndef NJOY_FORMAT_GENDF_READ_CREATEMULTIPLICITY
#define NJOY_FORMAT_GENDF_READ_CREATEMULTIPLICITY

// system includes
#include <variant>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/MultigroupMultiplicity.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {

  /**
   *  @brief Create an integer multiplicity
   *
   *  @param[in] multiplicity   the integer multiplicity
   */
  inline std::variant< int, dryad::MultigroupMultiplicity >
  createMultiplicity( int multiplicity ) {

    return multiplicity;
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
