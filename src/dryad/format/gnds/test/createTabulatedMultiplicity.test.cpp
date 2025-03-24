// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createTabulatedMultiplicity.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyFissionChunk( const TabulatedMultiplicity& );

SCENARIO( "createTabulatedMultiplicity" ) {

  GIVEN( "GNDS cross section node from incident neutron data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-093_Np_237.endf.gnds.xml" );
    pugi::xml_node multiplicity = document.child( "reactionSuite" ).child( "reactions" ).
                                           find_child_by_attribute( "reaction", "ENDF_MT", "18" ).
                                           child( "outputChannel" ).child( "products" ).
                                           find_child_by_attribute( "product", "pid", "n" ).
                                           child( "multiplicity" );

    WHEN( "a single multiplicity node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createTabulatedMultiplicity( multiplicity );

        verifyFissionChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyFissionChunk( const TabulatedMultiplicity& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 6 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 6 == chunk.energies().size() );
  CHECK( 6 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 5 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT( 1.0e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 4.0e+6, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 7.0e+6, WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 1.1e+7, WithinRel( chunk.energies()[3] ) );
  CHECK_THAT( 1.2e+7, WithinRel( chunk.energies()[4] ) );
  CHECK_THAT( 2.0e+7, WithinRel( chunk.energies()[5] ) );
  CHECK_THAT( 2.625000, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 3.224250, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 3.677437, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 4.324800, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 4.466900, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 5.520700, WithinRel( chunk.values()[5] ) );
}
