#ifndef NJOY_FORMAT_GNDS_READ_RESONANCES_CREATEPARTICLES
#define NJOY_FORMAT_GNDS_READ_RESONANCES_CREATEPARTICLES

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/format/gnds/read/pops/createParticleDatabase.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace resonances {

  /**
   *  @brief Create the Particle instances involved in resonance data
   *
   *  @param[in] global        the global particle data
   *  @param[in] local         the local particle data
   *  @param[in] identifiers   the particle identifiers used in the resonance data
   */
  inline std::vector< dryad::Particle >
  createParticles( const dryad::ParticleDatabase& global,
                   const dryad::ParticleDatabase& local,
                   const std::vector< dryad::id::ParticleID >& identifiers ) {

    // loop over the particle identifiers
    std::vector< dryad::Particle > particles;
    for ( const auto& id : identifiers ) {

      particles.emplace_back( global.particle( id ) );
      if ( local.hasParticle( id ) ) {

        decltype(auto) local_particle = local.particle( id );
        if ( local_particle.mass().has_value() ) {

          particles.back().mass( local_particle.mass() );
        }
        if ( local_particle.spin().has_value() ) {

          particles.back().spin( local_particle.spin() );
        }
        if ( local_particle.parity().has_value() ) {

          particles.back().parity( local_particle.parity() );
        }
      }

      particles.back().nuclearMass( std::nullopt );
      particles.back().energy( std::nullopt );
      particles.back().massUncertainty( std::nullopt );
      particles.back().nuclearMassUncertainty( std::nullopt );
      particles.back().energyUncertainty( std::nullopt );
    }

    return particles;
  }

} // resonances namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
