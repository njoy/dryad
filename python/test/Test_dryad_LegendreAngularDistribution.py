# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import LegendreAngularDistribution
from dryad import InterpolationType

class Test_dryad_LegendreAngularDistribution( unittest.TestCase ) :
    """Unit test for the LegendreAngularDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            # verify content
            self.assertAlmostEqual( 1.0 / normalisation, chunk.coefficients[0] )
            self.assertAlmostEqual( 0.5 / normalisation, chunk.coefficients[1] )

            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 1, pdf.order )
            self.assertEqual( 2, len( pdf.coefficients ) )
            self.assertAlmostEqual( 1.0 / normalisation, pdf.coefficients[0] )
            self.assertAlmostEqual( 0.5 / normalisation, pdf.coefficients[1] )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., cdf.upper_cosine_limit )
            self.assertEqual( 2, cdf.order )
            self.assertEqual( 3, len( cdf.coefficients ) )
            self.assertAlmostEqual( 0.8333333333333333 / normalisation, cdf.coefficients[0] )
            self.assertAlmostEqual( 1. / normalisation                , cdf.coefficients[1] )
            self.assertAlmostEqual( 0.1666666666666666 / normalisation, cdf.coefficients[2] )
            self.assertAlmostEqual( 0., cdf( -1. ) )
            self.assertAlmostEqual( 2. / normalisation, cdf(  1. ) )

            # verify evaluation
            self.assertAlmostEqual( 0.5 / normalisation, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1.0 / normalisation, chunk( cosine =  0. ) )
            self.assertAlmostEqual( 1.5 / normalisation, chunk( cosine =  1. ) )

            # verify average cosine
            self.assertAlmostEqual( 1. / 3. / normalisation, chunk.average_cosine )

            # verify linearisation
            linear = chunk.linearise()
            self.assertAlmostEqual( -1., linear.pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., linear.pdf.upper_cosine_limit )
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
            self.assertAlmostEqual( 0.5 / normalisation, linear.pdf.values[0] )
            self.assertAlmostEqual( 1.5 / normalisation, linear.pdf.values[1] )
            self.assertEqual( True, linear.pdf.is_linearised )

            self.assertAlmostEqual( -1., linear.cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., linear.cdf.upper_cosine_limit )
            self.assertEqual( 2, linear.cdf.number_points )
            self.assertEqual( 1, linear.cdf.number_regions )
            self.assertEqual( 2, len( linear.cdf.cosines) )
            self.assertEqual( 2, len( linear.cdf.values) )
            self.assertEqual( 1, len( linear.cdf.boundaries) )
            self.assertEqual( 1, len( linear.cdf.interpolants) )
            self.assertEqual( 1, linear.cdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.cdf.interpolants[0] )
            self.assertAlmostEqual( -1.0, linear.cdf.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.cdf.cosines[1] )
            self.assertAlmostEqual( 0. / normalisation, linear.cdf.values[0] )
            self.assertAlmostEqual( 2. / normalisation, linear.cdf.values[1] )
            self.assertEqual( True, linear.cdf.is_linearised )

        # the data is given explicitly
        chunk1 = LegendreAngularDistribution( coefficients = [ 1., 0.5 ], normalise = False )
        chunk2 = LegendreAngularDistribution( coefficients = [ 1., 0.5 ], normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

    def test_comparison( self ) :

        left = LegendreAngularDistribution( [ 0.5, 0.25 ] )
        equal = LegendreAngularDistribution( [ 0.5, 0.25 ] )
        unnormalised = LegendreAngularDistribution( [ 1., 0.5 ], True )
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
