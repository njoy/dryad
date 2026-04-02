#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEPARTICLEPAIRS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEPARTICLEPAIRS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/resonances/ParticlePair.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createReactionIdentifiers.hpp"
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
   *  @param[in] endfPairs    the parsed ENDF particle pairs
   */
  inline auto createParticlePairs(
                  const id::ParticleID& projectile,
                  const id::ParticleID& target,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& endfPairs ) {

    std::vector< std::optional< dryad::resonances::ParticlePair > > pairs;

    auto reactions = lrf7::createReactionIdentifiers( projectile, target, endfPairs );
    for ( unsigned int i = 0; i < endfPairs.numberParticlePairs(); ++i ) {

      if ( reactions[i].particles().has_value() ) {

        // an empty particles map means there's only photons
        auto id = reactions[i].particles()->size() > 0 ? reactions[i].particles()->begin()->first
                                                       : dryad::id::ParticleID::photon();
        dryad::Particle a( id,
                           endfPairs.massParticleA()[i] * constants::neutron_mass,
                           std::abs( endfPairs.spinParticleA()[i] ),
                           endfPairs.spinParticleA()[i] == 0.
                             ? endfPairs.parityParticleA()[i] >= 0 ? +1 : -1
                             : endfPairs.spinParticleA()[i] >= 0 ? +1 : -1 );
        dryad::Particle b( reactions[i].residual().value(),
                           endfPairs.massParticleB()[i] * constants::neutron_mass,
                           std::abs( endfPairs.spinParticleB()[i] ),
                           endfPairs.spinParticleB()[i] == 0.
                             ? endfPairs.parityParticleB()[i] >= 0 ? +1 : -1
                             : endfPairs.spinParticleB()[i] >= 0 ? +1 : -1 );
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
