# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import IncoherentElasticScattering
from njoy.dryad.thermal import TabulatedDebyeWallerIntegral
from njoy.dryad import InterpolationType

def verify_chunk( self, chunk ) :

    self.assertAlmostEqual( 6.337872, chunk.bound_cross_section )

    self.assertAlmostEqual(  296, chunk.debye_waller_integral.lower_temperature_limit )
    self.assertAlmostEqual( 1200, chunk.debye_waller_integral.upper_temperature_limit )
    self.assertEqual( 8, chunk.debye_waller_integral.number_points )
    self.assertEqual( 1, chunk.debye_waller_integral.number_regions )
    self.assertEqual( 8, len( chunk.debye_waller_integral.temperatures ) )
    self.assertEqual( 8, len( chunk.debye_waller_integral.values ) )
    self.assertEqual( 1, len( chunk.debye_waller_integral.boundaries ) )
    self.assertEqual( 1, len( chunk.debye_waller_integral.interpolants ) )
    self.assertAlmostEqual(  296, chunk.debye_waller_integral.temperatures[0] )
    self.assertAlmostEqual(  400, chunk.debye_waller_integral.temperatures[1] )
    self.assertAlmostEqual( 1000, chunk.debye_waller_integral.temperatures[6] )
    self.assertAlmostEqual( 1200, chunk.debye_waller_integral.temperatures[7] )
    self.assertAlmostEqual( 2.013538, chunk.debye_waller_integral.values[0] )
    self.assertAlmostEqual( 2.677764, chunk.debye_waller_integral.values[1] )
    self.assertAlmostEqual( 6.583171, chunk.debye_waller_integral.values[6] )
    self.assertAlmostEqual( 7.891981, chunk.debye_waller_integral.values[7] )
    self.assertEqual( 7, chunk.debye_waller_integral.boundaries[0] )
    self.assertEqual( InterpolationType.LinearLinear, chunk.debye_waller_integral.interpolants[0] )
    self.assertEqual( True, chunk.debye_waller_integral.is_linearised )

class Test_IncoherentElasticScattering( unittest.TestCase ) :
    """Unit test for the IncoherentElasticScattering class."""

    def test_component( self ) :

        chunk = IncoherentElasticScattering(
                  xs = 6.337872,
                  debye_waller_integral = TabulatedDebyeWallerIntegral(
                                            [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                            [ 2.013538, 2.677764, 3.323456, 3.972601,
                                              4.623738, 5.276127, 6.583171, 7.891981 ] ) )

        verify_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = IncoherentElasticScattering(
                  xs = 6.337872,
                  debye_waller_integral = TabulatedDebyeWallerIntegral(
                                            [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                            [ 2.013538, 2.677764, 3.323456, 3.972601,
                                              4.623738, 5.276127, 6.583171, 7.891981 ] ) )

        # the awr can be changed
        newxs = 25.
        original = 6.337872

        chunk.bound_cross_section = newxs

        self.assertEqual( newxs, chunk.bound_cross_section )

        chunk.bound_cross_section = original

        verify_chunk( self, chunk )

        # the library can be changed
        newintegral = TabulatedDebyeWallerIntegral(
                       [ 296, 1200 ],
                       [ 2.013538, 7.891981 ] )
        original = TabulatedDebyeWallerIntegral(
                     [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                     [ 2.013538, 2.677764, 3.323456, 3.972601,
                       4.623738, 5.276127, 6.583171, 7.891981 ] )

        chunk.debye_waller_integral = newintegral

        self.assertEqual( newintegral, chunk.debye_waller_integral )

        chunk.debye_waller_integral = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = IncoherentElasticScattering(
                 xs = 6.337872,
                 debye_waller_integral = TabulatedDebyeWallerIntegral(
                                           [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                           [ 2.013538, 2.677764, 3.323456, 3.972601,
                                             4.623738, 5.276127, 6.583171, 7.891981 ] ) )
        equal = IncoherentElasticScattering(
                  xs = 6.337872,
                  debye_waller_integral = TabulatedDebyeWallerIntegral(
                                            [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                            [ 2.013538, 2.677764, 3.323456, 3.972601,
                                              4.623738, 5.276127, 6.583171, 7.891981 ] ) )
        different = IncoherentElasticScattering(
                      xs = 25,
                      debye_waller_integral = TabulatedDebyeWallerIntegral(
                                                [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                                [ 2.013538, 2.677764, 3.323456, 3.972601,
                                                  4.623738, 5.276127, 6.583171, 7.891981 ] ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
