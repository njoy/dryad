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
   *  The projectile and target mass values are available in MF1 MT451 but they are in
   *  in neutron mass units so it must be converted to atomic mass units.
   *
   *  Particle instances are sorted in order of the particle identifier before returning
   *  the vector.
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

    // add projectile default data and override mass and uncertainty
    particles.emplace_back( Particle::defaultParticle( projectile ) );
    particles.back().mass( information.projectileAtomicMassRatio() * constants::neutron_mass );
    particles.back().massUncertainty( std::nullopt );

    // add target default data and override mass, energy and uncertainties
    particles.emplace_back( Particle::defaultParticle( target ) );
    particles.back().mass( information.atomicWeightRatio() * constants::neutron_mass );
    particles.back().massUncertainty( std::nullopt );
    if ( target.a() != 0 ) {

      particles.back().energy( information.excitationEnergy() );
      particles.back().energyUncertainty( std::nullopt );
    }

    // sort for later searching
    std::sort( particles.begin(), particles.end(),
               [] ( auto&& left, auto&& right ) { return left.identifier() < right.identifier(); } );

    return particles;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
