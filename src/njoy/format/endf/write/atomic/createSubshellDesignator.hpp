#ifndef NJOY_FORMAT_ENDF_WRITE_ATOMIC_CREATESUBSHELLDESIGNATOR
#define NJOY_FORMAT_ENDF_WRITE_ATOMIC_CREATESUBSHELLDESIGNATOR

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ElectronSubshellID.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {
namespace atomic {

  /**
   *  @brief Create an ENDF subshell designator
   *
   *  @param[in] id   the subshell identifier
   */
  inline unsigned int createSubshellDesignator( const dryad::id::ElectronSubshellID& id ) {

    return id.mt().value() - dryad::id::ElectronSubshellID::K + 1;
  }

} // atomic namespace
} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
