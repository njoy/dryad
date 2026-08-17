#ifndef NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPREACTIONPRODUCTS
#define NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPREACTIONPRODUCTS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/MultigroupReactionProduct.hpp"
#include "njoy/dryad/MultigroupAverageCosine.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/gendf/read/createMultiplicity.hpp"
#include "ENDFtk/GMaterial.hpp"
#include "ENDFtk/tree/GMaterial.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {

  /**
   *  @brief Add a placeholder reaction product if it is not present yet
   *
   *  @param[in] particle        the particle identifier
   *  @param[in] multiplicity    the multiplicity of the reaction product
   *  @param[in, out] products   the current set of reaction products
   */
  inline void addProduct( const dryad::id::ParticleID& particle,
                          int multiplicity,
                          std::vector< dryad::MultigroupReactionProduct >& products ) {

    auto iter = std::find_if( products.begin(), products.end(),
                              [&particle] ( auto&& product )
                                          { return product.productIdentifier() == particle &&
                                                   product.chainIndex() == 0; } );
    if ( iter == products.end() ) {

      Log::info( "Adding '{}' as an expected reaction product", particle.symbol() );
      products.emplace_back( particle, createMultiplicity( multiplicity ) );
    }
  }

  /**
   *  @brief Create the reaction products for a GENDF reaction
   *
   *  For now, just add all expected reaction products.
   *
   *  @param[in] reaction   the reaction identifier
   */
  inline std::vector< dryad::MultigroupReactionProduct >
  createMultigroupReactionProducts( const dryad::id::ReactionID& reaction,
                                    const ENDFtk::tree::GMaterial& material,
                                    int mt,
                                    const std::vector< double >& boundaries,
                                    std::size_t dilution ) {

    std::vector< dryad::MultigroupReactionProduct > products;

    if ( material.hasSection( 3, mt ) ) {

      if ( mt == 2 && material.hasSection( 3, 251 ) ) {

        Log::info( "Reading average cosine data for MT251" );

        auto section = material.section( 3, 251 ).parse< 3 >();
        auto cosines = createVector( section.ratio( 0, dilution ) );
        dryad::MultigroupAverageCosine average( boundaries, std::move( cosines ) );

        products.emplace_back( dryad::id::ParticleID::neutron(), createMultiplicity( 1 ), std::move( average ) );
      }
    }

    // add missing expected reaction products
    if ( reaction.particles().has_value() ) {

      if ( reaction.particles()->size() == 0 ) {

        // add photons as an expected reaction product if it is not there yet
        addProduct( dryad::id::ParticleID::photon(), 1, products );
      }
      else {

        // add all expected reaction products if they are not there yet
        for ( const auto& [particle, multiplicity] : reaction.particles().value() ) {

          addProduct( particle, multiplicity, products );
        }
      }
    }

    // add the residual if it is not there yet
    if ( reaction.residual().has_value() ) {

      addProduct( reaction.residual().value(), 1, products );
    }

    products.shrink_to_fit();
    return products;
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
