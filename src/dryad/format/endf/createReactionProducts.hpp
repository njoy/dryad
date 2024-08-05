#ifndef NJOY_DRYAD_FORMAT_ENDF_REACTIONPRODUCTS
#define NJOY_DRYAD_FORMAT_ENDF_REACTIONPRODUCTS

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
   *  @brief Create a Reaction from an unparsed ENDF material
   */
  std::vector< ReactionProduct >
  createReactionProducts( const id::ParticleID& projectile, const id::ParticleID& target,
                          const ENDFtk::tree::Material& material, int mt ) {

    std::vector< ReactionProduct > products;

    if ( material.hasSection( 4, mt ) ) {

      Log::info( "Reading reaction product information from MF4 is not implemented yet" );
    }
    else if ( material.hasSection( 6, mt ) ) {

      auto section = material.section( 6, mt ).parse< 6 >();
      for ( const auto& product : section.reactionProducts() ) {

        id::ParticleID id = createProductIdentifier( product.productIdentifier() );
        Log::info( "Reading reaction product for \'{}\'", id );

        TabulatedMultiplicity multiplicity = createTabulatedMultiplicity( product.multiplicity(), mt );
        products.emplace_back( std::move( id ), std::move( multiplicity ) );
      }
    }
    else if ( material.hasSection( 26, mt ) ) {

      auto section = material.section( 26, mt ).parse< 26 >();
      for ( const auto& product : section.reactionProducts() ) {

        id::ParticleID id = createProductIdentifier( product.productIdentifier() );
        Log::info( "Reading reaction product for \'{}\'", id );

        TabulatedMultiplicity multiplicity = createTabulatedMultiplicity( product.multiplicity(), mt );
        products.emplace_back( std::move( id ), std::move( multiplicity ) );
      }
    }
    else {

      Log::error( "The material does not have reaction products for MT{}", mt );
      throw std::exception();
    }

    // std::sort( products.begin(), products.end(),
    //            [] ( auto&& left, auto&& right )
    //               { return left.identifier() < right.identifier(); } );
    return products;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
