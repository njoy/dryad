// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createTabulatedEnergyDistributionFunctions.hpp"

// other includes
#include "njoy/format/gnds/read/readAxes.hpp"
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const std::pair< std::vector< std::optional< double > >,
                                   std::vector< TabulatedEnergyDistributionFunction > >& );

SCENARIO( "createTabulatedEnergyDistributionFunctions" ) {

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
    pugi::xml_node function1ds = node.child( "function1ds" );

    WHEN( "a single two body data node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::createTabulatedEnergyDistributionFunctions( function1ds, axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::pair< std::vector< std::optional< double > >,
                                   std::vector< TabulatedEnergyDistributionFunction > >& chunk ) {

  CHECK( 10 == chunk.first.size() );
  CHECK( 10 == chunk.second.size() );

  CHECK_THAT(   10.   , WithinRel( chunk.first[0].value() ) );
  CHECK_THAT(   20.736, WithinRel( chunk.first[1].value() ) );
  CHECK_THAT(   1e+7  , WithinRel( chunk.first[8].value() ) );
  CHECK_THAT(   1e+11 , WithinRel( chunk.first[9].value() ) );

  CHECK(  17 == chunk.second[0].energies().size() );
  CHECK(  17 == chunk.second[0].values().size() );
  CHECK(  19 == chunk.second[1].energies().size() );
  CHECK(  19 == chunk.second[1].values().size() );
  CHECK(  85 == chunk.second[8].energies().size() );
  CHECK(  85 == chunk.second[8].values().size() );
  CHECK( 111 == chunk.second[9].energies().size() );
  CHECK( 111 == chunk.second[9].values().size() );
  CHECK_THAT(        0.1        , WithinRel( chunk.second[0].energies()[0] ) );
  CHECK_THAT(        0.133352   , WithinRel( chunk.second[0].energies()[1] ) );
  CHECK_THAT(        9.9        , WithinRel( chunk.second[0].energies()[15] ) );
  CHECK_THAT(       10.         , WithinRel( chunk.second[0].energies()[16] ) );
  CHECK_THAT(        2.1394     , WithinRel( chunk.second[0].values()[0] ) );
  CHECK_THAT(        1.60421    , WithinRel( chunk.second[0].values()[1] ) );
  CHECK_THAT(         .0214392  , WithinRel( chunk.second[0].values()[15] ) );
  CHECK_THAT(         .0212245  , WithinRel( chunk.second[0].values()[16] ) );
  CHECK_THAT(       0.1         , WithinRel( chunk.second[1].energies()[0] ) );
  CHECK_THAT(       0.14608     , WithinRel( chunk.second[1].energies()[1] ) );
  CHECK_THAT(      20.5286      , WithinRel( chunk.second[1].energies()[17] ) );
  CHECK_THAT(      20.736       , WithinRel( chunk.second[1].energies()[18] ) );
  CHECK_THAT(       1.84823     , WithinRel( chunk.second[1].values()[0] ) );
  CHECK_THAT(       1.26507     , WithinRel( chunk.second[1].values()[1] ) );
  CHECK_THAT(        .00885527  , WithinRel( chunk.second[1].values()[17] ) );
  CHECK_THAT(        .00876641  , WithinRel( chunk.second[1].values()[18] ) );
  CHECK_THAT(        .100000000 , WithinRel( chunk.second[8].energies()[0] ) );
  CHECK_THAT(        .128640000 , WithinRel( chunk.second[8].energies()[1] ) );
  CHECK_THAT( 9981470.          , WithinRel( chunk.second[8].energies()[83] ) );
  CHECK_THAT(    1e+7           , WithinRel( chunk.second[8].energies()[84] ) );
  CHECK_THAT(        .608334000 , WithinRel( chunk.second[8].values()[0] ) );
  CHECK_THAT(        .472898000 , WithinRel( chunk.second[8].values()[1] ) );
  CHECK_THAT(       9.28343e-12 , WithinRel( chunk.second[8].values()[83] ) );
  CHECK_THAT(       5.8374e-12  , WithinRel( chunk.second[8].values()[84] ) );
  CHECK_THAT(        .100000000 , WithinRel( chunk.second[9].energies()[0] ) );
  CHECK_THAT(        .148551000 , WithinRel( chunk.second[9].energies()[1] ) );
  CHECK_THAT(       9.99082E+10 , WithinRel( chunk.second[9].energies()[109] ) );
  CHECK_THAT(   1e+11           , WithinRel( chunk.second[9].energies()[110] ) );
  CHECK_THAT(       .365591000  , WithinRel( chunk.second[9].values()[0] ) );
  CHECK_THAT(       .246105000  , WithinRel( chunk.second[9].values()[1] ) );
  CHECK_THAT(      9.06486E-16  , WithinRel( chunk.second[9].values()[109] ) );
  CHECK_THAT(      5.16344E-16  , WithinRel( chunk.second[9].values()[110] ) );
}
