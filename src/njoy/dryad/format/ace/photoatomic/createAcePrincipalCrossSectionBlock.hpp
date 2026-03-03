#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEPRINCIPALCROSSSECTIONBLOCK
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEPRINCIPALCROSSSECTIONBLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/photoatomic/PrincipalCrossSectionBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create the principal cross section block for photoatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid photoatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] photoatomic   the photoatomic data
   */
  inline njoy::ACEtk::photoatomic::PrincipalCrossSectionBlock
  createAcePrincipalCrossSectionBlock( const ProjectileTarget& photoatomic ) {

    // energy is converted to MeV

    // photoatomic data is stored as log values, except when the value
    // is exactly 0 (in which case it is zero). If the value is exactly 1,
    // the final value is shifted by 1e-13 to avoid having a zero value
    // (this practice in found in older eprdata files)
    auto convertValue = [] ( auto&& value ) {

      return value == 0. ? value
                         : value == 1. ? std::log( value + 1e-13 )
                                       : std::log( value );
    };
    auto convertEnergy = [&] ( auto&& energy ) {

      return convertValue( energy * constants::micro );
    };

    // identifiers
    decltype(auto) projectile = photoatomic.projectileIdentifier();
    decltype(auto) target = photoatomic.targetIdentifier();
    dryad::id::ReactionID incoherent_id( projectile, target, dryad::id::ReactionType( projectile, 504 ) );
    dryad::id::ReactionID coherent_id( projectile, target, dryad::id::ReactionType( projectile, 502 ) );
    dryad::id::ReactionID pairproduction_id( projectile, target, dryad::id::ReactionType( projectile, 516 ) );
    dryad::id::ReactionID totalionisation_id( projectile, target, dryad::id::ReactionType( projectile, 522 ) );

    // collect all cross section data: incoherent, coherent, photoelectric and photoionisation
    std::vector< double > energies = photoatomic.reactions().front().crossSection().energies();
    std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );

    std::vector< double > incoherent = photoatomic.reaction( incoherent_id ).crossSection().values();
    std::transform( incoherent.begin(), incoherent.end(), incoherent.begin(), convertValue );

    std::vector< double > coherent = photoatomic.reaction( coherent_id ).crossSection().values();
    std::transform( coherent.begin(), coherent.end(), coherent.begin(), convertValue );

    std::vector< double > totalionisation = photoatomic.reaction( totalionisation_id ).crossSection().values();
    std::transform( totalionisation.begin(), totalionisation.end(), totalionisation.begin(), convertValue );

    std::vector< double > pairproduction = photoatomic.reaction( pairproduction_id ).crossSection().values();
    std::transform( pairproduction.begin(), pairproduction.end(), pairproduction.begin(), convertValue );

    return njoy::ACEtk::photoatomic::PrincipalCrossSectionBlock(
               std::move( energies ), std::move( incoherent ), std::move( coherent ),
               std::move( totalionisation ), std::move( pairproduction ) );
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
