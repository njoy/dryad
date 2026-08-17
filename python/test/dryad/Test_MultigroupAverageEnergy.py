# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import MultigroupAverageEnergy

class Test_MultigroupAverageEnergy( unittest.TestCase ) :
    """Unit test for the MultigroupAverageEnergy class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 5., chunk.upper_energy_limit )
            self.assertEqual( 4, chunk.number_groups )
            self.assertEqual( 5, len( chunk.boundaries ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertAlmostEqual( 1., chunk.boundaries[0] )
            self.assertAlmostEqual( 2., chunk.boundaries[1] )
            self.assertAlmostEqual( 3., chunk.boundaries[2] )
            self.assertAlmostEqual( 4., chunk.boundaries[3] )
            self.assertAlmostEqual( 5., chunk.boundaries[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )

            # verify arithmetic operators
            result = MultigroupAverageEnergy( [ 1., 5. ], [ 0. ] )
            other = MultigroupAverageEnergy( [ 1., 2., 3., 4., 5. ], [ 1., 2., 3., 4. ] );
            different = MultigroupAverageEnergy( [ 1., 2., 3., 4. ], [ 1., 2., 3. ] );

            chunk += 2.

            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 5., chunk.upper_energy_limit )
            self.assertEqual( 4, chunk.number_groups )
            self.assertEqual( 5, len( chunk.boundaries ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertAlmostEqual( 1., chunk.boundaries[0] )
            self.assertAlmostEqual( 2., chunk.boundaries[1] )
            self.assertAlmostEqual( 3., chunk.boundaries[2] )
            self.assertAlmostEqual( 4., chunk.boundaries[3] )
            self.assertAlmostEqual( 5., chunk.boundaries[4] )
            self.assertAlmostEqual( 6., chunk.values[0] )
            self.assertAlmostEqual( 5., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 3., chunk.values[3] )

            chunk -= 2.

            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 5., chunk.upper_energy_limit )
            self.assertEqual( 4, chunk.number_groups )
            self.assertEqual( 5, len( chunk.boundaries ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertAlmostEqual( 1., chunk.boundaries[0] )
            self.assertAlmostEqual( 2., chunk.boundaries[1] )
            self.assertAlmostEqual( 3., chunk.boundaries[2] )
            self.assertAlmostEqual( 4., chunk.boundaries[3] )
            self.assertAlmostEqual( 5., chunk.boundaries[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )

            chunk *= 2.

            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 5., chunk.upper_energy_limit )
            self.assertEqual( 4, chunk.number_groups )
            self.assertEqual( 5, len( chunk.boundaries ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertAlmostEqual( 1., chunk.boundaries[0] )
            self.assertAlmostEqual( 2., chunk.boundaries[1] )
            self.assertAlmostEqual( 3., chunk.boundaries[2] )
            self.assertAlmostEqual( 4., chunk.boundaries[3] )
            self.assertAlmostEqual( 5., chunk.boundaries[4] )
            self.assertAlmostEqual( 8., chunk.values[0] )
            self.assertAlmostEqual( 6., chunk.values[1] )
            self.assertAlmostEqual( 4., chunk.values[2] )
            self.assertAlmostEqual( 2., chunk.values[3] )

            chunk /= 2.

            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 5., chunk.upper_energy_limit )
            self.assertEqual( 4, chunk.number_groups )
            self.assertEqual( 5, len( chunk.boundaries ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertAlmostEqual( 1., chunk.boundaries[0] )
            self.assertAlmostEqual( 2., chunk.boundaries[1] )
            self.assertAlmostEqual( 3., chunk.boundaries[2] )
            self.assertAlmostEqual( 4., chunk.boundaries[3] )
            self.assertAlmostEqual( 5., chunk.boundaries[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )

            result = -chunk

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual( -4., result.values[0] )
            self.assertAlmostEqual( -3., result.values[1] )
            self.assertAlmostEqual( -2., result.values[2] )
            self.assertAlmostEqual( -1., result.values[3] )

            result = chunk + 2.

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual( 6., result.values[0] )
            self.assertAlmostEqual( 5., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 3., result.values[3] )

            result = 2. + chunk

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual( 6., result.values[0] )
            self.assertAlmostEqual( 5., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 3., result.values[3] )

            result = chunk - 2.

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual(  2., result.values[0] )
            self.assertAlmostEqual(  1., result.values[1] )
            self.assertAlmostEqual(  0., result.values[2] )
            self.assertAlmostEqual( -1., result.values[3] )

            result = 2. - chunk

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual( -2., result.values[0] )
            self.assertAlmostEqual( -1., result.values[1] )
            self.assertAlmostEqual(  0., result.values[2] )
            self.assertAlmostEqual(  1., result.values[3] )

            result = chunk * 2.

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual( 8., result.values[0] )
            self.assertAlmostEqual( 6., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 2., result.values[3] )

            result = 2. * chunk

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual( 8., result.values[0] )
            self.assertAlmostEqual( 6., result.values[1] )
            self.assertAlmostEqual( 4., result.values[2] )
            self.assertAlmostEqual( 2., result.values[3] )

            result = chunk / 2

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual( 2. , result.values[0] )
            self.assertAlmostEqual( 1.5, result.values[1] )
            self.assertAlmostEqual( 1. , result.values[2] )
            self.assertAlmostEqual( 0.5, result.values[3] )

            chunk += other

            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 5., chunk.upper_energy_limit )
            self.assertEqual( 4, chunk.number_groups )
            self.assertEqual( 5, len( chunk.boundaries ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertAlmostEqual( 1., chunk.boundaries[0] )
            self.assertAlmostEqual( 2., chunk.boundaries[1] )
            self.assertAlmostEqual( 3., chunk.boundaries[2] )
            self.assertAlmostEqual( 4., chunk.boundaries[3] )
            self.assertAlmostEqual( 5., chunk.boundaries[4] )
            self.assertAlmostEqual( 5., chunk.values[0] )
            self.assertAlmostEqual( 5., chunk.values[1] )
            self.assertAlmostEqual( 5., chunk.values[2] )
            self.assertAlmostEqual( 5., chunk.values[3] )

            chunk -= other

            self.assertAlmostEqual( 1., chunk.lower_energy_limit )
            self.assertAlmostEqual( 5., chunk.upper_energy_limit )
            self.assertEqual( 4, chunk.number_groups )
            self.assertEqual( 5, len( chunk.boundaries ) )
            self.assertEqual( 4, len( chunk.values ) )
            self.assertAlmostEqual( 1., chunk.boundaries[0] )
            self.assertAlmostEqual( 2., chunk.boundaries[1] )
            self.assertAlmostEqual( 3., chunk.boundaries[2] )
            self.assertAlmostEqual( 4., chunk.boundaries[3] )
            self.assertAlmostEqual( 5., chunk.boundaries[4] )
            self.assertAlmostEqual( 4., chunk.values[0] )
            self.assertAlmostEqual( 3., chunk.values[1] )
            self.assertAlmostEqual( 2., chunk.values[2] )
            self.assertAlmostEqual( 1., chunk.values[3] )

            result = chunk + other

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual( 5., result.values[0] )
            self.assertAlmostEqual( 5., result.values[1] )
            self.assertAlmostEqual( 5., result.values[2] )
            self.assertAlmostEqual( 5., result.values[3] )

            result = chunk - other

            self.assertAlmostEqual( 1., result.lower_energy_limit )
            self.assertAlmostEqual( 5., result.upper_energy_limit )
            self.assertEqual( 4, result.number_groups )
            self.assertEqual( 5, len( result.boundaries ) )
            self.assertEqual( 4, len( result.values ) )
            self.assertAlmostEqual( 1., result.boundaries[0] )
            self.assertAlmostEqual( 2., result.boundaries[1] )
            self.assertAlmostEqual( 3., result.boundaries[2] )
            self.assertAlmostEqual( 4., result.boundaries[3] )
            self.assertAlmostEqual( 5., result.boundaries[4] )
            self.assertAlmostEqual(  3., result.values[0] )
            self.assertAlmostEqual(  1., result.values[1] )
            self.assertAlmostEqual( -1., result.values[2] )
            self.assertAlmostEqual( -3., result.values[3] )

            with self.assertRaises( Exception ) : chunk += different
            with self.assertRaises( Exception ) : chunk -= different
            with self.assertRaises( Exception ) : result = chunk + different
            with self.assertRaises( Exception ) : result = chunk - different

        # the data is given explicitly
        chunk = MultigroupAverageEnergy( boundaries = [ 1., 2., 3., 4., 5. ],
                                        values = [ 4., 3., 2., 1. ] )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = MultigroupAverageEnergy( [ 1., 2., 3., 4., 5. ], [ 4., 3., 2., 1. ] )
        equal = MultigroupAverageEnergy( [ 1., 2., 3., 4., 5. ], [ 4., 3., 2., 1. ] )
        different = MultigroupAverageEnergy( [ 1., 4. ], [ 4. ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the boundaries or values
        with self.assertRaises( Exception ) :

            chunk = MultigroupAverageEnergy( boundaries = [ 1. ], values = [] )

        # the boundaries or values do not have the current number of values
        with self.assertRaises( Exception ) :

            chunk = MultigroupAverageEnergy( boundaries = [ 1., 2., 3., 4. ],
                                            values = [ 4., 3. ] )

        # the boundaries are not sorted
        with self.assertRaises( Exception ) :

            chunk = MultigroupAverageEnergy( boundaries = [ 1., 3., 2., 4. ],
                                            values = [ 4., 3., 2. ] )

        # the boundaries are not unique
        with self.assertRaises( Exception ) :

            chunk = MultigroupAverageEnergy( boundaries = [ 1., 3., 3., 4. ],
                                            values = [ 4., 3., 2. ] )

if __name__ == '__main__' :

    unittest.main()
