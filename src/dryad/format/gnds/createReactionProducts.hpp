#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCTS
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCTS

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createReactionProduct.hpp"
#include "dryad/ReactionProduct.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a Reaction from a GNDS products node
   */
  static std::vector< ReactionProduct >
  createReactionProducts( const id::ParticleID& projectile, const id::ParticleID& target,
                          pugi::xml_node suite, pugi::xml_node products,
                         const std::string& style = "eval" ) {

    // check that this is a valid products node
    throwExceptionOnWrongNode( products, "products" );

    // loop over product children
    std::vector< ReactionProduct > data;
    for ( pugi::xml_node product = products.child( "product" ); product; 
          product = product.next_sibling( "product" ) ) {

      data.emplace_back( createReactionProduct( projectile, target, suite, product, style ) );
    }

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
