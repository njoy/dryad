#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONPRODUCTS
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONPRODUCTS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/format/endf/createComplexBreakUpParticles.hpp"
#include "njoy/dryad/format/endf/createMultiplicity.hpp"
#include "njoy/dryad/format/endf/createReactionProduct.hpp"
#include "njoy/dryad/ReactionProduct.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Add a placeholder reaction product if it is not present yet
   *
   *  @param[in] particle        the particle identifier
   *  @param[in] multiplicity    the multiplicity of the target
   *  @param[in, out] products   the current set of reaction products
   */
  inline void addProduct( const id::ParticleID& particle,
                          int multiplicity,
                          std::vector< ReactionProduct >& products ) {

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
   *  @brief Create a Reaction from an unparsed ENDF material
   *
   *  @param[in] reaction     the reaction identifier
   *  @param[in] material     the unparsed ENDF material
   *  @param[in] mt           the MT number to process
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  inline std::vector< ReactionProduct >
  createReactionProducts( const id::ReactionID& reaction,
                          const ENDFtk::tree::Material& material,
                          int mt,
                          bool normalise ) {

    std::vector< ReactionProduct > products;

    if ( material.hasSection( 3, mt ) ) {

      auto has_mf4 = material.hasSection( 4, mt );
      auto has_mf5 = material.hasSection( 5, mt );
      auto has_mf6 = material.hasSection( 6, mt );
      auto has_mf12 = material.hasSection( 12, mt );
      auto has_mf13 = material.hasSection( 13, mt );
      auto has_mf14 = material.hasSection( 14, mt );
      auto has_mf15 = material.hasSection( 15, mt );
      auto has_photon_prod = has_mf12 || has_mf13 || has_mf14 || has_mf15;
      auto has_products = has_mf4 || has_mf5 || has_mf6 || has_photon_prod;

      auto xs = material.section( 3, mt ).parse< 3 >();
      int complex_breakup = xs.complexBreakUp();

      if ( has_products ) {

        // add the secondary particle distribution accordingly
        if ( has_mf4 || has_mf5 ) {

          if ( has_mf4 && has_mf5 ) {

            Log::info( "Reading reaction product data from MF4 and MF5 is not implemented yet" );
          }
          else if ( has_mf4 ) {

            auto section = material.section( 4, mt ).parse< 4 >();
            products.emplace_back( createReactionProduct( reaction, section, normalise ) );
          }
          else {

            Log::info( "Reading reaction product data from MF5 is not implemented yet" );
          }

          if ( reaction.residual().has_value() ) {

            auto residual = reaction.residual().value();
            if ( complex_breakup != 0  ) {

              if ( complex_breakup == 1 ) {

                Log::error( "Complex breakup flag \'{}\' for residual \'{}\' cannot be used with MF4/MF5 data",
                            complex_breakup, residual.symbol() );
                throw std::exception();
              }

              Log::info( "Applying complex breakup flag \'{}\' for residual \'{}\'",
                         complex_breakup, residual.symbol() );

              auto breakup = createComplexBreakUpParticles( residual, complex_breakup );
              for ( const auto& [id, multiplicity] : breakup ) {

                Log::info( "Adding '{}' as a complex breakup reaction product", id.symbol() );
                products.emplace_back( id, createMultiplicity( multiplicity ), std::nullopt,
                                       std::nullopt, std::nullopt, residual, 1 );
              }
            }
          }
          else {

            if ( complex_breakup != 0  ) {

              Log::error( "Complex breakup flag \'{}\' cannot be used with a reaction that has no defined residual",
                          complex_breakup );
              throw std::exception();
            }
          }
        }

        if ( has_mf6 ) {

          auto section = material.section( 6, mt ).parse< 6 >();
          for ( const auto& product : section.reactionProducts() ) {

            if ( product.productIdentifier() == 1 && ( has_mf4 || has_mf5 ) ) {

              Log::info( "Skipping neutron data in MF6 since MF4 and/or MF5 are present as well" );
            }
            else if ( product.productIdentifier() == 0 && has_photon_prod ) {

              Log::info( "Skipping photon data in MF6 since MF12, MF13, MF14 and/or MF15 are present as well" );
            }
            else if ( mt == 18 ) {

              //! @todo handle P(nu) case
              Log::warning( "Skipping P(nu) and P(nu_g) in MF6" );
            }
            else {

              products.emplace_back( createReactionProduct( reaction, product, normalise ) );
            }
          }

          if ( reaction.residual().has_value() ) {

            auto residual = reaction.residual().value();
            if ( complex_breakup != 0 ) {

              if ( complex_breakup != 1 ) {

                Log::error( "Complex breakup flag \'{}\' for residual \'{}\' cannot be used with MF6 data",
                            complex_breakup, residual.symbol() );
                throw std::exception();
              }

              Log::error( "Complex breakup flag for MF6 data is not handled yet, contact a developer" );
              throw std::exception();
            }
          }
          else {

            if ( complex_breakup != 0  ) {

              Log::error( "Complex breakup flag \'{}\' cannot be used with a reaction that has no defined residual",
                          complex_breakup );
              throw std::exception();
            }
          }
        }

        if ( has_photon_prod ) {

          Log::info( "Reading photon data from MF12, MF13, MF14 and/or MF15 is not implemented yet" );
        }
      }
      else {

        Log::info( "The material does not have reaction products for MT{}", mt );
      }
    }
    else if ( material.hasSection( 23, mt ) ) {

      if ( material.hasSection( 26, mt ) ) {

        auto section = material.section( 26, mt ).parse< 26 >();
        for ( const auto& product : section.reactionProducts() ) {

          products.emplace_back( createReactionProduct( reaction, product, mt, normalise ) );
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
            products.emplace_back( createReactionProduct( reaction, section, real, imaginary, mt, normalise ) );
            break;
          }
          case 504 : {

            auto section = material.section( 27, mt ).parse< 27 >();
            products.emplace_back( createReactionProduct( reaction, section, mt, normalise ) );
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
    }
    else {

      Log::info( "The material does not have reaction products for MT{}", mt );
    }

    // add missing expected reaction products
    if ( reaction.particles().has_value() ) {

      if ( reaction.particles()->size() == 0 ) {

        // add photons as an expected reaction product if it is not there yet
        addProduct( id::ParticleID::photon(), 1, products );
      }
      else {

        // add all expected reaction products if they are not there yet
        for ( const auto& pair : reaction.particles().value() ) {

          addProduct( pair.first, pair.second, products );
        }
      }
    }

    // add the residual if it is not there yet
    if ( reaction.residual().has_value() ) {

      addProduct( reaction.residual().value(), 1, products );
    }

    // std::sort( products.begin(), products.end(),
    //            [] ( auto&& left, auto&& right )
    //               { return left.identifier() < right.identifier(); } );
    products.shrink_to_fit();
    return products;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
