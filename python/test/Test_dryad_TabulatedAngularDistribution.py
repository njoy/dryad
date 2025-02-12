# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import TabulatedAngularDistribution

class Test_dryad_TabulatedAngularDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedAngularDistribution class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 4, len( pdf.cosines ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertAlmostEqual( -1.  , pdf.cosines[0] )
            self.assertAlmostEqual(  0.  , pdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , pdf.cosines[2] )
            self.assertAlmostEqual(  1.  , pdf.cosines[3] )
            self.assertAlmostEqual(  0.  , pdf.values[0] )
            self.assertAlmostEqual(  0.5 , pdf.values[1] )
            self.assertAlmostEqual(  0.75, pdf.values[2] )
            self.assertAlmostEqual(  1.  , pdf.values[3] )

            self.assertEqual( False, chunk.has_cdf )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0.  , chunk( cosine = -1. ) )
            self.assertAlmostEqual( 0.5 , chunk( cosine =  0. ) )
            self.assertAlmostEqual( 0.75, chunk( cosine =  0.5 ) )
            self.assertAlmostEqual( 1.  , chunk( cosine =  1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( cosine = -5. ) )
            self.assertAlmostEqual( 0.0, chunk( cosine =  5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 0.25 , chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 0.875, chunk( cosine = 0.75 ) )

        # the data is given explicitly using a normalised series
        chunk = TabulatedAngularDistribution( cosines = [ -1., 0., 0.5, 1. ], values = [ 0., 0.5, 0.75, 1. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the cosine and values vector are not of the same length
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistribution( cosines = [ -1., 1. ], values = [ 0., 0.5, 0.75, 1. ] )

if __name__ == '__main__' :

    unittest.main()
