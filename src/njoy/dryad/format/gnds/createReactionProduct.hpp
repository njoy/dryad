#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCT
#define NJOY_DRYAD_FORMAT_GNDS_CREATEREACTIONPRODUCT

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "njoy/dryad/format/gnds/createParticleIdentifier.hpp"
#include "njoy/dryad/format/gnds/createMultiplicity.hpp"
#include "njoy/dryad/format/gnds/createTwoBodyDistributionData.hpp"
#include "njoy/dryad/format/gnds/createUncorrelatedDistributionData.hpp"
#include "njoy/dryad/format/gnds/createCoherentDistributionData.hpp"
#include "njoy/dryad/format/gnds/createIncoherentDistributionData.hpp"
#include "njoy/dryad/format/gnds/createTabulatedAverageEnergy.hpp"
#include "njoy/dryad/format/gnds/resolveLink.hpp"
#include "njoy/dryad/ReactionProduct.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a ReactionProduct from an GNDS product node
   *
   *  @param[in] reaction     the reaction identifier
   *  @param[in] suite        the gnds xml reaction suite
   *  @param[in] product      the gnds xml product suite
   *  @param[in] parent       the parent reaction product
   *  @param[in] chain        the current chain index
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   *  @param[in] style        the gnds style to process (default is eval)
   */
  inline ReactionProduct
  createReactionProduct( const id::ReactionID& reaction,
                         pugi::xml_node /* suite */,
                         pugi::xml_node product,
                         std::optional< id::ParticleID > parent,
                         std::size_t chain,
                         bool normalise,
                         const std::string& style = "eval" ) {

    // check that this is a valid product node
    throwExceptionOnWrongNode( product, "product" );

    // get the reaction product id and look for the residual - if it is defined
    id::ParticleID id = createParticleIdentifier( product.attribute( "pid" ).as_string() );
    if ( chain == 0 ) {

      if ( reaction.residual().has_value() ) {

        auto residual = reaction.residual().value();
        if ( id.groundState() == residual.groundState() ) {

          if ( id.e() == residual.e() ||
               ( residual.e() == id::LevelID::all || residual.e() == id::LevelID::continuum && id.e() == 0 ) ) {

            id = residual;
          }
        }
      }
    }

    // change the product identifier to a fundamental particle if need be
    if ( reaction.residual() != id ) {

      if ( id == id::ParticleID( "H1" ) ) {

        id = id::ParticleID::proton();
      }
      else if ( id == id::ParticleID( "H2" ) ) {

        id = id::ParticleID::deuteron();
      }
      else if ( id == id::ParticleID( "H3" ) ) {

        id = id::ParticleID::triton();
      }
      else if ( id == id::ParticleID( "He3" ) ) {

        id = id::ParticleID::helion();
      }
      else if ( id == id::ParticleID( "He4" ) ) {

        id = id::ParticleID::alpha();
      }
    }

    // start reading the data
    Log::info( "Reading reaction product data for \'{}\'", id.symbol() );

    // get the multiplicity
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
      else if ( strcmp( node.name(), "unspecified" ) == 0 ) {

        // nothing to do here
        // placeholder if we want to assign unknown distribution type
      }
    }

    // get average data
    std::optional< TabulatedAverageCosine > average_cosine = std::nullopt;
    std::optional< TabulatedAverageEnergy > average_energy = std::nullopt;
    node = product.child( "averageProductEnergy" );
    if ( node ) {

      average_energy = createTabulatedAverageEnergy( node );
    }

    return ReactionProduct( id, multiplicity,
                            std::move( distribution ),
                            std::move( average_cosine ),
                            std::move( average_energy ),
                            std::move( parent ),
                            chain );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
