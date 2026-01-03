#ifndef NJOY_DRYAD_ATOMIC_ElECTRONSUBSHELLCONFIGURATION
#define NJOY_DRYAD_ATOMIC_ElECTRONSUBSHELLCONFIGURATION

// system includes
#include <vector>
#include <numeric>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ElectronSubshellID.hpp"
#include "njoy/dryad/atomic/RadiativeTransitionData.hpp"
#include "njoy/dryad/atomic/NonRadiativeTransitionData.hpp"

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
   *  If there are transitions defined, the transition probabilities can be
   *  normalised to 1 upon construction. Transitions are always sorted at
   *  construction time (by originating shell for radiative transitions and
   *  by originating and emitting shell for non-radiative transitions).
   */
  class ElectronSubshellConfiguration {

    /* fields */
    id::ElectronSubshellID id_;

    double binding_energy_;
    double population_;
    std::vector< RadiativeTransitionData > radiative_;
    std::vector< NonRadiativeTransitionData > nonradiative_;

    /* auxiliary functions */

    #include "njoy/dryad/atomic/ElectronSubshellConfiguration/src/sort.hpp"
    #include "njoy/dryad/atomic/ElectronSubshellConfiguration/src/iterator.hpp"
    #include "njoy/dryad/atomic/ElectronSubshellConfiguration/src/calculateTotalProbability.hpp"
    #include "njoy/dryad/atomic/ElectronSubshellConfiguration/src/calculateAverageEnergy.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/atomic/ElectronSubshellConfiguration/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the electron subshell identifier
     */
    const id::ElectronSubshellID& identifier() const {

      return this->id_;
    }

    /**
     *  @brief Set the electron subshell identifier
     *
     *  @param[in] id.  the electron subshell identifier
     */
    void identifier( id::ElectronSubshellID id ) {

      this->id_ = std::move( id );
    }

    /**
     *  @brief Return the subshell binding energy
     */
    double bindingEnergy() const {

      return this->binding_energy_;
    }

    /**
     *  @brief Set the subshell binding energy
     *
     *  @param[in] energy   the subshell binding energy
     */
    void bindingEnergy( double energy ) {

      this->binding_energy_ = energy;
    }

    /**
     *  @brief Return the electron subshell population when the atom is neutral
     */
    double population() const {

      return this->population_;
    }

    /**
     *  @brief Set the electron subshell population
     *
     *  @param[in] population   the electron subshell population
     */
    void population( double population ) {

      this->population_ = population;
    }

    /**
     *  @brief Return the number of available radiative transitions
     */
    std::size_t numberRadiativeTransitions() const {

      return this->radiativeTransitions().size();
    }

    /**
     *  @brief Return the number of available non-radiative transitions
     */
    std::size_t numberNonRadiativeTransitions() const {

      return this->nonRadiativeTransitions().size();
    }

    /**
     *  @brief Return the number of available transitions
     */
    std::size_t numberTransitions() const {

      return this->numberRadiativeTransitions() + this->numberNonRadiativeTransitions();
    }

    /**
     *  @brief Return whether or not radiative transitions are available
     */
    bool hasRadiativeTransitions() const {

      return this->numberRadiativeTransitions() > 0;
    }

    /**
     *  @brief Return whether or not non-radiative transitions are available
     */
    bool hasNonRadiativeTransitions() const {

      return this->numberNonRadiativeTransitions() > 0;
    }

    /**
     *  @brief Return whether or not any transitions are available
     */
    bool hasTransitions() const {

      return this->hasRadiativeTransitions() || this->hasNonRadiativeTransitions();
    }

    /**
     *  @brief Return the available radiative transitions to this subshell
     */
    const std::vector< RadiativeTransitionData >& radiativeTransitions() const {

      return this->radiative_;
    }

    /**
     *  @brief Return the available radiative transitions to this subshell
     */
    std::vector< RadiativeTransitionData >& radiativeTransitions() {

      return this->radiative_;
    }

    /**
     *  @brief Set the available radiative transitions to this subshell
     *
     *  @param[in] radiative   the available radiative transitions to this subshell
     */
    void radiativeTransitions( std::vector< RadiativeTransitionData > radiative ) {

      this->radiative_ = std::move( radiative );
      this->sort();
    }

    /**
     *  @brief Return the available non-radiative transitions to this subshell
     */
    const std::vector< NonRadiativeTransitionData >& nonRadiativeTransitions() const {

      return this->nonradiative_;
    }

    /**
     *  @brief Return the available non-radiative transitions to this subshell
     */
    std::vector< NonRadiativeTransitionData >& nonRadiativeTransitions() {

      return this->nonradiative_;
    }

    /**
     *  @brief Set the available non-radiative transitions to this subshell
     *
     *  @param[in] radiative   the available non-radiative transitions to this subshell
     */
    void nonRadiativeTransitions( std::vector< NonRadiativeTransitionData > nonradiative ) {

      this->nonradiative_ = std::move( nonradiative );
      this->sort();
    }

    /**
     *  @brief Return whether or not a given radiative transition is present
     *
     *  @param originating   the identifier of the subshell from which the
     *                       vacancy filling electron originated
     */
    bool hasRadiativeTransition( const id::ElectronSubshellID& originating ) const {

      auto iter = this->iterator( originating );
      return iter != this->radiativeTransitions().end() &&
             iter->originatingShell() == originating;
    }

    /**
     *  @brief Return whether or not a given non-radiative transition is present
     *
     *  @param originating   the identifier of the subshell from which the
     *                       vacancy filling electron originated
     *  @param emitting      the identifier of the subshell from which the
     *                       emitted electron originated
     */
    bool hasNonRadiativeTransition( const id::ElectronSubshellID& originating,
                                    const id::ElectronSubshellID& emitting ) const {

      auto iter = this->iterator( originating, emitting );
      return iter != this->nonRadiativeTransitions().end() &&
             iter->originatingShell() == originating &&
             iter->emittingShell() == emitting;
    }

    /**
     *  @brief Return the requested radiative transition
     *
     *  @param originating   the identifier of the subshell from which the
     *                       vacancy filling electron originated
     */
    const RadiativeTransitionData&
    radiativeTransition( const id::ElectronSubshellID& originating ) const {

      auto iter = this->iterator( originating );
      if ( iter != this->radiativeTransitions().end() &&
           iter->originatingShell() == originating ) {

        return *iter;
      }
      else {

        Log::error( "The requested radiative transition originating from subshell "
                    "\'{}\' could not be found", originating.symbol() );
        throw std::exception();
      }
    }

    /**
     *  @brief Return the requested non-radiative transition
     *
     *  @param originating   the identifier of the subshell from which the
     *                       vacancy filling electron originated
     *  @param emitting      the identifier of the subshell from which the
     *                       emitted electron originated
     */
    const NonRadiativeTransitionData&
    nonRadiativeTransition( const id::ElectronSubshellID& originating,
                            const id::ElectronSubshellID& emitting ) const {

      auto iter = this->iterator( originating, emitting );
      if ( iter != this->nonRadiativeTransitions().end() &&
           iter->originatingShell() == originating &&
           iter->emittingShell() == emitting ) {

        return *iter;
      }
      else {

        Log::error( "The requested non-radiative transition originating from subshell "
                    "\'{}\' could not be found", originating.symbol() );
        throw std::exception();
      }
    }

    /**
     *  @brief Return the total radiative probability
     */
    double totalRadiativeProbability() const {

      return calculateProbability( this->radiativeTransitions().begin(),
                                   this->radiativeTransitions().end() );
    }

    /**
     *  @brief Return the radiative probability for transitions
     *         originating from a range of subshells
     *
     *  @param first   the identifier of the first subshell
     *  @param last    the identifier of the last subshell (included)
     */
    double radiativeProbability( const id::ElectronSubshellID& first,
                                 const id::ElectronSubshellID& last ) const {

      return calculateProbability( lower_iterator( first, this->radiativeTransitions() ),
                                   upper_iterator( last, this->radiativeTransitions() ) );
    }

    /**
     *  @brief Return the total non-radiative probability
     */
    double totalNonRadiativeProbability() const {

      return calculateProbability( this->nonRadiativeTransitions().begin(),
                                   this->nonRadiativeTransitions().end() );
    }

    /**
     *  @brief Return the non-radiative probability for transitions
     *         originating from a range of subshells
     *
     *  @param first   the identifier of the first subshell
     *  @param last    the identifier of the last subshell (included)
     */
    double nonRadiativeProbability( const id::ElectronSubshellID& first,
                                    const id::ElectronSubshellID& last ) const {

      return calculateProbability( lower_iterator( first, this->nonRadiativeTransitions() ),
                                   upper_iterator( last, this->nonRadiativeTransitions() ) );
    }

    /**
     *  @brief Return the average radiative energy
     *
     *  This function assumes that the transition energies are present.
     */
    double averageRadiativeEnergy() const {

      return calculateAverageEnergy( this->radiativeTransitions().begin(),
                                     this->radiativeTransitions().end() );
    }

    /**
     *  @brief Return the average radiative energy for transitions
     *         originating from a range of subshells
     *
     *  This function assumes that the transition energies are present.
     *
     *  @param first   the identifier of the first subshell
     *  @param last    the identifier of the last subshell (included)
     */
    double averageRadiativeEnergy( const id::ElectronSubshellID& first,
                                   const id::ElectronSubshellID& last ) const {

      return calculateAverageEnergy( lower_iterator( first, this->radiativeTransitions() ),
                                     upper_iterator( last, this->radiativeTransitions() ) );
    }

    /**
     *  @brief Return the average non-radiative energy
     *
     *  This function assumes that the transition energies are present.
     */
    double averageNonRadiativeEnergy() const {

      return calculateAverageEnergy( this->nonRadiativeTransitions().begin(),
                                     this->nonRadiativeTransitions().end() );
    }

    /**
     *  @brief Return the average non-radiative energy for transitions
     *         originating from a range of subshells
     *
     *  This function assumes that the transition energies are present.
     *
     *  @param first   the identifier of the first subshell
     *  @param last    the identifier of the last subshell (included)
     */
    double averageNonRadiativeEnergy( const id::ElectronSubshellID& first,
                                      const id::ElectronSubshellID& last ) const {

      return calculateAverageEnergy( lower_iterator( first, this->nonRadiativeTransitions() ),
                                     upper_iterator( last, this->nonRadiativeTransitions() ) );
    }

    /**
     *  @brief Normalise the transition probabilities
     */
    void normalise() {

      if ( this->hasTransitions() ) {

        double total = this->totalRadiativeProbability() + this->totalNonRadiativeProbability();
        for ( RadiativeTransitionData& transition : this->radiativeTransitions() ) {

          transition.probability( transition.probability() / total );
        }
        for ( NonRadiativeTransitionData& transition : this->nonRadiativeTransitions() ) {

          transition.probability( transition.probability() / total );
        }
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ElectronSubshellConfiguration& right ) const {

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
    bool operator!=( const ElectronSubshellConfiguration& right ) const {

      return ! this->operator==( right );
    }
  };

} // atomic namespace
} // dryad namespace
} // njoy namespace

#endif
