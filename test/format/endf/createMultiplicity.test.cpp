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
using Multiplicity = std::variant< int, TabulatedMultiplicity, PolynomialMultiplicity >;

void verifyFissionPolynomialChunk( const Multiplicity& );
void verifyFissionTabulatedChunk( const Multiplicity& );
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

  GIVEN( "ENDF MF1 polynomial nubar" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-094_Pu_237-jeff33.endf" );
    auto section = tape.materials().front().section( 1, 452 ).parse< 1, 452 >();
    auto multiplicity = std::get< njoy::ENDFtk::section::PolynomialMultiplicity >( section.nubar() );

    WHEN( "a single parsed MF6 multiplicity with a constant value is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createMultiplicity( 1e-5, 2e+7, multiplicity );

        verifyFissionPolynomialChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF1 tabulated nubar" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-093_Np_237.endf" );
    auto section = tape.materials().front().section( 1, 456 ).parse< 1, 456 >();
    auto multiplicity = std::get< njoy::ENDFtk::section::TabulatedMultiplicity >( section.nubar() );

    WHEN( "a single parsed MF6 multiplicity with a constant value is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createMultiplicity( 1e-5, 2e+7, multiplicity );

        verifyFissionTabulatedChunk( chunk );
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

void verifyFissionPolynomialChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< PolynomialMultiplicity >( chunk ) );

  auto multiplicity = std::get< PolynomialMultiplicity >( chunk );
  CHECK( 2 == multiplicity.coefficients().size() );
  CHECK( 1 == multiplicity.order() );

  CHECK_THAT( 1e-5, WithinRel( multiplicity.lowerEnergyLimit() ) );
  CHECK_THAT( 2e+7, WithinRel( multiplicity.upperEnergyLimit() ) );

  CHECK_THAT(   2.824, WithinRel( multiplicity.coefficients()[0] ) );
  CHECK_THAT( 1.42e-7, WithinRel( multiplicity.coefficients()[1] ) );
}

void verifyFissionTabulatedChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< TabulatedMultiplicity >( chunk ) );

  auto multiplicity = std::get< TabulatedMultiplicity >( chunk );
  CHECK( true == multiplicity.isLinearised() );
  CHECK( 6 == multiplicity.numberPoints() );
  CHECK( 1 == multiplicity.numberRegions() );
  CHECK( 6 == multiplicity.energies().size() );
  CHECK( 6 == multiplicity.values().size() );
  CHECK( 1 == multiplicity.boundaries().size() );
  CHECK( 1 == multiplicity.interpolants().size() );
  CHECK( 5 == multiplicity.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == multiplicity.interpolants()[0] );
  CHECK_THAT( 1.0e-5, WithinRel( multiplicity.energies()[0] ) );
  CHECK_THAT( 4.0e+6, WithinRel( multiplicity.energies()[1] ) );
  CHECK_THAT( 7.0e+6, WithinRel( multiplicity.energies()[2] ) );
  CHECK_THAT( 1.1e+7, WithinRel( multiplicity.energies()[3] ) );
  CHECK_THAT( 1.2e+7, WithinRel( multiplicity.energies()[4] ) );
  CHECK_THAT( 2.0e+7, WithinRel( multiplicity.energies()[5] ) );
  CHECK_THAT( 2.625000, WithinRel( multiplicity.values()[0] ) );
  CHECK_THAT( 3.224250, WithinRel( multiplicity.values()[1] ) );
  CHECK_THAT( 3.677437, WithinRel( multiplicity.values()[2] ) );
  CHECK_THAT( 4.324800, WithinRel( multiplicity.values()[3] ) );
  CHECK_THAT( 4.466900, WithinRel( multiplicity.values()[4] ) );
  CHECK_THAT( 5.520700, WithinRel( multiplicity.values()[5] ) );
}

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
