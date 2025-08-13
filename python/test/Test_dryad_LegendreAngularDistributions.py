# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import LegendreAngularDistribution
from dryad import LegendreAngularDistributions
from dryad import InterpolationType

class Test_dryad_LegendreAngularDistributions( unittest.TestCase ) :
    """Unit test for the LegendreAngularDistribution class."""

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
            self.assertEqual( 1, len( chunk.distributions[0].pdf.coefficients ) )
            self.assertEqual( 2, len( chunk.distributions[1].pdf.coefficients ) )
            self.assertEqual( 2, len( chunk.distributions[2].pdf.coefficients ) )
            self.assertEqual( 2, len( chunk.distributions[3].pdf.coefficients ) )
            self.assertAlmostEqual( 0.5 , chunk.distributions[0].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[1].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.01, chunk.distributions[1].pdf.coefficients[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[2].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.1 , chunk.distributions[2].pdf.coefficients[1] )
            self.assertAlmostEqual( 0.5 , chunk.distributions[3].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.4 , chunk.distributions[3].pdf.coefficients[1] )
            self.assertEqual( 2, len( chunk.distributions[0].cdf.coefficients ) )
            self.assertEqual( 3, len( chunk.distributions[1].cdf.coefficients ) )
            self.assertEqual( 3, len( chunk.distributions[2].cdf.coefficients ) )
            self.assertEqual( 3, len( chunk.distributions[3].cdf.coefficients ) )
            self.assertAlmostEqual( 0.5               , chunk.distributions[0].cdf.coefficients[0] )
            self.assertAlmostEqual( 0.5               , chunk.distributions[0].cdf.coefficients[1] )
            self.assertAlmostEqual( 0.4966666666666666, chunk.distributions[1].cdf.coefficients[0] )
            self.assertAlmostEqual( 0.5               , chunk.distributions[1].cdf.coefficients[1] )
            self.assertAlmostEqual( 0.0033333333333333, chunk.distributions[1].cdf.coefficients[2] )
            self.assertAlmostEqual( 0.4666666666666666, chunk.distributions[2].cdf.coefficients[0] )
            self.assertAlmostEqual( 0.5               , chunk.distributions[2].cdf.coefficients[1] )
            self.assertAlmostEqual( 0.0333333333333333, chunk.distributions[2].cdf.coefficients[2] )
            self.assertAlmostEqual( 0.3666666666666666, chunk.distributions[3].cdf.coefficients[0] )
            self.assertAlmostEqual( 0.5               , chunk.distributions[3].cdf.coefficients[1] )
            self.assertAlmostEqual( 0.1333333333333333, chunk.distributions[3].cdf.coefficients[2] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            # verify evaluation
            self.assertAlmostEqual( 0.5  , chunk( 1., -0.5 ) )
            self.assertAlmostEqual( 0.495, chunk( 2., -0.5 ) )
            self.assertAlmostEqual( 0.45 , chunk( 3., -0.5 ) )
            self.assertAlmostEqual( 0.3  , chunk( 4., -0.5 ) )

            self.assertAlmostEqual( 0., chunk( 0., -0.5 ) )
            self.assertAlmostEqual( 0., chunk( 5., -0.5 ) )

            self.assertAlmostEqual( 0.4975, chunk( 1.5, -0.5 ) )
            self.assertAlmostEqual( 0.4725, chunk( 2.5, -0.5 ) )
            self.assertAlmostEqual( 0.375 , chunk( 3.5, -0.5 ) )

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

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )
            self.assertEqual( 4, len( linear.grid ) )
            self.assertEqual( 4, len( linear.distributions ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )
            self.assertAlmostEqual( 1., linear.grid[0] )
            self.assertAlmostEqual( 2., linear.grid[1] )
            self.assertAlmostEqual( 3., linear.grid[2] )
            self.assertAlmostEqual( 4., linear.grid[3] )
            self.assertEqual( True, linear.distributions[0].pdf.is_linearised )
            self.assertEqual( True, linear.distributions[1].pdf.is_linearised )
            self.assertEqual( True, linear.distributions[2].pdf.is_linearised )
            self.assertEqual( True, linear.distributions[3].pdf.is_linearised )
            self.assertEqual( 2, len( linear.distributions[0].pdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[1].pdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[2].pdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[3].pdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[0].pdf.values ) )
            self.assertEqual( 2, len( linear.distributions[1].pdf.values ) )
            self.assertEqual( 2, len( linear.distributions[2].pdf.values ) )
            self.assertEqual( 2, len( linear.distributions[3].pdf.values ) )
            self.assertAlmostEqual( -1.0, linear.distributions[0].pdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.distributions[0].pdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[1].pdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.distributions[1].pdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[2].pdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.distributions[2].pdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[3].pdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.distributions[3].pdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , linear.distributions[0].pdf.values[0] )
            self.assertAlmostEqual(  0.5 , linear.distributions[0].pdf.values[1] )
            self.assertAlmostEqual(  0.49, linear.distributions[1].pdf.values[0] )
            self.assertAlmostEqual(  0.51, linear.distributions[1].pdf.values[1] )
            self.assertAlmostEqual(  0.4 , linear.distributions[2].pdf.values[0] )
            self.assertAlmostEqual(  0.6 , linear.distributions[2].pdf.values[1] )
            self.assertAlmostEqual(  0.1 , linear.distributions[3].pdf.values[0] )
            self.assertAlmostEqual(  0.9 , linear.distributions[3].pdf.values[1] )
            self.assertIsNone( linear.distributions[0].cdf )
            self.assertIsNone( linear.distributions[1].cdf )
            self.assertIsNone( linear.distributions[2].cdf )
            self.assertIsNone( linear.distributions[3].cdf )
            self.assertEqual( 3, linear.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

        # the data is given explicitly
        chunk = LegendreAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                              distributions = [ LegendreAngularDistribution( [ 0.5 ] ),
                                                                LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                                                LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                                                LegendreAngularDistribution( [ 0.5, 0.4 ] ) ],
                                              interpolant = InterpolationType.LinearLinear )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = LegendreAngularDistributions( [ 1., 2., 3., 4. ],
                                             [ LegendreAngularDistribution( [ 0.5 ] ),
                                               LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                               LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                               LegendreAngularDistribution( [ 0.5, 0.4 ] ) ] )
        equal = LegendreAngularDistributions( [ 1., 2., 3., 4. ],
                                             [ LegendreAngularDistribution( [ 0.5 ] ),
                                               LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                               LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                               LegendreAngularDistribution( [ 0.5, 0.4 ] ) ] )
        unnormalised = LegendreAngularDistributions( [ 1., 2., 3., 4. ],
                                                     [ LegendreAngularDistribution( [ 1.0 ] ),
                                                       LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                                       LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                                       LegendreAngularDistribution( [ 0.5, 0.4 ] ) ] )
        different = LegendreAngularDistributions( [ 1., 4. ],
                                                  [ LegendreAngularDistribution( [ 0.5 ] ),
                                                    LegendreAngularDistribution( [ 0.5, 0.4 ] ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( True, ( left == unnormalised ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( False, ( left != unnormalised ) )
        self.assertEqual( True, ( left != different ) )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or f(y) grid
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [], distributions = [] )

        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [ 1. ],
                                                  distributions = [ LegendreAngularDistribution( [ 0.5 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [],
                                                  distributions = [ LegendreAngularDistribution( [ 0.5 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [ 1. ], distributions = [] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                                  distributions = [ LegendreAngularDistribution( [ 0.5 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.1 ] ) ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                                  distributions = [ LegendreAngularDistribution( [ 0.5 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.4 ] ) ],
                                                  boundaries = [ 3 ],
                                                  interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [ 1., 3., 2., 4. ],
                                                  distributions = [ LegendreAngularDistribution( [ 0.5 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.4 ] ) ] )

        # the x grid contains a triple x value
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [ 1., 2., 2., 2., 4. ],
                                                  distributions = [ LegendreAngularDistribution( [ 0.5 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.001 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.4 ] ) ] )

        # the x grid has a jump at the beginning
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [ 1., 1., 3., 4. ],
                                                  distributions = [ LegendreAngularDistribution( [ 0.5 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.4 ] ) ] )

        # the x grid has a jump at the end
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [ 1., 2., 4., 4. ],
                                                  distributions = [ LegendreAngularDistribution( [ 0.5 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.4 ] ) ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                                  distributions = [ LegendreAngularDistribution( [ 0.5 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.01 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.1 ] ),
                                                                    LegendreAngularDistribution( [ 0.5, 0.4 ] ) ],
                                                  boundaries = [ 2 ],
                                                  interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
