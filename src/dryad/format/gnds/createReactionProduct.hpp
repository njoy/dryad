#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCT
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCT

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
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

    std::string pid( product.attribute( "pid" ).as_string() );
    if ( pid == "photon" ) {

      pid = "g";
    }
    id::ParticleID id( pid );
    int multiplicity = 1;
 
    return ReactionProduct( id, multiplicity );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
