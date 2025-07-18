#ifndef NJOY_DRYAD_ATOMICRELAXATION
#define NJOY_DRYAD_ATOMICRELAXATION

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
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

    /* auxiliary functions */

    #include "dryad/AtomicRelaxation/src/sort.hpp"
    #include "dryad/AtomicRelaxation/src/iterator.hpp"

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

    /**
     *  @brief Return the electron shell configuration data
     */
    std::vector< atomic::ElectronSubshellConfiguration >&
    subshells() noexcept {

      return this->subshells_;
    }

    /**
     *  @brief Set the electron shell configuration data
     *
     *  @param[in] subshells   the electron shell configuration data
     */
    void subshells( std::vector< atomic::ElectronSubshellConfiguration > subshells ) noexcept {

      this->subshells_ = std::move( subshells );
      this->sort();
    }

    /**
     *  @brief Return whether or not a given subshell is present
     *
     *  @param[in] id   the subshell identifier
     */
    bool hasSubshell( const id::ElectronSubshellID& id ) const {

      auto iter = this->iterator( id );
      return iter != this->subshells().end();
    }

    /**
     *  @brief Return the requested subshell
     *
     *  @param[in] id   the reaction identifier
     */
    const atomic::ElectronSubshellConfiguration&
    subshell( const id::ElectronSubshellID& id ) const {

      auto iter = this->iterator( id );
      if ( ( iter != this->subshells().end() ) && ( iter->identifier() == id ) ) {

        return *iter;
      }
      else {

        Log::error( "The requested subshell \'{}\' could not be found", id.symbol() );
        throw std::exception();
      }
    }

    /**
     *  @brief Normalise the transition probabilities for each subshell
     */
    void normalise() noexcept {

      for ( atomic::ElectronSubshellConfiguration& subshell : this->subshells() ) {

        subshell.normalise();
      }
    }

    /**
     *  @brief Calculate the transition energies for all transitions
     */
    void calculateTransitionEnergies() noexcept {

      for ( atomic::ElectronSubshellConfiguration& subshell : this->subshells() ) {

        auto current = subshell.bindingEnergy();
        for ( atomic::RadiativeTransitionData& transition : subshell.radiativeTransitions() ) {

          auto originating = this->subshell( transition.originatingShell() ).bindingEnergy();
          transition.energy( current - originating );
        }
        for ( atomic::NonRadiativeTransitionData& transition : subshell.nonRadiativeTransitions() ) {

          auto originating = this->subshell( transition.originatingShell() ).bindingEnergy();
          auto emitting = this->subshell( transition.emittingShell() ).bindingEnergy();
          transition.energy( current - originating - emitting );
        }
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const AtomicRelaxation& right ) const noexcept {

      return this->elementIdentifier() == right.elementIdentifier() &&
             this->subshells() == right.subshells();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const AtomicRelaxation& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
