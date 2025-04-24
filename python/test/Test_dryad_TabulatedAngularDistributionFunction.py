# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import TabulatedAngularDistributionFunction
from dryad import InterpolationType

class Test_dryad_TabulatedAngularDistributionFunction( unittest.TestCase ) :
    """Unit test for the TabulatedAngularDistributionFunction class."""

    def test_component( self ) :

        def verify_chunk1( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  0.75, chunk.values[2] )
            self.assertAlmostEqual(  1.  , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_linearised )

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

            # verify arithmetic operators
            same = TabulatedAngularDistributionFunction( [ -1., 1. ], [ 1., 0. ] )
            threshold = TabulatedAngularDistributionFunction( [ 0., 1. ], [ 0., 2. ] )
            nonzerothreshold = TabulatedAngularDistributionFunction( [ 0., 1. ], [ 1., 1. ] )
            small = TabulatedAngularDistributionFunction( [ -1., 0. ], [ 0., 1. ] )

            result = -chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.5 , result.cosines[2] )
            self.assertAlmostEqual(  1.  , result.cosines[3] )
            self.assertAlmostEqual(  0.  , result.values[0] )
            self.assertAlmostEqual( -0.5 , result.values[1] )
            self.assertAlmostEqual( -0.75, result.values[2] )
            self.assertAlmostEqual( -1.  , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  2.  , chunk.values[0] )
            self.assertAlmostEqual(  2.5 , chunk.values[1] )
            self.assertAlmostEqual(  2.75, chunk.values[2] )
            self.assertAlmostEqual(  3.  , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  0.75, chunk.values[2] )
            self.assertAlmostEqual(  1.  , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk *= 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5, chunk.cosines[2] )
            self.assertAlmostEqual(  1. , chunk.cosines[3] )
            self.assertAlmostEqual(  0. , chunk.values[0] )
            self.assertAlmostEqual(  1. , chunk.values[1] )
            self.assertAlmostEqual(  1.5, chunk.values[2] )
            self.assertAlmostEqual(  2. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk /= 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  0.75, chunk.values[2] )
            self.assertAlmostEqual(  1.  , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.5 , result.cosines[2] )
            self.assertAlmostEqual(  1.  , result.cosines[3] )
            self.assertAlmostEqual(  2.  , result.values[0] )
            self.assertAlmostEqual(  2.5 , result.values[1] )
            self.assertAlmostEqual(  2.75, result.values[2] )
            self.assertAlmostEqual(  3.  , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. + chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.5 , result.cosines[2] )
            self.assertAlmostEqual(  1.  , result.cosines[3] )
            self.assertAlmostEqual(  2.  , result.values[0] )
            self.assertAlmostEqual(  2.5 , result.values[1] )
            self.assertAlmostEqual(  2.75, result.values[2] )
            self.assertAlmostEqual(  3.  , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.5 , result.cosines[2] )
            self.assertAlmostEqual(  1.  , result.cosines[3] )
            self.assertAlmostEqual( -2.  , result.values[0] )
            self.assertAlmostEqual( -1.5 , result.values[1] )
            self.assertAlmostEqual( -1.25, result.values[2] )
            self.assertAlmostEqual( -1.  , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. - chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.5 , result.cosines[2] )
            self.assertAlmostEqual(  1.  , result.cosines[3] )
            self.assertAlmostEqual(  2.  , result.values[0] )
            self.assertAlmostEqual(  1.5 , result.values[1] )
            self.assertAlmostEqual(  1.25, result.values[2] )
            self.assertAlmostEqual(  1.  , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk * 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0.5, result.cosines[2] )
            self.assertAlmostEqual(  1. , result.cosines[3] )
            self.assertAlmostEqual(  0. , result.values[0] )
            self.assertAlmostEqual(  1. , result.values[1] )
            self.assertAlmostEqual(  1.5, result.values[2] )
            self.assertAlmostEqual(  2. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. * chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0.5, result.cosines[2] )
            self.assertAlmostEqual(  1. , result.cosines[3] )
            self.assertAlmostEqual(  0. , result.values[0] )
            self.assertAlmostEqual(  1. , result.values[1] )
            self.assertAlmostEqual(  1.5, result.values[2] )
            self.assertAlmostEqual(  2. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk / 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1.   , result.cosines[0] )
            self.assertAlmostEqual(  0.   , result.cosines[1] )
            self.assertAlmostEqual(  0.5  , result.cosines[2] )
            self.assertAlmostEqual(  1.   , result.cosines[3] )
            self.assertAlmostEqual(  0.   , result.values[0] )
            self.assertAlmostEqual(  0.25 , result.values[1] )
            self.assertAlmostEqual(  0.375, result.values[2] )
            self.assertAlmostEqual(  0.5  , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += same
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5, chunk.cosines[2] )
            self.assertAlmostEqual(  1. , chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.values[0] )
            self.assertAlmostEqual(  1. , chunk.values[1] )
            self.assertAlmostEqual(  1. , chunk.values[2] )
            self.assertAlmostEqual(  1. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= same
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  0.75, chunk.values[2] )
            self.assertAlmostEqual(  1.  , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + same
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0.5, result.cosines[2] )
            self.assertAlmostEqual(  1. , result.cosines[3] )
            self.assertAlmostEqual(  1. , result.values[0] )
            self.assertAlmostEqual(  1. , result.values[1] )
            self.assertAlmostEqual(  1. , result.values[2] )
            self.assertAlmostEqual(  1. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - same
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0.5, result.cosines[2] )
            self.assertAlmostEqual(  1. , result.cosines[3] )
            self.assertAlmostEqual( -1. , result.values[0] )
            self.assertAlmostEqual(  0. , result.values[1] )
            self.assertAlmostEqual(  0.5, result.values[2] )
            self.assertAlmostEqual(  1. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += threshold
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  1.75, chunk.values[2] )
            self.assertAlmostEqual(  3.  , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= threshold
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  0.75, chunk.values[2] )
            self.assertAlmostEqual(  1.  , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + threshold
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.5 , result.cosines[2] )
            self.assertAlmostEqual(  1.  , result.cosines[3] )
            self.assertAlmostEqual(  0.  , result.values[0] )
            self.assertAlmostEqual(  0.5 , result.values[1] )
            self.assertAlmostEqual(  1.75, result.values[2] )
            self.assertAlmostEqual(  3.  , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - threshold
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.5 , result.cosines[2] )
            self.assertAlmostEqual(  1.  , result.cosines[3] )
            self.assertAlmostEqual(  0.  , result.values[0] )
            self.assertAlmostEqual(  0.5 , result.values[1] )
            self.assertAlmostEqual( -0.25, result.values[2] )
            self.assertAlmostEqual( -1.  , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += nonzerothreshold
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.  , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[3] )
            self.assertAlmostEqual(  1.  , chunk.cosines[4] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  1.5 , chunk.values[2] )
            self.assertAlmostEqual(  1.75, chunk.values[3] )
            self.assertAlmostEqual(  2.  , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= nonzerothreshold
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  0.75, chunk.values[2] )
            self.assertAlmostEqual(  1.  , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + nonzerothreshold
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.  , result.cosines[2] )
            self.assertAlmostEqual(  0.5 , result.cosines[3] )
            self.assertAlmostEqual(  1.  , result.cosines[4] )
            self.assertAlmostEqual(  0.  , result.values[0] )
            self.assertAlmostEqual(  0.5 , result.values[1] )
            self.assertAlmostEqual(  1.5 , result.values[2] )
            self.assertAlmostEqual(  1.75, result.values[3] )
            self.assertAlmostEqual(  2.  , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - nonzerothreshold
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1.   , result.cosines[0] )
            self.assertAlmostEqual(  0.   , result.cosines[1] )
            self.assertAlmostEqual(  0.   , result.cosines[2] )
            self.assertAlmostEqual(  0.5  , result.cosines[3] )
            self.assertAlmostEqual(  1.   , result.cosines[4] )
            self.assertAlmostEqual(  0.  , result.values[0] )
            self.assertAlmostEqual(  0.5 , result.values[1] )
            self.assertAlmostEqual( -0.5 , result.values[2] )
            self.assertAlmostEqual( -0.25, result.values[3] )
            self.assertAlmostEqual(  0.  , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            # this will add a second point at the lower end point
            result = chunk + small
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.  , result.cosines[2] )
            self.assertAlmostEqual(  0.5 , result.cosines[3] )
            self.assertAlmostEqual(  1.  , result.cosines[4] )
            self.assertAlmostEqual(  0.  , result.values[0] )
            self.assertAlmostEqual(  1.5 , result.values[1] )
            self.assertAlmostEqual(  0.5 , result.values[2] )
            self.assertAlmostEqual(  0.75, result.values[3] )
            self.assertAlmostEqual(  1.  , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            # this will add a second point at the lower end point
            result = chunk - small
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.  , result.cosines[2] )
            self.assertAlmostEqual(  0.5 , result.cosines[3] )
            self.assertAlmostEqual(  1.  , result.cosines[4] )
            self.assertAlmostEqual(  0.  , result.values[0] )
            self.assertAlmostEqual( -0.5 , result.values[1] )
            self.assertAlmostEqual(  0.5 , result.values[2] )
            self.assertAlmostEqual(  0.75, result.values[3] )
            self.assertAlmostEqual(  1.  , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 4, len( linear.cosines ) )
            self.assertEqual( 4, len( linear.values ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 3, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( -1.  , linear.cosines[0] )
            self.assertAlmostEqual(  0.  , linear.cosines[1] )
            self.assertAlmostEqual(  0.5 , linear.cosines[2] )
            self.assertAlmostEqual(  1.  , linear.cosines[3] )
            self.assertAlmostEqual(  0.  , linear.values[0] )
            self.assertAlmostEqual(  0.5 , linear.values[1] )
            self.assertAlmostEqual(  0.75, linear.values[2] )
            self.assertAlmostEqual(  1.  , linear.values[3] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk2( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.cosines[4] )
            self.assertAlmostEqual(  4. , chunk.values[0] )
            self.assertAlmostEqual(  3. , chunk.values[1] )
            self.assertAlmostEqual(  4. , chunk.values[2] )
            self.assertAlmostEqual(  3. , chunk.values[3] )
            self.assertAlmostEqual(  2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( cosine = -1. ) )
            self.assertAlmostEqual( 4., chunk( cosine = 0. ) )
            self.assertAlmostEqual( 3., chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 2., chunk( cosine = 1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( cosine = -2. ) )
            self.assertAlmostEqual( 0.0, chunk( cosine = 2. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 3.5, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 3.5, chunk( cosine = 0.25 ) )
            self.assertAlmostEqual( 2.5, chunk( cosine = 0.75 ) )

            # verify arithmetic operators
            same = TabulatedAngularDistributionFunction( [ -1., 1. ], [ 1., 0. ] )
            threshold = TabulatedAngularDistributionFunction( [ 0., 1. ], [ 0., 2. ] )
            nonzerothreshold = TabulatedAngularDistributionFunction( [ 0.5, 1. ], [ 1., 1. ] )
            small = TabulatedAngularDistributionFunction( [ -1., 0.5 ], [ 1., 1. ] )

            result = -chunk
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual( -4. , result.values[0] )
            self.assertAlmostEqual( -3. , result.values[1] )
            self.assertAlmostEqual( -4. , result.values[2] )
            self.assertAlmostEqual( -3. , result.values[3] )
            self.assertAlmostEqual( -2. , result.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk += 2.
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.cosines[4] )
            self.assertAlmostEqual(  6. , chunk.values[0] )
            self.assertAlmostEqual(  5. , chunk.values[1] )
            self.assertAlmostEqual(  6. , chunk.values[2] )
            self.assertAlmostEqual(  5. , chunk.values[3] )
            self.assertAlmostEqual(  4. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= 2.
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.cosines[4] )
            self.assertAlmostEqual(  4. , chunk.values[0] )
            self.assertAlmostEqual(  3. , chunk.values[1] )
            self.assertAlmostEqual(  4. , chunk.values[2] )
            self.assertAlmostEqual(  3. , chunk.values[3] )
            self.assertAlmostEqual(  2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk *= 2.
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.cosines[4] )
            self.assertAlmostEqual(  8. , chunk.values[0] )
            self.assertAlmostEqual(  6. , chunk.values[1] )
            self.assertAlmostEqual(  8. , chunk.values[2] )
            self.assertAlmostEqual(  6. , chunk.values[3] )
            self.assertAlmostEqual(  4. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk /= 2.
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.cosines[4] )
            self.assertAlmostEqual(  4. , chunk.values[0] )
            self.assertAlmostEqual(  3. , chunk.values[1] )
            self.assertAlmostEqual(  4. , chunk.values[2] )
            self.assertAlmostEqual(  3. , chunk.values[3] )
            self.assertAlmostEqual(  2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + 2.
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual(  6. , result.values[0] )
            self.assertAlmostEqual(  5. , result.values[1] )
            self.assertAlmostEqual(  6. , result.values[2] )
            self.assertAlmostEqual(  5. , result.values[3] )
            self.assertAlmostEqual(  4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. + chunk
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual(  6. , result.values[0] )
            self.assertAlmostEqual(  5. , result.values[1] )
            self.assertAlmostEqual(  6. , result.values[2] )
            self.assertAlmostEqual(  5. , result.values[3] )
            self.assertAlmostEqual(  4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - 2.
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual(  2. , result.values[0] )
            self.assertAlmostEqual(  1. , result.values[1] )
            self.assertAlmostEqual(  2. , result.values[2] )
            self.assertAlmostEqual(  1. , result.values[3] )
            self.assertAlmostEqual(  0. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. - chunk
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual( -2. , result.values[0] )
            self.assertAlmostEqual( -1. , result.values[1] )
            self.assertAlmostEqual( -2. , result.values[2] )
            self.assertAlmostEqual( -1. , result.values[3] )
            self.assertAlmostEqual(  0. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk * 2.
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual(  8. , result.values[0] )
            self.assertAlmostEqual(  6. , result.values[1] )
            self.assertAlmostEqual(  8. , result.values[2] )
            self.assertAlmostEqual(  6. , result.values[3] )
            self.assertAlmostEqual(  4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. * chunk
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual(  8. , result.values[0] )
            self.assertAlmostEqual(  6. , result.values[1] )
            self.assertAlmostEqual(  8. , result.values[2] )
            self.assertAlmostEqual(  6. , result.values[3] )
            self.assertAlmostEqual(  4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk / 2.
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual(  2. , result.values[0] )
            self.assertAlmostEqual(  1.5, result.values[1] )
            self.assertAlmostEqual(  2. , result.values[2] )
            self.assertAlmostEqual(  1.5, result.values[3] )
            self.assertAlmostEqual(  1. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            chunk += same
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.  , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[3] )
            self.assertAlmostEqual(  1.  , chunk.cosines[4] )
            self.assertAlmostEqual(  5.  , chunk.values[0] )
            self.assertAlmostEqual(  3.5 , chunk.values[1] )
            self.assertAlmostEqual(  4.5 , chunk.values[2] )
            self.assertAlmostEqual(  3.25, chunk.values[3] )
            self.assertAlmostEqual(  2.  , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= same
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.cosines[4] )
            self.assertAlmostEqual(  4. , chunk.values[0] )
            self.assertAlmostEqual(  3. , chunk.values[1] )
            self.assertAlmostEqual(  4. , chunk.values[2] )
            self.assertAlmostEqual(  3. , chunk.values[3] )
            self.assertAlmostEqual(  2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + same
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.  , result.cosines[2] )
            self.assertAlmostEqual(  0.5 , result.cosines[3] )
            self.assertAlmostEqual(  1.  , result.cosines[4] )
            self.assertAlmostEqual(  5.  , result.values[0] )
            self.assertAlmostEqual(  3.5 , result.values[1] )
            self.assertAlmostEqual(  4.5 , result.values[2] )
            self.assertAlmostEqual(  3.25, result.values[3] )
            self.assertAlmostEqual(  2.  , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - same
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1.  , result.cosines[0] )
            self.assertAlmostEqual(  0.  , result.cosines[1] )
            self.assertAlmostEqual(  0.  , result.cosines[2] )
            self.assertAlmostEqual(  0.5 , result.cosines[3] )
            self.assertAlmostEqual(  1.  , result.cosines[4] )
            self.assertAlmostEqual(  3.  , result.values[0] )
            self.assertAlmostEqual(  2.5 , result.values[1] )
            self.assertAlmostEqual(  3.5 , result.values[2] )
            self.assertAlmostEqual(  2.75, result.values[3] )
            self.assertAlmostEqual(  2.  , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            chunk += threshold
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.cosines[4] )
            self.assertAlmostEqual(  4. , chunk.values[0] )
            self.assertAlmostEqual(  3. , chunk.values[1] )
            self.assertAlmostEqual(  4. , chunk.values[2] )
            self.assertAlmostEqual(  4. , chunk.values[3] )
            self.assertAlmostEqual(  4. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= threshold
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.cosines[4] )
            self.assertAlmostEqual(  4. , chunk.values[0] )
            self.assertAlmostEqual(  3. , chunk.values[1] )
            self.assertAlmostEqual(  4. , chunk.values[2] )
            self.assertAlmostEqual(  3. , chunk.values[3] )
            self.assertAlmostEqual(  2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + threshold
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual(  4. , result.values[0] )
            self.assertAlmostEqual(  3. , result.values[1] )
            self.assertAlmostEqual(  4. , result.values[2] )
            self.assertAlmostEqual(  4. , result.values[3] )
            self.assertAlmostEqual(  4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - threshold
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  1. , result.cosines[4] )
            self.assertAlmostEqual(  4. , result.values[0] )
            self.assertAlmostEqual(  3. , result.values[1] )
            self.assertAlmostEqual(  4. , result.values[2] )
            self.assertAlmostEqual(  2. , result.values[3] )
            self.assertAlmostEqual(  0. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            chunk += nonzerothreshold
            self.assertEqual( 6, len( chunk.cosines ) )
            self.assertEqual( 6, len( chunk.values ) )
            self.assertEqual( 3, len( chunk.boundaries ) )
            self.assertEqual( 3, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  0.5, chunk.cosines[4] )
            self.assertAlmostEqual(  1. , chunk.cosines[5] )
            self.assertAlmostEqual(  4. , chunk.values[0] )
            self.assertAlmostEqual(  3. , chunk.values[1] )
            self.assertAlmostEqual(  4. , chunk.values[2] )
            self.assertAlmostEqual(  3. , chunk.values[3] )
            self.assertAlmostEqual(  4. , chunk.values[4] )
            self.assertAlmostEqual(  3. , chunk.values[5] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( 5, chunk.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[2] )

            chunk -= nonzerothreshold
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual(  0. , chunk.cosines[1] )
            self.assertAlmostEqual(  0. , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5, chunk.cosines[3] )
            self.assertAlmostEqual(  1. , chunk.cosines[4] )
            self.assertAlmostEqual(  4. , chunk.values[0] )
            self.assertAlmostEqual(  3. , chunk.values[1] )
            self.assertAlmostEqual(  4. , chunk.values[2] )
            self.assertAlmostEqual(  3. , chunk.values[3] )
            self.assertAlmostEqual(  2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + nonzerothreshold
            self.assertEqual( 6, len( result.cosines ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  0.5, result.cosines[4] )
            self.assertAlmostEqual(  1. , result.cosines[5] )
            self.assertAlmostEqual(  4. , result.values[0] )
            self.assertAlmostEqual(  3. , result.values[1] )
            self.assertAlmostEqual(  4. , result.values[2] )
            self.assertAlmostEqual(  3. , result.values[3] )
            self.assertAlmostEqual(  4. , result.values[4] )
            self.assertAlmostEqual(  3. , result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            result = chunk - nonzerothreshold
            self.assertEqual( 6, len( result.cosines ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  0.5, result.cosines[4] )
            self.assertAlmostEqual(  1. , result.cosines[5] )
            self.assertAlmostEqual(  4. , result.values[0] )
            self.assertAlmostEqual(  3. , result.values[1] )
            self.assertAlmostEqual(  4. , result.values[2] )
            self.assertAlmostEqual(  3. , result.values[3] )
            self.assertAlmostEqual(  2. , result.values[4] )
            self.assertAlmostEqual(  1. , result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            # this will add a second point at the lower end point
            result = chunk + small
            self.assertEqual( 6, len( result.cosines ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  0.5, result.cosines[4] )
            self.assertAlmostEqual(  1. , result.cosines[5] )
            self.assertAlmostEqual(  5. , result.values[0] )
            self.assertAlmostEqual(  4. , result.values[1] )
            self.assertAlmostEqual(  5. , result.values[2] )
            self.assertAlmostEqual(  4. , result.values[3] )
            self.assertAlmostEqual(  3. , result.values[4] )
            self.assertAlmostEqual(  2. , result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            # this will add a second point at the lower end point
            result = chunk - small
            self.assertEqual( 6, len( result.cosines ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual(  0. , result.cosines[1] )
            self.assertAlmostEqual(  0. , result.cosines[2] )
            self.assertAlmostEqual(  0.5, result.cosines[3] )
            self.assertAlmostEqual(  0.5, result.cosines[4] )
            self.assertAlmostEqual(  1. , result.cosines[5] )
            self.assertAlmostEqual(  3. , result.values[0] )
            self.assertAlmostEqual(  2. , result.values[1] )
            self.assertAlmostEqual(  3. , result.values[2] )
            self.assertAlmostEqual(  2. , result.values[3] )
            self.assertAlmostEqual(  3. , result.values[4] )
            self.assertAlmostEqual(  2. , result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 5, linear.number_points )
            self.assertEqual( 2, linear.number_regions )

            self.assertEqual( 5, len( linear.cosines ) )
            self.assertEqual( 5, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )

            self.assertEqual( 1, linear.boundaries[0] )
            self.assertEqual( 4, linear.boundaries[1] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )

            self.assertAlmostEqual( -1. , linear.cosines[0] )
            self.assertAlmostEqual(  0. , linear.cosines[1] )
            self.assertAlmostEqual(  0. , linear.cosines[2] )
            self.assertAlmostEqual(  0.5, linear.cosines[3] )
            self.assertAlmostEqual(  1. , linear.cosines[4] )

            self.assertAlmostEqual( 4., linear.values[0] )
            self.assertAlmostEqual( 3., linear.values[1] )
            self.assertAlmostEqual( 4., linear.values[2] )
            self.assertAlmostEqual( 3., linear.values[3] )
            self.assertAlmostEqual( 2., linear.values[4] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk3( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  0.75, chunk.values[2] )
            self.assertAlmostEqual(  1.  , chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0.  , chunk( cosine = -1. ) )
            self.assertAlmostEqual( 0.5 , chunk( cosine = 0. ) )
            self.assertAlmostEqual( 0.75, chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 1.  , chunk( cosine = 1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( cosine = -2. ) )
            self.assertAlmostEqual( 0.0, chunk( cosine = 2. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 0.25, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 0.61237243569579, chunk( cosine = 0.25 ) )
            self.assertAlmostEqual( 0.86602540378444, chunk( cosine = 0.75 ) )

            # verify arithmetic operators throw exceptions
            temp = TabulatedAngularDistributionFunction( [ 1., 4. ], [ 4., 1. ] )
            with self.assertRaises( Exception ) : result = chunk + 2.
            with self.assertRaises( Exception ) : result = chunk - 2.
            with self.assertRaises( Exception ) : result = chunk + temp
            with self.assertRaises( Exception ) : result = chunk - temp
            with self.assertRaises( Exception ) : chunk += 2.
            with self.assertRaises( Exception ) : chunk -= 2.
            with self.assertRaises( Exception ) : chunk += temp
            with self.assertRaises( Exception ) : chunk -= temp
            with self.assertRaises( Exception ) : result = 2. + chunk
            with self.assertRaises( Exception ) : result = 2. - chunk

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 14, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 14, len( linear.cosines ) )
            self.assertEqual( 14, len( linear.values ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 13, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( -1.    , linear.cosines[0] )
            self.assertAlmostEqual(  0.    , linear.cosines[1] )
            self.assertAlmostEqual(  0.0625, linear.cosines[2] )
            self.assertAlmostEqual(  0.125 , linear.cosines[3] )
            self.assertAlmostEqual(  0.1875, linear.cosines[4] )
            self.assertAlmostEqual(  0.25  , linear.cosines[5] )
            self.assertAlmostEqual(  0.3125, linear.cosines[6] )
            self.assertAlmostEqual(  0.375 , linear.cosines[7] )
            self.assertAlmostEqual(  0.4375, linear.cosines[8] )
            self.assertAlmostEqual(  0.5   , linear.cosines[9] )
            self.assertAlmostEqual(  0.625 , linear.cosines[10] )
            self.assertAlmostEqual(  0.75  , linear.cosines[11] )
            self.assertAlmostEqual(  0.875 , linear.cosines[12] )
            self.assertAlmostEqual(  1.    , linear.cosines[13] )

            self.assertAlmostEqual( 0.              , linear.values[0] )
            self.assertAlmostEqual( 0.5             , linear.values[1] )
            self.assertAlmostEqual( 0.52599475275432, linear.values[2] )
            self.assertAlmostEqual( 0.55334095985016, linear.values[3] )
            self.assertAlmostEqual( 0.58210888273045, linear.values[4] )
            self.assertAlmostEqual( 0.61237243569579, linear.values[5] )
            self.assertAlmostEqual( 0.64420937581474, linear.values[6] )
            self.assertAlmostEqual( 0.67770150270738, linear.values[7] )
            self.assertAlmostEqual( 0.71293486871561, linear.values[8] )
            self.assertAlmostEqual( 0.75            , linear.values[9] )
            self.assertAlmostEqual( 0.80592744886766, linear.values[10] )
            self.assertAlmostEqual( 0.86602540378444, linear.values[11] )
            self.assertAlmostEqual( 0.93060485910210, linear.values[12] )
            self.assertAlmostEqual( 1.              , linear.values[13] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk4( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.  , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[3] )
            self.assertAlmostEqual(  1.  , chunk.cosines[4] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  1.  , chunk.values[2] )
            self.assertAlmostEqual(  1.25, chunk.values[3] )
            self.assertAlmostEqual(  1.5 , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0.  , chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1.  , chunk( cosine = 0. ) )
            self.assertAlmostEqual( 1.25, chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 1.5 , chunk( cosine = 1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( cosine = -2. ) )
            self.assertAlmostEqual( 0.0, chunk( cosine = 2. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 0.25, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 1.11803398874989, chunk( cosine = 0.25 ) )
            self.assertAlmostEqual( 1.36930639376292, chunk( cosine = 0.75 ) )

            # verify arithmetic operators throw exceptions
            temp = TabulatedAngularDistributionFunction( [ 1., 4. ], [ 4., 1. ] )
            with self.assertRaises( Exception ) : result = chunk + 2.
            with self.assertRaises( Exception ) : result = chunk - 2.
            with self.assertRaises( Exception ) : result = chunk + temp
            with self.assertRaises( Exception ) : result = chunk - temp
            with self.assertRaises( Exception ) : chunk += 2.
            with self.assertRaises( Exception ) : chunk -= 2.
            with self.assertRaises( Exception ) : chunk += temp
            with self.assertRaises( Exception ) : chunk -= temp
            with self.assertRaises( Exception ) : result = 2. + chunk
            with self.assertRaises( Exception ) : result = 2. - chunk

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 11, linear.number_points )
            self.assertEqual( 2, linear.number_regions )

            self.assertEqual( 11, len( linear.cosines ) )
            self.assertEqual( 11, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )

            self.assertEqual(  1, linear.boundaries[0] )
            self.assertEqual( 10, linear.boundaries[1] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )

            self.assertAlmostEqual( -1.   , linear.cosines[0] )
            self.assertAlmostEqual(  0.   , linear.cosines[1] )
            self.assertAlmostEqual(  0.   , linear.cosines[2] )
            self.assertAlmostEqual(  0.125, linear.cosines[3] )
            self.assertAlmostEqual(  0.25 , linear.cosines[4] )
            self.assertAlmostEqual(  0.375, linear.cosines[5] )
            self.assertAlmostEqual(  0.5  , linear.cosines[6] )
            self.assertAlmostEqual(  0.625, linear.cosines[7] )
            self.assertAlmostEqual(  0.75 , linear.cosines[8] )
            self.assertAlmostEqual(  0.875, linear.cosines[9] )
            self.assertAlmostEqual(  1.   , linear.cosines[10] )

            self.assertAlmostEqual( 0.              , linear.values[0] )
            self.assertAlmostEqual( 0.5             , linear.values[1] )
            self.assertAlmostEqual( 1.              , linear.values[2] )
            self.assertAlmostEqual( 1.05737126344056, linear.values[3] )
            self.assertAlmostEqual( 1.11803398874989, linear.values[4] )
            self.assertAlmostEqual( 1.18217701125397, linear.values[5] )
            self.assertAlmostEqual( 1.25            , linear.values[6] )
            self.assertAlmostEqual( 1.30829392424013, linear.values[7] )
            self.assertAlmostEqual( 1.36930639376292, linear.values[8] )
            self.assertAlmostEqual( 1.43316418830655, linear.values[9] )
            self.assertAlmostEqual( 1.5             , linear.values[10] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk5( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.  , chunk.cosines[2] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[3] )
            self.assertAlmostEqual(  1.  , chunk.cosines[4] )
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  1.  , chunk.values[2] )
            self.assertAlmostEqual(  1.25, chunk.values[3] )
            self.assertAlmostEqual(  1.5 , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )    # <-- this is changed from 2 to 1
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

        def verify_chunk6( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1.  , chunk.cosines[0] )
            self.assertAlmostEqual(  0.  , chunk.cosines[1] )
            self.assertAlmostEqual(  0.5 , chunk.cosines[2] )
            self.assertAlmostEqual(  1.  , chunk.cosines[3] )      # <-- last point removed
            self.assertAlmostEqual(  0.  , chunk.values[0] )
            self.assertAlmostEqual(  0.5 , chunk.values[1] )
            self.assertAlmostEqual(  0.75, chunk.values[2] )
            self.assertAlmostEqual(  1.  , chunk.values[3] )      # <-- last point removed
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )    # <-- boundary value reset
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

        # the data is given explicitly for data without boundaries
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1. ],
                                                      values = [ 0., 0.5, 0.75, 1. ],
                                                      interpolant = InterpolationType.LinearLinear )

        verify_chunk1( self, chunk )

        # the data is given explicitly for data without boundaries and a jump
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0.5, 1. ],
                                                      values = [ 4., 3., 4., 3., 2. ],
                                                      interpolant = InterpolationType.LinearLinear )

        verify_chunk2( self, chunk )

        # the data is given explicitly for data without a jump
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1. ],
                                                      values = [ 0., 0.5, 0.75, 1. ],
                                                      boundaries = [ 1, 3 ],
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk3( self, chunk )

        # the data is given explicitly for data with a jump
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0.5, 1. ],
                                                      values = [ 0., 0.5, 1., 1.25, 1.5 ],
                                                      boundaries = [ 1, 4 ],
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk4( self, chunk )

        # the data is given explicitly with boundaries that point to the second x value in the jump
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0.5, 1. ],
                                                      values = [ 0., 0.5, 1., 1.25, 1.5 ],
                                                      boundaries = [ 2, 4 ],   # <-- pointing to end of the jump
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk5( self, chunk )

        # the data is given explicitly with a jump at the end that goes to zero
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1., 1. ], # <-- jump at end
                                                      values = [ 0., 0.5, 0.75, 1., 0. ], # <-- last value is zero
                                                      boundaries = [ 1, 4 ],      # <-- pointing to end
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk6( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( energies = [], values = [] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( energies = [ 1. ], values = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( energies = [ 1., 2., 3., 4. ],
                                                          values = [ 4., 3., 2. ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( energies = [ 1., 2., 3., 4. ],
                                                          values = [ 4., 3., 2., 1. ],
                                                          boundaries = [ 3 ],
                                                          interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( energies = [ 1., 3., 2., 4. ],
                                                          values = [ 4., 3., 2., 1. ] )

        # the x grid contains a triple x value
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( energies = [ 1., 2., 2., 2., 3., 4. ],
                                                          values = [ 4., 3., 3., 3., 2., 1. ] )

        # the x grid has a jump at the beginning
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( energies = [ 1., 1., 3., 4. ],
                                                          values = [ 4., 3., 1., 4. ] )

        # the x grid has a jump at the end
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( energies = [ 1., 2., 4., 4. ],
                                                          values = [ 4., 3., 1., 4. ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( energies = [ 1., 2., 3., 4. ],
                                                          values = [ 4., 3., 2., 1. ],
                                                          boundaries = [ 2 ],
                                                          interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
