#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEPARTICLEPAIRS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEPARTICLEPAIRS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/constants.hpp"
#include "dryad/id/ReactionID.hpp"
#include "dryad/resonances/ParticlePair.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the particle pairs
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] awr    the atomic weight ratio as given in the ENDF file
   */
  auto createParticlePairs(
           const id::ParticleID& projectile,
           const id::ParticleID& target,
           const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& endfPairs ) {

    std::vector< std::optional< dryad::resonances::ParticlePair > > pairs;
    for ( unsigned int i = 0; i < endfPairs.numberParticlePairs(); ++i ) {

      id::ReactionID reaction( projectile, target, endfPairs.MT()[i] );
      if ( reaction.particles().has_value() ) {

        // an empty particles map means there's only photons
        auto id = reaction.particles()->size() > 0 ? reaction.particles()->begin()->first
                                                   : dryad::id::ParticleID::photon();
        dryad::resonances::Particle a( id,
                                       endfPairs.massParticleA()[i] * constants::neutron_mass,
                                       endfPairs.spinParticleA()[i],
                                       endfPairs.spinParticleA()[i] == 0.
                                         ? endfPairs.parityParticleA()[i] >= 0 ? +1 : -1
                                         : endfPairs.spinParticleA()[i] > 0 ? +1 : -1 );
        dryad::resonances::Particle b( reaction.residual().value(),
                                       endfPairs.massParticleB()[i] * constants::neutron_mass,
                                       endfPairs.spinParticleB()[i],
                                       endfPairs.spinParticleB()[i] == 0.
                                         ? endfPairs.parityParticleB()[i] >= 0 ? +1 : -1
                                         : endfPairs.spinParticleB()[i] > 0 ? +1 : -1 );
        pairs.emplace_back( dryad::resonances::ParticlePair( std::move( a ), std::move( b ) ) );

        //! @todo compare spins and parity to particle database to detect errors
        //! @todo compare charge values in endf particle pairs to detect errors
      }
      else {

        pairs.emplace_back( std::nullopt );
      }
    }
    return pairs;
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
