#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEACEEXCITATIONBLOCK
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEACEEXCITATIONBLOCK

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/electroatomic/ExcitationBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create the excitation energy loss block for electroatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid electroatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] electroatomic   the electroatomic data
   */
  inline njoy::ACEtk::electroatomic::ExcitationBlock
  createAceExcitationBlock( const ProjectileTarget& electroatomic ) {

    // identifiers
    decltype(auto) projectile = electroatomic.projectileIdentifier();
    decltype(auto) target = electroatomic.targetIdentifier();
    dryad::id::ReactionID excitation_id( projectile, target, dryad::id::ReactionType( projectile, 528 ) );

    decltype(auto) excitation = electroatomic.reaction( excitation_id );
    decltype(auto) electron = excitation.product( dryad::id::ParticleID::electron() ).averageEnergy().value();

    std::vector< double > energies = electron.energies();
    std::vector< double > values = electron.values();
    std::transform( energies.begin(), energies.end(), values.begin(), values.begin(),
                    [] ( auto&& incident, auto&& average ) { return ( incident - average ) * constants::micro; } );
    std::transform( energies.begin(), energies.end(), energies.begin(),
                    [] ( auto&& incident ) { return incident * constants::micro; } );

    return njoy::ACEtk::electroatomic::ExcitationBlock( std::move( energies ), std::move( values ) );
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
