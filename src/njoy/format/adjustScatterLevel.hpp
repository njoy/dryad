#ifndef NJOY_FORMAT_ADJUSTSCATTERLEVEL
#define NJOY_FORMAT_ADJUSTSCATTERLEVEL

// system includes

// other includes
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"

namespace njoy {
namespace format {

  /**
   *  @brief Adjust the scatter level mt number for excited states
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] mt           the mt number to adjust
   */
  inline int adjustScatterLevel( const dryad::id::ParticleID& projectile,
                                 const dryad::id::ParticleID& target,
                                 int mt ) {

    if ( target.e() > 0 && projectile != dryad::id::ParticleID::photon() ) {

      int ground = dryad::id::ReactionID( projectile, target.groundState(), 2 ).reactionType().mt().value();
      int elastic = dryad::id::ReactionID( projectile, target, 2 ).reactionType().mt().value();
      if ( mt > ground && mt <= elastic ) {

        return mt - 1;
      }
    }
    return mt;
  };

} // format namespace
} // njoy namespace

#endif
