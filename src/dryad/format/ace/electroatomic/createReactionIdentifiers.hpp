#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONNUMBERS
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONNUMBERS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ReactionID.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create reaction identifiers for electroatomic data
   */
  std::vector< id::ReactionID >
  createReactionIdentifiers( const id::ParticleID& projectile,
                             const id::ParticleID& target,
                             const ACEtk::PhotoatomicTable& table ) {

    std::vector< id::ReactionID > identifiers;

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      // total - MT501
      identifiers.emplace_back( projectile, target, id::ReactionType( projectile, 501 ) );

      // ionisation - MT522
      identifiers.emplace_back( projectile, target, id::ReactionType( projectile, 522 ) );

      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // large angle elastic - MT525
        identifiers.emplace_back( projectile, target, id::ReactionType( projectile, 525 ) );
      }

      // total elastic - MT526
      identifiers.emplace_back( projectile, target, id::ReactionType( projectile, 526 ) );

      // bremsstrahlung - MT527
      identifiers.emplace_back( projectile, target, id::ReactionType( projectile, 527 ) );

      // excitation - MT528
      identifiers.emplace_back( projectile, target, id::ReactionType( projectile, 528 ) );

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell ionisation - MT534 and up
        identifiers.emplace_back( projectile, target, id::ReactionType( projectile, 534 + index - 1 ) );
      }

      // eprdata14 and higher has large angle and total elastic -> add deficit elastic
      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // elastic deficit
        identifiers.emplace_back( projectile, target, id::ReactionType( "deficit-scattering" ) );
      }
    }

    return identifiers;
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
