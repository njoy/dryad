#ifndef NJOY_DRYAD_FORMAT_ACE_CREATEPARTICLES
#define NJOY_DRYAD_FORMAT_ACE_CREATEPARTICLES

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
namespace ace {

  /**
   *  @brief Create Particle instances from an ACE table
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

    return particles;
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
