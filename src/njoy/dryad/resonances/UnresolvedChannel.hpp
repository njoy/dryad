#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL

// system includes
#include <tuple>
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/dryad/resonances/HardSpherePenetrabilityRatio.hpp"
#include "njoy/dryad/resonances/ReducedWidthConversion.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  class UnresolvedChannel : protected Channel {

  public:

    /* type aliases */

    using PenetrabilityRatio = std::variant< double, HardSpherePenetrabilityRatio >;
    using Background = Channel::Background;

  private:

    /* fields */

    double reference_energy_;
    PenetrabilityRatio ratio_;

    /* auxiliary functions */

    /**
     *  @brief Return the conversion factor
     *
     *  @param[in] l                 the orbital angular momentum
     *  @param[in] referenceEnergy   the reference energy
     *  @param[in] outgoing          the outgoing particle pair
     */
    static PenetrabilityRatio
    selectWidthPenetrabilityRatio( unsigned int l,
                                 const std::optional< ParticlePair >& outgoing ) {

      if ( outgoing.has_value() ) {

        if ( outgoing->lightParticle().identifier() == id::ParticleID::neutron() ) {

          return HardSpherePenetrabilityRatio( l, 0 );
        }
      }

      return 1.;
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    UnresolvedChannel() = default;

    UnresolvedChannel( const UnresolvedChannel& ) = default;
    UnresolvedChannel( UnresolvedChannel&& ) = default;

    UnresolvedChannel& operator=( const UnresolvedChannel& ) = default;
    UnresolvedChannel& operator=( UnresolvedChannel&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] identifier        the channel identifier
     *  @param[in] incident          the current incident particle pair
     *  @param[in] outgoing          the outgoing particle pair
     *  @param[in] qValue            the Q value associated with the transition from
     *                               the incident to the outgoing particle pair
     *  @param[in] boundary          the boundary condition
     *  @param[in] radii             the channel radii for the calculation of the
     *                               wave functions
     *  @param[in] referenceEnergy   the reference energy for the widths (default is 1 eV)
     */
    UnresolvedChannel( id::ChannelID identifier,
                       ParticlePair incident,
                       std::optional< ParticlePair > outgoing,
                       double qValue,
                       std::optional< double > boundary,
                       ChannelRadii radii,
                       double referenceEnergy = 1. ) :
        Channel( std::move( identifier ), std::move( incident ),
                 std::move( outgoing ), qValue,
                 std::move( boundary ), std::move( radii ),
                 Kinematics::NonRelativistic, std::nullopt ),
        reference_energy_( referenceEnergy ),
        ratio_( selectWidthPenetrabilityRatio(
                  Channel::quantumNumbers().orbitalAngularMomentum(),
                  Channel::outgoingParticlePair() ) ) {}

    /* methods */

    using Channel::identifier;
    using Channel::reaction;
    using Channel::quantumNumbers;
    using Channel::incidentParticlePair;
    using Channel::outgoingParticlePair;
    using Channel::background;
    using Channel::channelRadii;
    using Channel::statisticalSpinFactor;
    using Channel::isBelowThreshold;
    using Channel::waveNumber;
    using Channel::penetrability;
    using Channel::shiftFactor;
    using Channel::phaseShift;

    /**
     *  @brief Return the reference energy
     */
    double referenceEnergy() const {

      return this->reference_energy_;
    }

    /**
     *  @brief Set the reference energy
     */
    void referenceEnergy( double referenceEnergy ) {

      this->reference_energy_ = referenceEnergy;
    }

    /**
     *  @brief Calculate the width conversion factor at a given energy
     *
     *  @param[in] energy   the energy (given in eV)
     */
    double widthConversionFactor( double energy ) const {

      tools::overload visitor{

        []  ( const double factor ) -> double {

          return factor;
        },
        [&] ( const HardSpherePenetrabilityRatio& function ) -> double {

          const auto k = this->waveNumber( energy );
          const auto a = this->channelRadii().calculatePenetrabilityRadius( energy );
          return function( k * a ) * std::sqrt( energy / this->referenceEnergy() );
        }
      };

      return std::visit( visitor, this->ratio_);
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const UnresolvedChannel& right ) const {

      return Channel::operator==( right ) &&
             std::tie( this->reference_energy_, this->ratio_ ) ==
             std::tie( right.reference_energy_, right.ratio_ );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const UnresolvedChannel& right ) const {

      return ! this->operator==( right );
    }
  };

} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif
