// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createMixedAngularDistributions.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const MixedAngularDistributions&, bool );

SCENARIO( "createMixedAngularDistributions" ) {

  GIVEN( "GNDS mixed angular data" ) {

    pugi::xml_document document;
    document.load_file( "n-010_Ne_022.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                   child( "outputChannel" ).
                                   child( "products" ).
                                   find_child_by_attribute( "product", "label", "n" ).
                                   child( "distribution" ).child( "angularTwoBody" );

    pugi::xml_node regions2d = node.child( "regions2d" );

    WHEN( "a single two body data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk1 = gnds::read::createMixedAngularDistributions( regions2d, false );
        auto chunk2 = gnds::read::createMixedAngularDistributions( regions2d, true );

        verifyChunk( chunk1, false );
        verifyChunk( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const MixedAngularDistributions& chunk, bool normalise ) {

  CHECK( 51 == chunk.numberPoints() );
  CHECK( 2 == chunk.numberRegions() );
  CHECK( 51 == chunk.grid().size() );
  CHECK( 51 == chunk.distributions().size() );
  CHECK( 2 == chunk.boundaries().size() );
  CHECK( 2 == chunk.interpolants().size() );
  CHECK_THAT( 1e-5 , WithinRel( chunk.grid()[0] ) );
  CHECK_THAT( 1e+5 , WithinRel( chunk.grid()[1] ) );
  CHECK_THAT( 3e+7 , WithinRel( chunk.grid()[35] ) );
  CHECK_THAT( 3e+7 , WithinRel( chunk.grid()[36] ) );
  CHECK_THAT( 16e+7, WithinRel( chunk.grid()[49] ) );
  CHECK_THAT( 20e+7, WithinRel( chunk.grid()[50] ) );
  CHECK( 35 == chunk.boundaries()[0] );
  CHECK( 50 == chunk.boundaries()[1] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[0].pdf() ) );
  CHECK( true == std::holds_alternative< LegendreAngularDistributionFunction >( chunk.distributions()[35].pdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[36].pdf() ) );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributionFunction >( chunk.distributions()[50].pdf() ) );

  auto pdf0 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[0].pdf() );
  auto pdf35 = std::get< LegendreAngularDistributionFunction >( chunk.distributions()[35].pdf() );
  auto pdf36 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[36].pdf() );
  auto pdf50 = std::get< TabulatedAngularDistributionFunction >( chunk.distributions()[50].pdf() );

  CHECK(  1 == pdf0.coefficients().size() );
  CHECK( 31 == pdf35.coefficients().size() );
  CHECK_THAT(  0.5        , WithinRel( pdf0.coefficients()[0] ) );
  CHECK_THAT(  0.5        , WithinRel( pdf35.coefficients()[0] ) );
  CHECK_THAT( -1.455580e-9 * 30.5, WithinRel( pdf35.coefficients()[30] ) );

  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double normalisation36 = normalise ? 0.99999988111130 : 1.;
  double normalisation50 = normalise ? 1.00000091921303 : 1.;

  CHECK( 91 == pdf36.cosines().size() );
  CHECK( 91 == pdf36.values().size() );
  CHECK(  1 == pdf36.interpolants().size() );
  CHECK(  1 == pdf36.boundaries().size() );
  CHECK( 91 == pdf50.cosines().size() );
  CHECK( 91 == pdf50.values().size() );
  CHECK(  1 == pdf50.interpolants().size() );
  CHECK(  1 == pdf50.boundaries().size() );
  CHECK( 90 == pdf36.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf36.interpolants()[0] );
  CHECK_THAT( -1., WithinRel( pdf36.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( pdf36.cosines()[90] ) );
  CHECK_THAT( 2.562149e-3 / normalisation36, WithinRel( pdf36.values()[0] ) );
  CHECK_THAT( 1.593952e+1 / normalisation36, WithinRel( pdf36.values()[90] ) );
  CHECK( 90 == pdf50.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf50.interpolants()[0] );
  CHECK_THAT( -1., WithinRel( pdf50.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( pdf50.cosines()[90] ) );
  CHECK_THAT( 7.050719e-7 / normalisation50, WithinRel( pdf50.values()[0] ) );
  CHECK_THAT( 7.964481e+1 / normalisation50, WithinRel( pdf50.values()[90] ) );
}
