# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad.resonances import ChannelQuantumNumbers

class Test_dryad_resonances_ChannelQuantumNumbers( unittest.TestCase ) :
    """Unit test for the ChannelQuantumNumbers class."""

    def test_component( self ) :

        # the data is given as number
        chunk = ChannelQuantumNumbers( l = 1, s = 0.5, J = 1.5, parity = +1 )

        self.assertEqual( 1, chunk.orbital_angular_momentum )
        self.assertEqual( 0.5, chunk.spin )
        self.assertEqual( 1.5, chunk.total_angular_momentum )
        self.assertEqual( +1, chunk.parity )

        # the data is given as a string
        chunk = ChannelQuantumNumbers( '{1,1/2,3/2+}' )

        self.assertEqual( 1, chunk.orbital_angular_momentum )
        self.assertEqual( 0.5, chunk.spin )
        self.assertEqual( 1.5, chunk.total_angular_momentum )
        self.assertEqual( +1, chunk.parity )

    def test_allowed_channel_spin_values( self ) :

        # i=0.0, I=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_channel_spin_values( i = 0, I = 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 0., values[0] )

        values = ChannelQuantumNumbers.allowed_channel_spin_values( i = 0, I = 0.5 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )

        values = ChannelQuantumNumbers.allowed_channel_spin_values( i = 0, I = 1 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 1., values[0] )

        # i=0.5, I=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_channel_spin_values( i = 0.5, I = 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )

        values = ChannelQuantumNumbers.allowed_channel_spin_values( i = 0.5, I = 0.5 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 0., values[0] )
        self.assertAlmostEqual( 1., values[1] )

        values = ChannelQuantumNumbers.allowed_channel_spin_values( i = 0.5, I = 1 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )
        self.assertAlmostEqual( 1.5, values[1] )

        # i=1., I=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_channel_spin_values( i = 1, I = 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 1., values[0] )

        values = ChannelQuantumNumbers.allowed_channel_spin_values( i = 1, I = 0.5 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )
        self.assertAlmostEqual( 1.5, values[1] )

        values = ChannelQuantumNumbers.allowed_channel_spin_values( i = 1, I = 1 )

        self.assertEqual( 3, len( values ) )
        self.assertAlmostEqual( 0., values[0] )
        self.assertAlmostEqual( 1., values[1] )
        self.assertAlmostEqual( 2., values[2] )

    def test_allowed_total_angular_momentum_values( self ) :

        # l,i,I

        # l=0, i=0.0, I=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, i = 0, I = 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 0., values[0] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, i = 0, I = 0.5 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, i = 0, I = 1 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 1., values[0] )

        # l=0, i=0.5, I=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, i = 0.5, I = 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, i = 0.5, I = 0.5 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 0., values[0] )
        self.assertAlmostEqual( 1., values[1] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, i = 0.5, I = 1 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )
        self.assertAlmostEqual( 1.5, values[1] )

        # l=0, i=1.0, I=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, i = 1, I = 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 1., values[0] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, i = 1, I = 0.5 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )
        self.assertAlmostEqual( 1.5, values[1] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, i = 1, I = 1 )

        self.assertEqual( 3, len( values ) )
        self.assertAlmostEqual( 0., values[0] )
        self.assertAlmostEqual( 1., values[1] )
        self.assertAlmostEqual( 2., values[2] )

        # l=1, i=0.0, I=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, i = 0, I = 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 1., values[0] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, i = 0, I = 0.5 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )
        self.assertAlmostEqual( 1.5, values[1] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, i = 0, I = 1 )

        self.assertEqual( 3, len( values ) )
        self.assertAlmostEqual( 0., values[0] )
        self.assertAlmostEqual( 1., values[1] )
        self.assertAlmostEqual( 2., values[2] )

        # l=1, i=0.5, I=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, i = 0.5, I = 0 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )
        self.assertAlmostEqual( 1.5, values[1] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, i = 0.5, I = 0.5 )

        self.assertEqual( 3, len( values ) )
        self.assertAlmostEqual( 0., values[0] )
        self.assertAlmostEqual( 1., values[1] )
        self.assertAlmostEqual( 2., values[2] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, i = 0.5, I = 1 )

        self.assertEqual( 3, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )
        self.assertAlmostEqual( 1.5, values[1] )
        self.assertAlmostEqual( 2.5, values[2] )

        # l=1, i=1.0, I=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, i = 1, I = 0 )

        self.assertEqual( 3, len( values ) )
        self.assertAlmostEqual( 0., values[0] )
        self.assertAlmostEqual( 1., values[1] )
        self.assertAlmostEqual( 2., values[2] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, i = 1, I = 0.5 )

        self.assertEqual( 3, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )
        self.assertAlmostEqual( 1.5, values[1] )
        self.assertAlmostEqual( 2.5, values[2] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, i = 1, I = 1 )

        self.assertEqual( 4, len( values ) )
        self.assertAlmostEqual( 0., values[0] )
        self.assertAlmostEqual( 1., values[1] )
        self.assertAlmostEqual( 2., values[2] )
        self.assertAlmostEqual( 3., values[3] )

        # l,s

        # l=0, s=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, s= 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 0., values[0] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, s = 0.5 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 0, s = 1 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 1., values[0] )

        # l=1, s=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, s= 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 1., values[0] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, s = 0.5 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 0.5, values[0] )
        self.assertAlmostEqual( 1.5, values[1] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 1, s = 1 )

        self.assertEqual( 3, len( values ) )
        self.assertAlmostEqual( 0., values[0] )
        self.assertAlmostEqual( 1., values[1] )
        self.assertAlmostEqual( 2., values[2] )

        # l=2, s=0.0, 0.5, 1.0
        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 2, s= 0 )

        self.assertEqual( 1, len( values ) )
        self.assertAlmostEqual( 2., values[0] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 2, s = 0.5 )

        self.assertEqual( 2, len( values ) )
        self.assertAlmostEqual( 1.5, values[0] )
        self.assertAlmostEqual( 2.5, values[1] )

        values = ChannelQuantumNumbers.allowed_total_angular_momentum_values( l = 2, s = 1 )

        self.assertEqual( 3, len( values ) )
        self.assertAlmostEqual( 1., values[0] )
        self.assertAlmostEqual( 2., values[1] )
        self.assertAlmostEqual( 3., values[2] )

    def test_allowed_channel_quantum_numbers( self ) :

        values = ChannelQuantumNumbers.allowed_channel_quantum_numbers( 0.5, 0, 2 )

        self.assertEqual( 5, len( values ) )
        self.assertEqual( ChannelQuantumNumbers( 1, 0.5, 0.5, -1 ), values[0] )
        self.assertEqual( ChannelQuantumNumbers( 0, 0.5, 0.5, +1 ), values[1] )
        self.assertEqual( ChannelQuantumNumbers( 1, 0.5, 1.5, -1 ), values[2] )
        self.assertEqual( ChannelQuantumNumbers( 2, 0.5, 1.5, +1 ), values[3] )
        self.assertEqual( ChannelQuantumNumbers( 2, 0.5, 2.5, +1 ), values[4] )

        values = ChannelQuantumNumbers.allowed_channel_quantum_numbers( 0.5, 0.5, 2 )

        self.assertEqual( 10, len( values ) )
        self.assertEqual( ChannelQuantumNumbers( 1, 1, 0, -1 ), values[0] )
        self.assertEqual( ChannelQuantumNumbers( 0, 0, 0, +1 ), values[1] )
        self.assertEqual( ChannelQuantumNumbers( 1, 0, 1, -1 ), values[2] )
        self.assertEqual( ChannelQuantumNumbers( 1, 1, 1, -1 ), values[3] )
        self.assertEqual( ChannelQuantumNumbers( 0, 1, 1, +1 ), values[4] )
        self.assertEqual( ChannelQuantumNumbers( 2, 1, 1, +1 ), values[5] )
        self.assertEqual( ChannelQuantumNumbers( 1, 1, 2, -1 ), values[6] )
        self.assertEqual( ChannelQuantumNumbers( 2, 0, 2, +1 ), values[7] )
        self.assertEqual( ChannelQuantumNumbers( 2, 1, 2, +1 ), values[8] )
        self.assertEqual( ChannelQuantumNumbers( 2, 1, 3, +1 ), values[9] )

    def test_comparison( self ) :

        id1 = ChannelQuantumNumbers( 0, 0.5, 0.5, +1 )
        id2 = ChannelQuantumNumbers( 0, 0.5, 1.0, -1 )

        self.assertEqual( id1 <  id1, False )
        self.assertEqual( id1 <= id1, True )
        self.assertEqual( id1 >  id1, False )
        self.assertEqual( id1 >= id1, True )
        self.assertEqual( id1 == id1, True )
        self.assertEqual( id1 != id1, False )
        self.assertEqual( id1 <  id2, True )
        self.assertEqual( id1 <= id2, True )
        self.assertEqual( id1 >  id2, False )
        self.assertEqual( id1 >= id2, False )
        self.assertEqual( id1 == id2, False )
        self.assertEqual( id1 != id2, True )
        self.assertEqual( id2 <  id1, False )
        self.assertEqual( id2 <= id1, False )
        self.assertEqual( id2 >  id1, True )
        self.assertEqual( id2 >= id1, True )
        self.assertEqual( id2 == id1, False )
        self.assertEqual( id2 != id1, True )

if __name__ == '__main__' :

    unittest.main()
