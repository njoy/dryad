# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import IncoherentElasticAngularPdf
from njoy.dryad import InterpolationType

class Test_IncoherentElasticAngularPdf( unittest.TestCase ) :
    """Unit test for the IncoherentElasticAngularPdf class."""

    def verify_chunk( self, chunk ) :

        self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
        self.assertAlmostEqual(  1., chunk.upper_cosine_limit )
        self.assertAlmostEqual(  1., chunk.incident_energy )
        self.assertAlmostEqual( 2.013538, chunk.debye_waller_integral )

        self.assertAlmostEqual( 1.280130036188690E-03, chunk( -1.0 ) )
        self.assertAlmostEqual( 9.587878683533260E-03, chunk( -0.5 ) )
        self.assertAlmostEqual( 7.181099970425270E-02, chunk(  0.  ) )
        self.assertAlmostEqual( 5.378478231457790E-01, chunk(  0.5 ) )
        self.assertAlmostEqual( 4.028356130036190E+00, chunk(  1.0 ) )

        self.assertAlmostEqual( 1., chunk.integral )
        self.assertAlmostEqual( 0.752316633727453, chunk.mean )

        linear = chunk.linearise()
        self.assertEqual( 129, linear.number_points )
        self.assertEqual( 1, linear.number_regions )
        self.assertEqual( 129, len( linear.cosines ) )
        self.assertEqual( 129, len( linear.values ) )
        self.assertEqual( 1, len( linear.boundaries ) )
        self.assertEqual( 1, len( linear.interpolants ) )
        self.assertEqual( 128, linear.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
        self.assertAlmostEqual( -1. , linear.cosines[0] )
        self.assertAlmostEqual(  1. , linear.cosines[-1] )
        self.assertAlmostEqual( 1.280130036188690E-03, linear.values[0] )
        self.assertAlmostEqual( 4.028356130036190E+00, linear.values[-1] )
        self.assertEqual( True, linear.is_linearised )

    def test_component( self ) :

        chunk = IncoherentElasticAngularPdf(
                  incident = 1.,
                  debye_waller_integral = 2.013538 )

        self.verify_chunk( chunk )

    def test_comparison( self ) :

        left = IncoherentElasticAngularPdf( 1e-5, 2.013538 )
        equal = IncoherentElasticAngularPdf( 1e-5, 2.013538 )
        different = IncoherentElasticAngularPdf( 1e-5, 3. )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
