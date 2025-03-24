// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/readPolynomial1d.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const format::gnds::Polynomial1d& );

SCENARIO( "readPolynomial1d" ) {

  GIVEN( "a GNDS polynomial1d xml nodes" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-094_Pu_237.jeff33.gnds.xml" );
    pugi::xml_node polynomial1d = document.child( "reactionSuite" ).child( "reactions" ).
                                           find_child_by_attribute( "reaction", "ENDF_MT", "18" ).
                                           child( "outputChannel" ).child( "products" ).
                                           find_child_by_attribute( "product", "pid", "n" ).
                                           child( "multiplicity" ).child( "polynomial1d" );

    WHEN( "a single GNDS polynomial1d node with an outer domain value is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readPolynomial1d( polynomial1d );

        verifyChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readPolynomial1d( polynomial1d.child( "values" ) ) );    // wrong node
        CHECK_THROWS( format::gnds::readPolynomial1d( polynomial1d.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const format::gnds::Polynomial1d& chunk ) {

  // outer domain value and unit
  CHECK( std::nullopt == std::get< 0 >( chunk ) );
  CHECK( std::nullopt == std::get< 1 >( chunk ) );

  // domain
  CHECK( 1e-5 == std::get< 2 >( chunk ) );
  CHECK( 2e+7  == std::get< 3 >( chunk ) );

  // x and y units
  CHECK( "eV" == std::get< 5 >( chunk ) );
  CHECK( ""  == std::get< 6 >( chunk ) );

  // values
  CHECK( 2 == std::get< 4 >( chunk ).size() );
  CHECK_THAT(   2.824, WithinRel( std::get< 4 >( chunk )[0] ) );
  CHECK_THAT( 1.42e-7, WithinRel( std::get< 4 >( chunk )[1] ) );
}
