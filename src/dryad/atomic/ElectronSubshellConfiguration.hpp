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
   *
   *  If there are transitions defined, the transition probabilities are
   *  can be normalised to 1 upon construction.
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
     *  @brief Set the subshell binding energy
     *
     *  @param[in] energy   the subshell binding energy
     */
    void bindingEnergy( double energy ) noexcept {

      this->binding_energy_ = energy;
    }

    /**
     *  @brief Return the electron subshell population when the atom is neutral
     */
    double population() const noexcept {

      return this->population_;
    }

    /**
     *  @brief Set the electron subshell population
     *
     *  @param[in] population   the electron subshell population
     */
    void population( double population ) noexcept {

      this->population_ = population;
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
     *  @brief Return the available radiative transitions to this subshell
     */
    const std::vector< RadiativeTransitionData >& radiativeTransitions() const noexcept {

      return this->radiative_;
    }

    /**
     *  @brief Set the available radiative transitions to this subshell
     *
     *  @param[in] radiative   the available radiative transitions to this subshell
     */
    void radiativeTransitions( std::vector< RadiativeTransitionData > radiative ) noexcept {

      this->radiative_ = std::move( radiative );
      this->calculateTotalRadiativeProbability();
    }

    /**
     *  @brief Return the available non-radiative transitions to this subshell
     */
    const std::vector< NonRadiativeTransitionData >& nonRadiativeTransitions() const noexcept {

      return this->nonradiative_;
    }

    /**
     *  @brief Set the available non-radiative transitions to this subshell
     *
     *  @param[in] radiative   the available non-radiative transitions to this subshell
     */
    void nonRadiativeTransitions( std::vector< NonRadiativeTransitionData > nonradiative ) noexcept {

      this->nonradiative_ = std::move( nonradiative );
      this->calculateTotalNonRadiativeProbability();
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

    /**
     *  @brief Normalise the transition probabilities
     */
    void normalise() noexcept {

      if ( this->hasTransitions() ) {

        double total = this->totalRadiativeProbability() + this->totalNonRadiativeProbability();
        for ( RadiativeTransitionData& transition : this->radiative_ ) {

          transition.probability( transition.probability() / total );
        }
        for ( NonRadiativeTransitionData& transition : this->nonradiative_ ) {

          transition.probability( transition.probability() / total );
        }
        this->radiative_probability_ /= total;
        this->nonradiative_probability_ /= total;
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ElectronSubshellConfiguration& right ) const noexcept {

      return this->identifier() == right.identifier() &&
             this->bindingEnergy() == right.bindingEnergy() &&
             this->population() == right.population() &&
             this->totalRadiativeProbability() == right.totalRadiativeProbability() &&
             this->totalNonRadiativeProbability() == right.totalNonRadiativeProbability() &&
             this->radiativeTransitions() == right.radiativeTransitions() &&
             this->nonRadiativeTransitions() == right.nonRadiativeTransitions();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ElectronSubshellConfiguration& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // atomic namespace
} // dryad namespace
} // njoy namespace

#endif
