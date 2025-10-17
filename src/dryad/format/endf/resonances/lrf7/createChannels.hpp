#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATECHANNELS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATECHANNELS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/resonances/Channel.hpp"
#include "dryad/format/endf/resonances/lrf7/createParticlePairs.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the channels for a spin group
   *
   *  @param[in] incident        the incident particle pair
   *  @param[in] pairs           the particle pairs
   *  @param[in] reactions       the reaction identifiers
   *  @param[in] qvalues         the q values
   *  @param[in] boundaries      flag to indicate whether or not to read the boundary conditions
   *  @param[in] endfChannels    the parsed ENDF channels
   */
  auto createChannels(
           const dryad::resonances::ParticlePair& incident,
           const std::vector< std::optional< dryad::resonances::ParticlePair > >& pairs,
           const std::vector< id::ReactionID >& reactions,
           const std::vector< double >& qvalues,
           bool boundaries,
           const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceChannels& endfChannels ) {

    std::vector< dryad::resonances::Channel > channels;

    double spin = endfChannels.spin();
    short parity = spin == 0.0 ? endfChannels.parity() >= 0 ? +1 : -1
                               : spin > 0 ? +1 : -1;

    for ( unsigned int i = 0; i < endfChannels.numberChannels(); ++i ) {

      std::size_t index = endfChannels.particlePairNumbers()[i] - 1;

      dryad::resonances::ChannelQuantumNumbers numbers( endfChannels.orbitalMomentumValues()[i],
                                                        endfChannels.channelSpinValues()[i],
                                                        spin, parity );
      dryad::resonances::ChannelRadii radii( endfChannels.trueChannelRadii()[i],
                                             endfChannels.effectiveChannelRadii()[i] );

      channels.emplace_back( id::ChannelID( reactions[index], std::move( numbers ) ),
                             incident,
                             pairs[index],
                             qvalues[index],
                             boundaries ? std::nullopt
                                        : std::make_optional( endfChannels.boundaryConditionValues()[i] ),
                             std::move( radii ) );
    }

    return channels;
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
