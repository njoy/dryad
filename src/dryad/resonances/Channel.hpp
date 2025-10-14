#ifndef NJOY_DRYAD_RESONANCES_CHANNEL
#define NJOY_DRYAD_RESONANCES_CHANNEL

// system includes
#include <optional>

// other includes
#include "dryad/id/ChannelID.hpp"
#include "dryad/id/ReactionID.hpp"
#include "dryad/resonances/ChannelQuantumNumbers.hpp"
#include "dryad/resonances/ChannelRadii.hpp"
#include "dryad/resonances/ParticlePair.hpp"
#include "dryad/resonances/HardSpherePenetrability.hpp"
#include "dryad/resonances/HardSphereShiftFactor.hpp"
#include "dryad/resonances/HardSpherePhaseShift.hpp"
#include "dryad/resonances/TabulatedWaveFunction.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A resonance reaction channel
   */
  class Channel {

    /* type aliases */

    using Penetrability = std::variant< double,
                                        HardSpherePenetrability,
                                        TabulatedWaveFunction >;
    using ShiftFactor = std::variant< double,
                                      HardSphereShiftFactor,
                                      TabulatedWaveFunction >;
    using PhaseShift = std::variant< double,
                                     HardSpherePhaseShift,
                                     TabulatedWaveFunction >;

    /* fields */

    id::ChannelID id_;
    ParticlePair incident_pair_;
    std::optional< ParticlePair > outgoing_pair_;
    double q_;
    std::optional< double > boundary_condition_;

    ChannelRadii radii_;
    Penetrability penetrability_;
    ShiftFactor shift_factor_;
    PhaseShift phase_shift_;

    /* auxiliary functions */

    #include "dryad/resonances/Channel/src/selectWaveFunctions.hpp"

  public:

    /* constructor */
    #include "dryad/resonances/Channel/src/ctor.hpp"

    /**
     *  @brief Return the channel spin
     */
    const id::ChannelID& identifier() const { return this->id_; }

    /**
     *  @brief Return the reaction this channel contributes to
     */
    const id::ReactionID& reaction() const {

      return this->identifier().reaction();
    }

    /**
     *  @brief Return the quantum numbers of the channel
     */
    const ChannelQuantumNumbers& quantumNumbers() const {

      return this->identifier().quantumNumbers();
    }

    /**
     *  @brief Return the incident particle pair
     */
    const ParticlePair& incidentParticlePair() const {

      return this->incident_pair_;
    }

    /**
     *  @brief Return the outgoing particle pair (if defined)
     */
    const std::optional< ParticlePair >& outgoingParticlePair() const {

      return this->outgoing_pair_;
    }

    /**
     *  @brief Return whether or not the channel is an incident channel
     */
    bool isIncidentChannel() const {

      return this->incidentParticlePair() == this->outgoingParticlePair();
    }

    /**
     *  @brief Return the q value of the transition
     */
    double qValue() const { return this->q_; }

    /**
     *  @brief Return the q value of the transition
     */
    const std::optional< double >& boundaryCondition() const {

      return this->boundary_condition_;
    }

    /**
     *  @brief Return the channel radii
     */
    const ChannelRadii& channelRadii() const {

      return this->radii_;
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const Channel& left,
                            const Channel& right ) {

      return std::tie( left.identifier(), left.incidentParticlePair(),
                       left.outgoingParticlePair(), left.q_,
                       left.boundaryCondition(), left.channelRadii() ) ==
             std::tie( right.identifier(), right.incidentParticlePair(),
                       right.outgoingParticlePair(), right.q_,
                       right.boundaryCondition(), right.channelRadii() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const Channel& left,
                            const Channel& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
