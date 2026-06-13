// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf7/createSammyBackground.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy;
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const dryad::resonances::SammyBackground& );

SCENARIO( "createParticlePairs" ) {

  GIVEN( "ENDF MF2 MT151 sections" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-038_Sr_088.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );
    auto background = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited::SammyBackgroundRMatrix >(
                        parameters.spinGroups()[0].background().backgroundRMatrices()[1].value() );

    WHEN( "a single parsed scattering radius from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::resonances::lrf7::createSammyBackground( background );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const dryad::resonances::SammyBackground& chunk ) {

  CHECK_THAT( -0.043, WithinRel( chunk.polynomialCoefficients()[0] ) );
  CHECK_THAT( 2.8e-8, WithinRel( chunk.polynomialCoefficients()[1] ) );
  CHECK_THAT( 0.    , WithinRel( chunk.polynomialCoefficients()[2] ) );
  CHECK_THAT( 0.01  , WithinRel( chunk.logarithmicCoefficients()[0] ) );
  CHECK_THAT( 0.    , WithinRel( chunk.logarithmicCoefficients()[1] ) );
  CHECK_THAT( 0.    , WithinRel( chunk.lowerSingularity() ) );
  CHECK_THAT( 9.55e5, WithinRel( chunk.upperSingularity() ) );

  CHECK_THAT( -0.043 + 2.8e-8 - 0.01 * std::log( 9.55e5 - 1. / 1. ), WithinRel( chunk( 1. ) ) );
}
