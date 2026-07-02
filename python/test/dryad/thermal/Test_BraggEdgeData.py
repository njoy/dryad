# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import BraggEdgeData
from njoy.dryad import InterpolationType

def verify_chunk( self, chunk ) :

    self.assertAlmostEqual( 293.6, chunk.temperature )

    self.assertEqual( 2, chunk.number_bragg_edges )
    self.assertEqual( 2, len( chunk.energies ) )
    self.assertEqual( 2, len( chunk.values ) )

    self.assertAlmostEqual( 5.219736e-3, chunk.energies[0] )
    self.assertAlmostEqual( 5.         , chunk.energies[1] )
    self.assertAlmostEqual( 8.703783e-3, chunk.values[0] )
    self.assertAlmostEqual( 9.484639e-1, chunk.values[1] )

    xs = chunk.cross_section( 10. )
    self.assertEqual( 4, xs.number_points )
    self.assertEqual( 2, xs.number_regions )
    self.assertEqual( 4, len( xs.energies ) )
    self.assertEqual( 4, len( xs.values ) )
    self.assertEqual( 2, len( xs.boundaries ) )
    self.assertEqual( 2, len( xs.interpolants ) )
    self.assertAlmostEqual( 5.219736e-3, xs.energies[0] )
    self.assertAlmostEqual( 5.         , xs.energies[1] )
    self.assertAlmostEqual( 5.         , xs.energies[2] )
    self.assertAlmostEqual( 10.        , xs.energies[3] )
    self.assertAlmostEqual( 8.703783e-3 / 5.219736e-3, xs.values[0] )
    self.assertAlmostEqual( 8.703783e-3 / 5.         , xs.values[1] )
    self.assertAlmostEqual( 9.484639e-1 / 5.         , xs.values[2] )
    self.assertAlmostEqual( 9.484639e-1 / 10.        , xs.values[3] )
    self.assertEqual( 1, xs.boundaries[0] )
    self.assertEqual( 3, xs.boundaries[1] )
    self.assertEqual( InterpolationType.LogLog, xs.interpolants[0] )
    self.assertEqual( InterpolationType.LogLog, xs.interpolants[0] )

    xs = chunk.cross_section( 5. )
    self.assertEqual( 2, xs.number_points )
    self.assertEqual( 1, xs.number_regions )
    self.assertEqual( 2, len( xs.energies ) )
    self.assertEqual( 2, len( xs.values ) )
    self.assertEqual( 1, len( xs.boundaries ) )
    self.assertEqual( 1, len( xs.interpolants ) )
    self.assertAlmostEqual( 5.219736e-3, xs.energies[0] )
    self.assertAlmostEqual( 5.         , xs.energies[1] )
    self.assertAlmostEqual( 8.703783e-3 / 5.219736e-3, xs.values[0] )
    self.assertAlmostEqual( 8.703783e-3 / 5.         , xs.values[1] )
    self.assertEqual( 1, xs.boundaries[0] )
    self.assertEqual( InterpolationType.LogLog, xs.interpolants[0] )

    xs = chunk.cross_section( 4. )
    self.assertEqual( 2, xs.number_points )
    self.assertEqual( 1, xs.number_regions )
    self.assertEqual( 2, len( xs.energies ) )
    self.assertEqual( 2, len( xs.values ) )
    self.assertEqual( 1, len( xs.boundaries ) )
    self.assertEqual( 1, len( xs.interpolants ) )
    self.assertAlmostEqual( 5.219736e-3, xs.energies[0] )
    self.assertAlmostEqual( 4.         , xs.energies[1] )
    self.assertAlmostEqual( 8.703783e-3 / 5.219736e-3, xs.values[0] )
    self.assertAlmostEqual( 8.703783e-3 / 4.         , xs.values[1] )
    self.assertEqual( 1, xs.boundaries[0] )
    self.assertEqual( InterpolationType.LogLog, xs.interpolants[0] )

    with self.assertRaises( Exception ) : xs = chunk.cross_section( 1e-5 )

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
