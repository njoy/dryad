#ifndef NJOY_DRYAD_ATOMIC_NONRADIATIVETRANSITION
#define NJOY_DRYAD_ATOMIC_NONRADIATIVETRANSITION

// system includes
#include <optional>

// other includes
#include "dryad/id/ElectronSubshellID.hpp"
#include "dryad/atomic/TransitionType.hpp"

namespace njoy {
namespace dryad {
namespace atomic {

  /**
   *  @class
   *  @brief Data for a non-radiative transition in atomic relaxation
   *
   *  In a non-radiative transition, an electron from another shell fills a
   *  vacancy in the current shell while another electron is emitted (this
   *  electron is often referred to as an Auger electron). The energy of the
   *  emitted electron is equal to the binding energy of the subshell with
   *  the vacancy minus the binding energy of the subshell from which the
   *  electron filling the vacancy originated from and the subshell from
   *  which the emitted electron came from.
   */
  class NonRadiativeTransitionData {

    /* fields */
    id::ElectronSubshellID originating_shell_;
    id::ElectronSubshellID emitting_shell_;
    double probability_;
    std::optional< double > energy_;

  public:

    /* constructor */

    #include "dryad/atomic/NonRadiativeTransitionData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the transition type
     */
    static constexpr TransitionType type() noexcept {

      return TransitionType::NonRadiative;
    }

    /**
     *  @brief Return the identifier of the subshell from which the
     *         electron filling the vacancy originated
     */
    const id::ElectronSubshellID& originatingShell() const noexcept {

      return this->originating_shell_;
    }

    /**
     *  @brief Set the identifier of the subshell from which the
     *         electron filling the vacancy originated
     *
     *  @param originatingShell   the identifier of the subshell from which the
     *                            vacancy filling electron originated
     */
    void originatingShell( id::ElectronSubshellID originatingShell ) noexcept {

      this->originating_shell_ = std::move( originatingShell );
    }

    /**
     *  @brief Return the identifier of the subshell from which the
     *         emitted electron originated
     */
    const id::ElectronSubshellID& emittingShell() const noexcept {

      return this->emitting_shell_;
    }

    /**
     *  @brief Set the the identifier of the subshell from which the
     *         emitted electron originated
     *
     *  @param emittingShell      the identifier of the subshell from which the
     *                            emitted electron originated
     */
    void emittingShell( id::ElectronSubshellID emittingShell ) noexcept {

      this->emitting_shell_ = std::move( emittingShell );
    }

    /**
     *  @brief Return the transition probability
     */
    double probability() const noexcept {

      return this->probability_;
    }

    /**
     *  @brief Set the transition probability
     *
     *  @param[in] probability   the probability of the transition
     */
    void probability( double probability ) noexcept {

      this->probability_ = probability;
    }

    /**
     *  @brief Return the energy of the emitted electron
     */
    const std::optional< double >& energy() const noexcept {

      return this->energy_;
    }

    /**
     *  @brief Set the energy of the emitted electron
     *
     *  @param[in] energy   the energy of the emitted electron
     */
    void energy( std::optional< double > energy ) noexcept {

      this->energy_ = std::move( energy );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const NonRadiativeTransitionData& right ) const noexcept {

      return this->originatingShell() == right.originatingShell() &&
             this->emittingShell() == right.emittingShell() &&
             this->probability() == right.probability() &&
             this->energy() == right.energy();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const NonRadiativeTransitionData& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // atomic namespace
} // dryad namespace
} // njoy namespace

#endif
