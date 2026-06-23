#ifndef NJOY_DRYAD_FORMAT_ACE_CREATEPARTICLES
#define NJOY_DRYAD_FORMAT_ACE_CREATEPARTICLES

// system includes
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Particle.hpp"
#include "njoy/constants.hpp"
#include "ENDFtk/section/1/451.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create Particle instances from an ACE table
   *
   *  Since no mass information for the projectile is available in the ACE file, it is
   *  set to std::nullopt. The mass value for the target is the AWR in neutron mass
   *  units so it must be converted to atomic mass units.
   *
   *  Particle instances are sorted in order of the particle identifier before returning
   *  the vector.
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   */
  template < typename Table > std::vector< Particle >
  createParticles( const id::ParticleID& projectile,
                   const id::ParticleID& target,
                   const Table& table ) {

    auto getAtomicWeightRatio = [] ( auto&& header ) {

      return header.atomicWeightRatio();
    };

    std::vector< Particle > particles;
    particles.emplace_back( projectile );
    particles.emplace_back( target,
                            std::visit( getAtomicWeightRatio, table.header() )
                            * constants::neutron_mass );
    std::sort( particles.begin(), particles.end(),
               [] ( auto&& left, auto&& right ) { return left.identifier() < right.identifier(); } );

    return particles;
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
