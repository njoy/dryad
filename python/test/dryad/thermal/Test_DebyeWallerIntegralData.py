# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import DebyeWallerIntegralData

def verify_chunk( self, chunk ) :

    self.assertEqual( 4, len( chunk.temperatures ) )
    self.assertEqual( 4, len( chunk.values ) )

    self.assertAlmostEqual( 1., chunk.temperatures[0] )
    self.assertAlmostEqual( 2., chunk.temperatures[1] )
    self.assertAlmostEqual( 3., chunk.temperatures[2] )
    self.assertAlmostEqual( 4., chunk.temperatures[3] )
    self.assertAlmostEqual( 4., chunk.values[0] )
    self.assertAlmostEqual( 3., chunk.values[1] )
    self.assertAlmostEqual( 2., chunk.values[2] )
    self.assertAlmostEqual( 1., chunk.values[3] )

class Test_DebyeWallerIntegralData( unittest.TestCase ) :
    """Unit test for the DebyeWallerIntegralData class."""

    def test_component( self ) :

        chunk = DebyeWallerIntegralData( temperatures = [ 1., 2., 3., 4. ],
                                         values = [ 4., 3., 2., 1. ] )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = DebyeWallerIntegralData( temperatures = [ 1., 2., 3., 4. ],
                                        values = [ 4., 3., 2., 1. ] )
        equal = DebyeWallerIntegralData( temperatures = [ 1., 2., 3., 4. ],
                                         values = [ 4., 3., 2., 1. ] )
        different = DebyeWallerIntegralData( temperatures = [ 1., 2. ],
                                             values = [ 4., 3. ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
