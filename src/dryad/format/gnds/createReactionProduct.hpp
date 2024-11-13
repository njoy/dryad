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
#include "dryad/format/gnds/createUncorrelatedDistributionData.hpp"
#include "dryad/ReactionProduct.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a ReactionProduct from an GNDS product node
   */
  static ReactionProduct
  createReactionProduct( const id::ParticleID& projectile, const id::ParticleID& target,
                         pugi::xml_node suite, pugi::xml_node product,
                         const std::string& style = "eval" ) {

    // check that this is a valid product node
    throwExceptionOnWrongNode( product, "product" );

    // get the secondary particle identifier and adjust as required
    std::string pid( product.attribute( "pid" ).as_string() );
    if ( pid == "photon" ) {

      pid = "g";
    }
    id::ParticleID id( pid );
    Log::info( "Reading reaction product data for \'{}\'", id );

    // create the multiplicity
    auto multiplicity = createMultiplicity( product.child( "multiplicity" ), style );

    // get distribution
    auto distribution = product.child( "distribution" );
    if ( distribution ) {

      // get the first node of the requested style and act accordingly
      auto node = distribution.find_child_by_attribute( "label", style.c_str() );
      if ( strcmp( node.name(), "angularTwoBody" ) == 0 ) {

        // ignore recoil distributions for now
        auto recoil = node.child( "recoil" );
        if ( ! recoil ) {

          return ReactionProduct( id, multiplicity, createTwoBodyDistributionData( node ) );
        }
      }
      if ( strcmp( node.name(), "uncorrelated" ) == 0 ) {

        return ReactionProduct( id, multiplicity, createUncorrelatedDistributionData( node ) );
      }
      else {

        // for now, return a basic reaction product
        return ReactionProduct( id, multiplicity );
      }
    }

    // there is no distribution, return a basic reaction product
    return ReactionProduct( id, multiplicity );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
