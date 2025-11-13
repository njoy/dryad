// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/covariance/CrossSectionMetadata.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "Metadata" ) {

  GIVEN( "valid metadata for a covariance matrix for cross sections" ) {

    using Key = std::tuple< id::ReactionID, id::EnergyGroup >;

    // test variables
    id::ReactionID reaction1( "n,U235->n,U235_e0" );
    id::ReactionID reaction2( "n,U235->2n,U234[all]" );
    id::ReactionID reaction3( "n,U235->3n,U233[all]" );
    id::EnergyGroup group1( 1e-5, 1e+6 );
    id::EnergyGroup group2( 1e+6, 2e+7 );

    WHEN( "using metadata directly" ) {

      std::vector< id::ReactionID > reactions= { id::ReactionID( "n,U235->n,U235_e0" ),
                                                 id::ReactionID( "n,U235->2n,U234[all]" ),
                                                 id::ReactionID( "n,U235->3n,U233[all]" ) };
      std::vector< double > energies= { 1e-5, 1e+6, 2e+7 };

      CrossSectionMetadata chunk( std::move( reactions ), std::move( energies ) );

      THEN( "a Metadata can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235_e0" ) == chunk.reactionIdentifiers()[0] );
        CHECK( id::ReactionID( "n,U235->2n,U234[all]" ) == chunk.reactionIdentifiers()[1] );
        CHECK( id::ReactionID( "n,U235->3n,U233[all]" ) == chunk.reactionIdentifiers()[2] );

        CHECK( 3 == chunk.energies().size() );
        CHECK( 1e-5 == chunk.energies()[0] );
        CHECK( 1e+6 == chunk.energies()[1] );
        CHECK( 2e+7 == chunk.energies()[2] );

        CHECK( 6 == chunk.keys().size() );
        CHECK( std::tuple{ reaction1, group1 } == chunk.keys()[0] );
        CHECK( std::tuple{ reaction1, group2 } == chunk.keys()[1] );
        CHECK( std::tuple{ reaction2, group1 } == chunk.keys()[2] );
        CHECK( std::tuple{ reaction2, group2 } == chunk.keys()[3] );
        CHECK( std::tuple{ reaction3, group1 } == chunk.keys()[4] );
        CHECK( std::tuple{ reaction3, group2 } == chunk.keys()[5] );
      } // THEN
    } // WHEN

    WHEN( "using keys" ) {

      std::vector< Key > keys= { std::tuple{ reaction1, group1 },
                                 std::tuple{ reaction1, group2 },
                                 std::tuple{ reaction2, group1 },
                                 std::tuple{ reaction2, group2 },
                                 std::tuple{ reaction3, group1 },
                                 std::tuple{ reaction3, group2 } };

      CrossSectionMetadata chunk( std::move( keys ) );

      THEN( "a Metadata can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235_e0" ) == chunk.reactionIdentifiers()[0] );
        CHECK( id::ReactionID( "n,U235->2n,U234[all]" ) == chunk.reactionIdentifiers()[1] );
        CHECK( id::ReactionID( "n,U235->3n,U233[all]" ) == chunk.reactionIdentifiers()[2] );

        CHECK( 3 == chunk.energies().size() );
        CHECK( 1e-5 == chunk.energies()[0] );
        CHECK( 1e+6 == chunk.energies()[1] );
        CHECK( 2e+7 == chunk.energies()[2] );

        CHECK( 6 == chunk.keys().size() );
        CHECK( std::tuple{ reaction1, group1 } == chunk.keys()[0] );
        CHECK( std::tuple{ reaction1, group2 } == chunk.keys()[1] );
        CHECK( std::tuple{ reaction2, group1 } == chunk.keys()[2] );
        CHECK( std::tuple{ reaction2, group2 } == chunk.keys()[3] );
        CHECK( std::tuple{ reaction3, group1 } == chunk.keys()[4] );
        CHECK( std::tuple{ reaction3, group2 } == chunk.keys()[5] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO