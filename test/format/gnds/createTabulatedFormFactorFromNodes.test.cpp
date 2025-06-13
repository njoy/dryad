// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createTabulatedFormFactorFromNodes.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedFormFactor& );

SCENARIO( "createTabulatedFormFactorFromNodes" ) {

  GIVEN( "GNDS form factor node from photoatomic data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "photoat-001_H_000.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "502" ).
                                   child( "doubleDifferentialCrossSection" ).
                                   child( "coherentPhotonScattering" ).
                                   child( "realAnomalousFactor" ).
                                   first_child();

    WHEN( "a single form factor node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createTabulatedFormFactorFromNodes( node );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedFormFactor& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 297 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 297 == chunk.energies().size() );
  CHECK( 297 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 296 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT( 1.        , WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 2.        , WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 9549925.86, WithinRel( chunk.energies()[295] ) );
  CHECK_THAT( 1e+7      , WithinRel( chunk.energies()[296] ) );
  CHECK_THAT( -1.00260813, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( -1.01054501, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 2.8024E-11, WithinRel( chunk.values()[295] ) );
  CHECK_THAT( 0.        , WithinRel( chunk.values()[296] ) );
}
