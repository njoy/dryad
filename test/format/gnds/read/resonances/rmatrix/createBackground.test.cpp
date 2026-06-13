// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/resonances/rmatrix/createBackground.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;
using Background = std::variant< resonances::FrohnerBackground,
                                 resonances::SammyBackground,
                                 resonances::TabulatedBackground >;

void verifySammyBackgroundChunk( const Background& );

SCENARIO( "createBackground" ) {

  GIVEN( "GNDS external R-matrix node - SAMMY parametrisation" ) {

    pugi::xml_document document;
    document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node external = document.child( "reactionSuite" ).
                                       child( "resonances" ).child( "resolved" ).
                                       child( "RMatrix" ).child( "spinGroups" ).
                                       child( "spinGroup" ).child( "channels" ).
                                       find_child_by_attribute( "channel", "label", "1" ).
                                       child( "externalRMatrix" );

    WHEN( "a single external R-matrix node" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::resonances::rmatrix::createBackground( external );

        verifySammyBackgroundChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifySammyBackgroundChunk( const Background& chunk ) {

  CHECK( true == std::holds_alternative< resonances::SammyBackground >( chunk ) );

  auto background = std::get< resonances::SammyBackground >( chunk );
  CHECK_THAT( -0.043, WithinRel( background.polynomialCoefficients()[0] ) );
  CHECK_THAT( 2.8e-8, WithinRel( background.polynomialCoefficients()[1] ) );
  CHECK_THAT( 0.    , WithinRel( background.polynomialCoefficients()[2] ) );
  CHECK_THAT( 0.01  , WithinRel( background.logarithmicCoefficients()[0] ) );
  CHECK_THAT( 0.    , WithinRel( background.logarithmicCoefficients()[1] ) );
  CHECK_THAT( 0.    , WithinRel( background.lowerSingularity() ) );
  CHECK_THAT( 9.55e5, WithinRel( background.upperSingularity() ) );
}
