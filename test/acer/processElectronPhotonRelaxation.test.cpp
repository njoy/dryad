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

  GIVEN( "" ) {

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

      processElectronPhotonRelaxation( photoatomic, electroatomic, relaxation, filename );

      std::remove( filename.c_str() );
  } // GIVEN
} // SCENARIO
