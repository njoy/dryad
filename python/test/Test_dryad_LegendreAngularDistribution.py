# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import LegendreAngularDistribution

class Test_dryad_LegendreAngularDistributionFunction( unittest.TestCase ) :
    """Unit test for the LegendreAngularDistributionFunction class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 1, pdf.order )
            self.assertEqual( 2, len( pdf.coefficients ) )
            self.assertAlmostEqual( 0.5 , pdf.coefficients[0] )
            self.assertAlmostEqual( 0.25, pdf.coefficients[1] )

            self.assertEqual( True, chunk.has_cdf )

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
            self.assertAlmostEqual( 0.25, chunk.average_cosine )

        # the data is given explicitly using a normalised series
        chunk = LegendreAngularDistribution( coefficients = [ 0.5, 0.25 ] )

        verify_chunk( self, chunk )

        # the data is given explicitly using an unnormalised series
        chunk = LegendreAngularDistribution( coefficients = [ 1, 0.5 ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the coefficient vector is empty
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistribution( coefficients = [] )

if __name__ == '__main__' :

    unittest.main()
