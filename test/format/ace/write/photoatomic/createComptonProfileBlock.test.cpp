// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/ace/write/photoatomic/createComptonProfileBlock.hpp"

// other includes
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"
#include "njoy/dryad/external/ComptonProfiles.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createComptonProfileBlock" ) {

  GIVEN( "instances of ProjectileTarget" ) {

    WHEN( "correct data is given" ) {

      auto photoatomic = endf::read::createProjectileTargetFromFile( "photoat-001_H_000.endf", true );
      photoatomic.unioniseCrossSections();
      photoatomic.calculateSummationCrossSections();
      external::ComptonProfiles::apply( photoatomic, true );

      THEN( "the ace block can be generated" ) {

        auto block = ace::write::photoatomic::createComptonProfileBlock( photoatomic );

        CHECK( 1 == block.numberElectronShells() );

        CHECK( 31 == block.comptonProfile( 1 ).numberValues() );
        CHECK( 31 == block.comptonProfile( 1 ).momentum().size() );
        CHECK( 31 == block.comptonProfile( 1 ).pdf().size() );
        CHECK( 31 == block.comptonProfile( 1 ).cdf().size() );

        CHECK( 2 == block.comptonProfile( 1 ).interpolation() );

        CHECK_THAT(  0.  , WithinRel( block.comptonProfile( 1 ).momentum().front() ) );
        CHECK_THAT(  100., WithinRel( block.comptonProfile( 1 ).momentum().back() ) );
        CHECK_THAT(  1.690581458876890   , WithinRel( block.comptonProfile( 1 ).pdf().front() ) );
        CHECK_THAT(  5.17728126393395e-11, WithinRel( block.comptonProfile( 1 ).pdf().back() ) );
        CHECK_THAT(  0.  , WithinRel( block.comptonProfile( 1 ).cdf().front() ) );
        CHECK_THAT(  1.  , WithinRel( block.comptonProfile( 1 ).cdf().back() ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
