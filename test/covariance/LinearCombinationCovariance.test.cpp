// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/LinearCombinationCovariance.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "LinearCombinationCovariance" ) {

  //! @todo remove when we can parse string identifiers
  id::ReactionID( id::ParticleID::neutron(), id::ParticleID( "U235" ),
                  id::ReactionType( id::ParticleID::neutron(), 2 ) );
  id::ReactionID( id::ParticleID::neutron(), id::ParticleID( "U235" ),
                  id::ReactionType( id::ParticleID::neutron(), 4 ) );
  id::ReactionID( id::ParticleID::neutron(), id::ParticleID( "U235" ),
                  id::ReactionType( id::ParticleID::neutron(), 16 ) );

  GIVEN( "valid covariance data for a diagonal LinearCombinationCovariance" ) {

    double lower = 1e-5;
    double upper = 2e+7;
    std::vector< id::ReactionID > reactions = { id::ReactionID( "n,U235->n,U235" ),
                                                id::ReactionID( "n,U235->n,U235[all]" ),
                                                id::ReactionID( "n,U235->2n,U234[all]" ) };
    std::vector< double > coefficients = { .1, .2, .3 };

    LinearCombinationCovariance chunk( std::move( lower ), std::move( upper ),
                                       std::move( reactions ), std::move( coefficients ) );

    THEN( "a LinearCombinationCovariance can be constructed and members can be tested" ) {

      CHECK( 3 == chunk.numberReactions() );

      CHECK( 3 == chunk.reactions().size() );
      CHECK( id::ReactionID( "n,U235->n,U235" )  == chunk.reactions()[0] );
      CHECK( id::ReactionID( "n,U235->n,U235[all]" )  == chunk.reactions()[1] );
      CHECK( id::ReactionID( "n,U235->2n,U234[all]" ) == chunk.reactions()[2] );

      CHECK( 3 == chunk.coefficients().size() );
      CHECK_THAT( 0.1, WithinRel( chunk.coefficients()[0] ) );
      CHECK_THAT( 0.2, WithinRel( chunk.coefficients()[1] ) );
      CHECK_THAT( 0.3, WithinRel( chunk.coefficients()[2] ) );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a LinearCombinationCovariance" ) {

    WHEN( "the number of reactions and coefficients is not consistent or both are zero" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearCombinationCovariance( 1e-5, 2e+7, {}, { .1, .2, .3 } ) );
        CHECK_THROWS( LinearCombinationCovariance( 1e-5, 2e+7, { id::ReactionID( "n,U235->n,U235" ),
                                                                 id::ReactionID( "n,U235->n,U235[all]" ),
                                                                 id::ReactionID( "n,U235->2n,U234[all]" ) },
                                                   {} ) );
        CHECK_THROWS( LinearCombinationCovariance( 1e-5, 2e+7, {}, {} ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO