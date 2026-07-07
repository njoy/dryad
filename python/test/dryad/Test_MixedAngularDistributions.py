# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import MixedAngularDistribution
from njoy.dryad import MixedAngularDistributions
from njoy.dryad import IsotropicAngularDistributionFunction
from njoy.dryad import LegendreAngularDistributionFunction
from njoy.dryad import InterpolationType

class Test_MixedAngularDistributions( unittest.TestCase ) :
    """Unit test for the LegendreAngularDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

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

            self.assertEqual( 2, len( chunk.distributions[1].pdf.coefficients ) )
            self.assertEqual( 2, len( chunk.distributions[2].pdf.coefficients ) )
            self.assertEqual( 2, len( chunk.distributions[3].pdf.coefficients ) )
            self.assertAlmostEqual( 1.0  / normalisation, chunk.distributions[0].pdf.value )
            self.assertAlmostEqual( 1.0  / normalisation, chunk.distributions[1].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.02 / normalisation, chunk.distributions[1].pdf.coefficients[1] )
            self.assertAlmostEqual( 1.0  / normalisation, chunk.distributions[2].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.2  / normalisation, chunk.distributions[2].pdf.coefficients[1] )
            self.assertAlmostEqual( 1.0  / normalisation, chunk.distributions[3].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.8  / normalisation, chunk.distributions[3].pdf.coefficients[1] )
            self.assertEqual( 2, len( chunk.distributions[0].cdf.cosines ) )
            self.assertEqual( 2, len( chunk.distributions[0].cdf.values ) )
            self.assertEqual( 1, len( chunk.distributions[0].cdf.boundaries ) )
            self.assertEqual( 1, len( chunk.distributions[0].cdf.interpolants ) )
            self.assertEqual( 3, len( chunk.distributions[1].cdf.coefficients ) )
            self.assertEqual( 3, len( chunk.distributions[2].cdf.coefficients ) )
            self.assertEqual( 3, len( chunk.distributions[3].cdf.coefficients ) )
            self.assertAlmostEqual( -1., chunk.distributions[0].cdf.cosines[0] )
            self.assertAlmostEqual(  1., chunk.distributions[0].cdf.cosines[1] )
            self.assertAlmostEqual( 0.0                / normalisation, chunk.distributions[0].cdf.values[0] )
            self.assertAlmostEqual( 2.0                / normalisation, chunk.distributions[0].cdf.values[1] )
            self.assertAlmostEqual( 0.9933333333333333 / normalisation, chunk.distributions[1].cdf.coefficients[0] )
            self.assertAlmostEqual( 1.0                / normalisation, chunk.distributions[1].cdf.coefficients[1] )
            self.assertAlmostEqual( 0.0066666666666666 / normalisation, chunk.distributions[1].cdf.coefficients[2] )
            self.assertAlmostEqual( 0.9333333333333333 / normalisation, chunk.distributions[2].cdf.coefficients[0] )
            self.assertAlmostEqual( 1.0                / normalisation, chunk.distributions[2].cdf.coefficients[1] )
            self.assertAlmostEqual( 0.0666666666666666 / normalisation, chunk.distributions[2].cdf.coefficients[2] )
            self.assertAlmostEqual( 0.7333333333333333 / normalisation, chunk.distributions[3].cdf.coefficients[0] )
            self.assertAlmostEqual( 1.0                / normalisation, chunk.distributions[3].cdf.coefficients[1] )
            self.assertAlmostEqual( 0.2666666666666666 / normalisation, chunk.distributions[3].cdf.coefficients[2] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            # verify evaluation
            self.assertAlmostEqual( 1.0  / normalisation, chunk( 1., -0.5 ) )
            self.assertAlmostEqual( 0.99 / normalisation, chunk( 2., -0.5 ) )
            self.assertAlmostEqual( 0.9  / normalisation, chunk( 3., -0.5 ) )
            self.assertAlmostEqual( 0.6  / normalisation, chunk( 4., -0.5 ) )

            self.assertAlmostEqual( 0., chunk( 0., -0.5 ) )
            self.assertAlmostEqual( 0., chunk( 5., -0.5 ) )

            self.assertAlmostEqual( 0.995 / normalisation, chunk( 1.5, -0.5 ) )
            self.assertAlmostEqual( 0.945 / normalisation, chunk( 2.5, -0.5 ) )
            self.assertAlmostEqual( 0.75  / normalisation, chunk( 3.5, -0.5 ) )

            # verify average cosines - always the mean value even for unnormalised distributions
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
            self.assertAlmostEqual( 0.        / 2., cosines.values[0] )
            self.assertAlmostEqual( 0.04 / 3. / 2., cosines.values[1] )
            self.assertAlmostEqual( 0.4 / 3.  / 2., cosines.values[2] )
            self.assertAlmostEqual( 1.6 / 3.  / 2., cosines.values[3] )
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
            self.assertAlmostEqual(  1.0  / normalisation, linear.distributions[0].pdf.values[0] )
            self.assertAlmostEqual(  1.0  / normalisation, linear.distributions[0].pdf.values[1] )
            self.assertAlmostEqual(  0.98 / normalisation, linear.distributions[1].pdf.values[0] )
            self.assertAlmostEqual(  1.02 / normalisation, linear.distributions[1].pdf.values[1] )
            self.assertAlmostEqual(  0.8  / normalisation, linear.distributions[2].pdf.values[0] )
            self.assertAlmostEqual(  1.2  / normalisation, linear.distributions[2].pdf.values[1] )
            self.assertAlmostEqual(  0.2  / normalisation, linear.distributions[3].pdf.values[0] )
            self.assertAlmostEqual(  1.8  / normalisation, linear.distributions[3].pdf.values[1] )
            self.assertEqual( True, linear.distributions[0].cdf.is_linearised )
            self.assertEqual( True, linear.distributions[1].cdf.is_linearised )
            self.assertEqual( True, linear.distributions[2].cdf.is_linearised )
            self.assertEqual( True, linear.distributions[3].cdf.is_linearised )
            self.assertEqual( 2, len( linear.distributions[0].cdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[1].cdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[2].cdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[3].cdf.cosines ) )
            self.assertEqual( 2, len( linear.distributions[0].cdf.values ) )
            self.assertEqual( 2, len( linear.distributions[1].cdf.values ) )
            self.assertEqual( 2, len( linear.distributions[2].cdf.values ) )
            self.assertEqual( 2, len( linear.distributions[3].cdf.values ) )
            self.assertAlmostEqual( -1.0, linear.distributions[0].cdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.distributions[0].cdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[1].cdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.distributions[1].cdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[2].cdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.distributions[2].cdf.cosines[1] )
            self.assertAlmostEqual( -1.0, linear.distributions[3].cdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.distributions[3].cdf.cosines[1] )
            self.assertAlmostEqual(  0.0 / normalisation, linear.distributions[0].cdf.values[0] )
            self.assertAlmostEqual(  2.0 / normalisation, linear.distributions[0].cdf.values[1] )
            self.assertAlmostEqual(  0.0 / normalisation, linear.distributions[1].cdf.values[0] )
            self.assertAlmostEqual(  2.0 / normalisation, linear.distributions[1].cdf.values[1] )
            self.assertAlmostEqual(  0.0 / normalisation, linear.distributions[2].cdf.values[0] )
            self.assertAlmostEqual(  2.0 / normalisation, linear.distributions[2].cdf.values[1] )
            self.assertAlmostEqual(  0.0 / normalisation, linear.distributions[3].cdf.values[0] )
            self.assertAlmostEqual(  2.0 / normalisation, linear.distributions[3].cdf.values[1] )
            self.assertEqual( 3, linear.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

        def verify_chunk_jump( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            # verify content
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
            self.assertEqual( 2, len( chunk.distributions[1].pdf.coefficients ) )
            self.assertEqual( 2, len( chunk.distributions[2].pdf.coefficients ) )
            self.assertEqual( 2, len( chunk.distributions[3].pdf.coefficients ) )
            self.assertEqual( 2, len( chunk.distributions[4].pdf.coefficients ) )
            self.assertAlmostEqual( 1.0  / normalisation, chunk.distributions[0].pdf.value )
            self.assertAlmostEqual( 1.0  / normalisation, chunk.distributions[1].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.02 / normalisation, chunk.distributions[1].pdf.coefficients[1] )
            self.assertAlmostEqual( 1.0  / normalisation, chunk.distributions[2].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.01 / normalisation, chunk.distributions[2].pdf.coefficients[1] )
            self.assertAlmostEqual( 1.0  / normalisation, chunk.distributions[3].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.2  / normalisation, chunk.distributions[3].pdf.coefficients[1] )
            self.assertAlmostEqual( 1.0  / normalisation, chunk.distributions[4].pdf.coefficients[0] )
            self.assertAlmostEqual( 0.8  / normalisation, chunk.distributions[4].pdf.coefficients[1] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

        # the data is given explicitly
        chunk1 = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                            distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ],
                                            interpolant = InterpolationType.LinearLinear, normalise = False )
        chunk2 = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                            distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                              MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ],
                                            interpolant = InterpolationType.LinearLinear, normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk2, True )
        verify_chunk( self, chunk2, True )

        # the data is given explicitly with a jump that uses more than 2 x values
        chunk = MixedAngularDistributions( grid = [ 1., 2., 2., 2., 3., 4. ],
                                           distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.05 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.01 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ],
                                           interpolant = InterpolationType.LinearLinear )

        verify_chunk_jump( self, chunk, False )

        # the data is given explicitly with a jump at the beginning
        chunk = MixedAngularDistributions( grid = [ 1., 1., 2., 3., 4. ],
                                           distributions = [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.01 ] ) ),
                                                             MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ],
                                           interpolant = InterpolationType.LinearLinear )

        verify_chunk( self, chunk, False )

        # the data is given explicitly with a jump at the end
        chunk = MixedAngularDistributions( grid = [ 1., 2., 3., 4., 4. ],
                                           distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ),
                                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.01 ] ) ) ],
                                              interpolant = InterpolationType.LinearLinear )

        verify_chunk( self, chunk, False )

    def test_comparison( self ) :

        left = MixedAngularDistributions( [ 1., 2., 3., 4. ],
                                          [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 0.5 ) ),
                                            MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.01 ] ) ),
                                            MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.1 ] ) ),
                                            MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.4 ] ) ) ] )
        equal = MixedAngularDistributions( [ 1., 2., 3., 4. ],
                                           [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 0.5 ) ),
                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.01 ] ) ),
                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.1 ] ) ),
                                             MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.4 ] ) ) ] )
        unnormalised = MixedAngularDistributions( [ 1., 2., 3., 4. ],
                                                  [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                    MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                    MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                    MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ],
                                                  InterpolationType.LinearLinear,
                                                  True )
        different = MixedAngularDistributions( [ 1., 4. ],
                                               [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 0.5 ) ),
                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5, 0.4 ] ) ) ] )

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

            chunk = MixedAngularDistributions( grid = [], distributions = [] )

        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1. ],
                                               distributions = [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5 ] ) ) ] )

        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [],
                                               distributions = [ MixedAngularDistribution( LegendreAngularDistributionFunction( [ 0.5 ] ) ) ] )

        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1. ], distributions = [] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                               distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                               distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ],
                                               boundaries = [ 3 ],
                                               interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1., 3., 2., 4. ],
                                               distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = MixedAngularDistributions( grid = [ 1., 2., 3., 4. ],
                                               distributions = [ MixedAngularDistribution( IsotropicAngularDistributionFunction( 1. ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.02 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.2 ] ) ),
                                                                 MixedAngularDistribution( LegendreAngularDistributionFunction( [ 1., 0.8 ] ) ) ],
                                               boundaries = [ 2 ],
                                               interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
