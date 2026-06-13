#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPARTICLES
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPARTICLES

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/dryad/format/collectParticleIdentifiers.hpp"
#include "njoy/constants.hpp"
#include "ENDFtk/section/1/451.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a ParticleDatabase
   *
   *  The projectile and target mass values are available in MF1 MT451 but they are in
   *  in neutron mass units so it must be converted to atomic mass units.
   *
   *  @param[in] projectile    the projectile identifier
   *  @param[in] target        the target identifier
   *  @param[in] information   the parsed MF1 MT451 section
   */
  inline ParticleDatabase
  createParticleDatabase( const id::ParticleID& projectile,
                          const id::ParticleID& target,
                          const std::vector< Reaction >& reactions,
                          const ENDFtk::section::Type< 1, 451 >& information,
                          std::map< id::ParticleID, double >& masses ) {

    ParticleDatabase particles( collectParticleIdentifiers( reactions ) );

    // update the mass of the projectile
    decltype(auto) projectile_entry = particles.particle( projectile );
    projectile_entry.mass( information.projectileAtomicMassRatio() * constants::neutron_mass );
    projectile_entry.massUncertainty( std::nullopt );

    // update the mass of the target
    decltype(auto) target_entry = particles.particle( target );
    target_entry.mass( information.atomicWeightRatio() * constants::neutron_mass );
    target_entry.massUncertainty( std::nullopt );
    if ( target.a() != 0 ) {

      target_entry.energy( information.excitationEnergy() );
      target_entry.energyUncertainty( std::nullopt );
    }

    // update the mass for products that were in MF6
    masses[ target.groundState() ] = target_entry.mass().value();
    for ( auto& entry : particles.particles() ) {

      if ( entry.identifier() != projectile && entry.identifier() != target ) {

        auto iter = masses.find( entry.identifier().groundState() );
        if ( iter != masses.end() ) {

          entry.mass( iter->second );
          entry.massUncertainty( std::nullopt );
        }
      }
    }

    return particles;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
