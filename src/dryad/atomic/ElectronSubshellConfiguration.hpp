#ifndef NJOY_DRYAD_ATOMIC_ElECTRONSUBSHELLCONFIGURATION
#define NJOY_DRYAD_ATOMIC_ElECTRONSUBSHELLCONFIGURATION

// system includes
#include <vector>

// other includes
#include "dryad/id/ElectronSubshellID.hpp"
#include "dryad/atomic/RadiativeTransitionData.hpp"
#include "dryad/atomic/NonRadiativeTransitionData.hpp"

namespace njoy {
namespace dryad {
namespace atomic {

  /**
   *  @class
   *  @brief Electron subshell configuration information
   *
   *  This class contains the following information for an electron subshell:
   *    - the subshell identifier (K, L1, L2, L3, etc.)
   *    - the subshell binding energy (in eV)
   *    - the electron population, i.e. the number of electrons in the subshell
   *      when the atom is neutral (given as a floating point number)
   *    - the transitions that can fill a vacancy in this shell
   */
  class ElectronSubshellConfiguration {

    /* fields */
    id::ElectronSubshellID id_;

    double binding_energy_;
    double population_;
    std::vector< RadiativeTransitionData > radiative_;
    std::vector< NonRadiativeTransitionData > nonradiative_;

  public:

    /* constructor */

    #include "dryad/atomic/ElectronSubshellConfiguration/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the electron subshell identifier
     */
    const id::ElectronSubshellID& identifier() const noexcept {

      return this->id_;
    }

    /**
     *  @brief Return the subshell binding energy
     */
    double bindingEnergy() const noexcept {

      return this->binding_energy_;
    }

    /**
     *  @brief Return the electron subshell population when the atom is neutral
     */
    double population() const noexcept {

      return this->population_;
    }
  };

} // atomic namespace
} // dryad namespace
} // njoy namespace

#endif
