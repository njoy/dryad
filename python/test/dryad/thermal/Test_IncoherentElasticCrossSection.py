# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import IncoherentElasticScatteringCrossSection
from njoy.dryad import InterpolationType

class Test_IncoherentElasticScatteringCrossSection( unittest.TestCase ) :
    """Unit test for the IncoherentElasticScatteringCrossSection class."""

    def verify_chunk( self, chunk ) :

        self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
        self.assertAlmostEqual( 10. , chunk.upper_energy_limit )
        self.assertAlmostEqual( 6.337872, chunk.bound_cross_section )
        self.assertAlmostEqual( 2.013538, chunk.debye_waller_integral )

        self.assertAlmostEqual( 6.337616775925780E+00, chunk( 1e-5 ) )
        self.assertAlmostEqual( 6.335320375862280E+00, chunk( 1e-4 ) )
        self.assertAlmostEqual( 6.312417292315570E+00, chunk( 1e-3 ) )
        self.assertAlmostEqual( 6.089357527359890E+00, chunk( 1e-2 ) )
        self.assertAlmostEqual( 4.352366592338050E+00, chunk( 1e-1 ) )
        self.assertAlmostEqual( 7.866573603986530E-01, chunk( 1. ) )
        self.assertAlmostEqual( 7.869074236493180E-02, chunk( 10. ) )

        linear = chunk.linearise()
        self.assertEqual( 97, linear.number_points )
        self.assertEqual( 1, linear.number_regions )
        self.assertEqual( 97, len( linear.energies ) )
        self.assertEqual( 97, len( linear.values ) )
        self.assertEqual( 1, len( linear.boundaries ) )
        self.assertEqual( 1, len( linear.interpolants ) )
        self.assertEqual( 96, linear.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
        self.assertAlmostEqual( 1e-5 , linear.energies[0] )
        self.assertAlmostEqual( 10.  , linear.energies[-1] )
        self.assertAlmostEqual( 6.337616775925780E+00, linear.values[0] )
        self.assertAlmostEqual( 7.869074236493180E-02, linear.values[-1] )
        self.assertEqual( True, linear.is_linearised )

    def test_component( self ) :

        chunk = IncoherentElasticScatteringCrossSection(
                  lower = 1e-5,
                  upper = 10.,
                  xs = 6.337872,
                  debye_waller_integral = 2.013538 )

        self.verify_chunk( chunk )

    def test_comparison( self ) :

        left = IncoherentElasticScatteringCrossSection( 1e-5, 10., 6.337872, 2.013538 )
        equal = IncoherentElasticScatteringCrossSection( 1e-5, 10., 6.337872, 2.013538 )
        different = IncoherentElasticScatteringCrossSection( 1e-5, 5., 7., 3. )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
