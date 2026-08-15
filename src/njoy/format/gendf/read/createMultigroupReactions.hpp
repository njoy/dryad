#ifndef NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPREACTIONS
#define NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPREACTIONS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/MultigroupReaction.hpp"
#include "njoy/dryad/MultigroupAverageCosine.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/ReactionInformation.hpp"
#include "njoy/format/gendf/read/createMultigroupReaction.hpp"
#include "ENDFtk/GMaterial.hpp"
#include "ENDFtk/tree/GMaterial.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {

  /**
   *  @brief Create every MultigroupReaction from an unparsed GENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] material     the unparsed GENDF material
   *  @param[in] boundaries   the energy group boundaries
   *  @param[in] dilution     the dilution index to read
   */
  inline std::vector< dryad::MultigroupReaction >
  createMultigroupReactions( const dryad::id::ParticleID& projectile,
                             const dryad::id::ParticleID& target,
                             const ENDFtk::tree::GMaterial& material,
                             const std::vector< double >& boundaries,
                             std::size_t dilution ) {

    std::vector< dryad::MultigroupReaction > reactions;
    if ( material.hasFile( 3 ) ) {

      // loop over the available reactions and create the reaction objects
      reactions.reserve( material.file( 3 ).sectionNumbers().size() );
      for ( auto mt : material.file( 3 ).sectionNumbers() ) {

        if ( ! endf::ReactionInformation::isDerived( mt ) ) {

          reactions.emplace_back( createMultigroupReaction( projectile, target, material, mt, boundaries, dilution ) );

          if ( mt == 2 && material.hasSection( 3, 251 ) ) {

            Log::info( "Reading average cosine data for MT251" );
            auto section = material.section( 3, 251 ).parse< 3 >();
            auto cosines = createVector( section.ratio( 0, dilution ) );
            dryad::MultigroupAverageCosine average( boundaries, std::move( cosines ) );
            reactions.back().product( projectile ).averageCosine( std::move( average ) );
          }
        }
        else {

          Log::warning( "Skipping data for derived MT{}", mt );
        }
      }

      // sort by MT
      std::sort( reactions.begin(), reactions.end(),
                 [] ( auto&& left, auto&&right )
                    { return left.identifier().reactionType().mt()
                             < right.identifier().reactionType().mt(); } );

      reactions.shrink_to_fit();
    }

    return reactions;
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
