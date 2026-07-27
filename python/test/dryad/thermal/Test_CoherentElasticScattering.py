# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import CoherentElasticScattering
from njoy.dryad.thermal import BraggEdgeData
from njoy.dryad import InterpolationType

def verify_chunk( self, chunk ) :

    self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
    self.assertAlmostEqual( 10. , chunk.upper_energy_limit )

    self.assertEqual( 2, chunk.number_moderator_temperatures )
    self.assertEqual( 2, len( chunk.moderator_temperatures ) )
    self.assertEqual( 2, len( chunk.bragg_edges ) )

    self.assertAlmostEqual(  293.6, chunk.moderator_temperatures[0] )
    self.assertAlmostEqual(  600. , chunk.moderator_temperatures[1] )

    edge0 = chunk.bragg_edges[0]
    self.assertEqual( 2, edge0.number_bragg_edges )
    self.assertEqual( 2, len( edge0.energies ) )
    self.assertEqual( 2, len( edge0.values ) )
    self.assertAlmostEqual(  293.6, edge0.temperature )
    self.assertAlmostEqual( 5.219736e-3, edge0.energies[0] )
    self.assertAlmostEqual( 5.         , edge0.energies[1] )
    self.assertAlmostEqual( 8.703783e-3, edge0.values[0] )
    self.assertAlmostEqual( 9.484639e-1, edge0.values[1] )

    edge1 = chunk.bragg_edges[1]
    self.assertEqual( 2, edge1.number_bragg_edges )
    self.assertEqual( 2, len( edge1.energies ) )
    self.assertEqual( 2, len( edge1.values ) )
    self.assertAlmostEqual(  600, edge1.temperature )
    self.assertAlmostEqual( 5.219736e-3, edge1.energies[0] )
    self.assertAlmostEqual( 5.         , edge1.energies[1] )
    self.assertAlmostEqual( 1e-2       , edge1.values[0] )
    self.assertAlmostEqual( 1.         , edge1.values[1] )

    edge0 = chunk.bragg_edge_data( 293.6 )
    self.assertEqual( 2, edge0.number_bragg_edges )
    self.assertEqual( 2, len( edge0.energies ) )
    self.assertEqual( 2, len( edge0.values ) )
    self.assertAlmostEqual(  293.6, edge0.temperature )
    self.assertAlmostEqual( 5.219736e-3, edge0.energies[0] )
    self.assertAlmostEqual( 5.         , edge0.energies[1] )
    self.assertAlmostEqual( 8.703783e-3, edge0.values[0] )
    self.assertAlmostEqual( 9.484639e-1, edge0.values[1] )

    edge1 = chunk.bragg_edge_data( 600 )
    self.assertEqual( 2, edge1.number_bragg_edges )
    self.assertEqual( 2, len( edge1.energies ) )
    self.assertEqual( 2, len( edge1.values ) )
    self.assertAlmostEqual(  600, edge1.temperature )
    self.assertAlmostEqual( 5.219736e-3, edge1.energies[0] )
    self.assertAlmostEqual( 5.         , edge1.energies[1] )
    self.assertAlmostEqual( 1e-2       , edge1.values[0] )
    self.assertAlmostEqual( 1.         , edge1.values[1] )

    xs = chunk.cross_section( 293.6 )
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


class Test_CoherentElasticScattering( unittest.TestCase ) :
    """Unit test for the CoherentElasticScattering class."""

    def test_component( self ) :

        chunk = CoherentElasticScattering(
                  lower = 1e-5, upper = 10,
                  bragg_edges = [ BraggEdgeData( 600.0, [ 5.219736e-3, 5. ], [ 1e-2, 1. ] ),
                                  BraggEdgeData( 293.6, [ 5.219736e-3, 5. ], [ 8.703783e-3, 9.484639e-1 ] ) ] )

        verify_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = CoherentElasticScattering(
                  lower = 1e-5, upper = 10,
                  bragg_edges = [ BraggEdgeData( 600.0, [ 5.219736e-3, 5. ], [ 1e-2, 1. ] ),
                                  BraggEdgeData( 293.6, [ 5.219736e-3, 5. ], [ 8.703783e-3, 9.484639e-1 ] ) ] )

        # the bragg edges can be changed
        newedges = [ BraggEdgeData( 300.0, [ 5.219736e-3, 5. ], [ 1e-2, 1. ] ) ]
        original = [ BraggEdgeData( 600.0, [ 5.219736e-3, 5. ], [ 1e-2, 1. ] ),
                     BraggEdgeData( 293.6, [ 5.219736e-3, 5. ], [ 8.703783e-3, 9.484639e-1 ] ) ]

        chunk.bragg_edges = newedges

        self.assertEqual( newedges, chunk.bragg_edges )

        chunk.bragg_edges = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = CoherentElasticScattering(
                   lower = 1e-5, upper = 10,
                   bragg_edges = [ BraggEdgeData( 600.0, [ 5.219736e-3, 5. ], [ 1e-2, 1. ] ),
                                   BraggEdgeData( 293.6, [ 5.219736e-3, 5. ], [ 8.703783e-3, 9.484639e-1 ] ) ] )
        equal = CoherentElasticScattering(
                    lower = 1e-5, upper = 10,
                    bragg_edges = [ BraggEdgeData( 600.0, [ 5.219736e-3, 5. ], [ 1e-2, 1. ] ),
                                    BraggEdgeData( 293.6, [ 5.219736e-3, 5. ], [ 8.703783e-3, 9.484639e-1 ] ) ] )
        different = CoherentElasticScattering(
                      lower = 1e-5, upper = 10,
                      bragg_edges = [ BraggEdgeData( 300.0, [ 5.219736e-3, 5. ], [ 1e-2, 1. ] ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
