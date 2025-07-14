// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/atomic/ElectronSubshellConfiguration.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::atomic;

void verifyChunkWithoutTransitions( const ElectronSubshellConfiguration& );
void verifyChunk( const ElectronSubshellConfiguration&, bool );

SCENARIO( "ElectronSubshellConfiguration" ) {

  GIVEN( "valid data for a subshell configuration without transitions" ) {

    WHEN( "the data is given explicitly" ) {

      id::ElectronSubshellID id( "K" );
      double energy = 538;
      double population = 2.;

      ElectronSubshellConfiguration chunk( std::move( id ), std::move( energy ),
                                           std::move( population ) );

      THEN( "an ElectronSubshellConfiguration can be constructed and members "
            "can be tested" ) {

        verifyChunkWithoutTransitions( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a subshell configuration with transitions" ) {

    WHEN( "the data is given explicitly" ) {

      id::ElectronSubshellID id( "K" );
      double energy = 538;
      double population = 2.;
      std::vector< RadiativeTransitionData > radiative = {

        RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
        RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 )
      };
      std::vector< NonRadiativeTransitionData > nonradiative = {

        NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
        NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
        NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
        NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
        NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
        NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 )
      };

      // no normalisation
      ElectronSubshellConfiguration chunk1( id, energy, population,
                                            radiative, nonradiative ,
                                            false );

      // normalisation at construction time
      ElectronSubshellConfiguration chunk2( std::move( id ), std::move( energy ),
                                            std::move( population ),
                                            std::move( radiative ),
                                            std::move( nonradiative ),
                                            true );

      THEN( "an ElectronSubshellConfiguration can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk1, false ); // unnormalised
        verifyChunk( chunk2, true );  // normalised
      } // THEN

      THEN( "an ElectronSubshellConfiguration can be normalised" ) {

        chunk1.normalise();
        verifyChunk( chunk1, true ); // now normalised

        chunk2.normalise();
        verifyChunk( chunk2, true ); // still normalised
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of ElectronSubshellConfiguration is given" ) {

      id::ElectronSubshellID( "K" );
      double energy = 538;
      double population = 2.;

      ElectronSubshellConfiguration chunk( id::ElectronSubshellID( "K" ), 538, 2 );

      THEN( "the probability can be changed" ) {

        double newenergy = 538.6;
        double original = 538;

        chunk.bindingEnergy( newenergy );

        CHECK( newenergy == chunk.bindingEnergy() );

        chunk.bindingEnergy( original );

        verifyChunkWithoutTransitions( chunk );
      } // THEN

      THEN( "the population can be changed" ) {

        double newpopulation = 1.5;
        double original = 2;

        chunk.population( newpopulation );

        CHECK( newpopulation == chunk.population() );

        chunk.population( original );

        verifyChunkWithoutTransitions( chunk );
      } // THEN

      THEN( "the transitions can be changed" ) {

        std::vector< RadiativeTransitionData > newradiative = {

          RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
          RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 )
        };
        std::vector< NonRadiativeTransitionData > newnonradiative = {

          NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
          NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
          NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
          NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
          NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
          NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 )
        };

        chunk.radiativeTransitions( newradiative );
        chunk.nonRadiativeTransitions( newnonradiative );

        verifyChunk( chunk, false );

        chunk.radiativeTransitions( {} );
        chunk.nonRadiativeTransitions( {} );

        verifyChunkWithoutTransitions( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ElectronSubshellConfiguration are given" ) {

      id::ElectronSubshellID k_shell( id::ElectronSubshellID::K );
      id::ElectronSubshellID l1_shell( id::ElectronSubshellID::L1 );

      ElectronSubshellConfiguration left( k_shell, 538., 2.,
                                          { RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                            RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
                                          { NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                            NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
                                            NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
                                            NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
                                            NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
                                            NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) } );
      ElectronSubshellConfiguration equal( k_shell, 538., 2.,
                                           { RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                             RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
                                           { NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                             NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
                                             NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
                                             NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
                                             NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
                                             NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) } );
      ElectronSubshellConfiguration different( k_shell, 538., 2.,
                                               { RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                                 RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
                                               { NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                                 NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) } );

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

void verifyChunkWithoutTransitions( const ElectronSubshellConfiguration& chunk ) {

  CHECK( id::ElectronSubshellID( "K" ) == chunk.identifier() );
  CHECK_THAT( 538, WithinRel( chunk.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( chunk.population() ) );

  CHECK( false == chunk.hasRadiativeTransitions() );
  CHECK( false == chunk.hasNonRadiativeTransitions() );
  CHECK( false == chunk.hasTransitions() );

  CHECK( 0 == chunk.numberRadiativeTransitions() );
  CHECK( 0 == chunk.numberNonRadiativeTransitions() );
  CHECK( 0 == chunk.numberTransitions() );
  CHECK( 0 == chunk.radiativeTransitions().size() );
  CHECK( 0 == chunk.nonRadiativeTransitions().size() );

  CHECK_THAT( 0., WithinRel( chunk.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( chunk.totalNonRadiativeProbability() ) );
}

void verifyChunk( const ElectronSubshellConfiguration& chunk,
                  bool normalise ) {

  CHECK( id::ElectronSubshellID( "K" ) == chunk.identifier() );
  CHECK_THAT( 538, WithinRel( chunk.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( chunk.population() ) );

  CHECK( true == chunk.hasRadiativeTransitions() );
  CHECK( true == chunk.hasNonRadiativeTransitions() );
  CHECK( true == chunk.hasTransitions() );

  CHECK( 2 == chunk.numberRadiativeTransitions() );
  CHECK( 6 == chunk.numberNonRadiativeTransitions() );
  CHECK( 8 == chunk.numberTransitions() );
  CHECK( 2 == chunk.radiativeTransitions().size() );
  CHECK( 6 == chunk.nonRadiativeTransitions().size() );

  double normalisation = normalise ? 1.00000015 : 1.0;

  CHECK( TransitionType::Radiative == chunk.radiativeTransitions()[0].type() );
  CHECK( TransitionType::Radiative == chunk.radiativeTransitions()[1].type() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.radiativeTransitions()[1].originatingShell() );
  CHECK_THAT( 0.00190768 / normalisation, WithinRel( chunk.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.00380027 / normalisation, WithinRel( chunk.radiativeTransitions()[1].probability() ) );
  CHECK_THAT( 523.09, WithinRel( chunk.radiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 523.13, WithinRel( chunk.radiativeTransitions()[1].energy().value() ) );

  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[0].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[1].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[2].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[3].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[4].type() );
  CHECK( TransitionType::NonRadiative == chunk.nonRadiativeTransitions()[5].type() );
  CHECK( id::ElectronSubshellID( "L1" ) == chunk.nonRadiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == chunk.nonRadiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == chunk.nonRadiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.nonRadiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.nonRadiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.nonRadiativeTransitions()[5].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == chunk.nonRadiativeTransitions()[0].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.nonRadiativeTransitions()[1].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.nonRadiativeTransitions()[2].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == chunk.nonRadiativeTransitions()[3].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.nonRadiativeTransitions()[4].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == chunk.nonRadiativeTransitions()[5].emittingShell() );
  CHECK_THAT( 0.178644  / normalisation, WithinRel( chunk.nonRadiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.116224  / normalisation, WithinRel( chunk.nonRadiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.230418  / normalisation, WithinRel( chunk.nonRadiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0110822 / normalisation, WithinRel( chunk.nonRadiativeTransitions()[3].probability() ) );
  CHECK_THAT( 0.291115  / normalisation, WithinRel( chunk.nonRadiativeTransitions()[4].probability() ) );
  CHECK_THAT( 0.166809  / normalisation, WithinRel( chunk.nonRadiativeTransitions()[5].probability() ) );
  CHECK_THAT( 478.82, WithinRel( chunk.nonRadiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 493.86, WithinRel( chunk.nonRadiativeTransitions()[1].energy().value() ) );
  CHECK_THAT( 493.9 , WithinRel( chunk.nonRadiativeTransitions()[2].energy().value() ) );
  CHECK_THAT( 508.9 , WithinRel( chunk.nonRadiativeTransitions()[3].energy().value() ) );
  CHECK_THAT( 508.94, WithinRel( chunk.nonRadiativeTransitions()[4].energy().value() ) );
  CHECK_THAT( 508.98, WithinRel( chunk.nonRadiativeTransitions()[5].energy().value() ) );

  CHECK_THAT( 0.00570795 / normalisation, WithinRel( chunk.totalRadiativeProbability() ) );
  CHECK_THAT( 0.9942922  / normalisation, WithinRel( chunk.totalNonRadiativeProbability() ) );
}
