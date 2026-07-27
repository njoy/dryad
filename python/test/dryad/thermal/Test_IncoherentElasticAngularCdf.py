# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import IncoherentElasticAngularCdf
from njoy.dryad import InterpolationType

class Test_IncoherentElasticAngularCdf( unittest.TestCase ) :
    """Unit test for the IncoherentElasticAngularCdf class."""

    def verify_chunk( self, chunk ) :

        self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
        self.assertAlmostEqual(  1., chunk.upper_cosine_limit )
        self.assertAlmostEqual( 1., chunk.incident_energy )
        self.assertAlmostEqual( 2.013538, chunk.debye_waller_integral )

        self.assertAlmostEqual( 0.                   , chunk( -1.0 ) )
        self.assertAlmostEqual( 0.00206297289828974  , chunk( -0.5 ) )
        self.assertAlmostEqual( 0.017514164040693    , chunk(  0.  ) )
        self.assertAlmostEqual( 0.133240021571662    , chunk(  0.5 ) )
        self.assertAlmostEqual( 1.                   , chunk(  1.0 ) )

        linear = chunk.linearise()
        self.assertEqual( 147, linear.number_points )
        self.assertEqual( 1, linear.number_regions )
        self.assertEqual( 147, len( linear.cosines ) )
        self.assertEqual( 147, len( linear.values ) )
        self.assertEqual( 1, len( linear.boundaries ) )
        self.assertEqual( 1, len( linear.interpolants ) )
        self.assertEqual( 146, linear.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
        self.assertAlmostEqual( -1. , linear.cosines[0] )
        self.assertAlmostEqual(  1. , linear.cosines[-1] )
        self.assertAlmostEqual( 0., linear.values[0] )
        self.assertAlmostEqual( 1., linear.values[-1] )
        self.assertEqual( True, linear.is_linearised )

    def test_component( self ) :

        chunk = IncoherentElasticAngularCdf(
                  incident = 1.,
                  debye_waller_integral = 2.013538 )

        self.verify_chunk( chunk )

    def test_comparison( self ) :

        left = IncoherentElasticAngularCdf( 1e-5, 2.013538 )
        equal = IncoherentElasticAngularCdf( 1e-5, 2.013538 )
        different = IncoherentElasticAngularCdf( 1e-5, 3. )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
