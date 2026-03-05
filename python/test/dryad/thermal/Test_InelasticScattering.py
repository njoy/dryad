# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import InelasticScattering
from njoy.dryad.thermal import TabulatedScatteringKernelFunction
from njoy.dryad.thermal import TabulatedScatteringKernel
from njoy.dryad import InterpolationType

def verify_chunk( self, chunk ) :

    self.assertAlmostEqual( 6.337872, chunk.bound_cross_section )


class Test_InelasticScattering( unittest.TestCase ) :
    """Unit test for the InelasticScattering class."""

    def test_component( self ) :

        chunk = InelasticScattering(
                  xs = 6.337872,
                  self_scatter = TabulatedScatteringKernel(
                                   293.6, 300.,
                                   [ 1., 2., 3., 4. ],
                                   [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                     TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                     TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                     TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ) )

        verify_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = InelasticScattering(
                  xs = 6.337872,
                  self_scatter = TabulatedScatteringKernel(
                                   293.6, 300.,
                                   [ 1., 2., 3., 4. ],
                                   [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                     TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                     TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                     TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ) )

        # the awr can be changed
        newxs = 25.
        original = 6.337872

        chunk.bound_cross_section = newxs

        self.assertEqual( newxs, chunk.bound_cross_section )

        chunk.bound_cross_section = original

        verify_chunk( self, chunk )

        # the library can be changed
        newfunctions = TabulatedScatteringKernel(
                         293.6, 300.,
                         [ 1., 4. ],
                         [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                           TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] )
        original = TabulatedScatteringKernel(
                     293.6, 300.,
                     [ 1., 2., 3., 4. ],
                     [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                       TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                       TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                       TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] )

        chunk.self_scattering_function = newfunctions

        self.assertEqual( newfunctions, chunk.self_scattering_function )

        chunk.self_scattering_function = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = InelasticScattering(
                 xs = 6.337872,
                 self_scatter = TabulatedScatteringKernel(
                                  293.6, 300.,
                                  [ 1., 2., 3., 4. ],
                                  [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                    TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                    TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                    TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ) )
        equal = InelasticScattering(
                  xs = 6.337872,
                  self_scatter = TabulatedScatteringKernel(
                                   293.6, 300.,
                                   [ 1., 2., 3., 4. ],
                                   [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                     TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.52, 0.48 ] ),
                                     TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.48, 0.52 ] ),
                                     TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ) )
        different = InelasticScattering(
                      xs = 6.337872,
                      self_scatter = TabulatedScatteringKernel(
                                       293.6, 300.,
                                       [ 1., 4. ],
                                       [ TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.5, 0.5 ] ),
                                         TabulatedScatteringKernelFunction( [ 0., 4. ], [ 0.2, 0.8 ] ) ] ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
