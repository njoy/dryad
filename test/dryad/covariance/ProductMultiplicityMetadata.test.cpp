// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/ProductMultiplicityMetadata.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "Metadata" ) {

  GIVEN( "valid metadata for a covariance matrix for product multiplicities" ) {

    using Key = std::tuple< id::ReactionID, id::EnergyGroup, id::ParticleID >;

    // test variables
    id::ReactionID reaction1( "n,U235->n,U235_e0" );
    id::ReactionID reaction2( "n,U235->2n,U234[all]" );
    id::EnergyGroup group1( 1e-5, 1e+6 );
    id::EnergyGroup group2( 1e+6, 2e+7 );
    id::ParticleID product1( "Y99" );
    id::ParticleID product2( "Mo99" );
    id::ParticleID product3( "Pr148" );
    id::ParticleID product4( "Pr148_e1" );

    WHEN( "using metadata directly" ) {

      std::vector< id::ReactionID > reactions= { id::ReactionID( "n,U235->n,U235_e0" ),
                                                 id::ReactionID( "n,U235->2n,U234[all]" ) };
      std::vector< double > energies= { 1e-5, 1e+6, 2e+7 };
      std::vector< id::ParticleID > products= { id::ParticleID( "Y99" ), id::ParticleID( "Mo99" ),
                                                id::ParticleID( "Pr148" ), id::ParticleID( "Pr148_e1" ) };

      ProductMultiplicityMetadata chunk( std::move( reactions ), std::move( energies ), std::move( products ) );

      THEN( "a Metadata can be constructed and members can be tested" ) {

        CHECK( 2 == chunk.reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235_e0" ) == chunk.reactionIdentifiers()[0] );
        CHECK( id::ReactionID( "n,U235->2n,U234[all]" ) == chunk.reactionIdentifiers()[1] );

        CHECK( 3 == chunk.energies().size() );
        CHECK( 1e-5 == chunk.energies()[0] );
        CHECK( 1e+6 == chunk.energies()[1] );
        CHECK( 2e+7 == chunk.energies()[2] );

        CHECK( 4 == chunk.productIdentifiers().size() );
        CHECK( id::ParticleID( "Y99" ) == chunk.productIdentifiers()[0] );
        CHECK( id::ParticleID( "Mo99" ) == chunk.productIdentifiers()[1] );
        CHECK( id::ParticleID( "Pr148" ) == chunk.productIdentifiers()[2] );
        CHECK( id::ParticleID( "Pr148_e1" ) == chunk.productIdentifiers()[3] );

        CHECK( 16 == chunk.keys().size() );
        CHECK( std::tuple{ reaction1, group1, product1 } == chunk.keys()[0] );
        CHECK( std::tuple{ reaction1, group1, product2 } == chunk.keys()[1] );
        CHECK( std::tuple{ reaction1, group1, product3 } == chunk.keys()[2] );
        CHECK( std::tuple{ reaction1, group1, product4 } == chunk.keys()[3] );
        CHECK( std::tuple{ reaction1, group2, product1 } == chunk.keys()[4] );
        CHECK( std::tuple{ reaction1, group2, product2 } == chunk.keys()[5] );
        CHECK( std::tuple{ reaction1, group2, product3 } == chunk.keys()[6] );
        CHECK( std::tuple{ reaction1, group2, product4 } == chunk.keys()[7] );
        CHECK( std::tuple{ reaction2, group1, product1 } == chunk.keys()[8] );
        CHECK( std::tuple{ reaction2, group1, product2 } == chunk.keys()[9] );
        CHECK( std::tuple{ reaction2, group1, product3 } == chunk.keys()[10] );
        CHECK( std::tuple{ reaction2, group1, product4 } == chunk.keys()[11] );
        CHECK( std::tuple{ reaction2, group2, product1 } == chunk.keys()[12] );
        CHECK( std::tuple{ reaction2, group2, product2 } == chunk.keys()[13] );
        CHECK( std::tuple{ reaction2, group2, product3 } == chunk.keys()[14] );
        CHECK( std::tuple{ reaction2, group2, product4 } == chunk.keys()[15] );
      } // THEN
    } // WHEN

    WHEN( "using keys" ) {

      std::vector< Key > keys= { std::tuple{ reaction1, group1, product1 },
                                 std::tuple{ reaction1, group1, product2 },
                                 std::tuple{ reaction1, group1, product3 },
                                 std::tuple{ reaction1, group1, product4 },
                                 std::tuple{ reaction1, group2, product1 },
                                 std::tuple{ reaction1, group2, product2 },
                                 std::tuple{ reaction1, group2, product3 },
                                 std::tuple{ reaction1, group2, product4 },
                                 std::tuple{ reaction2, group1, product1 },
                                 std::tuple{ reaction2, group1, product2 },
                                 std::tuple{ reaction2, group1, product3 },
                                 std::tuple{ reaction2, group1, product4 },
                                 std::tuple{ reaction2, group2, product1 },
                                 std::tuple{ reaction2, group2, product2 },
                                 std::tuple{ reaction2, group2, product3 },
                                 std::tuple{ reaction2, group2, product4 } };

      ProductMultiplicityMetadata chunk( std::move( keys ) );

      THEN( "a Metadata can be constructed and members can be tested" ) {

        CHECK( 2 == chunk.reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235_e0" ) == chunk.reactionIdentifiers()[0] );
        CHECK( id::ReactionID( "n,U235->2n,U234[all]" ) == chunk.reactionIdentifiers()[1] );

        CHECK( 3 == chunk.energies().size() );
        CHECK( 1e-5 == chunk.energies()[0] );
        CHECK( 1e+6 == chunk.energies()[1] );
        CHECK( 2e+7 == chunk.energies()[2] );

        CHECK( 4 == chunk.productIdentifiers().size() );
        CHECK( id::ParticleID( "Y99" ) == chunk.productIdentifiers()[0] );
        CHECK( id::ParticleID( "Mo99" ) == chunk.productIdentifiers()[1] );
        CHECK( id::ParticleID( "Pr148" ) == chunk.productIdentifiers()[2] );
        CHECK( id::ParticleID( "Pr148_e1" ) == chunk.productIdentifiers()[3] );

        CHECK( 16 == chunk.keys().size() );
        CHECK( std::tuple{ reaction1, group1, product1 } == chunk.keys()[0] );
        CHECK( std::tuple{ reaction1, group1, product2 } == chunk.keys()[1] );
        CHECK( std::tuple{ reaction1, group1, product3 } == chunk.keys()[2] );
        CHECK( std::tuple{ reaction1, group1, product4 } == chunk.keys()[3] );
        CHECK( std::tuple{ reaction1, group2, product1 } == chunk.keys()[4] );
        CHECK( std::tuple{ reaction1, group2, product2 } == chunk.keys()[5] );
        CHECK( std::tuple{ reaction1, group2, product3 } == chunk.keys()[6] );
        CHECK( std::tuple{ reaction1, group2, product4 } == chunk.keys()[7] );
        CHECK( std::tuple{ reaction2, group1, product1 } == chunk.keys()[8] );
        CHECK( std::tuple{ reaction2, group1, product2 } == chunk.keys()[9] );
        CHECK( std::tuple{ reaction2, group1, product3 } == chunk.keys()[10] );
        CHECK( std::tuple{ reaction2, group1, product4 } == chunk.keys()[11] );
        CHECK( std::tuple{ reaction2, group2, product1 } == chunk.keys()[12] );
        CHECK( std::tuple{ reaction2, group2, product2 } == chunk.keys()[13] );
        CHECK( std::tuple{ reaction2, group2, product3 } == chunk.keys()[14] );
        CHECK( std::tuple{ reaction2, group2, product4 } == chunk.keys()[15] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO