#ifndef NJOY_DRYAD_FORMAT_ACE_CREATEPARTICLEDATABASE
#define NJOY_DRYAD_FORMAT_ACE_CREATEPARTICLEDATABASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/constants.hpp"
#include "ENDFtk/section/1/451.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a ParticleDatabase instance from an ACE table
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   */
  template < typename Table > ParticleDatabase
  createParticleDatabase( const id::ParticleID& projectile,
                          const id::ParticleID& target,
                          const Table& table ) {

    Log::info( "Initialising particle database" );

    auto getAtomicWeightRatio = [] ( auto&& header ) {

      return header.atomicWeightRatio();
    };

    std::vector< Particle > particles;
    particles.emplace_back( projectile );
    particles.emplace_back( target,
                            std::visit( getAtomicWeightRatio, table.header() )
                            * constants::neutron_mass );

    return ParticleDatabase( std::move( particles ) );
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
