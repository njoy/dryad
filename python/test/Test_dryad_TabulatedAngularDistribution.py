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

        def verify_chunk( self, chunk, normalise ) :

            normalisation = 2.0 if normalise else 1.0

            # verify content
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  0.  / normalisation, chunk.values[0] )
            self.assertAlmostEqual(  1.  / normalisation, chunk.values[1] )
            self.assertAlmostEqual(  1.5 / normalisation, chunk.values[2] )
            self.assertAlmostEqual(  2.  / normalisation, chunk.values[3] )
            self.assertAlmostEqual( 3, chunk.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            pdf = chunk.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 4, len( pdf.cosines ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( -1.  , pdf.cosines[0] )
            self.assertAlmostEqual(  0.  , pdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , pdf.cosines[2] )
            self.assertAlmostEqual(  1.  , pdf.cosines[3] )
            self.assertAlmostEqual(  0.  / normalisation, pdf.values[0] )
            self.assertAlmostEqual(  1.  / normalisation, pdf.values[1] )
            self.assertAlmostEqual(  1.5 / normalisation, pdf.values[2] )
            self.assertAlmostEqual(  2.  / normalisation, pdf.values[3] )
            self.assertAlmostEqual( 3, pdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = chunk.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., cdf.upper_cosine_limit )
            self.assertEqual( 4, len( cdf.cosines ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1.  , cdf.cosines[0] )
            self.assertAlmostEqual(  0.  , cdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , cdf.cosines[2] )
            self.assertAlmostEqual(  1.  , cdf.cosines[3] )
            self.assertAlmostEqual(  0.    / normalisation, cdf.values[0] )
            self.assertAlmostEqual(  0.5   / normalisation, cdf.values[1] )
            self.assertAlmostEqual(  1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual(  2.    / normalisation, cdf.values[3] )
            self.assertAlmostEqual( 3, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

            self.assertAlmostEqual( 2.0 / normalisation, pdf.integral )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0.  / normalisation, chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1.  / normalisation, chunk( cosine =  0. ) )
            self.assertAlmostEqual( 1.5 / normalisation, chunk( cosine =  0.5 ) )
            self.assertAlmostEqual( 2.  / normalisation, chunk( cosine =  1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( cosine = -5. ) )
            self.assertAlmostEqual( 0.0, chunk( cosine =  5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 0.5  / normalisation, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 1.75 / normalisation, chunk( cosine = 0.75 ) )

            # verify average cosine
            self.assertAlmostEqual( 2. / 3. / normalisation, chunk.average_cosine )

            # verify linearisation
            linear = chunk.linearise()

            pdf = linear.pdf
            self.assertAlmostEqual( -1., pdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., pdf.upper_cosine_limit )
            self.assertEqual( 4, len( pdf.cosines ) )
            self.assertEqual( 4, len( pdf.values ) )
            self.assertEqual( 1, len( pdf.boundaries ) )
            self.assertEqual( 1, len( pdf.interpolants ) )
            self.assertAlmostEqual( -1.  , pdf.cosines[0] )
            self.assertAlmostEqual(  0.  , pdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , pdf.cosines[2] )
            self.assertAlmostEqual(  1.  , pdf.cosines[3] )
            self.assertAlmostEqual(  0.  / normalisation, pdf.values[0] )
            self.assertAlmostEqual(  1.  / normalisation, pdf.values[1] )
            self.assertAlmostEqual(  1.5 / normalisation, pdf.values[2] )
            self.assertAlmostEqual(  2.  / normalisation, pdf.values[3] )
            self.assertAlmostEqual( 3, pdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, pdf.interpolants[0] )

            cdf = linear.cdf
            self.assertAlmostEqual( -1., cdf.lower_cosine_limit )
            self.assertAlmostEqual(  1., cdf.upper_cosine_limit )
            self.assertEqual( 4, len( cdf.cosines ) )
            self.assertEqual( 4, len( cdf.values ) )
            self.assertEqual( 1, len( cdf.boundaries ) )
            self.assertEqual( 1, len( cdf.interpolants ) )
            self.assertAlmostEqual( -1.  , cdf.cosines[0] )
            self.assertAlmostEqual(  0.  , cdf.cosines[1] )
            self.assertAlmostEqual(  0.5 , cdf.cosines[2] )
            self.assertAlmostEqual(  1.  , cdf.cosines[3] )
            self.assertAlmostEqual(  0.    / normalisation, cdf.values[0] )
            self.assertAlmostEqual(  0.5   / normalisation, cdf.values[1] )
            self.assertAlmostEqual(  1.125 / normalisation, cdf.values[2] )
            self.assertAlmostEqual(  2.    / normalisation, cdf.values[3] )
            self.assertAlmostEqual( 3, cdf.boundaries[0] )
            self.assertAlmostEqual( InterpolationType.LinearLinear, cdf.interpolants[0] )

        # the data is given explicitly using a normalised table
        chunk1 = TabulatedAngularDistribution( cosines = [ -1., 0., 0.5, 1. ], values = [ 0., 1., 1.5, 2. ],
                                               normalise = False )
        chunk2 = TabulatedAngularDistribution( cosines = [ -1., 0., 0.5, 1. ], values = [ 0., 1., 1.5, 2. ],
                                               normalise = True )

        verify_chunk( self, chunk1, False )
        verify_chunk( self, chunk2, True )

        chunk1.normalise()
        chunk2.normalise()

        verify_chunk( self, chunk1, True )
        verify_chunk( self, chunk2, True )

    def test_comparison( self ) :

        left = TabulatedAngularDistribution( [ -1., 1. ], [ 0.5, 0.5 ] )
        equal = TabulatedAngularDistribution( [ -1., 1. ], [ 0.5, 0.5 ] )
        unnormalised = TabulatedAngularDistribution( [ -1., 1. ], [ 1., 1. ], InterpolationType.LinearLinear, True )
        different = TabulatedAngularDistribution( [ -1., 1. ], [ 0.25, 0.75 ] )

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

        # the cosine and values vector are not of the same length
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistribution( cosines = [ -1., 1. ], values = [ 0., 0.5, 0.75, 1. ] )

if __name__ == '__main__' :

    unittest.main()
