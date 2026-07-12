# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import IncoherentElasticScattering
from njoy.dryad.thermal import DebyeWallerIntegralData

def verify_chunk( self, chunk ) :

    self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
    self.assertAlmostEqual( 10. , chunk.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, chunk.bound_cross_section )

    self.assertEqual( 8, len( chunk.debye_waller_integral.temperatures ) )
    self.assertEqual( 8, len( chunk.debye_waller_integral.values ) )
    self.assertAlmostEqual(  296, chunk.debye_waller_integral.temperatures[0] )
    self.assertAlmostEqual(  400, chunk.debye_waller_integral.temperatures[1] )
    self.assertAlmostEqual( 1000, chunk.debye_waller_integral.temperatures[6] )
    self.assertAlmostEqual( 1200, chunk.debye_waller_integral.temperatures[7] )
    self.assertAlmostEqual( 2.013538, chunk.debye_waller_integral.values[0] )
    self.assertAlmostEqual( 2.677764, chunk.debye_waller_integral.values[1] )
    self.assertAlmostEqual( 6.583171, chunk.debye_waller_integral.values[6] )
    self.assertAlmostEqual( 7.891981, chunk.debye_waller_integral.values[7] )

def verify_xs( self, chunk ) :

    xs = chunk.cross_section( temperature = 296 )
    self.assertAlmostEqual( 1e-5, xs.lower_energy_limit )
    self.assertAlmostEqual( 10. , xs.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, xs.bound_cross_section )
    self.assertAlmostEqual( 2.013538, xs.debye_waller_integral )

    xs = chunk.cross_section( temperature = 400 )
    self.assertAlmostEqual( 1e-5, xs.lower_energy_limit )
    self.assertAlmostEqual( 10. , xs.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, xs.bound_cross_section )
    self.assertAlmostEqual( 2.677764, xs.debye_waller_integral )

    xs = chunk.cross_section( temperature = 500 )
    self.assertAlmostEqual( 1e-5, xs.lower_energy_limit )
    self.assertAlmostEqual( 10. , xs.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, xs.bound_cross_section )
    self.assertAlmostEqual( 3.323456, xs.debye_waller_integral )

    xs = chunk.cross_section( temperature = 600 )
    self.assertAlmostEqual( 1e-5, xs.lower_energy_limit )
    self.assertAlmostEqual( 10. , xs.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, xs.bound_cross_section )
    self.assertAlmostEqual( 3.972601, xs.debye_waller_integral )

    xs = chunk.cross_section( temperature = 700 )
    self.assertAlmostEqual( 1e-5, xs.lower_energy_limit )
    self.assertAlmostEqual( 10. , xs.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, xs.bound_cross_section )
    self.assertAlmostEqual( 4.623738, xs.debye_waller_integral )

    xs = chunk.cross_section( temperature = 800 )
    self.assertAlmostEqual( 1e-5, xs.lower_energy_limit )
    self.assertAlmostEqual( 10. , xs.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, xs.bound_cross_section )
    self.assertAlmostEqual( 5.276127, xs.debye_waller_integral )

    xs = chunk.cross_section( temperature = 1000 )
    self.assertAlmostEqual( 1e-5, xs.lower_energy_limit )
    self.assertAlmostEqual( 10. , xs.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, xs.bound_cross_section )
    self.assertAlmostEqual( 6.583171, xs.debye_waller_integral )

    xs = chunk.cross_section( temperature = 1200 )
    self.assertAlmostEqual( 1e-5, xs.lower_energy_limit )
    self.assertAlmostEqual( 10. , xs.upper_energy_limit )
    self.assertAlmostEqual( 6.337872, xs.bound_cross_section )
    self.assertAlmostEqual( 7.891981, xs.debye_waller_integral )

def verify_distribution( self, chunk ) :

    distribution = chunk.angular_distribution( incident = 1e-5, temperature = 296 )
    self.assertAlmostEqual( 1e-5    , distribution.incident_energy )
    self.assertAlmostEqual( 2.013538, distribution.debye_waller_integral )

    distribution = chunk.angular_distribution( incident = 1e-5, temperature = 400 )
    self.assertAlmostEqual( 1e-5    , distribution.incident_energy )
    self.assertAlmostEqual( 2.677764, distribution.debye_waller_integral )

    distribution = chunk.angular_distribution( incident = 1e-5, temperature = 500 )
    self.assertAlmostEqual( 1e-5    , distribution.incident_energy )
    self.assertAlmostEqual( 3.323456, distribution.debye_waller_integral )

    distribution = chunk.angular_distribution( incident = 1e-5, temperature = 600 )
    self.assertAlmostEqual( 1e-5    , distribution.incident_energy )
    self.assertAlmostEqual( 3.972601, distribution.debye_waller_integral )

    distribution = chunk.angular_distribution( incident = 1e-5, temperature = 700 )
    self.assertAlmostEqual( 1e-5    , distribution.incident_energy )
    self.assertAlmostEqual( 4.623738, distribution.debye_waller_integral )

    distribution = chunk.angular_distribution( incident = 1e-5, temperature = 800 )
    self.assertAlmostEqual( 1e-5    , distribution.incident_energy )
    self.assertAlmostEqual( 5.276127, distribution.debye_waller_integral )

    distribution = chunk.angular_distribution( incident = 1e-5, temperature = 1000 )
    self.assertAlmostEqual( 1e-5    , distribution.incident_energy )
    self.assertAlmostEqual( 6.583171, distribution.debye_waller_integral )

    distribution = chunk.angular_distribution( incident = 1e-5, temperature = 1200 )
    self.assertAlmostEqual( 1e-5    , distribution.incident_energy )
    self.assertAlmostEqual( 7.891981, distribution.debye_waller_integral )

class Test_IncoherentElasticScattering( unittest.TestCase ) :
    """Unit test for the IncoherentElasticScattering class."""

    def test_component( self ) :

        chunk = IncoherentElasticScattering(
                  lower = 1e-5,
                  upper = 10.,
                  xs = 6.337872,
                  debye_waller_integral = DebyeWallerIntegralData(
                                            [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                            [ 2.013538, 2.677764, 3.323456, 3.972601,
                                              4.623738, 5.276127, 6.583171, 7.891981 ] ) )

        verify_chunk( self, chunk )
        verify_xs( self, chunk )
        verify_distribution( self, chunk )

    def test_setter_functions( self ) :

        chunk = IncoherentElasticScattering(
                  lower = 1e-5,
                  upper = 10.,
                  xs = 6.337872,
                  debye_waller_integral = DebyeWallerIntegralData(
                                            [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                            [ 2.013538, 2.677764, 3.323456, 3.972601,
                                              4.623738, 5.276127, 6.583171, 7.891981 ] ) )

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

        # the integral values can be changed
        newintegral = DebyeWallerIntegralData(
                       [ 296, 1200 ],
                       [ 2.013538, 7.891981 ] )
        original = DebyeWallerIntegralData(
                     [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                     [ 2.013538, 2.677764, 3.323456, 3.972601,
                       4.623738, 5.276127, 6.583171, 7.891981 ] )

        chunk.debye_waller_integral = newintegral

        self.assertEqual( newintegral, chunk.debye_waller_integral )

        chunk.debye_waller_integral = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = IncoherentElasticScattering(
                 lower = 1e-5,
                 upper = 10.,
                 xs = 6.337872,
                 debye_waller_integral = DebyeWallerIntegralData(
                                           [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                           [ 2.013538, 2.677764, 3.323456, 3.972601,
                                             4.623738, 5.276127, 6.583171, 7.891981 ] ) )
        equal = IncoherentElasticScattering(
                  lower = 1e-5,
                  upper = 10.,
                  xs = 6.337872,
                  debye_waller_integral = DebyeWallerIntegralData(
                                            [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                            [ 2.013538, 2.677764, 3.323456, 3.972601,
                                              4.623738, 5.276127, 6.583171, 7.891981 ] ) )
        different = IncoherentElasticScattering(
                      lower = 1e-5,
                      upper = 10.,
                      xs = 25,
                      debye_waller_integral = DebyeWallerIntegralData(
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
