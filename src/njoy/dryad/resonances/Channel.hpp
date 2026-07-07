#ifndef NJOY_DRYAD_RESONANCES_CHANNEL
#define NJOY_DRYAD_RESONANCES_CHANNEL

// system includes
#include <optional>
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/id/ChannelID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/resonances/ChannelQuantumNumbers.hpp"
#include "njoy/dryad/resonances/ChannelRadii.hpp"
#include "njoy/dryad/resonances/ParticlePair.hpp"
#include "njoy/dryad/resonances/NonRelativisticWaveNumber.hpp"
#include "njoy/dryad/resonances/RelativisticWaveNumber.hpp"
#include "njoy/dryad/resonances/HardSpherePenetrability.hpp"
#include "njoy/dryad/resonances/HardSphereShiftFactor.hpp"
#include "njoy/dryad/resonances/HardSpherePhaseShift.hpp"
#include "njoy/dryad/resonances/CoulombPenetrability.hpp"
#include "njoy/dryad/resonances/CoulombShiftFactor.hpp"
#include "njoy/dryad/resonances/CoulombPhaseShift.hpp"
#include "njoy/dryad/resonances/CoulombPhaseShiftDifference.hpp"
#include "njoy/dryad/resonances/TabulatedWaveFunction.hpp"
#include "njoy/dryad/resonances/FrohnerBackground.hpp"
#include "njoy/dryad/resonances/SammyBackground.hpp"
#include "njoy/dryad/resonances/TabulatedBackground.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A resonance reaction channel
   */
  class Channel {

  public:

    /* type aliases */

    using Background = std::variant< FrohnerBackground,
                                     SammyBackground,
                                     TabulatedBackground >;
    using WaveNumber = std::variant< NonRelativisticWaveNumber,
                                     RelativisticWaveNumber >;
    using Penetrability = std::variant< double,
                                        HardSpherePenetrability,
                                        CoulombPenetrability,
                                        TabulatedWaveFunction >;
    using ShiftFactor = std::variant< double,
                                      HardSphereShiftFactor,
                                      CoulombShiftFactor,
                                      TabulatedWaveFunction >;
    using PhaseShift = std::variant< double,
                                     HardSpherePhaseShift,
                                     CoulombPhaseShift,
                                     TabulatedWaveFunction >;
    using PhaseShiftDifference = std::variant< double,
                                               CoulombPhaseShiftDifference >;

  private:

    /* fields */

    id::ChannelID id_;
    ParticlePair incident_pair_;
    std::optional< ParticlePair > outgoing_pair_;
    double q_;
    std::optional< double > boundary_condition_;
    std::optional< Background > background_;

    ChannelRadii radii_;
    WaveNumber wave_number_;
    Penetrability penetrability_;
    ShiftFactor shift_factor_;
    PhaseShift phase_shift_;
    PhaseShiftDifference phase_shift_difference_;

    double spin_factor_;

    /* auxiliary functions */

    #include "njoy/dryad/resonances/Channel/src/selectWaveNumber.hpp"
    #include "njoy/dryad/resonances/Channel/src/selectWaveFunctions.hpp"
    #include "njoy/dryad/resonances/Channel/src/updateWaveFunctions.hpp"
    #include "njoy/dryad/resonances/Channel/src/calculateSpinFactor.hpp"

  public:

    /* constructor */
    #include "njoy/dryad/resonances/Channel/src/ctor.hpp"

    /**
     *  @brief Return the channel identifier
     */
    const id::ChannelID& identifier() const {

      return this->id_;
    }

    /**
     *  @brief Set the channel identifier
     *
     *  @param[in] id   the channel identifier
     */
    void identifier( id::ChannelID id ) {

      this->id_ = std::move( id );
      this->updateWaveFunctions();
    }

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
     *  @brief Set the incident particle pair
     *
     *  @param[in] pair   the incident particle pair
     */
    void incidentParticlePair( ParticlePair pair ) {

      this->incident_pair_ = std::move( pair );
    }

    /**
     *  @brief Return the outgoing particle pair (if defined)
     */
    const std::optional< ParticlePair >& outgoingParticlePair() const {

      return this->outgoing_pair_;
    }

    /**
     *  @brief Set the outgoing particle pair
     *
     *  @param[in] pair   the outgoing particle pair
     */
    void outgoingParticlePair( std::optional< ParticlePair > pair ) {

      this->outgoing_pair_ = std::move( pair );
      this->updateWaveFunctions();
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
     *  @brief Set the q value of the transition
     *
     *  @param[in] q_value   the q value
     */
    void qValue( double q_value ) {

      this->q_ = std::move( q_value );
    }

    /**
     *  @brief Return the boundary condition value (if defined)
     */
    const std::optional< double >& boundaryCondition() const {

      return this->boundary_condition_;
    }

    /**
     *  @brief Set the boundary condition value
     *
     *  @param[in] boundary   the boundary condition value
     */
    void boundaryCondition( std::optional< double > boundary ) {

      this->boundary_condition_ = std::move( boundary );
    }

    /**
     *  @brief Return the background function (if defined)
     */
    const std::optional< Background >& background() const {

      return this->background_;
    }

    /**
     *  @brief Set the background function
     *
     *  @param[in] background   the background function
     */
    void background( std::optional< Background > background ) {

      this->background_ = std::move( background );
    }

    /**
     *  @brief Return the channel radii
     */
    const ChannelRadii& channelRadii() const {

      return this->radii_;
    }

    /**
     *  @brief Set the channel radii
     *
     *  @param[in] radii   the channel radii
     */
    void channelRadii( ChannelRadii radii ) {

      this->radii_ = std::move( radii );
    }

    /**
     *  @brief Return the kinematics type applied to the channel
     */
    Kinematics kinematicsType() const {

      return std::visit( [] ( auto&& function ) -> Kinematics
                            { return function.kinematicsType(); },
                         this->wave_number_ );
    }

    /**
     *  @brief Set the kinematics type
     *
     *  @param[in] kinematics   the kinematics type
     */
    void kinematicsType( Kinematics kinematics ) {

      this->wave_number_ = selectWaveNumber( kinematics );
    }

    /**
     *  @brief Return the statistical spin factor
     *
     *  The statistical spin factor g of a channel is defined as follows:
     *     g = ( 2 * J + 1 ) / ( 2 * ia + 1 ) / ( 2 * ib + 1 )
     *  in which J is the total angular momentum of the channel and ia and ib
     *  are the spins of the particles in the outgoing particle pair.
     */
    double statisticalSpinFactor() const { return this->spin_factor_; }

    /**
     *  @brief Return whether or not the energy is below the threshold for this
     *         channel
     *
     *  The incident energy is below the threshold energy for the channel if
     *      energy * ratio + q < 0.0
     *  where energy is the incident energy, ratio is the mass ratio M / ( m + M )
     *  for the incident particle pair and q is the Q value for this channel.
     *
     *  @param[in] energy   the energy to be tested
     */
    bool isBelowThreshold( double energy ) const {

      double value = this->incidentParticlePair().massRatio() * energy;
      return ( value + this->qValue() ) < 0.0;
    }

    /**
     *  @brief Calculate the channel wave number (given in fm^-1) at a given energy
     *
     *  @param[in] energy   the energy (given in eV)
     */
    double waveNumber( double energy ) const {

      tools::overload visitor{

        [&] ( const NonRelativisticWaveNumber& function ) -> double {

          return function( energy, this->qValue(),
                           this->incidentParticlePair(),
                           this->outgoingParticlePair().value() );
        },
        [&] ( const RelativisticWaveNumber& function ) -> double {

          return function( energy, this->incidentParticlePair() );
        }
      };

      return std::visit( visitor, this->wave_number_ );
    }

    /**
     *  @brief Calculate the Sommerfeld parameter for the channel at a
     *         given energy
     *
     *  The Sommerfeld parameter eta is an energy dependent quantity defined as
     *  follows:
     *     eta = z * Z * mu / ( 4 * pi * epsilon0 * hbar^2 * k )
     *  in which z and Z are the electrical charge of the particles in the
     *  particle pair, mu is the reduced mass of the particle pair, hbar is the
     *  Planck constant, k is the wave number and epsilon0 is the vacuum
     *  permittivity.
     *
     *  It is a dimensionless parameter.
     *
     *  @param[in] energy   the energy (given in eV)
     */
    double sommerfeldParameter( double energy ) const {

      // conversion constant to convert the final value to a dimensionless value
      constexpr double conversion = constants::amu * constants::femto;

      if ( this->outgoingParticlePair()->lightParticle().charge() != 0 ) {

        const auto zZ = this->outgoingParticlePair()->lightParticle().charge() *
                        this->outgoingParticlePair()->heavyParticle().charge(); // e^2
        const auto mu = this->outgoingParticlePair()->reducedMass();            // amu
        const auto k = this->waveNumber( energy );                              // fm^-1
        return zZ * mu * conversion
               / ( 4. * k * constants::pi * constants::epsilon0
                          * constants::hbar * constants::hbar );
      }
      else {

        return 0.;
      }
    }

    /**
     *  @brief Calculate the penetrability for the channel at a given energy
     *
     *  @param[in] energy   the energy (given in eV)
     */
    double penetrability( double energy ) const {

      tools::overload visitor{

        [] ( double value ) -> double { return value; },
        [&] ( const HardSpherePenetrability& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculatePenetrabilityRadius( energy );
          return function( k * a );
        },
        [&] ( const CoulombPenetrability& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculatePenetrabilityRadius( energy );
          const auto eta = this->sommerfeldParameter( energy );
          return function( k * a, eta );
        },
        [&] ( const TabulatedWaveFunction& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculatePenetrabilityRadius( energy );
          return function( k * a );
        }
      };

      return std::visit( visitor, this->penetrability_ );
    }

    /**
     *  @brief Calculate the shift factor for the channel at a given energy
     *
     *  @param[in] energy   the energy (given in eV)
     */
    double shiftFactor( double energy ) const {

      tools::overload visitor{

        [] ( double value ) -> double { return value; },
        [&] ( const HardSphereShiftFactor& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculateShiftFactorRadius( energy );
          return function( k * a );
        },
        [&] ( const CoulombShiftFactor& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculateShiftFactorRadius( energy );
          const auto eta = this->sommerfeldParameter( energy );
          return function( k * a, eta );
        },
        [&] ( const TabulatedWaveFunction& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculateShiftFactorRadius( energy );
          return function( k * a );
        }
      };

      return std::visit( visitor, this->shift_factor_ );
    }

    /**
     *  @brief Calculate the phase shift for the channel at a given energy
     *
     *  @param[in] energy   the energy (given in eV)
     */
    double phaseShift( double energy ) const {

      tools::overload visitor{

        [] ( double value ) -> double { return value; },
        [&] ( const HardSpherePhaseShift& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculatePhaseShiftRadius( energy );
          return function( k * a );
        },
        [&] ( const CoulombPhaseShift& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculatePhaseShiftRadius( energy );
          const auto eta = this->sommerfeldParameter( energy );
          return function( k * a, eta );
        },
        [&] ( const TabulatedWaveFunction& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculatePhaseShiftRadius( energy );
          return function( k * a );
        }
      };

      return std::visit( visitor, this->phase_shift_ );
    }

    /**
     *  @brief Calculate the phase shift difference for the channel at a given energy
     *
     *  @param[in] energy   the energy (given in eV)
     */
    double phaseShiftDifference( double energy ) const {

      tools::overload visitor{

        [] ( double value ) -> double { return value; },
        [&] ( const CoulombPhaseShiftDifference& function ) -> double {

          const auto eta = this->sommerfeldParameter( energy );
          return function( eta );
        }
      };

      return std::visit( visitor, this->phase_shift_difference_ );
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
                       left.boundaryCondition(), left.channelRadii(),
                       left.background() ) ==
             std::tie( right.identifier(), right.incidentParticlePair(),
                       right.outgoingParticlePair(), right.q_,
                       right.boundaryCondition(), right.channelRadii(),
                       right.background() );
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
