// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/atomic/createElectronSubshellID.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createElectronSubshellID" ) {

  GIVEN( "ENDF subshell identifiers" ) {

    WHEN( "a single subshell identifier is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ElectronSubshellID( "K" ) == format::endf::atomic::createElectronSubshellID( 1 ) );
        CHECK( id::ElectronSubshellID( "L1" ) == format::endf::atomic::createElectronSubshellID( 2 ) );
        CHECK( id::ElectronSubshellID( "L2" ) == format::endf::atomic::createElectronSubshellID( 3 ) );
        CHECK( id::ElectronSubshellID( "L3" ) == format::endf::atomic::createElectronSubshellID( 4 ) );
        CHECK( id::ElectronSubshellID( "M1" ) == format::endf::atomic::createElectronSubshellID( 5 ) );
        CHECK( id::ElectronSubshellID( "M2" ) == format::endf::atomic::createElectronSubshellID( 6 ) );
        CHECK( id::ElectronSubshellID( "M3" ) == format::endf::atomic::createElectronSubshellID( 7 ) );
        CHECK( id::ElectronSubshellID( "M4" ) == format::endf::atomic::createElectronSubshellID( 8 ) );
        CHECK( id::ElectronSubshellID( "M5" ) == format::endf::atomic::createElectronSubshellID( 9 ) );
        CHECK( id::ElectronSubshellID( "N1" ) == format::endf::atomic::createElectronSubshellID( 10 ) );
        CHECK( id::ElectronSubshellID( "N2" ) == format::endf::atomic::createElectronSubshellID( 11 ) );
        CHECK( id::ElectronSubshellID( "N3" ) == format::endf::atomic::createElectronSubshellID( 12 ) );
        CHECK( id::ElectronSubshellID( "N4" ) == format::endf::atomic::createElectronSubshellID( 13 ) );
        CHECK( id::ElectronSubshellID( "N5" ) == format::endf::atomic::createElectronSubshellID( 14 ) );
        CHECK( id::ElectronSubshellID( "N6" ) == format::endf::atomic::createElectronSubshellID( 15 ) );
        CHECK( id::ElectronSubshellID( "N7" ) == format::endf::atomic::createElectronSubshellID( 16 ) );
        CHECK( id::ElectronSubshellID( "O1" ) == format::endf::atomic::createElectronSubshellID( 17 ) );
        CHECK( id::ElectronSubshellID( "O2" ) == format::endf::atomic::createElectronSubshellID( 18 ) );
        CHECK( id::ElectronSubshellID( "O3" ) == format::endf::atomic::createElectronSubshellID( 19 ) );
        CHECK( id::ElectronSubshellID( "O4" ) == format::endf::atomic::createElectronSubshellID( 20 ) );
        CHECK( id::ElectronSubshellID( "O5" ) == format::endf::atomic::createElectronSubshellID( 21 ) );
        CHECK( id::ElectronSubshellID( "O6" ) == format::endf::atomic::createElectronSubshellID( 22 ) );
        CHECK( id::ElectronSubshellID( "O7" ) == format::endf::atomic::createElectronSubshellID( 23 ) );
        CHECK( id::ElectronSubshellID( "O8" ) == format::endf::atomic::createElectronSubshellID( 24 ) );
        CHECK( id::ElectronSubshellID( "O9" ) == format::endf::atomic::createElectronSubshellID( 25 ) );
        CHECK( id::ElectronSubshellID( "P1" ) == format::endf::atomic::createElectronSubshellID( 26 ) );
        CHECK( id::ElectronSubshellID( "P2" ) == format::endf::atomic::createElectronSubshellID( 27 ) );
        CHECK( id::ElectronSubshellID( "P3" ) == format::endf::atomic::createElectronSubshellID( 28 ) );
        CHECK( id::ElectronSubshellID( "P4" ) == format::endf::atomic::createElectronSubshellID( 29 ) );
        CHECK( id::ElectronSubshellID( "P5" ) == format::endf::atomic::createElectronSubshellID( 30 ) );
        CHECK( id::ElectronSubshellID( "P6" ) == format::endf::atomic::createElectronSubshellID( 31 ) );
        CHECK( id::ElectronSubshellID( "P7" ) == format::endf::atomic::createElectronSubshellID( 32 ) );
        CHECK( id::ElectronSubshellID( "P8" ) == format::endf::atomic::createElectronSubshellID( 33 ) );
        CHECK( id::ElectronSubshellID( "P9" ) == format::endf::atomic::createElectronSubshellID( 34 ) );
        CHECK( id::ElectronSubshellID( "P10" ) == format::endf::atomic::createElectronSubshellID( 35 ) );
        CHECK( id::ElectronSubshellID( "P11" ) == format::endf::atomic::createElectronSubshellID( 36 ) );
        CHECK( id::ElectronSubshellID( "Q1" ) == format::endf::atomic::createElectronSubshellID( 37 ) );
        CHECK( id::ElectronSubshellID( "Q2" ) == format::endf::atomic::createElectronSubshellID( 38 ) );
        CHECK( id::ElectronSubshellID( "Q3" ) == format::endf::atomic::createElectronSubshellID( 39 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported identifier" ) {

        CHECK_THROWS( format::endf::atomic::createElectronSubshellID( 0 ) );
        CHECK_THROWS( format::endf::atomic::createElectronSubshellID( 50 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
