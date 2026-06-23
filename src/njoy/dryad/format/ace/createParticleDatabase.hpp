#ifndef NJOY_DRYAD_FORMAT_ACE_CREATEPARTICLES
#define NJOY_DRYAD_FORMAT_ACE_CREATEPARTICLES

// system includes
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/dryad/format/collectParticleIdentifiers.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create the ParticleDatabase from an ACE table
   *
   *  Since no mass information for the projectile is available in the ACE file, it is
   *  set to std::nullopt. The mass value for the target is the AWR in neutron mass
   *  units so it must be converted to atomic mass units.
   *
   *  Particle instances are sorted in order of the particle identifier before returning
   *  the vector.
   *
   *  @param[in] target       the target identifier
   *  @param[in] reactions    the reactions defined in the ace table
   *  @param[in] table        the ace table
   */
  template < typename Table > ParticleDatabase
  createParticleDatabase( const id::ParticleID& target,
                          const std::vector< Reaction >& reactions,
                          const Table& table ) {

    ParticleDatabase particles( collectParticleIdentifiers( reactions ) );
    double mass = std::visit( [] ( auto&& header ) { return header.atomicWeightRatio(); },
                              table.header() );
    decltype(auto) entry = particles.particle( target );
    entry.mass( mass * constants::neutron_mass );
    entry.massUncertainty( std::nullopt );

    return particles;
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
