// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/ChannelRadii.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "ChannelRadii" ) {

  GIVEN( "valid data for a ChannelRadii" ) {

    double radius = 0.1;

    double trueRadius = 0.2;
    double effectiveRadius = 0.3;

    double pRadius = 0.4;
    double sRadius = 0.5;
    TabulatedRadius phiRadius( { 1e-5, 2e+7 }, { .6, .6 } );

    THEN( "a ChannelRadii can be constructed using constant radii" ) {

      double energy = 1e-5;

      ChannelRadii radii1( radius );

      CHECK( false == radii1.hasShiftFactorRadius() );
      CHECK( false == radii1.hasPhaseShiftRadius() );
      CHECK( true == std::holds_alternative< double >( radii1.penetrabilityRadius() ) );
      CHECK( std::nullopt == radii1.shiftFactorRadius() );
      CHECK( std::nullopt == radii1.phaseShiftRadius() );
      CHECK_THAT( 0.1, WithinRel( radii1.calculatePenetrabilityRadius( energy ) ) );
      CHECK_THAT( 0.1, WithinRel( radii1.calculateShiftFactorRadius( energy ) ) );
      CHECK_THAT( 0.1, WithinRel( radii1.calculatePhaseShiftRadius( energy ) ) );

      ChannelRadii radii2( trueRadius, effectiveRadius );

      CHECK( false == radii2.hasShiftFactorRadius() );
      CHECK( true == radii2.hasPhaseShiftRadius() );
      CHECK( true == std::holds_alternative< double >( radii2.penetrabilityRadius() ) );
      CHECK( true == std::holds_alternative< double >( radii2.phaseShiftRadius().value() ) );
      CHECK( std::nullopt == radii2.shiftFactorRadius() );
      CHECK( std::nullopt != radii2.phaseShiftRadius() );
      CHECK_THAT( 0.2, WithinRel( radii2.calculatePenetrabilityRadius( energy ) ) );
      CHECK_THAT( 0.2, WithinRel( radii2.calculateShiftFactorRadius( energy ) ) );
      CHECK_THAT( 0.3, WithinRel( radii2.calculatePhaseShiftRadius( energy ) ) );

      ChannelRadii radii3( pRadius, sRadius, phiRadius );

      CHECK( true == radii3.hasShiftFactorRadius() );
      CHECK( true == radii3.hasPhaseShiftRadius() );
      CHECK( true == std::holds_alternative< double >( radii3.penetrabilityRadius() ) );
      CHECK( true == std::holds_alternative< double >( radii3.shiftFactorRadius().value() ) );
      CHECK( true == std::holds_alternative< TabulatedRadius >( radii3.phaseShiftRadius().value() ) );
      CHECK( std::nullopt != radii3.shiftFactorRadius() );
      CHECK( std::nullopt != radii3.phaseShiftRadius() );
      CHECK_THAT( 0.4, WithinRel( radii3.calculatePenetrabilityRadius( energy ) ) );
      CHECK_THAT( 0.5, WithinRel( radii3.calculateShiftFactorRadius( energy ) ) );
      CHECK_THAT( 0.6, WithinRel( radii3.calculatePhaseShiftRadius( energy ) ) );
    } // THEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of ChannelRadii is given" ) {

      using Radius = std::variant< double, njoy::dryad::resonances::TabulatedRadius >;
      using OptionalRadius = std::optional< Radius >;

      ChannelRadii chunk( .1 );

      THEN( "the penetrability radius can be changed" ) {

        Radius newradius = .3;
        Radius original = .1;

        chunk.penetrabilityRadius( newradius );

        CHECK( newradius == chunk.penetrabilityRadius() );

        chunk.penetrabilityRadius( original );

        CHECK( original == chunk.penetrabilityRadius() );
      } // THEN

      THEN( "the shift factor radius can be changed" ) {

        OptionalRadius newradius = .3;
        OptionalRadius original = std::nullopt;

        chunk.shiftFactorRadius( newradius );

        CHECK( newradius == chunk.shiftFactorRadius() );

        chunk.shiftFactorRadius( original );

        CHECK( original == chunk.shiftFactorRadius() );
      } // THEN

      THEN( "the phase shift radius can be changed" ) {

        OptionalRadius newradius = .3;
        OptionalRadius original = std::nullopt;

        chunk.phaseShiftRadius( newradius );

        CHECK( newradius == chunk.phaseShiftRadius() );

        chunk.phaseShiftRadius( original );

        CHECK( original == chunk.phaseShiftRadius() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of Documentation are given" ) {

      ChannelRadii left( .1 );
      ChannelRadii equal( .1 );
      ChannelRadii different( .2 );

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
