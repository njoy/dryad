// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"

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

      std::vector< double > cosines = { -1., 0., 0.5, 1. };
      std::vector< double > values = { 0., 0.5, 0.75, 1. };

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
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be copy and move constructed" ) {

        TabulatedAngularDistributionFunction copy( chunk );

        CHECK_THAT( -1., WithinRel( copy.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( copy.upperCosineLimit() ) );
        CHECK( 4 == copy.numberPoints() );
        CHECK( 1 == copy.numberRegions() );
        CHECK( 4 == copy.cosines().size() );
        CHECK( 4 == copy.values().size() );
        CHECK( 1 == copy.boundaries().size() );
        CHECK( 1 == copy.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( copy.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( copy.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( copy.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( copy.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( copy.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( copy.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( copy.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( copy.values()[3] ) );
        CHECK( 3 == copy.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == copy.interpolants()[0] );
        CHECK( true == copy.isLinearised() );
        CHECK( true == copy.isCurated() );

        TabulatedAngularDistributionFunction move( std::move( copy ) );

        CHECK_THAT( -1., WithinRel( move.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( move.upperCosineLimit() ) );
        CHECK( 4 == move.numberPoints() );
        CHECK( 1 == move.numberRegions() );
        CHECK( 4 == move.cosines().size() );
        CHECK( 4 == move.values().size() );
        CHECK( 1 == move.boundaries().size() );
        CHECK( 1 == move.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( move.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( move.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( move.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( move.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( move.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( move.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( move.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( move.values()[3] ) );
        CHECK( 3 == move.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == move.interpolants()[0] );
        CHECK( true == move.isLinearised() );
        CHECK( true == move.isCurated() );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be copy and move assigned" ) {

        TabulatedAngularDistributionFunction copy( { -1., 1. }, { 0., 0. } );
        copy = chunk;

        CHECK_THAT( -1., WithinRel( copy.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( copy.upperCosineLimit() ) );
        CHECK( 4 == copy.numberPoints() );
        CHECK( 1 == copy.numberRegions() );
        CHECK( 4 == copy.cosines().size() );
        CHECK( 4 == copy.values().size() );
        CHECK( 1 == copy.boundaries().size() );
        CHECK( 1 == copy.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( copy.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( copy.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( copy.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( copy.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( copy.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( copy.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( copy.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( copy.values()[3] ) );
        CHECK( 3 == copy.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == copy.interpolants()[0] );
        CHECK( true == copy.isLinearised() );
        CHECK( true == copy.isCurated() );

        TabulatedAngularDistributionFunction move( { -1., 1. }, { 0., 0. } );
        move = std::move( copy );

        CHECK_THAT( -1., WithinRel( move.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( move.upperCosineLimit() ) );
        CHECK( 4 == move.numberPoints() );
        CHECK( 1 == move.numberRegions() );
        CHECK( 4 == move.cosines().size() );
        CHECK( 4 == move.values().size() );
        CHECK( 1 == move.boundaries().size() );
        CHECK( 1 == move.interpolants().size() );
        CHECK_THAT( -1.  , WithinRel( move.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( move.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( move.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( move.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( move.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( move.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( move.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( move.values()[3] ) );
        CHECK( 3 == move.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == move.interpolants()[0] );
        CHECK( true == move.isLinearised() );
        CHECK( true == move.isCurated() );
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

      THEN( "the cumulative integral of a TabulatedAngularDistributionFunction can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0.    , WithinRel( cumulative[0] ) );
        CHECK_THAT( 0.25  , WithinRel( cumulative[1] ) );
        CHECK_THAT( 0.5625, WithinRel( cumulative[2] ) );
        CHECK_THAT( 1.    , WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the mean of a TabulatedAngularDistributionFunction can be calculated" ) {

        CHECK_THAT( 1. / 3., WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        TabulatedAngularDistributionFunction result( { -1., 1. }, { 0., 0. } );
        TabulatedAngularDistributionFunction same( { -1., 1. }, { 1., 0. } );
        TabulatedAngularDistributionFunction threshold( { 0., 1. }, { 0., 2. } );
        TabulatedAngularDistributionFunction nonzerothreshold( { 0., 1. }, { 1., 1. } );
        TabulatedAngularDistributionFunction small( { -1., 0. }, { 0., 1. } );

        chunk += 2.;

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
        CHECK_THAT(  2.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  2.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  2.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= 2.;

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

        chunk *= 2.;

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
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

        result = -chunk;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
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

        result = chunk + same;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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
        CHECK_THAT(  1.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  3.  , WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= threshold;

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

        result = chunk + threshold;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
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

        result = chunk + nonzerothreshold;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        // this will add a second point at the upper end point of small
        result = chunk + small;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        // this will add a second point at the upper end point of small
        result = chunk - small;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK_THAT( -1., WithinRel( linear.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( linear.upperCosineLimit() ) );
        CHECK( 4 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 4 == linear.cosines().size() );
        CHECK( 4 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 3 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( -1.  , WithinRel( linear.cosines()[0] ) );
        CHECK_THAT(  0.  , WithinRel( linear.cosines()[1] ) );
        CHECK_THAT(  0.5 , WithinRel( linear.cosines()[2] ) );
        CHECK_THAT(  1.  , WithinRel( linear.cosines()[3] ) );
        CHECK_THAT(  0.  , WithinRel( linear.values()[0] ) );
        CHECK_THAT(  0.5 , WithinRel( linear.values()[1] ) );
        CHECK_THAT(  0.75, WithinRel( linear.values()[2] ) );
        CHECK_THAT(  1.  , WithinRel( linear.values()[3] ) );

        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data without boundaries and a jump" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > cosines = { -1., 0., 0., 0.5, 1. };
      std::vector< double > values = { 4., 3., 4., 3., 2. };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      TabulatedAngularDistributionFunction chunk( std::move( cosines ),
                                   std::move( values ),
                                   interpolant );

      THEN( "a TabulatedAngularDistributionFunction can be constructed and members can be tested" ) {

        // the constructor will detect the jump and add interpolation regions
        // as required
        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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
        CHECK( true == chunk.isCurated() );
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

      THEN( "a TabulatedAngularDistributionFunction can be integrated" ) {

        // ( 4 + 3 ) / 2 + ( 4 + 2 ) / 2 = 6.5
        CHECK_THAT( 6.5, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of a TabulatedAngularDistributionFunction can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 5 == cumulative.size() );
        CHECK_THAT( 0.  , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5 , WithinRel( cumulative[1] ) );
        CHECK_THAT( 3.5 , WithinRel( cumulative[2] ) );
        CHECK_THAT( 5.25, WithinRel( cumulative[3] ) );
        CHECK_THAT( 6.5 , WithinRel( cumulative[4] ) );
      } // THEN

      THEN( "the mean of a TabulatedAngularDistributionFunction can be calculated" ) {

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
        CHECK_THAT( -0.5 / 6.5, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK_THAT( -1., WithinRel( linear.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( linear.upperCosineLimit() ) );
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
        CHECK( true == linear.isCurated() );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        TabulatedAngularDistributionFunction result( { -1., 1. }, { 0., 0. } );
        TabulatedAngularDistributionFunction same( { -1., 1. }, { 1., 0. } );
        TabulatedAngularDistributionFunction threshold( { 0., 1. }, { 0., 2. } );
        TabulatedAngularDistributionFunction nonzerothreshold( { 0.5, 1. }, { 1., 1. } );
        TabulatedAngularDistributionFunction small( { -1., 0.5 }, { 1., 1. } );

        chunk += 2.;

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 6 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 6 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
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

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 6 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
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

        // this will add a second point at the upper end point of small
        result = chunk + small;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 6 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
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

        // this will add a second point at the upper end point of small
        result = chunk - small;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 6 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
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
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions without a jump" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > cosines = { -1., 0., 0.5, 1. };
      std::vector< double > values = { 0., 0.5, 0.75, 1. };
      std::vector< std::size_t > boundaries = { 1, 3 };
      std::vector< InterpolationType > interpolants = {

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
        CHECK( true == chunk.isCurated() );
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

      THEN( "a TabulatedAngularDistributionFunction can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, -1.,  0. )
        //                                     + integrator( chunk,  0.,  1. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        CHECK_THAT( 0.99279536989483, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of a TabulatedAngularDistributionFunction can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, -1. , 0. ) << ' '
        //                                    << integrator( chunk, -1. , 0. )
        //                                     + integrator( chunk,  0. , 0.5 ) << ' '
        //                                    << integrator( chunk, -1. , 0. )
        //                                     + integrator( chunk,  0. , 0.5 )
        //                                     + integrator( chunk,  0.5, 1. ) << std::endl;
        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0.               , WithinRel( cumulative[0] ) );
        CHECK_THAT( 0.25             , WithinRel( cumulative[1] ) );
        CHECK_THAT( 0.558287932797054, WithinRel( cumulative[2] ) );
        CHECK_THAT( 0.99279536989483 , WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the mean of a TabulatedAngularDistributionFunction can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, -1.,  0. )
        //                                     + integrator( functor,  0.,  1. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 0.330014509000453 / 0.99279536989483, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK_THAT( -1., WithinRel( linear.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( linear.upperCosineLimit() ) );
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
        CHECK( true == linear.isCurated() );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        TabulatedAngularDistributionFunction result( { -1., 1. }, { 0., 0. } );

        chunk *= 2.;

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
        CHECK_THAT(  1.  , WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  1.5 , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  2.  , WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );

        chunk /= 2.;

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
        CHECK( true == chunk.isCurated() );

        result = -chunk;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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
        CHECK( true == result.isCurated() );

        result = chunk * 2.;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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
        CHECK( true == result.isCurated() );

        result = 2. * chunk;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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
        CHECK( true == result.isCurated() );

        result = chunk / 2.;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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
        CHECK( true == result.isCurated() );
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
        CHECK_THROWS( right += chunk );
        CHECK_THROWS( right -= chunk );
        CHECK_THROWS( result = right + chunk );
        CHECK_THROWS( result = right - chunk );

        // the table is unchanged after the failed operations
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
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > cosines = { -1., 0., 0., 0.5, 1. };
      std::vector< double > values = { 0., 0.5, 1., 1.25, 1.5 };
      std::vector< std::size_t > boundaries = { 1, 4 };
      std::vector< InterpolationType > interpolants = {

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
        CHECK_THAT(  1.  , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  1.5 , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
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

      THEN( "a TabulatedAngularDistributionFunction can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, -1., 0. )
        //                                     + integrator( chunk,  0., 1. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        CHECK_THAT( 1.49577938318395, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of a TabulatedAngularDistributionFunction can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, -1. , 0. ) << ' '
        //                                    << integrator( chunk, -1. , 0. )
        //                                     + integrator( chunk,  0. , 0.5 ) << ' '
        //                                    << integrator( chunk, -1. , 0. )
        //                                     + integrator( chunk,  0. , 0.5 )
        //                                     + integrator( chunk,  0.5, 1. ) << std::endl;
        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 5 == cumulative.size() );
        CHECK_THAT( 0.               , WithinRel( cumulative[0] ) );
        CHECK_THAT( 0.25             , WithinRel( cumulative[1] ) );
        CHECK_THAT( 0.25             , WithinRel( cumulative[2] ) );
        CHECK_THAT( 0.810177514715569, WithinRel( cumulative[3] ) );
        CHECK_THAT( 1.49577938318395 , WithinRel( cumulative[4] ) );
      } // THEN

      THEN( "the mean of a TabulatedAngularDistributionFunction can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, -1., 0. )
        //                                     + integrator( functor,  0., 1. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 0.581321912933929 / 1.49577938318395, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be linearised" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK_THAT( -1., WithinRel( linear.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( linear.upperCosineLimit() ) );
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
        CHECK( true == linear.isCurated() );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        TabulatedAngularDistributionFunction result( { -1., 1. }, { 0., 0. } );

        chunk *= 2.;

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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
        CHECK( true == chunk.isCurated() );

        chunk /= 2.;

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
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
        CHECK( true == chunk.isCurated() );

        result = -chunk;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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
        CHECK( true == result.isCurated() );

        result = chunk * 2.;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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
        CHECK( true == result.isCurated() );

        result = 2. * chunk;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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
        CHECK( true == result.isCurated() );

        result = chunk / 2.;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
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
        CHECK( true == result.isCurated() );
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
        CHECK_THROWS( right += chunk );
        CHECK_THROWS( right -= chunk );
        CHECK_THROWS( result = right + chunk );
        CHECK_THROWS( result = right - chunk );

        // the table is unchanged after the failed operations
        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
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
        CHECK_THAT(  1.  , WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  1.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  1.5 , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump that consist of "
         "more than 2 points" ) {

    // note: by default (curate = false), the extraneous points in between the first and
    //       last x value in the jump are kept. boundaries always point to the first point
    //       in the jump, regardless of curation.

    WHEN( "the data is given explicitly and curate is not requested" ) {

      std::vector< double > cosines = { -1., 0., 0., 0., 0.5, 1. }; // <-- jump of 3 x values
      std::vector< double > values = { 0., 0.5, 0.25, 1., 1.25, 1.5 };
      std::vector< std::size_t > boundaries = { 2, 5 }; // <-- pointing to middle of the jump
      std::vector< InterpolationType > interpolants = {

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
        CHECK( 6 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 6 == chunk.cosines().size() );
        CHECK( 6 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[5] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 0.25, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 1.25, WithinRel( chunk.values()[4] ) );
        CHECK_THAT( 1.5 , WithinRel( chunk.values()[5] ) );
        CHECK( 1 == chunk.boundaries()[0] );         // <-- this is changed from 2 to 1
        CHECK( 5 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );
      } // THEN

      THEN( "the table can be curated on demand and the extraneous points are removed" ) {

        // note: curate() curates the table in place - it does not return a new instance
        chunk.curate();

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 1.5 , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "the table can be linearised and the extraneous point in the jump is removed" ) {

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK_THAT( -1., WithinRel( linear.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( linear.upperCosineLimit() ) );
        CHECK( 11 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );
        CHECK( 11 == linear.cosines().size() );
        CHECK( 11 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );
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
        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 10 == linear.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );
        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN

      THEN( "the cumulative integral has a value for every x value, including the extraneous "
            "point in the jump" ) {

        auto cumulative = chunk.cumulativeIntegral();
        REQUIRE( 6 == cumulative.size() );
        CHECK_THAT( 0.               , WithinRel( cumulative[0] ) );
        CHECK_THAT( 0.25             , WithinRel( cumulative[1] ) );
        CHECK_THAT( 0.25             , WithinRel( cumulative[2] ) ); // <-- extraneous point
        CHECK_THAT( 0.25             , WithinRel( cumulative[3] ) );
        CHECK_THAT( 0.810177514715569, WithinRel( cumulative[4] ) );
        CHECK_THAT( 1.49577938318395 , WithinRel( cumulative[5] ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and curate is requested" ) {

      std::vector< double > cosines = { -1., 0., 0., 0., 0.5, 1. }; // <-- jump of 3 x values
      std::vector< double > values = { 0., 0.5, 0.25, 1., 1.25, 1.5 };
      std::vector< std::size_t > boundaries = { 2, 5 }; // <-- pointing to middle of the jump
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LogLinear
      };

      TabulatedAngularDistributionFunction chunk( std::move( cosines ),
                                                  std::move( values ),
                                                  std::move( boundaries ),
                                                  std::move( interpolants ),
                                                  true );

      THEN( "a TabulatedAngularDistributionFunction can be constructed and members can be tested" ) {

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 1.5 , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );         // <-- this is changed from 2 to 1
        CHECK( 4 == chunk.boundaries()[1] );         // <-- this is changed from 5 to 4
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "calling curate() again on an already curated table does not change anything" ) {

        chunk.curate();

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 1.5 , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data with multiple jumps that consist of more than 2 points" ) {

    WHEN( "the data is given explicitly and curate is not requested" ) {

      std::vector< double > cosines = { -1., -0.5, -0.5, -0.5, 0., 0.5, 0.5, 0.5, 1. }; // <-- 2 jumps of 3 x values
      std::vector< double > values = { 1., 2., 3., 4., 5., 6., 7., 8., 9. };

      TabulatedAngularDistributionFunction chunk( std::move( cosines ), std::move( values ) );

      THEN( "a TabulatedAngularDistributionFunction can be constructed and members can be tested" ) {

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 9 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK( 9 == chunk.cosines().size() );
        CHECK( 9 == chunk.values().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[5] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[6] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[7] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[8] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[4] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[5] ) );
        CHECK_THAT( 7., WithinRel( chunk.values()[6] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[7] ) );
        CHECK_THAT( 9., WithinRel( chunk.values()[8] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 5 == chunk.boundaries()[1] );
        CHECK( 8 == chunk.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[2] );
        CHECK( true == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be evaluated and the extraneous points are ignored" ) {

        // note: in a jump, the table is evaluated using the last point of the jump
        CHECK_THAT( 1. , WithinRel( chunk( -1. ) ) );
        CHECK_THAT( 1.5, WithinRel( chunk( -0.75 ) ) );
        CHECK_THAT( 4. , WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( 4.5, WithinRel( chunk( -0.25 ) ) );
        CHECK_THAT( 5. , WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 8. , WithinRel( chunk( 0.5 ) ) );
        CHECK_THAT( 8.5, WithinRel( chunk( 0.75 ) ) );
        CHECK_THAT( 9. , WithinRel( chunk( 1. ) ) );
      } // THEN

      THEN( "arithmetic operations can be performed and the table remains uncurated" ) {

        TabulatedAngularDistributionFunction same( { -1., -0.5, -0.5, -0.5, 0., 0.5, 0.5, 0.5, 1. },
                                                   { 1., 1., 1., 1., 1., 1., 1., 1., 1. } );
        TabulatedAngularDistributionFunction different( { -1., 1. }, { 0., 4. } );

        chunk += 2.;

        CHECK( 9 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[5] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[6] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[7] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[8] ) );
        CHECK_THAT(  3., WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  4., WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  5., WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  6., WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  7., WithinRel( chunk.values()[4] ) );
        CHECK_THAT(  8., WithinRel( chunk.values()[5] ) );
        CHECK_THAT(  9., WithinRel( chunk.values()[6] ) );
        CHECK_THAT( 10., WithinRel( chunk.values()[7] ) );
        CHECK_THAT( 11., WithinRel( chunk.values()[8] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 5 == chunk.boundaries()[1] );
        CHECK( 8 == chunk.boundaries()[2] );
        CHECK( true == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );

        chunk -= same;

        CHECK( 9 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[5] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[6] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[7] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[8] ) );
        CHECK_THAT(  2., WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT(  5., WithinRel( chunk.values()[3] ) );
        CHECK_THAT(  6., WithinRel( chunk.values()[4] ) );
        CHECK_THAT(  7., WithinRel( chunk.values()[5] ) );
        CHECK_THAT(  8., WithinRel( chunk.values()[6] ) );
        CHECK_THAT(  9., WithinRel( chunk.values()[7] ) );
        CHECK_THAT( 10., WithinRel( chunk.values()[8] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 5 == chunk.boundaries()[1] );
        CHECK( 8 == chunk.boundaries()[2] );
        CHECK( true == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );

        chunk *= 2.;

        CHECK( 9 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[5] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[6] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[7] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[8] ) );
        CHECK_THAT(  4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT(  6., WithinRel( chunk.values()[1] ) );
        CHECK_THAT(  8., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 10., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 12., WithinRel( chunk.values()[4] ) );
        CHECK_THAT( 14., WithinRel( chunk.values()[5] ) );
        CHECK_THAT( 16., WithinRel( chunk.values()[6] ) );
        CHECK_THAT( 18., WithinRel( chunk.values()[7] ) );
        CHECK_THAT( 20., WithinRel( chunk.values()[8] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 5 == chunk.boundaries()[1] );
        CHECK( 8 == chunk.boundaries()[2] );
        CHECK( true == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );

        // note: the union grid keeps all points in the jumps of the uncurated table
        TabulatedAngularDistributionFunction result = chunk + different;

        CHECK_THAT( -1., WithinRel( result.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperCosineLimit() ) );
        CHECK( 9 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
        CHECK( 9 == result.cosines().size() );
        CHECK( 9 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( result.cosines()[0] ) );
        CHECK_THAT( -0.5, WithinRel( result.cosines()[1] ) );
        CHECK_THAT( -0.5, WithinRel( result.cosines()[2] ) );
        CHECK_THAT( -0.5, WithinRel( result.cosines()[3] ) );
        CHECK_THAT(  0. , WithinRel( result.cosines()[4] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[5] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[6] ) );
        CHECK_THAT(  0.5, WithinRel( result.cosines()[7] ) );
        CHECK_THAT(  1. , WithinRel( result.cosines()[8] ) );
        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
        CHECK_THAT(  7., WithinRel( result.values()[1] ) );
        CHECK_THAT(  9., WithinRel( result.values()[2] ) );
        CHECK_THAT( 11., WithinRel( result.values()[3] ) );
        CHECK_THAT( 14., WithinRel( result.values()[4] ) );
        CHECK_THAT( 17., WithinRel( result.values()[5] ) );
        CHECK_THAT( 19., WithinRel( result.values()[6] ) );
        CHECK_THAT( 21., WithinRel( result.values()[7] ) );
        CHECK_THAT( 24., WithinRel( result.values()[8] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 5 == result.boundaries()[1] );
        CHECK( 8 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );
        CHECK( true == result.isLinearised() );
        CHECK( false == result.isCurated() );
      } // THEN

      THEN( "the extraneous points are removed when calling curate()" ) {

        chunk.curate();

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 7 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK( 7 == chunk.cosines().size() );
        CHECK( 7 == chunk.values().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[5] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[6] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[4] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[5] ) );
        CHECK_THAT( 9., WithinRel( chunk.values()[6] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( 6 == chunk.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[2] );
        CHECK( true == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and curate is requested" ) {

      std::vector< double > cosines = { -1., -0.5, -0.5, -0.5, 0., 0.5, 0.5, 0.5, 1. }; // <-- 2 jumps of 3 x values
      std::vector< double > values = { 1., 2., 3., 4., 5., 6., 7., 8., 9. };

      TabulatedAngularDistributionFunction chunk( std::move( cosines ), std::move( values ),
                                                  InterpolationType::LinearLinear, true );

      THEN( "a TabulatedAngularDistributionFunction can be constructed and members can be tested" ) {

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 7 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK( 7 == chunk.cosines().size() );
        CHECK( 7 == chunk.values().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT( -0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[5] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[6] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[4] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[5] ) );
        CHECK_THAT( 9., WithinRel( chunk.values()[6] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( 6 == chunk.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[2] );
        CHECK( true == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data with a jump that consist of more than 2 points" ) {

    WHEN( "the data is given explicitly and curate is not requested" ) {

      std::vector< double > cosines = { -1., 0., 0., 0., 1. }; // <-- jump of 3 x values
      std::vector< double > values = { 1., 2., 5., 3., 4. };

      TabulatedAngularDistributionFunction chunk( std::move( cosines ), std::move( values ) );

      THEN( "linearise() removes the extraneous point in the jump" ) {

        CHECK( true == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK_THAT( -1., WithinRel( linear.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( linear.upperCosineLimit() ) );
        CHECK( 4 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );
        CHECK( 4 == linear.cosines().size() );
        CHECK( 4 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );
        CHECK_THAT( -1., WithinRel( linear.cosines()[0] ) );
        CHECK_THAT(  0., WithinRel( linear.cosines()[1] ) );
        CHECK_THAT(  0., WithinRel( linear.cosines()[2] ) );
        CHECK_THAT(  1., WithinRel( linear.cosines()[3] ) );
        CHECK_THAT( 1., WithinRel( linear.values()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.values()[1] ) );
        CHECK_THAT( 3., WithinRel( linear.values()[2] ) );
        CHECK_THAT( 4., WithinRel( linear.values()[3] ) );
        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 3 == linear.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );
        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN

      THEN( "the cumulative integral has a value for every x value, including the extraneous "
            "point in the jump" ) {

        // region 1: ( 1 + 2 ) / 2 = 1.5
        // region 2: ( 3 + 4 ) / 2 = 3.5
        auto cumulative = chunk.cumulativeIntegral();
        REQUIRE( 5 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[2] ) ); // <-- extraneous point
        CHECK_THAT( 1.5, WithinRel( cumulative[3] ) );
        CHECK_THAT( 5. , WithinRel( cumulative[4] ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and the first and second y value in the jump are "
          "the same" ) {

      std::vector< double > cosines = { -1., 0., 0., 0., 1. }; // <-- jump of 3 x values
      std::vector< double > values = { 1., 2., 2., 3., 4. }; // <-- extraneous point has same y

      TabulatedAngularDistributionFunction chunk( std::move( cosines ), std::move( values ) );

      THEN( "linearise() removes the extraneous point in the jump and keeps the jump" ) {

        CHECK( true == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );

        TabulatedAngularDistributionFunction linear = chunk.linearise();

        CHECK_THAT( -1., WithinRel( linear.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( linear.upperCosineLimit() ) );
        CHECK( 4 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );
        CHECK( 4 == linear.cosines().size() );
        CHECK( 4 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );
        CHECK_THAT( -1., WithinRel( linear.cosines()[0] ) );
        CHECK_THAT(  0., WithinRel( linear.cosines()[1] ) );
        CHECK_THAT(  0., WithinRel( linear.cosines()[2] ) );
        CHECK_THAT(  1., WithinRel( linear.cosines()[3] ) );
        CHECK_THAT( 1., WithinRel( linear.values()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.values()[1] ) );
        CHECK_THAT( 3., WithinRel( linear.values()[2] ) );
        CHECK_THAT( 4., WithinRel( linear.values()[3] ) );
        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 3 == linear.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );
        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );

        CHECK_THAT( 1.5, WithinRel( linear( -0.5 ) ) );
        CHECK_THAT( 3.5, WithinRel( linear( 0.5 ) ) );
      } // THEN

      THEN( "the cumulative integral has a value for every x value, including the extraneous "
            "point in the jump" ) {

        // region 1: ( 1 + 2 ) / 2 = 1.5
        // region 2: ( 3 + 4 ) / 2 = 3.5
        auto cumulative = chunk.cumulativeIntegral();
        REQUIRE( 5 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[2] ) ); // <-- extraneous point
        CHECK_THAT( 1.5, WithinRel( cumulative[3] ) );
        CHECK_THAT( 5. , WithinRel( cumulative[4] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data with a jump where both y values in the jump are the same" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > cosines = { -1., 0., 0., 1. };
      std::vector< double > values = { 1., 2., 2., 3. }; // <-- same y values in the jump

      TabulatedAngularDistributionFunction chunk( std::move( cosines ), std::move( values ) );

      THEN( "a TabulatedAngularDistributionFunction can be constructed and members can be tested" ) {

        CHECK_THAT( -1., WithinRel( chunk.lowerCosineLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperCosineLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.cosines().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1., WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0., WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0., WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1., WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "a TabulatedAngularDistributionFunction can be integrated" ) {

        // ( 1 + 2 ) / 2 + ( 2 + 3 ) / 2 = 4
        CHECK_THAT( 4., WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral has a value for every x value" ) {

        auto cumulative = chunk.cumulativeIntegral();
        REQUIRE( 4 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[2] ) );
        CHECK_THAT( 4. , WithinRel( cumulative[3] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump and boundaries "
         "that point to the second x value in the jump" ) {

    // note: at construction time, the boundary value will be set to the first point in
    //       the jump. As a result, the final data contained in this TabulatedAngularDistributionFunction is the
    //       same as the "non-linearised data with multiple regions with a jump" test.

    WHEN( "the data is given explicitly" ) {

      std::vector< double > cosines = { -1., 0., 0., 0.5, 1. };
      std::vector< double > values = { 0., 0.5, 1., 1.25, 1.5 };
      std::vector< std::size_t > boundaries = { 2, 4 }; // <-- pointing to end of the jump
      std::vector< InterpolationType > interpolants = {

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
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.cosines().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[4] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.25, WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 1.5 , WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );           // <-- this is changed from 2 to 1
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump at the end" ) {

    // note: at construction time, all but the first point of the jump will be removed and
    //       the last boundary value will point to the first point of the jump.

    WHEN( "the data is given explicitly and the jump consists of 2 points" ) {

      std::vector< double > cosines = { -1., 0., 0.5, 1., 1. }; // <-- jump at end
      std::vector< double > values = { 0., 0.5, 0.75, 1., 2. };
      std::vector< std::size_t > boundaries = { 1, 4 }; // <-- pointing to end
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LogLinear
      };

      TabulatedAngularDistributionFunction chunk( std::move( cosines ), std::move( values ),
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
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[3] ) ); // <-- last point removed
        CHECK_THAT( 0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.values()[3] ) ); // <-- last point removed
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and the jump consists of more than 2 points" ) {

      std::vector< double > cosines = { -1., 0., 0.5, 1., 1., 1. }; // <-- jump of 3 x values at end
      std::vector< double > values = { 0., 0.5, 0.75, 1., 2., 2.5 };
      std::vector< std::size_t > boundaries = { 1, 5 }; // <-- pointing to end
      std::vector< InterpolationType > interpolants = {

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
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) );
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[3] ) ); // <-- last two points removed
        CHECK_THAT( 0.  , WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.values()[3] ) ); // <-- last two points removed
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump at the beginning" ) {

    // note: at construction time, all but the last point of the jump will be removed and
    //       all boundary values will be decremented by the number of points removed.

    WHEN( "the data is given explicitly and the jump consists of 2 points" ) {

      std::vector< double > cosines = { -1., -1., 0., 0.5, 1. }; // <-- jump at beginning
      std::vector< double > values = { 1., 0., 0.5, 0.75, 1. };
      std::vector< std::size_t > boundaries = { 2, 4 };
      std::vector< InterpolationType > interpolants = {

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
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) ); // <-- first point removed
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.values()[0] ) ); // <-- first point removed
        CHECK_THAT( 0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );         // <-- boundary value reset
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and the jump consists of more than 2 points" ) {

      std::vector< double > cosines = { -1., -1., -1., 0., 0.5, 1. }; // <-- jump of 3 x values at beginning
      std::vector< double > values = { 1., 2., 0., 0.5, 0.75, 1. };
      std::vector< std::size_t > boundaries = { 3, 5 };
      std::vector< InterpolationType > interpolants = {

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
        CHECK_THAT( -1. , WithinRel( chunk.cosines()[0] ) ); // <-- first two points removed
        CHECK_THAT(  0. , WithinRel( chunk.cosines()[1] ) );
        CHECK_THAT(  0.5, WithinRel( chunk.cosines()[2] ) );
        CHECK_THAT(  1. , WithinRel( chunk.cosines()[3] ) );
        CHECK_THAT( 0.  , WithinRel( chunk.values()[0] ) ); // <-- first two points removed
        CHECK_THAT( 0.5 , WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 0.75, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.  , WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );         // <-- boundary value reset
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LogLinear == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of TabulatedAngularDistributionFunction are given" ) {

      TabulatedAngularDistributionFunction left( { -1., 0., 1. }, { 1., 2., 3. } );
      TabulatedAngularDistributionFunction equal( { -1., 0., 1. }, { 1., 2., 3. } );
      TabulatedAngularDistributionFunction different1( { -1., 0., 1. }, { 1., 0., 3. } );
      TabulatedAngularDistributionFunction different2( { -1., 0., 1. }, { 1., 2., 3. }, InterpolationType::LogLog );
      TabulatedAngularDistributionFunction different3( { -1., 0., 1. }, { 1., 2., 3. },
                                                       { 1, 2 },
                                                       { InterpolationType::LinearLinear, InterpolationType::LogLog } );
      TabulatedAngularDistributionFunction different4( { -1., 0.5, 1. }, { 1., 2., 3. } );
      TabulatedAngularDistributionFunction uncurated( { -1., 0., 0., 0., 1. }, { 1., 2., 3., 4., 5. } );
      TabulatedAngularDistributionFunction curated( { -1., 0., 0., 0., 1. }, { 1., 2., 3., 4., 5. },
                                                    InterpolationType::LinearLinear, true );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different1 ) );
        CHECK( false == ( left == different2 ) );
        CHECK( false == ( left == different3 ) );
        CHECK( false == ( left == different4 ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different1 ) );
        CHECK( true == ( left != different2 ) );
        CHECK( true == ( left != different3 ) );
        CHECK( true == ( left != different4 ) );

        CHECK( false == uncurated.isCurated() );
        CHECK( true == curated.isCurated() );

        CHECK( false == ( uncurated == curated ) );
        CHECK( true == ( uncurated != curated ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a TabulatedAngularDistributionFunction object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( empty, empty ) );
        CHECK_THROWS( TabulatedAngularDistributionFunction( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > cosines = { -1., 0., 0.5, 1. };
      std::vector< double > values = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( cosines ), std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      std::vector< double > cosines = { -1., 0., 0.5, 1. };
      std::vector< double > values = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( cosines ),
                                                            std::move( values ),
                                                            std::move( boundaries ),
                                                            std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > cosines = { -1., 0.5, 0., 1. };
      std::vector< double > values = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( cosines ), std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      std::vector< double > cosines = { -1., 0., 1., 1. };
      std::vector< double > values = { 4., 3., 1., 4. };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( cosines ),
                                                            std::move( values ),
                                                            std::move( boundaries ),
                                                            std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are not sorted" ) {

      std::vector< double > cosines = { -1., 0., 0.5, 1. };
      std::vector< double > values = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 2, 1, 3 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLinear,
        InterpolationType::LinearLinear
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( cosines ),
                                                            std::move( values ),
                                                            std::move( boundaries ),
                                                            std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are not unique" ) {

      std::vector< double > cosines = { -1., 0., 0.5, 1. };
      std::vector< double > values = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 1, 1, 3 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLinear,
        InterpolationType::LinearLinear
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( cosines ),
                                                            std::move( values ),
                                                            std::move( boundaries ),
                                                            std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "there are no boundaries and interpolants" ) {

      std::vector< double > cosines = { -1., 0., 0.5, 1. };
      std::vector< double > values = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = {};
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedAngularDistributionFunction( std::move( cosines ),
                                                            std::move( values ),
                                                            std::move( boundaries ),
                                                            std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
