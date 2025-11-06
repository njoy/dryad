#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEREACTIONIDENTIFIERS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEREACTIONIDENTIFIERS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
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
                  const id::ParticleID& projectile,
                  const id::ParticleID& target,
                  const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& endfPairs ) {

    std::vector< id::ReactionID > reactions;
    for ( const auto& mt : endfPairs.MT() ) {

      reactions.emplace_back( projectile, target, mt );
    }
    return reactions;
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
