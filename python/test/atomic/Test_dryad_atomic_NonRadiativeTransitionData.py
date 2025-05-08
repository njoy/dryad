# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.atomic import TransitionType
from dryad.atomic import NonRadiativeTransitionData
from dryad.id import ElectronSubshellID

class Test_dryad_NonRadiativeTransitionData( unittest.TestCase ) :
    """Unit test for the NonRadiativeTransitionData class."""

    def test_component( self ) :

        def verify_chunk_without_transition_energy( self, chunk ) :

            self.assertEqual( TransitionType.NonRadiative, chunk.type )
            self.assertEqual( ElectronSubshellID( 'K' ), chunk.originating_shell )
            self.assertEqual( ElectronSubshellID( 'L1' ), chunk.emitting_shell )
            self.assertAlmostEqual( 1e-3, chunk.probability )
            self.assertEqual( None, chunk.energy )

        def verify_chunk_with_transition_energy( self, chunk ) :

            self.assertEqual( TransitionType.NonRadiative, chunk.type )
            self.assertEqual( ElectronSubshellID( 'K' ), chunk.originating_shell )
            self.assertEqual( ElectronSubshellID( 'L1' ), chunk.emitting_shell )
            self.assertAlmostEqual( 1e-3, chunk.probability )
            self.assertAlmostEqual( 550, chunk.energy )

        # the data is given explicitly for a non-radiative transition without a transition energy
        chunk = NonRadiativeTransitionData( originating_shell = ElectronSubshellID( 'K' ),
                                            emitting_shell = ElectronSubshellID( 'L1' ),
                                            probability = 1e-3 )

        verify_chunk_without_transition_energy( self, chunk )

        # the data is given explicitly for a non- radiative transition without a transition energy
        chunk = NonRadiativeTransitionData( originating_shell = ElectronSubshellID( 'K' ),
                                            emitting_shell = ElectronSubshellID( 'L1' ),
                                            probability = 1e-3, energy = 550 )

        verify_chunk_with_transition_energy( self, chunk )

if __name__ == '__main__' :

    unittest.main()
