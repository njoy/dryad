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

    std::vector< Particle > particles;

    // add projectile default data
    particles.emplace_back( Particle::defaultParticle( projectile ) );

    // add target default data and override mass and uncertainty
    particles.emplace_back( Particle::defaultParticle( target ) );
    double mass = std::visit( [] ( auto&& header ) { return header.atomicWeightRatio(); },
                              table.header() );
    particles.back().mass( mass * constants::neutron_mass );
    particles.back().massUncertainty( std::nullopt );

    // sort for later searching
    std::sort( particles.begin(), particles.end(),
               [] ( auto&& left, auto&& right ) { return left.identifier() < right.identifier(); } );

    return particles;
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
