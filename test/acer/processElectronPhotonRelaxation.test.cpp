// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/acer/processElectronPhotonRelaxation.hpp"

// other includes
#include "njoy/dryad/format/endf/createProjectileTargetFromFile.hpp"
#include "njoy/dryad/format/endf/createAtomicRelaxationFromFile.hpp"

// convenience typedefs
using namespace njoy::acer;
using namespace njoy::dryad;

SCENARIO( "processElectronPhotonRelaxation" ) {

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z < 12" ) {

    WHEN( "correct data is given" ) {

      auto relaxation = format::endf::createAtomicRelaxationFromFile( "atom-001_H_000.endf", true );
      relaxation.calculateTransitionEnergies();
      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();
      external::ComptonProfiles::apply( photoatomic, true );
      auto electroatomic = format::endf::createProjectileTargetFromFile( "e-001_H_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      std::string filename = "fuvnrkljnvoiarnglkanrlknfalkvnlkrua.ace";

      THEN( "the ace file can be generated" ) {

        processElectronPhotonRelaxation( photoatomic, electroatomic, relaxation, filename );

//      std::remove( filename.c_str() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 12 and z < 31" ) {

    WHEN( "correct data is given" ) {

      auto relaxation = format::endf::createAtomicRelaxationFromFile( "atom-029_Cu_000.endf", true );
      relaxation.calculateTransitionEnergies();
      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-029_Cu_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();
      external::ComptonProfiles::apply( photoatomic, true );
      auto electroatomic = format::endf::createProjectileTargetFromFile( "e-029_Cu_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      std::string filename = "ajrhctvnoiweuynckeuhrckeuhwkrlk.ace";

      THEN( "the ace file can be generated" ) {

        processElectronPhotonRelaxation( photoatomic, electroatomic, relaxation, filename );

//      std::remove( filename.c_str() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 31 and z < 36" ) {

    WHEN( "correct data is given" ) {

      auto relaxation = format::endf::createAtomicRelaxationFromFile( "atom-032_Ge_000.endf", true );
      relaxation.calculateTransitionEnergies();
      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-032_Ge_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();
      external::ComptonProfiles::apply( photoatomic, true );
      auto electroatomic = format::endf::createProjectileTargetFromFile( "e-032_Ge_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      std::string filename = "oieucnroieurcnouwehxmfkhskue4grkuegfl.ace";

      THEN( "the ace file can be generated" ) {

        processElectronPhotonRelaxation( photoatomic, electroatomic, relaxation, filename );

//      std::remove( filename.c_str() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of ProjectileTarget and AtomicRelaxation with z >= 37" ) {

    WHEN( "correct data is given" ) {

      auto relaxation = format::endf::createAtomicRelaxationFromFile( "atom-094_Pu_000.endf", true );
      relaxation.calculateTransitionEnergies();
      auto photoatomic = format::endf::createProjectileTargetFromFile( "photoat-094_Pu_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      photoatomic.calculateAverageEnergy();
      external::ComptonProfiles::apply( photoatomic, true );
      auto electroatomic = format::endf::createProjectileTargetFromFile( "e-094_Pu_000.endf", true );
      electroatomic.unioniseCrossSections();
      electroatomic.calculateSummationCrossSections();

      std::string filename = "oxwincaweuxlkeuhrfkclalhnriuheuchaiulhrlm.ace";

      THEN( "the ace file can be generated" ) {

        processElectronPhotonRelaxation( photoatomic, electroatomic, relaxation, filename );
//      std::remove( filename.c_str() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
