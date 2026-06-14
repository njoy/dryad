// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertInteger.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

SCENARIO( "insertInteger" ) {

  GIVEN( "a parent node" ) {

    pugi::xml_document parent;
    gnds::write::Options options;

    THEN( "an integer node can be inserted" ) {

      auto node1 = gnds::write::insertInteger( parent, options, 1000, std::nullopt, std::nullopt );
      auto node2 = gnds::write::insertInteger( parent, options, 1000, "energy", std::nullopt );
      auto node3 = gnds::write::insertInteger( parent, options, 1000, std::nullopt, "eV" );
      auto node4 = gnds::write::insertInteger( parent, options, 1000, "energy", "eV" );

      CHECK( 0 == strcmp( "integer", node1.name() ) );
      CHECK( false == node1.attribute( "value" ).empty() );
      CHECK(  true == node1.attribute( "label" ).empty() );
      CHECK(  true == node1.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1000", node1.attribute( "value" ).as_string() ) );

      CHECK( 0 == strcmp( "integer", node2.name() ) );
      CHECK( false == node2.attribute( "value" ).empty() );
      CHECK( false == node2.attribute( "label" ).empty() );
      CHECK(  true == node2.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1000", node2.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "energy", node2.attribute( "label" ).as_string() ) );

      CHECK( 0 == strcmp( "integer", node3.name() ) );
      CHECK( false == node3.attribute( "value" ).empty() );
      CHECK(  true == node3.attribute( "label" ).empty() );
      CHECK( false == node3.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1000", node3.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "eV", node3.attribute( "unit" ).as_string() ) );

      CHECK( 0 == strcmp( "integer", node4.name() ) );
      CHECK( false == node4.attribute( "value" ).empty() );
      CHECK( false == node4.attribute( "label" ).empty() );
      CHECK( false == node4.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1000", node4.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "energy", node4.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "eV", node4.attribute( "unit" ).as_string() ) );
    } // THEN
  } // GIVEN
} // SCENARIO
