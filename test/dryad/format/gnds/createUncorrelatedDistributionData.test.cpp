// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createUncorrelatedDistributionData.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const UncorrelatedDistributionData&, bool );

SCENARIO( "createUncorrelatedDistributionData" ) {

  GIVEN( "GNDS uncorrelated distribution data node with isotropic angular and tabulated energy" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "527" ).
                                   child( "outputChannel" ).
                                   child( "products" ).
                                   find_child_by_attribute( "product", "label", "photon" ).
                                   child( "distribution" );

    pugi::xml_node uncorrelated = node.child( "uncorrelated" );

    WHEN( "a single uncorrelated data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk1 = format::gnds::createUncorrelatedDistributionData( uncorrelated, false );
        auto chunk2 = format::gnds::createUncorrelatedDistributionData( uncorrelated, true );

        verifyChunk( chunk1, false );
        verifyChunk( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const UncorrelatedDistributionData& chunk, bool normalise ) {

  CHECK( DistributionDataType::Uncorrelated == chunk.type() );
  CHECK( true == std::holds_alternative< IsotropicAngularDistributions >( chunk.angle() ) );
  CHECK( true == std::holds_alternative< TabulatedEnergyDistributions >( chunk.energy() ) );
  auto energy = std::get< TabulatedEnergyDistributions >( chunk.energy() );

  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double normalisation00 = normalise ? 0.99999998809250 : 1.;
  double normalisation01 = normalise ? 0.99999998353900 : 1.;
  double normalisation08 = normalise ? 0.99999973884057 : 1.;
  double normalisation09 = normalise ? 0.99999993564706 : 1.;

  CHECK( 10 == energy.numberPoints() );
  CHECK( 1 == energy.numberRegions() );
  CHECK( 10 == energy.grid().size() );
  CHECK( 10 == energy.distributions().size() );
  CHECK( 1 == energy.boundaries().size() );
  CHECK( 1 == energy.interpolants().size() );
  CHECK_THAT(   10.   , WithinRel( energy.grid()[0] ) );
  CHECK_THAT(   20.736, WithinRel( energy.grid()[1] ) );
  CHECK_THAT(   1e+7  , WithinRel( energy.grid()[8] ) );
  CHECK_THAT(   1e+11 , WithinRel( energy.grid()[9] ) );
  CHECK(  17 == energy.distributions()[0].pdf().energies().size() );
  CHECK(  17 == energy.distributions()[0].pdf().values().size() );
  CHECK(  19 == energy.distributions()[1].pdf().energies().size() );
  CHECK(  19 == energy.distributions()[1].pdf().values().size() );
  CHECK(  85 == energy.distributions()[8].pdf().energies().size() );
  CHECK(  85 == energy.distributions()[8].pdf().values().size() );
  CHECK( 111 == energy.distributions()[9].pdf().energies().size() );
  CHECK( 111 == energy.distributions()[9].pdf().values().size() );
  CHECK_THAT(        0.1        , WithinRel( energy.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT(        0.133352   , WithinRel( energy.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT(        9.9        , WithinRel( energy.distributions()[0].pdf().energies()[15] ) );
  CHECK_THAT(       10.         , WithinRel( energy.distributions()[0].pdf().energies()[16] ) );
  CHECK_THAT(        2.1394     / normalisation00, WithinRel( energy.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(        1.60421    / normalisation00, WithinRel( energy.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT(         .0214392  / normalisation00, WithinRel( energy.distributions()[0].pdf().values()[15] ) );
  CHECK_THAT(         .0212245  / normalisation00, WithinRel( energy.distributions()[0].pdf().values()[16] ) );
  CHECK_THAT(       0.1         , WithinRel( energy.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT(       0.14608     , WithinRel( energy.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT(      20.5286      , WithinRel( energy.distributions()[1].pdf().energies()[17] ) );
  CHECK_THAT(      20.736       , WithinRel( energy.distributions()[1].pdf().energies()[18] ) );
  CHECK_THAT(       1.84823     / normalisation01, WithinRel( energy.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(       1.26507     / normalisation01, WithinRel( energy.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT(        .00885527  / normalisation01, WithinRel( energy.distributions()[1].pdf().values()[17] ) );
  CHECK_THAT(        .00876641  / normalisation01, WithinRel( energy.distributions()[1].pdf().values()[18] ) );
  CHECK_THAT(        .100000000 , WithinRel( energy.distributions()[8].pdf().energies()[0] ) );
  CHECK_THAT(        .128640000 , WithinRel( energy.distributions()[8].pdf().energies()[1] ) );
  CHECK_THAT( 9981470.          , WithinRel( energy.distributions()[8].pdf().energies()[83] ) );
  CHECK_THAT(    1e+7           , WithinRel( energy.distributions()[8].pdf().energies()[84] ) );
  CHECK_THAT(        .608334000 / normalisation08, WithinRel( energy.distributions()[8].pdf().values()[0] ) );
  CHECK_THAT(        .472898000 / normalisation08, WithinRel( energy.distributions()[8].pdf().values()[1] ) );
  CHECK_THAT(       9.28343e-12 / normalisation08, WithinRel( energy.distributions()[8].pdf().values()[83] ) );
  CHECK_THAT(       5.8374e-12  / normalisation08, WithinRel( energy.distributions()[8].pdf().values()[84] ) );
  CHECK_THAT(        .100000000 , WithinRel( energy.distributions()[9].pdf().energies()[0] ) );
  CHECK_THAT(        .148551000 , WithinRel( energy.distributions()[9].pdf().energies()[1] ) );
  CHECK_THAT(       9.99082E+10 , WithinRel( energy.distributions()[9].pdf().energies()[109] ) );
  CHECK_THAT(   1e+11           , WithinRel( energy.distributions()[9].pdf().energies()[110] ) );
  CHECK_THAT(       .365591000  / normalisation09, WithinRel( energy.distributions()[9].pdf().values()[0] ) );
  CHECK_THAT(       .246105000  / normalisation09, WithinRel( energy.distributions()[9].pdf().values()[1] ) );
  CHECK_THAT(      9.06486E-16  / normalisation09, WithinRel( energy.distributions()[9].pdf().values()[109] ) );
  CHECK_THAT(      5.16344E-16  / normalisation09, WithinRel( energy.distributions()[9].pdf().values()[110] ) );
  CHECK(  17 == energy.distributions()[0].cdf().energies().size() );
  CHECK(  17 == energy.distributions()[0].cdf().values().size() );
  CHECK(  19 == energy.distributions()[1].cdf().energies().size() );
  CHECK(  19 == energy.distributions()[1].cdf().values().size() );
  CHECK(  85 == energy.distributions()[8].cdf().energies().size() );
  CHECK(  85 == energy.distributions()[8].cdf().values().size() );
  CHECK( 111 == energy.distributions()[9].cdf().energies().size() );
  CHECK( 111 == energy.distributions()[9].cdf().values().size() );
  CHECK_THAT(        0.1        , WithinRel( energy.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT(        0.133352   , WithinRel( energy.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT(        9.9        , WithinRel( energy.distributions()[0].cdf().energies()[15] ) );
  CHECK_THAT(       10.         , WithinRel( energy.distributions()[0].cdf().energies()[16] ) );
  CHECK_THAT(   0.              / normalisation00, WithinRel( energy.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(   0.06242844036   / normalisation00, WithinRel( energy.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT(   0.9978668030925 / normalisation00, WithinRel( energy.distributions()[0].cdf().values()[15] ) );
  CHECK_THAT(   0.9999999880925 / normalisation00, WithinRel( energy.distributions()[0].cdf().values()[16] ) );
  CHECK_THAT(       0.1         , WithinRel( energy.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT(       0.14608     , WithinRel( energy.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT(      20.5286      , WithinRel( energy.distributions()[1].cdf().energies()[17] ) );
  CHECK_THAT(      20.736       , WithinRel( energy.distributions()[1].cdf().energies()[18] ) );
  CHECK_THAT(   0.              / normalisation01, WithinRel( energy.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(   0.071730432     / normalisation01, WithinRel( energy.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT(   0.998172615323  / normalisation01, WithinRel( energy.distributions()[1].cdf().values()[17] ) );
  CHECK_THAT(   0.9999999835390 / normalisation01, WithinRel( energy.distributions()[1].cdf().values()[18] ) );
  CHECK_THAT(        .100000000 , WithinRel( energy.distributions()[8].cdf().energies()[0] ) );
  CHECK_THAT(        .128640000 , WithinRel( energy.distributions()[8].cdf().energies()[1] ) );
  CHECK_THAT( 9981470.          , WithinRel( energy.distributions()[8].cdf().energies()[83] ) );
  CHECK_THAT(    1e+7           , WithinRel( energy.distributions()[8].cdf().energies()[84] ) );
  CHECK_THAT(   0.              / normalisation08, WithinRel( energy.distributions()[8].cdf().values()[0] ) );
  CHECK_THAT(   0.01548324224   / normalisation08, WithinRel( energy.distributions()[8].cdf().values()[1] ) );
  CHECK_THAT(   0.99999959874608 / normalisation08, WithinRel( energy.distributions()[8].cdf().values()[83] ) );
  CHECK_THAT(   0.99999973884057 / normalisation08, WithinRel( energy.distributions()[8].cdf().values()[84] ) );
  CHECK_THAT(        .100000000 , WithinRel( energy.distributions()[9].cdf().energies()[0] ) );
  CHECK_THAT(        .148551000 , WithinRel( energy.distributions()[9].cdf().energies()[1] ) );
  CHECK_THAT(       9.99082E+10 , WithinRel( energy.distributions()[9].cdf().energies()[109] ) );
  CHECK_THAT(   1e+11           , WithinRel( energy.distributions()[9].cdf().energies()[110] ) );
  CHECK_THAT(   0.              / normalisation09, WithinRel( energy.distributions()[9].cdf().values()[0] ) );
  CHECK_THAT(   0.014849226248  / normalisation09, WithinRel( energy.distributions()[9].cdf().values()[1] ) );
  CHECK_THAT(   0.99999987033916 / normalisation09, WithinRel( energy.distributions()[9].cdf().values()[109] ) );
  CHECK_THAT(   0.99999993564706 / normalisation09, WithinRel( energy.distributions()[9].cdf().values()[110] ) );
  CHECK( 9 == energy.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );
}
