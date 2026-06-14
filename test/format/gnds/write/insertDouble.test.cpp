// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertDouble.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include <iostream>
// convenience typedefs
using namespace njoy::format;

SCENARIO( "insertDouble" ) {

  GIVEN( "a parent node" ) {

    pugi::xml_document parent;
    gnds::write::Options options;

    THEN( "a double node can be inserted" ) {

      auto node1 = gnds::write::insertDouble( parent, options, 1000, std::nullopt, std::nullopt );
      auto node2 = gnds::write::insertDouble( parent, options, 1.123456789, "energy", std::nullopt );
      auto node3 = gnds::write::insertDouble( parent, options, 123.123456789, std::nullopt, "eV" );
      auto node4 = gnds::write::insertDouble( parent, options, 1234567890123.12345678, "energy", "eV" );

      CHECK( 0 == strcmp( "double", node1.name() ) );
      CHECK( false == node1.attribute( "value" ).empty() );
      CHECK(  true == node1.attribute( "label" ).empty() );
      CHECK(  true == node1.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1000", node1.attribute( "value" ).as_string() ) );

      CHECK( 0 == strcmp( "double", node2.name() ) );
      CHECK( false == node2.attribute( "value" ).empty() );
      CHECK( false == node2.attribute( "label" ).empty() );
      CHECK(  true == node2.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1.123456789", node2.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "energy", node2.attribute( "label" ).as_string() ) );

      CHECK( 0 == strcmp( "double", node3.name() ) );
      CHECK( false == node3.attribute( "value" ).empty() );
      CHECK(  true == node3.attribute( "label" ).empty() );
      CHECK( false == node3.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "123.1234568", node3.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "eV", node3.attribute( "unit" ).as_string() ) );

      CHECK( 0 == strcmp( "double", node4.name() ) );
      CHECK( false == node4.attribute( "value" ).empty() );
      CHECK( false == node4.attribute( "label" ).empty() );
      CHECK( false == node4.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1.23456789e+12", node4.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "energy", node4.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "eV", node4.attribute( "unit" ).as_string() ) );
    } // THEN
  } // GIVEN
} // SCENARIO
