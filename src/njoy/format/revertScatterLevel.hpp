#ifndef NJOY_FORMAT_READJUSTSCATTERLEVEL
#define NJOY_FORMAT_READJUSTSCATTERLEVEL

// system includes

// other includes
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"

namespace njoy {
namespace format {

  /**
   *  @brief Revert the scatter level mt number when required
   *
   *  Internally, we use MT50, MT600, etc. for the elastic reaction instead of MT2.
   *  For excited states we need to upshift all levels below the excited state back to
   *  their original MT number.
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] mt           the mt number to adjust
   */
  inline int revertScatterLevel( const dryad::id::ParticleID& projectile,
                                 const dryad::id::ParticleID& target,
                                 int mt ) {

    int elastic = dryad::id::ReactionID( projectile, target, 2 ).reactionType().mt().value();
    if ( target.e() > 0 && projectile != dryad::id::ParticleID::photon() ) {

      int ground = dryad::id::ReactionID( projectile, target.groundState(), 2 ).reactionType().mt().value();
      if ( mt >= ground && mt < elastic ) {

        return mt + 1;
      }
    }

    if ( mt == elastic ) {

      mt = 2;
    }

    return mt;
  };

} // format namespace
} // njoy namespace

#endif
