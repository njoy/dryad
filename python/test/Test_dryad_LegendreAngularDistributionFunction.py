# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import LegendreAngularDistributionFunction
from dryad import InterpolationType
from dryad import ToleranceConvergence

class Test_dryad_LegendreAngularDistributionFunction( unittest.TestCase ) :
    """Unit test for the LegendreAngularDistributionFunction class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.order )

            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -10.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual(  -4.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.4             , chunk.coefficients[3] )

            # verify evaluation
            self.assertAlmostEqual(  -8.0, chunk( cosine =  0. ) )
            self.assertAlmostEqual(   0.0, chunk( cosine =  1. ) )
            self.assertAlmostEqual( -30.0, chunk( cosine = -1. ) )

            # verify linearisation
            convergence = ToleranceConvergence( 0.01 )
            linear = chunk.linearise( convergence )

            self.assertEqual( 21, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 21, len( linear.cosines ) )
            self.assertEqual( 21, len( linear.values ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 20, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( -1.0      , linear.cosines[0] )
            self.assertAlmostEqual( -0.75     , linear.cosines[1] )
            self.assertAlmostEqual( -0.5      , linear.cosines[2] )
            self.assertAlmostEqual( -0.25     , linear.cosines[3] )
            self.assertAlmostEqual( -0.125    , linear.cosines[4] )
            self.assertAlmostEqual(  0.0      , linear.cosines[5] )
            self.assertAlmostEqual(  0.125    , linear.cosines[6] )
            self.assertAlmostEqual(  0.25     , linear.cosines[7] )
            self.assertAlmostEqual(  0.375    , linear.cosines[8] )
            self.assertAlmostEqual(  0.5      , linear.cosines[9] )
            self.assertAlmostEqual(  0.625    , linear.cosines[10] )
            self.assertAlmostEqual(  0.6875   , linear.cosines[11] )
            self.assertAlmostEqual(  0.75     , linear.cosines[12] )
            self.assertAlmostEqual(  0.8125   , linear.cosines[13] )
            self.assertAlmostEqual(  0.875    , linear.cosines[14] )
            self.assertAlmostEqual(  0.90625  , linear.cosines[15] )
            self.assertAlmostEqual(  0.9375   , linear.cosines[16] )
            self.assertAlmostEqual(  0.96875  , linear.cosines[17] )
            self.assertAlmostEqual(  0.984375 , linear.cosines[18] )
            self.assertAlmostEqual(  0.9921875, linear.cosines[19] )
            self.assertAlmostEqual(  1.0      , linear.cosines[20] )

            self.assertAlmostEqual( -30.0      , linear.values[0] )
            self.assertAlmostEqual( -22.859375 , linear.values[1] )
            self.assertAlmostEqual( -16.875    , linear.values[2] )
            self.assertAlmostEqual( -11.953125 , linear.values[3] )
            self.assertAlmostEqual( -9.86132813, linear.values[4] )
            self.assertAlmostEqual( -8.0       , linear.values[5] )
            self.assertAlmostEqual( -6.35742188, linear.values[6] )
            self.assertAlmostEqual( -4.921875  , linear.values[7] )
            self.assertAlmostEqual( -3.68164063, linear.values[8] )
            self.assertAlmostEqual( -2.625     , linear.values[9] )
            self.assertAlmostEqual( -1.74023438, linear.values[10] )
            self.assertAlmostEqual( -1.35864258, linear.values[11] )
            self.assertAlmostEqual( -1.015625  , linear.values[12] )
            self.assertAlmostEqual( -0.70971680, linear.values[13] )
            self.assertAlmostEqual( -0.43945313, linear.values[14] )
            self.assertAlmostEqual( -0.31723023, linear.values[15] )
            self.assertAlmostEqual( -0.20336914, linear.values[16] )
            self.assertAlmostEqual( -0.09768677, linear.values[17] )
            self.assertAlmostEqual( -0.04785538, linear.values[18] )
            self.assertAlmostEqual( -0.02368212, linear.values[19] )
            self.assertAlmostEqual(  0.0       , linear.values[20] )

            self.assertEqual( True, linear.is_linearised )

            # verify arithmetic operators
            small = LegendreAngularDistributionFunction( [ 3., 0., 1. ] )
            equal = LegendreAngularDistributionFunction( [ 3., 0., 0., 1. ] )
            large = LegendreAngularDistributionFunction( [ 3., 0., 0., 0., 1. ] )

            result = -chunk
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual(  10.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual( -14.6             , result.coefficients[1] )
            self.assertAlmostEqual(   4.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(  -0.4             , result.coefficients[3] )

            chunk += 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual( 14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual( -4.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(  0.4             , chunk.coefficients[3] )

            chunk -= 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -10.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual(  -4.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.4             , chunk.coefficients[3] )

            chunk += small
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -7.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual( 14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual( -3.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(  0.4             , chunk.coefficients[3] )

            chunk -= small
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -10.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual(  -4.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.4             , chunk.coefficients[3] )

            chunk += equal
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -7.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual( 14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual( -4.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(  1.4             , chunk.coefficients[3] )

            chunk -= equal
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -10.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual(  -4.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.4             , chunk.coefficients[3] )

            chunk += large
            self.assertEqual( 4, chunk.order )
            self.assertEqual( 5, len( chunk.coefficients ) )
            self.assertAlmostEqual( -7.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual( 14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual( -4.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(  0.4             , chunk.coefficients[3] )
            self.assertAlmostEqual(  1.              , chunk.coefficients[4] )

            chunk -= large
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -10.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual(  -4.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.4             , chunk.coefficients[3] )

            chunk *= 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -20.66666666666666, chunk.coefficients[0] )
            self.assertAlmostEqual(  29.2             , chunk.coefficients[1] )
            self.assertAlmostEqual(  -9.33333333333333, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.8             , chunk.coefficients[3] )

            chunk /= 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -10.33333333333333, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.6             , chunk.coefficients[1] )
            self.assertAlmostEqual(  -4.66666666666666, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.4             , chunk.coefficients[3] )

            result = chunk * 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -20.66666666666666, result.coefficients[0] )
            self.assertAlmostEqual(  29.2             , result.coefficients[1] )
            self.assertAlmostEqual(  -9.33333333333333, result.coefficients[2] )
            self.assertAlmostEqual(   0.8             , result.coefficients[3] )

            result = 2. * chunk
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -20.66666666666666, result.coefficients[0] )
            self.assertAlmostEqual(  29.2             , result.coefficients[1] )
            self.assertAlmostEqual(  -9.33333333333333, result.coefficients[2] )
            self.assertAlmostEqual(   0.8             , result.coefficients[3] )

            result = chunk / 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -5.16666666666666, result.coefficients[0] )
            self.assertAlmostEqual(  7.3             , result.coefficients[1] )
            self.assertAlmostEqual( -2.33333333333333, result.coefficients[2] )
            self.assertAlmostEqual(  0.2             , result.coefficients[3] )

            result = chunk + 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -8.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual( 14.6             , result.coefficients[1] )
            self.assertAlmostEqual( -4.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(  0.4             , result.coefficients[3] )

            result = 2. + chunk
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -8.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual( 14.6             , result.coefficients[1] )
            self.assertAlmostEqual( -4.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(  0.4             , result.coefficients[3] )

            result = chunk - 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -12.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual(  14.6             , result.coefficients[1] )
            self.assertAlmostEqual(  -4.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(   0.4             , result.coefficients[3] )

            result = 2. - chunk
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual(  12.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual( -14.6             , result.coefficients[1] )
            self.assertAlmostEqual(   4.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(  -0.4             , result.coefficients[3] )

            result = chunk + small
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -7.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual( 14.6             , result.coefficients[1] )
            self.assertAlmostEqual( -3.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(  0.4             , result.coefficients[3] )

            result = chunk - small
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -13.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual(  14.6             , result.coefficients[1] )
            self.assertAlmostEqual(  -5.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(   0.4             , result.coefficients[3] )

            result = chunk + equal
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -7.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual( 14.6             , result.coefficients[1] )
            self.assertAlmostEqual( -4.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(  1.4             , result.coefficients[3] )

            result = chunk - equal
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -13.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual(  14.6             , result.coefficients[1] )
            self.assertAlmostEqual(  -4.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(  -0.6             , result.coefficients[3] )

            result = chunk + large
            self.assertEqual( 4, result.order )
            self.assertEqual( 5, len( result.coefficients ) )
            self.assertAlmostEqual( -7.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual( 14.6             , result.coefficients[1] )
            self.assertAlmostEqual( -4.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(  0.4             , result.coefficients[3] )
            self.assertAlmostEqual(  1.              , result.coefficients[4] )

            result = chunk - large
            self.assertEqual( 4, result.order )
            self.assertEqual( 5, len( result.coefficients ) )
            self.assertAlmostEqual( -13.33333333333333, result.coefficients[0] )
            self.assertAlmostEqual(  14.6             , result.coefficients[1] )
            self.assertAlmostEqual(  -4.66666666666666, result.coefficients[2] )
            self.assertAlmostEqual(   0.4             , result.coefficients[3] )
            self.assertAlmostEqual(  -1.              , result.coefficients[4] )

        # the data is given explicitly
        chunk = LegendreAngularDistributionFunction( coefficients = [ -31./3., 73./5., -14./3., 2./5. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the coefficient vector is empty
        with self.assertRaises( Exception ) :

            chunk = LegendreAngularDistributionFunction( coefficients = [] )

if __name__ == '__main__' :

    unittest.main()
