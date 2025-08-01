# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import LegendreAngularDistribution
from dryad import InterpolationType

class Test_dryad_LegendreAngularDistributionFunction( unittest.TestCase ) :
    """Unit test for the LegendreAngularDistributionFunction class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.5 , chunk.coefficients[0] )
            self.assertAlmostEqual( 0.25, chunk.coefficients[1] )

            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 1, pdf.order )
            self.assertEqual( 2, len( pdf.coefficients ) )
            self.assertAlmostEqual( 0.5 , pdf.coefficients[0] )
            self.assertAlmostEqual( 0.25, pdf.coefficients[1] )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., cdf.upper_cosine_limit )
            self.assertEqual( 2, cdf.order )
            self.assertEqual( 3, len( cdf.coefficients ) )
            self.assertAlmostEqual( 0.4166666666666666, cdf.coefficients[0] )
            self.assertAlmostEqual( 0.5               , cdf.coefficients[1] )
            self.assertAlmostEqual( 0.0833333333333333, cdf.coefficients[2] )
            self.assertAlmostEqual( 0., cdf( -1. ) )
            self.assertAlmostEqual( 1., cdf(  1. ) )

            # verify evaluation
            self.assertAlmostEqual( 0.25, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 0.5 , chunk( cosine =  0. ) )
            self.assertAlmostEqual( 0.75, chunk( cosine =  1. ) )

            # verify average cosine
            self.assertAlmostEqual( 1. / 6., chunk.average_cosine )

            # verify linearisation
            linear = chunk.linearise()
            self.assertEqual( 2, linear.pdf.number_points )
            self.assertEqual( 1, linear.pdf.number_regions )
            self.assertEqual( 2, len( linear.pdf.cosines) )
            self.assertEqual( 2, len( linear.pdf.values) )
            self.assertEqual( 1, len( linear.pdf.boundaries) )
            self.assertEqual( 1, len( linear.pdf.interpolants) )
            self.assertEqual( 1, linear.pdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.pdf.interpolants[0] )
            self.assertAlmostEqual( -1.0, linear.pdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.pdf.cosines[1] )
            self.assertAlmostEqual( 0.25, linear.pdf.values[0] )
            self.assertAlmostEqual( 0.75, linear.pdf.values[1] )
            self.assertEqual( True, linear.pdf.is_linearised )

        # the data is given explicitly using a normalised series
        chunk = LegendreAngularDistribution( coefficients = [ 0.5, 0.25 ] )

        verify_chunk( self, chunk )

        # the data is given explicitly using an unnormalised series
        chunk = LegendreAngularDistribution( coefficients = [ 1, 0.5 ] )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = LegendreAngularDistribution( [ 0.5, 0.25 ] )
        equal = LegendreAngularDistribution( [ 0.5, 0.25 ] )
        unnormalised = LegendreAngularDistribution( [ 1., 0.5 ] )
        different = LegendreAngularDistribution( [ 0.5, 0.1, 0.0001 ] )

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

        # the coefficient vector is empty
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistribution( coefficients = [] )

if __name__ == '__main__' :

    unittest.main()
