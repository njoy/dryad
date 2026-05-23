// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/covariance/AngularDistributionMetadata.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "Metadata" ) {

  GIVEN( "valid metadata for a covariance matrix for angular distributions" ) {

    using Key = std::tuple< id::ReactionID, id::EnergyGroup, std::size_t >;

    // test variables
    id::ReactionID reaction1( "n,U235->n(0)" );
    id::ReactionID reaction2( "n,U235->n(1)" );
    id::EnergyGroup group1( 1e-5, 1e+6 );
    id::EnergyGroup group2( 1e+6, 2e+7 );

    WHEN( "using metadata directly" ) {

      std::vector< id::ReactionID > reactions= { id::ReactionID( "n,U235->n(0)" ),
                                                 id::ReactionID( "n,U235->n(1)" ) };
      std::vector< double > energies= { 1e-5, 1e+6, 2e+7 };
      std::vector< std::size_t > moments= { 1, 2, 3, 4 };

      AngularDistributionMetadata chunk( std::move( reactions ), std::move( energies ), std::move( moments ) );

      THEN( "a Metadata can be constructed and members can be tested" ) {

        CHECK( 2 == chunk.reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n(0)" ) == chunk.reactionIdentifiers()[0] );
        CHECK( id::ReactionID( "n,U235->n(1)" ) == chunk.reactionIdentifiers()[1] );

        CHECK( 3 == chunk.energies().size() );
        CHECK( 1e-5 == chunk.energies()[0] );
        CHECK( 1e+6 == chunk.energies()[1] );
        CHECK( 2e+7 == chunk.energies()[2] );

        CHECK( 4 == chunk.moments().size() );
        CHECK( 1 == chunk.moments()[0] );
        CHECK( 2 == chunk.moments()[1] );
        CHECK( 3 == chunk.moments()[2] );
        CHECK( 4 == chunk.moments()[3] );

        CHECK( 16 == chunk.keys().size() );
        CHECK( std::tuple{ reaction1, group1, 1 } == chunk.keys()[0] );
        CHECK( std::tuple{ reaction1, group1, 2 } == chunk.keys()[1] );
        CHECK( std::tuple{ reaction1, group1, 3 } == chunk.keys()[2] );
        CHECK( std::tuple{ reaction1, group1, 4 } == chunk.keys()[3] );
        CHECK( std::tuple{ reaction1, group2, 1 } == chunk.keys()[4] );
        CHECK( std::tuple{ reaction1, group2, 2 } == chunk.keys()[5] );
        CHECK( std::tuple{ reaction1, group2, 3 } == chunk.keys()[6] );
        CHECK( std::tuple{ reaction1, group2, 4 } == chunk.keys()[7] );
        CHECK( std::tuple{ reaction2, group1, 1 } == chunk.keys()[8] );
        CHECK( std::tuple{ reaction2, group1, 2 } == chunk.keys()[9] );
        CHECK( std::tuple{ reaction2, group1, 3 } == chunk.keys()[10] );
        CHECK( std::tuple{ reaction2, group1, 4 } == chunk.keys()[11] );
        CHECK( std::tuple{ reaction2, group2, 1 } == chunk.keys()[12] );
        CHECK( std::tuple{ reaction2, group2, 2 } == chunk.keys()[13] );
        CHECK( std::tuple{ reaction2, group2, 3 } == chunk.keys()[14] );
        CHECK( std::tuple{ reaction2, group2, 4 } == chunk.keys()[15] );
      } // THEN
    } // WHEN

    WHEN( "using keys" ) {

      std::vector< Key > keys= { std::tuple{ reaction1, group1, 1 },
                                 std::tuple{ reaction1, group1, 2 },
                                 std::tuple{ reaction1, group1, 3 },
                                 std::tuple{ reaction1, group1, 4 },
                                 std::tuple{ reaction1, group2, 1 },
                                 std::tuple{ reaction1, group2, 2 },
                                 std::tuple{ reaction1, group2, 3 },
                                 std::tuple{ reaction1, group2, 4 },
                                 std::tuple{ reaction2, group1, 1 },
                                 std::tuple{ reaction2, group1, 2 },
                                 std::tuple{ reaction2, group1, 3 },
                                 std::tuple{ reaction2, group1, 4 },
                                 std::tuple{ reaction2, group2, 1 },
                                 std::tuple{ reaction2, group2, 2 },
                                 std::tuple{ reaction2, group2, 3 },
                                 std::tuple{ reaction2, group2, 4 } };

      AngularDistributionMetadata chunk( std::move( keys ) );

      THEN( "a Metadata can be constructed and members can be tested" ) {

        CHECK( 2 == chunk.reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n(0)" ) == chunk.reactionIdentifiers()[0] );
        CHECK( id::ReactionID( "n,U235->n(1)" ) == chunk.reactionIdentifiers()[1] );

        CHECK( 3 == chunk.energies().size() );
        CHECK( 1e-5 == chunk.energies()[0] );
        CHECK( 1e+6 == chunk.energies()[1] );
        CHECK( 2e+7 == chunk.energies()[2] );

        CHECK( 4 == chunk.moments().size() );
        CHECK( 1 == chunk.moments()[0] );
        CHECK( 2 == chunk.moments()[1] );
        CHECK( 3 == chunk.moments()[2] );
        CHECK( 4 == chunk.moments()[3] );

        CHECK( 16 == chunk.keys().size() );
        CHECK( std::tuple{ reaction1, group1, 1 } == chunk.keys()[0] );
        CHECK( std::tuple{ reaction1, group1, 2 } == chunk.keys()[1] );
        CHECK( std::tuple{ reaction1, group1, 3 } == chunk.keys()[2] );
        CHECK( std::tuple{ reaction1, group1, 4 } == chunk.keys()[3] );
        CHECK( std::tuple{ reaction1, group2, 1 } == chunk.keys()[4] );
        CHECK( std::tuple{ reaction1, group2, 2 } == chunk.keys()[5] );
        CHECK( std::tuple{ reaction1, group2, 3 } == chunk.keys()[6] );
        CHECK( std::tuple{ reaction1, group2, 4 } == chunk.keys()[7] );
        CHECK( std::tuple{ reaction2, group1, 1 } == chunk.keys()[8] );
        CHECK( std::tuple{ reaction2, group1, 2 } == chunk.keys()[9] );
        CHECK( std::tuple{ reaction2, group1, 3 } == chunk.keys()[10] );
        CHECK( std::tuple{ reaction2, group1, 4 } == chunk.keys()[11] );
        CHECK( std::tuple{ reaction2, group2, 1 } == chunk.keys()[12] );
        CHECK( std::tuple{ reaction2, group2, 2 } == chunk.keys()[13] );
        CHECK( std::tuple{ reaction2, group2, 3 } == chunk.keys()[14] );
        CHECK( std::tuple{ reaction2, group2, 4 } == chunk.keys()[15] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO