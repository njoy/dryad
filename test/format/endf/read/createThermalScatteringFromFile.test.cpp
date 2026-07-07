// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/createThermalScatteringFromFile.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createThermalScattering" ) {

  GIVEN( "ENDF materials - coherent elastic and inelastic" ) {

    WHEN( "a single ENDF material is given" ) {

      THEN( "it can be converted" ) {

        ThermalScattering chunk = endf::read::createThermalScatteringFromFile( "tsl-Be-metal.endf" );

        tsl::bemetal::verifyBeMetal( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - incoherent elastic and inelastic" ) {

    WHEN( "a single ENDF material is given" ) {

      THEN( "it can be converted" ) {

        ThermalScattering chunk = endf::read::createThermalScatteringFromFile( "tsl-ZrinZrH.endf" );

        tsl::zrinzrh::verifyZrInZrH( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF materials - mixed elastic and inelastic" ) {

    WHEN( "a single ENDF material is given" ) {

      THEN( "it can be converted" ) {

        ThermalScattering chunk = endf::read::createThermalScatteringFromFile( "tsl-7Liin7LiD-mixed.endf" );

        tsl::li7inli7d::verifyLi7InLi7D( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
