// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/UniformEnergyDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "UniformEnergyDistribution" ) {

  GIVEN( "Cosines for a discrete cosine distribution" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 2., 3., 10. };
      UniformDistributionType type = UniformDistributionType::Discrete;

      UniformEnergyDistribution chunk( std::move( energies ), std::move( type ) );

      THEN( "a UniformEnergyDistribution can be constructed and members can "
            "be tested" ) {

        CHECK( UniformDistributionType::Discrete == chunk.type() );
        CHECK( 3 == chunk.numberCosines() );

        CHECK_THAT(  2., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT(  3., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 10., WithinRel( chunk.energies()[2] ) );
      } // THEN

      THEN( "the average cosine can be calculated" ) {

        CHECK_THAT( 5., WithinRel( chunk.averageEnergy() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "Cosines for a discrete cosine distribution" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 0., 1., 4., 6. };
      UniformDistributionType type = UniformDistributionType::Interval;

      UniformEnergyDistribution chunk( std::move( energies ), std::move( type ) );

      THEN( "a UniformEnergyDistribution can be constructed and members can "
            "be tested" ) {

        CHECK( UniformDistributionType::Interval == chunk.type() );
        CHECK( 4 == chunk.numberCosines() );

        CHECK_THAT( 0., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 1., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 6., WithinRel( chunk.energies()[3] ) );
      } // THEN

      THEN( "the average cosine can be calculated" ) {

        CHECK_THAT( 2.5, WithinRel( chunk.averageEnergy() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the values are empty for a discrete uniform distribution" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformEnergyDistribution( {}, UniformDistributionType::Discrete ) );
      } // THEN
    } // WHEN

    WHEN( "there are none or only one value for an interval uniform distribution" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UniformEnergyDistribution( {}, UniformDistributionType::Interval ) );
        CHECK_THROWS( UniformEnergyDistribution( { 1. }, UniformDistributionType::Interval ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
