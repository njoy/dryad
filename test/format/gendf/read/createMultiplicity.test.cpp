// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gendf/read/createMultiplicity.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;
using Multiplicity = std::variant< int, MultigroupMultiplicity >;

void verifyConstantChunk( const Multiplicity& );

SCENARIO( "createMultiplicity" ) {

  GIVEN( "integer multiplicities" ) {

    WHEN( "a onstant value is given" ) {

      int multiplicity = 2;

      THEN( "it can be converted" ) {

        auto chunk = gendf::read::createMultiplicity( multiplicity );

        verifyConstantChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyConstantChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< int >( chunk ) );

  auto multiplicity = std::get< int >( chunk );
  CHECK( 2 == multiplicity );
}
