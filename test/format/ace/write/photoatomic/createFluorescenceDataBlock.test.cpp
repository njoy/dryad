// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/photoatomic/createFluorescenceDataBlock.hpp"

// other includes
#include "njoy/format/endf/read/createAtomicRelaxationFromFile.hpp"
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createFluorescenceDataBlock" ) {

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z < 12" ) {

    WHEN( "correct data is given" ) {

      auto atomic = endf::read::createAtomicRelaxationFromFile( "atom-001_H_000.endf", true );
      atomic.calculateTransitionEnergies();
      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();

      THEN( "the ace block can be generated and is empty" ) {

        auto block = ace::write::photoatomic::createFluorescenceDataBlock( photoatomic, atomic );

        CHECK( 0 == block.NFLO() );
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

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createFluorescenceDataBlock( photoatomic, atomic );

        CHECK( 4 == block.NFLO() );
        CHECK( 4 == block.fluorescenceEdgeEnergies().size() );
        CHECK( 4 == block.relativeEjectionProbabilities().size() );
        CHECK( 4 == block.yields().size() );
        CHECK( 4 == block.fluorescentEnergies().size() );

        CHECK_THAT( 8986e-6, WithinRel( block.fluorescenceEdgeEnergies()[0] ) );
        CHECK_THAT( 8986e-6, WithinRel( block.fluorescenceEdgeEnergies()[1] ) );
        CHECK_THAT( 8986e-6, WithinRel( block.fluorescenceEdgeEnergies()[2] ) );
        CHECK_THAT( 8986e-6, WithinRel( block.fluorescenceEdgeEnergies()[3] ) );

        CHECK_THAT( 0.131177527809299, WithinRel( block.relativeEjectionProbabilities()[0] ) );
        CHECK_THAT( 0.643220353051359, WithinRel( block.relativeEjectionProbabilities()[1] ) );
        CHECK_THAT( 0.905820847453919, WithinRel( block.relativeEjectionProbabilities()[2] ) );
        CHECK_THAT( 1.               , WithinRel( block.relativeEjectionProbabilities()[3] ) );

        CHECK_THAT( 0.               , WithinRel( block.yields()[0] ) );
        CHECK_THAT( 0.222130065684762, WithinRel( block.yields()[1] ) );
        CHECK_THAT( 0.336049179858302, WithinRel( block.yields()[2] ) );
        CHECK_THAT( 0.376905179219891, WithinRel( block.yields()[3] ) );

        CHECK_THAT( 0.                 , WithinRel( block.fluorescentEnergies()[0] ) );
        CHECK_THAT( 8048e-6            , WithinRel( block.fluorescentEnergies()[1] ) );
        CHECK_THAT( 8028e-6            , WithinRel( block.fluorescentEnergies()[2] ) );
        CHECK_THAT( 8905.38889496365e-6, WithinRel( block.fluorescentEnergies()[3] ) );
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

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createFluorescenceDataBlock( photoatomic, atomic );

        CHECK( 5 == block.NFLO() );
        CHECK( 5 == block.fluorescenceEdgeEnergies().size() );
        CHECK( 5 == block.relativeEjectionProbabilities().size() );
        CHECK( 5 == block.yields().size() );
        CHECK( 5 == block.fluorescentEnergies().size() );

        CHECK_THAT( 1294.66666666666e-6, WithinRel( block.fluorescenceEdgeEnergies()[0] ) );
        CHECK_THAT( 1294.66666666666e-6, WithinRel( block.fluorescenceEdgeEnergies()[1] ) );
        CHECK_THAT( 11107e-6, WithinRel( block.fluorescenceEdgeEnergies()[2] ) );
        CHECK_THAT( 11107e-6, WithinRel( block.fluorescenceEdgeEnergies()[3] ) );
        CHECK_THAT( 11107e-6, WithinRel( block.fluorescenceEdgeEnergies()[4] ) );

        CHECK_THAT( 0.518974092414984, WithinRel( block.relativeEjectionProbabilities()[0] ) );
        CHECK_THAT( 1.               , WithinRel( block.relativeEjectionProbabilities()[1] ) );
        CHECK_THAT( 4.74393009164554 , WithinRel( block.relativeEjectionProbabilities()[2] ) );
        CHECK_THAT( 6.67295466695905 , WithinRel( block.relativeEjectionProbabilities()[3] ) );
        CHECK_THAT( 7.42244558067108 , WithinRel( block.relativeEjectionProbabilities()[4] ) );

        CHECK_THAT( 0.                , WithinRel( block.yields()[0] ) );
        CHECK_THAT( 5.7059893693256e-3, WithinRel( block.yields()[1] ) );
        CHECK_THAT( 1.98188634214128  , WithinRel( block.yields()[2] ) );
        CHECK_THAT( 3.00009458119345  , WithinRel( block.yields()[3] ) );
        CHECK_THAT( 3.39570272076953  , WithinRel( block.yields()[4] ) );

        CHECK_THAT( 0.                 , WithinRel( block.fluorescentEnergies()[0] ) );
        CHECK_THAT( 1.14590755068311e-3, WithinRel( block.fluorescentEnergies()[1] ) );
        CHECK_THAT( 9887e-6            , WithinRel( block.fluorescentEnergies()[2] ) );
        CHECK_THAT( 9856e-6            , WithinRel( block.fluorescentEnergies()[3] ) );
        CHECK_THAT( 10982.3284607849e-6, WithinRel( block.fluorescentEnergies()[4] ) );
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

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createFluorescenceDataBlock( photoatomic, atomic );

        CHECK( 6 == block.NFLO() );
        CHECK( 6 == block.fluorescenceEdgeEnergies().size() );
        CHECK( 6 == block.relativeEjectionProbabilities().size() );
        CHECK( 6 == block.yields().size() );
        CHECK( 6 == block.fluorescentEnergies().size() );

        CHECK_THAT( 21145e-6, WithinRel( block.fluorescenceEdgeEnergies()[0] ) );
        CHECK_THAT( 21145e-6, WithinRel( block.fluorescenceEdgeEnergies()[1] ) );
        CHECK_THAT( 121800e-6, WithinRel( block.fluorescenceEdgeEnergies()[2] ) );
        CHECK_THAT( 121800e-6, WithinRel( block.fluorescenceEdgeEnergies()[3] ) );
        CHECK_THAT( 121800e-6, WithinRel( block.fluorescenceEdgeEnergies()[4] ) );
        CHECK_THAT( 121800e-6, WithinRel( block.fluorescenceEdgeEnergies()[5] ) );

        CHECK_THAT( 0.258961992410833, WithinRel( block.relativeEjectionProbabilities()[0] ) );
        CHECK_THAT( 1.               , WithinRel( block.relativeEjectionProbabilities()[1] ) );
        CHECK_THAT( 2.49764925318338 , WithinRel( block.relativeEjectionProbabilities()[2] ) );
        CHECK_THAT( 3.44375852659793 , WithinRel( block.relativeEjectionProbabilities()[3] ) );
        CHECK_THAT( 3.97165266719616 , WithinRel( block.relativeEjectionProbabilities()[4] ) );
        CHECK_THAT( 4.14754181609835 , WithinRel( block.relativeEjectionProbabilities()[5] ) );

        CHECK_THAT( 0.               , WithinRel( block.yields()[0] ) );
        CHECK_THAT( 0.342850342848828, WithinRel( block.yields()[1] ) );
        CHECK_THAT( 1.79272453776756 , WithinRel( block.yields()[2] ) );
        CHECK_THAT( 2.70865289561325 , WithinRel( block.yields()[3] ) );
        CHECK_THAT( 3.21970719652869 , WithinRel( block.yields()[4] ) );
        CHECK_THAT( 3.38998547605071 , WithinRel( block.yields()[5] ) );

        CHECK_THAT( 0.                 , WithinRel( block.fluorescentEnergies()[0] ) );
        CHECK_THAT( 1.56059987938537e-2, WithinRel( block.fluorescentEnergies()[1] ) );
        CHECK_THAT( 103741e-6          , WithinRel( block.fluorescentEnergies()[2] ) );
        CHECK_THAT( 99533e-6           , WithinRel( block.fluorescentEnergies()[3] ) );
        CHECK_THAT( 116920.534878848e-6, WithinRel( block.fluorescentEnergies()[4] ) );
        CHECK_THAT( 120818.513473650e-6, WithinRel( block.fluorescentEnergies()[5] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
