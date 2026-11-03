# standard imports
import unittest
from copy import copy
import sys

# third party imports

# local imports
from njoy.dryad import TabulatedAngularDistributionFunction
from njoy.dryad import InterpolationType

class Test_TabulatedAngularDistributionFunction( unittest.TestCase ) :
    """Unit test for the TabulatedAngularDistributionFunction class."""

    def test_component( self ) :

        def verify_chunk1( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0. , chunk( cosine = -1. ) )
            self.assertAlmostEqual( 0.5, chunk( cosine = 0. ) )
            self.assertAlmostEqual( 0.75, chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 1. , chunk( cosine = 1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0., chunk( cosine = -5. ) )
            self.assertAlmostEqual( 0., chunk( cosine = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 0.25 , chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 0.875, chunk( cosine = 0.75 ) )

            # verify integration
            self.assertAlmostEqual( 1., chunk.integral )

            # verify cumulative integration
            cumulative = chunk.cumulative_integral
            self.assertEqual( 4, len( cumulative ) )
            self.assertAlmostEqual( 0. , cumulative[0] )
            self.assertAlmostEqual( 0.25 , cumulative[1] )
            self.assertAlmostEqual( 0.5625, cumulative[2] )
            self.assertAlmostEqual( 1. , cumulative[3] )

            # verify the mean
            self.assertAlmostEqual( 1. / 3., chunk.mean )

            # verify arithmetic operators
            same = TabulatedAngularDistributionFunction( [ -1., 1. ], [ 1., 0. ] )
            threshold = TabulatedAngularDistributionFunction( [ 0., 1. ], [ 0., 2. ] )
            nonzerothreshold = TabulatedAngularDistributionFunction( [ 0., 1. ], [ 1., 1. ] )
            small = TabulatedAngularDistributionFunction( [ -1., 0. ], [ 0., 1. ] )

            chunk += 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 2. , chunk.values[0] )
            self.assertAlmostEqual( 2.5 , chunk.values[1] )
            self.assertAlmostEqual( 2.75, chunk.values[2] )
            self.assertAlmostEqual( 3. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk *= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5, chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 1. , chunk.values[1] )
            self.assertAlmostEqual( 1.5, chunk.values[2] )
            self.assertAlmostEqual( 2. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk /= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = -chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( -0.5 , result.values[1] )
            self.assertAlmostEqual( -0.75, result.values[2] )
            self.assertAlmostEqual( -1. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk + 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 2. , result.values[0] )
            self.assertAlmostEqual( 2.5 , result.values[1] )
            self.assertAlmostEqual( 2.75, result.values[2] )
            self.assertAlmostEqual( 3. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. + chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 2. , result.values[0] )
            self.assertAlmostEqual( 2.5 , result.values[1] )
            self.assertAlmostEqual( 2.75, result.values[2] )
            self.assertAlmostEqual( 3. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( -2. , result.values[0] )
            self.assertAlmostEqual( -1.5 , result.values[1] )
            self.assertAlmostEqual( -1.25, result.values[2] )
            self.assertAlmostEqual( -1. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. - chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 2. , result.values[0] )
            self.assertAlmostEqual( 1.5 , result.values[1] )
            self.assertAlmostEqual( 1.25, result.values[2] )
            self.assertAlmostEqual( 1. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk * 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5, result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 1. , result.values[1] )
            self.assertAlmostEqual( 1.5, result.values[2] )
            self.assertAlmostEqual( 2. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. * chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5, result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 1. , result.values[1] )
            self.assertAlmostEqual( 1.5, result.values[2] )
            self.assertAlmostEqual( 2. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk / 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 0.25 , result.values[1] )
            self.assertAlmostEqual( 0.375, result.values[2] )
            self.assertAlmostEqual( 0.5 , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += same

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5, chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.values[0] )
            self.assertAlmostEqual( 1. , chunk.values[1] )
            self.assertAlmostEqual( 1. , chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= same

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + same

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5, result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 1. , result.values[0] )
            self.assertAlmostEqual( 1. , result.values[1] )
            self.assertAlmostEqual( 1. , result.values[2] )
            self.assertAlmostEqual( 1. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - same

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5, result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( -1. , result.values[0] )
            self.assertAlmostEqual( 0. , result.values[1] )
            self.assertAlmostEqual( 0.5, result.values[2] )
            self.assertAlmostEqual( 1. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += threshold

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 1.75, chunk.values[2] )
            self.assertAlmostEqual( 3. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= threshold

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + threshold

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 0.5 , result.values[1] )
            self.assertAlmostEqual( 1.75, result.values[2] )
            self.assertAlmostEqual( 3. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - threshold

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 0.5 , result.values[1] )
            self.assertAlmostEqual( -0.25, result.values[2] )
            self.assertAlmostEqual( -1. , result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += nonzerothreshold

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 1.5 , chunk.values[2] )
            self.assertAlmostEqual( 1.75, chunk.values[3] )
            self.assertAlmostEqual( 2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= nonzerothreshold

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + nonzerothreshold

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5 , result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 0.5 , result.values[1] )
            self.assertAlmostEqual( 1.5 , result.values[2] )
            self.assertAlmostEqual( 1.75, result.values[3] )
            self.assertAlmostEqual( 2. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - nonzerothreshold

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5 , result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 0.5 , result.values[1] )
            self.assertAlmostEqual( -0.5 , result.values[2] )
            self.assertAlmostEqual( -0.25, result.values[3] )
            self.assertAlmostEqual( 0. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            # this will add a second point at the upper end point of small
            result = chunk + small

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5 , result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 1.5 , result.values[1] )
            self.assertAlmostEqual( 0.5 , result.values[2] )
            self.assertAlmostEqual( 0.75, result.values[3] )
            self.assertAlmostEqual( 1. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            # this will add a second point at the upper end point of small
            result = chunk - small

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5 , result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( -0.5 , result.values[1] )
            self.assertAlmostEqual( 0.5 , result.values[2] )
            self.assertAlmostEqual( 0.75, result.values[3] )
            self.assertAlmostEqual( 1. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            # verify linearisation
            linear = chunk.linearise()

            self.assertAlmostEqual( -1., linear.lower_cosine_limit )
            self.assertAlmostEqual( 1., linear.upper_cosine_limit )
            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 4, len( linear.cosines ) )
            self.assertEqual( 4, len( linear.values ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 3, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( -1. , linear.cosines[0] )
            self.assertAlmostEqual( 0. , linear.cosines[1] )
            self.assertAlmostEqual( 0.5 , linear.cosines[2] )
            self.assertAlmostEqual( 1. , linear.cosines[3] )
            self.assertAlmostEqual( 0. , linear.values[0] )
            self.assertAlmostEqual( 0.5 , linear.values[1] )
            self.assertAlmostEqual( 0.75, linear.values[2] )
            self.assertAlmostEqual( 1. , linear.values[3] )

            self.assertEqual( True, linear.is_linearised )
            self.assertEqual( True, linear.is_curated )

        def verify_chunk2( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 4. , chunk.values[0] )
            self.assertAlmostEqual( 3. , chunk.values[1] )
            self.assertAlmostEqual( 4. , chunk.values[2] )
            self.assertAlmostEqual( 3. , chunk.values[3] )
            self.assertAlmostEqual( 2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( cosine = -1. ) )
            self.assertAlmostEqual( 4., chunk( cosine = 0. ) )
            self.assertAlmostEqual( 3., chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 2., chunk( cosine = 1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0., chunk( cosine = -2. ) )
            self.assertAlmostEqual( 0., chunk( cosine = 2. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 3.5, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 3.5, chunk( cosine = 0.25 ) )
            self.assertAlmostEqual( 2.5, chunk( cosine = 0.75 ) )

            # verify integration
            self.assertAlmostEqual( 6.5, chunk.integral )

            # verify cumulative integration
            cumulative = chunk.cumulative_integral
            self.assertEqual( 5, len( cumulative ) )
            self.assertAlmostEqual( 0. , cumulative[0] )
            self.assertAlmostEqual( 3.5 , cumulative[1] )
            self.assertAlmostEqual( 3.5 , cumulative[2] )
            self.assertAlmostEqual( 5.25, cumulative[3] )
            self.assertAlmostEqual( 6.5 , cumulative[4] )

            # verify the mean
            self.assertAlmostEqual( -0.5 / 6.5, chunk.mean )

            # verify linearisation
            linear = chunk.linearise()

            self.assertAlmostEqual( -1., linear.lower_cosine_limit )
            self.assertAlmostEqual( 1., linear.upper_cosine_limit )
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
            self.assertAlmostEqual( 0. , linear.cosines[1] )
            self.assertAlmostEqual( 0. , linear.cosines[2] )
            self.assertAlmostEqual( 0.5, linear.cosines[3] )
            self.assertAlmostEqual( 1. , linear.cosines[4] )

            self.assertAlmostEqual( 4., linear.values[0] )
            self.assertAlmostEqual( 3., linear.values[1] )
            self.assertAlmostEqual( 4., linear.values[2] )
            self.assertAlmostEqual( 3., linear.values[3] )
            self.assertAlmostEqual( 2., linear.values[4] )

            self.assertEqual( True, linear.is_linearised )
            self.assertEqual( True, linear.is_curated )

            # verify arithmetic operators
            same = TabulatedAngularDistributionFunction( [ -1., 1. ], [ 1., 0. ] )
            threshold = TabulatedAngularDistributionFunction( [ 0., 1. ], [ 0., 2. ] )
            nonzerothreshold = TabulatedAngularDistributionFunction( [ 0.5, 1. ], [ 1., 1. ] )
            small = TabulatedAngularDistributionFunction( [ -1., 0.5 ], [ 1., 1. ] )

            chunk += 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 6. , chunk.values[0] )
            self.assertAlmostEqual( 5. , chunk.values[1] )
            self.assertAlmostEqual( 6. , chunk.values[2] )
            self.assertAlmostEqual( 5. , chunk.values[3] )
            self.assertAlmostEqual( 4. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 4. , chunk.values[0] )
            self.assertAlmostEqual( 3. , chunk.values[1] )
            self.assertAlmostEqual( 4. , chunk.values[2] )
            self.assertAlmostEqual( 3. , chunk.values[3] )
            self.assertAlmostEqual( 2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk *= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 8. , chunk.values[0] )
            self.assertAlmostEqual( 6. , chunk.values[1] )
            self.assertAlmostEqual( 8. , chunk.values[2] )
            self.assertAlmostEqual( 6. , chunk.values[3] )
            self.assertAlmostEqual( 4. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk /= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 4. , chunk.values[0] )
            self.assertAlmostEqual( 3. , chunk.values[1] )
            self.assertAlmostEqual( 4. , chunk.values[2] )
            self.assertAlmostEqual( 3. , chunk.values[3] )
            self.assertAlmostEqual( 2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = -chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( -4. , result.values[0] )
            self.assertAlmostEqual( -3. , result.values[1] )
            self.assertAlmostEqual( -4. , result.values[2] )
            self.assertAlmostEqual( -3. , result.values[3] )
            self.assertAlmostEqual( -2. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk + 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 6. , result.values[0] )
            self.assertAlmostEqual( 5. , result.values[1] )
            self.assertAlmostEqual( 6. , result.values[2] )
            self.assertAlmostEqual( 5. , result.values[3] )
            self.assertAlmostEqual( 4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. + chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 6. , result.values[0] )
            self.assertAlmostEqual( 5. , result.values[1] )
            self.assertAlmostEqual( 6. , result.values[2] )
            self.assertAlmostEqual( 5. , result.values[3] )
            self.assertAlmostEqual( 4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 2. , result.values[0] )
            self.assertAlmostEqual( 1. , result.values[1] )
            self.assertAlmostEqual( 2. , result.values[2] )
            self.assertAlmostEqual( 1. , result.values[3] )
            self.assertAlmostEqual( 0. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. - chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( -2. , result.values[0] )
            self.assertAlmostEqual( -1. , result.values[1] )
            self.assertAlmostEqual( -2. , result.values[2] )
            self.assertAlmostEqual( -1. , result.values[3] )
            self.assertAlmostEqual( 0. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk * 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 8. , result.values[0] )
            self.assertAlmostEqual( 6. , result.values[1] )
            self.assertAlmostEqual( 8. , result.values[2] )
            self.assertAlmostEqual( 6. , result.values[3] )
            self.assertAlmostEqual( 4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. * chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 8. , result.values[0] )
            self.assertAlmostEqual( 6. , result.values[1] )
            self.assertAlmostEqual( 8. , result.values[2] )
            self.assertAlmostEqual( 6. , result.values[3] )
            self.assertAlmostEqual( 4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk / 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 2. , result.values[0] )
            self.assertAlmostEqual( 1.5, result.values[1] )
            self.assertAlmostEqual( 2. , result.values[2] )
            self.assertAlmostEqual( 1.5, result.values[3] )
            self.assertAlmostEqual( 1. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            chunk += same

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 5. , chunk.values[0] )
            self.assertAlmostEqual( 3.5 , chunk.values[1] )
            self.assertAlmostEqual( 4.5 , chunk.values[2] )
            self.assertAlmostEqual( 3.25, chunk.values[3] )
            self.assertAlmostEqual( 2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= same

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 4. , chunk.values[0] )
            self.assertAlmostEqual( 3. , chunk.values[1] )
            self.assertAlmostEqual( 4. , chunk.values[2] )
            self.assertAlmostEqual( 3. , chunk.values[3] )
            self.assertAlmostEqual( 2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + same

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5 , result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 5. , result.values[0] )
            self.assertAlmostEqual( 3.5 , result.values[1] )
            self.assertAlmostEqual( 4.5 , result.values[2] )
            self.assertAlmostEqual( 3.25, result.values[3] )
            self.assertAlmostEqual( 2. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - same

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5 , result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 3. , result.values[0] )
            self.assertAlmostEqual( 2.5 , result.values[1] )
            self.assertAlmostEqual( 3.5 , result.values[2] )
            self.assertAlmostEqual( 2.75, result.values[3] )
            self.assertAlmostEqual( 2. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            chunk += threshold

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 4. , chunk.values[0] )
            self.assertAlmostEqual( 3. , chunk.values[1] )
            self.assertAlmostEqual( 4. , chunk.values[2] )
            self.assertAlmostEqual( 4. , chunk.values[3] )
            self.assertAlmostEqual( 4. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= threshold

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 4. , chunk.values[0] )
            self.assertAlmostEqual( 3. , chunk.values[1] )
            self.assertAlmostEqual( 4. , chunk.values[2] )
            self.assertAlmostEqual( 3. , chunk.values[3] )
            self.assertAlmostEqual( 2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + threshold

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 4. , result.values[0] )
            self.assertAlmostEqual( 3. , result.values[1] )
            self.assertAlmostEqual( 4. , result.values[2] )
            self.assertAlmostEqual( 4. , result.values[3] )
            self.assertAlmostEqual( 4. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - threshold

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 4. , result.values[0] )
            self.assertAlmostEqual( 3. , result.values[1] )
            self.assertAlmostEqual( 4. , result.values[2] )
            self.assertAlmostEqual( 2. , result.values[3] )
            self.assertAlmostEqual( 0. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            chunk += nonzerothreshold

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 6, chunk.number_points )
            self.assertEqual( 3, chunk.number_regions )
            self.assertEqual( 6, len( chunk.cosines ) )
            self.assertEqual( 6, len( chunk.values ) )
            self.assertEqual( 3, len( chunk.boundaries ) )
            self.assertEqual( 3, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 0.5, chunk.cosines[4] )
            self.assertAlmostEqual( 1. , chunk.cosines[5] )
            self.assertAlmostEqual( 4. , chunk.values[0] )
            self.assertAlmostEqual( 3. , chunk.values[1] )
            self.assertAlmostEqual( 4. , chunk.values[2] )
            self.assertAlmostEqual( 3. , chunk.values[3] )
            self.assertAlmostEqual( 4. , chunk.values[4] )
            self.assertAlmostEqual( 3. , chunk.values[5] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( 5, chunk.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[2] )

            chunk -= nonzerothreshold

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 4. , chunk.values[0] )
            self.assertAlmostEqual( 3. , chunk.values[1] )
            self.assertAlmostEqual( 4. , chunk.values[2] )
            self.assertAlmostEqual( 3. , chunk.values[3] )
            self.assertAlmostEqual( 2. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + nonzerothreshold

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 6, result.number_points )
            self.assertEqual( 3, result.number_regions )
            self.assertEqual( 6, len( result.cosines ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 0.5, result.cosines[4] )
            self.assertAlmostEqual( 1. , result.cosines[5] )
            self.assertAlmostEqual( 4. , result.values[0] )
            self.assertAlmostEqual( 3. , result.values[1] )
            self.assertAlmostEqual( 4. , result.values[2] )
            self.assertAlmostEqual( 3. , result.values[3] )
            self.assertAlmostEqual( 4. , result.values[4] )
            self.assertAlmostEqual( 3. , result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            result = chunk - nonzerothreshold

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 6, result.number_points )
            self.assertEqual( 3, result.number_regions )
            self.assertEqual( 6, len( result.cosines ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 0.5, result.cosines[4] )
            self.assertAlmostEqual( 1. , result.cosines[5] )
            self.assertAlmostEqual( 4. , result.values[0] )
            self.assertAlmostEqual( 3. , result.values[1] )
            self.assertAlmostEqual( 4. , result.values[2] )
            self.assertAlmostEqual( 3. , result.values[3] )
            self.assertAlmostEqual( 2. , result.values[4] )
            self.assertAlmostEqual( 1. , result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            # this will add a second point at the upper end point of small
            result = chunk + small

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 6, result.number_points )
            self.assertEqual( 3, result.number_regions )
            self.assertEqual( 6, len( result.cosines ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 0.5, result.cosines[4] )
            self.assertAlmostEqual( 1. , result.cosines[5] )
            self.assertAlmostEqual( 5. , result.values[0] )
            self.assertAlmostEqual( 4. , result.values[1] )
            self.assertAlmostEqual( 5. , result.values[2] )
            self.assertAlmostEqual( 4. , result.values[3] )
            self.assertAlmostEqual( 3. , result.values[4] )
            self.assertAlmostEqual( 2. , result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            # this will add a second point at the upper end point of small
            result = chunk - small

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 6, result.number_points )
            self.assertEqual( 3, result.number_regions )
            self.assertEqual( 6, len( result.cosines ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 0.5, result.cosines[4] )
            self.assertAlmostEqual( 1. , result.cosines[5] )
            self.assertAlmostEqual( 3. , result.values[0] )
            self.assertAlmostEqual( 2. , result.values[1] )
            self.assertAlmostEqual( 3. , result.values[2] )
            self.assertAlmostEqual( 2. , result.values[3] )
            self.assertAlmostEqual( 3. , result.values[4] )
            self.assertAlmostEqual( 2. , result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

        def verify_chunk3( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0. , chunk( cosine = -1. ) )
            self.assertAlmostEqual( 0.5 , chunk( cosine = 0. ) )
            self.assertAlmostEqual( 0.75, chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 1. , chunk( cosine = 1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0., chunk( cosine = -2. ) )
            self.assertAlmostEqual( 0., chunk( cosine = 2. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 0.25, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 0.61237243569579, chunk( cosine = 0.25 ) )
            self.assertAlmostEqual( 0.86602540378444, chunk( cosine = 0.75 ) )

            # verify integration
            self.assertAlmostEqual( 0.99279536989483, chunk.integral )

            # verify cumulative integration
            cumulative = chunk.cumulative_integral
            self.assertEqual( 4, len( cumulative ) )
            self.assertAlmostEqual( 0. , cumulative[0] )
            self.assertAlmostEqual( 0.25 , cumulative[1] )
            self.assertAlmostEqual( 0.558287932797054, cumulative[2] )
            self.assertAlmostEqual( 0.99279536989483 , cumulative[3] )

            # verify the mean
            self.assertAlmostEqual( 0.330014509000453 / 0.99279536989483, chunk.mean )

            # verify linearisation
            linear = chunk.linearise()

            self.assertAlmostEqual( -1., linear.lower_cosine_limit )
            self.assertAlmostEqual( 1., linear.upper_cosine_limit )
            self.assertEqual( 14, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 14, len( linear.cosines ) )
            self.assertEqual( 14, len( linear.values ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 13, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( -1. , linear.cosines[0] )
            self.assertAlmostEqual( 0. , linear.cosines[1] )
            self.assertAlmostEqual( 0.0625, linear.cosines[2] )
            self.assertAlmostEqual( 0.125 , linear.cosines[3] )
            self.assertAlmostEqual( 0.1875, linear.cosines[4] )
            self.assertAlmostEqual( 0.25 , linear.cosines[5] )
            self.assertAlmostEqual( 0.3125, linear.cosines[6] )
            self.assertAlmostEqual( 0.375 , linear.cosines[7] )
            self.assertAlmostEqual( 0.4375, linear.cosines[8] )
            self.assertAlmostEqual( 0.5 , linear.cosines[9] )
            self.assertAlmostEqual( 0.625 , linear.cosines[10] )
            self.assertAlmostEqual( 0.75 , linear.cosines[11] )
            self.assertAlmostEqual( 0.875 , linear.cosines[12] )
            self.assertAlmostEqual( 1. , linear.cosines[13] )

            self.assertAlmostEqual( 0. , linear.values[0] )
            self.assertAlmostEqual( 0.5 , linear.values[1] )
            self.assertAlmostEqual( 0.52599475275432, linear.values[2] )
            self.assertAlmostEqual( 0.55334095985016, linear.values[3] )
            self.assertAlmostEqual( 0.58210888273045, linear.values[4] )
            self.assertAlmostEqual( 0.61237243569579, linear.values[5] )
            self.assertAlmostEqual( 0.64420937581474, linear.values[6] )
            self.assertAlmostEqual( 0.67770150270738, linear.values[7] )
            self.assertAlmostEqual( 0.71293486871561, linear.values[8] )
            self.assertAlmostEqual( 0.75 , linear.values[9] )
            self.assertAlmostEqual( 0.80592744886766, linear.values[10] )
            self.assertAlmostEqual( 0.86602540378444, linear.values[11] )
            self.assertAlmostEqual( 0.93060485910210, linear.values[12] )
            self.assertAlmostEqual( 1. , linear.values[13] )

            self.assertEqual( True, linear.is_linearised )
            self.assertEqual( True, linear.is_curated )

            # verify arithmetic operators
            chunk *= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 1. , chunk.values[1] )
            self.assertAlmostEqual( 1.5 , chunk.values[2] )
            self.assertAlmostEqual( 2. , chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            chunk /= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            result = -chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( -0. , result.values[0] )
            self.assertAlmostEqual( -0.5 , result.values[1] )
            self.assertAlmostEqual( -0.75, result.values[2] )
            self.assertAlmostEqual( -1. , result.values[3] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, result.interpolants[1] )
            self.assertEqual( False, result.is_linearised )
            self.assertEqual( True, result.is_curated )

            result = chunk * 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 1. , result.values[1] )
            self.assertAlmostEqual( 1.5 , result.values[2] )
            self.assertAlmostEqual( 2. , result.values[3] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, result.interpolants[1] )
            self.assertEqual( False, result.is_linearised )
            self.assertEqual( True, result.is_curated )

            result = 2. * chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 1. , result.values[1] )
            self.assertAlmostEqual( 1.5 , result.values[2] )
            self.assertAlmostEqual( 2. , result.values[3] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, result.interpolants[1] )
            self.assertEqual( False, result.is_linearised )
            self.assertEqual( True, result.is_curated )

            result = chunk / 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 4, len( result.cosines ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0.5 , result.cosines[2] )
            self.assertAlmostEqual( 1. , result.cosines[3] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 0.25 , result.values[1] )
            self.assertAlmostEqual( 0.375, result.values[2] )
            self.assertAlmostEqual( 0.5 , result.values[3] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, result.interpolants[1] )
            self.assertEqual( False, result.is_linearised )
            self.assertEqual( True, result.is_curated )

            # verify arithmetic operators throw exceptions
            right = TabulatedAngularDistributionFunction( [ -1., 1. ], [ 0., 0. ] )

            # scalar operations
            with self.assertRaises( Exception ) : chunk += 2.
            with self.assertRaises( Exception ) : chunk -= 2.
            with self.assertRaises( Exception ) : result = chunk + 2.
            with self.assertRaises( Exception ) : result = chunk - 2.
            with self.assertRaises( Exception ) : result = 2. + chunk
            with self.assertRaises( Exception ) : result = 2. - chunk

            # table operations
            with self.assertRaises( Exception ) : chunk += right
            with self.assertRaises( Exception ) : chunk -= right
            with self.assertRaises( Exception ) : result = chunk + right
            with self.assertRaises( Exception ) : result = chunk - right
            with self.assertRaises( Exception ) : right += chunk
            with self.assertRaises( Exception ) : right -= chunk
            with self.assertRaises( Exception ) : result = right + chunk
            with self.assertRaises( Exception ) : result = right - chunk

            # the table is unchanged after the failed operations
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk4( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 1. , chunk.values[2] )
            self.assertAlmostEqual( 1.25, chunk.values[3] )
            self.assertAlmostEqual( 1.5 , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 0. , chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1. , chunk( cosine = 0. ) )
            self.assertAlmostEqual( 1.25, chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 1.5 , chunk( cosine = 1. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0., chunk( cosine = -2. ) )
            self.assertAlmostEqual( 0., chunk( cosine = 2. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 0.25, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 1.11803398874989, chunk( cosine = 0.25 ) )
            self.assertAlmostEqual( 1.36930639376292, chunk( cosine = 0.75 ) )

            # verify integration
            self.assertAlmostEqual( 1.49577938318395, chunk.integral )

            # verify cumulative integration
            cumulative = chunk.cumulative_integral
            self.assertEqual( 5, len( cumulative ) )
            self.assertAlmostEqual( 0. , cumulative[0] )
            self.assertAlmostEqual( 0.25 , cumulative[1] )
            self.assertAlmostEqual( 0.25 , cumulative[2] )
            self.assertAlmostEqual( 0.810177514715569, cumulative[3] )
            self.assertAlmostEqual( 1.49577938318395 , cumulative[4] )

            # verify the mean
            self.assertAlmostEqual( 0.581321912933929 / 1.49577938318395, chunk.mean )

            # verify linearisation
            linear = chunk.linearise()

            self.assertAlmostEqual( -1., linear.lower_cosine_limit )
            self.assertAlmostEqual( 1., linear.upper_cosine_limit )
            self.assertEqual( 11, linear.number_points )
            self.assertEqual( 2, linear.number_regions )

            self.assertEqual( 11, len( linear.cosines ) )
            self.assertEqual( 11, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )

            self.assertEqual( 1, linear.boundaries[0] )
            self.assertEqual( 10, linear.boundaries[1] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )

            self.assertAlmostEqual( -1. , linear.cosines[0] )
            self.assertAlmostEqual( 0. , linear.cosines[1] )
            self.assertAlmostEqual( 0. , linear.cosines[2] )
            self.assertAlmostEqual( 0.125, linear.cosines[3] )
            self.assertAlmostEqual( 0.25 , linear.cosines[4] )
            self.assertAlmostEqual( 0.375, linear.cosines[5] )
            self.assertAlmostEqual( 0.5 , linear.cosines[6] )
            self.assertAlmostEqual( 0.625, linear.cosines[7] )
            self.assertAlmostEqual( 0.75 , linear.cosines[8] )
            self.assertAlmostEqual( 0.875, linear.cosines[9] )
            self.assertAlmostEqual( 1. , linear.cosines[10] )

            self.assertAlmostEqual( 0. , linear.values[0] )
            self.assertAlmostEqual( 0.5 , linear.values[1] )
            self.assertAlmostEqual( 1. , linear.values[2] )
            self.assertAlmostEqual( 1.05737126344056, linear.values[3] )
            self.assertAlmostEqual( 1.11803398874989, linear.values[4] )
            self.assertAlmostEqual( 1.18217701125397, linear.values[5] )
            self.assertAlmostEqual( 1.25 , linear.values[6] )
            self.assertAlmostEqual( 1.30829392424013, linear.values[7] )
            self.assertAlmostEqual( 1.36930639376292, linear.values[8] )
            self.assertAlmostEqual( 1.43316418830655, linear.values[9] )
            self.assertAlmostEqual( 1.5 , linear.values[10] )

            self.assertEqual( True, linear.is_linearised )
            self.assertEqual( True, linear.is_curated )

            # verify arithmetic operators
            chunk *= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 1. , chunk.values[1] )
            self.assertAlmostEqual( 2. , chunk.values[2] )
            self.assertAlmostEqual( 2.5 , chunk.values[3] )
            self.assertAlmostEqual( 3. , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            chunk /= 2.

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 1.0 , chunk.values[2] )
            self.assertAlmostEqual( 1.25, chunk.values[3] )
            self.assertAlmostEqual( 1.5 , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            result = -chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( -0. , result.values[0] )
            self.assertAlmostEqual( -0.5 , result.values[1] )
            self.assertAlmostEqual( -1. , result.values[2] )
            self.assertAlmostEqual( -1.25, result.values[3] )
            self.assertAlmostEqual( -1.5 , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, result.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, result.is_curated )

            result = chunk * 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 1. , result.values[1] )
            self.assertAlmostEqual( 2. , result.values[2] )
            self.assertAlmostEqual( 2.5 , result.values[3] )
            self.assertAlmostEqual( 3. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, result.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, result.is_curated )

            result = 2. * chunk

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 1. , result.values[1] )
            self.assertAlmostEqual( 2. , result.values[2] )
            self.assertAlmostEqual( 2.5 , result.values[3] )
            self.assertAlmostEqual( 3. , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, result.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, result.is_curated )

            result = chunk / 2.

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.cosines ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( 0. , result.cosines[1] )
            self.assertAlmostEqual( 0. , result.cosines[2] )
            self.assertAlmostEqual( 0.5, result.cosines[3] )
            self.assertAlmostEqual( 1. , result.cosines[4] )
            self.assertAlmostEqual( 0. , result.values[0] )
            self.assertAlmostEqual( 0.25 , result.values[1] )
            self.assertAlmostEqual( 0.5 , result.values[2] )
            self.assertAlmostEqual( 0.625, result.values[3] )
            self.assertAlmostEqual( 0.75 , result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, result.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, result.is_curated )

            # verify arithmetic operators throw exceptions
            right = TabulatedAngularDistributionFunction( [ -1., 1. ], [ 0., 0. ] )

            # scalar operations
            with self.assertRaises( Exception ) : chunk += 2.
            with self.assertRaises( Exception ) : chunk -= 2.
            with self.assertRaises( Exception ) : result = chunk + 2.
            with self.assertRaises( Exception ) : result = chunk - 2.
            with self.assertRaises( Exception ) : result = 2. + chunk
            with self.assertRaises( Exception ) : result = 2. - chunk

            # table operations
            with self.assertRaises( Exception ) : chunk += right
            with self.assertRaises( Exception ) : chunk -= right
            with self.assertRaises( Exception ) : result = chunk + right
            with self.assertRaises( Exception ) : result = chunk - right
            with self.assertRaises( Exception ) : right += chunk
            with self.assertRaises( Exception ) : right -= chunk
            with self.assertRaises( Exception ) : result = right + chunk
            with self.assertRaises( Exception ) : result = right - chunk

            # the table is unchanged after the failed operations
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5 , chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 1. , chunk.values[2] )
            self.assertAlmostEqual( 1.25, chunk.values[3] )
            self.assertAlmostEqual( 1.5 , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk5( self, chunk ) :

            original = copy( chunk )

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 6, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 6, len( chunk.cosines ) )
            self.assertEqual( 6, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0. , chunk.cosines[3] )
            self.assertAlmostEqual( 0.5, chunk.cosines[4] )
            self.assertAlmostEqual( 1. , chunk.cosines[5] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.25, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertAlmostEqual( 1.25, chunk.values[4] )
            self.assertAlmostEqual( 1.5 , chunk.values[5] )
            self.assertEqual( 1, chunk.boundaries[0] )    # <-- this is changed from 2 to 1
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( False, chunk.is_curated )

            # the table can be curated on demand and the extraneous points are removed
            # note: curate() curates the table in place - it does not return a new instance
            chunk.curate()

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 1. , chunk.values[2] )
            self.assertAlmostEqual( 1.25, chunk.values[3] )
            self.assertAlmostEqual( 1.5 , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            # the table can be linearised and the extraneous point in the jump is removed
            chunk = copy( original )
            linear = chunk.linearise()

            self.assertAlmostEqual( -1., linear.lower_cosine_limit )
            self.assertAlmostEqual( 1., linear.upper_cosine_limit )
            self.assertEqual( 11, linear.number_points )
            self.assertEqual( 2, linear.number_regions )
            self.assertEqual( 11, len( linear.cosines ) )
            self.assertEqual( 11, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )
            self.assertAlmostEqual( -1. , linear.cosines[0] )
            self.assertAlmostEqual( 0. , linear.cosines[1] )
            self.assertAlmostEqual( 0. , linear.cosines[2] )
            self.assertAlmostEqual( 0.125, linear.cosines[3] )
            self.assertAlmostEqual( 0.25 , linear.cosines[4] )
            self.assertAlmostEqual( 0.375, linear.cosines[5] )
            self.assertAlmostEqual( 0.5 , linear.cosines[6] )
            self.assertAlmostEqual( 0.625, linear.cosines[7] )
            self.assertAlmostEqual( 0.75 , linear.cosines[8] )
            self.assertAlmostEqual( 0.875, linear.cosines[9] )
            self.assertAlmostEqual( 1. , linear.cosines[10] )
            self.assertAlmostEqual( 0. , linear.values[0] )
            self.assertAlmostEqual( 0.5 , linear.values[1] )
            self.assertAlmostEqual( 1. , linear.values[2] )
            self.assertAlmostEqual( 1.05737126344056, linear.values[3] )
            self.assertAlmostEqual( 1.11803398874989, linear.values[4] )
            self.assertAlmostEqual( 1.18217701125397, linear.values[5] )
            self.assertAlmostEqual( 1.25 , linear.values[6] )
            self.assertAlmostEqual( 1.30829392424013, linear.values[7] )
            self.assertAlmostEqual( 1.36930639376292, linear.values[8] )
            self.assertAlmostEqual( 1.43316418830655, linear.values[9] )
            self.assertAlmostEqual( 1.5 , linear.values[10] )
            self.assertEqual( 1, linear.boundaries[0] )
            self.assertEqual( 10, linear.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )
            self.assertEqual( True, linear.is_linearised )
            self.assertEqual( True, linear.is_curated )

            # the cumulative integral has a value for every x value, including the extraneous point in the jump
            cumulative = chunk.cumulative_integral
            self.assertEqual( 6, len( cumulative ) )
            self.assertAlmostEqual( 0. , cumulative[0] )
            self.assertAlmostEqual( 0.25 , cumulative[1] )
            self.assertAlmostEqual( 0.25 , cumulative[2] )    # <-- extraneous point
            self.assertAlmostEqual( 0.25 , cumulative[3] )
            self.assertAlmostEqual( 0.810177514715569, cumulative[4] )
            self.assertAlmostEqual( 1.49577938318395 , cumulative[5] )

        def verify_chunk6( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 1. , chunk.values[2] )
            self.assertAlmostEqual( 1.25, chunk.values[3] )
            self.assertAlmostEqual( 1.5 , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )    # <-- this is changed from 2 to 1
            self.assertEqual( 4, chunk.boundaries[1] )    # <-- this is changed from 5 to 4
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            # calling curate() again on an already curated table does not change anything
            chunk.curate()

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 1. , chunk.values[2] )
            self.assertAlmostEqual( 1.25, chunk.values[3] )
            self.assertAlmostEqual( 1.5 , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk7( self, chunk ) :

            original = copy( chunk )

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 9, chunk.number_points )
            self.assertEqual( 3, chunk.number_regions )
            self.assertEqual( 9, len( chunk.cosines ) )
            self.assertEqual( 9, len( chunk.values ) )
            self.assertEqual( 3, len( chunk.boundaries ) )
            self.assertEqual( 3, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.cosines[1] )
            self.assertAlmostEqual( -0.5, chunk.cosines[2] )
            self.assertAlmostEqual( -0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.cosines[4] )
            self.assertAlmostEqual( 0.5, chunk.cosines[5] )
            self.assertAlmostEqual( 0.5, chunk.cosines[6] )
            self.assertAlmostEqual( 0.5, chunk.cosines[7] )
            self.assertAlmostEqual( 1. , chunk.cosines[8] )
            self.assertAlmostEqual( 1., chunk.values[0] )
            self.assertAlmostEqual( 2., chunk.values[1] )
            self.assertAlmostEqual( 3., chunk.values[2] )
            self.assertAlmostEqual( 4., chunk.values[3] )
            self.assertAlmostEqual( 5., chunk.values[4] )
            self.assertAlmostEqual( 6., chunk.values[5] )
            self.assertAlmostEqual( 7., chunk.values[6] )
            self.assertAlmostEqual( 8., chunk.values[7] )
            self.assertAlmostEqual( 9., chunk.values[8] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( 8, chunk.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[2] )
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( False, chunk.is_curated )

            # a TabulatedAngularDistributionFunction can be evaluated and the extraneous points are ignored
            # note: in a jump, the table is evaluated using the last point of the jump
            self.assertAlmostEqual( 1. , chunk( cosine = -1. ) )
            self.assertAlmostEqual( 1.5, chunk( cosine = -0.75 ) )
            self.assertAlmostEqual( 4. , chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 4.5, chunk( cosine = -0.25 ) )
            self.assertAlmostEqual( 5. , chunk( cosine = 0. ) )
            self.assertAlmostEqual( 8. , chunk( cosine = 0.5 ) )
            self.assertAlmostEqual( 8.5, chunk( cosine = 0.75 ) )
            self.assertAlmostEqual( 9. , chunk( cosine = 1. ) )

            # arithmetic operations can be performed and the table remains uncurated
            same = TabulatedAngularDistributionFunction( [ -1., -0.5, -0.5, -0.5, 0., 0.5, 0.5, 0.5, 1. ], [ 1., 1., 1., 1., 1., 1., 1., 1., 1. ],
             )
            different = TabulatedAngularDistributionFunction( [ -1., 1. ], [ 0., 4. ] )

            chunk += 2.

            self.assertEqual( 9, chunk.number_points )
            self.assertEqual( 3, chunk.number_regions )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.cosines[1] )
            self.assertAlmostEqual( -0.5, chunk.cosines[2] )
            self.assertAlmostEqual( -0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.cosines[4] )
            self.assertAlmostEqual( 0.5, chunk.cosines[5] )
            self.assertAlmostEqual( 0.5, chunk.cosines[6] )
            self.assertAlmostEqual( 0.5, chunk.cosines[7] )
            self.assertAlmostEqual( 1. , chunk.cosines[8] )
            self.assertAlmostEqual( 3., chunk.values[0] )
            self.assertAlmostEqual( 4., chunk.values[1] )
            self.assertAlmostEqual( 5., chunk.values[2] )
            self.assertAlmostEqual( 6., chunk.values[3] )
            self.assertAlmostEqual( 7., chunk.values[4] )
            self.assertAlmostEqual( 8., chunk.values[5] )
            self.assertAlmostEqual( 9., chunk.values[6] )
            self.assertAlmostEqual( 10., chunk.values[7] )
            self.assertAlmostEqual( 11., chunk.values[8] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( 8, chunk.boundaries[2] )
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( False, chunk.is_curated )

            chunk -= same

            self.assertEqual( 9, chunk.number_points )
            self.assertEqual( 3, chunk.number_regions )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.cosines[1] )
            self.assertAlmostEqual( -0.5, chunk.cosines[2] )
            self.assertAlmostEqual( -0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.cosines[4] )
            self.assertAlmostEqual( 0.5, chunk.cosines[5] )
            self.assertAlmostEqual( 0.5, chunk.cosines[6] )
            self.assertAlmostEqual( 0.5, chunk.cosines[7] )
            self.assertAlmostEqual( 1. , chunk.cosines[8] )
            self.assertAlmostEqual( 2., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 5., chunk.values[3] )
            self.assertAlmostEqual( 6., chunk.values[4] )
            self.assertAlmostEqual( 7., chunk.values[5] )
            self.assertAlmostEqual( 8., chunk.values[6] )
            self.assertAlmostEqual( 9., chunk.values[7] )
            self.assertAlmostEqual( 10., chunk.values[8] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( 8, chunk.boundaries[2] )
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( False, chunk.is_curated )

            chunk *= 2.

            self.assertEqual( 9, chunk.number_points )
            self.assertEqual( 3, chunk.number_regions )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.cosines[1] )
            self.assertAlmostEqual( -0.5, chunk.cosines[2] )
            self.assertAlmostEqual( -0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.cosines[4] )
            self.assertAlmostEqual( 0.5, chunk.cosines[5] )
            self.assertAlmostEqual( 0.5, chunk.cosines[6] )
            self.assertAlmostEqual( 0.5, chunk.cosines[7] )
            self.assertAlmostEqual( 1. , chunk.cosines[8] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 6., chunk.values[1] )
            self.assertAlmostEqual( 8., chunk.values[2] )
            self.assertAlmostEqual( 10., chunk.values[3] )
            self.assertAlmostEqual( 12., chunk.values[4] )
            self.assertAlmostEqual( 14., chunk.values[5] )
            self.assertAlmostEqual( 16., chunk.values[6] )
            self.assertAlmostEqual( 18., chunk.values[7] )
            self.assertAlmostEqual( 20., chunk.values[8] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 5, chunk.boundaries[1] )
            self.assertEqual( 8, chunk.boundaries[2] )
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( False, chunk.is_curated )

            # note: the union grid keeps all points in the jumps of the uncurated table
            result = chunk + different

            self.assertAlmostEqual( -1., result.lower_cosine_limit )
            self.assertAlmostEqual( 1., result.upper_cosine_limit )
            self.assertEqual( 9, result.number_points )
            self.assertEqual( 3, result.number_regions )
            self.assertEqual( 9, len( result.cosines ) )
            self.assertEqual( 9, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( -1. , result.cosines[0] )
            self.assertAlmostEqual( -0.5, result.cosines[1] )
            self.assertAlmostEqual( -0.5, result.cosines[2] )
            self.assertAlmostEqual( -0.5, result.cosines[3] )
            self.assertAlmostEqual( 0. , result.cosines[4] )
            self.assertAlmostEqual( 0.5, result.cosines[5] )
            self.assertAlmostEqual( 0.5, result.cosines[6] )
            self.assertAlmostEqual( 0.5, result.cosines[7] )
            self.assertAlmostEqual( 1. , result.cosines[8] )
            self.assertAlmostEqual( 4., result.values[0] )
            self.assertAlmostEqual( 7., result.values[1] )
            self.assertAlmostEqual( 9., result.values[2] )
            self.assertAlmostEqual( 11., result.values[3] )
            self.assertAlmostEqual( 14., result.values[4] )
            self.assertAlmostEqual( 17., result.values[5] )
            self.assertAlmostEqual( 19., result.values[6] )
            self.assertAlmostEqual( 21., result.values[7] )
            self.assertAlmostEqual( 24., result.values[8] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 5, result.boundaries[1] )
            self.assertEqual( 8, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )
            self.assertEqual( True, result.is_linearised )
            self.assertEqual( False, result.is_curated )

            # the extraneous points are removed when calling curate()
            chunk = copy( original )
            chunk.curate()

            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 7, chunk.number_points )
            self.assertEqual( 3, chunk.number_regions )
            self.assertEqual( 7, len( chunk.cosines ) )
            self.assertEqual( 7, len( chunk.values ) )
            self.assertEqual( 3, len( chunk.boundaries ) )
            self.assertEqual( 3, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.cosines[1] )
            self.assertAlmostEqual( -0.5, chunk.cosines[2] )
            self.assertAlmostEqual( 0. , chunk.cosines[3] )
            self.assertAlmostEqual( 0.5, chunk.cosines[4] )
            self.assertAlmostEqual( 0.5, chunk.cosines[5] )
            self.assertAlmostEqual( 1. , chunk.cosines[6] )
            self.assertAlmostEqual( 1., chunk.values[0] )
            self.assertAlmostEqual( 2., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 5., chunk.values[3] )
            self.assertAlmostEqual( 6., chunk.values[4] )
            self.assertAlmostEqual( 8., chunk.values[5] )
            self.assertAlmostEqual( 9., chunk.values[6] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( 6, chunk.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[2] )
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk8( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 7, chunk.number_points )
            self.assertEqual( 3, chunk.number_regions )
            self.assertEqual( 7, len( chunk.cosines ) )
            self.assertEqual( 7, len( chunk.values ) )
            self.assertEqual( 3, len( chunk.boundaries ) )
            self.assertEqual( 3, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( -0.5, chunk.cosines[1] )
            self.assertAlmostEqual( -0.5, chunk.cosines[2] )
            self.assertAlmostEqual( 0. , chunk.cosines[3] )
            self.assertAlmostEqual( 0.5, chunk.cosines[4] )
            self.assertAlmostEqual( 0.5, chunk.cosines[5] )
            self.assertAlmostEqual( 1. , chunk.cosines[6] )
            self.assertAlmostEqual( 1., chunk.values[0] )
            self.assertAlmostEqual( 2., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 5., chunk.values[3] )
            self.assertAlmostEqual( 6., chunk.values[4] )
            self.assertAlmostEqual( 8., chunk.values[5] )
            self.assertAlmostEqual( 9., chunk.values[6] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( 6, chunk.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[2] )
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk9( self, chunk ) :

            # linearise() removes the extraneous point in the jump
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( False, chunk.is_curated )

            linear = chunk.linearise()

            self.assertAlmostEqual( -1., linear.lower_cosine_limit )
            self.assertAlmostEqual( 1., linear.upper_cosine_limit )
            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 2, linear.number_regions )
            self.assertEqual( 4, len( linear.cosines ) )
            self.assertEqual( 4, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )
            self.assertAlmostEqual( -1., linear.cosines[0] )
            self.assertAlmostEqual( 0., linear.cosines[1] )
            self.assertAlmostEqual( 0., linear.cosines[2] )
            self.assertAlmostEqual( 1., linear.cosines[3] )
            self.assertAlmostEqual( 1., linear.values[0] )
            self.assertAlmostEqual( 2., linear.values[1] )
            self.assertAlmostEqual( 3., linear.values[2] )
            self.assertAlmostEqual( 4., linear.values[3] )
            self.assertEqual( 1, linear.boundaries[0] )
            self.assertEqual( 3, linear.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )
            self.assertEqual( True, linear.is_linearised )
            self.assertEqual( True, linear.is_curated )

            # the cumulative integral has a value for every x value, including the extraneous point in the jump
            cumulative = chunk.cumulative_integral
            self.assertEqual( 5, len( cumulative ) )
            self.assertAlmostEqual( 0. , cumulative[0] )
            self.assertAlmostEqual( 1.5, cumulative[1] )
            self.assertAlmostEqual( 1.5, cumulative[2] )    # <-- extraneous point
            self.assertAlmostEqual( 1.5, cumulative[3] )
            self.assertAlmostEqual( 5. , cumulative[4] )

        def verify_chunk10( self, chunk ) :

            # linearise() removes the extraneous point in the jump and keeps the jump
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( False, chunk.is_curated )

            linear = chunk.linearise()

            self.assertAlmostEqual( -1., linear.lower_cosine_limit )
            self.assertAlmostEqual( 1., linear.upper_cosine_limit )
            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 2, linear.number_regions )
            self.assertEqual( 4, len( linear.cosines ) )
            self.assertEqual( 4, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )
            self.assertAlmostEqual( -1., linear.cosines[0] )
            self.assertAlmostEqual( 0., linear.cosines[1] )
            self.assertAlmostEqual( 0., linear.cosines[2] )
            self.assertAlmostEqual( 1., linear.cosines[3] )
            self.assertAlmostEqual( 1., linear.values[0] )
            self.assertAlmostEqual( 2., linear.values[1] )
            self.assertAlmostEqual( 3., linear.values[2] )
            self.assertAlmostEqual( 4., linear.values[3] )
            self.assertEqual( 1, linear.boundaries[0] )
            self.assertEqual( 3, linear.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )
            self.assertEqual( True, linear.is_linearised )
            self.assertEqual( True, linear.is_curated )

            self.assertAlmostEqual( 1.5, linear( cosine = -0.5 ) )
            self.assertAlmostEqual( 3.5, linear( cosine = 0.5 ) )

            # the cumulative integral has a value for every x value, including the extraneous point in the jump
            cumulative = chunk.cumulative_integral
            self.assertEqual( 5, len( cumulative ) )
            self.assertAlmostEqual( 0. , cumulative[0] )
            self.assertAlmostEqual( 1.5, cumulative[1] )
            self.assertAlmostEqual( 1.5, cumulative[2] )    # <-- extraneous point
            self.assertAlmostEqual( 1.5, cumulative[3] )
            self.assertAlmostEqual( 5. , cumulative[4] )

        def verify_chunk11( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1., chunk.cosines[0] )
            self.assertAlmostEqual( 0., chunk.cosines[1] )
            self.assertAlmostEqual( 0., chunk.cosines[2] )
            self.assertAlmostEqual( 1., chunk.cosines[3] )
            self.assertAlmostEqual( 1., chunk.values[0] )
            self.assertAlmostEqual( 2., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

            # verify integration
            self.assertAlmostEqual( 4., chunk.integral )

            # the cumulative integral has a value for every x value
            cumulative = chunk.cumulative_integral
            self.assertEqual( 4, len( cumulative ) )
            self.assertAlmostEqual( 0. , cumulative[0] )
            self.assertAlmostEqual( 1.5, cumulative[1] )
            self.assertAlmostEqual( 1.5, cumulative[2] )
            self.assertAlmostEqual( 4. , cumulative[3] )

        def verify_chunk12( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.cosines ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0. , chunk.cosines[2] )
            self.assertAlmostEqual( 0.5, chunk.cosines[3] )
            self.assertAlmostEqual( 1. , chunk.cosines[4] )
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 1. , chunk.values[2] )
            self.assertAlmostEqual( 1.25, chunk.values[3] )
            self.assertAlmostEqual( 1.5 , chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )    # <-- this is changed from 2 to 1
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk13( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5, chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )    # <-- last point removed
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )    # <-- last point removed
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )    # <-- boundary value reset
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk14( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5, chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )    # <-- last two points removed
            self.assertAlmostEqual( 0. , chunk.values[0] )
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )    # <-- last two points removed
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )    # <-- boundary value reset
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk15( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )    # <-- first point removed
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5, chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )    # <-- first point removed
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )    # <-- boundary value reset
            self.assertEqual( 3, chunk.boundaries[1] )    # <-- boundary value reset
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        def verify_chunk16( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual( 1., chunk.upper_cosine_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.cosines ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( -1. , chunk.cosines[0] )    # <-- first two points removed
            self.assertAlmostEqual( 0. , chunk.cosines[1] )
            self.assertAlmostEqual( 0.5, chunk.cosines[2] )
            self.assertAlmostEqual( 1. , chunk.cosines[3] )
            self.assertAlmostEqual( 0. , chunk.values[0] )    # <-- first two points removed
            self.assertAlmostEqual( 0.5 , chunk.values[1] )
            self.assertAlmostEqual( 0.75, chunk.values[2] )
            self.assertAlmostEqual( 1. , chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )    # <-- boundary value reset
            self.assertEqual( 3, chunk.boundaries[1] )    # <-- boundary value reset
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )
            self.assertEqual( True, chunk.is_curated )

        # linearised data without boundaries and no jumps
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1. ],
                                                      values = [ 0., 0.5, 0.75, 1. ] )

        verify_chunk1( self, chunk )

        # linearised data without boundaries and a jump
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0.5, 1. ],
                                                      values = [ 4., 3., 4., 3., 2. ],
                                                      interpolant = InterpolationType.LinearLinear )

        verify_chunk2( self, chunk )

        # non-linearised data with multiple regions without a jump
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1. ],
                                                      values = [ 0., 0.5, 0.75, 1. ],
                                                      boundaries = [ 1, 3 ],
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk3( self, chunk )

        # non-linearised data with multiple regions with a jump
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0.5, 1. ],
                                                      values = [ 0., 0.5, 1., 1.25, 1.5 ],
                                                      boundaries = [ 1, 4 ],
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk4( self, chunk )

        # non-linearised data with multiple regions with a jump that consist of more than 2 points (curate is not requested)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0., 0.5, 1. ],    # <-- jump of 3 x values
                                                      values = [ 0., 0.5, 0.25, 1., 1.25, 1.5 ],
                                                      boundaries = [ 2, 5 ],    # <-- pointing to middle of the jump
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk5( self, chunk )

        # non-linearised data with multiple regions with a jump that consist of more than 2 points (curate is requested)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0., 0.5, 1. ],    # <-- jump of 3 x values
                                                      values = [ 0., 0.5, 0.25, 1., 1.25, 1.5 ],
                                                      boundaries = [ 2, 5 ],    # <-- pointing to middle of the jump
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ],
                                                      curate = True )

        verify_chunk6( self, chunk )

        # linearised data with multiple jumps that consist of more than 2 points (curate is not requested)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., -0.5, -0.5, -0.5, 0., 0.5, 0.5, 0.5, 1. ],    # <-- 2 jumps of 3 x values
                                                      values = [ 1., 2., 3., 4., 5., 6., 7., 8., 9. ] )

        verify_chunk7( self, chunk )

        # linearised data with multiple jumps that consist of more than 2 points (curate is requested)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., -0.5, -0.5, -0.5, 0., 0.5, 0.5, 0.5, 1. ],    # <-- 2 jumps of 3 x values
                                                      values = [ 1., 2., 3., 4., 5., 6., 7., 8., 9. ],
                                                      interpolant = InterpolationType.LinearLinear,
                                                      curate = True )

        verify_chunk8( self, chunk )

        # linearised data with a jump that consist of more than 2 points (curate is not requested)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0., 1. ],    # <-- jump of 3 x values
                                                      values = [ 1., 2., 5., 3., 4. ] )

        verify_chunk9( self, chunk )

        # linearised data with a jump that consist of more than 2 points (the first and second y value in the jump are the same)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0., 1. ],    # <-- jump of 3 x values
                                                      values = [ 1., 2., 2., 3., 4. ] )    # <-- extraneous point has same y

        verify_chunk10( self, chunk )

        # linearised data with a jump where both y values in the jump are the same
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 1. ],
                                                      values = [ 1., 2., 2., 3. ] )    # <-- same y values in the jump

        verify_chunk11( self, chunk )

        # non-linearised data with multiple regions with a jump and boundaries that point to the second x value in the jump
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0., 0.5, 1. ],
                                                      values = [ 0., 0.5, 1., 1.25, 1.5 ],
                                                      boundaries = [ 2, 4 ],    # <-- pointing to end of the jump
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk12( self, chunk )

        # non-linearised data with multiple regions with a jump at the end (the jump consists of 2 points)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1., 1. ],    # <-- jump at end
                                                      values = [ 0., 0.5, 0.75, 1., 2. ],
                                                      boundaries = [ 1, 4 ],    # <-- pointing to end
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk13( self, chunk )

        # non-linearised data with multiple regions with a jump at the end (the jump consists of more than 2 points)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1., 1., 1. ],    # <-- jump of 3 x values at end
                                                      values = [ 0., 0.5, 0.75, 1., 2., 2.5 ],
                                                      boundaries = [ 1, 5 ],    # <-- pointing to end
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk14( self, chunk )

        # non-linearised data with multiple regions with a jump at the beginning (the jump consists of 2 points)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., -1., 0., 0.5, 1. ],    # <-- jump at beginning
                                                      values = [ 1., 0., 0.5, 0.75, 1. ],
                                                      boundaries = [ 2, 4 ],
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk15( self, chunk )

        # non-linearised data with multiple regions with a jump at the beginning (the jump consists of more than 2 points)
        chunk = TabulatedAngularDistributionFunction( cosines = [ -1., -1., -1., 0., 0.5, 1. ],    # <-- jump of 3 x values at beginning
                                                      values = [ 1., 2., 0., 0.5, 0.75, 1. ],
                                                      boundaries = [ 3, 5 ],
                                                      interpolants = [ InterpolationType.LinearLinear,
                                                                       InterpolationType.LogLinear ] )

        verify_chunk16( self, chunk )

    def test_comparison( self ) :

        left = TabulatedAngularDistributionFunction( [ -1., 0., 1. ], [ 1., 2., 3. ] )
        equal = TabulatedAngularDistributionFunction( [ -1., 0., 1. ], [ 1., 2., 3. ] )
        different1 = TabulatedAngularDistributionFunction( [ -1., 0., 1. ], [ 1., 0., 3. ] )
        different2 = TabulatedAngularDistributionFunction( [ -1., 0., 1. ], [ 1., 2., 3. ],
                                                           InterpolationType.LogLog )
        different3 = TabulatedAngularDistributionFunction( [ -1., 0., 1. ], [ 1., 2., 3. ],
                                                           [ 1, 2 ],
                                                           [ InterpolationType.LinearLinear, InterpolationType.LogLog ] )
        different4 = TabulatedAngularDistributionFunction( [ -1., 0.5, 1. ], [ 1., 2., 3. ] )
        uncurated = TabulatedAngularDistributionFunction( [ -1., 0., 0., 0., 1. ], [ 1., 2., 3., 4., 5. ],
         )
        curated = TabulatedAngularDistributionFunction( [ -1., 0., 0., 0., 1. ], [ 1., 2., 3., 4., 5. ],
                                                        InterpolationType.LinearLinear,
                                                        True )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different1 ) )
        self.assertEqual( False, ( left == different2 ) )
        self.assertEqual( False, ( left == different3 ) )
        self.assertEqual( False, ( left == different4 ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different1 ) )
        self.assertEqual( True, ( left != different2 ) )
        self.assertEqual( True, ( left != different3 ) )
        self.assertEqual( True, ( left != different4 ) )

        self.assertEqual( False, uncurated.is_curated )
        self.assertEqual( True, curated.is_curated )

        self.assertEqual( False, ( uncurated == curated ) )
        self.assertEqual( True, ( uncurated != curated ) )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( cosines = [], values = [] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( cosines = [ 1. ], values = [ 1. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1. ],
                                                          values = [ 4., 3., 2. ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1. ],
                                                          values = [ 4., 3., 2., 1. ],
                                                          boundaries = [ 3 ],
                                                          interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0.5, 0., 1. ],
                                                          values = [ 4., 3., 2., 1. ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 1., 1. ],
                                                          values = [ 4., 3., 1., 4. ],
                                                          boundaries = [ 2 ],
                                                          interpolants = [ InterpolationType.LinearLinear ] )

        # the boundaries are not sorted
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1. ],
                                                          values = [ 4., 3., 2., 1. ],
                                                          boundaries = [ 2, 1, 3 ],
                                                          interpolants = [ InterpolationType.LinearLinear,
                                                                           InterpolationType.LinearLinear,
                                                                           InterpolationType.LinearLinear ] )

        # the boundaries are not unique
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1. ],
                                                          values = [ 4., 3., 2., 1. ],
                                                          boundaries = [ 1, 1, 3 ],
                                                          interpolants = [ InterpolationType.LinearLinear,
                                                                           InterpolationType.LinearLinear,
                                                                           InterpolationType.LinearLinear ] )

        # there are no boundaries and interpolants
        with self.assertRaises( Exception ) :

            chunk = TabulatedAngularDistributionFunction( cosines = [ -1., 0., 0.5, 1. ],
                                                          values = [ 4., 3., 2., 1. ],
                                                          boundaries = [],
                                                          interpolants = [] )

if __name__ == '__main__' :

    unittest.main()
