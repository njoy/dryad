// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/resonances/lrf7/createFormalism.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createFormalism" ) {

  GIVEN( "ENDF MF2 MT151 sections" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );

    WHEN( "a set of parsed LRF7 data from MF2 MT151 is given" ) {

      THEN( "the formalism can be derived" ) {

        CHECK( resonances::Formalism::ReichMoore
               == endf::read::resonances::lrf7::createFormalism( parameters ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
