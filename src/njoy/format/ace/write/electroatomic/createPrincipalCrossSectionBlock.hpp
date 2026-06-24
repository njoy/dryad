#ifndef NJOY_FORMAT_ACE_WRITE_ELECTROATOMIC_CREATEACEPRINCIPALCROSSSECTIONBLOCK
#define NJOY_FORMAT_ACE_WRITE_ELECTROATOMIC_CREATEACEPRINCIPALCROSSSECTIONBLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/electroatomic/PrincipalCrossSectionBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
namespace electroatomic {

  /**
   *  @brief Create the principal cross section block for electroatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid electroatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] electroatomic   the electroatomic data
   */
  inline njoy::ACEtk::electroatomic::PrincipalCrossSectionBlock
  createPrincipalCrossSectionBlock( const dryad::ProjectileTarget& electroatomic ) {

    // energy is converted to MeV
    auto convertEnergy = [] ( auto&& energy ) {

      return energy * constants::micro;
    };

    // identifiers
    decltype(auto) projectile = electroatomic.projectileIdentifier();
    decltype(auto) target = electroatomic.targetIdentifier();
    dryad::id::ReactionID bremsstrahlung_id( projectile, target, dryad::id::ReactionType( projectile, 527 ) );
    dryad::id::ReactionID excitation_id( projectile, target, dryad::id::ReactionType( projectile, 528 ) );
    dryad::id::ReactionID totalionisation_id( projectile, target, dryad::id::ReactionType( projectile, 522 ) );

    // check which eprdata format we want: only total elastic or large angle and total elastic
    dryad::id::ReactionID elastic_id( projectile, target, dryad::id::ReactionType( projectile, 525 ) );
    if ( ! electroatomic.hasReaction( elastic_id ) ) {

      elastic_id = dryad::id::ReactionID( projectile, target, dryad::id::ReactionType( projectile, 526 ) );
    }

    // collect all cross section data: large angle elastic, bremsstrahlung, excitation, ionisation
    std::vector< double > energies = electroatomic.reactions().front().crossSection().energies();
    std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );

    std::vector< double > elastic = electroatomic.reaction( elastic_id ).crossSection().values();
    std::vector< double > bremsstrahlung = electroatomic.reaction( bremsstrahlung_id ).crossSection().values();

    std::vector< std::vector< double > > ionisonisation;
    for ( auto&& id : electroatomic.reaction( totalionisation_id ).partialReactionIdentifiers().value() ) {

      ionisonisation.emplace_back( electroatomic.reaction( id ).crossSection().values() );
    }

    std::vector< double > excitation = electroatomic.reaction( excitation_id ).crossSection().values();

    return njoy::ACEtk::electroatomic::PrincipalCrossSectionBlock(
               std::move( energies ), std::move( elastic ), std::move( bremsstrahlung ),
               std::move( excitation ), std::move( ionisonisation ) );
  }

} // electroatomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
