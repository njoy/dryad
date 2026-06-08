#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPARTICLES
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPARTICLES

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Particle.hpp"
#include "njoy/constants.hpp"
#include "ENDFtk/section/1/451.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create Particle instances from a parsed MF1 MT451 section
   *
   *  @param[in] projectile    the projectile identifier
   *  @param[in] target        the target identifier
   *  @param[in] information   the parsed MF1 MT451 section
   */
  inline std::vector< Particle >
  createParticles( const id::ParticleID& projectile,
                   const id::ParticleID& target,
                   const ENDFtk::section::Type< 1, 451 >& information ) {

    std::vector< Particle > particles;
    particles.emplace_back( projectile,
                            information.projectileAtomicMassRatio() * constants::neutron_mass,
                            std::nullopt,
                            std::nullopt,
                            std::nullopt );
    particles.emplace_back( target,
                            information.atomicWeightRatio() * constants::neutron_mass,
                            std::nullopt,
                            std::nullopt,
                            information.excitationEnergy() );
    std::sort( particles.begin(), particles.end(),
               [] ( auto&& left, auto&& right ) { return left.identifier() < right.identifier(); } );

    return particles;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
