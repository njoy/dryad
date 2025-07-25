# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.atomic import TransitionType
from dryad.atomic import NonRadiativeTransitionData
from dryad.id import ElectronSubshellID

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

class Test_dryad_NonRadiativeTransitionData( unittest.TestCase ) :
    """Unit test for the NonRadiativeTransitionData class."""

    def test_component( self ) :

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

    def test_setter_functions( self ) :

        chunk = NonRadiativeTransitionData( originating_shell = ElectronSubshellID( 'K' ),
                                            emitting_shell = ElectronSubshellID( 'L1' ),
                                            probability = 1e-3 )

        # the originating shell can be changed
        newid = ElectronSubshellID( 'L1' )
        original = ElectronSubshellID( 'K' )

        chunk.originating_shell = newid

        self.assertEqual( newid, chunk.originating_shell )

        chunk.originating_shell = original

        verify_chunk_without_transition_energy( self, chunk )

        # the emitting shell can be changed
        newid = ElectronSubshellID( 'L3' )
        original = ElectronSubshellID( 'L1' )

        chunk.emitting_shell = newid

        self.assertEqual( newid, chunk.emitting_shell )

        chunk.emitting_shell = original

        verify_chunk_without_transition_energy( self, chunk )

        # the probability can be changed
        newprobability = 0.1
        original = 1e-3

        chunk.probability = newprobability

        self.assertEqual( newprobability, chunk.probability )

        chunk.probability = original

        verify_chunk_without_transition_energy( self, chunk )

        # the transition energy can be changed
        newenergy = 1.0
        original = None

        chunk.energy = newenergy

        self.assertEqual( newenergy, chunk.energy )

        chunk.energy = original

        verify_chunk_without_transition_energy( self, chunk )

    def test_comparison( self ) :

        k_shell = ElectronSubshellID( ElectronSubshellID.K )
        l1_shell = ElectronSubshellID( ElectronSubshellID.L1 )

        left = NonRadiativeTransitionData( k_shell, l1_shell, 1e-3 )
        equal = NonRadiativeTransitionData( k_shell, l1_shell, 1e-3 )
        different = NonRadiativeTransitionData( k_shell, l1_shell, 1e-3, 550. )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
