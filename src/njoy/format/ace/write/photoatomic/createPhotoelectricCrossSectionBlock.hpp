#ifndef NJOY_FORMAT_ACE_WRITE_PHOTOATOMIC_CREATEPHOTOELECTRICCROSSSECTIONBLOCK
#define NJOY_FORMAT_ACE_WRITE_PHOTOATOMIC_CREATEPHOTOELECTRICCROSSSECTIONBLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/photoatomic/PhotoelectricCrossSectionBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
namespace photoatomic {

  /**
   *  @brief Create the photoionisation cross section block for photoatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid photoatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] photoatomic   the photoatomic data
   */
  inline njoy::ACEtk::photoatomic::PhotoelectricCrossSectionBlock
  createPhotoelectricCrossSectionBlock( const dryad::ProjectileTarget& photoatomic ) {

    // photoatomic data is stored as log values, except when the value
    // is exactly 0 (in which case it is zero). If the value is exactly 1,
    // the final value is shifted by 1e-13 to avoid having a zero value
    // printed in the ACE file.
    auto convertValue = [] ( auto&& value ) {

      return value == 0. ? value
                         : value == 1. ? std::log( value + 1e-13 )
                                       : std::log( value );
    };

    // identifiers
    decltype(auto) projectile = photoatomic.projectileIdentifier();
    decltype(auto) target = photoatomic.targetIdentifier();
    dryad::id::ReactionID totalionisation_id( projectile, target, dryad::id::ReactionType( projectile, 522 ) );

    // collect all cross section data: partial photoionisation
    std::vector< std::vector< double > > photionisonisation;
    for ( auto&& id : photoatomic.reaction( totalionisation_id ).partialReactionIdentifiers().value() ) {

      std::vector< double > values = photoatomic.reaction( id ).crossSection().values();
      std::transform( values.begin(), values.end(), values.begin(), convertValue );
      photionisonisation.emplace_back( std::move( values ) );
    }

    return njoy::ACEtk::photoatomic::PhotoelectricCrossSectionBlock( std::move( photionisonisation ) );
  }

} // photoatomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
