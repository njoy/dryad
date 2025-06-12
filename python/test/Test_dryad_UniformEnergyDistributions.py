# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import UniformEnergyDistribution
from dryad import UniformEnergyDistributions
from dryad import UniformDistributionType
from dryad import InterpolationType

class Test_dryad_UniformEnergyDistributions( unittest.TestCase ) :
    """Unit test for the UniformEnergyDistribution class."""

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
            self.assertAlmostEqual(  0.5, chunk.distributions[0].energies[0] )
            self.assertAlmostEqual(  1. , chunk.distributions[0].energies[1] )
            self.assertAlmostEqual(  4. , chunk.distributions[0].energies[2] )
            self.assertAlmostEqual(  6. , chunk.distributions[0].energies[3] )
            self.assertAlmostEqual(  1. , chunk.distributions[1].energies[0] )
            self.assertAlmostEqual(  2. , chunk.distributions[1].energies[1] )
            self.assertAlmostEqual(  3. , chunk.distributions[2].energies[0] )
            self.assertAlmostEqual(  5. , chunk.distributions[2].energies[1] )
            self.assertAlmostEqual(  7. , chunk.distributions[2].energies[2] )
            self.assertAlmostEqual(  5. , chunk.distributions[3].energies[0] )
            self.assertAlmostEqual( 10. , chunk.distributions[3].energies[1] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            # verify average energies
            energies = chunk.average_energies
            self.assertAlmostEqual( 1., energies.lower_energy_limit )
            self.assertAlmostEqual( 4., energies.upper_energy_limit )
            self.assertEqual( 4, energies.number_points )
            self.assertEqual( 1, energies.number_regions )
            self.assertEqual( 4, len( energies.energies ) )
            self.assertEqual( 4, len( energies.values ) )
            self.assertEqual( 1, len( energies.boundaries ) )
            self.assertEqual( 1, len( energies.interpolants ) )
            self.assertAlmostEqual( 1., energies.energies[0] )
            self.assertAlmostEqual( 2., energies.energies[1] )
            self.assertAlmostEqual( 3., energies.energies[2] )
            self.assertAlmostEqual( 4., energies.energies[3] )
            self.assertAlmostEqual( 2.875, energies.values[0] )
            self.assertAlmostEqual( 1.5  , energies.values[1] )
            self.assertAlmostEqual( 5.   , energies.values[2] )
            self.assertAlmostEqual( 7.5  , energies.values[3] )
            self.assertEqual( 3, energies.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, energies.interpolants[0] )
            self.assertEqual( True, energies.is_linearised )

        # the data is given explicitly
        chunk = UniformEnergyDistributions( grid = [ 1., 2., 3., 4. ],
                                               distributions = [ UniformEnergyDistribution( [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ),
                                                                 UniformEnergyDistribution( [ 1., 2. ], UniformDistributionType.Discrete ),
                                                                 UniformEnergyDistribution( [ 3., 5., 7. ], UniformDistributionType.Discrete ),
                                                                 UniformEnergyDistribution( [ 5., 10. ], UniformDistributionType.Discrete ) ],
                                               interpolant = InterpolationType.LinearLinear )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = UniformEnergyDistributions( [ 1., 2., 3., 4. ],
                                           [ UniformEnergyDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                             UniformEnergyDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                             UniformEnergyDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                             UniformEnergyDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ] )
        equal = UniformEnergyDistributions( [ 1., 2., 3., 4. ],
                                            [ UniformEnergyDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                              UniformEnergyDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                              UniformEnergyDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                              UniformEnergyDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ] )
        different = UniformEnergyDistributions( [ 1., 4. ],
                                                [ UniformEnergyDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                  UniformEnergyDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or f(y) grid
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [], distributions = [] )

        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [ 1. ],
                                                distributions = [ [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ] )

        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [],
                                                distributions = [ [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ] )

        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [ 1. ], distributions = [] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [ 1., 2., 3., 4. ],
                                                distributions = [ UniformEnergyDistribution( [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 1., 2. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 3., 5., 7. ], UniformDistributionType.Discrete ) ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [ 1., 2., 3., 4. ],
                                                distributions = [ UniformEnergyDistribution( [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 1., 2. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 3., 5., 7. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 5., 10. ], UniformDistributionType.Discrete ) ],
                                                boundaries = [ 3 ],
                                                interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [ 1., 3., 2., 4. ],
                                                distributions = [ UniformEnergyDistribution( [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 1., 2. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 3., 5., 7. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 5., 10. ], UniformDistributionType.Discrete ) ] )

        # the x grid contains a triple x value
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [ 1., 2., 2., 2., 4. ],
                                                distributions = [ UniformEnergyDistribution( [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 1., 2. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 1., 2. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 3., 5., 7. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 5., 10. ], UniformDistributionType.Discrete ) ] )

        # the x grid has a jump at the beginning
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [ 1., 1., 3., 4. ],
                                                distributions = [ UniformEnergyDistribution( [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 1., 2. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 3., 5., 7. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 5., 10. ], UniformDistributionType.Discrete ) ] )

        # the x grid has a jump at the end
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [ 1., 2., 4., 4. ],
                                                distributions = [ UniformEnergyDistribution( [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 1., 2. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 3., 5., 7. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 5., 10. ], UniformDistributionType.Discrete ) ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = UniformEnergyDistributions( grid = [ 1., 2., 3., 4. ],
                                                distributions = [ UniformEnergyDistribution( [ 0.5, 1., 4., 6. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 1., 2. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 3., 5., 7. ], UniformDistributionType.Discrete ),
                                                                  UniformEnergyDistribution( [ 5., 10. ], UniformDistributionType.Discrete ) ],
                                                boundaries = [ 2 ],
                                                interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
