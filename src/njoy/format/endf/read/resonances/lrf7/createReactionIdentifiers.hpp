#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATEREACTIONIDENTIFIERS
#define NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATEREACTIONIDENTIFIERS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the reaction identifiers
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] endfPairs    the parsed ENDF particle pairs
   */
  inline auto createReactionIdentifiers(
                  const dryad::id::ParticleID& projectile,
                  const dryad::id::ParticleID& target,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& endfPairs ) {

    std::vector< dryad::id::ReactionID > reactions;
    for ( const auto& mt : endfPairs.MT() ) {

      reactions.emplace_back( projectile, target, mt );
    }
    return reactions;
  }

} // lrf7 namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
