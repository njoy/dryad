#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL

#include <cmath>
#include <tuple>
#include <variant>
#include <optional>

#include "tools/overload.hpp"
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/dryad/resonances/ReducedWidthConversion.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  class UnresolvedChannel {

    public:

      using ConversionFactor = std::variant< double,
                                             ReducedWidthConversion >;

    private:

      Channel channel_;
      ConversionFactor conversion_factor_;
      double reference_energy_;

      /* auxiliary functions */
      #include "njoy/dryad/resonances/UnresolvedChannel/src/selectWidthConversion.hpp"



    public: 
      #include "njoy/dryad/resonances/UnresolvedChannel/src/ctor.hpp"

      /**
       *  @brief Return the underlying channel
       */
      const Channel& channel() const {

        return this->channel_;
      }

      /**
       *  @brief Return the channel identifier
       */
      const id::ChannelID& identifier() const {

        return this->channel_.identifier();
      }

      /**
       *  @brief Return the reaction this channel contributes to
       */
      const id::ReactionID& reaction() const {

        return this->channel_.reaction();
      }

      /**
       *  @brief Return the wave number at a specific energy
       */
      const double waveNumber( double energy ) {

        return this->channel_.waveNumber( energy );
      }

      /**
       *  @brief Return the reference energy of a reduced channel
       */
      const double referenceEnergy() const {

        return this->reference_energy_;
      }

      /**
       *  @brief Return the outgoing particle pair (if defined)
       *
       */
      const std::optional< ParticlePair >& outgoingParticlePair() const {

        return this->channel_.outgoingParticlePair();
      }

      /**
       *  @brief Return the channel radii
       */
      const ChannelRadii& channelRadii() const {

        return this->channel_.channelRadii();
      }

      const ConversionFactor& conversionFactor() const {

        return this->conversion_factor_;
      }

      /**
       *  @brief Calculate the conversion factor for a width
       *
       *  @param[in] energy   the energy (given in eV)
       */
      const double widthConversionFactor( double energy ) const {

        tools::overload visitor{

          []  ( const double ) -> double {

            return 1.0;
          },
          [&] ( const ReducedWidthConversion& function ) -> double {

            double rho = this->channel_.waveNumber( energy ) * this->channelRadii().calculatePenetrabilityRadius( energy );
            return function.calculateConversionFactor( rho, energy);

          }
        };

        return std::visit( visitor, this->conversion_factor_);
      }

      /**
       *  @brief Equality comparison
       *
       *  @param[in]  left    the object on the left hand side
       *  @param[in]  right   the object on the right hand side
       */
      friend bool operator==( const UnresolvedChannel& left,
                              const UnresolvedChannel& right ) {

        return std::tie( left.channel_, left.conversion_factor_, left.reference_energy_ ) ==
               std::tie( right.channel_, right.conversion_factor_, right.reference_energy_ );
      }

      /**
       *  @brief Inequality comparison
       *
       *  @param[in]  left    the object on the left hand side
       *  @param[in]  right   the object on the right hand side
       */
      friend bool operator!=( const UnresolvedChannel& left,
                              const UnresolvedChannel& right ) {

        return ! ( left == right );
      }
  };
   
} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif
