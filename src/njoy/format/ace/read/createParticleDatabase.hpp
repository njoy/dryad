#ifndef NJOY_FORMAT_ACE_READ_CREATEPARTICLEDATABASE
#define NJOY_FORMAT_ACE_READ_CREATEPARTICLEDATABASE

// system includes
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/collectParticleIdentifiers.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {

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
  template < typename Table > dryad::ParticleDatabase
  createParticleDatabase( const dryad::id::ParticleID& target,
                          const std::vector< dryad::Reaction >& reactions,
                          const Table& table ) {

    dryad::ParticleDatabase particles( collectParticleIdentifiers( reactions ) );
    double mass = std::visit( [] ( auto&& header ) { return header.atomicWeightRatio(); },
                              table.header() );
    decltype(auto) entry = particles.particle( target );
    entry.mass( mass * constants::neutron_mass );
    entry.massUncertainty( std::nullopt );

    return particles;
  }

} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
