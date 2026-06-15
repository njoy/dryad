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

SCENARIO( "createHeatingNumbersBlock" ) {

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z < 12" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-001_H_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();

      THEN( "the ace block can be generated and is empty" ) {

        auto block = ace::write::photoatomic::createHeatingNumbersBlock( photoatomic, atomic );

        CHECK( 2021 == block.NES() );

//! @todo finish test
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

//! @todo finish test
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

//! @todo finish test
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

//! @todo finish test
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
