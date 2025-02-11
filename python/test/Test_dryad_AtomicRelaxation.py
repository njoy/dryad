# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import AtomicRelaxation
from dryad.id import ElementID
from dryad.atomic import TransitionType
from dryad.atomic import ElectronSubshellConfiguration
from dryad.atomic import RadiativeTransitionData
from dryad.atomic import NonRadiativeTransitionData

class Test_dryad_AtomicRelaxation( unittest.TestCase ) :
    """Unit test for the AtomicRelaxation class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # identifiers
            self.assertEqual( ElementID( 1 ), chunk.element_identifier )

            # subshell configuration data
            self.assertEqual( 4, len( chunk.subshells ) )

            self.assertEqual( True, chunk.has_subshell( 'K' ) )
            self.assertEqual( True, chunk.has_subshell( 'L1' ) )
            self.assertEqual( True, chunk.has_subshell( 'L2' ) )
            self.assertEqual( True, chunk.has_subshell( 'L3' ) )
            self.assertEqual( False, chunk.has_subshell( 'M1' ) )

            k_shell = chunk.subshell( 'K' )
            self.assertEqual( 'K', k_shell.identifier )
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
            self.assertEqual( 'L2', k_shell.radiative_transitions[0].originating_shell )
            self.assertEqual( 'L3', k_shell.radiative_transitions[1].originating_shell )
            self.assertAlmostEqual( 0.00190768, k_shell.radiative_transitions[0].probability )
            self.assertAlmostEqual( 0.00380027, k_shell.radiative_transitions[1].probability )
            self.assertAlmostEqual( 523.09, k_shell.radiative_transitions[0].energy )
            self.assertAlmostEqual( 523.13, k_shell.radiative_transitions[1].energy )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[0].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[1].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[2].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[3].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[4].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[5].type )
            self.assertEqual( 'L1', k_shell.non_radiative_transitions[0].originating_shell )
            self.assertEqual( 'L1', k_shell.non_radiative_transitions[1].originating_shell )
            self.assertEqual( 'L1', k_shell.non_radiative_transitions[2].originating_shell )
            self.assertEqual( 'L2', k_shell.non_radiative_transitions[3].originating_shell )
            self.assertEqual( 'L2', k_shell.non_radiative_transitions[4].originating_shell )
            self.assertEqual( 'L3', k_shell.non_radiative_transitions[5].originating_shell )
            self.assertEqual( 'L1', k_shell.non_radiative_transitions[0].emitting_shell )
            self.assertEqual( 'L2', k_shell.non_radiative_transitions[1].emitting_shell )
            self.assertEqual( 'L3', k_shell.non_radiative_transitions[2].emitting_shell )
            self.assertEqual( 'L2', k_shell.non_radiative_transitions[3].emitting_shell )
            self.assertEqual( 'L3', k_shell.non_radiative_transitions[4].emitting_shell )
            self.assertEqual( 'L3', k_shell.non_radiative_transitions[5].emitting_shell )
            self.assertAlmostEqual( 0.178644 , k_shell.non_radiative_transitions[0].probability )
            self.assertAlmostEqual( 0.116224 , k_shell.non_radiative_transitions[1].probability )
            self.assertAlmostEqual( 0.230418 , k_shell.non_radiative_transitions[2].probability )
            self.assertAlmostEqual( 0.0110822, k_shell.non_radiative_transitions[3].probability )
            self.assertAlmostEqual( 0.291115 , k_shell.non_radiative_transitions[4].probability )
            self.assertAlmostEqual( 0.166809 , k_shell.non_radiative_transitions[5].probability )
            self.assertAlmostEqual( 478.82, k_shell.non_radiative_transitions[0].energy )
            self.assertAlmostEqual( 493.86, k_shell.non_radiative_transitions[1].energy )
            self.assertAlmostEqual( 493.9 , k_shell.non_radiative_transitions[2].energy )
            self.assertAlmostEqual( 508.9 , k_shell.non_radiative_transitions[3].energy )
            self.assertAlmostEqual( 508.94, k_shell.non_radiative_transitions[4].energy )
            self.assertAlmostEqual( 508.98, k_shell.non_radiative_transitions[5].energy )
            self.assertAlmostEqual( 0.00570795, k_shell.total_radiative_probability )
            self.assertAlmostEqual( 0.9942922 , k_shell.total_non_radiative_probability )

            l1_shell = chunk.subshell( 'L1' )
            self.assertEqual( 'L1', l1_shell.identifier )
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

            l2_shell = chunk.subshell( 'L2' )
            self.assertEqual( 'L2', l2_shell.identifier )
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

            l3_shell = chunk.subshell( 'L3' )
            self.assertEqual( 'L3', l3_shell.identifier )
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
            self.assertEqual( 'K', k_shell.identifier )
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
            self.assertEqual( 'L2', k_shell.radiative_transitions[0].originating_shell )
            self.assertEqual( 'L3', k_shell.radiative_transitions[1].originating_shell )
            self.assertAlmostEqual( 0.00190768, k_shell.radiative_transitions[0].probability )
            self.assertAlmostEqual( 0.00380027, k_shell.radiative_transitions[1].probability )
            self.assertAlmostEqual( 523.09, k_shell.radiative_transitions[0].energy )
            self.assertAlmostEqual( 523.13, k_shell.radiative_transitions[1].energy )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[0].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[1].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[2].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[3].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[4].type )
            self.assertEqual( TransitionType.NonRadiative, k_shell.non_radiative_transitions[5].type )
            self.assertEqual( 'L1', k_shell.non_radiative_transitions[0].originating_shell )
            self.assertEqual( 'L1', k_shell.non_radiative_transitions[1].originating_shell )
            self.assertEqual( 'L1', k_shell.non_radiative_transitions[2].originating_shell )
            self.assertEqual( 'L2', k_shell.non_radiative_transitions[3].originating_shell )
            self.assertEqual( 'L2', k_shell.non_radiative_transitions[4].originating_shell )
            self.assertEqual( 'L3', k_shell.non_radiative_transitions[5].originating_shell )
            self.assertEqual( 'L1', k_shell.non_radiative_transitions[0].emitting_shell )
            self.assertEqual( 'L2', k_shell.non_radiative_transitions[1].emitting_shell )
            self.assertEqual( 'L3', k_shell.non_radiative_transitions[2].emitting_shell )
            self.assertEqual( 'L2', k_shell.non_radiative_transitions[3].emitting_shell )
            self.assertEqual( 'L3', k_shell.non_radiative_transitions[4].emitting_shell )
            self.assertEqual( 'L3', k_shell.non_radiative_transitions[5].emitting_shell )
            self.assertAlmostEqual( 0.178644 , k_shell.non_radiative_transitions[0].probability )
            self.assertAlmostEqual( 0.116224 , k_shell.non_radiative_transitions[1].probability )
            self.assertAlmostEqual( 0.230418 , k_shell.non_radiative_transitions[2].probability )
            self.assertAlmostEqual( 0.0110822, k_shell.non_radiative_transitions[3].probability )
            self.assertAlmostEqual( 0.291115 , k_shell.non_radiative_transitions[4].probability )
            self.assertAlmostEqual( 0.166809 , k_shell.non_radiative_transitions[5].probability )
            self.assertAlmostEqual( 478.82, k_shell.non_radiative_transitions[0].energy )
            self.assertAlmostEqual( 493.86, k_shell.non_radiative_transitions[1].energy )
            self.assertAlmostEqual( 493.9 , k_shell.non_radiative_transitions[2].energy )
            self.assertAlmostEqual( 508.9 , k_shell.non_radiative_transitions[3].energy )
            self.assertAlmostEqual( 508.94, k_shell.non_radiative_transitions[4].energy )
            self.assertAlmostEqual( 508.98, k_shell.non_radiative_transitions[5].energy )
            self.assertAlmostEqual( 0.00570795, k_shell.total_radiative_probability )
            self.assertAlmostEqual( 0.9942922 , k_shell.total_non_radiative_probability )

            l1_shell = chunk.subshells[1]
            self.assertEqual( 'L1', l1_shell.identifier )
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
            self.assertEqual( 'L2', l2_shell.identifier )
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
            self.assertEqual( 'L3', l3_shell.identifier )
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

        # the data is given explicitly
        chunk = AtomicRelaxation(
                    element = ElementID( 1 ),
                    subshells = [ ElectronSubshellConfiguration(
                                    'K', 538, 2,
                                    [ RadiativeTransitionData( 'L2', 0.00190768, 523.09 ),
                                      RadiativeTransitionData( 'L3', 0.00380027, 523.13 ) ],
                                    [ NonRadiativeTransitionData( 'L1', 'L1', 0.178644, 478.82 ),
                                      NonRadiativeTransitionData( 'L1', 'L2', 0.116224, 493.86 ),
                                      NonRadiativeTransitionData( 'L1', 'L3', 0.230418, 493.9 ),
                                      NonRadiativeTransitionData( 'L2', 'L2', 0.0110822, 508.9 ),
                                      NonRadiativeTransitionData( 'L2', 'L3', 0.291115, 508.94 ),
                                      NonRadiativeTransitionData( 'L3', 'L3', 0.166809, 508.98 ) ]
                                  ),
                                  ElectronSubshellConfiguration( 'L1', 28.48, 2 ),
                                  ElectronSubshellConfiguration( 'L2', 13.62, 1.33 ),
                                  ElectronSubshellConfiguration( 'L3', 13.62, 2.67 ) ] )

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()
