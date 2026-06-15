#ifndef NJOY_FORMAT_ACE_READ_ELECTROATOMIC_CREATEPARTIALREACTIONIDENTIFIERS
#define NJOY_FORMAT_ACE_READ_ELECTROATOMIC_CREATEPARTIALREACTIONIDENTIFIERS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace electroatomic {

  /**
   *  @brief Create partial reaction identifiers for electroatomic data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   */
  inline std::vector< std::vector< dryad::id::ReactionID > >
  createPartialReactionIdentifiers( const dryad::id::ParticleID& projectile,
                                    const dryad::id::ParticleID& target,
                                    const ACEtk::PhotoatomicTable& table ) {

    std::vector< std::vector< dryad::id::ReactionID > > partials;

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      // total - MT501
      partials.push_back( {} );

      // ionisation - MT522
      partials.push_back( {} );
      if ( table.numberElectronSubshells() > 0 ) {

        for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

          // partial: subshell ionisation - MT534 and up
          partials.back().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 534 + index - 1 ) );
        }
      }
      else {

        partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 522 ) );
      }

      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // large angle elastic - MT525
        partials.push_back( {} );
        partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 525 ) );
      }

      // total elastic - MT526
      partials.push_back( {} );
      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // partial: large angle elastic - MT525
        partials.back().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 525 ) );
        // partial: elastic deficit
        partials.back().emplace_back( projectile, target, dryad::id::ReactionType( "deficit-scattering" ) );
      }
      else {

        partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 526 ) );
      }

      // bremsstrahlung - MT527
      partials.push_back( {} );
      partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 527 ) );

      // excitation - MT528
      partials.push_back( {} );
      partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 528 ) );

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell ionisation - MT534 and up
        partials.push_back( {} );
        partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 534 + index - 1 ) );
      }

      // eprdata14 and higher has large angle and total elastic -> add deficit elastic
      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // elastic deficit
        partials.push_back( {} );
        partials.front().emplace_back( projectile, target, dryad::id::ReactionType( "deficit-scattering" ) );
      }
    }

    return partials;
  }

} // electroatomic namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
