// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/thermal/createCoherentElasticScattering.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const thermal::CoherentElasticScattering& );

SCENARIO( "createCoherentElasticScattering" ) {

  GIVEN( "ENDF MF7 MT2 scattering law components" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "tsl-Be-metal.endf" );
    auto section = tape.materials().front().section( 7, 2 ).parse< 7, 2 >();
    auto coherent = std::get< njoy::ENDFtk::section::Type< 7, 2 >::CoherentElastic >( section.scatteringLaw() );

    WHEN( "a single parsed coherent thermal scattering component is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::thermal::createCoherentElasticScattering( 1e-5, 10., coherent );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const thermal::CoherentElasticScattering& chunk ) {

  CHECK_THAT( 1e-5, WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 10. , WithinRel( chunk.upperEnergyLimit() ) );

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
