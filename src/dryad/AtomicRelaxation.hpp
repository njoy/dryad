#ifndef NJOY_DRYAD_ATOMICRELAXATION
#define NJOY_DRYAD_ATOMICRELAXATION

// system includes
#include <vector>

// other includes
#include "dryad/id/ElementID.hpp"
#include "dryad/atomic/ElectronSubshellConfiguration.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Atomic relaxation data for a given element
   */
  class AtomicRelaxation {

    /* fields */
    id::ElementID element_id_;

    std::vector< atomic::ElectronSubshellConfiguration > subshells_;

  public:

    /* constructor */

    #include "dryad/AtomicRelaxation/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the element identifier
     */
    const id::ElementID& elementIdentifier() const noexcept {

      return this->element_id_;
    }

    /**
     *  @brief Return the electron shell configuration data
     */
    const std::vector< atomic::ElectronSubshellConfiguration >&
    subshells() const noexcept {

      return this->subshells_;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
