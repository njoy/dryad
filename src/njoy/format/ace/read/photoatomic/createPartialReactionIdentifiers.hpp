#ifndef NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATEPARTIALREACTIONIDENTIFIERS
#define NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATEPARTIALREACTIONIDENTIFIERS

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
namespace photoatomic {

  /**
   *  @brief Create partial reaction identifiers for photoatomic data
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

    // total - MT501
    partials.push_back( {} );

    // coherent scattering - MT502
    partials.push_back( {} );
    partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 502 ) );

    // incoherent scattering - MT504
    partials.push_back( {} );
    partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 504 ) );

    // pair production - MT516 (sum of MT515 and MT517)
    partials.push_back( {} );
    partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 516 ) );

    // photoelectric - MT522 (sum of MT534 and up)
    partials.push_back( {} );
    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      auto sum = partials.size() - 1;
      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // partial: subshell photoelectric - MT534 and up
        partials.push_back( {} );
        partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 534 + index - 1 ) );
        partials[sum].emplace_back( projectile, target, dryad::id::ReactionType( projectile, 534 + index - 1 ) );
      }
    }
    else {

      partials.front().emplace_back( projectile, target, dryad::id::ReactionType( projectile, 522 ) );
    }

    return partials;
  }

} // photoatomic namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
