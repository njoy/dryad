#ifndef NJOY_DRYAD_FORMAT_ENDF_REACTIONPRODUCT
#define NJOY_DRYAD_FORMAT_ENDF_REACTIONPRODUCT

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/createProductIdentifier.hpp"
#include "dryad/format/endf/createTabulatedMultiplicity.hpp"
#include "dryad/ReactionProduct.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a ReactionProduct from a parsed ENDF MF6 reaction product
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] product      the MF26 reaction product data
   *  @param[in] multiple     the flag to indicate whether or not the product is a
   *                          multiple emission product
   */
  ReactionProduct
  createReactionProduct( const id::ParticleID& projectile, const id::ParticleID& target,
                         const ENDFtk::section::Type< 6 >::ReactionProduct& product,
                         bool multiple ) {


    id::ParticleID id = createProductIdentifier( product.productIdentifier(),
                                                 product.productModifierFlag(),
                                                 multiple );
    Log::info( "Reading reaction product data for \'{}\'", id );

    TabulatedMultiplicity multiplicity = createTabulatedMultiplicity( product.multiplicity() );
    return ReactionProduct( std::move( id ), std::move( multiplicity ) );
  }

  /**
   *  @brief Create a ReactionProduct from a parsed ENDF MF26 reaction product
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] product      the MF26 reaction product data
   */
  ReactionProduct
  createReactionProduct( const id::ParticleID& projectile, const id::ParticleID& target,
                         const ENDFtk::section::Type< 26 >::ReactionProduct& product ) {

    id::ParticleID id = createProductIdentifier( product.productIdentifier(), 0, false );
    Log::info( "Reading reaction product data for \'{}\'", id );

    TabulatedMultiplicity multiplicity = createTabulatedMultiplicity( product.multiplicity() );
    return ReactionProduct( std::move( id ), std::move( multiplicity ) );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
