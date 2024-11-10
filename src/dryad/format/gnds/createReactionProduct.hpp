#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCT
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCT

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/createMultiplicity.hpp"
#include "dryad/format/gnds/createTwoBodyDistributionData.hpp"
#include "dryad/ReactionProduct.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a ReactionProduct from an GNDS product node
   */
  ReactionProduct
  createReactionProduct( const id::ParticleID& projectile, const id::ParticleID& target,
                         pugi::xml_node suite, pugi::xml_node product ) {

    throwExceptionOnWrongNode( product, "product" );
    std::string pid( product.attribute( "pid" ).as_string() );
    if ( pid == "photon" ) {

      pid = "g";
    }
    id::ParticleID id( pid );
    auto multiplicity = createMultiplicity( product.child( "multiplicity" ) );

    auto distribution = product.child( "distribution" );
    if ( distribution ) {

      auto first = distribution.first_child();
      if ( strcmp( first.name(), "angularTwoBody" ) == 0 ) {

        auto recoil = first.child( "recoil" );
        if ( ! recoil ) {

          return ReactionProduct( id, multiplicity, createTwoBodyDistributionData( first ) );
        }
      }
    }
 
    return ReactionProduct( id, multiplicity );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
