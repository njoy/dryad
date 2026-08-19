// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/createMultigroupReactionProducts.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createMultigroupReactionProducts" ) {

  using GTape = njoy::ENDFtk::tree::GTape;
  auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.gendf" );
  auto material = tape.materials().front();

  std::vector< double > boundaries = {

    1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0,
    8.320000e+0, 2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2,
    1.235000e+3, 3.350000e+3, 9.120000e+3, 2.480000e+4, 6.760000e+4,
    1.840000e+5, 3.030000e+5, 5.000000e+5, 8.230000e+5, 1.353000e+6,
    1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6, 6.070000e+6,
    7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
    1.700000e+7
  };
  std::size_t dilution = 0;

  GIVEN( "a reaction identifier with a single outgoing particle and a residual" ) {

    WHEN( "the reaction products are created" ) {

      // elastic: neutron and residual
      auto products = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->n,U235" ),
                                                                     material, 2, boundaries, dilution );

      THEN( "the outgoing particles and residual are returned" ) {

        CHECK( 2 == products.size() );

        CHECK( id::ParticleID( "n" ) == products[0].productIdentifier() );
        CHECK( 0 == products[0].chainIndex() );
        CHECK( std::nullopt == products[0].parentIdentifier() );
        CHECK( true == std::holds_alternative< int >( products[0].multiplicity() ) );
        CHECK( 1 == std::get< int >( products[0].multiplicity() ) );
        CHECK( true == products[0].hasAverageCosine() );
        CHECK( 30 == products[0].averageCosine()->numberGroups() );
        CHECK_THAT( 1.390000e-4, WithinRel( products[0].averageCosine()->boundaries().front() ) );
        CHECK_THAT( 1.700000e+7, WithinRel( products[0].averageCosine()->boundaries().back() ) );
        CHECK_THAT( 0.002934899, WithinRel( products[0].averageCosine()->values().front() ) );
        CHECK_THAT( 0.9240258, WithinRel( products[0].averageCosine()->values().back() ) );

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
      auto products = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->2n,U234[all]" ),
                                                                     material, 16, boundaries, dilution );

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

      auto products = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->g,U236[all]" ),
                                                                     material, 102, boundaries, dilution );

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

      auto anything = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->anything" ),
                                                                     material, 5, boundaries, dilution );
      auto fission = gendf::read::createMultigroupReactionProducts( id::ReactionID( "n,U235->fission(t)" ),
                                                                     material, 18, boundaries, dilution );

      THEN( "no reaction products are created" ) {

        CHECK( 0 == anything.size() );
        CHECK( 0 == fission.size() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
