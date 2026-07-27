#ifndef NJOY_FORMAT_ENDF_READ_CREATEPARTICLEDATABASE
#define NJOY_FORMAT_ENDF_READ_CREATEPARTICLEDATABASE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/format/collectParticleIdentifiers.hpp"
#include "njoy/constants.hpp"
#include "ENDFtk/section/1/451.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a ParticleDatabase
   *
   *  The projectile and target mass values are available in MF1 MT451 but they are in
   *  in neutron mass units so it must be converted to atomic mass units.
   *
   *  @param[in] projectile    the projectile identifier
   *  @param[in] target        the target identifier
   *  @param[in] reactions     the reactions
   *  @param[in] information   the parsed MF1 MT451 section
   *  @param[in] masses        the atomic mass values read from the ENDF file
   */
  inline dryad::ParticleDatabase
  createParticleDatabase( const dryad::id::ParticleID& projectile,
                          const dryad::id::ParticleID& target,
                          const std::vector< dryad::Reaction >& reactions,
                          const ENDFtk::section::Type< 1, 451 >& information,
                          const std::map< dryad::id::ParticleID, double >& masses ) {

    dryad::ParticleDatabase particles( collectParticleIdentifiers( reactions ) );

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
    for ( auto& entry : particles.particles() ) {

      if ( entry.identifier() != projectile && entry.identifier() != target ) {

        if ( entry.identifier().groundState() == target.groundState() ) {

          entry.mass( target_entry.mass().value() );
          entry.massUncertainty( std::nullopt );
        }
        else {

          auto iter = masses.find( entry.identifier().groundState() );
          if ( iter != masses.end() ) {

            entry.mass( iter->second );
            entry.massUncertainty( std::nullopt );
          }
        }
      }
    }

    return particles;
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
