// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/TabulatedComptonProfileFunction.hpp"

// other includes

// includes for test result generation
// #include <iostream>
// #include <iomanip>
// #include "scion/integration/GaussLegendre/64.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "TabulatedComptonProfileFunction" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > momentum = { 1., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 2., 1. };

      TabulatedComptonProfileFunction chunk( std::move( momentum ), std::move( values ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be copy and move constructed" ) {

        TabulatedComptonProfileFunction copy( chunk );

        CHECK_THAT( 1., WithinRel( copy.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( copy.upperMomentumLimit() ) );
        CHECK( 4 == copy.numberPoints() );
        CHECK( 1 == copy.numberRegions() );
        CHECK( 4 == copy.momentum().size() );
        CHECK( 4 == copy.values().size() );
        CHECK( 1 == copy.boundaries().size() );
        CHECK( 1 == copy.interpolants().size() );
        CHECK_THAT( 1., WithinRel( copy.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( copy.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( copy.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( copy.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( copy.values()[0] ) );
        CHECK_THAT( 3., WithinRel( copy.values()[1] ) );
        CHECK_THAT( 2., WithinRel( copy.values()[2] ) );
        CHECK_THAT( 1., WithinRel( copy.values()[3] ) );
        CHECK( 3 == copy.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == copy.interpolants()[0] );
        CHECK( true == copy.isLinearised() );
        CHECK( true == copy.isCurated() );

        TabulatedComptonProfileFunction move( std::move( copy ) );

        CHECK_THAT( 1., WithinRel( move.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( move.upperMomentumLimit() ) );
        CHECK( 4 == move.numberPoints() );
        CHECK( 1 == move.numberRegions() );
        CHECK( 4 == move.momentum().size() );
        CHECK( 4 == move.values().size() );
        CHECK( 1 == move.boundaries().size() );
        CHECK( 1 == move.interpolants().size() );
        CHECK_THAT( 1., WithinRel( move.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( move.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( move.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( move.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( move.values()[0] ) );
        CHECK_THAT( 3., WithinRel( move.values()[1] ) );
        CHECK_THAT( 2., WithinRel( move.values()[2] ) );
        CHECK_THAT( 1., WithinRel( move.values()[3] ) );
        CHECK( 3 == move.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == move.interpolants()[0] );
        CHECK( true == move.isLinearised() );
        CHECK( true == move.isCurated() );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be copy and move assigned" ) {

        TabulatedComptonProfileFunction copy( { 1., 4. }, { 0., 0. } );
        copy = chunk;

        CHECK_THAT( 1., WithinRel( copy.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( copy.upperMomentumLimit() ) );
        CHECK( 4 == copy.numberPoints() );
        CHECK( 1 == copy.numberRegions() );
        CHECK( 4 == copy.momentum().size() );
        CHECK( 4 == copy.values().size() );
        CHECK( 1 == copy.boundaries().size() );
        CHECK( 1 == copy.interpolants().size() );
        CHECK_THAT( 1., WithinRel( copy.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( copy.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( copy.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( copy.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( copy.values()[0] ) );
        CHECK_THAT( 3., WithinRel( copy.values()[1] ) );
        CHECK_THAT( 2., WithinRel( copy.values()[2] ) );
        CHECK_THAT( 1., WithinRel( copy.values()[3] ) );
        CHECK( 3 == copy.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == copy.interpolants()[0] );
        CHECK( true == copy.isLinearised() );
        CHECK( true == copy.isCurated() );

        TabulatedComptonProfileFunction move( { 1., 4. }, { 0., 0. } );
        move = std::move( copy );

        CHECK_THAT( 1., WithinRel( move.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( move.upperMomentumLimit() ) );
        CHECK( 4 == move.numberPoints() );
        CHECK( 1 == move.numberRegions() );
        CHECK( 4 == move.momentum().size() );
        CHECK( 4 == move.values().size() );
        CHECK( 1 == move.boundaries().size() );
        CHECK( 1 == move.interpolants().size() );
        CHECK_THAT( 1., WithinRel( move.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( move.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( move.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( move.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( move.values()[0] ) );
        CHECK_THAT( 3., WithinRel( move.values()[1] ) );
        CHECK_THAT( 2., WithinRel( move.values()[2] ) );
        CHECK_THAT( 1., WithinRel( move.values()[3] ) );
        CHECK( 3 == move.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == move.interpolants()[0] );
        CHECK( true == move.isLinearised() );
        CHECK( true == move.isCurated() );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be evaluated" ) {

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

      THEN( "a TabulatedComptonProfileFunction can be integrated" ) {

        // ( 4 + 1 ) * 3 / 2 = 7.5
        CHECK_THAT( 7.5, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of a TabulatedComptonProfileFunction can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 6. , WithinRel( cumulative[2] ) );
        CHECK_THAT( 7.5, WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the mean of a TabulatedComptonProfileFunction can be calculated" ) {

        // f(x) = 5 - x
        // x f(x) = 5 x - x^2
        // primitive = 5 x^2 / 2 - x^3 / 3
        // integral = 5 * 16 / 2 - 64 / 3 - 5 / 2 + 1 / 3
        //          = 75 / 2 -  63 / 3 = 37.5 - 21
        CHECK_THAT( 16.5 / 7.5, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        TabulatedComptonProfileFunction result( { 1., 4. }, { 0., 0. } );
        TabulatedComptonProfileFunction same( { 1., 4. }, { 0., 3. } );
        TabulatedComptonProfileFunction threshold( { 2., 4. }, { 0., 2. } );
        TabulatedComptonProfileFunction nonzerothreshold( { 2., 4. }, { 1., 3. } );
        TabulatedComptonProfileFunction small( { 1., 3. }, { 0., 2. } );

        chunk += 2.;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 5., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= 2.;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk *= 2.;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk /= 2.;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = -chunk;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT(  3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT(  4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( -4., WithinRel( result.values()[0] ) );
        CHECK_THAT( -3., WithinRel( result.values()[1] ) );
        CHECK_THAT( -2., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk + 2.;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 3., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = 2. + chunk;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 3., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk - 2.;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT(  3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT(  4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT(  2., WithinRel( result.values()[0] ) );
        CHECK_THAT(  1., WithinRel( result.values()[1] ) );
        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = 2. - chunk;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT(  3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT(  4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( -2., WithinRel( result.values()[0] ) );
        CHECK_THAT( -1., WithinRel( result.values()[1] ) );
        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
        CHECK_THAT(  1., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk * 2.;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = 2. * chunk;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk / 2.;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.values()[1] ) );
        CHECK_THAT( 1.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 0.5, WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        chunk += same;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= same;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = chunk + same;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[1] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk - same;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.momentum()[3] ) );
        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
        CHECK_THAT(  2., WithinRel( result.values()[1] ) );
        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
        CHECK_THAT( -2., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        chunk += threshold;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        chunk -= threshold;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = chunk + threshold;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( result.values()[1] ) );
        CHECK_THAT( 3.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 3.0, WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        result = chunk - threshold;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.momentum()[3] ) );
        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
        CHECK_THAT(  3., WithinRel( result.values()[1] ) );
        CHECK_THAT(  1., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );

        chunk += nonzerothreshold;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2.0, WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1.0, WithinRel( chunk.values()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        result = chunk + nonzerothreshold;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT(  3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT(  4., WithinRel( result.momentum()[4] ) );
        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
        CHECK_THAT(  3., WithinRel( result.values()[1] ) );
        CHECK_THAT(  2., WithinRel( result.values()[2] ) );
        CHECK_THAT(  0., WithinRel( result.values()[3] ) );
        CHECK_THAT( -2., WithinRel( result.values()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        // this will add a second point at the upper end point of small
        result = chunk + small;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4. , WithinRel( result.momentum()[4] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[1] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[3] ) );
        CHECK_THAT( 1.0, WithinRel( result.values()[4] ) );
        CHECK( 2 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );

        // this will add a second point at the upper end point of small
        result = chunk - small;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4. , WithinRel( result.momentum()[4] ) );
        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[1] ) );
        CHECK_THAT( 0.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[3] ) );
        CHECK_THAT( 1.0, WithinRel( result.values()[4] ) );
        CHECK( 2 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be linearised" ) {

        TabulatedComptonProfileFunction linear = chunk.linearise();

        CHECK_THAT( 1., WithinRel( linear.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( linear.upperMomentumLimit() ) );
        CHECK( 4 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 4 == linear.momentum().size() );
        CHECK( 4 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 3 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( 1., WithinRel( linear.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( linear.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( linear.momentum()[3] ) );

        CHECK_THAT( 4., WithinRel( linear.values()[0] ) );
        CHECK_THAT( 3., WithinRel( linear.values()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.values()[2] ) );
        CHECK_THAT( 1., WithinRel( linear.values()[3] ) );

        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data without boundaries and a jump" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > momentum = { 1., 2., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 4., 3., 2. };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      TabulatedComptonProfileFunction chunk( std::move( momentum ),
                                             std::move( values ),
                                             interpolant );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        // the constructor will detect the jump and add interpolation regions
        // as required
        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be evaluated" ) {

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

      THEN( "a TabulatedComptonProfileFunction can be integrated" ) {

        // ( 4 + 3 ) / 2 + ( 4 + 2 ) * 2 / 2 = 9.5
        CHECK_THAT( 9.5, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of a TabulatedComptonProfileFunction can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 5 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 3.5, WithinRel( cumulative[2] ) );
        CHECK_THAT( 7. , WithinRel( cumulative[3] ) );
        CHECK_THAT( 9.5, WithinRel( cumulative[4] ) );
      } // THEN

      THEN( "the mean of a TabulatedComptonProfileFunction can be calculated" ) {

        // region 1
        // f(x) = 5 - x
        // x f(x) = 5 x - x^2
        // primitive = 5 x^2 / 2 - x^3 / 3
        // integral = 5 * 4 / 2 - 8 / 3 - 5 / 2 + 1 / 3
        //          = 7.5 - 7 / 3
        // region 2
        // f(x) = 6 - x
        // x f(x) = 6 x - x^2
        // primitive = 3 x^2 - x^3 / 3
        // integral = 48 - 64 / 3 - 12 + 2 / 3
        //          = 36 - 62 / 3
        // sum = 43.5 - 69 / 3 = 22.5
        CHECK_THAT( 22.5 / 9.5, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be linearised" ) {

        TabulatedComptonProfileFunction linear = chunk.linearise();

        CHECK_THAT( 1., WithinRel( linear.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( linear.upperMomentumLimit() ) );
        CHECK( 5 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 5 == linear.momentum().size() );
        CHECK( 5 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );

        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 4 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( 1., WithinRel( linear.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( linear.momentum()[4] ) );

        CHECK_THAT( 4., WithinRel( linear.values()[0] ) );
        CHECK_THAT( 3., WithinRel( linear.values()[1] ) );
        CHECK_THAT( 4., WithinRel( linear.values()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.values()[3] ) );
        CHECK_THAT( 2., WithinRel( linear.values()[4] ) );

        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        TabulatedComptonProfileFunction result( { 1., 4. }, { 0., 0. } );
        TabulatedComptonProfileFunction same( { 1., 4. }, { 0., 3. } );
        TabulatedComptonProfileFunction threshold( { 2., 4. }, { 0., 2. } );
        TabulatedComptonProfileFunction nonzerothreshold( { 3., 4. }, { 1., 2. } );
        TabulatedComptonProfileFunction small( { 1., 3. }, { 0., 2. } );

        chunk += 2.;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT(  3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT(  4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT(  3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT(  4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4. , WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 6 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK( 6 == chunk.momentum().size() );
        CHECK( 6 == chunk.values().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[5] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 6 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
        CHECK( 6 == result.momentum().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[5] ) );
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

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 6 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
        CHECK( 6 == result.momentum().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[5] ) );
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

        // this will add a second point at the upper end point of small
        result = chunk + small;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 6 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
        CHECK( 6 == result.momentum().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[5] ) );
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

        // this will add a second point at the upper end point of small
        result = chunk - small;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 6 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
        CHECK( 6 == result.momentum().size() );
        CHECK( 6 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[5] ) );
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
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions without a jump" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > momentum = { 1., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 1, 3 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedComptonProfileFunction chunk( std::move( momentum ),
                                             std::move( values ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be evaluated" ) {

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

      THEN( "a TabulatedComptonProfileFunction can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        CHECK_THAT( 7.44236295915864, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of a TabulatedComptonProfileFunction can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0.              , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5             , WithinRel( cumulative[1] ) );
        CHECK_THAT( 5.96630346237643, WithinRel( cumulative[2] ) );
        CHECK_THAT( 7.44236295915864, WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the mean of a TabulatedComptonProfileFunction can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, 1.,  2. )
        //                                     + integrator( functor, 2.,  3. )
        //                                     + integrator( functor, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 16.332650114006 / 7.44236295915864, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be linearised" ) {

        TabulatedComptonProfileFunction linear = chunk.linearise();

        CHECK_THAT( 1., WithinRel( linear.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( linear.upperMomentumLimit() ) );
        CHECK( 18 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 18 == linear.momentum().size() );
        CHECK( 18 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 17 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( 1.   , WithinRel( linear.momentum()[0] ) );
        CHECK_THAT( 2.   , WithinRel( linear.momentum()[1] ) );
        CHECK_THAT( 2.125, WithinRel( linear.momentum()[2] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.momentum()[3] ) );
        CHECK_THAT( 2.375, WithinRel( linear.momentum()[4] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.momentum()[5] ) );
        CHECK_THAT( 2.625, WithinRel( linear.momentum()[6] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.momentum()[7] ) );
        CHECK_THAT( 2.875, WithinRel( linear.momentum()[8] ) );
        CHECK_THAT( 3.   , WithinRel( linear.momentum()[9] ) );
        CHECK_THAT( 3.125, WithinRel( linear.momentum()[10] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.momentum()[11] ) );
        CHECK_THAT( 3.375, WithinRel( linear.momentum()[12] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.momentum()[13] ) );
        CHECK_THAT( 3.625, WithinRel( linear.momentum()[14] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.momentum()[15] ) );
        CHECK_THAT( 3.875, WithinRel( linear.momentum()[16] ) );
        CHECK_THAT( 4.   , WithinRel( linear.momentum()[17] ) );

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
        CHECK( true == linear.isCurated() );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        TabulatedComptonProfileFunction result( { 1., 4. }, { 0., 0. } );

        chunk *= 2.;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 8., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );

        chunk /= 2.;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );

        result = -chunk;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT(  2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT(  3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT(  4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( -4., WithinRel( result.values()[0] ) );
        CHECK_THAT( -3., WithinRel( result.values()[1] ) );
        CHECK_THAT( -2., WithinRel( result.values()[2] ) );
        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
        CHECK( true == result.isCurated() );

        result = chunk * 2.;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
        CHECK( true == result.isCurated() );

        result = 2. * chunk;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
        CHECK( true == result.isCurated() );

        result = chunk / 2.;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.momentum().size() );
        CHECK( 4 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 2.0, WithinRel( result.values()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.values()[1] ) );
        CHECK_THAT( 1.0, WithinRel( result.values()[2] ) );
        CHECK_THAT( 0.5, WithinRel( result.values()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
        CHECK( true == result.isCurated() );
      } // THEN

      THEN( "some arithmetic operations cannot be performed" ) {

        TabulatedComptonProfileFunction result( { 1., 4. }, { 0., 0. } );
        TabulatedComptonProfileFunction right( { 1., 4. }, { 0., 0. } );

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
        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > momentum = { 1., 2., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 4., 3., 2. };
      std::vector< std::size_t > boundaries = { 1, 4 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedComptonProfileFunction chunk( std::move( momentum ),
                                             std::move( values ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be evaluated" ) {

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

      THEN( "a TabulatedComptonProfileFunction can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        CHECK_THAT( 9.44236295915864, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of a TabulatedComptonProfileFunction can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 5 == cumulative.size() );
        CHECK_THAT( 0.              , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5             , WithinRel( cumulative[1] ) );
        CHECK_THAT( 3.5             , WithinRel( cumulative[2] ) );
        CHECK_THAT( 6.96630346237643, WithinRel( cumulative[3] ) );
        CHECK_THAT( 9.44236295915864, WithinRel( cumulative[4] ) );
      } // THEN

      THEN( "the mean of a TabulatedComptonProfileFunction can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, 1.,  2. )
        //                                     + integrator( functor, 2.,  3. )
        //                                     + integrator( functor, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 22.332650114006 / 9.44236295915864, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a TabulatedComptonProfileFunction can be linearised" ) {

        TabulatedComptonProfileFunction linear = chunk.linearise();

        CHECK_THAT( 1., WithinRel( linear.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( linear.upperMomentumLimit() ) );
        CHECK( 12 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 12 == linear.momentum().size() );
        CHECK( 12 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );

        CHECK(  1 == linear.boundaries()[0] );
        CHECK( 11 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( 1.   , WithinRel( linear.momentum()[0] ) );
        CHECK_THAT( 2.   , WithinRel( linear.momentum()[1] ) );
        CHECK_THAT( 2.   , WithinRel( linear.momentum()[2] ) );
        CHECK_THAT( 2.125, WithinRel( linear.momentum()[3] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.momentum()[4] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.momentum()[5] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.momentum()[6] ) );
        CHECK_THAT( 3.   , WithinRel( linear.momentum()[7] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.momentum()[8] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.momentum()[9] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.momentum()[10] ) );
        CHECK_THAT( 4.   , WithinRel( linear.momentum()[11] ) );

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
        CHECK( true == linear.isCurated() );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        TabulatedComptonProfileFunction result( { 1., 4. }, { 0., 0. } );

        chunk *= 2.;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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
        CHECK( true == chunk.isCurated() );

        chunk /= 2.;

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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
        CHECK( true == chunk.isCurated() );

        result = -chunk;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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
        CHECK( true == result.isCurated() );

        result = chunk * 2.;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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
        CHECK( true == result.isCurated() );

        result = 2. * chunk;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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
        CHECK( true == result.isCurated() );

        result = chunk / 2.;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.momentum().size() );
        CHECK( 5 == result.values().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[4] ) );
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
        CHECK( true == result.isCurated() );
      } // THEN

      THEN( "some arithmetic operations cannot be performed" ) {

        TabulatedComptonProfileFunction result( { 1., 4. }, { 0., 0. } );
        TabulatedComptonProfileFunction right( { 1., 4. }, { 0., 0. } );

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
        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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

      std::vector< double > momentum = { 1., 2., 2., 2., 3., 4. }; // <-- jump of 3 x values
      std::vector< double > values = { 4., 3., 2., 4., 3., 2. };
      std::vector< std::size_t > boundaries = { 2, 5 }; // <-- pointing to middle of the jump
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedComptonProfileFunction chunk( std::move( momentum ),
                                             std::move( values ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 6 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 6 == chunk.momentum().size() );
        CHECK( 6 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[5] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[4] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[5] ) );
        CHECK( 1 == chunk.boundaries()[0] );         // <-- this is changed from 2 to 1
        CHECK( 5 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );
      } // THEN

      THEN( "the table can be curated on demand and the extraneous points are removed" ) {

        // note: curate() curates the table in place - it does not return a new instance
        chunk.curate();

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "the table can be linearised and the extraneous point in the jump is removed" ) {

        TabulatedComptonProfileFunction linear = chunk.linearise();

        CHECK_THAT( 1., WithinRel( linear.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( linear.upperMomentumLimit() ) );
        CHECK( 12 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );
        CHECK( 12 == linear.momentum().size() );
        CHECK( 12 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );
        CHECK_THAT( 1.   , WithinRel( linear.momentum()[0] ) );
        CHECK_THAT( 2.   , WithinRel( linear.momentum()[1] ) );
        CHECK_THAT( 2.   , WithinRel( linear.momentum()[2] ) );
        CHECK_THAT( 2.125, WithinRel( linear.momentum()[3] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.momentum()[4] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.momentum()[5] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.momentum()[6] ) );
        CHECK_THAT( 3.   , WithinRel( linear.momentum()[7] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.momentum()[8] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.momentum()[9] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.momentum()[10] ) );
        CHECK_THAT( 4.   , WithinRel( linear.momentum()[11] ) );
        CHECK_THAT( 4.                 , WithinRel( linear.values()[0] ) );
        CHECK_THAT( 3.                 , WithinRel( linear.values()[1] ) );
        CHECK_THAT( 4.                 , WithinRel( linear.values()[2] ) );
        CHECK_THAT( 3.8504812853088648 , WithinRel( linear.values()[3] ) );
        CHECK_THAT( 3.709511291351455  , WithinRel( linear.values()[4] ) );
        CHECK_THAT( 3.4496602867867914 , WithinRel( linear.values()[5] ) );
        CHECK_THAT( 3.2145964603356649 , WithinRel( linear.values()[6] ) );
        CHECK_THAT( 3.                 , WithinRel( linear.values()[7] ) );
        CHECK_THAT( 2.7217667858432417 , WithinRel( linear.values()[8] ) );
        CHECK_THAT( 2.4641630654510251 , WithinRel( linear.values()[9] ) );
        CHECK_THAT( 2.2243397393085331 , WithinRel( linear.values()[10] ) );
        CHECK_THAT( 2.                 , WithinRel( linear.values()[11] ) );
        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 11 == linear.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );
        CHECK( true == linear.isLinearised() );
        CHECK( true == linear.isCurated() );
      } // THEN

      THEN( "the cumulative integral has a value for every x value, including the extraneous "
            "point in the jump" ) {

        auto cumulative = chunk.cumulativeIntegral();
        REQUIRE( 6 == cumulative.size() );
        CHECK_THAT( 0.              , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5             , WithinRel( cumulative[1] ) );
        CHECK_THAT( 3.5             , WithinRel( cumulative[2] ) ); // <-- extraneous point
        CHECK_THAT( 3.5             , WithinRel( cumulative[3] ) );
        CHECK_THAT( 6.96630346237643, WithinRel( cumulative[4] ) );
        CHECK_THAT( 9.44236295915864, WithinRel( cumulative[5] ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and curate is requested" ) {

      std::vector< double > momentum = { 1., 2., 2., 2., 3., 4. }; // <-- jump of 3 x values
      std::vector< double > values = { 4., 3., 2., 4., 3., 2. };
      std::vector< std::size_t > boundaries = { 2, 5 }; // <-- pointing to middle of the jump
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedComptonProfileFunction chunk( std::move( momentum ),
                                             std::move( values ),
                                             std::move( boundaries ),
                                             std::move( interpolants ),
                                             true );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );         // <-- this is changed from 2 to 1
        CHECK( 4 == chunk.boundaries()[1] );         // <-- this is changed from 5 to 4
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN

      THEN( "calling curate() again on an already curated table does not change anything" ) {

        chunk.curate();

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data with multiple jumps that consist of more than 2 points" ) {

    WHEN( "the data is given explicitly and curate is not requested" ) {

      std::vector< double > momentum = { 1., 2., 2., 2., 3., 4., 4., 4., 5. }; // <-- 2 jumps of 3 x values
      std::vector< double > values = { 1., 2., 3., 4., 5., 6., 7., 8., 9. };

      TabulatedComptonProfileFunction chunk( std::move( momentum ), std::move( values ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 5., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 9 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK( 9 == chunk.momentum().size() );
        CHECK( 9 == chunk.values().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[5] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[6] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[7] ) );
        CHECK_THAT( 5., WithinRel( chunk.momentum()[8] ) );
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

      THEN( "a TabulatedComptonProfileFunction can be evaluated and the extraneous points are ignored" ) {

        // note: in a jump, the table is evaluated using the last point of the jump
        CHECK_THAT( 1. , WithinRel( chunk( 1.  ) ) );
        CHECK_THAT( 1.5, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 4. , WithinRel( chunk( 2.  ) ) );
        CHECK_THAT( 4.5, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 5. , WithinRel( chunk( 3.  ) ) );
        CHECK_THAT( 8. , WithinRel( chunk( 4.  ) ) );
        CHECK_THAT( 8.5, WithinRel( chunk( 4.5 ) ) );
        CHECK_THAT( 9. , WithinRel( chunk( 5.  ) ) );
      } // THEN

      THEN( "arithmetic operations can be performed and the table remains uncurated" ) {

        TabulatedComptonProfileFunction same( { 1., 2., 2., 2., 3., 4., 4., 4., 5. },
                                              { 1., 1., 1., 1., 1., 1., 1., 1., 1. } );
        TabulatedComptonProfileFunction different( { 1., 5. }, { 0., 4. } );

        chunk += 2.;

        CHECK( 9 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[5] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[6] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[7] ) );
        CHECK_THAT( 5., WithinRel( chunk.momentum()[8] ) );
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
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[5] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[6] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[7] ) );
        CHECK_THAT( 5., WithinRel( chunk.momentum()[8] ) );
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
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[5] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[6] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[7] ) );
        CHECK_THAT( 5., WithinRel( chunk.momentum()[8] ) );
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
        TabulatedComptonProfileFunction result = chunk + different;

        CHECK_THAT( 1., WithinRel( result.lowerMomentumLimit() ) );
        CHECK_THAT( 5., WithinRel( result.upperMomentumLimit() ) );
        CHECK( 9 == result.numberPoints() );
        CHECK( 3 == result.numberRegions() );
        CHECK( 9 == result.momentum().size() );
        CHECK( 9 == result.values().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[2] ) );
        CHECK_THAT( 2., WithinRel( result.momentum()[3] ) );
        CHECK_THAT( 3., WithinRel( result.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[5] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[6] ) );
        CHECK_THAT( 4., WithinRel( result.momentum()[7] ) );
        CHECK_THAT( 5., WithinRel( result.momentum()[8] ) );
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

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 5., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 7 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK( 7 == chunk.momentum().size() );
        CHECK( 7 == chunk.values().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[5] ) );
        CHECK_THAT( 5., WithinRel( chunk.momentum()[6] ) );
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

      std::vector< double > momentum = { 1., 2., 2., 2., 3., 4., 4., 4., 5. }; // <-- 2 jumps of 3 x values
      std::vector< double > values = { 1., 2., 3., 4., 5., 6., 7., 8., 9. };

      TabulatedComptonProfileFunction chunk( std::move( momentum ), std::move( values ),
                                             InterpolationType::LinearLinear, true );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 5., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 7 == chunk.numberPoints() );
        CHECK( 3 == chunk.numberRegions() );
        CHECK( 7 == chunk.momentum().size() );
        CHECK( 7 == chunk.values().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[5] ) );
        CHECK_THAT( 5., WithinRel( chunk.momentum()[6] ) );
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

      std::vector< double > momentum = { 1., 2., 2., 2., 4. }; // <-- jump of 3 x values
      std::vector< double > values = { 1., 2., 5., 3., 4. };

      TabulatedComptonProfileFunction chunk( std::move( momentum ), std::move( values ) );

      THEN( "linearise() removes the extraneous point in the jump" ) {

        CHECK( true == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );

        TabulatedComptonProfileFunction linear = chunk.linearise();

        CHECK_THAT( 1., WithinRel( linear.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( linear.upperMomentumLimit() ) );
        CHECK( 4 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );
        CHECK( 4 == linear.momentum().size() );
        CHECK( 4 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );
        CHECK_THAT( 1., WithinRel( linear.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( linear.momentum()[3] ) );
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
        // region 2: ( 3 + 4 ) * 2 / 2 = 7
        auto cumulative = chunk.cumulativeIntegral();
        REQUIRE( 5 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[2] ) ); // <-- extraneous point
        CHECK_THAT( 1.5, WithinRel( cumulative[3] ) );
        CHECK_THAT( 8.5, WithinRel( cumulative[4] ) );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and the first and second y value in the jump are "
          "the same" ) {

      std::vector< double > momentum = { 1., 2., 2., 2., 4. }; // <-- jump of 3 x values
      std::vector< double > values = { 1., 2., 2., 3., 4. }; // <-- extraneous point has same y

      TabulatedComptonProfileFunction chunk( std::move( momentum ), std::move( values ) );

      THEN( "linearise() removes the extraneous point in the jump and keeps the jump" ) {

        CHECK( true == chunk.isLinearised() );
        CHECK( false == chunk.isCurated() );

        TabulatedComptonProfileFunction linear = chunk.linearise();

        CHECK_THAT( 1., WithinRel( linear.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( linear.upperMomentumLimit() ) );
        CHECK( 4 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );
        CHECK( 4 == linear.momentum().size() );
        CHECK( 4 == linear.values().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );
        CHECK_THAT( 1., WithinRel( linear.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( linear.momentum()[3] ) );
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

        CHECK_THAT( 1.5, WithinRel( linear( 1.5 ) ) );
        CHECK_THAT( 3.5, WithinRel( linear( 3. ) ) );
      } // THEN

      THEN( "the cumulative integral has a value for every x value, including the extraneous "
            "point in the jump" ) {

        // region 1: ( 1 + 2 ) / 2 = 1.5
        // region 2: ( 3 + 4 ) * 2 / 2 = 7
        auto cumulative = chunk.cumulativeIntegral();
        REQUIRE( 5 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 1.5, WithinRel( cumulative[2] ) ); // <-- extraneous point
        CHECK_THAT( 1.5, WithinRel( cumulative[3] ) );
        CHECK_THAT( 8.5, WithinRel( cumulative[4] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data with a jump where both y values in the jump are the same" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > momentum = { 1., 2., 2., 3. };
      std::vector< double > values = { 1., 2., 2., 3. }; // <-- same y values in the jump

      TabulatedComptonProfileFunction chunk( std::move( momentum ), std::move( values ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 3., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
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

      THEN( "a TabulatedComptonProfileFunction can be integrated" ) {

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
    //       the jump. As a result, the final data contained in this TabulatedComptonProfileFunction is the
    //       same as the "non-linearised data with multiple regions with a jump" test.

    WHEN( "the data is given explicitly" ) {

      std::vector< double > momentum = { 1., 2., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 4., 3., 2. };
      std::vector< std::size_t > boundaries = { 2, 4 }; // <-- pointing to end of the jump
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedComptonProfileFunction chunk( std::move( momentum ),
                                             std::move( values ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.momentum().size() );
        CHECK( 5 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[4] ) );
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
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump at the end" ) {

    // note: at construction time, all but the first point of the jump will be removed and
    //       the last boundary value will point to the first point of the jump.

    WHEN( "the data is given explicitly and the jump consists of 2 points" ) {

      std::vector< double > momentum = { 1., 2., 3., 4., 4. }; // <-- jump at end
      std::vector< double > values = { 4., 3., 2., 1., 4. };
      std::vector< std::size_t > boundaries = { 1, 4 }; // <-- pointing to end
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedComptonProfileFunction chunk( std::move( momentum ), std::move( values ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) ); // <-- last point removed
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) ); // <-- last point removed
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and the jump consists of more than 2 points" ) {

      std::vector< double > momentum = { 1., 2., 3., 4., 4., 4. }; // <-- jump of 3 x values at end
      std::vector< double > values = { 4., 3., 2., 1., 4., 5. };
      std::vector< std::size_t > boundaries = { 1, 5 }; // <-- pointing to end
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedComptonProfileFunction chunk( std::move( momentum ),
                                             std::move( values ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) ); // <-- last two points removed
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) ); // <-- last two points removed
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump at the beginning" ) {

    // note: at construction time, all but the last point of the jump will be removed and
    //       all boundary values will be decremented by the number of points removed.

    WHEN( "the data is given explicitly and the jump consists of 2 points" ) {

      std::vector< double > momentum = { 1., 1., 2., 3., 4. }; // <-- jump at beginning
      std::vector< double > values = { 1., 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 2, 4 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedComptonProfileFunction chunk( std::move( momentum ),
                                             std::move( values ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) ); // <-- first point removed
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) ); // <-- first point removed
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );         // <-- boundary value reset
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly and the jump consists of more than 2 points" ) {

      std::vector< double > momentum = { 1., 1., 1., 2., 3., 4. }; // <-- jump of 3 x values at beginning
      std::vector< double > values = { 1., 2., 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 3, 5 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      TabulatedComptonProfileFunction chunk( std::move( momentum ),
                                             std::move( values ),
                                             std::move( boundaries ),
                                             std::move( interpolants ) );

      THEN( "a TabulatedComptonProfileFunction can be constructed and members can be tested" ) {

        CHECK_THAT( 1., WithinRel( chunk.lowerMomentumLimit() ) );
        CHECK_THAT( 4., WithinRel( chunk.upperMomentumLimit() ) );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.momentum().size() );
        CHECK( 4 == chunk.values().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.momentum()[0] ) ); // <-- first two points removed
        CHECK_THAT( 2., WithinRel( chunk.momentum()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.momentum()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.momentum()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) ); // <-- first two points removed
        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );         // <-- boundary value reset
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of TabulatedComptonProfileFunction are given" ) {

      TabulatedComptonProfileFunction left( { 1., 2., 3. }, { 1., 2., 3. } );
      TabulatedComptonProfileFunction equal( { 1., 2., 3. }, { 1., 2., 3. } );
      TabulatedComptonProfileFunction different1( { 1., 2., 3. }, { 1., 0., 3. } );
      TabulatedComptonProfileFunction different2( { 1., 2., 3. }, { 1., 2., 3. }, InterpolationType::LogLog );
      TabulatedComptonProfileFunction different3( { 1., 2., 3. }, { 1., 2., 3. },
                                                  { 1, 2 },
                                                  { InterpolationType::LinearLinear, InterpolationType::LogLog } );
      TabulatedComptonProfileFunction different4( { 1., 2.5, 3. }, { 1., 2., 3. } );
      TabulatedComptonProfileFunction uncurated( { 1., 2., 2., 2., 3. }, { 1., 2., 3., 4., 5. } );
      TabulatedComptonProfileFunction curated( { 1., 2., 2., 2., 3. }, { 1., 2., 3., 4., 5. },
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

  GIVEN( "invalid data for a TabulatedComptonProfileFunction object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComptonProfileFunction( empty, empty ) );
        CHECK_THROWS( TabulatedComptonProfileFunction( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > momentum = { 1., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComptonProfileFunction( std::move( momentum ), std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      std::vector< double > momentum = { 1., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComptonProfileFunction( std::move( momentum ),
                                                       std::move( values ),
                                                       std::move( boundaries ),
                                                       std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > momentum = { 1., 3., 2., 4. };
      std::vector< double > values = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComptonProfileFunction( std::move( momentum ), std::move( values ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      std::vector< double > momentum = { 1., 2., 4., 4. };
      std::vector< double > values = { 4., 3., 1., 4. };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComptonProfileFunction( std::move( momentum ),
                                                       std::move( values ),
                                                       std::move( boundaries ),
                                                       std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are not sorted" ) {

      std::vector< double > momentum = { 1., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 2, 1, 3 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLinear,
        InterpolationType::LinearLinear
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComptonProfileFunction( std::move( momentum ),
                                                       std::move( values ),
                                                       std::move( boundaries ),
                                                       std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are not unique" ) {

      std::vector< double > momentum = { 1., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 1, 1, 3 };
      std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLinear,
        InterpolationType::LinearLinear
      };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComptonProfileFunction( std::move( momentum ),
                                                       std::move( values ),
                                                       std::move( boundaries ),
                                                       std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "there are no boundaries and interpolants" ) {

      std::vector< double > momentum = { 1., 2., 3., 4. };
      std::vector< double > values = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = {};
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( TabulatedComptonProfileFunction( std::move( momentum ),
                                                       std::move( values ),
                                                       std::move( boundaries ),
                                                       std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
