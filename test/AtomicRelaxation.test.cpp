// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/AtomicRelaxation.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const AtomicRelaxation&, bool );

SCENARIO( "AtomicRelaxation" ) {

  GIVEN( "valid data for a AtomicRelaxation" ) {

    WHEN( "the data is given explicitly" ) {

      // note: subshell data is deliberately given out of order to check for sorting,
      //       the transition probabilities are not normalised to test normalisation
      //       and the transition energies are not correct to test calculating the energies

      id::ElementID element( 1 );
      std::vector< atomic::ElectronSubshellConfiguration > subshells = {

        atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L3" ), 13.62, 2.67 ),
        atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L2" ), 13.62, 1.33 ),
        atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L1" ), 28.48, 2 ),
        atomic::ElectronSubshellConfiguration(

          id::ElectronSubshellID( "K" ), 538, 2,
          { atomic::RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
            atomic::RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
          { atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
            atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
            atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
            atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
            atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
            atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) },
          false
        )
      };

      // no normalisation
      AtomicRelaxation chunk1( element, subshells, false );

      // normalisation at construction time
      AtomicRelaxation chunk2( std::move( element ), std::move( subshells ), true );

      THEN( "a AtomicRelaxation can be constructed and members can be tested" ) {

        verifyChunk( chunk1, false ); // unnormalised
        verifyChunk( chunk2, true );  // normalised
      } // THEN

      THEN( "a AtomicRelaxation can be normalised" ) {

        chunk1.normalise();
        verifyChunk( chunk1, true ); // now normalised

        chunk2.normalise();
        verifyChunk( chunk2, true ); // still normalised
      } // THEN

      THEN( "transition energies can be calculated" ) {

        chunk1.calculateTransitionEnergies();

        CHECK_THAT( 538 - 13.62        , WithinRel( chunk1.subshells()[0].radiativeTransitions()[0].energy().value() ) );
        CHECK_THAT( 538 - 13.62        , WithinRel( chunk1.subshells()[0].radiativeTransitions()[1].energy().value() ) );
        CHECK_THAT( 538 - 28.48 - 28.48, WithinRel( chunk1.subshells()[0].nonRadiativeTransitions()[0].energy().value() ) );
        CHECK_THAT( 538 - 28.48 - 13.62, WithinRel( chunk1.subshells()[0].nonRadiativeTransitions()[1].energy().value() ) );
        CHECK_THAT( 538 - 28.48 - 13.62, WithinRel( chunk1.subshells()[0].nonRadiativeTransitions()[2].energy().value() ) );
        CHECK_THAT( 538 - 13.62 - 13.62, WithinRel( chunk1.subshells()[0].nonRadiativeTransitions()[3].energy().value() ) );
        CHECK_THAT( 538 - 13.62 - 13.62, WithinRel( chunk1.subshells()[0].nonRadiativeTransitions()[4].energy().value() ) );
        CHECK_THAT( 538 - 13.62 - 13.62, WithinRel( chunk1.subshells()[0].nonRadiativeTransitions()[5].energy().value() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of Reaction is given" ) {

      AtomicRelaxation chunk( id::ElementID( 1 ),
                              { atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L3" ), 13.62, 2.67 ),
                                atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L2" ), 13.62, 1.33 ),
                                atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L1" ), 28.48, 2 ),
                                atomic::ElectronSubshellConfiguration(

                                  id::ElectronSubshellID( "K" ), 538, 2,
                                  { atomic::RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                    atomic::RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
                                  { atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) },
                                  false
                                ) } );

      THEN( "the subshell data can be changed" ) {

        std::vector< atomic::ElectronSubshellConfiguration > newsubshells = {

                atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "M1" ), 5000, 2 )
        };
        std::vector< atomic::ElectronSubshellConfiguration > original = {
                atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L3" ), 13.62, 2.67 ),
                atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L2" ), 13.62, 1.33 ),
                atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L1" ), 28.48, 2 ),
                atomic::ElectronSubshellConfiguration(

                  id::ElectronSubshellID( "K" ), 538, 2,
                  { atomic::RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                    atomic::RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
                  { atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) } )
        };

        chunk.subshells( newsubshells );

        CHECK( newsubshells == chunk.subshells() );

        chunk.subshells( original );

        verifyChunk( chunk, false );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of AtomicRelaxation are given" ) {

      id::ElementID h( 1 );
      id::ElectronSubshellID k_shell( id::ElectronSubshellID::K );
      id::ElectronSubshellID l1_shell( id::ElectronSubshellID::L1 );

      AtomicRelaxation left( h,
                             { atomic::ElectronSubshellConfiguration(
                                 k_shell, 538., 2.,
                                 { atomic::RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                   atomic::RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
                                 { atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                   atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
                                   atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
                                   atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
                                   atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
                                   atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) } ),
                               atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L1" ), 28.48, 2 ),
                               atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L2" ), 13.62, 1.33 ),
                               atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L3" ), 13.62, 2.67 ) } );
      AtomicRelaxation equal( h,
                              { atomic::ElectronSubshellConfiguration(
                                  k_shell, 538., 2.,
                                  { atomic::RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                    atomic::RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
                                  { atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
                                    atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) } ),
                                atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L1" ), 28.48, 2 ),
                                atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L2" ), 13.62, 1.33 ),
                                atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L3" ), 13.62, 2.67 ) } );
      AtomicRelaxation different( h,
                                  { atomic::ElectronSubshellConfiguration(
                                      k_shell, 538., 2.,
                                      { atomic::RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
                                        atomic::RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 ) },
                                      { atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
                                        atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 ) } ),
                                    atomic::ElectronSubshellConfiguration( id::ElectronSubshellID( "L3" ), 13.62, 2.67 ) } );

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

void verifyChunk( const AtomicRelaxation& chunk, bool normalise ) {

  // identifiers
  CHECK( id::ElementID( 1 ) == chunk.elementIdentifier() );

  // subshell configuration data
  CHECK( 4 == chunk.numberSubshells() );
  CHECK( 4 == chunk.subshells().size() );

  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "K" ) ) );
  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "L1" ) ) );
  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "L2" ) ) );
  CHECK( true == chunk.hasSubshell( id::ElectronSubshellID( "L3" ) ) );
  CHECK( false == chunk.hasSubshell( id::ElectronSubshellID( "M1" ) ) );

  double normalisation = normalise ? 1.00000015 : 1.0;

  auto k_shell = chunk.subshell( id::ElectronSubshellID( "K" ) );
  CHECK( id::ElectronSubshellID( "K" ) == k_shell.identifier() );
  CHECK_THAT( 538, WithinRel( k_shell.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( k_shell.population() ) );
  CHECK( true == k_shell.hasRadiativeTransitions() );
  CHECK( true == k_shell.hasNonRadiativeTransitions() );
  CHECK( true == k_shell.hasTransitions() );
  CHECK( 2 == k_shell.numberRadiativeTransitions() );
  CHECK( 6 == k_shell.numberNonRadiativeTransitions() );
  CHECK( 8 == k_shell.numberTransitions() );
  CHECK( 2 == k_shell.radiativeTransitions().size() );
  CHECK( 6 == k_shell.nonRadiativeTransitions().size() );
  CHECK( atomic::TransitionType::Radiative == k_shell.radiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::Radiative == k_shell.radiativeTransitions()[1].type() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.radiativeTransitions()[1].originatingShell() );
  CHECK_THAT( 0.00190768 / normalisation, WithinRel( k_shell.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.00380027 / normalisation, WithinRel( k_shell.radiativeTransitions()[1].probability() ) );
  CHECK_THAT( 523.09, WithinRel( k_shell.radiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 523.13, WithinRel( k_shell.radiativeTransitions()[1].energy().value() ) );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[1].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[2].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[3].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[4].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[5].type() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[5].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[0].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[1].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[2].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[3].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[4].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[5].emittingShell() );
  CHECK_THAT( 0.178644  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.116224  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.230418  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0110822 / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[3].probability() ) );
  CHECK_THAT( 0.291115  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[4].probability() ) );
  CHECK_THAT( 0.166809  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[5].probability() ) );
  CHECK_THAT( 478.82, WithinRel( k_shell.nonRadiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 493.86, WithinRel( k_shell.nonRadiativeTransitions()[1].energy().value() ) );
  CHECK_THAT( 493.9 , WithinRel( k_shell.nonRadiativeTransitions()[2].energy().value() ) );
  CHECK_THAT( 508.9 , WithinRel( k_shell.nonRadiativeTransitions()[3].energy().value() ) );
  CHECK_THAT( 508.94, WithinRel( k_shell.nonRadiativeTransitions()[4].energy().value() ) );
  CHECK_THAT( 508.98, WithinRel( k_shell.nonRadiativeTransitions()[5].energy().value() ) );
  CHECK_THAT( 0.00570795 / normalisation, WithinRel( k_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0.9942922  / normalisation, WithinRel( k_shell.totalNonRadiativeProbability() ) );

  auto l1_shell = chunk.subshell( id::ElectronSubshellID( "L1" ) );
  CHECK( id::ElectronSubshellID( "L1" ) == l1_shell.identifier() );
  CHECK_THAT( 28.48, WithinRel( l1_shell.bindingEnergy() ) );
  CHECK_THAT( 2.   , WithinRel( l1_shell.population() ) );
  CHECK( false == l1_shell.hasRadiativeTransitions() );
  CHECK( false == l1_shell.hasNonRadiativeTransitions() );
  CHECK( false == l1_shell.hasTransitions() );
  CHECK( 0 == l1_shell.numberRadiativeTransitions() );
  CHECK( 0 == l1_shell.numberNonRadiativeTransitions() );
  CHECK( 0 == l1_shell.numberTransitions() );
  CHECK( 0 == l1_shell.radiativeTransitions().size() );
  CHECK( 0 == l1_shell.nonRadiativeTransitions().size() );
  CHECK_THAT( 0., WithinRel( l1_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( l1_shell.totalNonRadiativeProbability() ) );

  auto l2_shell = chunk.subshell( id::ElectronSubshellID( "L2" ) );
  CHECK( id::ElectronSubshellID( "L2" ) == l2_shell.identifier() );
  CHECK_THAT( 13.62, WithinRel( l2_shell.bindingEnergy() ) );
  CHECK_THAT( 1.33 , WithinRel( l2_shell.population() ) );
  CHECK( false == l2_shell.hasRadiativeTransitions() );
  CHECK( false == l2_shell.hasNonRadiativeTransitions() );
  CHECK( false == l2_shell.hasTransitions() );
  CHECK( 0 == l2_shell.numberRadiativeTransitions() );
  CHECK( 0 == l2_shell.numberNonRadiativeTransitions() );
  CHECK( 0 == l2_shell.numberTransitions() );
  CHECK( 0 == l2_shell.radiativeTransitions().size() );
  CHECK( 0 == l2_shell.nonRadiativeTransitions().size() );
  CHECK_THAT( 0., WithinRel( l2_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( l2_shell.totalNonRadiativeProbability() ) );

  auto l3_shell = chunk.subshell( id::ElectronSubshellID( "L3" ) );
  CHECK( id::ElectronSubshellID( "L3" ) == l3_shell.identifier() );
  CHECK_THAT( 13.62, WithinRel( l3_shell.bindingEnergy() ) );
  CHECK_THAT( 2.67 , WithinRel( l3_shell.population() ) );
  CHECK( false == l3_shell.hasRadiativeTransitions() );
  CHECK( false == l3_shell.hasNonRadiativeTransitions() );
  CHECK( false == l3_shell.hasTransitions() );
  CHECK( 0 == l3_shell.numberRadiativeTransitions() );
  CHECK( 0 == l3_shell.numberNonRadiativeTransitions() );
  CHECK( 0 == l3_shell.numberTransitions() );
  CHECK( 0 == l3_shell.radiativeTransitions().size() );
  CHECK( 0 == l3_shell.nonRadiativeTransitions().size() );
  CHECK_THAT( 0., WithinRel( l3_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( l3_shell.totalNonRadiativeProbability() ) );

  k_shell = chunk.subshells()[0];
  CHECK( id::ElectronSubshellID( "K" ) == k_shell.identifier() );
  CHECK_THAT( 538, WithinRel( k_shell.bindingEnergy() ) );
  CHECK_THAT( 2. , WithinRel( k_shell.population() ) );
  CHECK( true == k_shell.hasRadiativeTransitions() );
  CHECK( true == k_shell.hasNonRadiativeTransitions() );
  CHECK( true == k_shell.hasTransitions() );
  CHECK( 2 == k_shell.numberRadiativeTransitions() );
  CHECK( 6 == k_shell.numberNonRadiativeTransitions() );
  CHECK( 8 == k_shell.numberTransitions() );
  CHECK( 2 == k_shell.radiativeTransitions().size() );
  CHECK( 6 == k_shell.nonRadiativeTransitions().size() );
  CHECK( atomic::TransitionType::Radiative == k_shell.radiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::Radiative == k_shell.radiativeTransitions()[1].type() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.radiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.radiativeTransitions()[1].originatingShell() );
  CHECK_THAT( 0.00190768 / normalisation, WithinRel( k_shell.radiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.00380027 / normalisation, WithinRel( k_shell.radiativeTransitions()[1].probability() ) );
  CHECK_THAT( 523.09, WithinRel( k_shell.radiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 523.13, WithinRel( k_shell.radiativeTransitions()[1].energy().value() ) );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[0].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[1].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[2].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[3].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[4].type() );
  CHECK( atomic::TransitionType::NonRadiative == k_shell.nonRadiativeTransitions()[5].type() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[0].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[1].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[2].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[3].originatingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[4].originatingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[5].originatingShell() );
  CHECK( id::ElectronSubshellID( "L1" ) == k_shell.nonRadiativeTransitions()[0].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[1].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[2].emittingShell() );
  CHECK( id::ElectronSubshellID( "L2" ) == k_shell.nonRadiativeTransitions()[3].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[4].emittingShell() );
  CHECK( id::ElectronSubshellID( "L3" ) == k_shell.nonRadiativeTransitions()[5].emittingShell() );
  CHECK_THAT( 0.178644  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[0].probability() ) );
  CHECK_THAT( 0.116224  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[1].probability() ) );
  CHECK_THAT( 0.230418  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[2].probability() ) );
  CHECK_THAT( 0.0110822 / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[3].probability() ) );
  CHECK_THAT( 0.291115  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[4].probability() ) );
  CHECK_THAT( 0.166809  / normalisation, WithinRel( k_shell.nonRadiativeTransitions()[5].probability() ) );
  CHECK_THAT( 478.82, WithinRel( k_shell.nonRadiativeTransitions()[0].energy().value() ) );
  CHECK_THAT( 493.86, WithinRel( k_shell.nonRadiativeTransitions()[1].energy().value() ) );
  CHECK_THAT( 493.9 , WithinRel( k_shell.nonRadiativeTransitions()[2].energy().value() ) );
  CHECK_THAT( 508.9 , WithinRel( k_shell.nonRadiativeTransitions()[3].energy().value() ) );
  CHECK_THAT( 508.94, WithinRel( k_shell.nonRadiativeTransitions()[4].energy().value() ) );
  CHECK_THAT( 508.98, WithinRel( k_shell.nonRadiativeTransitions()[5].energy().value() ) );
  CHECK_THAT( 0.00570795 / normalisation, WithinRel( k_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0.9942922  / normalisation, WithinRel( k_shell.totalNonRadiativeProbability() ) );

  l1_shell = chunk.subshells()[1];
  CHECK( id::ElectronSubshellID( "L1" ) == l1_shell.identifier() );
  CHECK_THAT( 28.48, WithinRel( l1_shell.bindingEnergy() ) );
  CHECK_THAT( 2.   , WithinRel( l1_shell.population() ) );
  CHECK( false == l1_shell.hasRadiativeTransitions() );
  CHECK( false == l1_shell.hasNonRadiativeTransitions() );
  CHECK( false == l1_shell.hasTransitions() );
  CHECK( 0 == l1_shell.numberRadiativeTransitions() );
  CHECK( 0 == l1_shell.numberNonRadiativeTransitions() );
  CHECK( 0 == l1_shell.numberTransitions() );
  CHECK( 0 == l1_shell.radiativeTransitions().size() );
  CHECK( 0 == l1_shell.nonRadiativeTransitions().size() );
  CHECK_THAT( 0., WithinRel( l1_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( l1_shell.totalNonRadiativeProbability() ) );

  l2_shell = chunk.subshells()[2];
  CHECK( id::ElectronSubshellID( "L2" ) == l2_shell.identifier() );
  CHECK_THAT( 13.62, WithinRel( l2_shell.bindingEnergy() ) );
  CHECK_THAT( 1.33 , WithinRel( l2_shell.population() ) );
  CHECK( false == l2_shell.hasRadiativeTransitions() );
  CHECK( false == l2_shell.hasNonRadiativeTransitions() );
  CHECK( false == l2_shell.hasTransitions() );
  CHECK( 0 == l2_shell.numberRadiativeTransitions() );
  CHECK( 0 == l2_shell.numberNonRadiativeTransitions() );
  CHECK( 0 == l2_shell.numberTransitions() );
  CHECK( 0 == l2_shell.radiativeTransitions().size() );
  CHECK( 0 == l2_shell.nonRadiativeTransitions().size() );
  CHECK_THAT( 0., WithinRel( l2_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( l2_shell.totalNonRadiativeProbability() ) );

  l3_shell = chunk.subshells()[3];
  CHECK( id::ElectronSubshellID( "L3" ) == l3_shell.identifier() );
  CHECK_THAT( 13.62, WithinRel( l3_shell.bindingEnergy() ) );
  CHECK_THAT( 2.67 , WithinRel( l3_shell.population() ) );
  CHECK( false == l3_shell.hasRadiativeTransitions() );
  CHECK( false == l3_shell.hasNonRadiativeTransitions() );
  CHECK( false == l3_shell.hasTransitions() );
  CHECK( 0 == l3_shell.numberRadiativeTransitions() );
  CHECK( 0 == l3_shell.numberNonRadiativeTransitions() );
  CHECK( 0 == l3_shell.numberTransitions() );
  CHECK( 0 == l3_shell.radiativeTransitions().size() );
  CHECK( 0 == l3_shell.nonRadiativeTransitions().size() );
  CHECK_THAT( 0., WithinRel( l3_shell.totalRadiativeProbability() ) );
  CHECK_THAT( 0., WithinRel( l3_shell.totalNonRadiativeProbability() ) );

  CHECK_THROWS( chunk.subshell( id::ElectronSubshellID( "M1" ) ) );
}
