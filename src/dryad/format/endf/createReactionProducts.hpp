#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONPRODUCTS
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONPRODUCTS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/createProductIdentifier.hpp"
#include "dryad/format/endf/createReactionProduct.hpp"
#include "dryad/format/endf/createTabulatedMultiplicity.hpp"
#include "dryad/ReactionProduct.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a Reaction from an unparsed ENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] target       the unparsed ENDF material
   *  @param[in] mt           the MT number to process
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  std::vector< ReactionProduct >
  createReactionProducts( const id::ParticleID& projectile, const id::ParticleID& target,
                          const ENDFtk::tree::Material& material, int mt,
                          bool normalise ) {

    std::vector< ReactionProduct > products;

    if ( material.hasSection( 4, mt ) || material.hasSection( 5, mt ) ) {

      switch ( mt ) {

        case   2 : {

          auto section = material.section( 4, mt ).parse< 4 >();
          switch ( section.LTT() ) {

            case   1 : {

              using LegendreDistributions = ENDFtk::section::Type< 4 >::LegendreDistributions;
              auto distributions = std::get< LegendreDistributions >( section.distributions() );
              products.emplace_back( createReactionProduct( projectile, target, distributions, normalise ) );
              break;
            }
            default : {

              Log::info( "Any MF4 LTT different from 1 is not implemented yet" );
              break;
            }
          }
          break;
        }
        default : {

          Log::info( "Reading reaction product data from MF4 and/or MF5 is not implemented yet" );
          break;
        }
      }
    }
    else if ( material.hasSection( 6, mt ) ) {

      auto section = material.section( 6, mt ).parse< 6 >();
      for ( const auto& product : section.reactionProducts() ) {

        if ( mt != 18 ) {

          products.emplace_back( createReactionProduct( projectile, target, product, normalise ) );
        }
        else {

          //! @todo handle P(nu) case
          Log::warning( "Skipping P(nu) and P(nu_g) in MF6" );
        }
      }
    }
    else if ( material.hasSection( 26, mt ) ) {

      auto section = material.section( 26, mt ).parse< 26 >();
      for ( const auto& product : section.reactionProducts() ) {

        products.emplace_back( createReactionProduct( projectile, target, product, mt, normalise ) );
      }
    }
    else if ( material.hasSection( 27, mt ) ) {

      switch ( mt ) {

        case 502 : {

          auto section = material.section( 27, mt ).parse< 27 >();
          std::optional< ENDFtk::section::Type< 27 > > real = std::nullopt;
          std::optional< ENDFtk::section::Type< 27 > > imaginary = std::nullopt;
          if ( material.hasSection( 27, 506 ) ) { real = material.section( 27, 506 ).parse< 27 >(); }
          if ( material.hasSection( 27, 505 ) ) { imaginary = material.section( 27, 505 ).parse< 27 >(); }
          products.emplace_back( createReactionProduct( projectile, target, section, real, imaginary, mt, normalise ) );
          break;
        }
        case 504 : {

          auto section = material.section( 27, mt ).parse< 27 >();
          products.emplace_back( createReactionProduct( projectile, target, section, mt, normalise ) );
          break;
        }
        default : {

          Log::info( "The material does not have reaction products for MT{}", mt );
          break;
        }
      }
    }
    else {

      Log::info( "The material does not have reaction products for MT{}", mt );
    }

    // std::sort( products.begin(), products.end(),
    //            [] ( auto&& left, auto&& right )
    //               { return left.identifier() < right.identifier(); } );
    return products;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
