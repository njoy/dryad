// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/thermal/createTabulatedDebyeWallerIntegral.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::thermal;

void verifyChunk( const TabulatedDebyeWallerIntegral& );

SCENARIO( "createTabulatedDebyeWallerIntegral" ) {

  GIVEN( "ENDF MF7 MT2 scattering law components" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "tsl-ZrinZrH.endf" );
    auto section = tape.materials().front().section( 7, 2 ).parse< 7, 2 >();
    auto incoherent = std::get< njoy::ENDFtk::section::Type< 7, 2 >::IncoherentElastic >( section.scatteringLaw() );

    WHEN( "a single parsed incoherent thermal scattering component is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::thermal::createTabulatedDebyeWallerIntegral( incoherent );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedDebyeWallerIntegral& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 8 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 8 == chunk.temperatures().size() );
  CHECK( 8 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 7 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(  296, WithinRel( chunk.temperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( chunk.temperatures()[1] ) );
  CHECK_THAT( 1000, WithinRel( chunk.temperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( chunk.temperatures()[7] ) );
  CHECK_THAT( 2.013538, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 2.677764, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 6.583171, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 7.891981, WithinRel( chunk.values()[7] ) );
}
