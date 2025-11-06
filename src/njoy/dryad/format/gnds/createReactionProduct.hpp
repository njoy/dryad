#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCT
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCT

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/createParticleIdentifier.hpp"
#include "dryad/format/gnds/createMultiplicity.hpp"
#include "dryad/format/gnds/createTwoBodyDistributionData.hpp"
#include "dryad/format/gnds/createUncorrelatedDistributionData.hpp"
#include "dryad/format/gnds/createCoherentDistributionData.hpp"
#include "dryad/format/gnds/createIncoherentDistributionData.hpp"
#include "dryad/format/gnds/createTabulatedAverageEnergy.hpp"
#include "dryad/format/gnds/resolveLink.hpp"
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
                         bool normalise,
                         const std::string& style = "eval" ) {

    // check that this is a valid product node
    throwExceptionOnWrongNode( product, "product" );

    // get the secondary particle identifier and adjust as required
    id::ParticleID id = createParticleIdentifier( product.attribute( "pid" ).as_string() );
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );

    // create the multiplicity
    auto multiplicity = createMultiplicity( product.child( "multiplicity" ), style );

    // get distribution data
    std::optional< ReactionProduct::DistributionData > distribution = std::nullopt;
    auto node = product.child( "distribution" );
    if ( node ) {

      // get the first node of the requested style and act accordingly
      node = node.find_child_by_attribute( "label", style.c_str() );
      if ( strcmp( node.name(), "angularTwoBody" ) == 0 ) {

        // ignore recoil or regions2d distributions for now
        auto recoil = node.child( "recoil" );
        auto regions2d = node.child( "regions2d" );
        if ( ! recoil && ! regions2d ) {

          distribution = createTwoBodyDistributionData( node, normalise );
        }
      }
      else if ( strcmp( node.name(), "uncorrelated" ) == 0 ) {

        // ignore discrete gamma distributions for now
        auto discreteGamma = node.child( "energy" ).child( "discreteGamma" );
        auto primaryGamma = node.child( "energy" ).child( "primaryGamma" );
        if ( ! discreteGamma && ! primaryGamma ) {

          try {

            distribution = createUncorrelatedDistributionData( node, normalise );
          }
          catch ( const std::runtime_error& error ) {

            Log::info( "Ignoring distribution type since it is not implemented yet: {}", error.what() );
          }
        }
      }
      else if ( strcmp( node.name(), "coherentPhotonScattering" ) == 0 ) {

        // the distribution can be linked to
        if ( node.attribute( "href" ) ) {

          node = resolveLink( node );
        }
        distribution = createCoherentDistributionData( node );
      }
      else if ( strcmp( node.name(), "incoherentPhotonScattering" ) == 0 ) {

        // the distribution can be linked to
        if ( node.attribute( "href" ) ) {

          node = resolveLink( node );
        }
        distribution = createIncoherentDistributionData( node );
      }
    }

    // get distribution data
    std::optional< TabulatedAverageEnergy > average = std::nullopt;
    node = product.child( "averageProductEnergy" );
    if ( node ) {

      average = createTabulatedAverageEnergy( node );
    }

    return ReactionProduct( id, multiplicity,
                            std::move( distribution ),
                            std::move( average ) );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
