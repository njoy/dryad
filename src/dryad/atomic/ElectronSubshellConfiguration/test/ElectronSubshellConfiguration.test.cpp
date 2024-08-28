// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/atomic/ElectronSubshellConfiguration.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::atomic;

void verifyChunk( const ElectronSubshellConfiguration& );

SCENARIO( "ElectronSubshellConfiguration" ) {

  GIVEN( "valid data for a subshell configuration" ) {

    WHEN( "the data is given explicitly" ) {

      id::ElectronSubshellID id( "K" );
      double energy = 13.6;
      double population = 1.33;

      ElectronSubshellConfiguration chunk( std::move( id ), std::move( energy ),
                                           std::move( population ) );

      THEN( "an ElectronSubshellConfiguration can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const ElectronSubshellConfiguration& chunk ) {

  CHECK( id::ElectronSubshellID( "K" ) == chunk.identifier() );
  CHECK_THAT( 13.6, WithinRel( chunk.bindingEnergy() ) );
  CHECK_THAT( 1.33, WithinRel( chunk.population() ) );
}
