# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import TabulatedScatteringKernelFunction
from njoy.dryad.thermal import TabulatedScatteringKernel
from njoy.dryad import InterpolationType

class Test_TabulatedScatteringKernel( unittest.TestCase ) :
    """Unit test for the TabulatedScatteringKernel class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.lower_energy_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., chunk.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_momentum_transfer_limit )

            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.energy_transfers ) )
            self.assertEqual( 4, len( chunk.functions ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energy_transfers[0] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[1] )
            self.assertAlmostEqual( 3., chunk.energy_transfers[2] )
            self.assertAlmostEqual( 4., chunk.energy_transfers[3] )
            self.assertEqual( 2, len( chunk.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[0].values ) )
            self.assertEqual( 2, len( chunk.functions[1].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[1].values ) )
            self.assertEqual( 2, len( chunk.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[2].values ) )
            self.assertEqual( 2, len( chunk.functions[3].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[3].values ) )
            self.assertAlmostEqual( 0.  , chunk.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , chunk.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , chunk.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , chunk.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , chunk.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , chunk.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , chunk.functions[3].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , chunk.functions[3].momentum_transfers[1] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[0] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[1] )
            self.assertAlmostEqual( 0.52, chunk.functions[1].values[0] )
            self.assertAlmostEqual( 0.48, chunk.functions[1].values[1] )
            self.assertAlmostEqual( 0.48, chunk.functions[2].values[0] )
            self.assertAlmostEqual( 0.52, chunk.functions[2].values[1] )
            self.assertAlmostEqual( 0.2 , chunk.functions[3].values[0] )
            self.assertAlmostEqual( 0.8 , chunk.functions[3].values[1] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            # verify evaluation
            self.assertAlmostEqual( 0.5 , chunk( 1., 3. ) )
            self.assertAlmostEqual( 0.49, chunk( 2., 3. ) )
            self.assertAlmostEqual( 0.51, chunk( 3., 3. ) )
            self.assertAlmostEqual( 0.65, chunk( 4., 3. ) )

            self.assertAlmostEqual( 0.    , chunk( 0., 3. ) )
            self.assertAlmostEqual( 0.    , chunk( 5., 3. ) )

            self.assertAlmostEqual( 0.495, chunk( 1.5, 3. ) )
            self.assertAlmostEqual( 0.5  , chunk( 2.5, 3. ) )
            self.assertAlmostEqual( 0.58 , chunk( 3.5, 3. ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertAlmostEqual( 1., linear.lower_energy_transfer_limit )
            self.assertAlmostEqual( 4., linear.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., linear.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., linear.upper_momentum_transfer_limit )

            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )
            self.assertEqual( 4, len( linear.energy_transfers ) )
            self.assertEqual( 4, len( linear.functions ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )
            self.assertAlmostEqual( 1., linear.energy_transfers[0] )
            self.assertAlmostEqual( 2., linear.energy_transfers[1] )
            self.assertAlmostEqual( 3., linear.energy_transfers[2] )
            self.assertAlmostEqual( 4., linear.energy_transfers[3] )
            self.assertEqual( True, linear.functions[0].is_linearised )
            self.assertEqual( True, linear.functions[1].is_linearised )
            self.assertEqual( True, linear.functions[2].is_linearised )
            self.assertEqual( True, linear.functions[3].is_linearised )
            self.assertEqual( 2, len( linear.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( linear.functions[1].momentum_transfers ) )
            self.assertEqual( 2, len( linear.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( linear.functions[3].momentum_transfers ) )
            self.assertEqual( 2, len( linear.functions[0].values ) )
            self.assertEqual( 2, len( linear.functions[1].values ) )
            self.assertEqual( 2, len( linear.functions[2].values ) )
            self.assertEqual( 2, len( linear.functions[3].values ) )
            self.assertAlmostEqual(  0.  , linear.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual(  4.  , linear.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual(  0.  , linear.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual(  4.  , linear.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual(  0.  , linear.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual(  4.  , linear.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual(  0.  , linear.functions[3].momentum_transfers[0] )
            self.assertAlmostEqual(  4.  , linear.functions[3].momentum_transfers[1] )

            self.assertEqual( 3, linear.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

        def verify_chunk_jump( self, chunk ) :

            # verify content

            self.assertAlmostEqual( 1., chunk.lower_energy_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., chunk.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., chunk.upper_momentum_transfer_limit )

            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 5, len( chunk.energy_transfers ) )
            self.assertEqual( 5, len( chunk.functions ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.energy_transfers[0] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[1] )
            self.assertAlmostEqual( 2., chunk.energy_transfers[2] )
            self.assertAlmostEqual( 3., chunk.energy_transfers[3] )
            self.assertAlmostEqual( 4., chunk.energy_transfers[4] )
            self.assertEqual( 2, len( chunk.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[0].values ) )
            self.assertEqual( 2, len( chunk.functions[1].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[1].values ) )
            self.assertEqual( 2, len( chunk.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[2].values ) )
            self.assertEqual( 2, len( chunk.functions[3].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[3].values ) )
            self.assertEqual( 2, len( chunk.functions[4].momentum_transfers ) )
            self.assertEqual( 2, len( chunk.functions[4].values ) )
            self.assertAlmostEqual( 0.  , chunk.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , chunk.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , chunk.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , chunk.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , chunk.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , chunk.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , chunk.functions[3].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , chunk.functions[3].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , chunk.functions[4].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , chunk.functions[4].momentum_transfers[1] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[0] )
            self.assertAlmostEqual( 0.5 , chunk.functions[0].values[1] )
            self.assertAlmostEqual( 0.52, chunk.functions[1].values[0] )
            self.assertAlmostEqual( 0.48, chunk.functions[1].values[1] )
            self.assertAlmostEqual( 0.51, chunk.functions[2].values[0] )
            self.assertAlmostEqual( 0.49, chunk.functions[2].values[1] )
            self.assertAlmostEqual( 0.48, chunk.functions[3].values[0] )
            self.assertAlmostEqual( 0.52, chunk.functions[3].values[1] )
            self.assertAlmostEqual( 0.2 , chunk.functions[4].values[0] )
            self.assertAlmostEqual( 0.8 , chunk.functions[4].values[1] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

        # the data is given explicitly
        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                           interpolant = InterpolationType.LinearLinear )

        verify_chunk( self, chunk )

        # the data is given explicitly with a jump that uses more than 2 x values
        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 2., 2., 3., 4. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.51, 0.49 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                           interpolant = InterpolationType.LinearLinear )

        verify_chunk_jump( self, chunk )

        # the data is given explicitly with a jump at the beginning
        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 1., 2., 3., 4. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 1. ], [ 0.1, 0.1 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                           interpolant = InterpolationType.LinearLinear )

        verify_chunk( self, chunk )

        # the data is given explicitly with a jump at the end
        chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4., 4. ],
                                           functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ),
                                                         TabulatedScatteringKernelFunction( [ 0., 1. ], [ 0.1, 0.1 ] ) ],
                                           interpolant = InterpolationType.LinearLinear )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = TabulatedScatteringKernel( [ 1., 2., 3., 4. ],
                                          [ TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.5, 0.5 ] ),
                                            TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.49, 0.51 ] ),
                                            TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.4, 0.6 ] ),
                                            TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )
        equal = TabulatedScatteringKernel( [ 1., 2., 3., 4. ],
                                           [ TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.5, 0.5 ] ),
                                             TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.49, 0.51 ] ),
                                             TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.4, 0.6 ] ),
                                             TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )
        different = TabulatedScatteringKernel( [ 1., 4. ],
                                               [ TabulatedScatteringKernelFunction( [ 1., 3. ], [ 1.0, 1.0 ] ),
                                                 TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or f(y) grid
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [], functions = [] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1. ], functions = [] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ) ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.1, 0.9 ] ) ],
                                               boundaries = [ 3 ],
                                               interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 3., 2., 4. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.1, 0.9 ] ) ] )

        # the last boundary does not point to the last point
        with self.assertRaises( Exception ) :

            chunk = TabulatedScatteringKernel( energy_transfers = [ 1., 2., 3., 4. ],
                                               functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 1., 4. ], [ 0.49, 0.5, 0.51 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 2., 4. ], [ 0.4, 0.5, 0.6 ] ),
                                                             TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.1, 0.9 ] ) ],
                                               boundaries = [ 2 ],
                                               interpolants = [ InterpolationType.LinearLinear ] )

if __name__ == '__main__' :

    unittest.main()
