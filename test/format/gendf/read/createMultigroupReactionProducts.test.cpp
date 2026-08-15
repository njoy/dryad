// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "njoy/format/gendf/read/createMultigroupReactionProducts.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createMultigroupReactionProducts" ) {

  GIVEN( "a reaction identifier with a single outgoing particle and a residual" ) {

    WHEN( "the reaction products are created" ) {

      // elastic: neutron and residual
      auto products = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->n,U235" ) );

      THEN( "the outgoing particles and residual are returned" ) {

        CHECK( 2 == products.size() );

        CHECK( id::ParticleID( "n" ) == products[0].productIdentifier() );
        CHECK( 0 == products[0].chainIndex() );
        CHECK( std::nullopt == products[0].parentIdentifier() );
        CHECK( true == std::holds_alternative< int >( products[0].multiplicity() ) );
        CHECK( 1 == std::get< int >( products[0].multiplicity() ) );
        CHECK( false == products[0].hasAverageCosine() );

        CHECK( id::ParticleID( "U235" ) == products[1].productIdentifier() );
        CHECK( 0 == products[1].chainIndex() );
        CHECK( std::nullopt == products[1].parentIdentifier() );
        CHECK( true == std::holds_alternative< int >( products[1].multiplicity() ) );
        CHECK( 1 == std::get< int >( products[1].multiplicity() ) );
        CHECK( false == products[1].hasAverageCosine() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a reaction identifier with a multiplicity larger than one" ) {

    WHEN( "the reaction products are created" ) {

      // (n,2n): two neutrons and the residual
      auto products = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->2n,U234[all]" ) );

      THEN( "the outgoing particles and residual are returned" ) {

        CHECK( 2 == products.size() );

        CHECK( id::ParticleID( "n" ) == products[0].productIdentifier() );
        CHECK( 0 == products[0].chainIndex() );
        CHECK( std::nullopt == products[0].parentIdentifier() );
        CHECK( true == std::holds_alternative< int >( products[0].multiplicity() ) );
        CHECK( 2 == std::get< int >( products[0].multiplicity() ) );
        CHECK( false == products[0].hasAverageCosine() );

        CHECK( id::ParticleID( "U234[all]" ) == products[1].productIdentifier() );
        CHECK( 0 == products[1].chainIndex() );
        CHECK( std::nullopt == products[1].parentIdentifier() );
        CHECK( true == std::holds_alternative< int >( products[1].multiplicity() ) );
        CHECK( 1 == std::get< int >( products[1].multiplicity() ) );
        CHECK( false == products[1].hasAverageCosine() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a capture reaction identifier" ) {

    WHEN( "the reaction products are created" ) {

      auto products = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->g,U236[all]" ) );

      THEN( "the outgoing particles and residual are returned" ) {

        CHECK( 2 == products.size() );

        CHECK( id::ParticleID( "g" ) == products[0].productIdentifier() );
        CHECK( 0 == products[0].chainIndex() );
        CHECK( std::nullopt == products[0].parentIdentifier() );
        CHECK( true == std::holds_alternative< int >( products[0].multiplicity() ) );
        CHECK( 1 == std::get< int >( products[0].multiplicity() ) );
        CHECK( false == products[0].hasAverageCosine() );

        CHECK( id::ParticleID( "U236[all]" ) == products[1].productIdentifier() );
        CHECK( 0 == products[1].chainIndex() );
        CHECK( std::nullopt == products[1].parentIdentifier() );
        CHECK( true == std::holds_alternative< int >( products[1].multiplicity() ) );
        CHECK( 1 == std::get< int >( products[1].multiplicity() ) );
        CHECK( false == products[1].hasAverageCosine() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "reaction identifiers without defined outgoing particles" ) {

    WHEN( "the reaction products are created" ) {

      auto anything = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->anything" ) );
      auto fission = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->fission(t)" ) );

      THEN( "no reaction products are created" ) {

        CHECK( 0 == anything.size() );
        CHECK( 0 == fission.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
