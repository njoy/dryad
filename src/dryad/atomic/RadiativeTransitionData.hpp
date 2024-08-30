#ifndef NJOY_DRYAD_ATOMIC_RADIATIVETRANSITION
#define NJOY_DRYAD_ATOMIC_RADIATIVETRANSITION

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
   *  @brief Data for a radiative transition in atomic relaxation
   *
   *  In a radiative transition, an electron from another shell fills a
   *  vacancy in the current shell while emitting a photon. The energy of
   *  the emitted photon is equal to the difference in binding energies
   *  between the subshell with the vacancy and the subshell from which the
   *  electron filling the vacancy originated from.
   */
  class RadiativeTransitionData {

    /* fields */
    id::ElectronSubshellID originating_shell_;
    double probability_;
    std::optional< double > energy_;

  public:

    /* constructor */

    #include "dryad/atomic/RadiativeTransitionData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the transition type
     */
    static constexpr TransitionType type() noexcept {

      return TransitionType::Radiative;
    }

    /**
     *  @brief Return the identifier of the subshell from which the
     *         electron filling the vacancy originated
     */
    const id::ElectronSubshellID& originatingShell() const noexcept {

      return this->originating_shell_;
    }

    /**
     *  @brief Return the transition probability
     */
    double probability() const noexcept {

      return this->probability_;
    }

    /**
     *  @brief Set the transition probability
     */
    void probability( double probability ) noexcept {

      this->probability_ = probability;
    }

    /**
     *  @brief Return the energy of the emitted photon
     */
    const std::optional< double >& energy() const noexcept {

      return this->energy_;
    }
  };

} // atomic namespace
} // dryad namespace
} // njoy namespace

#endif
