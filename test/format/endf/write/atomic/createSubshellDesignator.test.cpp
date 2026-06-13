// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/atomic/createSubshellDesignator.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "toSubshellDesignator" ) {

  GIVEN( "dryad subshell identifiers" ) {

    WHEN( "a single subshell identifier is given" ) {

      THEN( "it can be converted" ) {

        CHECK(  1 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "K" ) ) );
        CHECK(  2 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "L1" ) ) );
        CHECK(  3 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "L2" ) ) );
        CHECK(  4 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "L3" ) ) );
        CHECK(  5 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "M1" ) ) );
        CHECK(  6 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "M2" ) ) );
        CHECK(  7 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "M3" ) ) );
        CHECK(  8 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "M4" ) ) );
        CHECK(  9 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "M5" ) ) );
        CHECK( 10 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "N1" ) ) );
        CHECK( 11 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "N2" ) ) );
        CHECK( 12 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "N3" ) ) );
        CHECK( 13 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "N4" ) ) );
        CHECK( 14 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "N5" ) ) );
        CHECK( 15 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "N6" ) ) );
        CHECK( 16 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "N7" ) ) );
        CHECK( 17 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "O1" ) ) );
        CHECK( 18 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "O2" ) ) );
        CHECK( 19 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "O3" ) ) );
        CHECK( 20 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "O4" ) ) );
        CHECK( 21 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "O5" ) ) );
        CHECK( 22 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "O6" ) ) );
        CHECK( 23 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "O7" ) ) );
        CHECK( 24 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "O8" ) ) );
        CHECK( 25 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "O9" ) ) );
        CHECK( 26 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P1" ) ) );
        CHECK( 27 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P2" ) ) );
        CHECK( 28 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P3" ) ) );
        CHECK( 29 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P4" ) ) );
        CHECK( 30 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P5" ) ) );
        CHECK( 31 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P6" ) ) );
        CHECK( 32 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P7" ) ) );
        CHECK( 33 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P8" ) ) );
        CHECK( 34 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P9" ) ) );
        CHECK( 35 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P10" ) ) );
        CHECK( 36 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "P11" ) ) );
        CHECK( 37 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "Q1" ) ) );
        CHECK( 38 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "Q2" ) ) );
        CHECK( 39 == endf::write::atomic::createSubshellDesignator( id::ElectronSubshellID( "Q3" ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
