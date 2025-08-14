// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createTabulatedEnergyDistribution.hpp"

// other includes
#include "dryad/format/gnds/readAxes.hpp"
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const std::pair< std::optional< double >,
                                   TabulatedEnergyDistribution >&, bool );

SCENARIO( "createTabulatedEnergyDistribution" ) {

  GIVEN( "GNDS two body distribution data node with tabulated energy distribution data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).
                                   child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "527" ).
                                   child( "outputChannel" ).
                                   child( "products" ).
                                   find_child_by_attribute( "product", "label", "photon" ).
                                   child( "distribution" ).child( "uncorrelated" ).
                                   child( "energy" ).child( "XYs2d" );

    auto axes = format::gnds::readAxes( node.child( "axes" ) );
    pugi::xml_node xys1d = node.child( "function1ds" ).child( "XYs1d" );

    WHEN( "a single two body data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk1 = format::gnds::createTabulatedEnergyDistribution( xys1d, axes, false );
        auto chunk2 = format::gnds::createTabulatedEnergyDistribution( xys1d, axes, true );

        verifyChunk( chunk1, false );
        verifyChunk( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::pair< std::optional< double >,
                                   TabulatedEnergyDistribution >& chunk,
                  bool normalise ) {

  CHECK_THAT( 10., WithinRel( chunk.first.value() ) );

  CHECK( 17 == chunk.second.pdf().energies().size() );
  CHECK( 17 == chunk.second.pdf().values().size() );

  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double normalisation00 = normalise ? 0.99999998809250 : 1.;

  CHECK_THAT(        0.1        , WithinRel( chunk.second.pdf().energies()[0] ) );
  CHECK_THAT(        0.133352   , WithinRel( chunk.second.pdf().energies()[1] ) );
  CHECK_THAT(        9.9        , WithinRel( chunk.second.pdf().energies()[15] ) );
  CHECK_THAT(       10.         , WithinRel( chunk.second.pdf().energies()[16] ) );
  CHECK_THAT(        2.1394     / normalisation00, WithinRel( chunk.second.pdf().values()[0] ) );
  CHECK_THAT(        1.60421    / normalisation00, WithinRel( chunk.second.pdf().values()[1] ) );
  CHECK_THAT(         .0214392  / normalisation00, WithinRel( chunk.second.pdf().values()[15] ) );
  CHECK_THAT(         .0212245  / normalisation00, WithinRel( chunk.second.pdf().values()[16] ) );

  CHECK( 17 == chunk.second.cdf().energies().size() );
  CHECK( 17 == chunk.second.cdf().values().size() );

  CHECK_THAT(        0.1        , WithinRel( chunk.second.cdf().energies()[0] ) );
  CHECK_THAT(        0.133352   , WithinRel( chunk.second.cdf().energies()[1] ) );
  CHECK_THAT(        9.9        , WithinRel( chunk.second.cdf().energies()[15] ) );
  CHECK_THAT(       10.         , WithinRel( chunk.second.cdf().energies()[16] ) );
  CHECK_THAT(   0.              / normalisation00, WithinRel( chunk.second.cdf().values()[0] ) );
  CHECK_THAT(   0.06242844036   / normalisation00, WithinRel( chunk.second.cdf().values()[1] ) );
  CHECK_THAT(   0.9978668030925 / normalisation00, WithinRel( chunk.second.cdf().values()[15] ) );
  CHECK_THAT(   0.9999999880925 / normalisation00, WithinRel( chunk.second.cdf().values()[16] ) );
}
