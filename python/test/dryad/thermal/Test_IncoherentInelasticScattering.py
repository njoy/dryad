# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import IncoherentInelasticScattering
from njoy.dryad.thermal import ScatteringKernel
from njoy.dryad.thermal import TabulatedScatteringKernelFunction
from njoy.dryad import InterpolationType

def verify_chunk( self, chunk ) :

    self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
    self.assertAlmostEqual( 10. , chunk.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, chunk.bound_cross_section )

    self.assertEqual( 2, chunk.number_moderator_temperatures )
    self.assertEqual( 2, len( chunk.moderator_temperatures ) )
    self.assertEqual( 2, len( chunk.scattering_kernels ) )

    self.assertAlmostEqual(  293.6, chunk.moderator_temperatures[0] )
    self.assertAlmostEqual(  325. , chunk.moderator_temperatures[1] )

    self.assertEqual( True, chunk.has_scattering_kernel( 293.6 ) )
    self.assertEqual( True, chunk.has_scattering_kernel( 325 ) )
    self.assertEqual( False, chunk.has_scattering_kernel( 350 ) )

    sab0 = chunk.scattering_kernel( 293.6 )
    self.assertAlmostEqual( 293.6, sab0.moderator_temperature )
    self.assertAlmostEqual( 300. , sab0.effective_temperature )
    table = sab0.tabulated_scattering_kernel
    self.assertAlmostEqual( 0., table.lower_energy_transfer_limit )
    self.assertAlmostEqual( 4., table.upper_energy_transfer_limit )
    self.assertAlmostEqual( 0., table.lower_momentum_transfer_limit )
    self.assertAlmostEqual( 4., table.upper_momentum_transfer_limit )
    self.assertEqual( 2, table.number_points )
    self.assertEqual( 1, table.number_regions )
    self.assertEqual( 2, len( table.energy_transfers ) )
    self.assertEqual( 2, len( table.functions ) )
    self.assertEqual( 1, len( table.boundaries ) )
    self.assertEqual( 1, len( table.interpolants ) )
    self.assertAlmostEqual( 0., table.energy_transfers[0] )
    self.assertAlmostEqual( 4., table.energy_transfers[1] )
    self.assertEqual( 2, len( table.functions[0].momentum_transfers ) )
    self.assertEqual( 2, len( table.functions[0].values ) )
    self.assertEqual( 2, len( table.functions[1].momentum_transfers ) )
    self.assertEqual( 2, len( table.functions[1].values ) )
    self.assertAlmostEqual( 0.  , table.functions[0].momentum_transfers[0] )
    self.assertAlmostEqual( 4.  , table.functions[0].momentum_transfers[1] )
    self.assertAlmostEqual( 0.  , table.functions[1].momentum_transfers[0] )
    self.assertAlmostEqual( 4.  , table.functions[1].momentum_transfers[1] )
    self.assertAlmostEqual( 0.8 , table.functions[0].values[0] )
    self.assertAlmostEqual( 0.2 , table.functions[0].values[1] )
    self.assertAlmostEqual( 0.2 , table.functions[1].values[0] )
    self.assertAlmostEqual( 0.8 , table.functions[1].values[1] )
    self.assertEqual( 1, table.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, table.interpolants[0] )

    sab1 = chunk.scattering_kernel( 325. )
    self.assertAlmostEqual( 325., sab1.moderator_temperature )
    self.assertAlmostEqual( 350., sab1.effective_temperature )
    table = sab1.tabulated_scattering_kernel
    self.assertAlmostEqual( 0., table.lower_energy_transfer_limit )
    self.assertAlmostEqual( 5., table.upper_energy_transfer_limit )
    self.assertAlmostEqual( 0., table.lower_momentum_transfer_limit )
    self.assertAlmostEqual( 5., table.upper_momentum_transfer_limit )
    self.assertEqual( 2, table.number_points )
    self.assertEqual( 1, table.number_regions )
    self.assertEqual( 2, len( table.energy_transfers ) )
    self.assertEqual( 2, len( table.functions ) )
    self.assertEqual( 1, len( table.boundaries ) )
    self.assertEqual( 1, len( table.interpolants ) )
    self.assertAlmostEqual( 0., table.energy_transfers[0] )
    self.assertAlmostEqual( 5., table.energy_transfers[1] )
    self.assertEqual( 2, len( table.functions[0].momentum_transfers ) )
    self.assertEqual( 2, len( table.functions[0].values ) )
    self.assertEqual( 2, len( table.functions[1].momentum_transfers ) )
    self.assertEqual( 2, len( table.functions[1].values ) )
    self.assertAlmostEqual( 0.  , table.functions[0].momentum_transfers[0] )
    self.assertAlmostEqual( 5.  , table.functions[0].momentum_transfers[1] )
    self.assertAlmostEqual( 0.  , table.functions[1].momentum_transfers[0] )
    self.assertAlmostEqual( 5.  , table.functions[1].momentum_transfers[1] )
    self.assertAlmostEqual( 0.9 , table.functions[0].values[0] )
    self.assertAlmostEqual( 0.1 , table.functions[0].values[1] )
    self.assertAlmostEqual( 0.1 , table.functions[1].values[0] )
    self.assertAlmostEqual( 0.9 , table.functions[1].values[1] )
    self.assertEqual( 1, table.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, table.interpolants[0] )

class Test_IncoherentInelasticScattering( unittest.TestCase ) :
    """Unit test for the IncoherentInelasticScattering class."""

    def test_component( self ) :

        chunk = IncoherentInelasticScattering(
                  lower = 1e-5,
                  upper = 10.,
                  xs = 6.337872,
                  kernels = [ ScatteringKernel( 293.6, 300.,
                                                [ 0., 4. ],
                                                [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                                  TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ),
                              ScatteringKernel( 325, 350.,
                                                [ 0., 5. ],
                                                [ TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.9, 0.1 ] ),
                                                  TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.1, 0.9 ] ) ] ) ] )

        verify_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = IncoherentInelasticScattering(
                  1e-5, 10., 6.337872,
                  [ ScatteringKernel( 293.6, 300.,
                                      [ 0., 4. ],
                                      [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                        TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ),
                    ScatteringKernel( 325, 350.,
                                      [ 0., 5. ],
                                      [ TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.9, 0.1 ] ),
                                        TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.1, 0.9 ] ) ] ) ] )

        # the lower energy limit can be changed
        newlimit = 1e-4
        original = 1e-5

        chunk.lower_energy_limit = newlimit

        self.assertEqual( newlimit, chunk.lower_energy_limit )

        chunk.lower_energy_limit = original

        verify_chunk( self, chunk )

        # the upper energy limit can be changed
        newlimit = 7.5
        original = 10.

        chunk.upper_energy_limit = newlimit

        self.assertEqual( newlimit, chunk.upper_energy_limit )

        chunk.upper_energy_limit = original

        verify_chunk( self, chunk )

        # the bound xs can be changed
        newxs = 25.
        original = 6.337872

        chunk.bound_cross_section = newxs

        self.assertEqual( newxs, chunk.bound_cross_section )

        chunk.bound_cross_section = original

        verify_chunk( self, chunk )

        # the scattering kernels can be changed
        newkernels = [ ScatteringKernel( 300., 305.,
                                         [ 0., 4. ],
                                         [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                           TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ),
                       ScatteringKernel( 330, 355.,
                                         [ 0., 5. ],
                                         [ TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.9, 0.1 ] ),
                                           TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.1, 0.9 ] ) ] ) ]
        original = [ ScatteringKernel( 293.6, 300.,
                                       [ 0., 4. ],
                                       [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ),
                     ScatteringKernel( 325, 350.,
                                       [ 0., 5. ],
                                       [ TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.9, 0.1 ] ),
                                         TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.1, 0.9 ] ) ] ) ]

        chunk.scattering_kernels = newkernels

        self.assertEqual( newkernels, chunk.scattering_kernels )

        chunk.scattering_kernels = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = IncoherentInelasticScattering(
                   1e-5, 10., 6.337872,
                   [ ScatteringKernel( 293.6, 300.,
                                       [ 0., 4. ],
                                       [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ),
                     ScatteringKernel( 325, 350.,
                                       [ 0., 5. ],
                                       [ TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.9, 0.1 ] ),
                                         TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.1, 0.9 ] ) ] ) ] )
        equal = IncoherentInelasticScattering(
                   1e-5, 10., 6.337872,
                   [ ScatteringKernel( 293.6, 300.,
                                        [ 0., 4. ],
                                        [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.8, 0.2 ] ),
                                          TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ),
                      ScatteringKernel( 325, 350.,
                                        [ 0., 5. ],
                                        [ TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.9, 0.1 ] ),
                                          TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.1, 0.9 ] ) ] ) ] )
        different = IncoherentInelasticScattering(
                        1e-5, 10., 6.337872,
                        [ ScatteringKernel( 293.6, 300.,
                                            [ 0., 5. ],
                                            [ TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.8, 0.2 ] ),
                                              TabulatedScatteringKernelFunction( [ 0., 5. ], [ 0.2, 0.8 ] ) ] ),
                          ScatteringKernel( 325, 350.,
                                            [ 0., 4. ],
                                            [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.9, 0.1 ] ),
                                              TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.1, 0.9 ] ) ] ) ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
