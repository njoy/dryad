# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.atomic import TransitionType
from dryad.atomic import RadiativeTransitionData
from dryad.atomic import NonRadiativeTransitionData
from dryad.atomic import ElectronSubshellConfiguration
from dryad.id import ElectronSubshellID

class Test_dryad_ElectronSubshellConfiguration( unittest.TestCase ) :
    """Unit test for the ElectronSubshellConfiguration class."""

    def test_component( self ) :

        def verify_chunk_without_transitions( self, chunk ) :

            self.assertEqual( ElectronSubshellID( 'K' ), chunk.identifier )
            self.assertAlmostEqual( 538, chunk.binding_energy )
            self.assertAlmostEqual( 2, chunk.population )

            self.assertEqual( False, chunk.has_radiative_transitions )
            self.assertEqual( False, chunk.has_non_radiative_transitions )
            self.assertEqual( False, chunk.has_transitions )

            self.assertEqual( 0, chunk.number_radiative_transitions )
            self.assertEqual( 0, chunk.number_non_radiative_transitions )
            self.assertEqual( 0, chunk.number_transitions )
            self.assertEqual( 0, len( chunk.radiative_transitions ) )
            self.assertEqual( 0, len( chunk.non_radiative_transitions ) )

            self.assertAlmostEqual( 0, chunk.total_radiative_probability )
            self.assertAlmostEqual( 0, chunk.total_non_radiative_probability )

        def verify_chunk_with_transitions( self, chunk ) :

            self.assertEqual( ElectronSubshellID( 'K' ), chunk.identifier )
            self.assertAlmostEqual( 538, chunk.binding_energy )
            self.assertAlmostEqual( 2, chunk.population )

            self.assertEqual( True, chunk.has_radiative_transitions )
            self.assertEqual( True, chunk.has_non_radiative_transitions )
            self.assertEqual( True, chunk.has_transitions )

            self.assertEqual( 2, chunk.number_radiative_transitions )
            self.assertEqual( 6, chunk.number_non_radiative_transitions )
            self.assertEqual( 8, chunk.number_transitions )
            self.assertEqual( 2, len( chunk.radiative_transitions ) )
            self.assertEqual( 6, len( chunk.non_radiative_transitions ) )

            self.assertEqual( TransitionType.Radiative, chunk.radiative_transitions[0].type )
            self.assertEqual( TransitionType.Radiative, chunk.radiative_transitions[1].type )
            self.assertEqual( ElectronSubshellID( 'L2' ), chunk.radiative_transitions[0].originating_shell )
            self.assertEqual( ElectronSubshellID( 'L3' ), chunk.radiative_transitions[1].originating_shell )
            self.assertAlmostEqual( 0.00190768, chunk.radiative_transitions[0].probability )
            self.assertAlmostEqual( 0.00380027, chunk.radiative_transitions[1].probability )
            self.assertAlmostEqual( 523.09, chunk.radiative_transitions[0].energy )
            self.assertAlmostEqual( 523.13, chunk.radiative_transitions[1].energy )

            self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[0].type )
            self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[1].type )
            self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[2].type )
            self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[3].type )
            self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[4].type )
            self.assertEqual( TransitionType.NonRadiative, chunk.non_radiative_transitions[5].type )
            self.assertEqual( ElectronSubshellID( 'L1' ), chunk.non_radiative_transitions[0].originating_shell )
            self.assertEqual( ElectronSubshellID( 'L1' ), chunk.non_radiative_transitions[1].originating_shell )
            self.assertEqual( ElectronSubshellID( 'L1' ), chunk.non_radiative_transitions[2].originating_shell )
            self.assertEqual( ElectronSubshellID( 'L2' ), chunk.non_radiative_transitions[3].originating_shell )
            self.assertEqual( ElectronSubshellID( 'L2' ), chunk.non_radiative_transitions[4].originating_shell )
            self.assertEqual( ElectronSubshellID( 'L3' ), chunk.non_radiative_transitions[5].originating_shell )
            self.assertEqual( ElectronSubshellID( 'L1' ), chunk.non_radiative_transitions[0].emitting_shell )
            self.assertEqual( ElectronSubshellID( 'L2' ), chunk.non_radiative_transitions[1].emitting_shell )
            self.assertEqual( ElectronSubshellID( 'L3' ), chunk.non_radiative_transitions[2].emitting_shell )
            self.assertEqual( ElectronSubshellID( 'L2' ), chunk.non_radiative_transitions[3].emitting_shell )
            self.assertEqual( ElectronSubshellID( 'L3' ), chunk.non_radiative_transitions[4].emitting_shell )
            self.assertEqual( ElectronSubshellID( 'L3' ), chunk.non_radiative_transitions[5].emitting_shell )
            self.assertAlmostEqual( 0.178644 , chunk.non_radiative_transitions[0].probability )
            self.assertAlmostEqual( 0.116224 , chunk.non_radiative_transitions[1].probability )
            self.assertAlmostEqual( 0.230418 , chunk.non_radiative_transitions[2].probability )
            self.assertAlmostEqual( 0.0110822, chunk.non_radiative_transitions[3].probability )
            self.assertAlmostEqual( 0.291115 , chunk.non_radiative_transitions[4].probability )
            self.assertAlmostEqual( 0.166809 , chunk.non_radiative_transitions[5].probability )
            self.assertAlmostEqual( 478.82, chunk.non_radiative_transitions[0].energy )
            self.assertAlmostEqual( 493.86, chunk.non_radiative_transitions[1].energy )
            self.assertAlmostEqual( 493.9 , chunk.non_radiative_transitions[2].energy )
            self.assertAlmostEqual( 508.9 , chunk.non_radiative_transitions[3].energy )
            self.assertAlmostEqual( 508.94, chunk.non_radiative_transitions[4].energy )
            self.assertAlmostEqual( 508.98, chunk.non_radiative_transitions[5].energy )

            self.assertAlmostEqual( 0.00570795, chunk.total_radiative_probability )
            self.assertAlmostEqual( 0.9942922 , chunk.total_non_radiative_probability )

        # the data is given explicitly for a non-radiative transition without a transition energy
        chunk = ElectronSubshellConfiguration( id = ElectronSubshellID( 'K' ), energy = 538, population = 2. )

        verify_chunk_without_transitions( self, chunk )

        # the data is given explicitly for a non- radiative transition without a transition energy
        chunk = ElectronSubshellConfiguration( id = ElectronSubshellID( 'K' ), energy = 538, population = 2.,
                                               radiative = [ RadiativeTransitionData( ElectronSubshellID( 'L2' ), 0.00190768, 523.09 ),
                                                             RadiativeTransitionData( ElectronSubshellID( 'L3' ), 0.00380027, 523.13 ) ],
                                               non_radiative = [ NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L1' ), 0.178644 , 478.82 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L2' ), 0.116224 , 493.86 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L1' ), ElectronSubshellID( 'L3' ), 0.230418 , 493.9 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L2' ), 0.0110822, 508.9 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L2' ), ElectronSubshellID( 'L3' ), 0.291115 , 508.94 ),
                                                                 NonRadiativeTransitionData( ElectronSubshellID( 'L3' ), ElectronSubshellID( 'L3' ), 0.166809 , 508.98 ) ] )

        verify_chunk_with_transitions( self, chunk )

if __name__ == '__main__' :

    unittest.main()
