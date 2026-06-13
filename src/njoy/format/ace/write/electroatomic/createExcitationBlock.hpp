#ifndef NJOY_FORMAT_ACE_WRITE_ELECTROATOMIC_CREATEACEEXCITATIONBLOCK
#define NJOY_FORMAT_ACE_WRITE_ELECTROATOMIC_CREATEACEEXCITATIONBLOCK

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/electroatomic/ExcitationBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
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
  createExcitationBlock( const dryad::ProjectileTarget& electroatomic ) {

    // energy is converted to MeV
    auto convertEnergy = [] ( auto&& energy ) {

      return energy * constants::micro;
    };

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
    std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );

    return njoy::ACEtk::electroatomic::ExcitationBlock( std::move( energies ), std::move( values ) );
  }

} // electroatomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
