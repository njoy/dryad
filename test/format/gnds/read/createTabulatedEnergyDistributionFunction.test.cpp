// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createTabulatedEnergyDistributionFunction.hpp"

// other includes
#include "njoy/format/gnds/read/readAxes.hpp"
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const std::pair< std::optional< double >,
                                   TabulatedEnergyDistributionFunction >& );

SCENARIO( "createTabulatedEnergyDistributionFunction" ) {

  GIVEN( "GNDS two body distribution data node with tabulated energy distribution data" ) {

    pugi::xml_document document;
    document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).
                                   child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "527" ).
                                   child( "outputChannel" ).
                                   child( "products" ).
                                   find_child_by_attribute( "product", "label", "photon" ).
                                   child( "distribution" ).child( "uncorrelated" ).
                                   child( "energy" ).child( "XYs2d" );

    auto axes = gnds::read::readAxes( node.child( "axes" ) );
    pugi::xml_node xys1d = node.child( "function1ds" ).child( "XYs1d" );

    WHEN( "a single two body data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::createTabulatedEnergyDistributionFunction( xys1d, axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::pair< std::optional< double >,
                                   TabulatedEnergyDistributionFunction >& chunk ) {

  CHECK_THAT( 10., WithinRel( chunk.first.value() ) );

  CHECK( 17 == chunk.second.energies().size() );
  CHECK( 17 == chunk.second.values().size() );

  CHECK_THAT(        0.1        , WithinRel( chunk.second.energies()[0] ) );
  CHECK_THAT(        0.133352   , WithinRel( chunk.second.energies()[1] ) );
  CHECK_THAT(        9.9        , WithinRel( chunk.second.energies()[15] ) );
  CHECK_THAT(       10.         , WithinRel( chunk.second.energies()[16] ) );
  CHECK_THAT(        2.1394     , WithinRel( chunk.second.values()[0] ) );
  CHECK_THAT(        1.60421    , WithinRel( chunk.second.values()[1] ) );
  CHECK_THAT(         .0214392  , WithinRel( chunk.second.values()[15] ) );
  CHECK_THAT(         .0212245  , WithinRel( chunk.second.values()[16] ) );
}
