# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import ScatteringKernel
from njoy.dryad.thermal import TabulatedScatteringKernelFunction
from njoy.dryad import InterpolationType

class Test_ScatteringKernel( unittest.TestCase ) :
    """Unit test for the ScatteringKernel class."""

    def test_component( self ) :

        def verify_symmetric_chunk( self, chunk ) :

            self.assertAlmostEqual( 293.6, chunk.moderator_temperature )
            self.assertAlmostEqual( 300. , chunk.effective_temperature )

            sab = chunk.tabulated_scattering_kernel
            self.assertAlmostEqual( 0., sab.lower_energy_transfer_limit )
            self.assertAlmostEqual( 4., sab.upper_energy_transfer_limit )
            self.assertAlmostEqual( 0., sab.lower_momentum_transfer_limit )
            self.assertAlmostEqual( 4., sab.upper_momentum_transfer_limit )

            self.assertEqual( 5, sab.number_points )
            self.assertEqual( 1, sab.number_regions )
            self.assertEqual( 5, len( sab.energy_transfers ) )
            self.assertEqual( 5, len( sab.functions ) )
            self.assertEqual( 1, len( sab.boundaries ) )
            self.assertEqual( 1, len( sab.interpolants ) )
            self.assertAlmostEqual( 0., sab.energy_transfers[0] )
            self.assertAlmostEqual( 1., sab.energy_transfers[1] )
            self.assertAlmostEqual( 2., sab.energy_transfers[2] )
            self.assertAlmostEqual( 3., sab.energy_transfers[3] )
            self.assertAlmostEqual( 4., sab.energy_transfers[4] )
            self.assertEqual( 2, len( sab.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[0].values ) )
            self.assertEqual( 2, len( sab.functions[1].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[1].values ) )
            self.assertEqual( 2, len( sab.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[2].values ) )
            self.assertEqual( 2, len( sab.functions[3].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[3].values ) )
            self.assertEqual( 2, len( sab.functions[4].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[4].values ) )
            self.assertAlmostEqual( 0.  , sab.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , sab.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , sab.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , sab.functions[3].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[3].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , sab.functions[4].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[4].momentum_transfers[1] )
            self.assertAlmostEqual( 0.8 , sab.functions[0].values[0] )
            self.assertAlmostEqual( 0.2 , sab.functions[0].values[1] )
            self.assertAlmostEqual( 0.5 , sab.functions[1].values[0] )
            self.assertAlmostEqual( 0.5 , sab.functions[1].values[1] )
            self.assertAlmostEqual( 0.52, sab.functions[2].values[0] )
            self.assertAlmostEqual( 0.48, sab.functions[2].values[1] )
            self.assertAlmostEqual( 0.48, sab.functions[3].values[0] )
            self.assertAlmostEqual( 0.52, sab.functions[3].values[1] )
            self.assertAlmostEqual( 0.2 , sab.functions[4].values[0] )
            self.assertAlmostEqual( 0.8 , sab.functions[4].values[1] )
            self.assertEqual( 4, sab.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, sab.interpolants[0] )

            # a value below lower momentum transfer value, b within domain
            self.assertAlmostEqual( 0.52 , chunk( -1.,  2. ) )
            self.assertAlmostEqual( 0.52 , chunk( -2.,  2. ) )
            self.assertAlmostEqual( 0.52 , chunk( -1., -2. ) )
            self.assertAlmostEqual( 0.52 , chunk( -2., -2. ) )

            # a and b within domain
            self.assertAlmostEqual( 0.5  , chunk( 3.,  1. ) )
            self.assertAlmostEqual( 0.49 , chunk( 3.,  2. ) )
            self.assertAlmostEqual( 0.51 , chunk( 3.,  3. ) )
            self.assertAlmostEqual( 0.65 , chunk( 3.,  4. ) )
            self.assertAlmostEqual( 0.495, chunk( 3.,  1.5 ) )
            self.assertAlmostEqual( 0.5  , chunk( 3.,  2.5 ) )
            self.assertAlmostEqual( 0.58 , chunk( 3.,  3.5 ) )
            self.assertAlmostEqual( 0.5  , chunk( 3., -1. ) )
            self.assertAlmostEqual( 0.49 , chunk( 3., -2. ) )
            self.assertAlmostEqual( 0.51 , chunk( 3., -3. ) )
            self.assertAlmostEqual( 0.65 , chunk( 3., -4. ) )
            self.assertAlmostEqual( 0.495, chunk( 3., -1.5 ) )
            self.assertAlmostEqual( 0.5  , chunk( 3., -2.5 ) )
            self.assertAlmostEqual( 0.58 , chunk( 3., -3.5 ) )

            # large a - sct approximation (values calculated in excel)
            self.assertAlmostEqual( 0.0295576357155647, chunk( 5.,  2. ) )
            self.assertAlmostEqual( 0.0295576357155647, chunk( 5., -2. ) )

            # large b - sct approximation (values calculated in excel)
            self.assertAlmostEqual( 0.0095441910268629, chunk( 3.,  5. ) )
            self.assertAlmostEqual( 0.0095441910268629, chunk( 3., -5. ) )

        def verify_asymmetric_chunk( self, chunk ) :

            self.assertAlmostEqual( 293.6, chunk.moderator_temperature )
            self.assertAlmostEqual( 300. , chunk.effective_temperature )

            sab = chunk.tabulated_scattering_kernel
            self.assertAlmostEqual( -1., sab.lower_energy_transfer_limit )
            self.assertAlmostEqual(  4., sab.upper_energy_transfer_limit )
            self.assertAlmostEqual(  0., sab.lower_momentum_transfer_limit )
            self.assertAlmostEqual(  4., sab.upper_momentum_transfer_limit )

            self.assertEqual( 5, sab.number_points )
            self.assertEqual( 1, sab.number_regions )
            self.assertEqual( 5, len( sab.energy_transfers ) )
            self.assertEqual( 5, len( sab.functions ) )
            self.assertEqual( 1, len( sab.boundaries ) )
            self.assertEqual( 1, len( sab.interpolants ) )
            self.assertAlmostEqual( -1., sab.energy_transfers[0] )
            self.assertAlmostEqual(  1., sab.energy_transfers[1] )
            self.assertAlmostEqual(  2., sab.energy_transfers[2] )
            self.assertAlmostEqual(  3., sab.energy_transfers[3] )
            self.assertAlmostEqual(  4., sab.energy_transfers[4] )
            self.assertEqual( 2, len( sab.functions[0].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[0].values ) )
            self.assertEqual( 2, len( sab.functions[1].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[1].values ) )
            self.assertEqual( 2, len( sab.functions[2].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[2].values ) )
            self.assertEqual( 2, len( sab.functions[3].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[3].values ) )
            self.assertEqual( 2, len( sab.functions[4].momentum_transfers ) )
            self.assertEqual( 2, len( sab.functions[4].values ) )
            self.assertAlmostEqual( 0.  , sab.functions[0].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[0].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , sab.functions[1].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[1].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , sab.functions[2].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[2].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , sab.functions[3].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[3].momentum_transfers[1] )
            self.assertAlmostEqual( 0.  , sab.functions[4].momentum_transfers[0] )
            self.assertAlmostEqual( 4.  , sab.functions[4].momentum_transfers[1] )
            self.assertAlmostEqual( 0.8 , sab.functions[0].values[0] )
            self.assertAlmostEqual( 0.2 , sab.functions[0].values[1] )
            self.assertAlmostEqual( 0.5 , sab.functions[1].values[0] )
            self.assertAlmostEqual( 0.5 , sab.functions[1].values[1] )
            self.assertAlmostEqual( 0.52, sab.functions[2].values[0] )
            self.assertAlmostEqual( 0.48, sab.functions[2].values[1] )
            self.assertAlmostEqual( 0.48, sab.functions[3].values[0] )
            self.assertAlmostEqual( 0.52, sab.functions[3].values[1] )
            self.assertAlmostEqual( 0.2 , sab.functions[4].values[0] )
            self.assertAlmostEqual( 0.8 , sab.functions[4].values[1] )
            self.assertEqual( 4, sab.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, sab.interpolants[0] )

            # a value below lower momentum transfer value, b within domain
            self.assertAlmostEqual( 0.52 , chunk( -1.,  2. ) )
            self.assertAlmostEqual( 0.52 , chunk( -2.,  2. ) )
            self.assertAlmostEqual( 0.80 , chunk( -1., -1. ) )
            self.assertAlmostEqual( 0.80 , chunk( -2., -1. ) )

            # a and b within domain
            self.assertAlmostEqual( 0.5  , chunk( 3.,  1. ) )
            self.assertAlmostEqual( 0.49 , chunk( 3.,  2. ) )
            self.assertAlmostEqual( 0.51 , chunk( 3.,  3. ) )
            self.assertAlmostEqual( 0.65 , chunk( 3.,  4. ) )
            self.assertAlmostEqual( 0.495, chunk( 3.,  1.5 ) )
            self.assertAlmostEqual( 0.5  , chunk( 3.,  2.5 ) )
            self.assertAlmostEqual( 0.58 , chunk( 3.,  3.5 ) )
            self.assertAlmostEqual( 0.35 , chunk( 3., -1. ) )

            # large a - sct approximation (values calculated in excel)
            self.assertAlmostEqual( 0.0295576357155647, chunk( 5.,  2. ) )
            self.assertAlmostEqual( 0.0295576357155647, chunk( 5., -2. ) )

            # large b - sct approximation (values calculated in excel)
            self.assertAlmostEqual( 0.0095441910268629, chunk( 3.,  5. ) )
            self.assertAlmostEqual( 0.0095441910268629, chunk( 3., -5. ) )

        # symmetric table
        chunk = ScatteringKernel( moderator_temperature = 293.6,
                                  effective_temperature = 300,
                                  energy_transfers = [ 0., 1., 2., 3., 4. ],
                                  functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                                TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                  interpolant = InterpolationType.LinearLinear )

        verify_symmetric_chunk( self, chunk )

        # asymmetric table
        chunk = ScatteringKernel( moderator_temperature = 293.6,
                                  effective_temperature = 300,
                                  energy_transfers = [ -1., 1., 2., 3., 4. ],
                                  functions = [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                                TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                                TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                                TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                                TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ],
                                  interpolant = InterpolationType.LinearLinear )

        verify_asymmetric_chunk( self, chunk )

    def test_comparison( self ) :

        left = ScatteringKernel( 293.6, 300,
                                 [ 0., 1., 2., 3., 4. ],
                                 [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                   TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                   TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                   TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                   TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] )
        equal = ScatteringKernel( 293.6, 300,
                                  [ 0., 1., 2., 3., 4. ],
                                  [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                    TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                    TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                    TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                    TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] )
        different = ScatteringKernel( 293.6, 300,
                                      [ 1., 4. ],
                                      [ TabulatedScatteringKernelFunction( [ 1., 3. ], [ 1.0, 1.0 ] ),
                                        TabulatedScatteringKernelFunction( [ 1., 3. ], [ 0.1, 0.9 ] ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
