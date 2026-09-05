#ifndef NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPREACTION
#define NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPREACTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/MultigroupReaction.hpp"
#include "njoy/format/adjustScatterLevel.hpp"
#include "njoy/format/ndi/read/createMultigroupCrossSection.hpp"
#include "NDItk/MultigroupLibrary.hpp"

namespace njoy {
namespace format {
namespace ndi {
namespace read {

  /**
   *  @brief Create a MultigroupReaction from an NDI table
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the NDI multigroup table
   *  @param[in] mt           the MT number to process
   *  @param[in] boundaries   the energy group boundaries
   */
  inline dryad::MultigroupReaction
  createMultigroupReaction( const dryad::id::ParticleID& projectile,
                            const dryad::id::ParticleID& target,
                            const NDItk::MultigroupTable& table,
                            int mt,
                            const std::vector< double >& boundaries ) {

    // metadata and miscellaneous information
    dryad::id::ReactionID id( projectile, target, adjustScatterLevel( projectile, target, mt ) );
    Log::info( "Reading data for \'{}\' - MT{}", id.symbol(), mt );

    if ( table.reactionCrossSections().hasReaction( mt ) ) {

      // cross section
      decltype(auto) subrecord = table.reactionCrossSections().reaction( mt );
      dryad::MultigroupCrossSection xs = createMultigroupCrossSection( boundaries, subrecord );

      // q value
      std::optional< double > qValue = subrecord.qvalue() * constants::mega;

      // return the reaction
      return dryad::MultigroupReaction( std::move( id ), std::move( xs ), {},
                                        std::nullopt, std::move( qValue ) );
    }
    else {

        Log::error( "{} is not an MT number that designates a valid reaction", mt );
      throw std::exception();
    }
  }

} // read namespace
} // ndi namespace
} // format namespace
} // njoy namespace

#endif
