#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCTS
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCTS

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/format/gnds/createReactionProduct.hpp"
#include "njoy/dryad/ReactionProduct.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Add a placeholder reaction product if it is not present yet
   *
   *  @param[in] particle        the particle identifier
   *  @param[in] multiplicity    the multiplicity of the target
   *  @param[in, out] products   the current set of reaction products
   */
  inline void addProduct( const id::ParticleID& particle, int multiplicity,
                          std::vector< ReactionProduct >& products ) {

    auto iter = std::find_if( products.begin(), products.end(),
                              [&particle] ( auto&& product )
                                          { return product.productIdentifier() == particle &&
                                                   product.chainIndex() == 0; } );
    if ( iter == products.end() ) {

      Log::info( "Adding '{}' as an expected reaction product", particle.symbol() );
      products.emplace_back( particle, multiplicity );
    }
  }

  /**
   *  @brief Create a Reaction from a GNDS products node
   *
   *  @param[in] reaction     the reaction identifier
   *  @param[in] suite        the gnds xml reaction suite
   *  @param[in] products     the gnds xml products suite
   *  @param[in] parent       the parent reaction product
   *  @param[in] chain        the current chain index
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   *  @param[in] style        the gnds style to process (default is eval)
   */
  inline std::vector< ReactionProduct >
  createReactionProducts( const id::ReactionID& reaction,
                          pugi::xml_node suite,
                          pugi::xml_node products,
                          std::optional< id::ParticleID > parent,
                          std::size_t chain,
                          bool normalise,
                          const std::string& style = "eval" ) {

    // check that this is a valid products node
    throwExceptionOnWrongNode( products, "products" );

    // loop over product children
    std::vector< ReactionProduct > data;
    for ( pugi::xml_node product = products.child( "product" ); product;
          product = product.next_sibling( "product" ) ) {

      // add the current product
      data.emplace_back( createReactionProduct( reaction, suite, product, parent, chain, normalise, style ) );

      // look for higher chain products with this product as a parent
      auto node = product.child( "outputChannel" ).child( "products" );
      if ( node ) {

        auto daughters = createReactionProducts( reaction, suite, node, data.back().productIdentifier(),
                                                 chain + 1, normalise );
        data.insert( data.end(), daughters.begin(), daughters.end() );
      }
    }

    // add missing expected reaction products
    if ( chain == 0 && reaction.particles().has_value() ) {

      if ( reaction.particles()->size() == 0 ) {

        // add photons as an expected reaction product
        addProduct( id::ParticleID::photon(), 1, data );
      }
      else {

        // add all expected reaction products
        for ( const auto& pair : reaction.particles().value() ) {

          addProduct( pair.first, pair.second, data );
        }
      }
    }

    // add the residual if it is not there yet
    if ( chain == 0 && reaction.residual().has_value() ) {

      addProduct( reaction.residual().value(), 1, data );
    }

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
