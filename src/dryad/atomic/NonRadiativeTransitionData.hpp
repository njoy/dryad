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
   *  vacancy in the current shell while another electron () is emitted. The
   *  energy of the emitted electron is equal to the binding energy of the
   *  subshell with the vacancy minus the binding energy of the subshell from
   *  which the electron filling the vacancy originated from and the subshell
   *  from which the emitted electron came from.
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
     *  @brief Return the identifier of the subshell from which the
     *         emitted electron originated
     */
    const id::ElectronSubshellID& emittingShell() const noexcept {

      return this->emitting_shell_;
    }

    /**
     *  @brief Return the transition probability
     */
    double probability() const noexcept {

      return this->probability_;
    }

    /**
     *  @brief Return the energy of the emitted electron
     */
    const std::optional< double >& energy() const noexcept {

      return this->energy_;
    }
  };

} // atomic namespace
} // dryad namespace
} // njoy namespace

#endif
