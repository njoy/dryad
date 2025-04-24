// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/TabulatedAngularDistributionFunction.hpp"

// other includes

// includes for test result generation
// #include <iostream>
// #include <iomanip>
// #include "scion/integration/GaussLegendre/64.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "TabulatedAngularDistributionFunction" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > cosines = { -1., 0., 0.5, 1. };
      const std::vector< double > values = { 0., 0.5, 0.75, 1. };

      TabulatedAngularDistributionFunction chunk( std::move( cosines ), std::move( values ) );

      THEN( "a TabulatedAngularDistributionFunction can be constructed and members can be tested" ) {

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == chunk.isLinearised() );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0. , WithinRel( chunk( -1. ) ) );
        CHECK_THAT( 0.5, WithinRel( chunk(  0. ) ) );
        CHECK_THAT( 0.75, WithinRel( chunk( 0.5 ) ) );
        CHECK_THAT( 1. , WithinRel( chunk(  1. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( -5. ) ) );
        CHECK_THAT( 0., WithinRel( chunk(  5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.25 , WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( 0.875, WithinRel( chunk(  0.75 ) ) );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be integrated" ) {

        CHECK_THAT( 1., WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the first raw moment of a TabulatedAngularDistributionFunction can be calculated" ) {

        CHECK_THAT( 1. / 3., WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        TabulatedAngularDistributionFunction result( { -1., 1. }, { 0., 0. } );
        TabulatedAngularDistributionFunction same( { -1., 1. }, { 1., 0. } );
        TabulatedAngularDistributionFunction threshold( { 0., 1. }, { 0., 2. } );
        TabulatedAngularDistributionFunction nonzerothreshold( { 0., 1. }, { 1., 1. } );
        TabulatedAngularDistributionFunction small( { -1., 0. }, { 0., 1. } );

        chunk += 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  2.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  2.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  2.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk *= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  1. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  1.5, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  2. , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk /= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = -chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT( -0.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT( -0.75, WithinRel( result.values()[2] ) );
        CHECK_THAT( -1.  , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk + 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  2.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  2.75, WithinRel( result.values()[2] ) );
        CHECK_THAT(  3.  , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = 2. + chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  2.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  2.75, WithinRel( result.values()[2] ) );
        CHECK_THAT(  3.  , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk - 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT( -2.  , WithinRel( result.values()[0] ) );
        CHECK_THAT( -1.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT( -1.25, WithinRel( result.values()[2] ) );
        CHECK_THAT( -1.  , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = 2. - chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  1.25, WithinRel( result.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk * 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  1.5, WithinRel( result.values()[2] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = 2. * chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  1.5, WithinRel( result.values()[2] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk / 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1.   , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.   , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5  , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.   , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.   , WithinRel( result.values()[0] ) );
        CHECK_THAT(  0.25 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  0.375, WithinRel( result.values()[2] ) );
        CHECK_THAT(  0.5  , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        chunk += same;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  1. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  1. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1. , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= same;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = chunk + same;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk - same;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[3] ) );
        CHECK_THAT( -1. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  0.5, WithinRel( result.values()[2] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        chunk += threshold;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  1.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= threshold;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = chunk + threshold;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  1.75, WithinRel( result.values()[2] ) );
        CHECK_THAT(  3.  , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk - threshold;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT( -0.25, WithinRel( result.values()[2] ) );
        CHECK_THAT( -1.  , WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        chunk += nonzerothreshold;

        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  1.5 , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.75, WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  2.  , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk -= nonzerothreshold;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = chunk + nonzerothreshold;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  1.5 , WithinRel( result.values()[2] ) );
        CHECK_THAT(  1.75, WithinRel( result.values()[3] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk - nonzerothreshold;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT( -0.5 , WithinRel( result.values()[2] ) );
        CHECK_THAT( -0.25, WithinRel( result.values()[3] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        // this will add a second point at the lower end point
        result = chunk + small;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.values()[2] ) );
        CHECK_THAT(  0.75, WithinRel( result.values()[3] ) );
        CHECK_THAT(  1.  , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        // this will add a second point at the lower end point
        result = chunk - small;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT( -0.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.values()[2] ) );
        CHECK_THAT(  0.75, WithinRel( result.values()[3] ) );
        CHECK_THAT(  1.  , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK( 4 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 4 == linear.cosines().size() );
        CHECK( 4 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 3 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data without boundaries and a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > cosines = { -1., 0., 0., 0.5, 1. };
      const std::vector< double > values = { 4., 3., 4., 3., 2. };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      TabulatedAngularDistributionFunction chunk( std::move( cosines ), std::move( values ),
                                                  interpolant );

      THEN( "a TabulatedAngularDistributionFunction can be constructed and members can be tested" ) {

        // the constructor will detect the jump and add interpolation regions
        // as required
        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  2. , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == chunk.isLinearised() );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( -1. ) ) );
        CHECK_THAT( 4., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 0.5 ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 1. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( -2. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 2. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.5, WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( 3.5, WithinRel( chunk( 0.25 ) ) );
        CHECK_THAT( 2.5, WithinRel( chunk( 0.75 ) ) );
      } // THEN

      THEN( "an InterpolationTable can be integrated" ) {

        // ( 4 + 3 ) / 2 + ( 4 + 2 ) / 2 = 6.5
        CHECK_THAT( 6.5, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the first raw moment of an InterpolationTable can be calculated" ) {

        // region 1
        // f(x) = 3 - x
        // x f(x) = 3 x - x^2
        // primitive = 3 x^2 / 2 - x^3 / 3
        // integral = - 3 / 2 - 1 / 3 = - 11 / 6
        // region 2
        // f(x) = 4 - 2 x
        // x f(x) = 4 x - 2 x^2
        // primitive = 2 x^2 - 2 x^3 / 3
        // integral = 2 - 2 / 3 = 4 / 3
        // sum = - 11 / 6 + 4 / 3 = - 1 / 2
        CHECK_THAT( -0.5, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        TabulatedAngularDistributionFunction result( { -1., 1. }, { 0., 0. } );
        TabulatedAngularDistributionFunction same( { -1., 1. }, { 1., 0. } );
        TabulatedAngularDistributionFunction threshold( { 0., 1. }, { 0., 2. } );
        TabulatedAngularDistributionFunction nonzerothreshold( { 0.5, 1. }, { 1., 1. } );
        TabulatedAngularDistributionFunction small( { -1., 0.5 }, { 1., 1. } );

        chunk += 2.;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  6. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  5. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  6. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  5. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk -= 2.;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  2. , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk *= 2.;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  8. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  6. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  8. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  6. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk /= 2.;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  2. , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        result = -chunk;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT( -4. , WithinRel( result.values()[0] ) );
        CHECK_THAT( -3. , WithinRel( result.values()[1] ) );
        CHECK_THAT( -4. , WithinRel( result.values()[2] ) );
        CHECK_THAT( -3. , WithinRel( result.values()[3] ) );
        CHECK_THAT( -2. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk + 2.;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  6. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  5. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  6. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  5. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = 2. + chunk;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  6. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  5. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  6. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  5. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk - 2.;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  0. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = 2. - chunk;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT( -2. , WithinRel( result.values()[0] ) );
        CHECK_THAT( -1. , WithinRel( result.values()[1] ) );
        CHECK_THAT( -2. , WithinRel( result.values()[2] ) );
        CHECK_THAT( -1. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  0. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk * 2.;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  8. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  6. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  8. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  6. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = 2. * chunk;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  8. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  6. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  8. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  6. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk / 2.;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1.5, WithinRel( result.values()[1] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  1.5, WithinRel( result.values()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        chunk += same;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  5.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4.5 , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  2.  , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk -= same;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  2. , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        result = chunk + same;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  5.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  3.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  4.5 , WithinRel( result.values()[2] ) );
        CHECK_THAT(  3.25, WithinRel( result.values()[3] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk - same;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  3.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  2.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  3.5 , WithinRel( result.values()[2] ) );
        CHECK_THAT(  2.75, WithinRel( result.values()[3] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        chunk += threshold;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        chunk -= threshold;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  2. , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        result = chunk + threshold;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        result = chunk - threshold;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  0. , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        chunk += nonzerothreshold;

        CHECK( 6 == chunk.cosines().size() );
        CHECK( 6 == chunk.values().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[5] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[4] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[5] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( 5 == chunk.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[2] );

        chunk -= nonzerothreshold;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3. , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  2. , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );

        result = chunk + nonzerothreshold;

        CHECK( 6 == result.cosines().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[5] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[4] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );

        result = chunk - nonzerothreshold;

        CHECK( 6 == result.cosines().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[5] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[4] ) );
        CHECK_THAT(  1. , WithinRel( result.values()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );

        // this will add a second point at the lower end point
        result = chunk + small;

        CHECK( 6 == result.cosines().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[5] ) );
        CHECK_THAT(  5. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  5. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  4. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[4] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );

        // this will add a second point at the lower end point
        result = chunk - small;

        CHECK( 6 == result.cosines().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[5] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[0] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[1] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[2] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[3] ) );
        CHECK_THAT(  3. , WithinRel( result.values()[4] ) );
        CHECK_THAT(  2. , WithinRel( result.values()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK( 5 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 5 == linear.cosines().size() );
        CHECK( 5 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );

        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 4 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( -1. , WithinRel( linear.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( linear.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( linear.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( linear.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( linear.cosines()[4] ) );

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

      const std::vector< double > cosines = { -1., 0., 0.5, 1. };
      const std::vector< double > values = { 0., 0.5, 0.75, 1. };
      const std::vector< std::size_t > boundaries = { 1, 3 };
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LogLinear
      };

      TabulatedAngularDistributionFunction chunk( std::move( cosines ),
                                                  std::move( values ),
                                                  std::move( boundaries ),
                                                  std::move( interpolants ) );

      THEN( "a TabulatedAngularDistributionFunction can be constructed and members can be tested" ) {

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.  , WithinRel( chunk( -1. ) ) );
        CHECK_THAT( 0.5 , WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0.75, WithinRel( chunk( 0.5 ) ) );
        CHECK_THAT( 1.  , WithinRel( chunk( 1. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( -2. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 2. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.25, WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( 0.61237243569579, WithinRel( chunk( 0.25 ) ) );
        CHECK_THAT( 0.86602540378444, WithinRel( chunk( 0.75 ) ) );
      } // THEN

      THEN( "an InterpolationTable can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, -1.,  0. )
        //                                     + integrator( chunk,  0.,  1. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        CHECK_THAT( 0.99279536989483, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the first raw moment of an InterpolationTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, -1.,  0. )
        //                                     + integrator( functor,  0.,  1. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 0.330014509000453, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        TabulatedAngularDistributionFunction result( { -1., 1. }, { 0., 0. } );

        chunk *= 2.;

        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  1.5 , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  2.  , WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        chunk /= 2.;

        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        result = -chunk;

        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT( -0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT( -0.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT( -0.75, WithinRel( result.values()[2] ) );
        CHECK_THAT( -1.  , WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );

        result = chunk * 2.;

        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1.  , WithinRel( result.values()[1] ) );
        CHECK_THAT(  1.5 , WithinRel( result.values()[2] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );

        result = 2. * chunk;

        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1.  , WithinRel( result.values()[1] ) );
        CHECK_THAT(  1.5 , WithinRel( result.values()[2] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );

        result = chunk / 2.;

        CHECK( 4 == result.cosines().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0.   , WithinRel( result.values()[0] ) );
        CHECK_THAT(  0.25 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  0.375, WithinRel( result.values()[2] ) );
        CHECK_THAT(  0.5  , WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
      } // THEN

      THEN( "some arithmetic operations cannot be performed" ) {

        TabulatedAngularDistributionFunction result( { 1., 4. }, { 0., 0. } );
        TabulatedAngularDistributionFunction right( { 1., 4. }, { 0., 0. } );

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

      THEN( "a TabulatedAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK( 14 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 14 == linear.cosines().size() );
        CHECK( 14 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 13 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( -1.    , WithinRel( linear.cosines()[0] ) );
        CHECK_THAT(  0.    , WithinRel( linear.cosines()[1] ) );
        CHECK_THAT(  0.0625, WithinRel( linear.cosines()[2] ) );
        CHECK_THAT(  0.125 , WithinRel( linear.cosines()[3] ) );
        CHECK_THAT(  0.1875, WithinRel( linear.cosines()[4] ) );
        CHECK_THAT(  0.25  , WithinRel( linear.cosines()[5] ) );
        CHECK_THAT(  0.3125, WithinRel( linear.cosines()[6] ) );
        CHECK_THAT(  0.375 , WithinRel( linear.cosines()[7] ) );
        CHECK_THAT(  0.4375, WithinRel( linear.cosines()[8] ) );
        CHECK_THAT(  0.5   , WithinRel( linear.cosines()[9] ) );
        CHECK_THAT(  0.625 , WithinRel( linear.cosines()[10] ) );
        CHECK_THAT(  0.75  , WithinRel( linear.cosines()[11] ) );
        CHECK_THAT(  0.875 , WithinRel( linear.cosines()[12] ) );
        CHECK_THAT(  1.    , WithinRel( linear.cosines()[13] ) );

        CHECK_THAT( 0.              , WithinRel( linear.values()[0] ) );
        CHECK_THAT( 0.5              , WithinRel( linear.values()[1] ) );
        CHECK_THAT( 0.52599475275432, WithinRel( linear.values()[2] ) );
        CHECK_THAT( 0.55334095985016, WithinRel( linear.values()[3] ) );
        CHECK_THAT( 0.58210888273045, WithinRel( linear.values()[4] ) );
        CHECK_THAT( 0.61237243569579, WithinRel( linear.values()[5] ) );
        CHECK_THAT( 0.64420937581474, WithinRel( linear.values()[6] ) );
        CHECK_THAT( 0.67770150270738, WithinRel( linear.values()[7] ) );
        CHECK_THAT( 0.71293486871561, WithinRel( linear.values()[8] ) );
        CHECK_THAT( 0.75            , WithinRel( linear.values()[9] ) );
        CHECK_THAT( 0.80592744886766, WithinRel( linear.values()[10] ) );
        CHECK_THAT( 0.86602540378444, WithinRel( linear.values()[11] ) );
        CHECK_THAT( 0.93060485910210, WithinRel( linear.values()[12] ) );
        CHECK_THAT( 1.              , WithinRel( linear.values()[13] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > cosines = { -1., 0., 0., 0.5, 1. };
      const std::vector< double > values = { 0., 0.5, 1., 1.25, 1.5 };
      const std::vector< std::size_t > boundaries = { 1, 4 };
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LogLinear
      };

      TabulatedAngularDistributionFunction chunk( std::move( cosines ),
                                                  std::move( values ),
                                                  std::move( boundaries ),
                                                  std::move( interpolants ) );

      THEN( "a TabulatedAngularDistributionFunction can be constructed and members can be tested" ) {

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  1.5 , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 0.  , WithinRel( chunk( -1. ) ) );
        CHECK_THAT( 1.  , WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 1.25, WithinRel( chunk( 0.5 ) ) );
        CHECK_THAT( 1.5 , WithinRel( chunk( 1. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( -2. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 2. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 0.25, WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( 1.11803398874989, WithinRel( chunk( 0.25 ) ) );
        CHECK_THAT( 1.36930639376292, WithinRel( chunk( 0.75 ) ) );
      } // THEN

      THEN( "an InterpolationTable can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, -1., 0. )
        //                                     + integrator( chunk,  0., 1. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        // CHECK_THAT( 1.49577938318395, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the first raw moment of an InterpolationTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, -1., 0. )
        //                                     + integrator( functor,  0., 1. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 0.581321912933929, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        TabulatedAngularDistributionFunction result( { -1., 1. }, { 0., 0. } );

        chunk *= 2.;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  2.  , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  2.5 , WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  3.  , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        chunk /= 2.;

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  1.0 , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  1.5 , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        result = -chunk;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT( -0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT( -0.5 , WithinRel( result.values()[1] ) );
        CHECK_THAT( -1.  , WithinRel( result.values()[2] ) );
        CHECK_THAT( -1.25, WithinRel( result.values()[3] ) );
        CHECK_THAT( -1.5 , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == result.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        result = chunk * 2.;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1.  , WithinRel( result.values()[1] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[2] ) );
        CHECK_THAT(  2.5 , WithinRel( result.values()[3] ) );
        CHECK_THAT(  3.  , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == result.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        result = 2. * chunk;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( result.values()[0] ) );
        CHECK_THAT(  1.  , WithinRel( result.values()[1] ) );
        CHECK_THAT(  2.  , WithinRel( result.values()[2] ) );
        CHECK_THAT(  2.5 , WithinRel( result.values()[3] ) );
        CHECK_THAT(  3.  , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == result.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        result = chunk / 2.;

        CHECK( 5 == result.cosines().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  0.   , WithinRel( result.values()[0] ) );
        CHECK_THAT(  0.25 , WithinRel( result.values()[1] ) );
        CHECK_THAT(  0.5  , WithinRel( result.values()[2] ) );
        CHECK_THAT(  0.625, WithinRel( result.values()[3] ) );
        CHECK_THAT(  0.75 , WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == result.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
      } // THEN

      THEN( "some arithmetic operations cannot be performed" ) {

        TabulatedAngularDistributionFunction result( { -1., 1. }, { 0., 0. } );
        TabulatedAngularDistributionFunction right( { -1., 1. }, { 0., 0. } );

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

      THEN( "a TabulatedAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK( 11 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 11 == linear.cosines().size() );
        CHECK( 11 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );

        CHECK(  1 == linear.boundaries()[0] );
        CHECK( 10 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( -1.   , WithinRel( linear.cosines()[0] ) );
        CHECK_THAT(  0.   , WithinRel( linear.cosines()[1] ) );
        CHECK_THAT(  0.   , WithinRel( linear.cosines()[2] ) );
        CHECK_THAT(  0.125, WithinRel( linear.cosines()[3] ) );
        CHECK_THAT(  0.25 , WithinRel( linear.cosines()[4] ) );
        CHECK_THAT(  0.375, WithinRel( linear.cosines()[5] ) );
        CHECK_THAT(  0.5  , WithinRel( linear.cosines()[6] ) );
        CHECK_THAT(  0.625, WithinRel( linear.cosines()[7] ) );
        CHECK_THAT(  0.75 , WithinRel( linear.cosines()[8] ) );
        CHECK_THAT(  0.875, WithinRel( linear.cosines()[9] ) );
        CHECK_THAT(  1.   , WithinRel( linear.cosines()[10] ) );

        CHECK_THAT( 0.              , WithinRel( linear.values()[0] ) );
        CHECK_THAT( 0.5             , WithinRel( linear.values()[1] ) );
        CHECK_THAT( 1.              , WithinRel( linear.values()[2] ) );
        CHECK_THAT( 1.05737126344056, WithinRel( linear.values()[3] ) );
        CHECK_THAT( 1.11803398874989, WithinRel( linear.values()[4] ) );
        CHECK_THAT( 1.18217701125397, WithinRel( linear.values()[5] ) );
        CHECK_THAT( 1.25            , WithinRel( linear.values()[6] ) );
        CHECK_THAT( 1.30829392424013, WithinRel( linear.values()[7] ) );
        CHECK_THAT( 1.36930639376292, WithinRel( linear.values()[8] ) );
        CHECK_THAT( 1.43316418830655, WithinRel( linear.values()[9] ) );
        CHECK_THAT( 1.5             , WithinRel( linear.values()[10] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump and boundaries "
         "that point to the second x value in the jump" ) {

    // note: at construction time, the boundary value will be set to the first point in
    //       the jump. As a result, the final data contained in this InterpolationTable is the
    //       same as the previous test.

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { -1., 0., 0., 0.5, 1. };
      const std::vector< double > y = { 0., 0.5, 1., 1.25, 1.5 };
      const std::vector< std::size_t > boundaries = { 2, 4 }; // <-- pointing to end of the jump
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LogLinear
      };

      TabulatedAngularDistributionFunction chunk( std::move( x ), std::move( y ),
                                                  std::move( boundaries ),
                                                  std::move( interpolants ) );

      THEN( "a InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  1.5 , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );           // <-- this is changed from 2 to 1
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump at the end that goes to zero" ) {

    // note: at construction time, the last x and y value will be removed and the last
    //       boundary value will be decremented by 1.

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { -1., 0., 0.5, 1., 1. }; // <-- jump at end
      const std::vector< double > y = { 0., 0.5, 0.75, 1., 0. }; // <-- last value is zero
      const std::vector< std::size_t > boundaries = { 1, 4 };   // <-- pointing to end
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LogLinear
      };

      TabulatedAngularDistributionFunction chunk( std::move( x ), std::move( y ),
                                                  std::move( boundaries ),
                                                  std::move( interpolants ) );

      THEN( "an InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.cosines()[3] ) ); // <-- last point removed
        CHECK_THAT(  0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( chunk.values()[3] ) ); // <-- last point removed
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an InterpolationTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( empty, empty ) );
        CHECK_THROWS( TabulatedAngularDistributionFunction( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { -1., 0., 0.5, 1. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      std::vector< double > x = { -1., 0., 0.5, 1. };
      std::vector< double > y = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( x ), std::move( y ),
                                                            std::move( boundaries ),
                                                            std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { -1., 0.5, 0., 1. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid contains a triple x value" ) {

      std::vector< double > x = { -1., 0., 0., 0., 0.5, 1. };
      std::vector< double > y = { 4., 3., 3., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the beginning" ) {

      std::vector< double > x = { -1., -1., 0.5, 1. };
      std::vector< double > y = { 4., 3., 1., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the end" ) {

      std::vector< double > x = { -1., 0., 1., 1. };
      std::vector< double > y = { 4., 3., 1., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      std::vector< double > x = { -1., 0., 0.5, 1. };
      std::vector< double > y = { 4., 3., 1., 4. };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( x ), std::move( y ),
                                                            std::move( boundaries ),
                                                            std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
