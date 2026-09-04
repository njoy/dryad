// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/ndi/read/createMultigroupProjectileTargetFromFile.hpp"

// other includes
#include "NDItk/MultigroupLibrary.hpp"
#include "NDItk/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

// include common test verification functions
#include "test_verification_functions.hpp"

SCENARIO( "createMultigroupProjectileTargetFromFile" ) {

  using Library = njoy::NDItk::MultigroupLibrary;
  auto library = njoy::NDItk::fromFile< Library >( "1001.831nm" );
  decltype(auto) table = library.tables()[0];

  GIVEN( "an NDI multigroup library file" ) {

    WHEN( "constructing a MultigroupProjectileTarget" ) {

      auto chunk = ndi::read::createMultigroupProjectileTargetFromFile( "1001.831nm" );

      THEN( "a MultigroupProjectileTarget can be created and members can be tested" ) {

        CHECK( 1 == chunk.size() );

        neutron::h1::verifyH1( chunk[0] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
