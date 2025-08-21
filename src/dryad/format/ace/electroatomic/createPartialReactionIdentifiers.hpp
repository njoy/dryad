#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPARTIALREACTIONNUMBERS
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPARTIALREACTIONNUMBERS

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
   *  @brief Create partial reaction identifiers for electroatomic data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   */
  std::vector< std::vector< id::ReactionID > >
  createPartialReactionIdentifiers( const id::ParticleID& projectile,
                                    const id::ParticleID& target,
                                    const ACEtk::PhotoatomicTable& table ) {

    std::vector< std::vector< id::ReactionID > > partials;
    auto e = id::ParticleID::electron();

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      // total - MT501
      partials.push_back( {} );

      // ionisation - MT522
      partials.push_back( {} );
      if ( table.numberElectronSubshells() > 0 ) {

        for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

          // partial: subshell ionisation - MT534 and up
          partials.back().emplace_back( projectile, target, id::ReactionType( projectile, 534 + index - 1 ) );
        }
      }
      else {

        partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 522 ) );
      }

      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // large angle elastic - MT525
        partials.push_back( {} );
        partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 525 ) );
      }

      // total elastic - MT526
      partials.push_back( {} );
      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // partial: large angle elastic - MT525
        partials.back().emplace_back( projectile, target, id::ReactionType( projectile, 525 ) );
        // partial: elastic deficit
        partials.back().emplace_back( projectile, target, id::ReactionType( "deficit-scattering" ) );
      }
      else {

        partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 526 ) );
      }

      // bremsstrahlung - MT527
      partials.push_back( {} );
      partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 527 ) );

      // excitation - MT528
      partials.push_back( {} );
      partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 528 ) );

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell ionisation - MT534 and up
        partials.push_back( {} );
        partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 534 + index - 1 ) );
      }

      // eprdata14 and higher has large angle and total elastic -> add deficit elastic
      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // elastic deficit
        partials.push_back( {} );
        partials.front().emplace_back( projectile, target, id::ReactionType( "deficit-scattering" ) );
      }
    }

    return partials;
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
