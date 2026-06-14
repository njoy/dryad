// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertString.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

SCENARIO( "insertString" ) {

  GIVEN( "a parent node" ) {

    pugi::xml_document parent;
    gnds::write::Options options;

    THEN( "a string node can be inserted" ) {

      auto node1 = gnds::write::insertString( parent, options, "a", std::nullopt, std::nullopt );
      auto node2 = gnds::write::insertString( parent, options, "a", "b", std::nullopt );
      auto node3 = gnds::write::insertString( parent, options, "a", std::nullopt, "c" );
      auto node4 = gnds::write::insertString( parent, options, "a", "b", "c" );

      CHECK( 0 == strcmp( "string", node1.name() ) );
      CHECK( false == node1.attribute( "value" ).empty() );
      CHECK(  true == node1.attribute( "label" ).empty() );
      CHECK(  true == node1.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "a", node1.attribute( "value" ).as_string() ) );

      CHECK( 0 == strcmp( "string", node2.name() ) );
      CHECK( false == node2.attribute( "value" ).empty() );
      CHECK( false == node2.attribute( "label" ).empty() );
      CHECK(  true == node2.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "a", node2.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "b", node2.attribute( "label" ).as_string() ) );

      CHECK( 0 == strcmp( "string", node3.name() ) );
      CHECK( false == node3.attribute( "value" ).empty() );
      CHECK(  true == node3.attribute( "label" ).empty() );
      CHECK( false == node3.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "a", node3.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "c", node3.attribute( "unit" ).as_string() ) );

      CHECK( 0 == strcmp( "string", node4.name() ) );
      CHECK( false == node4.attribute( "value" ).empty() );
      CHECK( false == node4.attribute( "label" ).empty() );
      CHECK( false == node4.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "a", node4.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "b", node4.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "c", node4.attribute( "unit" ).as_string() ) );
    } // THEN
  } // GIVEN
} // SCENARIO
