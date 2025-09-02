# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import AtomicRelaxation
from dryad.id import ElementID
from dryad.id import ElectronSubshellID
from dryad.atomic import TransitionType
from dryad.atomic import ElectronSubshellConfiguration
from dryad.atomic import RadiativeTransitionData
from dryad.atomic import NonRadiativeTransitionData

def verify_chunk( self, chunk, normalise ) :

    self.assertIsNone( chunk.documentation.awr )
    self.assertIsNone( chunk.documentation.library )
    self.assertIsNone( chunk.documentation.version )
    self.assertIsNone( chunk.documentation.description )

    # identifiers
    self.assertEqual( ElementID( 1 ), chunk.element_identifier )

    # subshell configuration data
    self.assertEqual( 4, len( chunk.subshells ) )

    self.assertEqual( True, chunk.has_subshell( ElectronSubshellID( 'K' ) ) )
    self.assertEqual( True, chunk.has_subshell( ElectronSubshellID( 'L1' ) ) )
    self.assertEqual( True, chunk.has_subshell( ElectronSubshellID( 'L2' ) ) )
    self.assertEqual( True, chunk.has_subshell( ElectronSubshellID( 'L3' ) ) )
    self.assertEqual( False, chunk.has_subshell( ElectronSubshellID( 'M1' ) ) )

    normalisation = 1.00000015 if normalise else 1.0

    k_shell = chunk.subshell( ElectronSubshellID( 'K' ) )
    self.assertEqual( ElectronSubshellID( 'K' ), k_shell.identifier )
    self.assertAlmostEqual( 538, k_shell.binding_energy )
    self.assertAlmostEqual( 2, k_shell.population )
    self.assertEqual( True, k_shell.has_radiative_transitions )
    self.assertEqual( True, k_shell.has_non_radiative_transitions )
    self.assertEqual( True, k_shell.has_transitions )
    self.assertEqual( 2, k_shell.number_radiative_transitions )
    self.assertEqual( 6, k_shell.number_non_radiative_transitions )
    self.assertEqual( 8, k_shell.number_transitions )
    self.assertEqual( 2, len( k_shell.radiative_transitions ) )
    self.assertEqual( 6, len( k_shell.non_radiative_transitions ) )
    self.assertEqual( TransitionType.Radiative, k_shell.radiative_transitions[0].type )
    self.assertEqual( TransitionType.Radiative, k_shell.radiative_transitions[1].type )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.radiative_transitions[0].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.radiative_transitions[1].originating_shell )
    self.assertAlmostEqual( 0.00190768 / normalisation, k_shell.radiative_transitions[0].probability )
    self.assertAlmostEqual( 0.00380027 / normalisation, k_shell.radiative_transitions[1].probability )
    self.assertAlmostEqual( 523.09, k_shell.radiative_transitions[0].energy )
    self.assertAlmostEqual( 523.13, k_shell.radiative_transitions[1].energy )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[0].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[1].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[2].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[3].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[4].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[5].type )
    self.assertEqual( ElectronSubshellID( 'L1' ), k_shell.non_radiative_transitions[0].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L1' ), k_shell.non_radiative_transitions[1].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L1' ), k_shell.non_radiative_transitions[2].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.non_radiative_transitions[3].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.non_radiative_transitions[4].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.non_radiative_transitions[5].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L1' ), k_shell.non_radiative_transitions[0].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.non_radiative_transitions[1].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.non_radiative_transitions[2].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.non_radiative_transitions[3].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.non_radiative_transitions[4].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.non_radiative_transitions[5].emitting_shell )
    self.assertAlmostEqual( 0.178644  / normalisation, k_shell.non_radiative_transitions[0].probability )
    self.assertAlmostEqual( 0.116224  / normalisation, k_shell.non_radiative_transitions[1].probability )
    self.assertAlmostEqual( 0.230418  / normalisation, k_shell.non_radiative_transitions[2].probability )
    self.assertAlmostEqual( 0.0110822 / normalisation, k_shell.non_radiative_transitions[3].probability )
    self.assertAlmostEqual( 0.291115  / normalisation, k_shell.non_radiative_transitions[4].probability )
    self.assertAlmostEqual( 0.166809  / normalisation, k_shell.non_radiative_transitions[5].probability )
    self.assertAlmostEqual( 478.82, k_shell.non_radiative_transitions[0].energy )
    self.assertAlmostEqual( 493.86, k_shell.non_radiative_transitions[1].energy )
    self.assertAlmostEqual( 493.9 , k_shell.non_radiative_transitions[2].energy )
    self.assertAlmostEqual( 508.9 , k_shell.non_radiative_transitions[3].energy )
    self.assertAlmostEqual( 508.94, k_shell.non_radiative_transitions[4].energy )
    self.assertAlmostEqual( 508.98, k_shell.non_radiative_transitions[5].energy )
    self.assertAlmostEqual( 0.00570795 / normalisation, k_shell.total_radiative_probability )
    self.assertAlmostEqual( 0.9942922  / normalisation, k_shell.total_non_radiative_probability )

    l1_shell = chunk.subshell( ElectronSubshellID( 'L1' ) )
    self.assertEqual( ElectronSubshellID( 'L1' ), l1_shell.identifier )
    self.assertAlmostEqual( 28.48, l1_shell.binding_energy )
    self.assertAlmostEqual( 2.   , l1_shell.population )
    self.assertEqual( False, l1_shell.has_radiative_transitions )
    self.assertEqual( False, l1_shell.has_non_radiative_transitions )
    self.assertEqual( False, l1_shell.has_transitions )
    self.assertEqual( 0, l1_shell.number_radiative_transitions )
    self.assertEqual( 0, l1_shell.number_non_radiative_transitions )
    self.assertEqual( 0, l1_shell.number_transitions )
    self.assertEqual( 0, len( l1_shell.radiative_transitions ) )
    self.assertEqual( 0, len( l1_shell.non_radiative_transitions ) )
    self.assertAlmostEqual( 0, l1_shell.total_radiative_probability )
    self.assertAlmostEqual( 0, l1_shell.total_non_radiative_probability )

    l2_shell = chunk.subshell( ElectronSubshellID( 'L2' ) )
    self.assertEqual( ElectronSubshellID( 'L2' ), l2_shell.identifier )
    self.assertAlmostEqual( 13.62, l2_shell.binding_energy )
    self.assertAlmostEqual( 1.33 , l2_shell.population )
    self.assertEqual( False, l2_shell.has_radiative_transitions )
    self.assertEqual( False, l2_shell.has_non_radiative_transitions )
    self.assertEqual( False, l2_shell.has_transitions )
    self.assertEqual( 0, l2_shell.number_radiative_transitions )
    self.assertEqual( 0, l2_shell.number_non_radiative_transitions )
    self.assertEqual( 0, l2_shell.number_transitions )
    self.assertEqual( 0, len( l2_shell.radiative_transitions ) )
    self.assertEqual( 0, len( l2_shell.non_radiative_transitions ) )
    self.assertAlmostEqual( 0, l2_shell.total_radiative_probability )
    self.assertAlmostEqual( 0, l2_shell.total_non_radiative_probability )

    l3_shell = chunk.subshell( ElectronSubshellID( 'L3' ) )
    self.assertEqual( ElectronSubshellID( 'L3' ), l3_shell.identifier )
    self.assertAlmostEqual( 13.62, l3_shell.binding_energy )
    self.assertAlmostEqual( 2.67 , l3_shell.population )
    self.assertEqual( False, l3_shell.has_radiative_transitions )
    self.assertEqual( False, l3_shell.has_non_radiative_transitions )
    self.assertEqual( False, l3_shell.has_transitions )
    self.assertEqual( 0, l3_shell.number_radiative_transitions )
    self.assertEqual( 0, l3_shell.number_non_radiative_transitions )
    self.assertEqual( 0, l3_shell.number_transitions )
    self.assertEqual( 0, len( l3_shell.radiative_transitions ) )
    self.assertEqual( 0, len( l3_shell.non_radiative_transitions ) )
    self.assertAlmostEqual( 0, l3_shell.total_radiative_probability )
    self.assertAlmostEqual( 0, l3_shell.total_non_radiative_probability )

    k_shell = chunk.subshells[0]
    self.assertEqual( ElectronSubshellID( 'K' ), k_shell.identifier )
    self.assertAlmostEqual( 538, k_shell.binding_energy )
    self.assertAlmostEqual( 2, k_shell.population )
    self.assertEqual( True, k_shell.has_radiative_transitions )
    self.assertEqual( True, k_shell.has_non_radiative_transitions )
    self.assertEqual( True, k_shell.has_transitions )
    self.assertEqual( 2, k_shell.number_radiative_transitions )
    self.assertEqual( 6, k_shell.number_non_radiative_transitions )
    self.assertEqual( 8, k_shell.number_transitions )
    self.assertEqual( 2, len( k_shell.radiative_transitions ) )
    self.assertEqual( 6, len( k_shell.non_radiative_transitions ) )
    self.assertEqual( TransitionType.Radiative, k_shell.radiative_transitions[0].type )
    self.assertEqual( TransitionType.Radiative, k_shell.radiative_transitions[1].type )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.radiative_transitions[0].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.radiative_transitions[1].originating_shell )
    self.assertAlmostEqual( 0.00190768 / normalisation, k_shell.radiative_transitions[0].probability )
    self.assertAlmostEqual( 0.00380027 / normalisation, k_shell.radiative_transitions[1].probability )
    self.assertAlmostEqual( 523.09, k_shell.radiative_transitions[0].energy )
    self.assertAlmostEqual( 523.13, k_shell.radiative_transitions[1].energy )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[0].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[1].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[2].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[3].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[4].type )
    self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[5].type )
    self.assertEqual( ElectronSubshellID( 'L1' ), k_shell.non_radiative_transitions[0].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L1' ), k_shell.non_radiative_transitions[1].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L1' ), k_shell.non_radiative_transitions[2].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.non_radiative_transitions[3].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.non_radiative_transitions[4].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.non_radiative_transitions[5].originating_shell )
    self.assertEqual( ElectronSubshellID( 'L1' ), k_shell.non_radiative_transitions[0].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.non_radiative_transitions[1].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.non_radiative_transitions[2].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L2' ), k_shell.non_radiative_transitions[3].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.non_radiative_transitions[4].emitting_shell )
    self.assertEqual( ElectronSubshellID( 'L3' ), k_shell.non_radiative_transitions[5].emitting_shell )
    self.assertAlmostEqual( 0.178644  / normalisation, k_shell.non_radiative_transitions[0].probability )
    self.assertAlmostEqual( 0.116224  / normalisation, k_shell.non_radiative_transitions[1].probability )
    self.assertAlmostEqual( 0.230418  / normalisation, k_shell.non_radiative_transitions[2].probability )
    self.assertAlmostEqual( 0.0110822 / normalisation, k_shell.non_radiative_transitions[3].probability )
    self.assertAlmostEqual( 0.291115  / normalisation, k_shell.non_radiative_transitions[4].probability )
    self.assertAlmostEqual( 0.166809  / normalisation, k_shell.non_radiative_transitions[5].probability )
    self.assertAlmostEqual( 478.82, k_shell.non_radiative_transitions[0].energy )
    self.assertAlmostEqual( 493.86, k_shell.non_radiative_transitions[1].energy )
    self.assertAlmostEqual( 493.9 , k_shell.non_radiative_transitions[2].energy )
    self.assertAlmostEqual( 508.9 , k_shell.non_radiative_transitions[3].energy )
    self.assertAlmostEqual( 508.94, k_shell.non_radiative_transitions[4].energy )
    self.assertAlmostEqual( 508.98, k_shell.non_radiative_transitions[5].energy )
    self.assertAlmostEqual( 0.00570795 / normalisation, k_shell.total_radiative_probability )
    self.assertAlmostEqual( 0.9942922  / normalisation, k_shell.total_non_radiative_probability )

    l1_shell = chunk.subshells[1]
    self.assertEqual( ElectronSubshellID( 'L1' ), l1_shell.identifier )
    self.assertAlmostEqual( 28.48, l1_shell.binding_energy )
    self.assertAlmostEqual( 2.   , l1_shell.population )
    self.assertEqual( False, l1_shell.has_radiative_transitions )
    self.assertEqual( False, l1_shell.has_non_radiative_transitions )
    self.assertEqual( False, l1_shell.has_transitions )
    self.assertEqual( 0, l1_shell.number_radiative_transitions )
    self.assertEqual( 0, l1_shell.number_non_radiative_transitions )
    self.assertEqual( 0, l1_shell.number_transitions )
    self.assertEqual( 0, len( l1_shell.radiative_transitions ) )
    self.assertEqual( 0, len( l1_shell.non_radiative_transitions ) )
    self.assertAlmostEqual( 0, l1_shell.total_radiative_probability )
    self.assertAlmostEqual( 0, l1_shell.total_non_radiative_probability )

    l2_shell = chunk.subshells[2]
    self.assertEqual( ElectronSubshellID( 'L2' ), l2_shell.identifier )
    self.assertAlmostEqual( 13.62, l2_shell.binding_energy )
    self.assertAlmostEqual( 1.33 , l2_shell.population )
    self.assertEqual( False, l2_shell.has_radiative_transitions )
    self.assertEqual( False, l2_shell.has_non_radiative_transitions )
    self.assertEqual( False, l2_shell.has_transitions )
    self.assertEqual( 0, l2_shell.number_radiative_transitions )
    self.assertEqual( 0, l2_shell.number_non_radiative_transitions )
    self.assertEqual( 0, l2_shell.number_transitions )
    self.assertEqual( 0, len( l2_shell.radiative_transitions ) )
    self.assertEqual( 0, len( l2_shell.non_radiative_transitions ) )
    self.assertAlmostEqual( 0, l2_shell.total_radiative_probability )
    self.assertAlmostEqual( 0, l2_shell.total_non_radiative_probability )

    l3_shell = chunk.subshells[3]
    self.assertEqual( ElectronSubshellID( 'L3' ), l3_shell.identifier )
    self.assertAlmostEqual( 13.62, l3_shell.binding_energy )
    self.assertAlmostEqual( 2.67 , l3_shell.population )
    self.assertEqual( False, l3_shell.has_radiative_transitions )
    self.assertEqual( False, l3_shell.has_non_radiative_transitions )
    self.assertEqual( False, l3_shell.has_transitions )
    self.assertEqual( 0, l3_shell.number_radiative_transitions )
    self.assertEqual( 0, l3_shell.number_non_radiative_transitions )
    self.assertEqual( 0, l3_shell.number_transitions )
    self.assertEqual( 0, len( l3_shell.radiative_transitions ) )
    self.assertEqual( 0, len( l3_shell.non_radiative_transitions ) )
    self.assertAlmostEqual( 0, l3_shell.total_radiative_probability )
    self.assertAlmostEqual( 0, l3_shell.total_non_radiative_probability )

def verify_transition_energies( self, chunk ) :

    self.assertAlmostEqual( 538 - 13.62        , chunk.subshells[0].radiative_transitions[0].energy )
    self.assertAlmostEqual( 538 - 13.62        , chunk.subshells[0].radiative_transitions[1].energy )
    self.assertAlmostEqual( 538 - 28.48 - 28.48, chunk.subshells[0].non_radiative_transitions[0].energy )
    self.assertAlmostEqual( 538 - 28.48 - 13.62, chunk.subshells[0].non_radiative_transitions[1].energy )
    self.assertAlmostEqual( 538 - 28.48 - 13.62, chunk.subshells[0].non_radiative_transitions[2].energy )
    self.assertAlmostEqual( 538 - 13.62 - 13.62, chunk.subshells[0].non_radiative_transitions[3].energy )
    self.assertAlmostEqual( 538 - 13.62 - 13.62, chunk.subshells[0].non_radiative_transitions[4].energy )
    self.assertAlmostEqual( 538 - 13.62 - 13.62, chunk.subshells[0].non_radiative_transitions[5].energy )

class Test_dryad_AtomicRelaxation( unittest.TestCase ) :
    """Unit test for the AtomicRelaxation class."""

    def test_component( self ) :

        # the data is given explicitly - no normalisation
        chunk = AtomicRelaxation(
                    element = ElementID( 1 ),
                    subshells = [ ElectronSubshellConfiguration(
                                    ElectronSubshellID( 'K' ), 538, 2,
                                    [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                                      RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                                    [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644, 478.82 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224, 493.86 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418, 493.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115, 508.94 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809, 508.98 ) ],
                                    False
                                  ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L1' ), 28.48, 2 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L2' ), 13.62, 1.33 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L3' ), 13.62, 2.67 ) ],
                    normalise = False )

        verify_chunk( self, chunk, False )

        chunk.normalise()

        verify_chunk( self, chunk, True )

        chunk.calculate_transition_energies()

        verify_transition_energies( self, chunk )

        # the data is given explicitly - with normalisation
        chunk = AtomicRelaxation(
                    element = ElementID( 1 ),
                    subshells = [ ElectronSubshellConfiguration(
                                    ElectronSubshellID( 'K' ), 538, 2,
                                    [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                                      RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                                    [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644, 478.82 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224, 493.86 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418, 493.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115, 508.94 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809, 508.98 ) ],
                                    False
                                  ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L1' ), 28.48, 2 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L2' ), 13.62, 1.33 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L3' ), 13.62, 2.67 ) ],
                    normalise = True )

        verify_chunk( self, chunk, True )

        chunk.normalise()

        verify_chunk( self, chunk, True )

        chunk.calculate_transition_energies()

        verify_transition_energies( self, chunk )

    def test_setter_functions( self ) :

        chunk = AtomicRelaxation(
                    element = ElementID( 1 ),
                    subshells = [ ElectronSubshellConfiguration(
                                    ElectronSubshellID( 'K' ), 538, 2,
                                    [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                                      RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                                    [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644, 478.82 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224, 493.86 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418, 493.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115, 508.94 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809, 508.98 ) ] ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L1' ), 28.48, 2 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L2' ), 13.62, 1.33 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L3' ), 13.62, 2.67 ) ]  )

        # the originating shell can be changed
        newid =  ElementID( 2 )
        original =  ElementID( 1 )

        chunk.element_identifier = newid

        self.assertEqual( newid, chunk.element_identifier )

        chunk.element_identifier = original

        verify_chunk( self, chunk, False )

        # the subshells can be changed
        newsubshells = [ ElectronSubshellConfiguration( ElectronSubshellID( 'M1' ), 5000, 2 ) ]
        original = [ ElectronSubshellConfiguration(
                           ElectronSubshellID( 'K' ), 538, 2,
                           [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                             RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                           [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644, 478.82 ),
                             NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224, 493.86 ),
                             NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418, 493.9 ),
                             NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                             NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115, 508.94 ),
                             NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809, 508.98 ) ],
                           False
                         ),
                         ElectronSubshellConfiguration( ElectronSubshellID( 'L1' ), 28.48, 2 ),
                         ElectronSubshellConfiguration( ElectronSubshellID( 'L2' ), 13.62, 1.33 ),
                         ElectronSubshellConfiguration( ElectronSubshellID( 'L3' ), 13.62, 2.67 ) ]

        chunk.subshells = newsubshells

        self.assertEqual( newsubshells, chunk.subshells )

        chunk.subshells = original

        verify_chunk( self, chunk, False )

    def test_comparison( self ) :

        left = AtomicRelaxation(
                    element = ElementID( 1 ),
                    subshells = [ ElectronSubshellConfiguration(
                                    ElectronSubshellID( 'K' ), 538, 2,
                                    [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                                      RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                                    [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644, 478.82 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224, 493.86 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418, 493.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115, 508.94 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809, 508.98 ) ] ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L1' ), 28.48, 2 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L2' ), 13.62, 1.33 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L3' ), 13.62, 2.67 ) ]  )
        equal = AtomicRelaxation(
                    element = ElementID( 1 ),
                    subshells = [ ElectronSubshellConfiguration(
                                    ElectronSubshellID( 'K' ), 538, 2,
                                    [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                                      RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                                    [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644, 478.82 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224, 493.86 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418, 493.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115, 508.94 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809, 508.98 ) ] ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L1' ), 28.48, 2 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L2' ), 13.62, 1.33 ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L3' ), 13.62, 2.67 ) ]  )
        different = AtomicRelaxation(
                    element = ElementID( 1 ),
                    subshells = [ ElectronSubshellConfiguration(
                                    ElectronSubshellID( 'K' ), 538, 2,
                                    [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                                      RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                                    [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644, 478.82 ),
                                      NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809, 508.98 ) ] ),
                                  ElectronSubshellConfiguration( ElectronSubshellID( 'L3' ), 13.62, 2.67 ) ]  )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
