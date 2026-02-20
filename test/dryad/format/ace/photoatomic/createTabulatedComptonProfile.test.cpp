// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/photoatomic/createTabulatedComptonProfile.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createTabulatedComptonProfile" ) {

  GIVEN( "instances of cdfs" ) {

    njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

    WHEN( "an instance of photoatomic ACE ComptonProfile" ) {

      id::ElectronSubshellID identifier( "1s1/2" );
      auto profile = table.comptonProfileBlock().value().comptonProfile( 1 );

      THEN( "a Compton profile can be derived" ) {

        auto chunk = format::ace::photoatomic::createTabulatedComptonProfile( identifier, profile );


      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
