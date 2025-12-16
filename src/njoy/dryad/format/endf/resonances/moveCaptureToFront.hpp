#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_MOVECAPTURETOFRONT
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_MOVECAPTURETOFRONT

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {

  /**
   *  @brief Move the eliminated capture channel to the front
   *
   *  @param[in] channel_data   the channel data
   */
  inline void
  moveCaptureToFront( std::vector< dryad::resonances::SpinGroup::ChannelData >& channel_data ) {

    auto iter = std::find_if( channel_data.begin(), channel_data.end(),
                              [] ( auto&& entry ) {

                                if ( entry.first.outgoingParticlePair().has_value() ) {

                                  return entry.first.outgoingParticlePair()->lightParticle().identifier()
                                         == id::ParticleID::photon();
                                }
                                return false;
                              } );

    std::rotate( channel_data.begin(), iter, iter + 1 );
  }

} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
