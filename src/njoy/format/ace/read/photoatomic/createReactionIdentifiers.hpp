#ifndef NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATEREACTIONIDENTIFIERS
#define NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATEREACTIONIDENTIFIERS

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
   *  @brief Create reaction identifiers for photoatomic data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   */
  inline std::vector< dryad::id::ReactionID >
  createReactionIdentifiers( const dryad::id::ParticleID& projectile,
                             const dryad::id::ParticleID& target,
                             const ACEtk::PhotoatomicTable& table ) {

    std::vector< dryad::id::ReactionID > numbers;

    // total - MT501
    numbers.emplace_back( projectile, target, dryad::id::ReactionType( projectile, 501 ) );

    // coherent scattering - MT502
    numbers.emplace_back( projectile, target, dryad::id::ReactionType( projectile, 502 ) );

    // incoherent scattering - MT504
    numbers.emplace_back( projectile, target, dryad::id::ReactionType( projectile, 504 ) );

    // pair production - MT516 (sum of MT515 and MT517)
    numbers.emplace_back( projectile, target, dryad::id::ReactionType( projectile, 516 ) );

    // photoelectric - MT522 (sum of MT534 and up)
    numbers.emplace_back( projectile, target, dryad::id::ReactionType( projectile, 522 ) );

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell photoelectric - MT534 and up
        numbers.emplace_back( projectile, target, dryad::id::ReactionType( projectile, 534 + index - 1 ) );
      }
    }

    return numbers;
  }

} // photoatomic namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
