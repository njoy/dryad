//include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/ReducedWidthConversion.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "ReducedWidthConversion" ) {

  GIVEN( "valid orbital momentum values for a reduced width conversion" ) {

    unsigned int l = 0;
    double ref_energy = 1.0;

    THEN( "A valid ReducedWidthConversion can be constructed") {

      ReducedWidthConversion chunk( l, ref_energy );

      CHECK( l == chunk.orbitalAngularMomentum() );
      CHECK_THAT( 1.00, WithinRel( chunk.referenceEnergy() ) );

      CHECK_THAT( 3.1622776601683794e-3, WithinRel( chunk.calculateConversionFactor( 1.0, 1e-5 ) ) );
      CHECK_THAT( 1.,                    WithinRel( chunk.calculateConversionFactor( 1.0, 1.   ) ) );
      CHECK_THAT( 10.,                   WithinRel( chunk.calculateConversionFactor( 1.0, 100. ) ) );

    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ReducedWidthConversion are given" ) {
      unsigned int l = 0;
      double ref_energy = 1.0;

      ReducedWidthConversion left( l, ref_energy );
      ReducedWidthConversion equal( l, ref_energy );
      ReducedWidthConversion different( 1, ref_energy );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
