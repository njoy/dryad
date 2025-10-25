// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/resonances/lrf7/createBoundaryCondition.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "createBoundaryCondition" ) {

  GIVEN( "ENDF MF2 MT151 sections - Cl35 - ShiftFactor boundary condition" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );
    auto pairs = parameters.particlePairs();

    WHEN( "a single parsed particle pair component from MF2 MT151 is given" ) {

      THEN( "the boundary condition can be derived" ) {

        CHECK( resonances::BoundaryCondition::ShiftFactor
               == format::endf::resonances::lrf7::createBoundaryCondition( pairs ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF2 MT151 sections - Cu63 - Constant boundary condition" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-029_Cu_063.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );
    auto pairs = parameters.particlePairs();

    WHEN( "a single parsed particle pair component from MF2 MT151 is given" ) {

      THEN( "the boundary condition can be derived" ) {

        CHECK( resonances::BoundaryCondition::Constant
               == format::endf::resonances::lrf7::createBoundaryCondition( pairs ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
