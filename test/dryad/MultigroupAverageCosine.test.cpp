// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/MultigroupAverageCosine.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "MultigroupAverageCosine" ) {

  GIVEN( "grouped data" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > boundaries = { 1., 2., 3., 4., 5. };
      const std::vector< double > values = { 4., 3., 2., 1. };

      MultigroupAverageCosine chunk( std::move( boundaries ), std::move( values ) );

      THEN( "a MultigroupAverageCosine can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerEnergyLimit() ) );
        CHECK_THAT( 5., WithinRel( chunk.upperEnergyLimit() ) );
        CHECK( 4 == chunk.numberGroups() );
        CHECK( 5 == chunk.boundaries().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK_THAT( 1., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.boundaries()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        MultigroupAverageCosine result( { 0., 5. }, { 0. } );
        MultigroupAverageCosine other( { 1., 2., 3., 4., 5. }, { 1., 2., 3., 4. } );
        MultigroupAverageCosine different( { 1., 2., 3., 4. }, { 1., 2., 3. } );

        chunk += 2.;

        CHECK( 4 == chunk.numberGroups() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 5 == chunk.boundaries().size() );
        CHECK_THAT( 1., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.boundaries()[4] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );

        chunk -= 2.;

        CHECK( 4 == chunk.numberGroups() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 5 == chunk.boundaries().size() );
        CHECK_THAT( 1., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.boundaries()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );

        chunk *= 2.;

        CHECK( 4 == chunk.numberGroups() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 5 == chunk.boundaries().size() );
        CHECK_THAT( 1., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.boundaries()[4] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[3] ) );

        chunk /= 2.;

        CHECK( 4 == chunk.numberGroups() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 5 == chunk.boundaries().size() );
        CHECK_THAT( 1., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.boundaries()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );

        result = -chunk;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT( -4., WithinRel( result.values()[0] ) );
        CHECK_THAT( -3., WithinRel( result.values()[1] ) );
        CHECK_THAT( -2., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );

        result = chunk + 2.;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 3., WithinRel( result.values()[3] ) );

        result = 2. + chunk;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 3., WithinRel( result.values()[3] ) );

        result = chunk - 2.;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT(  2., WithinRel( result.values()[0] ) );
        CHECK_THAT(  1., WithinRel( result.values()[1] ) );
        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );

        result = 2. - chunk;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT( -2., WithinRel( result.values()[0] ) );
        CHECK_THAT( -1., WithinRel( result.values()[1] ) );
        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
        CHECK_THAT(  1., WithinRel( result.values()[3] ) );

        result = chunk * 2.;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );

        result = 2. * chunk;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );

        result = chunk / 2;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT( 2. , WithinRel( result.values()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.values()[1] ) );
        CHECK_THAT( 1. , WithinRel( result.values()[2] ) );
        CHECK_THAT( 0.5, WithinRel( result.values()[3] ) );

        chunk += other;

        CHECK( 4 == chunk.numberGroups() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 5 == chunk.boundaries().size() );
        CHECK_THAT( 1., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.boundaries()[4] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[3] ) );

        chunk -= other;

        CHECK( 4 == chunk.numberGroups() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 5 == chunk.boundaries().size() );
        CHECK_THAT( 1., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.boundaries()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );

        result = chunk + other;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT( 5., WithinRel( result.values()[0] ) );
        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
        CHECK_THAT( 5., WithinRel( result.values()[2] ) );
        CHECK_THAT( 5., WithinRel( result.values()[3] ) );

        result = chunk - other;

        CHECK( 4 == result.numberGroups() );
        CHECK( 4 == result.values().size() );
        CHECK( 5 == result.boundaries().size() );
        CHECK_THAT( 1., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 2., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 3., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 4., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 5., WithinRel( result.boundaries()[4] ) );
        CHECK_THAT(  3., WithinRel( result.values()[0] ) );
        CHECK_THAT(  1., WithinRel( result.values()[1] ) );
        CHECK_THAT( -1., WithinRel( result.values()[2] ) );
        CHECK_THAT( -3., WithinRel( result.values()[3] ) );

        CHECK_THROWS( chunk += different );
        CHECK_THROWS( chunk -= different );
        CHECK_THROWS( result = chunk + different );
        CHECK_THROWS( result = chunk - different );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an MultigroupAverageCosine object" ) {

    WHEN( "there are not enough values in the boundaries or values" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MultigroupAverageCosine( one, empty ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries or values do not have the current number of values" ) {

      std::vector< double > boundaries = { 1., 2., 3., 4. };
      std::vector< double > values = { 4., 3. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MultigroupAverageCosine( std::move( boundaries ), std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are not sorted" ) {

      std::vector< double > boundaries = { 1., 3., 2., 4. };
      std::vector< double > values = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MultigroupAverageCosine( std::move( boundaries ), std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are not unique" ) {

      std::vector< double > boundaries = { 1., 3., 3., 4. };
      std::vector< double > values = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( MultigroupAverageCosine( std::move( boundaries ), std::move( values ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
