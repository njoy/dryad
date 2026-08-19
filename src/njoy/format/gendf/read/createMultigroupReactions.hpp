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
   *  @param[in] projectile            the projectile identifier
   *  @param[in] target                the target identifier
   *  @param[in] material              the unparsed GENDF material (main groupr file)
   *  @param[in] covariances_xs        the optional unparsed xs covariances material (errorr file)
   *  @param[in] covariances_angular   the optional unparsed angular covariances material (errorr file)
   *  @param[in] boundaries            the energy group boundaries
   *  @param[in] dilution              the dilution index to read
   */
  inline std::vector< dryad::MultigroupReaction >
  createMultigroupReactions( const dryad::id::ParticleID& projectile,
                             const dryad::id::ParticleID& target,
                             const ENDFtk::tree::GMaterial& material,
                             const std::optional< ENDFtk::tree::GMaterial >& covariances_xs,
                             const std::optional< ENDFtk::tree::GMaterial >& covariances_angular,
                             const std::vector< double >& boundaries,
                             std::size_t dilution ) {

    std::vector< dryad::MultigroupReaction > reactions;

    // get all reactions from the main gendf file
    if ( material.hasFile( 3 ) ) {

      // loop over the available reactions and create the reaction objects
      reactions.reserve( material.file( 3 ).sectionNumbers().size() );
      for ( auto mt : material.file( 3 ).sectionNumbers() ) {

        if ( ! endf::ReactionInformation::isDerived( mt ) ) {

          reactions.emplace_back( createMultigroupReaction( projectile, target, material, mt, boundaries, dilution ) );
        }
        else {

          Log::warning( "Skipping data for derived MT{}", mt );
        }
      }
    }

    // add lumped covariance reactions
    if ( covariances_xs.has_value() && covariances_xs->hasFile( 3 ) ) {

      for ( auto mt : covariances_xs->file( 3 ).sectionNumbers() ) {

        if ( endf::ReactionInformation::isLumpedCovariance( mt ) ) {

          reactions.emplace_back( createMultigroupReaction( projectile, target, covariances_xs.value(), mt, boundaries, 0 ) );
        }
      }
    }

    // sort by MT
    std::sort( reactions.begin(), reactions.end(),
               [] ( auto&& left, auto&&right )
                  { return left.identifier().reactionType().mt()
                           < right.identifier().reactionType().mt(); } );
    reactions.shrink_to_fit();

    return reactions;
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
