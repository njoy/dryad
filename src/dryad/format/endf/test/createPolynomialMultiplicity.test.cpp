// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createPolynomialMultiplicity.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyFissionChunk( const PolynomialMultiplicity& );

SCENARIO( "createPolynomialMultiplicity" ) {

  GIVEN( "ENDF MF1 nubar polynomial multiplicities" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-090_Th_230.endf" );
    auto section = tape.materials().front().section( 1, 452 ).parse< 1, 452 >();
    auto multiplicity = std::get< njoy::ENDFtk::section::PolynomialMultiplicity >( section.nubar() );

    WHEN( "a single parsed MF6 multiplicity is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createPolynomialMultiplicity( 1e-5, 2e+7, multiplicity );

        verifyFissionChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyFissionChunk( const PolynomialMultiplicity& chunk ) {

  CHECK( 2 == chunk.coefficients().size() );
  CHECK( 1 == chunk.order() );
  CHECK_THAT( 2.01, WithinRel( chunk.coefficients()[0] ) );
  CHECK_THAT( 1e-7, WithinRel( chunk.coefficients()[1] ) );
}
