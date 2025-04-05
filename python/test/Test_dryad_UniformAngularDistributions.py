# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import UniformAngularDistribution
from dryad import UniformAngularDistributions
from dryad import UniformDistributionType
from dryad import InterpolationType

class Test_dryad_UniformAngularDistributions( unittest.TestCase ) :
    """Unit test for the UniformAngularDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.grid ) )
            self.assertEqual( 4, len( chunk.distributions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 3., chunk.grid[2] )
            self.assertAlmostEqual( 4., chunk.grid[3] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[0].cosines[0] )
            self.assertAlmostEqual(  0.5 , chunk.distributions[0].cosines[1] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[1].cosines[0] )
            self.assertAlmostEqual(  0.02, chunk.distributions[1].cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.distributions[1].cosines[2] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[2].cosines[0] )
            self.assertAlmostEqual(  0.2 , chunk.distributions[2].cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.distributions[2].cosines[2] )
            self.assertAlmostEqual( -1.  , chunk.distributions[3].cosines[0] )
            self.assertAlmostEqual(  0.8 , chunk.distributions[3].cosines[1] )
            self.assertAlmostEqual(  1.  , chunk.distributions[3].cosines[2] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            # verify average cosines
            cosines = chunk.average_cosines
            self.assertAlmostEqual( 1., cosines.lower_energy_limit )
            self.assertAlmostEqual( 4., cosines.upper_energy_limit )
            self.assertEqual( 4, cosines.number_points )
            self.assertEqual( 1, cosines.number_regions )
            self.assertEqual( 4, len( cosines.energies ) )
            self.assertEqual( 4, len( cosines.values ) )
            self.assertEqual( 1, len( cosines.boundaries ) )
            self.assertEqual( 1, len( cosines.interpolants ) )
            self.assertAlmostEqual( 1., cosines.energies[0] )
            self.assertAlmostEqual( 2., cosines.energies[1] )
            self.assertAlmostEqual( 3., cosines.energies[2] )
            self.assertAlmostEqual( 4., cosines.energies[3] )
            self.assertAlmostEqual( 0.       , cosines.values[0] )
            self.assertAlmostEqual( 0.02 / 3., cosines.values[1] )
            self.assertAlmostEqual( 0.2 / 3. , cosines.values[2] )
            self.assertAlmostEqual( 0.8 / 3. , cosines.values[3] )
            self.assertEqual( 3, cosines.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cosines.interpolants[0] )
            self.assertEqual( True, cosines.is_linearised )

        # the data is given explicitly
        chunk = UniformAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                             distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ],
                                             interpolant = InterpolationType.LinearLinear )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or f(y) grid
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [], distributions = [] )

        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1. ],
                                                 distributions = [ [ -0.5, 0.5 ], UniformDistributionType.Discrete ] )

        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [],
                                                 distributions = [ [ -0.5, 0.5 ], UniformDistributionType.Discrete ] )

        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1. ], distributions = [] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ) ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ) ],
                                                 boundaries = [ 3 ],
                                                 interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 3., 2., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ) ] )

        # the x grid contains a triple x value
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 2., 2., 2., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ) ] )

        # the x grid has a jump at the beginning
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 1., 3., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ) ] )

        # the x grid has a jump at the end
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 2., 4., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ) ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ) ],
                                                 boundaries = [ 2 ],
                                                 interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
