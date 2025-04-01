# standard imports
import unittest
import sys

# third party imports

# local imports
from dryad import TabulatedScatteringFunction
from dryad import InterpolationType

class Test_dryad_TabulatedScatteringFunction( unittest.TestCase ) :
    """Unit test for the TabulatedScatteringFunction class."""

    def test_component( self ) :

        def verify_chunk1( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_inverse_length_limit )
            self.assertAlmostEqual( 4., chunk.upper_inverse_length_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( inverse_length = 1. ) )
            self.assertAlmostEqual( 3., chunk( inverse_length = 2. ) )
            self.assertAlmostEqual( 2., chunk( inverse_length = 3. ) )
            self.assertAlmostEqual( 1., chunk( inverse_length = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( inverse_length = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( inverse_length = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( inverse_length = 1.5 ) )
            self.assertAlmostEqual( 2.5, chunk( inverse_length = 2.5 ) )
            self.assertAlmostEqual( 1.5, chunk( inverse_length = 3.5 ) )

            # verify arithmetic operators
            same = TabulatedScatteringFunction( [ 1., 4. ], [ 0., 3. ] )
            threshold = TabulatedScatteringFunction( [ 2., 4. ], [ 0., 2. ] )
            nonzerothreshold = TabulatedScatteringFunction( [ 2., 4. ], [ 1., 3. ] )
            small = TabulatedScatteringFunction( [ 1., 3. ], [ 0., 2. ] )

            result = -chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.inverse_lengths[0] )
            self.assertAlmostEqual(  2., result.inverse_lengths[1] )
            self.assertAlmostEqual(  3., result.inverse_lengths[2] )
            self.assertAlmostEqual(  4., result.inverse_lengths[3] )
            self.assertAlmostEqual( -4., result.values[0] )
            self.assertAlmostEqual( -3., result.values[1] )
            self.assertAlmostEqual( -2., result.values[2] )
            self.assertAlmostEqual( -1., result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 6., chunk.values[0] )
            self.assertAlmostEqual( 5., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk *= 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 8., chunk.values[0] )
            self.assertAlmostEqual( 6., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 2., chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk /= 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 3., result.inverse_lengths[2] )
            self.assertAlmostEqual( 4., result.inverse_lengths[3] )
            self.assertAlmostEqual( 6., result.values[0] )
            self.assertAlmostEqual( 5., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 3., result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. + chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 3., result.inverse_lengths[2] )
            self.assertAlmostEqual( 4., result.inverse_lengths[3] )
            self.assertAlmostEqual( 6., result.values[0] )
            self.assertAlmostEqual( 5., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 3., result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.inverse_lengths[0] )
            self.assertAlmostEqual(  2., result.inverse_lengths[1] )
            self.assertAlmostEqual(  3., result.inverse_lengths[2] )
            self.assertAlmostEqual(  4., result.inverse_lengths[3] )
            self.assertAlmostEqual(  2., result.values[0] )
            self.assertAlmostEqual(  1., result.values[1] )
            self.assertAlmostEqual(  0., result.values[2] )
            self.assertAlmostEqual( -1., result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. - chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.inverse_lengths[0] )
            self.assertAlmostEqual(  2., result.inverse_lengths[1] )
            self.assertAlmostEqual(  3., result.inverse_lengths[2] )
            self.assertAlmostEqual(  4., result.inverse_lengths[3] )
            self.assertAlmostEqual( -2., result.values[0] )
            self.assertAlmostEqual( -1., result.values[1] )
            self.assertAlmostEqual(  0., result.values[2] )
            self.assertAlmostEqual(  1., result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk * 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 3., result.inverse_lengths[2] )
            self.assertAlmostEqual( 4., result.inverse_lengths[3] )
            self.assertAlmostEqual( 8., result.values[0] )
            self.assertAlmostEqual( 6., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 2., result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. * chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 3., result.inverse_lengths[2] )
            self.assertAlmostEqual( 4., result.inverse_lengths[3] )
            self.assertAlmostEqual( 8., result.values[0] )
            self.assertAlmostEqual( 6., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 2., result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk / 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , result.inverse_lengths[3] )
            self.assertAlmostEqual( 2. , result.values[0] )
            self.assertAlmostEqual( 1.5, result.values[1] )
            self.assertAlmostEqual( 1. , result.values[2] )
            self.assertAlmostEqual( 0.5, result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += same
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1. , chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4.0, chunk.values[0] )
            self.assertAlmostEqual( 4.0, chunk.values[1] )
            self.assertAlmostEqual( 4.0, chunk.values[2] )
            self.assertAlmostEqual( 4.0, chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= same
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1. , chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4.0, chunk.values[0] )
            self.assertAlmostEqual( 3.0, chunk.values[1] )
            self.assertAlmostEqual( 2.0, chunk.values[2] )
            self.assertAlmostEqual( 1.0, chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + same
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , result.inverse_lengths[3] )
            self.assertAlmostEqual( 4.0, result.values[0] )
            self.assertAlmostEqual( 4.0, result.values[1] )
            self.assertAlmostEqual( 4.0, result.values[2] )
            self.assertAlmostEqual( 4.0, result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - same
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , result.inverse_lengths[3] )
            self.assertAlmostEqual(  4., result.values[0] )
            self.assertAlmostEqual(  2., result.values[1] )
            self.assertAlmostEqual(  0., result.values[2] )
            self.assertAlmostEqual( -2., result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += threshold
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1. , chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4.0, chunk.values[0] )
            self.assertAlmostEqual( 3.0, chunk.values[1] )
            self.assertAlmostEqual( 3.0, chunk.values[2] )
            self.assertAlmostEqual( 3.0, chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= threshold
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1. , chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4.0, chunk.values[0] )
            self.assertAlmostEqual( 3.0, chunk.values[1] )
            self.assertAlmostEqual( 2.0, chunk.values[2] )
            self.assertAlmostEqual( 1.0, chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + threshold
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , result.inverse_lengths[3] )
            self.assertAlmostEqual( 4.0, result.values[0] )
            self.assertAlmostEqual( 3.0, result.values[1] )
            self.assertAlmostEqual( 3.0, result.values[2] )
            self.assertAlmostEqual( 3.0, result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - threshold
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.inverse_lengths ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , result.inverse_lengths[3] )
            self.assertAlmostEqual(  4., result.values[0] )
            self.assertAlmostEqual(  3., result.values[1] )
            self.assertAlmostEqual(  1., result.values[2] )
            self.assertAlmostEqual( -1., result.values[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += nonzerothreshold
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1. , chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2. , chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3. , chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4. , chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4.0, chunk.values[0] )
            self.assertAlmostEqual( 3.0, chunk.values[1] )
            self.assertAlmostEqual( 4.0, chunk.values[2] )
            self.assertAlmostEqual( 4.0, chunk.values[3] )
            self.assertAlmostEqual( 4.0, chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= nonzerothreshold
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1. , chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4. , chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4.0, chunk.values[0] )
            self.assertAlmostEqual( 3.0, chunk.values[1] )
            self.assertAlmostEqual( 2.0, chunk.values[2] )
            self.assertAlmostEqual( 1.0, chunk.values[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + nonzerothreshold
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[1] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[2] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[3] )
            self.assertAlmostEqual( 4. , result.inverse_lengths[4] )
            self.assertAlmostEqual( 4.0, result.values[0] )
            self.assertAlmostEqual( 3.0, result.values[1] )
            self.assertAlmostEqual( 4.0, result.values[2] )
            self.assertAlmostEqual( 4.0, result.values[3] )
            self.assertAlmostEqual( 4.0, result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - nonzerothreshold
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual(  1. , result.inverse_lengths[0] )
            self.assertAlmostEqual(  2. , result.inverse_lengths[1] )
            self.assertAlmostEqual(  2. , result.inverse_lengths[2] )
            self.assertAlmostEqual(  3. , result.inverse_lengths[3] )
            self.assertAlmostEqual(  4. , result.inverse_lengths[4] )
            self.assertAlmostEqual(  4., result.values[0] )
            self.assertAlmostEqual(  3., result.values[1] )
            self.assertAlmostEqual(  2., result.values[2] )
            self.assertAlmostEqual(  0., result.values[3] )
            self.assertAlmostEqual( -2., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            # this will add a second point at the lower end point
            result = chunk + small
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[2] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[3] )
            self.assertAlmostEqual( 4. , result.inverse_lengths[4] )
            self.assertAlmostEqual( 4.0, result.values[0] )
            self.assertAlmostEqual( 4.0, result.values[1] )
            self.assertAlmostEqual( 4.0, result.values[2] )
            self.assertAlmostEqual( 2.0, result.values[3] )
            self.assertAlmostEqual( 1.0, result.values[4] )
            self.assertEqual( 2, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            # this will add a second point at the lower end point
            result = chunk - small
            self.assertEqual( 5, result.number_points )
            self.assertEqual( 2, result.number_regions )
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[1] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[2] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[3] )
            self.assertAlmostEqual( 4. , result.inverse_lengths[4] )
            self.assertAlmostEqual( 4.0, result.values[0] )
            self.assertAlmostEqual( 2.0, result.values[1] )
            self.assertAlmostEqual( 0.0, result.values[2] )
            self.assertAlmostEqual( 2.0, result.values[3] )
            self.assertAlmostEqual( 1.0, result.values[4] )
            self.assertEqual( 2, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 4, len( linear.inverse_lengths ) )
            self.assertEqual( 4, len( linear.values ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 3, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( 1., linear.inverse_lengths[0] )
            self.assertAlmostEqual( 2., linear.inverse_lengths[1] )
            self.assertAlmostEqual( 3., linear.inverse_lengths[2] )
            self.assertAlmostEqual( 4., linear.inverse_lengths[3] )

            self.assertAlmostEqual( 4., linear.values[0] )
            self.assertAlmostEqual( 3., linear.values[1] )
            self.assertAlmostEqual( 2., linear.values[2] )
            self.assertAlmostEqual( 1., linear.values[3] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk2( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_inverse_length_limit )
            self.assertAlmostEqual( 4., chunk.upper_inverse_length_limit )
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( inverse_length = 1. ) )
            self.assertAlmostEqual( 4., chunk( inverse_length = 2. ) )
            self.assertAlmostEqual( 3., chunk( inverse_length = 3. ) )
            self.assertAlmostEqual( 2., chunk( inverse_length = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( inverse_length = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( inverse_length = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 3.5, chunk( inverse_length = 1.5 ) )
            self.assertAlmostEqual( 3.5, chunk( inverse_length = 2.5 ) )
            self.assertAlmostEqual( 2.5, chunk( inverse_length = 3.5 ) )

            # verify arithmetic operators
            same = TabulatedScatteringFunction( [ 1., 4. ], [ 0., 3. ] )
            threshold = TabulatedScatteringFunction( [ 2., 4. ], [ 0., 2. ] )
            nonzerothreshold = TabulatedScatteringFunction( [ 3., 4. ], [ 1., 2. ] )
            small = TabulatedScatteringFunction( [ 1., 3. ], [ 0., 2. ] )

            result = -chunk
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.inverse_lengths[0] )
            self.assertAlmostEqual(  2., result.inverse_lengths[1] )
            self.assertAlmostEqual(  2., result.inverse_lengths[2] )
            self.assertAlmostEqual(  3., result.inverse_lengths[3] )
            self.assertAlmostEqual(  4., result.inverse_lengths[4] )
            self.assertAlmostEqual( -4., result.values[0] )
            self.assertAlmostEqual( -3., result.values[1] )
            self.assertAlmostEqual( -4., result.values[2] )
            self.assertAlmostEqual( -3., result.values[3] )
            self.assertAlmostEqual( -2., result.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk += 2.
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 6., chunk.values[0] )
            self.assertAlmostEqual( 5., chunk.values[1] )
            self.assertAlmostEqual( 6., chunk.values[2] )
            self.assertAlmostEqual( 5., chunk.values[3] )
            self.assertAlmostEqual( 4., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= 2.
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk *= 2.
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 8., chunk.values[0] )
            self.assertAlmostEqual( 6., chunk.values[1] )
            self.assertAlmostEqual( 8., chunk.values[2] )
            self.assertAlmostEqual( 6., chunk.values[3] )
            self.assertAlmostEqual( 4., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk /= 2.
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + 2.
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 4., result.inverse_lengths[4] )
            self.assertAlmostEqual( 6., result.values[0] )
            self.assertAlmostEqual( 5., result.values[1] )
            self.assertAlmostEqual( 6., result.values[2] )
            self.assertAlmostEqual( 5., result.values[3] )
            self.assertAlmostEqual( 4., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. + chunk
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 4., result.inverse_lengths[4] )
            self.assertAlmostEqual( 6., result.values[0] )
            self.assertAlmostEqual( 5., result.values[1] )
            self.assertAlmostEqual( 6., result.values[2] )
            self.assertAlmostEqual( 5., result.values[3] )
            self.assertAlmostEqual( 4., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - 2.
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 4., result.inverse_lengths[4] )
            self.assertAlmostEqual( 2., result.values[0] )
            self.assertAlmostEqual( 1., result.values[1] )
            self.assertAlmostEqual( 2., result.values[2] )
            self.assertAlmostEqual( 1., result.values[3] )
            self.assertAlmostEqual( 0., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. - chunk
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.inverse_lengths[0] )
            self.assertAlmostEqual(  2., result.inverse_lengths[1] )
            self.assertAlmostEqual(  2., result.inverse_lengths[2] )
            self.assertAlmostEqual(  3., result.inverse_lengths[3] )
            self.assertAlmostEqual(  4., result.inverse_lengths[4] )
            self.assertAlmostEqual( -2., result.values[0] )
            self.assertAlmostEqual( -1., result.values[1] )
            self.assertAlmostEqual( -2., result.values[2] )
            self.assertAlmostEqual( -1., result.values[3] )
            self.assertAlmostEqual(  0., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk * 2.
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 4., result.inverse_lengths[4] )
            self.assertAlmostEqual( 8., result.values[0] )
            self.assertAlmostEqual( 6., result.values[1] )
            self.assertAlmostEqual( 8., result.values[2] )
            self.assertAlmostEqual( 6., result.values[3] )
            self.assertAlmostEqual( 4., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. * chunk
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 4., result.inverse_lengths[4] )
            self.assertAlmostEqual( 8., result.values[0] )
            self.assertAlmostEqual( 6., result.values[1] )
            self.assertAlmostEqual( 8., result.values[2] )
            self.assertAlmostEqual( 6., result.values[3] )
            self.assertAlmostEqual( 4., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk / 2.
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.inverse_lengths[0] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[1] )
            self.assertAlmostEqual( 2. , result.inverse_lengths[2] )
            self.assertAlmostEqual( 3. , result.inverse_lengths[3] )
            self.assertAlmostEqual( 4. , result.inverse_lengths[4] )
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
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 4., chunk.values[1] )
            self.assertAlmostEqual( 5., chunk.values[2] )
            self.assertAlmostEqual( 5., chunk.values[3] )
            self.assertAlmostEqual( 5., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= same
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + same
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 4., result.inverse_lengths[4] )
            self.assertAlmostEqual( 4., result.values[0] )
            self.assertAlmostEqual( 4., result.values[1] )
            self.assertAlmostEqual( 5., result.values[2] )
            self.assertAlmostEqual( 5., result.values[3] )
            self.assertAlmostEqual( 5., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - same
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 4., result.inverse_lengths[4] )
            self.assertAlmostEqual(  4., result.values[0] )
            self.assertAlmostEqual(  2., result.values[1] )
            self.assertAlmostEqual(  3., result.values[2] )
            self.assertAlmostEqual(  1., result.values[3] )
            self.assertAlmostEqual( -1., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            chunk += threshold
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 4., chunk.values[3] )
            self.assertAlmostEqual( 4., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= threshold
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + threshold
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 4., result.inverse_lengths[4] )
            self.assertAlmostEqual( 4., result.values[0] )
            self.assertAlmostEqual( 3., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 4., result.values[3] )
            self.assertAlmostEqual( 4., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - threshold
            self.assertEqual( 5, len( result.inverse_lengths ) )
            self.assertEqual( 5, len( result.values ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 4., result.inverse_lengths[4] )
            self.assertAlmostEqual( 4., result.values[0] )
            self.assertAlmostEqual( 3., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 2., result.values[3] )
            self.assertAlmostEqual( 0., result.values[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            chunk += nonzerothreshold
            self.assertEqual( 6, len( chunk.inverse_lengths ) )
            self.assertEqual( 6, len( chunk.values ) )
            self.assertEqual( 3, len( chunk.boundaries ) )
            self.assertEqual( 3, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[5] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 4., chunk.values[4] )
            self.assertAlmostEqual( 4., chunk.values[5] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( 5, chunk.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[2] )

            chunk -= nonzerothreshold
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + nonzerothreshold
            self.assertEqual( 6, len( result.inverse_lengths ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 3., result.inverse_lengths[4] )
            self.assertAlmostEqual( 4., result.inverse_lengths[5] )
            self.assertAlmostEqual( 4., result.values[0] )
            self.assertAlmostEqual( 3., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 3., result.values[3] )
            self.assertAlmostEqual( 4., result.values[4] )
            self.assertAlmostEqual( 4., result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            result = chunk - nonzerothreshold
            self.assertEqual( 6, len( result.inverse_lengths ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 3., result.inverse_lengths[4] )
            self.assertAlmostEqual( 4., result.inverse_lengths[5] )
            self.assertAlmostEqual( 4., result.values[0] )
            self.assertAlmostEqual( 3., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 3., result.values[3] )
            self.assertAlmostEqual( 2., result.values[4] )
            self.assertAlmostEqual( 0., result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            # this will add a second point at the lower end point
            result = chunk + small
            self.assertEqual( 6, len( result.inverse_lengths ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 3., result.inverse_lengths[4] )
            self.assertAlmostEqual( 4., result.inverse_lengths[5] )
            self.assertAlmostEqual( 4., result.values[0] )
            self.assertAlmostEqual( 4., result.values[1] )
            self.assertAlmostEqual( 5., result.values[2] )
            self.assertAlmostEqual( 5., result.values[3] )
            self.assertAlmostEqual( 3., result.values[4] )
            self.assertAlmostEqual( 2., result.values[5] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 3, result.boundaries[1] )
            self.assertEqual( 5, result.boundaries[2] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[2] )

            # this will add a second point at the lower end point
            result = chunk - small
            self.assertEqual( 6, len( result.inverse_lengths ) )
            self.assertEqual( 6, len( result.values ) )
            self.assertEqual( 3, len( result.boundaries ) )
            self.assertEqual( 3, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.inverse_lengths[0] )
            self.assertAlmostEqual( 2., result.inverse_lengths[1] )
            self.assertAlmostEqual( 2., result.inverse_lengths[2] )
            self.assertAlmostEqual( 3., result.inverse_lengths[3] )
            self.assertAlmostEqual( 3., result.inverse_lengths[4] )
            self.assertAlmostEqual( 4., result.inverse_lengths[5] )
            self.assertAlmostEqual( 4., result.values[0] )
            self.assertAlmostEqual( 2., result.values[1] )
            self.assertAlmostEqual( 3., result.values[2] )
            self.assertAlmostEqual( 1., result.values[3] )
            self.assertAlmostEqual( 3., result.values[4] )
            self.assertAlmostEqual( 2., result.values[5] )
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

            self.assertEqual( 5, len( linear.inverse_lengths ) )
            self.assertEqual( 5, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )

            self.assertEqual( 1, linear.boundaries[0] )
            self.assertEqual( 4, linear.boundaries[1] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )

            self.assertAlmostEqual( 1., linear.inverse_lengths[0] )
            self.assertAlmostEqual( 2., linear.inverse_lengths[1] )
            self.assertAlmostEqual( 2., linear.inverse_lengths[2] )
            self.assertAlmostEqual( 3., linear.inverse_lengths[3] )
            self.assertAlmostEqual( 4., linear.inverse_lengths[4] )

            self.assertAlmostEqual( 4., linear.values[0] )
            self.assertAlmostEqual( 3., linear.values[1] )
            self.assertAlmostEqual( 4., linear.values[2] )
            self.assertAlmostEqual( 3., linear.values[3] )
            self.assertAlmostEqual( 2., linear.values[4] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk3( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_inverse_length_limit )
            self.assertAlmostEqual( 4., chunk.upper_inverse_length_limit )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( inverse_length = 1. ) )
            self.assertAlmostEqual( 3., chunk( inverse_length = 2. ) )
            self.assertAlmostEqual( 2., chunk( inverse_length = 3. ) )
            self.assertAlmostEqual( 1., chunk( inverse_length = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( inverse_length = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( inverse_length = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( inverse_length = 1.5 ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 2.44966028678679, chunk( inverse_length = 2.5 ) )
            self.assertAlmostEqual( 1.46416306545103, chunk( inverse_length = 3.5 ) )

            # verify arithmetic operators throw exceptions
            temp = TabulatedScatteringFunction( [ 1., 4. ], [ 4., 1. ] )
            with self.assertRaises( Exception ) : result = -chunk
            with self.assertRaises( Exception ) : result = chunk + 2.
            with self.assertRaises( Exception ) : result = chunk - 2.
            with self.assertRaises( Exception ) : result = chunk * 2.
            with self.assertRaises( Exception ) : result = chunk / 2.
            with self.assertRaises( Exception ) : result = chunk + temp
            with self.assertRaises( Exception ) : result = chunk - temp
            with self.assertRaises( Exception ) : chunk += 2.
            with self.assertRaises( Exception ) : chunk -= 2.
            with self.assertRaises( Exception ) : chunk *= 2.
            with self.assertRaises( Exception ) : chunk /= 2.
            with self.assertRaises( Exception ) : chunk += temp
            with self.assertRaises( Exception ) : chunk -= temp
            with self.assertRaises( Exception ) : result = 2. + chunk
            with self.assertRaises( Exception ) : result = 2. - chunk
            with self.assertRaises( Exception ) : result = 2. * chunk

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 18, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 18, len( linear.inverse_lengths ) )
            self.assertEqual( 18, len( linear.values ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 17, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( 1.   , linear.inverse_lengths[0] )
            self.assertAlmostEqual( 2.   , linear.inverse_lengths[1] )
            self.assertAlmostEqual( 2.125, linear.inverse_lengths[2] )
            self.assertAlmostEqual( 2.25 , linear.inverse_lengths[3] )
            self.assertAlmostEqual( 2.375, linear.inverse_lengths[4] )
            self.assertAlmostEqual( 2.5  , linear.inverse_lengths[5] )
            self.assertAlmostEqual( 2.625, linear.inverse_lengths[6] )
            self.assertAlmostEqual( 2.75 , linear.inverse_lengths[7] )
            self.assertAlmostEqual( 2.875, linear.inverse_lengths[8] )
            self.assertAlmostEqual( 3.   , linear.inverse_lengths[9] )
            self.assertAlmostEqual( 3.125, linear.inverse_lengths[10] )
            self.assertAlmostEqual( 3.25 , linear.inverse_lengths[11] )
            self.assertAlmostEqual( 3.375, linear.inverse_lengths[12] )
            self.assertAlmostEqual( 3.5  , linear.inverse_lengths[13] )
            self.assertAlmostEqual( 3.625, linear.inverse_lengths[14] )
            self.assertAlmostEqual( 3.75 , linear.inverse_lengths[15] )
            self.assertAlmostEqual( 3.875, linear.inverse_lengths[16] )
            self.assertAlmostEqual( 4.   , linear.inverse_lengths[17] )

            self.assertAlmostEqual( 4.              , linear.values[0] )
            self.assertAlmostEqual( 3.              , linear.values[1] )
            self.assertAlmostEqual( 2.85048128530886, linear.values[2] )
            self.assertAlmostEqual( 2.70951129135145, linear.values[3] )
            self.assertAlmostEqual( 2.57616511633150, linear.values[4] )
            self.assertAlmostEqual( 2.44966028678679, linear.values[5] )
            self.assertAlmostEqual( 2.32932893596581, linear.values[6] )
            self.assertAlmostEqual( 2.21459646033567, linear.values[7] )
            self.assertAlmostEqual( 2.10496492439848, linear.values[8] )
            self.assertAlmostEqual( 2.              , linear.values[9] )
            self.assertAlmostEqual( 1.85810031827028, linear.values[10] )
            self.assertAlmostEqual( 1.72176678584324, linear.values[11] )
            self.assertAlmostEqual( 1.59057916034679, linear.values[12] )
            self.assertAlmostEqual( 1.46416306545103, linear.values[13] )
            self.assertAlmostEqual( 1.34218354996644, linear.values[14] )
            self.assertAlmostEqual( 1.22433973930853, linear.values[15] )
            self.assertAlmostEqual( 1.11036036428687, linear.values[16] )
            self.assertAlmostEqual( 1.              , linear.values[17] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk4( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_inverse_length_limit )
            self.assertAlmostEqual( 4., chunk.upper_inverse_length_limit )
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( inverse_length = 1. ) )
            self.assertAlmostEqual( 4., chunk( inverse_length = 2. ) )
            self.assertAlmostEqual( 3., chunk( inverse_length = 3. ) )
            self.assertAlmostEqual( 2., chunk( inverse_length = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( inverse_length = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( inverse_length = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( inverse_length = 1.5 ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.44966028678679, chunk( inverse_length = 2.5 ) )
            self.assertAlmostEqual( 2.46416306545103, chunk( inverse_length = 3.5 ) )

            # verify arithmetic operators throw exceptions
            temp = TabulatedScatteringFunction( [ 1., 4. ], [ 4., 1. ] )
            with self.assertRaises( Exception ) : result = -chunk
            with self.assertRaises( Exception ) : result = chunk + 2.
            with self.assertRaises( Exception ) : result = chunk - 2.
            with self.assertRaises( Exception ) : result = chunk * 2.
            with self.assertRaises( Exception ) : result = chunk / 2.
            with self.assertRaises( Exception ) : result = chunk + temp
            with self.assertRaises( Exception ) : result = chunk - temp
            with self.assertRaises( Exception ) : chunk += 2.
            with self.assertRaises( Exception ) : chunk -= 2.
            with self.assertRaises( Exception ) : chunk *= 2.
            with self.assertRaises( Exception ) : chunk /= 2.
            with self.assertRaises( Exception ) : chunk += temp
            with self.assertRaises( Exception ) : chunk -= temp
            with self.assertRaises( Exception ) : result = 2. + chunk
            with self.assertRaises( Exception ) : result = 2. - chunk
            with self.assertRaises( Exception ) : result = 2. * chunk

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 12, linear.number_points )
            self.assertEqual( 2, linear.number_regions )

            self.assertEqual( 12, len( linear.inverse_lengths ) )
            self.assertEqual( 12, len( linear.values ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )

            self.assertEqual(  1, linear.boundaries[0] )
            self.assertEqual( 11, linear.boundaries[1] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )

            self.assertAlmostEqual( 1.   , linear.inverse_lengths[0] )
            self.assertAlmostEqual( 2.   , linear.inverse_lengths[1] )
            self.assertAlmostEqual( 2.   , linear.inverse_lengths[2] )
            self.assertAlmostEqual( 2.125, linear.inverse_lengths[3] )
            self.assertAlmostEqual( 2.25 , linear.inverse_lengths[4] )
            self.assertAlmostEqual( 2.5  , linear.inverse_lengths[5] )
            self.assertAlmostEqual( 2.75 , linear.inverse_lengths[6] )
            self.assertAlmostEqual( 3.   , linear.inverse_lengths[7] )
            self.assertAlmostEqual( 3.25 , linear.inverse_lengths[8] )
            self.assertAlmostEqual( 3.5  , linear.inverse_lengths[9] )
            self.assertAlmostEqual( 3.75 , linear.inverse_lengths[10] )
            self.assertAlmostEqual( 4.   , linear.inverse_lengths[11] )

            self.assertAlmostEqual( 4.              , linear.values[0] )
            self.assertAlmostEqual( 3.              , linear.values[1] )
            self.assertAlmostEqual( 4.              , linear.values[2] )
            self.assertAlmostEqual( 3.85048128530886, linear.values[3] )
            self.assertAlmostEqual( 3.70951129135145, linear.values[4] )
            self.assertAlmostEqual( 3.44966028678679, linear.values[5] )
            self.assertAlmostEqual( 3.21459646033567, linear.values[6] )
            self.assertAlmostEqual( 3.              , linear.values[7] )
            self.assertAlmostEqual( 2.72176678584324, linear.values[8] )
            self.assertAlmostEqual( 2.46416306545103, linear.values[9] )
            self.assertAlmostEqual( 2.22433973930853, linear.values[10] )
            self.assertAlmostEqual( 2.              , linear.values[11] )

            self.assertEqual( True, linear.is_linearised )

        def verify_chunk5( self, chunk ) :

            # verify content
            self.assertEqual( 5, len( chunk.inverse_lengths ) )
            self.assertEqual( 5, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[3] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )
            self.assertAlmostEqual( 2., chunk.values[4] )
            self.assertEqual( 1, chunk.boundaries[0] )    # <-- this is changed from 2 to 1
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

        def verify_chunk6( self, chunk ) :

            # verify content
            self.assertEqual( 4, len( chunk.inverse_lengths ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.inverse_lengths[0] )
            self.assertAlmostEqual( 2., chunk.inverse_lengths[1] )
            self.assertAlmostEqual( 3., chunk.inverse_lengths[2] )
            self.assertAlmostEqual( 4., chunk.inverse_lengths[3] )      # <-- last point removed
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )      # <-- last point removed
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )    # <-- boundary value reset
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

        # the data is given explicitly for data without boundaries
        chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 3., 4. ],
                                             values = [ 4., 3., 2., 1. ],
                                             interpolant = InterpolationType.LinearLinear )

        verify_chunk1( self, chunk )

        # the data is given explicitly for data without boundaries and a jump
        chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 2., 3., 4. ],
                                             values = [ 4., 3., 4., 3., 2. ],
                                             interpolant = InterpolationType.LinearLinear )

        verify_chunk2( self, chunk )

        # the data is given explicitly for data without a jump
        chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 3., 4. ],
                                             values = [ 4., 3., 2., 1. ],
                                             boundaries = [ 1, 3 ],
                                             interpolants = [ InterpolationType.LinearLinear,
                                                              InterpolationType.LinearLog ] )

        verify_chunk3( self, chunk )

        # the data is given explicitly for data with a jump
        chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 2., 3., 4. ],
                                             values = [ 4., 3., 4., 3., 2. ],
                                             boundaries = [ 1, 4 ],
                                             interpolants = [ InterpolationType.LinearLinear,
                                                              InterpolationType.LinearLog ] )

        verify_chunk4( self, chunk )

        # the data is given explicitly with boundaries that point to the second x value in the jump
        chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 2., 3., 4. ],
                                             values = [ 4., 3., 4., 3., 2. ],
                                             boundaries = [ 2, 4 ],   # <-- pointing to end of the jump
                                             interpolants = [ InterpolationType.LinearLinear,
                                                           InterpolationType.LinearLog ] )

        verify_chunk5( self, chunk )

        # the data is given explicitly with a jump at the end that goes to zero
        chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 3., 4., 4. ], # <-- jump at end
                                             values = [ 4., 3., 2., 1., 0. ], # <-- last value is zero
                                             boundaries = [ 1, 4 ],      # <-- pointing to end
                                             interpolants = [ InterpolationType.LinearLinear,
                                                              InterpolationType.LinearLog ] )

        verify_chunk6( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringFunction( inverse_lengths = [], values = [] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringFunction( inverse_lengths = [ 1. ], values = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 3., 4. ],
                                                 values = [ 4., 3., 2. ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 3., 4. ],
                                         values = [ 4., 3., 2., 1. ],
                                         boundaries = [ 3 ],
                                         interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 3., 2., 4. ],
                                         values = [ 4., 3., 2., 1. ] )

        # the x grid contains a triple x value
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 2., 2., 3., 4. ],
                                         values = [ 4., 3., 3., 3., 2., 1. ] )

        # the x grid has a jump at the beginning
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 1., 3., 4. ],
                                         values = [ 4., 3., 1., 4. ] )

        # the x grid has a jump at the end
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 4., 4. ],
                                         values = [ 4., 3., 1., 4. ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringFunction( inverse_lengths = [ 1., 2., 3., 4. ],
                                         values = [ 4., 3., 2., 1. ],
                                         boundaries = [ 2 ],
                                         interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
