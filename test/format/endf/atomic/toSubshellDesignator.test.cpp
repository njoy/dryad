// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/atomic/toSubshellDesignator.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "toSubshellDesignator" ) {

  GIVEN( "dryad subshell identifiers" ) {

    WHEN( "a single subshell identifier is given" ) {

      THEN( "it can be converted" ) {

        CHECK(  1 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "K" ) ) );
        CHECK(  2 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "L1" ) ) );
        CHECK(  3 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "L2" ) ) );
        CHECK(  4 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "L3" ) ) );
        CHECK(  5 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "M1" ) ) );
        CHECK(  6 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "M2" ) ) );
        CHECK(  7 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "M3" ) ) );
        CHECK(  8 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "M4" ) ) );
        CHECK(  9 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "M5" ) ) );
        CHECK( 10 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "N1" ) ) );
        CHECK( 11 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "N2" ) ) );
        CHECK( 12 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "N3" ) ) );
        CHECK( 13 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "N4" ) ) );
        CHECK( 14 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "N5" ) ) );
        CHECK( 15 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "N6" ) ) );
        CHECK( 16 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "N7" ) ) );
        CHECK( 17 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "O1" ) ) );
        CHECK( 18 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "O2" ) ) );
        CHECK( 19 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "O3" ) ) );
        CHECK( 20 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "O4" ) ) );
        CHECK( 21 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "O5" ) ) );
        CHECK( 22 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "O6" ) ) );
        CHECK( 23 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "O7" ) ) );
        CHECK( 24 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "O8" ) ) );
        CHECK( 25 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "O9" ) ) );
        CHECK( 26 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P1" ) ) );
        CHECK( 27 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P2" ) ) );
        CHECK( 28 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P3" ) ) );
        CHECK( 29 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P4" ) ) );
        CHECK( 30 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P5" ) ) );
        CHECK( 31 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P6" ) ) );
        CHECK( 32 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P7" ) ) );
        CHECK( 33 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P8" ) ) );
        CHECK( 34 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P9" ) ) );
        CHECK( 35 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P10" ) ) );
        CHECK( 36 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "P11" ) ) );
        CHECK( 37 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "Q1" ) ) );
        CHECK( 38 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "Q2" ) ) );
        CHECK( 39 == format::endf::atomic::toSubshellDesignator( id::ElectronSubshellID( "Q3" ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
