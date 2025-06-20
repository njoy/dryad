// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/atomic/RadiativeTransitionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::atomic;

void verifyChunkWithoutTransitionEnergy( const RadiativeTransitionData& );
void verifyChunkWithTransitionEnergy( const RadiativeTransitionData& );

SCENARIO( "RadiativeTransitionData" ) {

  GIVEN( "valid data for a radiative transition" ) {

    WHEN( "the data is given explicitly for a radiative transition without "
          "a transition energy" ) {

      id::ElectronSubshellID originatingShell( "K" );
      double probability = 1e-3;

      RadiativeTransitionData chunk( std::move( originatingShell ), std::move( probability ) );

      THEN( "an RadiativeTransitionData can be constructed and members can be tested" ) {

        verifyChunkWithoutTransitionEnergy( chunk );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly for a radiative transition with "
          "a transition energy" ) {

      id::ElectronSubshellID originatingShell( "K" );
      double probability = 1e-3;
      double energy = 550.;

      RadiativeTransitionData chunk( std::move( originatingShell ), std::move( probability ),
                                     std::move( energy ) );

      THEN( "an RadiativeTransitionData can be constructed and members can be tested" ) {

        verifyChunkWithTransitionEnergy( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of NonRadiativeTransitionData are given" ) {

      id::ElectronSubshellID k_shell( id::ElectronSubshellID::K );

      RadiativeTransitionData left( k_shell, 1e-3 );
      RadiativeTransitionData equal( k_shell, 1e-3 );
      RadiativeTransitionData different( k_shell, 1e-3, 550. );

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

void verifyChunkWithoutTransitionEnergy( const RadiativeTransitionData& chunk ) {

  CHECK( TransitionType::Radiative == chunk.type() );
  CHECK( id::ElectronSubshellID( "K" ) == chunk.originatingShell() );
  CHECK_THAT( 1e-3, WithinRel( chunk.probability() ) );
  CHECK( std::nullopt == chunk.energy() );
}

void verifyChunkWithTransitionEnergy( const RadiativeTransitionData& chunk ) {

  CHECK( TransitionType::Radiative == chunk.type() );
  CHECK( id::ElectronSubshellID( "K" ) == chunk.originatingShell() );
  CHECK_THAT( 1e-3, WithinRel( chunk.probability() ) );
  CHECK_THAT( 550., WithinRel( chunk.energy().value() ) );
}
