#ifndef NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPREACTION
#define NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPREACTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/MultigroupReaction.hpp"
#include "njoy/format/adjustScatterLevel.hpp"
#include "njoy/format/endf/ReactionInformation.hpp"
#include "njoy/format/gendf/read/createMultigroupCrossSection.hpp"
#include "njoy/format/gendf/read/createMultigroupReactionProducts.hpp"
#include "ENDFtk/GMaterial.hpp"
#include "ENDFtk/tree/GMaterial.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {

  /**
   *  @brief Create a MultigroupReaction from an unparsed GENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] material     the unparsed GENDF material
   *  @param[in] mt           the MT number to process
   *  @param[in] boundaries   the energy group boundaries
   *  @param[in] dilution     the dilution index to read
   */
  inline dryad::MultigroupReaction
  createMultigroupReaction( const dryad::id::ParticleID& projectile,
                            const dryad::id::ParticleID& target,
                            const ENDFtk::tree::GMaterial& material,
                            int mt,
                            const std::vector< double >& boundaries,
                            std::size_t dilution ) {

    // metadata and miscellaneous information
    dryad::id::ReactionID id( projectile, target, adjustScatterLevel( projectile, target, mt ) );
    Log::info( "Reading data for \'{}\' - MT{}", id.symbol(), mt );

    if ( material.hasSection( 3, mt ) ) {

      // cross section
      auto section = material.section( 3, mt ).parse< 3 >();
      dryad::MultigroupCrossSection xs = createMultigroupCrossSection( boundaries, section, dilution );

      if ( endf::ReactionInformation::isPrimary( material, mt ) ) {

        // reaction products
        std::vector< dryad::MultigroupReactionProduct > products = createMultigroupReactionProducts( id );

        // return the reaction data
        return dryad::MultigroupReaction( std::move( id ), std::move( xs ), std::move( products ) );
      }
      else if ( endf::ReactionInformation::isSummation( material, mt ) ) {

        // return the reaction data
        return dryad::MultigroupReaction( std::move( id ),
                                          endf::ReactionInformation::partials( projectile, target, material, 3, mt ),
                                          std::move( xs ) );
      }
      else if ( endf::ReactionInformation::isLumpedCovariance( mt ) ) {

        // return the reaction data
        return dryad::MultigroupReaction( std::move( id ),
                                          endf::ReactionInformation::partials( projectile, target, material, 33, mt ),
                                          std::move( xs ) );
      }
      else {

        Log::error( "{} is not an MT number that designates a valid reaction", mt );
        throw std::exception();
      }
    }
    else {

      Log::error( "The material does not have reaction data for MT{}", mt );
      throw std::exception();
    }
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
