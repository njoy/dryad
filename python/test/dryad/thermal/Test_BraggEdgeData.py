# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import BraggEdgeData

def verify_chunk( self, chunk ) :

    self.assertAlmostEqual( 293.6, chunk.temperature )

    self.assertEqual( 2, len( chunk.energies ) )
    self.assertEqual( 2, len( chunk.values ) )

    self.assertAlmostEqual( 5.219736e-3, chunk.energies[0] )
    self.assertAlmostEqual( 5.         , chunk.energies[1] )
    self.assertAlmostEqual( 8.703783e-3, chunk.values[0] )
    self.assertAlmostEqual( 9.484639e-1, chunk.values[1] )

class Test_BraggEdgeData( unittest.TestCase ) :
    """Unit test for the BraggEdgeData class."""

    def test_component( self ) :

        chunk = BraggEdgeData( temperature = 293.6,
                              energies = [ 5.219736e-3, 5. ],
                              values = [ 8.703783e-3, 9.484639e-1 ] )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = BraggEdgeData( temperature = 293.6,
                             energies = [ 5.219736e-3, 5. ],
                            values = [ 8.703783e-3, 9.484639e-1 ] )
        equal = BraggEdgeData( temperature = 293.6,
                              energies = [ 5.219736e-3, 5. ],
                              values = [ 8.703783e-3, 9.484639e-1 ] )
        different = BraggEdgeData( temperature = 300,
                              energies = [ 5.219736e-3 ],
                              values = [ 8.703783e-3 ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
