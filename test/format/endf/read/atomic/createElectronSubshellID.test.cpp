// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/atomic/createElectronSubshellID.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createElectronSubshellID" ) {

  GIVEN( "ENDF subshell identifiers" ) {

    WHEN( "a single subshell identifier is given" ) {

      THEN( "it can be converted" ) {

        CHECK( id::ElectronSubshellID( "K" ) == endf::read::atomic::createElectronSubshellID( 1 ) );
        CHECK( id::ElectronSubshellID( "L1" ) == endf::read::atomic::createElectronSubshellID( 2 ) );
        CHECK( id::ElectronSubshellID( "L2" ) == endf::read::atomic::createElectronSubshellID( 3 ) );
        CHECK( id::ElectronSubshellID( "L3" ) == endf::read::atomic::createElectronSubshellID( 4 ) );
        CHECK( id::ElectronSubshellID( "M1" ) == endf::read::atomic::createElectronSubshellID( 5 ) );
        CHECK( id::ElectronSubshellID( "M2" ) == endf::read::atomic::createElectronSubshellID( 6 ) );
        CHECK( id::ElectronSubshellID( "M3" ) == endf::read::atomic::createElectronSubshellID( 7 ) );
        CHECK( id::ElectronSubshellID( "M4" ) == endf::read::atomic::createElectronSubshellID( 8 ) );
        CHECK( id::ElectronSubshellID( "M5" ) == endf::read::atomic::createElectronSubshellID( 9 ) );
        CHECK( id::ElectronSubshellID( "N1" ) == endf::read::atomic::createElectronSubshellID( 10 ) );
        CHECK( id::ElectronSubshellID( "N2" ) == endf::read::atomic::createElectronSubshellID( 11 ) );
        CHECK( id::ElectronSubshellID( "N3" ) == endf::read::atomic::createElectronSubshellID( 12 ) );
        CHECK( id::ElectronSubshellID( "N4" ) == endf::read::atomic::createElectronSubshellID( 13 ) );
        CHECK( id::ElectronSubshellID( "N5" ) == endf::read::atomic::createElectronSubshellID( 14 ) );
        CHECK( id::ElectronSubshellID( "N6" ) == endf::read::atomic::createElectronSubshellID( 15 ) );
        CHECK( id::ElectronSubshellID( "N7" ) == endf::read::atomic::createElectronSubshellID( 16 ) );
        CHECK( id::ElectronSubshellID( "O1" ) == endf::read::atomic::createElectronSubshellID( 17 ) );
        CHECK( id::ElectronSubshellID( "O2" ) == endf::read::atomic::createElectronSubshellID( 18 ) );
        CHECK( id::ElectronSubshellID( "O3" ) == endf::read::atomic::createElectronSubshellID( 19 ) );
        CHECK( id::ElectronSubshellID( "O4" ) == endf::read::atomic::createElectronSubshellID( 20 ) );
        CHECK( id::ElectronSubshellID( "O5" ) == endf::read::atomic::createElectronSubshellID( 21 ) );
        CHECK( id::ElectronSubshellID( "O6" ) == endf::read::atomic::createElectronSubshellID( 22 ) );
        CHECK( id::ElectronSubshellID( "O7" ) == endf::read::atomic::createElectronSubshellID( 23 ) );
        CHECK( id::ElectronSubshellID( "O8" ) == endf::read::atomic::createElectronSubshellID( 24 ) );
        CHECK( id::ElectronSubshellID( "O9" ) == endf::read::atomic::createElectronSubshellID( 25 ) );
        CHECK( id::ElectronSubshellID( "P1" ) == endf::read::atomic::createElectronSubshellID( 26 ) );
        CHECK( id::ElectronSubshellID( "P2" ) == endf::read::atomic::createElectronSubshellID( 27 ) );
        CHECK( id::ElectronSubshellID( "P3" ) == endf::read::atomic::createElectronSubshellID( 28 ) );
        CHECK( id::ElectronSubshellID( "P4" ) == endf::read::atomic::createElectronSubshellID( 29 ) );
        CHECK( id::ElectronSubshellID( "P5" ) == endf::read::atomic::createElectronSubshellID( 30 ) );
        CHECK( id::ElectronSubshellID( "P6" ) == endf::read::atomic::createElectronSubshellID( 31 ) );
        CHECK( id::ElectronSubshellID( "P7" ) == endf::read::atomic::createElectronSubshellID( 32 ) );
        CHECK( id::ElectronSubshellID( "P8" ) == endf::read::atomic::createElectronSubshellID( 33 ) );
        CHECK( id::ElectronSubshellID( "P9" ) == endf::read::atomic::createElectronSubshellID( 34 ) );
        CHECK( id::ElectronSubshellID( "P10" ) == endf::read::atomic::createElectronSubshellID( 35 ) );
        CHECK( id::ElectronSubshellID( "P11" ) == endf::read::atomic::createElectronSubshellID( 36 ) );
        CHECK( id::ElectronSubshellID( "Q1" ) == endf::read::atomic::createElectronSubshellID( 37 ) );
        CHECK( id::ElectronSubshellID( "Q2" ) == endf::read::atomic::createElectronSubshellID( 38 ) );
        CHECK( id::ElectronSubshellID( "Q3" ) == endf::read::atomic::createElectronSubshellID( 39 ) );
      } // THEN

      THEN( "an exception is thrown for an unknown or unsupported identifier" ) {

        CHECK_THROWS( endf::read::atomic::createElectronSubshellID( 0 ) );
        CHECK_THROWS( endf::read::atomic::createElectronSubshellID( 50 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
