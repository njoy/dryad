# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import ThermalScattering
from njoy.dryad.thermal import DebyeWallerIntegralData
from njoy.dryad.thermal import IncoherentElasticScattering
from njoy.dryad import InterpolationType

def verify_chunk( self, chunk ) :

    # documentation
    self.assertIsNone( chunk.documentation.awr )
    self.assertIsNone( chunk.documentation.library )
    self.assertIsNone( chunk.documentation.version )
    self.assertIsNone( chunk.documentation.description )

    # incoherent elastic scattering
    incoherent = chunk.incoherent_elastic_scattering
    self.assertAlmostEqual( 6.337872, incoherent.bound_cross_section )
    self.assertEqual( 8, len( incoherent.debye_waller_integral.temperatures ) )
    self.assertEqual( 8, len( incoherent.debye_waller_integral.values ) )
    self.assertAlmostEqual(  296, incoherent.debye_waller_integral.temperatures[0] )
    self.assertAlmostEqual(  400, incoherent.debye_waller_integral.temperatures[1] )
    self.assertAlmostEqual( 1000, incoherent.debye_waller_integral.temperatures[6] )
    self.assertAlmostEqual( 1200, incoherent.debye_waller_integral.temperatures[7] )
    self.assertAlmostEqual( 2.013538, incoherent.debye_waller_integral.values[0] )
    self.assertAlmostEqual( 2.677764, incoherent.debye_waller_integral.values[1] )
    self.assertAlmostEqual( 6.583171, incoherent.debye_waller_integral.values[6] )
    self.assertAlmostEqual( 7.891981, incoherent.debye_waller_integral.values[7] )

class Test_ThermalScattering( unittest.TestCase ) :
    """Unit test for the ThermalScattering class."""

    def test_component( self ) :

        chunk = ThermalScattering(
                    incoherent = IncoherentElasticScattering(
                                   6.337872,
                                   DebyeWallerIntegralData(
                                     [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                     [ 2.013538, 2.677764, 3.323456, 3.972601,
                                       4.623738, 5.276127, 6.583171, 7.891981 ] ) ) )

        verify_chunk( self, chunk )

    def test_setter_functions( self ) :

        chunk = ThermalScattering(
                    incoherent = IncoherentElasticScattering(
                                   6.337872,
                                   DebyeWallerIntegralData(
                                     [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                     [ 2.013538, 2.677764, 3.323456, 3.972601,
                                       4.623738, 5.276127, 6.583171, 7.891981 ] ) ) )

        # the incoherent data can be changed
        newincoherent = IncoherentElasticScattering(
                            25,
                            DebyeWallerIntegralData(
                              [ 296, 1200 ],
                              [ 2.013538, 7.891981 ] ) )
        original = IncoherentElasticScattering(
                       6.337872,
                       DebyeWallerIntegralData(
                         [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                         [ 2.013538, 2.677764, 3.323456, 3.972601,
                           4.623738, 5.276127, 6.583171, 7.891981 ] ) )

        chunk.incoherent_elastic_scattering = newincoherent

        self.assertEqual( newincoherent, chunk.incoherent_elastic_scattering )

        chunk.incoherent_elastic_scattering = original

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = ThermalScattering(
                   incoherent = IncoherentElasticScattering(
                                  6.337872,
                                  DebyeWallerIntegralData(
                                    [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                    [ 2.013538, 2.677764, 3.323456, 3.972601,
                                      4.623738, 5.276127, 6.583171, 7.891981 ] ) ) )
        equal = ThermalScattering(
                    incoherent = IncoherentElasticScattering(
                                   6.337872,
                                   DebyeWallerIntegralData(
                                     [ 296, 400, 500, 600, 700, 800, 1000, 1200 ],
                                     [ 2.013538, 2.677764, 3.323456, 3.972601,
                                       4.623738, 5.276127, 6.583171, 7.891981 ] ) ) )
        different = ThermalScattering(
                        incoherent = IncoherentElasticScattering(
                                       25.,
                                       DebyeWallerIntegralData(
                                         [ 296, 1200 ],
                                         [ 2.013538, 7.891981 ] ) ) )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
