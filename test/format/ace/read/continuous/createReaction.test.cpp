// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/read/continuous/createReaction.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createReaction" ) {

  GIVEN( "instances of ContinuousEnergyTable" ) {

    WHEN( "a Lib81 formatted table is given" ) {

      njoy::ACEtk::ContinuousEnergyTable table( njoy::ACEtk::fromFile( "1001.10c" ) );

      THEN( "a Reaction can be created" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );

        Reaction capture = ace::read::continuous::createReaction( projectile, target, table, 1, false );
        continuous::lib81::h1::verifyCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
