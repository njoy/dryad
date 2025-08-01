#ifndef NJOY_DRYAD_ATOMICRELAXATION
#define NJOY_DRYAD_ATOMICRELAXATION

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/Documentation.hpp"
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
    Documentation documentation_;
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
     *  @brief Return the documentation
     */
    const Documentation& documentation() const {

      return this->documentation_;
    }

    /**
     *  @brief Return the documentation
     */
    Documentation& documentation() {

      return this->documentation_;
    }

    /**
     *  @brief Set the documentation
     *
     *  @param[in] documentation   the documentation
     */
    void documentation( Documentation documentation ) {

      this->documentation_ = std::move( documentation );
    }

    /**
     *  @brief Return the element identifier
     */
    const id::ElementID& elementIdentifier() const {

      return this->element_id_;
    }

    /**
     *  @brief Return the element identifier
     *
     *  @param[in] element   the element identifier
     */
    void elementIdentifier( id::ElementID element ) {

      this->element_id_ = std::move( element );
    }

    /**
     *  @brief Return the electron shell configuration data
     */
    const std::vector< atomic::ElectronSubshellConfiguration >&
    subshells() const {

      return this->subshells_;
    }

    /**
     *  @brief Return the electron shell configuration data
     */
    std::vector< atomic::ElectronSubshellConfiguration >&
    subshells() {

      return this->subshells_;
    }

    /**
     *  @brief Set the electron shell configuration data
     *
     *  @param[in] subshells   the electron shell configuration data
     */
    void subshells( std::vector< atomic::ElectronSubshellConfiguration > subshells ) {

      this->subshells_ = std::move( subshells );
      this->sort();
    }

    /**
     *  @brief Return the number of subshells defined for this atom
     */
    std::size_t numberSubshells() const {

      return this->subshells().size();
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
    void normalise() {

      for ( atomic::ElectronSubshellConfiguration& subshell : this->subshells() ) {

        subshell.normalise();
      }
    }

    /**
     *  @brief Calculate the transition energies for all transitions
     */
    void calculateTransitionEnergies() {

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
    bool operator==( const AtomicRelaxation& right ) const {

      return this->elementIdentifier() == right.elementIdentifier() &&
             this->subshells() == right.subshells();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const AtomicRelaxation& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
