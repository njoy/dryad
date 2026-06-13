// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/read/continuous/createReactions.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createReactions" ) {

  GIVEN( "instances of ContinuousEnergyTable" ) {

    WHEN( "a Lib81 formatted table is given" ) {

      auto n = id::ParticleID::neutron();
      auto H1 = id::ParticleID( "H1" );
      njoy::ACEtk::ContinuousEnergyTable table( njoy::ACEtk::fromFile( "1001.10c" ) );

      THEN( "reactions can be derived" ) {

        auto reactions = ace::read::continuous::createReactions( n, H1, table, false );

        CHECK( 3 == reactions.size() );

        auto total = reactions[0];
        continuous::lib81::h1::verifyTotalReaction( total );

        auto elastic = reactions[1];
        continuous::lib81::h1::verifyElasticReaction( elastic );

        auto capture = reactions[2];
        continuous::lib81::h1::verifyCaptureReaction( capture );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
