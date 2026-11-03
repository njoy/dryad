# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import UniformAngularDistribution
from njoy.dryad import UniformAngularDistributions
from njoy.dryad import UniformDistributionType
from njoy.dryad import InterpolationType

class Test_UniformAngularDistributions( unittest.TestCase ) :
    """Unit test for the UniformAngularDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

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
            self.assertAlmostEqual( 0.5 , chunk.distributions[0].cosines[1] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[1].cosines[0] )
            self.assertAlmostEqual( 0.02, chunk.distributions[1].cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[1].cosines[2] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[2].cosines[0] )
            self.assertAlmostEqual( 0.2 , chunk.distributions[2].cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[2].cosines[2] )
            self.assertAlmostEqual( -1. , chunk.distributions[3].cosines[0] )
            self.assertAlmostEqual( 0.8 , chunk.distributions[3].cosines[1] )
            self.assertAlmostEqual( 1. , chunk.distributions[3].cosines[2] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_curated )

            # average cosines
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
            self.assertAlmostEqual( 0. , cosines.values[0] )
            self.assertAlmostEqual( 0.02 / 3., cosines.values[1] )
            self.assertAlmostEqual( 0.2 / 3. , cosines.values[2] )
            self.assertAlmostEqual( 0.8 / 3. , cosines.values[3] )
            self.assertEqual( 3, cosines.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, cosines.interpolants[0] )
            self.assertEqual( True, cosines.is_linearised )

        def verify_chunk_with_jump_curated( self, chunk ) :

            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.grid ) )
            self.assertEqual( 5, len( chunk.distributions ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 2., chunk.grid[2] )
            self.assertAlmostEqual( 3., chunk.grid[3] )
            self.assertAlmostEqual( 4., chunk.grid[4] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[0].cosines[0] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[0].cosines[1] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[1].cosines[0] )
            self.assertAlmostEqual( 0.02, chunk.distributions[1].cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[1].cosines[2] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[2].cosines[0] )
            self.assertAlmostEqual( 1.0 , chunk.distributions[2].cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[2].cosines[2] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[3].cosines[0] )
            self.assertAlmostEqual( 0.2 , chunk.distributions[3].cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[3].cosines[2] )
            self.assertAlmostEqual( -1. , chunk.distributions[4].cosines[0] )
            self.assertAlmostEqual( 0.8 , chunk.distributions[4].cosines[1] )
            self.assertAlmostEqual( 1. , chunk.distributions[4].cosines[2] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk_with_jump_not_curated( self, chunk ) :

            self.assertEqual( 6, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 6, len( chunk.grid ) )
            self.assertEqual( 6, len( chunk.distributions ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.grid[0] )
            self.assertAlmostEqual( 2., chunk.grid[1] )
            self.assertAlmostEqual( 2., chunk.grid[2] )
            self.assertAlmostEqual( 2., chunk.grid[3] )
            self.assertAlmostEqual( 3., chunk.grid[4] )
            self.assertAlmostEqual( 4., chunk.grid[5] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[0].cosines[0] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[0].cosines[1] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[1].cosines[0] )
            self.assertAlmostEqual( 0.02, chunk.distributions[1].cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[1].cosines[2] )
            self.assertAlmostEqual( -0.9 , chunk.distributions[2].cosines[0] )
            self.assertAlmostEqual( 0.8 , chunk.distributions[2].cosines[1] )
            self.assertAlmostEqual( 0.9 , chunk.distributions[2].cosines[2] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[3].cosines[0] )
            self.assertAlmostEqual( 1.0 , chunk.distributions[3].cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[3].cosines[2] )
            self.assertAlmostEqual( -0.5 , chunk.distributions[4].cosines[0] )
            self.assertAlmostEqual( 0.2 , chunk.distributions[4].cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[4].cosines[2] )
            self.assertAlmostEqual( -1. , chunk.distributions[5].cosines[0] )
            self.assertAlmostEqual( 0.8 , chunk.distributions[5].cosines[1] )
            self.assertAlmostEqual( 1. , chunk.distributions[5].cosines[2] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_curated )

        # linearised data without boundaries and no jumps

        chunk = UniformAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                             distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ],
                                             interpolant = InterpolationType.LinearLinear )

        # a UniformAngularDistributions can be constructed and members can be tested
        verify_chunk( self, chunk )

        # linearised data with a jump that consist of more than 2 points (curate is not requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump are kept. boundaries always point to the first point
        # in the jump, regardless of curation.

        chunk = UniformAngularDistributions( grid = [ 1., 2., 2., 2., 3., 4. ],
                                             distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.9, 0.8, 0.9 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 1., 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ] )

        # a UniformAngularDistributions can be constructed and members can be tested
        verify_chunk_with_jump_not_curated( self, chunk )

        # the table can be curated on demand and the extraneous points are removed
        chunk.curate()

        verify_chunk_with_jump_curated( self, chunk )

        # linearised data with a jump that consist of more than 2 points (curate is requested)
        # note: by default (curate = false), the extraneous points in between the first and
        # last x value in the jump are kept. boundaries always point to the first point
        # in the jump, regardless of curation.

        chunk = UniformAngularDistributions( grid = [ 1., 2., 2., 2., 3., 4. ],
                                             distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.9, 0.8, 0.9 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 1., 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ],
                                             interpolant = InterpolationType.LinearLinear,
                                             curate = True )

        # a UniformAngularDistributions can be constructed and members can be tested
        verify_chunk_with_jump_curated( self, chunk )

        # calling curate() again on an already curated table does not change anything
        chunk.curate()

        verify_chunk_with_jump_curated( self, chunk )

        # data with a jump at the beginning
        # note: at construction time, the first point is removed

        chunk = UniformAngularDistributions( grid = [ 1., 1., 2., 3., 4. ],
                                             distributions = [ UniformAngularDistribution( [ -0.5, 1., 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ] )

        # a UniformAngularDistributions can be constructed and members can be tested
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
        self.assertAlmostEqual( 0.5 , chunk.distributions[0].cosines[1] )
        self.assertAlmostEqual( -0.5 , chunk.distributions[1].cosines[0] )
        self.assertAlmostEqual( 0.02, chunk.distributions[1].cosines[1] )
        self.assertAlmostEqual( 0.5 , chunk.distributions[1].cosines[2] )
        self.assertAlmostEqual( -0.5 , chunk.distributions[2].cosines[0] )
        self.assertAlmostEqual( 0.2 , chunk.distributions[2].cosines[1] )
        self.assertAlmostEqual( 0.5 , chunk.distributions[2].cosines[2] )
        self.assertAlmostEqual( -1. , chunk.distributions[3].cosines[0] )
        self.assertAlmostEqual( 0.8 , chunk.distributions[3].cosines[1] )
        self.assertAlmostEqual( 1. , chunk.distributions[3].cosines[2] )
        self.assertEqual( 3, chunk.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

        # data with a jump at the end
        # note: at construction time, the last point is removed

        chunk = UniformAngularDistributions( grid = [ 1., 2., 3., 4., 4. ],
                                             distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ),
                                                               UniformAngularDistribution( [ -0.5, 1., 0.5 ], UniformDistributionType.Discrete ) ] )

        # a UniformAngularDistributions can be constructed and members can be tested
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
        self.assertAlmostEqual( 0.5 , chunk.distributions[0].cosines[1] )
        self.assertAlmostEqual( -0.5 , chunk.distributions[1].cosines[0] )
        self.assertAlmostEqual( 0.02, chunk.distributions[1].cosines[1] )
        self.assertAlmostEqual( 0.5 , chunk.distributions[1].cosines[2] )
        self.assertAlmostEqual( -0.5 , chunk.distributions[2].cosines[0] )
        self.assertAlmostEqual( 0.2 , chunk.distributions[2].cosines[1] )
        self.assertAlmostEqual( 0.5 , chunk.distributions[2].cosines[2] )
        self.assertAlmostEqual( -1. , chunk.distributions[3].cosines[0] )
        self.assertAlmostEqual( 0.8 , chunk.distributions[3].cosines[1] )
        self.assertAlmostEqual( 1. , chunk.distributions[3].cosines[2] )
        self.assertEqual( 3, chunk.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

    def test_comparison( self ) :

        left = UniformAngularDistributions( [ 1., 2., 3., 4. ],
                                            [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                              UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                              UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                              UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ] )
        equal = UniformAngularDistributions( [ 1., 2., 3., 4. ],
                                             [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                               UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                               UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                               UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ] )
        different = UniformAngularDistributions( [ 1., 4. ],
                                                 [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                   UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ] )

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

            chunk = UniformAngularDistributions( grid = [], distributions = [] )

        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ) ] )

        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ) ] )

        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1. ],
                                                 distributions = [] )

        # the x and f(y) grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ) ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ],
                                                 boundaries = [ 3 ],
                                                 interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 3., 2., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = UniformAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                                 distributions = [ UniformAngularDistribution( [ -0.5, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.02, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -0.5, 0.2, 0.5 ], UniformDistributionType.Discrete ),
                                                                   UniformAngularDistribution( [ -1., 0.8, 1. ], UniformDistributionType.Discrete ) ],
                                                 boundaries = [ 2 ],
                                                 interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
