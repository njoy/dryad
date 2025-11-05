// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createTwoBodyDistributionData.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunkLegendre( const TwoBodyDistributionData& );
void verifyChunkTabulated( const TwoBodyDistributionData&, bool );

SCENARIO( "createTwoBodyDistributionData" ) {

  GIVEN( "GNDS two body distribution data node with legendre angular data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                   child( "outputChannel" ).
                                   child( "products" ).
                                   find_child_by_attribute( "product", "label", "n" ).
                                   child( "distribution" );

    pugi::xml_node twobody = node.child( "angularTwoBody" );

    WHEN( "a single two body data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk1 = format::gnds::createTwoBodyDistributionData( twobody, false );
        auto chunk2 = format::gnds::createTwoBodyDistributionData( twobody, true );

        verifyChunkLegendre( chunk1 );
        verifyChunkLegendre( chunk2 );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS two body distribution data node with tabulated angular data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).
                                   child( "incompleteReactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "525" ).
                                   child( "outputChannel" ).
                                   child( "products" ).
                                   find_child_by_attribute( "product", "label", "e-" ).
                                   child( "distribution" );

    pugi::xml_node twobody = node.child( "angularTwoBody" );

    WHEN( "a single two body data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk1 = format::gnds::createTwoBodyDistributionData( twobody, false );
        auto chunk2 = format::gnds::createTwoBodyDistributionData( twobody, true );

        verifyChunkTabulated( chunk1, false );
        verifyChunkTabulated( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkLegendre( const TwoBodyDistributionData& chunk ) {

    CHECK( DistributionDataType::TwoBody == chunk.type() );
    CHECK( true == std::holds_alternative< LegendreAngularDistributions >( chunk.angle() ) );
    auto angle = std::get< LegendreAngularDistributions >( chunk.angle() );
    CHECK( 153 == angle.numberPoints() );
    CHECK( 1 == angle.numberRegions() );
    CHECK( 153 == angle.grid().size() );
    CHECK( 153 == angle.distributions().size() );
    CHECK( 1 == angle.boundaries().size() );
    CHECK( 1 == angle.interpolants().size() );
    CHECK_THAT( 1e-5   , WithinRel( angle.grid()[0] ) );
    CHECK_THAT( 2e-5   , WithinRel( angle.grid()[1] ) );
    CHECK_THAT( 1.95e+7, WithinRel( angle.grid()[151] ) );
    CHECK_THAT( 2e+7   , WithinRel( angle.grid()[152] ) );
    CHECK( 7 == angle.distributions()[0].pdf().coefficients().size() );
    CHECK( 7 == angle.distributions()[1].pdf().coefficients().size() );
    CHECK( 7 == angle.distributions()[151].pdf().coefficients().size() );
    CHECK( 7 == angle.distributions()[152].pdf().coefficients().size() );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].pdf().coefficients()[0] ) );
    CHECK_THAT( -1.7511000E-14  , WithinRel( angle.distributions()[0].pdf().coefficients()[1] ) );
    CHECK_THAT( -2.5280750E-16  , WithinRel( angle.distributions()[0].pdf().coefficients()[2] ) );
    CHECK_THAT( -6.4002050E-17  , WithinRel( angle.distributions()[0].pdf().coefficients()[3] ) );
    CHECK_THAT(  1.3653765E-16  , WithinRel( angle.distributions()[0].pdf().coefficients()[4] ) );
    CHECK_THAT( -1.7067215E-17  , WithinRel( angle.distributions()[0].pdf().coefficients()[5] ) );
    CHECK_THAT(  2.5600835E-17  , WithinRel( angle.distributions()[0].pdf().coefficients()[6] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[1].pdf().coefficients()[0] ) );
    CHECK_THAT( -3.4846950E-14  , WithinRel( angle.distributions()[1].pdf().coefficients()[1] ) );
    CHECK_THAT( -1.7387225E-16  , WithinRel( angle.distributions()[1].pdf().coefficients()[2] ) );
    CHECK_THAT( -9.1736400E-17  , WithinRel( angle.distributions()[1].pdf().coefficients()[3] ) );
    CHECK_THAT( -2.9867625E-17  , WithinRel( angle.distributions()[1].pdf().coefficients()[4] ) );
    CHECK_THAT( -3.4134430E-17  , WithinRel( angle.distributions()[1].pdf().coefficients()[5] ) );
    CHECK_THAT(  1.8773950E-16  , WithinRel( angle.distributions()[1].pdf().coefficients()[6] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[151].pdf().coefficients()[0] ) );
    CHECK_THAT( -2.4240045E-02  , WithinRel( angle.distributions()[151].pdf().coefficients()[1] ) );
    CHECK_THAT(  1.7942750E-02  , WithinRel( angle.distributions()[151].pdf().coefficients()[2] ) );
    CHECK_THAT( -2.54685165E-03 , WithinRel( angle.distributions()[151].pdf().coefficients()[3] ) );
    CHECK_THAT(  1.54781595E-03 , WithinRel( angle.distributions()[151].pdf().coefficients()[4] ) );
    CHECK_THAT(  4.91773975E-05 , WithinRel( angle.distributions()[151].pdf().coefficients()[5] ) );
    CHECK_THAT(  3.82748535E-05 , WithinRel( angle.distributions()[151].pdf().coefficients()[6] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[152].pdf().coefficients()[0] ) );
    CHECK_THAT( -2.41945200E-02 , WithinRel( angle.distributions()[152].pdf().coefficients()[1] ) );
    CHECK_THAT(  1.95173075E-02 , WithinRel( angle.distributions()[152].pdf().coefficients()[2] ) );
    CHECK_THAT( -2.71943700E-03 , WithinRel( angle.distributions()[152].pdf().coefficients()[3] ) );
    CHECK_THAT(  1.69449750E-03 , WithinRel( angle.distributions()[152].pdf().coefficients()[4] ) );
    CHECK_THAT(  5.25219970E-05 , WithinRel( angle.distributions()[152].pdf().coefficients()[5] ) );
    CHECK_THAT(  4.48370065E-05 , WithinRel( angle.distributions()[152].pdf().coefficients()[6] ) );
    CHECK( 8 == angle.distributions()[0].cdf().coefficients().size() );
    CHECK( 8 == angle.distributions()[1].cdf().coefficients().size() );
    CHECK( 8 == angle.distributions()[151].cdf().coefficients().size() );
    CHECK( 8 == angle.distributions()[152].cdf().coefficients().size() );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].cdf().coefficients()[1] ) );
    CHECK_THAT( -5.82785685e-15 , WithinRel( angle.distributions()[0].cdf().coefficients()[2] ) );
    CHECK_THAT( -6.57323500e-17 , WithinRel( angle.distributions()[0].cdf().coefficients()[3] ) );
    CHECK_THAT( -7.59158500e-18 , WithinRel( angle.distributions()[0].cdf().coefficients()[4] ) );
    CHECK_THAT(  1.32015550e-17 , WithinRel( angle.distributions()[0].cdf().coefficients()[5] ) );
    CHECK_THAT( -1.55156500e-18 , WithinRel( angle.distributions()[0].cdf().coefficients()[6] ) );
    CHECK_THAT(  1.96929500e-18 , WithinRel( angle.distributions()[0].cdf().coefficients()[7] ) );
    CHECK_THAT( 0.50000000000001, WithinRel( angle.distributions()[1].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[1].cdf().coefficients()[1] ) );
    CHECK_THAT( -1.16025448e-14 , WithinRel( angle.distributions()[1].cdf().coefficients()[2] ) );
    CHECK_THAT( -3.14558250e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[3] ) );
    CHECK_THAT( -1.00020700e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[4] ) );
    CHECK_THAT( -1.77601250e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[5] ) );
    CHECK_THAT( -3.10313000e-18 , WithinRel( angle.distributions()[1].cdf().coefficients()[6] ) );
    CHECK_THAT(  1.44415000e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[7] ) );
    CHECK_THAT(  5.08080015e-01 , WithinRel( angle.distributions()[151].cdf().coefficients()[0] ) );
    CHECK_THAT(  4.96411450e-01 , WithinRel( angle.distributions()[151].cdf().coefficients()[1] ) );
    CHECK_THAT( -7.71617905e-03 , WithinRel( angle.distributions()[151].cdf().coefficients()[2] ) );
    CHECK_THAT(  3.41657045e-03 , WithinRel( angle.distributions()[151].cdf().coefficients()[3] ) );
    CHECK_THAT( -3.683066225e-04, WithinRel( angle.distributions()[151].cdf().coefficients()[4] ) );
    CHECK_THAT(  1.690353305e-04, WithinRel( angle.distributions()[151].cdf().coefficients()[5] ) );
    CHECK_THAT(  4.47067250e-06 , WithinRel( angle.distributions()[151].cdf().coefficients()[6] ) );
    CHECK_THAT(  2.94421950e-06 , WithinRel( angle.distributions()[151].cdf().coefficients()[7] ) );
    CHECK_THAT(  5.08064840e-01 , WithinRel( angle.distributions()[152].cdf().coefficients()[0] ) );
    CHECK_THAT(  4.960965385e-01, WithinRel( angle.distributions()[152].cdf().coefficients()[1] ) );
    CHECK_THAT( -7.67634900e-03 , WithinRel( angle.distributions()[152].cdf().coefficients()[2] ) );
    CHECK_THAT(  3.71518400e-03 , WithinRel( angle.distributions()[152].cdf().coefficients()[3] ) );
    CHECK_THAT( -3.93265727e-04 , WithinRel( angle.distributions()[152].cdf().coefficients()[4] ) );
    CHECK_THAT(  1.848284995e-04, WithinRel( angle.distributions()[152].cdf().coefficients()[5] ) );
    CHECK_THAT(  4.77472700e-06 , WithinRel( angle.distributions()[152].cdf().coefficients()[6] ) );
    CHECK_THAT(  3.44900050e-06 , WithinRel( angle.distributions()[152].cdf().coefficients()[7] ) );
    CHECK( 152 == angle.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );
}

void verifyChunkTabulated( const TwoBodyDistributionData& chunk, bool normalise ) {

  CHECK( DistributionDataType::TwoBody == chunk.type() );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributions >( chunk.angle() ) );
  auto angle = std::get< TabulatedAngularDistributions >( chunk.angle() );
  CHECK( 16 == angle.numberPoints() );
  CHECK( 1 == angle.numberRegions() );
  CHECK( 16 == angle.grid().size() );
  CHECK( 16 == angle.distributions().size() );
  CHECK( 1 == angle.boundaries().size() );
  CHECK( 1 == angle.interpolants().size() );
  CHECK_THAT(       10., WithinRel( angle.grid()[0] ) );
  CHECK_THAT(     1000., WithinRel( angle.grid()[1] ) );
  CHECK_THAT( 66250000., WithinRel( angle.grid()[14] ) );
  CHECK_THAT(     1e+11, WithinRel( angle.grid()[15] ) );
  CHECK(  2 == angle.distributions()[0].pdf().cosines().size() );
  CHECK(  2 == angle.distributions()[0].pdf().values().size() );
  CHECK( 30 == angle.distributions()[1].pdf().cosines().size() );
  CHECK( 30 == angle.distributions()[1].pdf().values().size() );
  CHECK( 95 == angle.distributions()[14].pdf().cosines().size() );
  CHECK( 95 == angle.distributions()[14].pdf().values().size() );
  CHECK( 96 == angle.distributions()[15].pdf().cosines().size() );
  CHECK( 96 == angle.distributions()[15].pdf().values().size() );

  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double normalisation00 = normalise ? 0.9999995 : 1.;
  double normalisation01 = normalise ? 1.00000016366000 : 1.;
  double normalisation14 = normalise ? 1.00000048323214 : 1.;
  double normalisation15 = normalise ? 1.00000000937718 : 1.;

  CHECK_THAT( -1.                           , WithinRel( angle.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT(  0.999999                     , WithinRel( angle.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT(  0.5 / normalisation00        , WithinRel( angle.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0.5 / normalisation00        , WithinRel( angle.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( -1.                           , WithinRel( angle.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT( -0.93                         , WithinRel( angle.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9962001                    , WithinRel( angle.distributions()[1].pdf().cosines()[28] ) );
  CHECK_THAT(  0.999999                     , WithinRel( angle.distributions()[1].pdf().cosines()[29] ) );
  CHECK_THAT(  0.00293923 / normalisation01 , WithinRel( angle.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0.00314865 / normalisation01 , WithinRel( angle.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 42.358      / normalisation01 , WithinRel( angle.distributions()[1].pdf().values()[28] ) );
  CHECK_THAT( 62.1102     / normalisation01 , WithinRel( angle.distributions()[1].pdf().values()[29] ) );
  CHECK_THAT( -1.                           , WithinRel( angle.distributions()[14].pdf().cosines()[0] ) );
  CHECK_THAT( -0.995                        , WithinRel( angle.distributions()[14].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                    , WithinRel( angle.distributions()[14].pdf().cosines()[93] ) );
  CHECK_THAT(  0.999999                     , WithinRel( angle.distributions()[14].pdf().cosines()[94] ) );
  CHECK_THAT(  1.51157e-11 / normalisation14, WithinRel( angle.distributions()[14].pdf().values()[0] ) );
  CHECK_THAT(  6.43040e-10 / normalisation14, WithinRel( angle.distributions()[14].pdf().values()[1] ) );
  CHECK_THAT(  8.14179e+5 / normalisation14 , WithinRel( angle.distributions()[14].pdf().values()[93] ) );
  CHECK_THAT(  9.84753e+5 / normalisation14 , WithinRel( angle.distributions()[14].pdf().values()[94] ) );
  CHECK_THAT( -1.                           , WithinRel( angle.distributions()[15].pdf().cosines()[0] ) );
  CHECK_THAT( -0.9999                       , WithinRel( angle.distributions()[15].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                    , WithinRel( angle.distributions()[15].pdf().cosines()[94] ) );
  CHECK_THAT(  0.999999                     , WithinRel( angle.distributions()[15].pdf().cosines()[95] ) );
  CHECK_THAT(  6.25670e-13 / normalisation15, WithinRel( angle.distributions()[15].pdf().values()[0] ) );
  CHECK_THAT(  1.25808e-11 / normalisation15, WithinRel( angle.distributions()[15].pdf().values()[1] ) );
  CHECK_THAT(  8.15658e+5 / normalisation15 , WithinRel( angle.distributions()[15].pdf().values()[94] ) );
  CHECK_THAT(  9.86945e+5 / normalisation15 , WithinRel( angle.distributions()[15].pdf().values()[95] ) );

  CHECK(  2 == angle.distributions()[0].cdf().cosines().size() );
  CHECK(  2 == angle.distributions()[0].cdf().values().size() );
  CHECK( 30 == angle.distributions()[1].cdf().cosines().size() );
  CHECK( 30 == angle.distributions()[1].cdf().values().size() );
  CHECK( 95 == angle.distributions()[14].cdf().cosines().size() );
  CHECK( 95 == angle.distributions()[14].cdf().values().size() );
  CHECK( 96 == angle.distributions()[15].cdf().cosines().size() );
  CHECK( 96 == angle.distributions()[15].cdf().values().size() );

  CHECK_THAT( -1.                                    , WithinRel( angle.distributions()[0].cdf().cosines()[0] ) );
  CHECK_THAT(  0.999999                              , WithinRel( angle.distributions()[0].cdf().cosines()[1] ) );
  CHECK_THAT(  0.            / normalisation00       , WithinRel( angle.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(  1.999999 / 2. / normalisation00       , WithinRel( angle.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT( -1.                                    , WithinRel( angle.distributions()[1].cdf().cosines()[0] ) );
  CHECK_THAT( -0.93                                  , WithinRel( angle.distributions()[1].cdf().cosines()[1] ) );
  CHECK_THAT(  0.9962001                             , WithinRel( angle.distributions()[1].cdf().cosines()[28] ) );
  CHECK_THAT(  0.999999                              , WithinRel( angle.distributions()[1].cdf().cosines()[29] ) );
  CHECK_THAT(  0.0           / normalisation01       , WithinRel( angle.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(  0.0002130758  / normalisation01       , WithinRel( angle.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT(  0.80156804117 / normalisation01       , WithinRel( angle.distributions()[1].cdf().values()[28] ) );
  CHECK_THAT(  1.00000016366 / normalisation01       , WithinRel( angle.distributions()[1].cdf().values()[29] ) );
  CHECK_THAT( -1.                                    , WithinRel( angle.distributions()[14].cdf().cosines()[0] ) );
  CHECK_THAT( -0.995                                 , WithinRel( angle.distributions()[14].cdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                             , WithinRel( angle.distributions()[14].cdf().cosines()[93] ) );
  CHECK_THAT(  0.999999                              , WithinRel( angle.distributions()[14].cdf().cosines()[94] ) );
  CHECK_THAT(  0.               / normalisation14    , WithinRel( angle.distributions()[14].cdf().values()[0] ) );
  CHECK_THAT(  1.645389250e-12  / normalisation14    , WithinRel( angle.distributions()[14].cdf().values()[1] ) );
  CHECK_THAT(  0.91005388327948 / normalisation14    , WithinRel( angle.distributions()[14].cdf().values()[93] ) );
  CHECK_THAT(  1.00000048323214 / normalisation14    , WithinRel( angle.distributions()[14].cdf().values()[94] ) );
  CHECK_THAT( -1.                                    , WithinRel( angle.distributions()[15].cdf().cosines()[0] ) );
  CHECK_THAT( -0.9999                                , WithinRel( angle.distributions()[15].cdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                             , WithinRel( angle.distributions()[15].cdf().cosines()[94] ) );
  CHECK_THAT(  0.999999                              , WithinRel( angle.distributions()[15].cdf().cosines()[95] ) );
  CHECK_THAT(  0.                   / normalisation15, WithinRel( angle.distributions()[15].cdf().values()[0] ) );
  CHECK_THAT(  6.60323499999927e-16 / normalisation15, WithinRel( angle.distributions()[15].cdf().values()[1] ) );
  CHECK_THAT(  0.90986985942462     / normalisation15, WithinRel( angle.distributions()[15].cdf().values()[94] ) );
  CHECK_THAT(  1.00000000937718     / normalisation15, WithinRel( angle.distributions()[15].cdf().values()[95] ) );
}
