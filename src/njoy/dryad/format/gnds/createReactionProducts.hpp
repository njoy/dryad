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

      data.emplace_back( createReactionProduct( reaction, suite, product, parent, chain, normalise, style ) );

      auto node = product.child( "outputChannel" ).child( "products" );
      if ( node ) {

        auto daughters = createReactionProducts( reaction, suite, node, data.back().productIdentifier(),
                                                 chain + 1, normalise );
        data.insert( data.end(), daughters.begin(), daughters.end() );
      }
    }

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
