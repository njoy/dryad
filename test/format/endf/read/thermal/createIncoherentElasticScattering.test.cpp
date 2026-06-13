// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/thermal/createIncoherentElasticScattering.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const thermal::IncoherentElasticScattering& );

SCENARIO( "createIncoherentElasticScattering" ) {

  GIVEN( "ENDF MF7 MT2 scattering law components" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "tsl-ZrinZrH.endf" );
    auto section = tape.materials().front().section( 7, 2 ).parse< 7, 2 >();
    auto incoherent = std::get< njoy::ENDFtk::section::Type< 7, 2 >::IncoherentElastic >( section.scatteringLaw() );

    WHEN( "a single parsed incoherent thermal scattering component is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = endf::read::thermal::createIncoherentElasticScattering( incoherent );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const thermal::IncoherentElasticScattering& chunk ) {

  CHECK_THAT( 6.337872, WithinRel( chunk.boundCrossSection() ) );

  CHECK( 8 == chunk.debyeWallerIntegral().temperatures().size() );
  CHECK( 8 == chunk.debyeWallerIntegral().values().size() );
  CHECK_THAT(  296, WithinRel( chunk.debyeWallerIntegral().temperatures()[0] ) );
  CHECK_THAT(  400, WithinRel( chunk.debyeWallerIntegral().temperatures()[1] ) );
  CHECK_THAT( 1000, WithinRel( chunk.debyeWallerIntegral().temperatures()[6] ) );
  CHECK_THAT( 1200, WithinRel( chunk.debyeWallerIntegral().temperatures()[7] ) );
  CHECK_THAT( 2.013538, WithinRel( chunk.debyeWallerIntegral().values()[0] ) );
  CHECK_THAT( 2.677764, WithinRel( chunk.debyeWallerIntegral().values()[1] ) );
  CHECK_THAT( 6.583171, WithinRel( chunk.debyeWallerIntegral().values()[6] ) );
  CHECK_THAT( 7.891981, WithinRel( chunk.debyeWallerIntegral().values()[7] ) );
}
