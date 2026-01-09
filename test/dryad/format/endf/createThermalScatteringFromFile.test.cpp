// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/createThermalScatteringFromFile.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createThermalScattering" ) {

  GIVEN( "ENDF materials - incoherent elastic and inelastic" ) {

    WHEN( "a single ENDF material is given" ) {

      THEN( "it can be converted" ) {

        ThermalScattering chunk = format::endf::createThermalScatteringFromFile( "tsl-ZrinZrH.endf" );

        tsl::zrinzrh::verifyZrInZrH( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
