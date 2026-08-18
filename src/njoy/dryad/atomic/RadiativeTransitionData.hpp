#ifndef NJOY_DRYAD_ATOMIC_RADIATIVETRANSITIONDATA
#define NJOY_DRYAD_ATOMIC_RADIATIVETRANSITIONDATA

// system includes
#include <optional>

// other includes
#include "njoy/dryad/id/ElectronSubshellID.hpp"
#include "njoy/dryad/atomic/TransitionType.hpp"

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

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    RadiativeTransitionData() = default;

    RadiativeTransitionData( const RadiativeTransitionData& ) = default;
    RadiativeTransitionData( RadiativeTransitionData&& ) = default;

    RadiativeTransitionData& operator=( const RadiativeTransitionData& ) = default;
    RadiativeTransitionData& operator=( RadiativeTransitionData&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param originating   the identifier of the subshell from which the
     *                       vacancy filling electron originated
     *  @param probability   the probability of the transition
     *  @param energy        the energy of the emitted photon (default: undefined)
     */
    RadiativeTransitionData( id::ElectronSubshellID originating,
                             double probability,
                             std::optional< double > energy = std::nullopt ) :
      originating_shell_( std::move( originating ) ),
      probability_( std::move( probability ) ),
      energy_( std::move( energy ) ) {}

    /* methods */

    /**
     *  @brief Return the transition type
     */
    static constexpr TransitionType type() {

      return TransitionType::Radiative;
    }

    /**
     *  @brief Return the identifier of the subshell from which the
     *         electron filling the vacancy originated
     */
    const id::ElectronSubshellID& originatingShell() const {

      return this->originating_shell_;
    }

    /**
     *  @brief Set the identifier of the subshell from which the
     *         electron filling the vacancy originated
     *
     *  @param[in] originatingShell   the identifier of the subshell from which the
     *                                vacancy filling electron originated
     */
    void originatingShell( id::ElectronSubshellID originatingShell ) {

      this->originating_shell_ = std::move( originatingShell );
    }

    /**
     *  @brief Return the transition probability
     */
    double probability() const {

      return this->probability_;
    }

    /**
     *  @brief Set the transition probability
     *
     *  @param[in] probability   the probability of the transition
     */
    void probability( double probability ) {

      this->probability_ = probability;
    }

    /**
     *  @brief Return the energy of the emitted photon
     */
    const std::optional< double >& energy() const {

      return this->energy_;
    }

    /**
     *  @brief Set the energy of the emitted photon
     *
     *  @param[in] energy   the energy of the emitted photon
     */
    void energy( std::optional< double > energy ) {

      this->energy_ = std::move( energy );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const RadiativeTransitionData& right ) const {

      return this->originatingShell() == right.originatingShell() &&
             this->probability() == right.probability() &&
             this->energy() == right.energy();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const RadiativeTransitionData& right ) const {

      return ! this->operator==( right );
    }
  };

} // atomic namespace
} // dryad namespace
} // njoy namespace

#endif
