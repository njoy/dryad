// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createTabulatedAngularDistributionFunctions.hpp"

// other includes
#include "njoy/format/gnds/read/readAxes.hpp"
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const std::pair< std::vector< std::optional< double > >,
                                   std::vector< TabulatedAngularDistributionFunction > >& );

SCENARIO( "createTabulatedAngularDistributionFunctions" ) {

  GIVEN( "GNDS two body distribution data node with tabulated angular data" ) {

    pugi::xml_document document;
    document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).
                                   child( "incompleteReactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "525" ).
                                   child( "outputChannel" ).
                                   child( "products" ).
                                   find_child_by_attribute( "product", "label", "e-" ).
                                   child( "distribution" ).child( "angularTwoBody" ).
                                   child( "XYs2d" );

    auto axes = gnds::read::readAxes( node.child( "axes" ) );
    pugi::xml_node function1ds = node.child( "function1ds" );

    WHEN( "a single two body data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::createTabulatedAngularDistributionFunctions( function1ds, axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::pair< std::vector< std::optional< double > >,
                                   std::vector< TabulatedAngularDistributionFunction > >& chunk ) {

  CHECK( 16 == chunk.first.size() );
  CHECK( 16 == chunk.second.size() );

  CHECK_THAT(       10., WithinRel( chunk.first[0].value() ) );
  CHECK_THAT(     1000., WithinRel( chunk.first[1].value() ) );
  CHECK_THAT( 66250000., WithinRel( chunk.first[14].value() ) );
  CHECK_THAT(     1e+11, WithinRel( chunk.first[15].value() ) );

  CHECK(  2 == chunk.second[0].cosines().size() );
  CHECK(  2 == chunk.second[0].values().size() );
  CHECK( 30 == chunk.second[1].cosines().size() );
  CHECK( 30 == chunk.second[1].values().size() );
  CHECK( 95 == chunk.second[14].cosines().size() );
  CHECK( 95 == chunk.second[14].values().size() );
  CHECK( 96 == chunk.second[15].cosines().size() );
  CHECK( 96 == chunk.second[15].values().size() );

  CHECK_THAT( -1.          , WithinRel( chunk.second[0].cosines()[0] ) );
  CHECK_THAT(  0.999999    , WithinRel( chunk.second[0].cosines()[1] ) );
  CHECK_THAT(  0.5         , WithinRel( chunk.second[0].values()[0] ) );
  CHECK_THAT(  0.5         , WithinRel( chunk.second[0].values()[1] ) );
  CHECK_THAT( -1.          , WithinRel( chunk.second[1].cosines()[0] ) );
  CHECK_THAT( -0.93        , WithinRel( chunk.second[1].cosines()[1] ) );
  CHECK_THAT(  0.9962001   , WithinRel( chunk.second[1].cosines()[28] ) );
  CHECK_THAT(  0.999999    , WithinRel( chunk.second[1].cosines()[29] ) );
  CHECK_THAT(  0.00293923  , WithinRel( chunk.second[1].values()[0] ) );
  CHECK_THAT(  0.00314865  , WithinRel( chunk.second[1].values()[1] ) );
  CHECK_THAT( 42.358       , WithinRel( chunk.second[1].values()[28] ) );
  CHECK_THAT( 62.1102      , WithinRel( chunk.second[1].values()[29] ) );
  CHECK_THAT( -1.          , WithinRel( chunk.second[14].cosines()[0] ) );
  CHECK_THAT( -0.995       , WithinRel( chunk.second[14].cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( chunk.second[14].cosines()[93] ) );
  CHECK_THAT(  0.999999    , WithinRel( chunk.second[14].cosines()[94] ) );
  CHECK_THAT(  1.51157e-11 , WithinRel( chunk.second[14].values()[0] ) );
  CHECK_THAT(  6.43040e-10 , WithinRel( chunk.second[14].values()[1] ) );
  CHECK_THAT(  8.14179e+5  , WithinRel( chunk.second[14].values()[93] ) );
  CHECK_THAT(  9.84753e+5  , WithinRel( chunk.second[14].values()[94] ) );
  CHECK_THAT( -1.          , WithinRel( chunk.second[15].cosines()[0] ) );
  CHECK_THAT( -0.9999      , WithinRel( chunk.second[15].cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( chunk.second[15].cosines()[94] ) );
  CHECK_THAT(  0.999999    , WithinRel( chunk.second[15].cosines()[95] ) );
  CHECK_THAT(  6.25670e-13 , WithinRel( chunk.second[15].values()[0] ) );
  CHECK_THAT(  1.25808e-11 , WithinRel( chunk.second[15].values()[1] ) );
  CHECK_THAT(  8.15658e+5  , WithinRel( chunk.second[15].values()[94] ) );
  CHECK_THAT(  9.86945e+5  , WithinRel( chunk.second[15].values()[95] ) );
}
