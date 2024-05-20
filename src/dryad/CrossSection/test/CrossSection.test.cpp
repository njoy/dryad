// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/CrossSection.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "InterpolationTable" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 2., 1. };

      CrossSection chunk( std::move( x ), std::move( y ) );

      THEN( "an InterpolationTable can be constructed and members can be tested" ) {

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
        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == chunk.isLinearised() );
      } // THEN

      THEN( "an InterpolationTable can be evaluated" ) {

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

//      THEN( "arithmetic operations can be performed" ) {
//
//        CrossSection result( { 1., 4. }, { 0., 0. } );
//        CrossSection same( { 1., 4. }, { 0., 3. } );
//        CrossSection threshold( { 2., 4. }, { 0., 2. } );
//        CrossSection nonzerothreshold( { 2., 4. }, { 1., 2. } );
//        CrossSection small( { 1., 3. }, { 0., 2. } );
//
//        chunk += 2.;
//
//        CHECK( 4 == chunk.numberPoints() );
//        CHECK( 1 == chunk.numberRegions() );
//        CHECK( 4 == chunk.energies().size() );
//        CHECK( 4 == chunk.values().size() );
//        CHECK( 1 == chunk.boundaries().size() );
//        CHECK( 1 == chunk.interpolants().size() );
//        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
//        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
//        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
//        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
//        CHECK_THAT( 6., WithinRel( chunk.values()[0] ) );
//        CHECK_THAT( 5., WithinRel( chunk.values()[1] ) );
//        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
//        CHECK_THAT( 3., WithinRel( chunk.values()[3] ) );
//        CHECK( 3 == chunk.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == chunk.interpolants()[0] );
//
//        chunk -= 2.;
//
//        CHECK( 4 == chunk.numberPoints() );
//        CHECK( 1 == chunk.numberRegions() );
//        CHECK( 4 == chunk.energies().size() );
//        CHECK( 4 == chunk.values().size() );
//        CHECK( 1 == chunk.boundaries().size() );
//        CHECK( 1 == chunk.interpolants().size() );
//        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
//        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
//        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
//        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
//        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
//        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
//        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
//        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
//        CHECK( 3 == chunk.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == chunk.interpolants()[0] );
//
//        chunk *= 2.;
//
//        CHECK( 4 == chunk.numberPoints() );
//        CHECK( 1 == chunk.numberRegions() );
//        CHECK( 4 == chunk.energies().size() );
//        CHECK( 4 == chunk.values().size() );
//        CHECK( 1 == chunk.boundaries().size() );
//        CHECK( 1 == chunk.interpolants().size() );
//        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
//        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
//        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
//        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
//        CHECK_THAT( 8., WithinRel( chunk.values()[0] ) );
//        CHECK_THAT( 6., WithinRel( chunk.values()[1] ) );
//        CHECK_THAT( 4., WithinRel( chunk.values()[2] ) );
//        CHECK_THAT( 2., WithinRel( chunk.values()[3] ) );
//        CHECK( 3 == chunk.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == chunk.interpolants()[0] );
//
//        chunk /= 2.;
//
//        CHECK( 4 == chunk.numberPoints() );
//        CHECK( 1 == chunk.numberRegions() );
//        CHECK( 4 == chunk.energies().size() );
//        CHECK( 4 == chunk.values().size() );
//        CHECK( 1 == chunk.boundaries().size() );
//        CHECK( 1 == chunk.interpolants().size() );
//        CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
//        CHECK_THAT( 2., WithinRel( chunk.energies()[1] ) );
//        CHECK_THAT( 3., WithinRel( chunk.energies()[2] ) );
//        CHECK_THAT( 4., WithinRel( chunk.energies()[3] ) );
//        CHECK_THAT( 4., WithinRel( chunk.values()[0] ) );
//        CHECK_THAT( 3., WithinRel( chunk.values()[1] ) );
//        CHECK_THAT( 2., WithinRel( chunk.values()[2] ) );
//        CHECK_THAT( 1., WithinRel( chunk.values()[3] ) );
//        CHECK( 3 == chunk.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == chunk.interpolants()[0] );
//
//        result = -chunk;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
//        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
//        CHECK_THAT(  3., WithinRel( result.energies()[2] ) );
//        CHECK_THAT(  4., WithinRel( result.energies()[3] ) );
//        CHECK_THAT( -4., WithinRel( result.values()[0] ) );
//        CHECK_THAT( -3., WithinRel( result.values()[1] ) );
//        CHECK_THAT( -2., WithinRel( result.values()[2] ) );
//        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        result = chunk + 2.;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
//        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
//        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
//        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
//        CHECK_THAT( 3., WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        result = 2. + chunk;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
//        CHECK_THAT( 6., WithinRel( result.values()[0] ) );
//        CHECK_THAT( 5., WithinRel( result.values()[1] ) );
//        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
//        CHECK_THAT( 3., WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        result = chunk - 2.;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
//        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
//        CHECK_THAT(  3., WithinRel( result.energies()[2] ) );
//        CHECK_THAT(  4., WithinRel( result.energies()[3] ) );
//        CHECK_THAT(  2., WithinRel( result.values()[0] ) );
//        CHECK_THAT(  1., WithinRel( result.values()[1] ) );
//        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
//        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        result = 2. - chunk;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT(  1., WithinRel( result.energies()[0] ) );
//        CHECK_THAT(  2., WithinRel( result.energies()[1] ) );
//        CHECK_THAT(  3., WithinRel( result.energies()[2] ) );
//        CHECK_THAT(  4., WithinRel( result.energies()[3] ) );
//        CHECK_THAT( -2., WithinRel( result.values()[0] ) );
//        CHECK_THAT( -1., WithinRel( result.values()[1] ) );
//        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
//        CHECK_THAT(  1., WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        result = chunk * 2.;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
//        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
//        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
//        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
//        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        result = 2. * chunk;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT( 1., WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2., WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3., WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 4., WithinRel( result.energies()[3] ) );
//        CHECK_THAT( 8., WithinRel( result.values()[0] ) );
//        CHECK_THAT( 6., WithinRel( result.values()[1] ) );
//        CHECK_THAT( 4., WithinRel( result.values()[2] ) );
//        CHECK_THAT( 2., WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        result = chunk / 2.;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
//        CHECK_THAT( 2.0, WithinRel( result.values()[0] ) );
//        CHECK_THAT( 1.5, WithinRel( result.values()[1] ) );
//        CHECK_THAT( 1.0, WithinRel( result.values()[2] ) );
//        CHECK_THAT( 0.5, WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        chunk += same;
//
//        CHECK( 4 == chunk.numberPoints() );
//        CHECK( 1 == chunk.numberRegions() );
//        CHECK( 4 == chunk.energies().size() );
//        CHECK( 4 == chunk.values().size() );
//        CHECK( 1 == chunk.boundaries().size() );
//        CHECK( 1 == chunk.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( chunk.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( chunk.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( chunk.energies()[2] ) );
//        CHECK_THAT( 4. , WithinRel( chunk.energies()[3] ) );
//        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
//        CHECK_THAT( 4.0, WithinRel( chunk.values()[1] ) );
//        CHECK_THAT( 4.0, WithinRel( chunk.values()[2] ) );
//        CHECK_THAT( 4.0, WithinRel( chunk.values()[3] ) );
//        CHECK( 3 == chunk.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == chunk.interpolants()[0] );
//
//        chunk -= same;
//
//        CHECK( 4 == chunk.numberPoints() );
//        CHECK( 1 == chunk.numberRegions() );
//        CHECK( 4 == chunk.energies().size() );
//        CHECK( 4 == chunk.values().size() );
//        CHECK( 1 == chunk.boundaries().size() );
//        CHECK( 1 == chunk.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( chunk.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( chunk.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( chunk.energies()[2] ) );
//        CHECK_THAT( 4. , WithinRel( chunk.energies()[3] ) );
//        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
//        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
//        CHECK_THAT( 2.0, WithinRel( chunk.values()[2] ) );
//        CHECK_THAT( 1.0, WithinRel( chunk.values()[3] ) );
//        CHECK( 3 == chunk.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == chunk.interpolants()[0] );
//
//        result = chunk + same;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
//        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
//        CHECK_THAT( 4.0, WithinRel( result.values()[1] ) );
//        CHECK_THAT( 4.0, WithinRel( result.values()[2] ) );
//        CHECK_THAT( 4.0, WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        result = chunk - same;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
//        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
//        CHECK_THAT(  2., WithinRel( result.values()[1] ) );
//        CHECK_THAT(  0., WithinRel( result.values()[2] ) );
//        CHECK_THAT( -2., WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        chunk += threshold;
//
//        CHECK( 4 == chunk.numberPoints() );
//        CHECK( 1 == chunk.numberRegions() );
//        CHECK( 4 == chunk.energies().size() );
//        CHECK( 4 == chunk.values().size() );
//        CHECK( 1 == chunk.boundaries().size() );
//        CHECK( 1 == chunk.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( chunk.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( chunk.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( chunk.energies()[2] ) );
//        CHECK_THAT( 4. , WithinRel( chunk.energies()[3] ) );
//        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
//        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
//        CHECK_THAT( 3.0, WithinRel( chunk.values()[2] ) );
//        CHECK_THAT( 3.0, WithinRel( chunk.values()[3] ) );
//        CHECK( 3 == chunk.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == chunk.interpolants()[0] );
//
//        chunk -= threshold;
//
//        CHECK( 4 == chunk.numberPoints() );
//        CHECK( 1 == chunk.numberRegions() );
//        CHECK( 4 == chunk.energies().size() );
//        CHECK( 4 == chunk.values().size() );
//        CHECK( 1 == chunk.boundaries().size() );
//        CHECK( 1 == chunk.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( chunk.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( chunk.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( chunk.energies()[2] ) );
//        CHECK_THAT( 4. , WithinRel( chunk.energies()[3] ) );
//        CHECK_THAT( 4.0, WithinRel( chunk.values()[0] ) );
//        CHECK_THAT( 3.0, WithinRel( chunk.values()[1] ) );
//        CHECK_THAT( 2.0, WithinRel( chunk.values()[2] ) );
//        CHECK_THAT( 1.0, WithinRel( chunk.values()[3] ) );
//        CHECK( 3 == chunk.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == chunk.interpolants()[0] );
//
//        result = chunk + threshold;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
//        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
//        CHECK_THAT( 3.0, WithinRel( result.values()[1] ) );
//        CHECK_THAT( 3.0, WithinRel( result.values()[2] ) );
//        CHECK_THAT( 3.0, WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        result = chunk - threshold;
//
//        CHECK( 4 == result.numberPoints() );
//        CHECK( 1 == result.numberRegions() );
//        CHECK( 4 == result.energies().size() );
//        CHECK( 4 == result.values().size() );
//        CHECK( 1 == result.boundaries().size() );
//        CHECK( 1 == result.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 4. , WithinRel( result.energies()[3] ) );
//        CHECK_THAT(  4., WithinRel( result.values()[0] ) );
//        CHECK_THAT(  3., WithinRel( result.values()[1] ) );
//        CHECK_THAT(  1., WithinRel( result.values()[2] ) );
//        CHECK_THAT( -1., WithinRel( result.values()[3] ) );
//        CHECK( 3 == result.boundaries()[0] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        // this will add a second point at the lower end point
//        result = chunk + small;
//
//        CHECK( 5 == result.numberPoints() );
//        CHECK( 2 == result.numberRegions() );
//        CHECK( 5 == result.energies().size() );
//        CHECK( 5 == result.values().size() );
//        CHECK( 2 == result.boundaries().size() );
//        CHECK( 2 == result.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 3. , WithinRel( result.energies()[3] ) );
//        CHECK_THAT( 4. , WithinRel( result.energies()[4] ) );
//        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
//        CHECK_THAT( 4.0, WithinRel( result.values()[1] ) );
//        CHECK_THAT( 4.0, WithinRel( result.values()[2] ) );
//        CHECK_THAT( 2.0, WithinRel( result.values()[3] ) );
//        CHECK_THAT( 1.0, WithinRel( result.values()[4] ) );
//        CHECK( 2 == result.boundaries()[0] );
//        CHECK( 4 == result.boundaries()[1] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        // this will add a second point at the lower end point
//        result = chunk - small;
//
//        CHECK( 5 == result.numberPoints() );
//        CHECK( 2 == result.numberRegions() );
//        CHECK( 5 == result.energies().size() );
//        CHECK( 5 == result.values().size() );
//        CHECK( 2 == result.boundaries().size() );
//        CHECK( 2 == result.interpolants().size() );
//        CHECK_THAT( 1. , WithinRel( result.energies()[0] ) );
//        CHECK_THAT( 2. , WithinRel( result.energies()[1] ) );
//        CHECK_THAT( 3. , WithinRel( result.energies()[2] ) );
//        CHECK_THAT( 3. , WithinRel( result.energies()[3] ) );
//        CHECK_THAT( 4. , WithinRel( result.energies()[4] ) );
//        CHECK_THAT( 4.0, WithinRel( result.values()[0] ) );
//        CHECK_THAT( 2.0, WithinRel( result.values()[1] ) );
//        CHECK_THAT( 0.0, WithinRel( result.values()[2] ) );
//        CHECK_THAT( 2.0, WithinRel( result.values()[3] ) );
//        CHECK_THAT( 1.0, WithinRel( result.values()[4] ) );
//        CHECK( 2 == result.boundaries()[0] );
//        CHECK( 4 == result.boundaries()[1] );
//        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == result.interpolants()[0] );
//
//        // the threshold table starts with a non-zero value
//        CHECK_THROWS( chunk += nonzerothreshold );
//        CHECK_THROWS( chunk -= nonzerothreshold );
//        CHECK_THROWS( result = chunk + nonzerothreshold );
//        CHECK_THROWS( result = chunk - nonzerothreshold );
//      } // THEN

      THEN( "an InterpolationTable can be linearised" ) {

        CrossSection linear = chunk.linearise( CrossSection::Tolerance( 0.001 ) );

        CHECK( 4 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 4 == linear.energies().size() );
        CHECK( 4 == linear.values().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 3 == linear.boundaries()[0] );

        CHECK( njoy::scion::interpolation::InterpolationType::LinearLinear == linear.interpolants()[0] );

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
} // SCENARIO
