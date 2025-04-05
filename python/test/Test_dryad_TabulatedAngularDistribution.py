# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import TabulatedAngularDistribution
from dryad import InterpolationType

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

            # verify average cosine
            self.assertAlmostEqual( 1. / 3., chunk.average_cosine )

            # verify linearisation
            linear = chunk.linearise()
            self.assertEqual( 4, linear.pdf.number_points )
            self.assertEqual( 1, linear.pdf.number_regions )
            self.assertEqual( 4, len( linear.pdf.cosines) )
            self.assertEqual( 4, len( linear.pdf.values) )
            self.assertEqual( 1, len( linear.pdf.boundaries) )
            self.assertEqual( 1, len( linear.pdf.interpolants) )
            self.assertEqual( 3, linear.pdf.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.pdf.interpolants[0] )
            self.assertAlmostEqual( -1. , linear.pdf.cosines[0] )
            self.assertAlmostEqual(  0. , linear.pdf.cosines[1] )
            self.assertAlmostEqual(  0.5, linear.pdf.cosines[2] )
            self.assertAlmostEqual(  1. , linear.pdf.cosines[3] )
            self.assertAlmostEqual( 0.  , linear.pdf.values[0] )
            self.assertAlmostEqual( 0.5 , linear.pdf.values[1] )
            self.assertAlmostEqual( 0.75, linear.pdf.values[2] )
            self.assertAlmostEqual( 1.  , linear.pdf.values[3] )
            self.assertEqual( True, linear.pdf.is_linearised )

        # the data is given explicitly using a normalised table
        chunk = TabulatedAngularDistribution( cosines = [ -1., 0., 0.5, 1. ], values = [ 0., 0.5, 0.75, 1. ] )

        verify_chunk( self, chunk )

        # the data is given explicitly using a unnormalised table
        chunk = TabulatedAngularDistribution( cosines = [ -1., 0., 0.5, 1. ], values = [ 0., 1., 1.5, 2. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the cosine and values vector are not of the same length
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistribution( cosines = [ -1., 1. ], values = [ 0., 0.5, 0.75, 1. ] )

if __name__ == '__main__' :

    unittest.main()
