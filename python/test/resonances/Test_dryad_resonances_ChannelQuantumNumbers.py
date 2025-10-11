# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.resonances import ChannelQuantumNumbers

class Test_dryad_resonances_ChannelQuantumNumbers( unittest.TestCase ) :
    """Unit test for the ChannelQuantumNumbers class."""

    def test_component( self ) :

        # the data is given explicitly
        chunk = ChannelQuantumNumbers( l = 1, s = 0.5, J = 1.5, parity = +1 )

        self.assertEqual( 1, chunk.orbital_angular_momentum )
        self.assertEqual( 0.5, chunk.spin )
        self.assertEqual( 1.5, chunk.total_angular_momentum )
        self.assertEqual( +1, chunk.parity )

    def test_comparison( self ) :

        left = ChannelQuantumNumbers( l = 1, s = 0.5, J = 1.5, parity = +1 )
        equal = ChannelQuantumNumbers( l = 1, s = 0.5, J = 1.5, parity = +1 )
        different = ChannelQuantumNumbers( l = 0, s = 0.5, J = 1.5, parity = -1 )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
