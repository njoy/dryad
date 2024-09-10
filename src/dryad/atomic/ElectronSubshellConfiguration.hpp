#ifndef NJOY_DRYAD_ATOMIC_ElECTRONSUBSHELLCONFIGURATION
#define NJOY_DRYAD_ATOMIC_ElECTRONSUBSHELLCONFIGURATION

// system includes
#include <vector>
#include <numeric>

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

    double radiative_probability_;
    double nonradiative_probability_;

    /* auxiliary functions */

    #include "dryad/atomic/ElectronSubshellConfiguration/src/calculateProbabilities.hpp"

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

    /**
     *  @brief Return the number of available radiative transitions
     */
    std::size_t numberRadiativeTransitions() const noexcept {

      return this->radiative_.size();
    }

    /**
     *  @brief Return the number of available non-radiative transitions
     */
    std::size_t numberNonRadiativeTransitions() const noexcept {

      return this->nonradiative_.size();
    }

    /**
     *  @brief Return the number of available transitions
     */
    std::size_t numberTransitions() const noexcept {

      return this->numberRadiativeTransitions() + this->numberNonRadiativeTransitions();
    }

    /**
     *  @brief Return whether or not radiative transitions are available
     */
    bool hasRadiativeTransitions() const noexcept {

      return this->numberRadiativeTransitions() > 0;
    }

    /**
     *  @brief Return whether or not non-radiative transitions are available
     */
    bool hasNonRadiativeTransitions() const noexcept {

      return this->numberNonRadiativeTransitions() > 0;
    }

    /**
     *  @brief Return whether or not any transitions are available
     */
    bool hasTransitions() const noexcept {

      return this->hasRadiativeTransitions() || this->hasNonRadiativeTransitions();
    }

    /**
     *  @brief Return the data for all available radiative transitions to this subshell
     */
    const std::vector< RadiativeTransitionData >& radiativeTransitions() const noexcept {

      return this->radiative_;
    }

    /**
     *  @brief Return the data for all available non-radiative transitions to this subshell
     */
    const std::vector< NonRadiativeTransitionData >& nonRadiativeTransitions() const noexcept {

      return this->nonradiative_;
    }

    /**
     *  @brief Return the total radiative probability
     */
    double totalRadiativeProbability() const noexcept {

      return this->radiative_probability_;
    }

    /**
     *  @brief Return the total non-radiative probability
     */
    double totalNonRadiativeProbability() const noexcept {

      return this->nonradiative_probability_;
    }
  };

} // atomic namespace
} // dryad namespace
} // njoy namespace

#endif
