// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/resonances/createRadius.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;
using Radius = std::variant< double, TabulatedRadius >;

void verifyEnergyDependentScatteringRadiusChunk( const Radius& );
void verifyConstantScatteringRadiusChunk( const Radius& );
void verifyConstantHardSphereRadiusChunk( const Radius& );

SCENARIO( "createRadius" ) {

  GIVEN( "GNDS scattering radius node - energy dependent" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-069_Tm_168.endf.gnds.xml" );
    pugi::xml_node radius = document.child( "reactionSuite" ).child( "resonances" ).
                                           child( "resolved" ).child( "BreitWigner" ).
                                           child( "scatteringRadius" );

    WHEN( "a single scattering radius node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::resonances::createRadius( radius );

        verifyEnergyDependentScatteringRadiusChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS scattering radius node (top level) - constant" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-082_Pb_208.endf.gnds.xml" );
    pugi::xml_node radius = document.child( "reactionSuite" ).child( "resonances" ).
                                     child( "scatteringRadius" );

    WHEN( "a single scattering radius node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::resonances::createRadius( radius );

        verifyConstantScatteringRadiusChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS scattering radius node (in channel) - constant" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-082_Pb_208.endf.gnds.xml" );
    pugi::xml_node radius = document.child( "reactionSuite" ).child( "resonances" ).
                                     child( "resolved" ).child( "RMatrix" ).
                                     child( "spinGroups" ).
                                     find_child_by_attribute( "spinGroup", "label", "0" ).
                                     child( "channels" ).
                                     find_child_by_attribute( "channel", "label", "1" ).
                                     child( "scatteringRadius" );

    WHEN( "a single scattering radius node is given" ) {

      THEN( "it can be converted" ) {

        // the scattering and hard sphere radius are the same for this channel
        auto chunk = format::gnds::resonances::createRadius( radius );

        verifyConstantHardSphereRadiusChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS hard sphere radius node - constant" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-082_Pb_208.endf.gnds.xml" );
    pugi::xml_node radius = document.child( "reactionSuite" ).child( "resonances" ).
                                     child( "resolved" ).child( "RMatrix" ).
                                     child( "spinGroups" ).
                                     find_child_by_attribute( "spinGroup", "label", "0" ).
                                     child( "channels" ).
                                     find_child_by_attribute( "channel", "label", "1" ).
                                     child( "hardSphereRadius" );

    WHEN( "a hard sphere radius node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::resonances::createRadius( radius );

        // the scattering and hard sphere radius are the same for this channel
        verifyConstantHardSphereRadiusChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyEnergyDependentScatteringRadiusChunk( const Radius& chunk ) {

  CHECK( true == std::holds_alternative< TabulatedRadius >( chunk ) );

  auto radius = std::get< TabulatedRadius >( chunk );
  CHECK( true == radius.isLinearised() );
  CHECK( 50 == radius.numberPoints() );
  CHECK( 1 == radius.numberRegions() );
  CHECK( 50 == radius.energies().size() );
  CHECK( 50 == radius.values().size() );
  CHECK( 1 == radius.boundaries().size() );
  CHECK( 1 == radius.interpolants().size() );
  CHECK( 49 == radius.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == radius.interpolants()[0] );
  CHECK_THAT( 1e-5, WithinRel( radius.energies()[0] ) );
  CHECK_THAT( 9e+3, WithinRel( radius.energies()[24] ) );
  CHECK_THAT( 2e+5, WithinRel( radius.energies()[49] ) );
  CHECK_THAT( 12.381, WithinRel( radius.values()[0] ) );
  CHECK_THAT(  7.844, WithinRel( radius.values()[24] ) );
  CHECK_THAT(  5.803, WithinRel( radius.values()[49] ) );
}

void verifyConstantScatteringRadiusChunk( const Radius& chunk ) {

  CHECK( true == std::holds_alternative< double >( chunk ) );

  auto radius = std::get< double >( chunk );
  CHECK_THAT( 9.75, WithinRel( radius ) );
}

void verifyConstantHardSphereRadiusChunk( const Radius& chunk ) {

  CHECK( true == std::holds_alternative< double >( chunk ) );

  auto radius = std::get< double >( chunk );
  CHECK_THAT( 9.67, WithinRel( radius ) );
}
