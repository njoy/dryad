// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createMultiplicity.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using Multiplicity = std::variant< int, TabulatedMultiplicity >;

void verifyNeutronConstantChunk( const Multiplicity& );
void verifyNeutronTabulatedChunk( const Multiplicity& );
void verifyElectronConstantChunk( const Multiplicity& );

//! @todo look for an electron example where the multiplicity is tabulated?

SCENARIO( "createMultiplicity" ) {

  GIVEN( "integer multiplicities" ) {

    WHEN( "a single parsed MF6 multiplicity with a constant value is given" ) {

      int multiplicity = 2;

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createMultiplicity( multiplicity );

        verifyNeutronConstantChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF6 multiplicities" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 6, 16 ).parse< 6 >();
    auto constant = section.reactionProduct( 1 ).multiplicity();
    auto tabulated = section.reactionProduct( 0 ).multiplicity();

    WHEN( "a single parsed MF6 multiplicity with a constant value is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createMultiplicity( constant );

        verifyNeutronConstantChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single parsed MF6 multiplicity with tabulated values is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createMultiplicity( tabulated );

        verifyNeutronTabulatedChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF26 multiplicities" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto section = tape.materials().front().section( 26, 527 ).parse< 26 >();
    auto constant = section.reactionProducts()[0].multiplicity();

    WHEN( "a single parsed MF6 multiplicity with a constant value is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createMultiplicity( constant );

        verifyElectronConstantChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyNeutronConstantChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< int >( chunk ) );

  auto multiplicity = std::get< int >( chunk );
  CHECK( 2 == multiplicity );
}

void verifyNeutronTabulatedChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< TabulatedMultiplicity >( chunk ) );

  auto multiplicity = std::get< TabulatedMultiplicity >( chunk );
  CHECK( true == multiplicity.isLinearised() );
  CHECK( 15 == multiplicity.numberPoints() );
  CHECK( 1 == multiplicity.numberRegions() );
  CHECK( 15 == multiplicity.energies().size() );
  CHECK( 15 == multiplicity.values().size() );
  CHECK( 1 == multiplicity.boundaries().size() );
  CHECK( 1 == multiplicity.interpolants().size() );
  CHECK( 14 == multiplicity.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == multiplicity.interpolants()[0] );
  CHECK_THAT( 1.300979e+7, WithinRel( multiplicity.energies()[0] ) );
  CHECK_THAT( 2e+7       , WithinRel( multiplicity.energies()[14] ) );
  CHECK_THAT( 0.8634751  , WithinRel( multiplicity.values()[0] ) );
  CHECK_THAT( 1.618791   , WithinRel( multiplicity.values()[14] ) );
}

void verifyElectronConstantChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< int >( chunk ) );

  auto multiplicity = std::get< int >( chunk );
  CHECK( 1 == multiplicity );
}
