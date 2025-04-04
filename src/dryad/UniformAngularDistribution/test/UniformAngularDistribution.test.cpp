// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/UniformAngularDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "UniformAngularDistribution" ) {

  GIVEN( "Cosines for a discrete cosine distribution" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > cosines = { -0.25, 0., 0.55 };
      UniformDistributionType type = UniformDistributionType::Discrete;

      UniformAngularDistribution chunk( std::move( cosines ), std::move( type ) );

      THEN( "a UniformAngularDistribution can be constructed and members can "
            "be tested" ) {

        CHECK( UniformDistributionType::Discrete == chunk.type() );
        CHECK( 3 == chunk.number() );

        CHECK_THAT( -0.25, WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.55, WithinRel( chunk.cosines()[2] ) );
      } // THEN

      THEN( "the average cosine can be calculated" ) {

        CHECK_THAT( 0.1, WithinRel( chunk.averageCosine() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "Cosines for a discrete cosine distribution" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > cosines = { -1., -0.25, 0., 0.5, 1.0 };
      UniformDistributionType type = UniformDistributionType::Interval;

      UniformAngularDistribution chunk( std::move( cosines ), std::move( type ) );

      THEN( "a UniformAngularDistribution can be constructed and members can "
            "be tested" ) {

        CHECK( UniformDistributionType::Interval == chunk.type() );
        CHECK( 4 == chunk.number() );

        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT( -0.25, WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[4] ) );
      } // THEN

      THEN( "the average cosine can be calculated" ) {

        CHECK_THAT( 0.0625, WithinRel( chunk.averageCosine() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "" ) {

      THEN( "" ) {

      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
