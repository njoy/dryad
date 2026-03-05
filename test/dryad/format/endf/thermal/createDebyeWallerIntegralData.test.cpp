// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/thermal/createDebyeWallerIntegralData.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const DebyeWallerIntegralData& );

SCENARIO( "createDebyeWallerIntegralData" ) {

  GIVEN( "ENDF MF7 MT2 scattering law components" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "tsl-ZrinZrH.endf" );
    auto section = tape.materials().front().section( 7, 2 ).parse< 7, 2 >();
    auto incoherent = std::get< njoy::ENDFtk::section::Type< 7, 2 >::IncoherentElastic >( section.scatteringLaw() );

    WHEN( "a single parsed incoherent thermal scattering component is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::thermal::createDebyeWallerIntegralData( incoherent );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const DebyeWallerIntegralData& chunk ) {

  CHECK( 8 == chunk.temperatures().size() );
  CHECK( 8 == chunk.values().size() );
  CHECK_THAT(  296, WithinRel( chunk.temperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( chunk.temperatures()[1] ) );
  CHECK_THAT( 1000, WithinRel( chunk.temperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( chunk.temperatures()[7] ) );
  CHECK_THAT( 2.013538, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 2.677764, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 6.583171, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 7.891981, WithinRel( chunk.values()[7] ) );
}
