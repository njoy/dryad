// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/photoatomic/createHeatingNumbersBlock.hpp"

// other includes
#include "njoy/format/endf/read/createAtomicRelaxationFromFile.hpp"
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// test result generated using the modern NJOY code after comparison with NJOY2016

SCENARIO( "createHeatingNumbersBlock" ) {

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z < 12" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-001_H_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-001_H_000.endf", true, true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 2021 == block.NES() );
        CHECK( 2021 == block.heating().size() );

        CHECK_THAT( 5.669515193837952e-14, WithinRel( block.heating()[0], 1e-8 ) );
        CHECK_THAT( 8.060572335180150e-04, WithinRel( block.heating()[505] ) );
        CHECK_THAT( 3.157319572260764e-01, WithinRel( block.heating()[1010] ) );
        CHECK_THAT( 3.242256612132395e+00, WithinRel( block.heating()[1515] ) );
        CHECK_THAT( 9.999078027392806e+04, WithinRel( block.heating()[2020], 1e-10 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 12 and z < 31" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-029_Cu_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-029_Cu_000.endf", true, true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 7314 == block.NES() );
        CHECK( 7314 == block.heating().size() );

        CHECK_THAT( 7.599865545986436e-14, WithinRel( block.heating()[0], 1e-8 ) );
        CHECK_THAT( 6.287198664583877e-03, WithinRel( block.heating()[1828] ) );
        CHECK_THAT( 6.905810333805126e-02, WithinRel( block.heating()[3657] ) );
        CHECK_THAT( 9.440061452189093e+00, WithinRel( block.heating()[5485] ) );
        CHECK_THAT( 9.999819762042005e+04, WithinRel( block.heating()[7313], 1e-10 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 31 and z < 36" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-032_Ge_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-032_Ge_000.endf", true, true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 8513 == block.NES() );
        CHECK( 8513 == block.heating().size() );

        CHECK_THAT( 2.783767048696003e-14, WithinRel( block.heating()[0], 1e-8 ) );
        CHECK_THAT( 5.354031962535011e-03, WithinRel( block.heating()[2128] ) );
        CHECK_THAT( 7.501900619644278e-02, WithinRel( block.heating()[4256] ) );
        CHECK_THAT( 1.048140788285556e+01, WithinRel( block.heating()[6384] ) );
        CHECK_THAT( 9.999825940170279e+04, WithinRel( block.heating()[8512], 1e-10 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 37" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-094_Pu_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-094_Pu_000.endf", true, true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 12396 == block.NES() );
        CHECK( 12396 == block.heating().size() );

        CHECK_THAT( 6.183061341056360e-14, WithinRel( block.heating()[0], 1e-08 ) );
        CHECK_THAT( 1.004647688207476e-02, WithinRel( block.heating()[3099] ) );
        CHECK_THAT( 1.377269835360243e-02, WithinRel( block.heating()[6198] ) );
        CHECK_THAT( 1.316061394675344e+00, WithinRel( block.heating()[9297] ) );
        CHECK_THAT( 9.999867060491102e+04, WithinRel( block.heating()[12395], 1e-10 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
