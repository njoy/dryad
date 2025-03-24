// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createMultiplicity.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using Multiplicity = std::variant< int, TabulatedMultiplicity, PolynomialMultiplicity >;

void verifyChunk( const Multiplicity& );

SCENARIO( "createMultiplicity" ) {

  GIVEN( "GNDS multiplciity node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node average = document.child( "reactionSuite" ).child( "reactions" ).
                                      find_child_by_attribute( "reaction", "ENDF_MT", "527" ).
                                      child( "outputChannel" ).child( "products" ).
                                      find_child_by_attribute( "product", "pid", "e-" ).
                                      child( "multiplicity" );

    WHEN( "a single multiplciity node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createMultiplicity( average );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< int >( chunk ) );

  auto value = std::get< int >( chunk );
  CHECK( 1 == value );
}
