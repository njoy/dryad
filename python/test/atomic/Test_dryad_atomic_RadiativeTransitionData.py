# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.atomic import TransitionType
from dryad.atomic import RadiativeTransitionData
from dryad.id import ElectronSubshellID

class Test_dryad_RadiativeTransitionData( unittest.TestCase ) :
    """Unit test for the RadiativeTransitionData class."""

    def test_component( self ) :

        def verify_chunk_without_transition_energy( self, chunk ) :

            self.assertEqual( TransitionType.Radiative, chunk.type )
            self.assertEqual( ElectronSubshellID( 'K' ), chunk.originating_shell )
            self.assertAlmostEqual( 1e-3, chunk.probability )
            self.assertEqual( None, chunk.energy )

        def verify_chunk_with_transition_energy( self, chunk ) :

            self.assertEqual( TransitionType.Radiative, chunk.type )
            self.assertEqual( ElectronSubshellID( 'K' ), chunk.originating_shell )
            self.assertAlmostEqual( 1e-3, chunk.probability )
            self.assertAlmostEqual( 550, chunk.energy )

        # the data is given explicitly for a radiative transition without a transition energy
        chunk = RadiativeTransitionData( originating_shell = ElectronSubshellID( 'K' ), probability = 1e-3 )

        verify_chunk_without_transition_energy( self, chunk )

        # the data is given explicitly for a radiative transition without a transition energy
        chunk = RadiativeTransitionData( originating_shell = ElectronSubshellID( 'K' ), probability = 1e-3, energy = 550 )

        verify_chunk_with_transition_energy( self, chunk )

if __name__ == '__main__' :

    unittest.main()
