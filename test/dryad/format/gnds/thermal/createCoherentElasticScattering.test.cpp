// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/thermal/createCoherentElasticScattering.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const CoherentElasticScattering& );

SCENARIO( "createCoherentElasticScattering" ) {

  GIVEN( "GNDS coherent elastic node from tsl data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "tsl-Be-metal.endf.gnds.xml" );
    pugi::xml_node coherent = document.child( "reactionSuite" ).child( "reactions" ).
                                         find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                         child( "doubleDifferentialCrossSection" ).
                                         child( "thermalNeutronScatteringLaw_coherentElastic" );

    WHEN( "a single coherent elastic node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::thermal::createCoherentElasticScattering( coherent );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const CoherentElasticScattering& chunk ) {


  CHECK( 11 == chunk.numberModeratorTemperatures() );
  CHECK_THAT(   77, WithinRel( chunk.braggEdges()[0].temperature() ) );
  CHECK_THAT(  100, WithinRel( chunk.braggEdges()[1].temperature() ) );
  CHECK_THAT( 1000, WithinRel( chunk.braggEdges()[9].temperature() ) );
  CHECK_THAT( 1200, WithinRel( chunk.braggEdges()[10].temperature() ) );
  CHECK( 2306 == chunk.braggEdges()[0].numberBraggEdges() );
  CHECK( 2306 == chunk.braggEdges()[1].numberBraggEdges() );
  CHECK( 2306 == chunk.braggEdges()[9].numberBraggEdges() );
  CHECK( 2306 == chunk.braggEdges()[10].numberBraggEdges() );
  CHECK( 2306 == chunk.braggEdges()[0].energies().size() );
  CHECK( 2306 == chunk.braggEdges()[1].energies().size() );
  CHECK( 2306 == chunk.braggEdges()[9].energies().size() );
  CHECK( 2306 == chunk.braggEdges()[10].energies().size() );
  CHECK( 2306 == chunk.braggEdges()[0].values().size() );
  CHECK( 2306 == chunk.braggEdges()[1].values().size() );
  CHECK( 2306 == chunk.braggEdges()[9].values().size() );
  CHECK( 2306 == chunk.braggEdges()[10].values().size() );

  CHECK_THAT( 5.219736e-3, WithinRel( chunk.braggEdges()[0].energies().front() ) );
  CHECK_THAT( 5.219736e-3, WithinRel( chunk.braggEdges()[1].energies().front() ) );
  CHECK_THAT( 5.219736e-3, WithinRel( chunk.braggEdges()[9].energies().front() ) );
  CHECK_THAT( 5.219736e-3, WithinRel( chunk.braggEdges()[10].energies().front() ) );
  CHECK_THAT( 5., WithinRel( chunk.braggEdges()[0].energies().back() ) );
  CHECK_THAT( 5., WithinRel( chunk.braggEdges()[1].energies().back() ) );
  CHECK_THAT( 5., WithinRel( chunk.braggEdges()[9].energies().back() ) );
  CHECK_THAT( 5., WithinRel( chunk.braggEdges()[10].energies().back() ) );

  CHECK_THAT( 8.703783e-3, WithinRel( chunk.braggEdges()[0].values().front() ) );
  CHECK_THAT( 8.699222e-3, WithinRel( chunk.braggEdges()[1].values().front() ) );
  CHECK_THAT( 7.851222e-3, WithinRel( chunk.braggEdges()[9].values().front() ) );
  CHECK_THAT( 7.640495e-3, WithinRel( chunk.braggEdges()[10].values().front() ) );
  CHECK_THAT( 9.484639e-1, WithinRel( chunk.braggEdges()[0].values().back() ) );
  CHECK_THAT( 9.363035e-1, WithinRel( chunk.braggEdges()[1].values().back() ) );
  CHECK_THAT( 2.579243e-1, WithinRel( chunk.braggEdges()[9].values().back() ) );
  CHECK_THAT( 2.142492e-1, WithinRel( chunk.braggEdges()[10].values().back() ) );
}
