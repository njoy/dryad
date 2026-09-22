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
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 2021 == block.NES() );
        CHECK( 2021 == block.heating().size() );

        CHECK_THAT( 5.66951513548201e-14, WithinRel( block.heating()[0] ) );
        CHECK_THAT( 8.06057233517367e-04, WithinRel( block.heating()[505] ) );
        CHECK_THAT( 3.15731954259184e-01, WithinRel( block.heating()[1010] ) );
        CHECK_THAT( 3.24225663054988e+00, WithinRel( block.heating()[1515] ) );
        CHECK_THAT( 9.99907803034981e+04, WithinRel( block.heating()[2020] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 12 and z < 31" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-029_Cu_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-029_Cu_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 7314 == block.NES() );
        CHECK( 7314 == block.heating().size() );

        CHECK_THAT( 7.59986547084122e-14, WithinRel( block.heating()[0] ) );
        CHECK_THAT( 6.28719866458501e-03, WithinRel( block.heating()[1828] ) );
        CHECK_THAT( 6.90581043148343e-02, WithinRel( block.heating()[3657] ) );
        CHECK_THAT( 9.44006142905027e+00, WithinRel( block.heating()[5485] ) );
        CHECK_THAT( 9.99981976231828e+04, WithinRel( block.heating()[7313] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 31 and z < 36" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-032_Ge_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-032_Ge_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 8513 == block.NES() );
        CHECK( 8513 == block.heating().size() );

        CHECK_THAT( 2.78376701970445e-14, WithinRel( block.heating()[0] ) );
        CHECK_THAT( 5.35403196253482e-03, WithinRel( block.heating()[2128] ) );
        CHECK_THAT( 7.50190061717532e-02, WithinRel( block.heating()[4256] ) );
        CHECK_THAT( 1.04814078890686e+01, WithinRel( block.heating()[6384] ) );
        CHECK_THAT( 9.99982594042480e+04, WithinRel( block.heating()[8512] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 37" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-094_Pu_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-094_Pu_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 12396 == block.NES() );
        CHECK( 12396 == block.heating().size() );

        CHECK_THAT( 6.18306127716396e-14, WithinRel( block.heating()[0], 5e-10 ) );
        CHECK_THAT( 1.00464768820740e-02, WithinRel( block.heating()[3099] ) );
        CHECK_THAT( 1.37726983856500e-02, WithinRel( block.heating()[6198] ) );
        CHECK_THAT( 1.31606138907762e+00, WithinRel( block.heating()[9297] ) );
        CHECK_THAT( 9.99986706059987e+04, WithinRel( block.heating()[12395] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
