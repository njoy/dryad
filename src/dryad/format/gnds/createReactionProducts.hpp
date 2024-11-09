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
   *  @brief Create a Reaction from an unparsed ENDF material
   */
  std::vector< ReactionProduct >
  createReactionProducts( const id::ParticleID& projectile, const id::ParticleID& target,
                          pugi::xml_node suite, pugi::xml_node data ) {

    std::vector< ReactionProduct > products;
    for ( pugi::xml_node product = data.child( "product" ); product; 
          product = product.next_sibling( "product" ) ) {

      products.emplace_back( createReactionProduct( projectile, target, suite, product ) );
    }

    return products;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
