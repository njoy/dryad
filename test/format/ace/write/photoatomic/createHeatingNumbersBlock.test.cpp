// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/photoatomic/createAceHeatingNumbersBlock.hpp"

// other includes
#include "njoy/dryad/format/endf/createAtomicRelaxationFromFile.hpp"
#include "njoy/dryad/format/endf/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createAceHeatingNumbersBlock" ) {

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z < 12" ) {

    WHEN( "correct data is given" ) {

      auto atomic = format::endf::createAtomicRelaxationFromFile( "atom-001_H_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated and is empty" ) {

        auto block = format::ace::photoatomic::createAceHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 2021 == block.NES() );

//! @todo finish test
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 12 and z < 31" ) {

    WHEN( "correct data is given" ) {

      auto atomic = format::endf::createAtomicRelaxationFromFile( "atom-029_Cu_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-029_Cu_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::photoatomic::createAceHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 7314 == block.NES() );

//! @todo finish test
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 31 and z < 36" ) {

    WHEN( "correct data is given" ) {

      auto atomic = format::endf::createAtomicRelaxationFromFile( "atom-032_Ge_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-032_Ge_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::photoatomic::createAceHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 8513 == block.NES() );

//! @todo finish test
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 37" ) {

    WHEN( "correct data is given" ) {

      auto atomic = format::endf::createAtomicRelaxationFromFile( "atom-094_Pu_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-094_Pu_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated" ) {

        auto block = format::ace::photoatomic::createAceHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 12396 == block.NES() );

//! @todo finish test
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
