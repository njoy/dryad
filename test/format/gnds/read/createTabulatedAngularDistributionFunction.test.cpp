// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createTabulatedAngularDistributionFunction.hpp"

// other includes
#include "njoy/format/gnds/read/readAxes.hpp"
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const std::pair< std::optional< double >,
                                   TabulatedAngularDistributionFunction >& );

SCENARIO( "createTabulatedAngularDistributionFunction" ) {

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
    pugi::xml_node xys1d = node.child( "function1ds" ).child( "XYs1d" );

    WHEN( "a single two body data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::createTabulatedAngularDistributionFunction( xys1d, axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::pair< std::optional< double >,
                                   TabulatedAngularDistributionFunction >& chunk ) {

  CHECK_THAT( 10., WithinRel( chunk.first.value() ) );

  CHECK(  2 == chunk.second.cosines().size() );
  CHECK(  2 == chunk.second.values().size() );

  CHECK_THAT( -1.      , WithinRel( chunk.second.cosines()[0] ) );
  CHECK_THAT(  0.999999, WithinRel( chunk.second.cosines()[1] ) );
  CHECK_THAT(  0.5     , WithinRel( chunk.second.values()[0] ) );
  CHECK_THAT(  0.5     , WithinRel( chunk.second.values()[1] ) );
}
