#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATESPINGROUP
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATESPINGROUP

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/resonances/SpinGroup.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/resonances/lrf7/createParticlePairs.hpp"
#include "dryad/format/endf/resonances/lrf7/createChannels.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the spin groups
   */
  auto createSpinGroups( const id::ParticleID& projectile,
                         const id::ParticleID& target,
                         const ENDFtk::section::Type< 2, 151 >::RMatrixLimited& endf ) {

    std::vector< dryad::resonances::SpinGroup > groups;

    // reactions defined in the data
    std::vector< id::ReactionID > reactions( endf.particlePairs().numberParticlePairs() );
    std::transform( endf.particlePairs().MT().begin(), endf.particlePairs().MT().end(),
                    reactions.begin(),
                    [&] ( int mt ) { return id::ReactionID( projectile, target, mt ); } );

    // particle pair information in the data
    auto pairs = lrf7::createParticlePairs( reactions, endf.particlePairs() );

    //! @todo look for incident pair
    dryad::resonances::ParticlePair incident;

    // q values
    auto qvalues = format::createVector( endf.particlePairs().Q() );

    // see if we have to read boundary conditions
    //! @todo for non-zero shift flag
    bool boundaries = false;

    // go over each spin group
    for ( const auto& group : endf.spinGroups() ) {

      // channels in this spin group
      auto channels = lrf7::createChannels( incident, pairs, reactions, qvalues,
                                            boundaries, group.channels() );
    }

    return groups;
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
