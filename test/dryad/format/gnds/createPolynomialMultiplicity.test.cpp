// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createPolynomialMultiplicity.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyFissionChunk( const PolynomialMultiplicity& );

SCENARIO( "createPolynomialMultiplicity" ) {

  GIVEN( "GNDS multiplicity node from incident neutron data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-094_Pu_237.jeff33.gnds.xml" );
    pugi::xml_node multiplicity = document.child( "reactionSuite" ).child( "reactions" ).
                                           find_child_by_attribute( "reaction", "ENDF_MT", "18" ).
                                           child( "outputChannel" ).child( "products" ).
                                           find_child_by_attribute( "product", "pid", "n" ).
                                           child( "multiplicity" );

    WHEN( "a single multiplicity node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createPolynomialMultiplicity( multiplicity );

        verifyFissionChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyFissionChunk( const PolynomialMultiplicity& chunk ) {

  CHECK( 2 == chunk.coefficients().size() );
  CHECK( 1 == chunk.order() );

  CHECK_THAT( 1e-5, WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 2e+7, WithinRel( chunk.upperEnergyLimit() ) );

  CHECK_THAT(   2.824, WithinRel( chunk.coefficients()[0] ) );
  CHECK_THAT( 1.42e-7, WithinRel( chunk.coefficients()[1] ) );
}
