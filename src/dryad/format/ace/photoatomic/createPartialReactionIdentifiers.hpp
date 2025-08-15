#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEPARTIALREACTIONNUMBERS
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEPARTIALREACTIONNUMBERS

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
namespace photoatomic {

  /**
   *  @brief Create partial reaction identifiers for photoatomic data
   */
  std::vector< std::vector< id::ReactionID > >
  createPartialReactionIdentifiers( const id::ParticleID& projectile,
                                    const id::ParticleID& target,
                                    const ACEtk::PhotoatomicTable& table ) {

    std::vector< std::vector< id::ReactionID > > partials;

    // total - MT501
    partials.push_back( {} );

    // coherent scattering - MT502
    partials.push_back( {} );
    partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 502 ) );

    // incoherent scattering - MT504
    partials.push_back( {} );
    partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 504 ) );

    // pair production - MT516 (sum of MT515 and MT517)
    partials.push_back( {} );
    partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 516 ) );

    // photoelectric - MT522 (sum of MT534 and up)
    partials.push_back( {} );
    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      auto sum = partials.size() - 1;
      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // partial: subshell photoelectric - MT534 and up
        partials.push_back( {} );
        partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 534 + index - 1 ) );
        partials[sum].emplace_back( projectile, target, id::ReactionType( projectile, 534 + index - 1 ) );
      }
    }
    else {

      partials.front().emplace_back( projectile, target, id::ReactionType( projectile, 522 ) );
    }

    return partials;
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
