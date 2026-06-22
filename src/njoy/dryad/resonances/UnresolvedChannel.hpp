#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL

#include <cmath>
#include <tuple>
#include <variant>

#include "tools/overload.hpp"
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/dryad/resonances/UnresolvedWidthConversion.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  class UnresolvedChannel {

    public:

      using ConversionFactor = std::variant< ConstantWidthConversion,
                                             NeutronWidthConversion >;

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

      /**
       *  @brief Calculate the conversion factor for a width
       *
       *  @param[in] energy   the energy (given in eV)
       */
      double conversion_factor( double energy ) const {

        tools::overload visitor{

          [&] ( const ConstantWidthConversion& ) -> double {

            return 1;
          },
          [&] ( const NeutronWidthConversion& ) -> double {

            double rho = this->channel_.waveNumber( energy ) * this->channelRadii().calculatePenetrabilityRadius( energy );
            const auto p_e = this->channel_.penetrability( energy );
            return p_e / rho * std::sqrt( energy / this->reference_energy_);
          }
        };

        return std::visit( visitor, this->conversion_factor_);
      }





  };
    
}
}
}

#endif
