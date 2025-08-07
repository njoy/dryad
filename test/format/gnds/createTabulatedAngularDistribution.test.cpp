// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createTabulatedAngularDistribution.hpp"

// other includes
#include "dryad/format/gnds/readAxes.hpp"
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const std::pair< std::optional< double >,
                                   TabulatedAngularDistribution >&, bool );

SCENARIO( "createTabulatedAngularDistribution" ) {

  GIVEN( "GNDS two body distribution data node with tabulated angular data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).
                                   child( "incompleteReactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "525" ).
                                   child( "outputChannel" ).
                                   child( "products" ).
                                   find_child_by_attribute( "product", "label", "e-" ).
                                   child( "distribution" ).child( "angularTwoBody" ).
                                   child( "XYs2d" );

    auto axes = format::gnds::readAxes( node.child( "axes" ) );
    pugi::xml_node xys1d = node.child( "function1ds" ).child( "XYs1d" );

    WHEN( "a single two body data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk1 = format::gnds::createTabulatedAngularDistribution( xys1d, axes, false );
        auto chunk2 = format::gnds::createTabulatedAngularDistribution( xys1d, axes, true );

        verifyChunk( chunk1, false );
        verifyChunk( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::pair< std::optional< double >,
                                   TabulatedAngularDistribution >& chunk,
                  bool normalise ) {

  CHECK_THAT( 10., WithinRel( chunk.first.value() ) );

  CHECK(  2 == chunk.second.pdf().cosines().size() );
  CHECK(  2 == chunk.second.pdf().values().size() );

  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double normalisation00 = normalise ? 0.9999995 : 1.;

  CHECK_THAT( -1.                   , WithinRel( chunk.second.pdf().cosines()[0] ) );
  CHECK_THAT(  0.999999             , WithinRel( chunk.second.pdf().cosines()[1] ) );
  CHECK_THAT(  0.5 / normalisation00, WithinRel( chunk.second.pdf().values()[0] ) );
  CHECK_THAT(  0.5 / normalisation00, WithinRel( chunk.second.pdf().values()[1] ) );

  CHECK(  2 == chunk.second.cdf().cosines().size() );
  CHECK(  2 == chunk.second.cdf().values().size() );

  CHECK_THAT( -1.                                    , WithinRel( chunk.second.cdf().cosines()[0] ) );
  CHECK_THAT(  0.999999                              , WithinRel( chunk.second.cdf().cosines()[1] ) );
  CHECK_THAT(  0.            / normalisation00       , WithinRel( chunk.second.cdf().values()[0] ) );
  CHECK_THAT(  1.999999 / 2. / normalisation00       , WithinRel( chunk.second.cdf().values()[1] ) );
}
