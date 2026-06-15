// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertFraction.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

SCENARIO( "insertFraction" ) {

  GIVEN( "a parent node" ) {

    pugi::xml_document parent;
    gnds::write::Options options;

    THEN( "a fraction node can be inserted" ) {

      auto node1 = gnds::write::insertFraction( parent, options, 1, 2, std::nullopt, std::nullopt );
      auto node2 = gnds::write::insertFraction( parent, options, 1, 2, "spin", std::nullopt );
      auto node3 = gnds::write::insertFraction( parent, options, 1, 2, std::nullopt, "hbar" );
      auto node4 = gnds::write::insertFraction( parent, options, 1, 2, "spin", "hbar" );

      auto node5 = gnds::write::insertFraction( parent, options, 2, 1, std::nullopt, std::nullopt );

      CHECK( 0 == strcmp( "fraction", node2.name() ) );
      CHECK( false == node2.attribute( "value" ).empty() );
      CHECK( false == node2.attribute( "label" ).empty() );
      CHECK(  true == node2.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1/2", node2.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "spin", node2.attribute( "label" ).as_string() ) );

      CHECK( 0 == strcmp( "fraction", node3.name() ) );
      CHECK( false == node3.attribute( "value" ).empty() );
      CHECK(  true == node3.attribute( "label" ).empty() );
      CHECK( false == node3.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1/2", node3.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "hbar", node3.attribute( "unit" ).as_string() ) );

      CHECK( 0 == strcmp( "fraction", node4.name() ) );
      CHECK( false == node4.attribute( "value" ).empty() );
      CHECK( false == node4.attribute( "label" ).empty() );
      CHECK( false == node4.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "1/2", node4.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "spin", node4.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "hbar", node4.attribute( "unit" ).as_string() ) );

      CHECK( 0 == strcmp( "fraction", node5.name() ) );
      CHECK( false == node5.attribute( "value" ).empty() );
      CHECK(  true == node5.attribute( "label" ).empty() );
      CHECK(  true == node5.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "2", node5.attribute( "value" ).as_string() ) );
    } // THEN
  } // GIVEN
} // SCENARIO
