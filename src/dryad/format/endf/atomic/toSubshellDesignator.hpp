#ifndef NJOY_DRYAD_FORMAT_ENDF_ATOMIC_CREATEELECTRONSUBSHELLID
#define NJOY_DRYAD_FORMAT_ENDF_ATOMIC_CREATEELECTRONSUBSHELLID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ElectronSubshellID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace atomic {

  /**
   *  @brief Create an ENDF subshell designator
   *
   *  @param[in] subshell   the subshell identifier
   */
  unsigned int toSubshellDesignator( const id::ElectronSubshellID& id ) {

    return id.number() - id::ElectronSubshellID::K + 1;
  }

} // atomic namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
