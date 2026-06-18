#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL

#include <cmath>
#include <tuple>
#include <variant>

#include "tools/overload.hpp"
#include "njoy/dryad/resonances/Channel.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  class UnresolvedChannel {


    private:

      Channel channel_;


    public:

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





  }
    
}
}
}

#endif
