// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/covariance/CrossSectionMetadata.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "CrossSectionMetadata" ) {

  GIVEN( "valid data for a CrossSectionMetadata" ) {

    WHEN( "the data is given explicitly" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      id::ReactionID reaction( "2" );
      std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

      CrossSectionMetadata chunk( std::move( projectile ),
                                  std::move( target ),
                                  std::move( reaction ),
                                  std::move( energies ) );

      THEN( "a CrossSectionMetadata can be constructed and members can be tested" ) {

        CHECK( "n" == chunk.projectileIdentifier() );
        CHECK( "U235" == chunk.targetIdentifier() );
        CHECK( "2" == chunk.reactionIdentifier() );

        CHECK( 4 == chunk.energies().size() );
        CHECK( 3 == chunk.numberGroups() );
        CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 1e+6, WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 2e+7, WithinRel( chunk.energies()[3] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a CrossSectionMetadata" ) {

    WHEN( "the energy grid does not have at least 2 elements" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      id::ReactionID reaction( "2" );
      std::vector< double > wrong = { 1e-5 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSectionMetadata( std::move( projectile ),
                                            std::move( target ),
                                            std::move( reaction ),
                                            std::move( wrong ) ) );
      } // THEN
    } // WHEN

    WHEN( "the energy grid is not sorted" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      id::ReactionID reaction( "2" );
      std::vector< double > wrong = { 2e+7, 1e+6, 1., 1e-5 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSectionMetadata( std::move( projectile ),
                                            std::move( target ),
                                            std::move( reaction ),
                                            std::move( wrong ) ) );
      } // THEN
    } // WHEN

    WHEN( "the energy grid has duplicate points" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      id::ReactionID reaction( "2" );
      std::vector< double > wrong = { 1e-5, 1., 1., 2e+7 };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSectionMetadata( std::move( projectile ),
                                            std::move( target ),
                                            std::move( reaction ),
                                            std::move( wrong ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
