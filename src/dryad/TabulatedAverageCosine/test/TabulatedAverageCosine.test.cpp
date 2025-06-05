// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/TabulatedAverageCosine.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "TabulatedAverageCosine" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 1., 2., 3., 4. };
      const std::vector< double > values = { 4., 3., 2., 1. };

      TabulatedAverageCosine chunk( std::move( energies ), std::move( values ) );

      THEN( "a TabulatedAverageCosine can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerEnergyLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperEnergyLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == chunk.isLinearised() );
      } // THEN

      THEN( "a TabulatedAverageCosine can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.5, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.5, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        TabulatedAverageCosine result( { 1., 4. }, { 0., 0. } );
        TabulatedAverageCosine same( { 1., 4. }, { 0., 3. } );
        TabulatedAverageCosine threshold( { 2., 4. }, { 0., 2. } );
        TabulatedAverageCosine nonzerothreshold( { 2., 4. }, { 1., 3. } );
        TabulatedAverageCosine small( { 1., 3. }, { 0., 2. } );

        chunk += 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk *= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk /= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = -chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
        CHECK_THAT(  3., WithinRel( result.energies()[2] ) );
        CHECK_THAT(  4., WithinRel( result.energies()[3] ) );
        CHECK_THAT( -4., WithinRel( result.values()[0] ) );
        CHECK_THAT( -3., WithinRel( result.values()[1] ) );
        CHECK_THAT( -2., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk + 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 3., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = 2. + chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 3., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk - 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
        CHECK_THAT(  3., WithinRel( result.energies()[2] ) );
        CHECK_THAT(  4., WithinRel( result.energies()[3] ) );
        CHECK_THAT(  2., WithinRel( result.values()[0] ) );
        CHECK_THAT(  1., WithinRel( result.values()[1] ) );
        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = 2. - chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
        CHECK_THAT(  3., WithinRel( result.energies()[2] ) );
        CHECK_THAT(  4., WithinRel( result.energies()[3] ) );
        CHECK_THAT( -2., WithinRel( result.values()[0] ) );
        CHECK_THAT( -1., WithinRel( result.values()[1] ) );
        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
        CHECK_THAT(  1., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk * 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = 2. * chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk / 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.values()[1] ) );
        CHECK_THAT( 1.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 0.5, WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        chunk += same;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= same;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = chunk + same;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[1] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk - same;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
        CHECK_THAT(  2., WithinRel( result.values()[1] ) );
        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
        CHECK_THAT( -2., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        chunk += threshold;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= threshold;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = chunk + threshold;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( result.values()[1] ) );
        CHECK_THAT( 3.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 3.0, WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk - threshold;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
        CHECK_THAT(  3., WithinRel( result.values()[1] ) );
        CHECK_THAT(  1., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        chunk += nonzerothreshold;

        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk -= nonzerothreshold;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = chunk + nonzerothreshold;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( result.values()[0] ) );
        CHECK_THAT( 3., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 4., WithinRel( result.values()[3] ) );
        CHECK_THAT( 4., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk - nonzerothreshold;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[2] ) );
        CHECK_THAT(  3., WithinRel( result.energies()[3] ) );
        CHECK_THAT(  4., WithinRel( result.energies()[4] ) );
        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
        CHECK_THAT(  3., WithinRel( result.values()[1] ) );
        CHECK_THAT(  2., WithinRel( result.values()[2] ) );
        CHECK_THAT(  0., WithinRel( result.values()[3] ) );
        CHECK_THAT( -2., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        // this will add a second point at the lower end point
        result = chunk + small;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4. , WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[1] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[3] ) );
        CHECK_THAT( 1.0, WithinRel( result.values()[4] ) );
        CHECK( 2 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        // this will add a second point at the lower end point
        result = chunk - small;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4. , WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[1] ) );
        CHECK_THAT( 0.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[3] ) );
        CHECK_THAT( 1.0, WithinRel( result.values()[4] ) );
        CHECK( 2 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
      } // THEN

      THEN( "a TabulatedAverageCosine can be linearised" ) {

        TabulatedAverageCosine linear = chunk.linearise();

        CHECK( 4 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 4 == linear.energies().size() );
        CHECK( 4 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 3 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( 1., WithinRel( linear.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( linear.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( linear.energies()[3] ) );

        CHECK_THAT( 4., WithinRel( linear.values()[0] ) );
        CHECK_THAT( 3., WithinRel( linear.values()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.values()[2] ) );
        CHECK_THAT( 1., WithinRel( linear.values()[3] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data without boundaries and a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 1., 2., 2., 3., 4. };
      const std::vector< double > values = { 4., 3., 4., 3., 2. };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      TabulatedAverageCosine chunk( std::move( energies ), std::move( values ),
                                   interpolant );

      THEN( "a TabulatedAverageCosine can be constructed and members can be tested" ) {

        // the constructor will detect the jump and add interpolation regions
        // as required
        CHECK_THAT( 1., WithinRel( chunk.lowerEnergyLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperEnergyLimit() ) );
        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == chunk.isLinearised() );
      } // THEN

      THEN( "a TabulatedAverageCosine can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 4., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 3.5, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 2.5, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        TabulatedAverageCosine result( { 1., 4. }, { 0., 0. } );
        TabulatedAverageCosine same( { 1., 4. }, { 0., 3. } );
        TabulatedAverageCosine threshold( { 2., 4. }, { 0., 2. } );
        TabulatedAverageCosine nonzerothreshold( { 3., 4. }, { 1., 2. } );
        TabulatedAverageCosine small( { 1., 3. }, { 0., 2. } );

        chunk += 2.;

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk -= 2.;

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk *= 2.;

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk /= 2.;

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        result = -chunk;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[2] ) );
        CHECK_THAT(  3., WithinRel( result.energies()[3] ) );
        CHECK_THAT(  4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( -4., WithinRel( result.values()[0] ) );
        CHECK_THAT( -3., WithinRel( result.values()[1] ) );
        CHECK_THAT( -4., WithinRel( result.values()[2] ) );
        CHECK_THAT( -3., WithinRel( result.values()[3] ) );
        CHECK_THAT( -2., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk + 2.;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
        CHECK_THAT( 6., WithinRel( result.values()[2] ) );
        CHECK_THAT( 5., WithinRel( result.values()[3] ) );
        CHECK_THAT( 4., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = 2. + chunk;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
        CHECK_THAT( 6., WithinRel( result.values()[2] ) );
        CHECK_THAT( 5., WithinRel( result.values()[3] ) );
        CHECK_THAT( 4., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk - 2.;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 2., WithinRel( result.values()[0] ) );
        CHECK_THAT( 1., WithinRel( result.values()[1] ) );
        CHECK_THAT( 2., WithinRel( result.values()[2] ) );
        CHECK_THAT( 1., WithinRel( result.values()[3] ) );
        CHECK_THAT( 0., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = 2. - chunk;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[2] ) );
        CHECK_THAT(  3., WithinRel( result.energies()[3] ) );
        CHECK_THAT(  4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( -2., WithinRel( result.values()[0] ) );
        CHECK_THAT( -1., WithinRel( result.values()[1] ) );
        CHECK_THAT( -2., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
        CHECK_THAT(  0., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk * 2.;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 8., WithinRel( result.values()[2] ) );
        CHECK_THAT( 6., WithinRel( result.values()[3] ) );
        CHECK_THAT( 4., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = 2. * chunk;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 8., WithinRel( result.values()[2] ) );
        CHECK_THAT( 6., WithinRel( result.values()[3] ) );
        CHECK_THAT( 4., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk / 2.;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4. , WithinRel( result.energies()[4] ) );
        CHECK_THAT( 2. , WithinRel( result.values()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.values()[1] ) );
        CHECK_THAT( 2. , WithinRel( result.values()[2] ) );
        CHECK_THAT( 1.5, WithinRel( result.values()[3] ) );
        CHECK_THAT( 1. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        chunk += same;

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk -= same;

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        result = chunk + same;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( result.values()[0] ) );
        CHECK_THAT( 4., WithinRel( result.values()[1] ) );
        CHECK_THAT( 5., WithinRel( result.values()[2] ) );
        CHECK_THAT( 5., WithinRel( result.values()[3] ) );
        CHECK_THAT( 5., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk - same;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
        CHECK_THAT(  2., WithinRel( result.values()[1] ) );
        CHECK_THAT(  3., WithinRel( result.values()[2] ) );
        CHECK_THAT(  1., WithinRel( result.values()[3] ) );
        CHECK_THAT( -1., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        chunk += threshold;

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk -= threshold;

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        result = chunk + threshold;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( result.values()[0] ) );
        CHECK_THAT( 3., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 4., WithinRel( result.values()[3] ) );
        CHECK_THAT( 4., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk - threshold;

        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( result.values()[0] ) );
        CHECK_THAT( 3., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
        CHECK_THAT( 0., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        chunk += nonzerothreshold;

        CHECK( 6 == chunk.energies().size() );
        CHECK( 6 == chunk.values().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[5] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[5] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( 5 == chunk.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[2] );

        chunk -= nonzerothreshold;

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        result = chunk + nonzerothreshold;

        CHECK( 6 == result.energies().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[5] ) );
        CHECK_THAT( 4., WithinRel( result.values()[0] ) );
        CHECK_THAT( 3., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 3., WithinRel( result.values()[3] ) );
        CHECK_THAT( 4., WithinRel( result.values()[4] ) );
        CHECK_THAT( 4., WithinRel( result.values()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );

        result = chunk - nonzerothreshold;

        CHECK( 6 == result.energies().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[5] ) );
        CHECK_THAT( 4., WithinRel( result.values()[0] ) );
        CHECK_THAT( 3., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 3., WithinRel( result.values()[3] ) );
        CHECK_THAT( 2., WithinRel( result.values()[4] ) );
        CHECK_THAT( 0., WithinRel( result.values()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );

        // this will add a second point at the lower end point
        result = chunk + small;

        CHECK( 6 == result.energies().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[5] ) );
        CHECK_THAT( 4., WithinRel( result.values()[0] ) );
        CHECK_THAT( 4., WithinRel( result.values()[1] ) );
        CHECK_THAT( 5., WithinRel( result.values()[2] ) );
        CHECK_THAT( 5., WithinRel( result.values()[3] ) );
        CHECK_THAT( 3., WithinRel( result.values()[4] ) );
        CHECK_THAT( 2., WithinRel( result.values()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );

        // this will add a second point at the lower end point
        result = chunk - small;

        CHECK( 6 == result.energies().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[5] ) );
        CHECK_THAT( 4., WithinRel( result.values()[0] ) );
        CHECK_THAT( 2., WithinRel( result.values()[1] ) );
        CHECK_THAT( 3., WithinRel( result.values()[2] ) );
        CHECK_THAT( 1., WithinRel( result.values()[3] ) );
        CHECK_THAT( 3., WithinRel( result.values()[4] ) );
        CHECK_THAT( 2., WithinRel( result.values()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );
      } // THEN

      THEN( "a TabulatedAverageCosine can be linearised" ) {

        TabulatedAverageCosine linear = chunk.linearise();

        CHECK( 5 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 5 == linear.energies().size() );
        CHECK( 5 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );

        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 4 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( 1., WithinRel( linear.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( linear.energies()[4] ) );

        CHECK_THAT( 4., WithinRel( linear.values()[0] ) );
        CHECK_THAT( 3., WithinRel( linear.values()[1] ) );
        CHECK_THAT( 4., WithinRel( linear.values()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.values()[3] ) );
        CHECK_THAT( 2., WithinRel( linear.values()[4] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions without a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 1., 2., 3., 4. };
      const std::vector< double > values = { 4., 3., 2., 1. };
      const std::vector< std::size_t > boundaries = { 1, 3 };
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedAverageCosine chunk( std::move( energies ),
                                   std::move( values ),
                                   std::move( boundaries ),
                                   std::move( interpolants ) );

      THEN( "a TabulatedAverageCosine can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerEnergyLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperEnergyLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
      } // THEN

      THEN( "a TabulatedAverageCosine can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid (lin-lin piece)
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );

        // values of x inside the x grid (lin-log piece)
        CHECK_THAT( 2.44966028678679, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.46416306545103, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        TabulatedAverageCosine result( { 1., 4. }, { 0., 0. } );

        chunk *= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        chunk /= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        result = -chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
        CHECK_THAT(  3., WithinRel( result.energies()[2] ) );
        CHECK_THAT(  4., WithinRel( result.energies()[3] ) );
        CHECK_THAT( -4., WithinRel( result.values()[0] ) );
        CHECK_THAT( -3., WithinRel( result.values()[1] ) );
        CHECK_THAT( -2., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );

        result = chunk * 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );

        result = 2. * chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );

        result = chunk / 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.energies().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.values()[1] ) );
        CHECK_THAT( 1.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 0.5, WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
      } // THEN

      THEN( "some arithmetic operations cannot be performed" ) {

        TabulatedAverageCosine result( { 1., 4. }, { 0., 0. } );
        TabulatedAverageCosine right( { 1., 4. }, { 0., 0. } );

        // scalar operations
        CHECK_THROWS( chunk += 2. );
        CHECK_THROWS( chunk -= 2. );
        CHECK_THROWS( result = chunk + 2. );
        CHECK_THROWS( result = chunk - 2. );
        CHECK_THROWS( result = 2. + chunk );
        CHECK_THROWS( result = 2. - chunk );

        // table operations
        CHECK_THROWS( chunk += right );
        CHECK_THROWS( chunk -= right );
        CHECK_THROWS( result = chunk + right );
        CHECK_THROWS( result = chunk - right );
      } // THEN

      THEN( "a TabulatedAverageCosine can be linearised" ) {

        TabulatedAverageCosine linear = chunk.linearise();

        CHECK( 18 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 18 == linear.energies().size() );
        CHECK( 18 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 17 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( 1.   , WithinRel( linear.energies()[0] ) );
        CHECK_THAT( 2.   , WithinRel( linear.energies()[1] ) );
        CHECK_THAT( 2.125, WithinRel( linear.energies()[2] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.energies()[3] ) );
        CHECK_THAT( 2.375, WithinRel( linear.energies()[4] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.energies()[5] ) );
        CHECK_THAT( 2.625, WithinRel( linear.energies()[6] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.energies()[7] ) );
        CHECK_THAT( 2.875, WithinRel( linear.energies()[8] ) );
        CHECK_THAT( 3.   , WithinRel( linear.energies()[9] ) );
        CHECK_THAT( 3.125, WithinRel( linear.energies()[10] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.energies()[11] ) );
        CHECK_THAT( 3.375, WithinRel( linear.energies()[12] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.energies()[13] ) );
        CHECK_THAT( 3.625, WithinRel( linear.energies()[14] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.energies()[15] ) );
        CHECK_THAT( 3.875, WithinRel( linear.energies()[16] ) );
        CHECK_THAT( 4.   , WithinRel( linear.energies()[17] ) );

        CHECK_THAT( 4.              , WithinRel( linear.values()[0] ) );
        CHECK_THAT( 3.              , WithinRel( linear.values()[1] ) );
        CHECK_THAT( 2.85048128530886, WithinRel( linear.values()[2] ) );
        CHECK_THAT( 2.70951129135145, WithinRel( linear.values()[3] ) );
        CHECK_THAT( 2.57616511633150, WithinRel( linear.values()[4] ) );
        CHECK_THAT( 2.44966028678679, WithinRel( linear.values()[5] ) );
        CHECK_THAT( 2.32932893596581, WithinRel( linear.values()[6] ) );
        CHECK_THAT( 2.21459646033567, WithinRel( linear.values()[7] ) );
        CHECK_THAT( 2.10496492439848, WithinRel( linear.values()[8] ) );
        CHECK_THAT( 2.              , WithinRel( linear.values()[9] ) );
        CHECK_THAT( 1.85810031827028, WithinRel( linear.values()[10] ) );
        CHECK_THAT( 1.72176678584324, WithinRel( linear.values()[11] ) );
        CHECK_THAT( 1.59057916034679, WithinRel( linear.values()[12] ) );
        CHECK_THAT( 1.46416306545103, WithinRel( linear.values()[13] ) );
        CHECK_THAT( 1.34218354996644, WithinRel( linear.values()[14] ) );
        CHECK_THAT( 1.22433973930853, WithinRel( linear.values()[15] ) );
        CHECK_THAT( 1.11036036428687, WithinRel( linear.values()[16] ) );
        CHECK_THAT( 1.              , WithinRel( linear.values()[17] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 1., 2., 2., 3., 4. };
      const std::vector< double > values = { 4., 3., 4., 3., 2. };
      const std::vector< std::size_t > boundaries = { 1, 4 };
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedAverageCosine chunk( std::move( energies ),
                                   std::move( values ),
                                   std::move( boundaries ),
                                   std::move( interpolants ) );

      THEN( "a TabulatedAverageCosine can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerEnergyLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperEnergyLimit() ) );
        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
      } // THEN

      THEN( "a TabulatedAverageCosine can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 4., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid (lin-lin piece)
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );

        // values of x inside the x grid (lin-log piece)
        CHECK_THAT( 3.44966028678679, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 2.46416306545103, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        TabulatedAverageCosine result( { 1., 4. }, { 0., 0. } );

        chunk *= 2.;

        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        chunk /= 2.;

        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        result = -chunk;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( -4., WithinRel( result.values()[0] ) );
        CHECK_THAT( -3., WithinRel( result.values()[1] ) );
        CHECK_THAT( -4., WithinRel( result.values()[2] ) );
        CHECK_THAT( -3., WithinRel( result.values()[3] ) );
        CHECK_THAT( -2., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );

        result = chunk * 2.;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 8., WithinRel( result.values()[2] ) );
        CHECK_THAT( 6., WithinRel( result.values()[3] ) );
        CHECK_THAT( 4., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );

        result = 2. * chunk;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 8., WithinRel( result.values()[2] ) );
        CHECK_THAT( 6., WithinRel( result.values()[3] ) );
        CHECK_THAT( 4., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );

        result = chunk / 2.;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.energies().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( result.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( result.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( result.energies()[4] ) );
        CHECK_THAT( 2. , WithinRel( result.values()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.values()[1] ) );
        CHECK_THAT( 2. , WithinRel( result.values()[2] ) );
        CHECK_THAT( 1.5, WithinRel( result.values()[3] ) );
        CHECK_THAT( 1. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
      } // THEN

      THEN( "arithmetic operations cannot be performed" ) {

        TabulatedAverageCosine result( { 1., 4. }, { 0., 0. } );
        TabulatedAverageCosine right( { 1., 4. }, { 0., 0. } );

        // scalar operations
        CHECK_THROWS( chunk += 2. );
        CHECK_THROWS( chunk -= 2. );
        CHECK_THROWS( result = chunk + 2. );
        CHECK_THROWS( result = chunk - 2. );
        CHECK_THROWS( result = 2. + chunk );
        CHECK_THROWS( result = 2. - chunk );

        // table operations
        CHECK_THROWS( chunk += right );
        CHECK_THROWS( chunk -= right );
        CHECK_THROWS( result = chunk + right );
        CHECK_THROWS( result = chunk - right );
      } // THEN

      THEN( "a TabulatedAverageCosine can be linearised" ) {

        TabulatedAverageCosine linear = chunk.linearise();

        CHECK( 12 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 12 == linear.energies().size() );
        CHECK( 12 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );

        CHECK(  1 == linear.boundaries()[0] );
        CHECK( 11 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( 1.   , WithinRel( linear.energies()[0] ) );
        CHECK_THAT( 2.   , WithinRel( linear.energies()[1] ) );
        CHECK_THAT( 2.   , WithinRel( linear.energies()[2] ) );
        CHECK_THAT( 2.125, WithinRel( linear.energies()[3] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.energies()[4] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.energies()[5] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.energies()[6] ) );
        CHECK_THAT( 3.   , WithinRel( linear.energies()[7] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.energies()[8] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.energies()[9] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.energies()[10] ) );
        CHECK_THAT( 4.   , WithinRel( linear.energies()[11] ) );

        CHECK_THAT( 4.              , WithinRel( linear.values()[0] ) );
        CHECK_THAT( 3.              , WithinRel( linear.values()[1] ) );
        CHECK_THAT( 4.              , WithinRel( linear.values()[2] ) );
        CHECK_THAT( 3.85048128530886, WithinRel( linear.values()[3] ) );
        CHECK_THAT( 3.70951129135145, WithinRel( linear.values()[4] ) );
        CHECK_THAT( 3.44966028678679, WithinRel( linear.values()[5] ) );
        CHECK_THAT( 3.21459646033567, WithinRel( linear.values()[6] ) );
        CHECK_THAT( 3.              , WithinRel( linear.values()[7] ) );
        CHECK_THAT( 2.72176678584324, WithinRel( linear.values()[8] ) );
        CHECK_THAT( 2.46416306545103, WithinRel( linear.values()[9] ) );
        CHECK_THAT( 2.22433973930853, WithinRel( linear.values()[10] ) );
        CHECK_THAT( 2.              , WithinRel( linear.values()[11] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump and boundaries "
         "that point to the second x value in the jump" ) {

    // note: at construction time, the boundary value will be set to the first point in
    //       the jump. As a result, the final data contained in this TabulatedAverageCosine is the
    //       same as the previous test.

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 4., 3., 2. };
      const std::vector< std::size_t > boundaries = { 2, 4 }; // <-- pointing to end of the jump
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedAverageCosine chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "a TabulatedAverageCosine can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.energies().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );           // <-- this is changed from 2 to 1
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump at the end that goes to zero" ) {

    // note: at construction time, the last x and y value will be removed and the last
    //       boundary value will be decremented by 1.

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 3., 4., 4. }; // <-- jump at end
      const std::vector< double > y = { 4., 3., 2., 1., 0. }; // <-- last value is zero
      const std::vector< std::size_t > boundaries = { 1, 4 }; // <-- pointing to end
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedAverageCosine chunk( std::move( x ), std::move( y ),
                                   std::move( boundaries ),
                                   std::move( interpolants ) );

      THEN( "an TabulatedAverageCosine can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.energies().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) ); // <-- last point removed
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) ); // <-- last point removed
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an TabulatedAverageCosine object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAverageCosine( empty, empty ) );
        CHECK_THROWS( TabulatedAverageCosine( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAverageCosine( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAverageCosine( std::move( x ), std::move( y ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAverageCosine( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid contains a triple x value" ) {

      std::vector< double > x = { 1., 2., 2., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 3., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAverageCosine( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the beginning" ) {

      std::vector< double > x = { 1., 1., 3., 4. };
      std::vector< double > y = { 4., 3., 1., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAverageCosine( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the end" ) {

      std::vector< double > x = { 1., 2., 4., 4. };
      std::vector< double > y = { 4., 3., 1., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAverageCosine( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      std::vector< double > x = { 1., 2., 4., 4. };
      std::vector< double > y = { 4., 3., 1., 4. };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAverageCosine( std::move( x ), std::move( y ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
