# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad.thermal import IncoherentElasticAngularDistribution
from njoy.dryad import InterpolationType

class Test_IncoherentElasticAngularDistribution( unittest.TestCase ) :
    """Unit test for the IncoherentElasticAngularDistribution class."""

    def verify_chunk( self, chunk ) :

        self.assertAlmostEqual( 1., chunk.incident_energy )
        self.assertAlmostEqual( 2.013538, chunk.debye_waller_integral )
        self.assertAlmostEqual( 0.752316633727453, chunk.average_cosine )

        self.assertAlmostEqual( -1., chunk.pdf.lower_cosine_limit )
        self.assertAlmostEqual(  1., chunk.pdf.upper_cosine_limit )
        self.assertAlmostEqual(  1., chunk.pdf.incident_energy )
        self.assertAlmostEqual( 2.013538, chunk.pdf.debye_waller_integral )

        self.assertAlmostEqual( 1., chunk.pdf.integral )
        self.assertAlmostEqual( 0.752316633727453, chunk.pdf.mean )

        self.assertAlmostEqual( -1., chunk.cdf.lower_cosine_limit )
        self.assertAlmostEqual(  1., chunk.cdf.upper_cosine_limit )
        self.assertAlmostEqual( 1., chunk.cdf.incident_energy )
        self.assertAlmostEqual( 2.013538, chunk.cdf.debye_waller_integral )

        self.assertAlmostEqual( 1.280130036188690E-03, chunk( -1.0 ) )
        self.assertAlmostEqual( 9.587878683533260E-03, chunk( -0.5 ) )
        self.assertAlmostEqual( 7.181099970425270E-02, chunk(  0.  ) )
        self.assertAlmostEqual( 5.378478231457790E-01, chunk(  0.5 ) )
        self.assertAlmostEqual( 4.028356130036190E+00, chunk(  1.0 ) )

        linear = chunk.linearise()
        self.assertEqual( 129, linear.pdf.number_points )
        self.assertEqual( 1, linear.pdf.number_regions )
        self.assertEqual( 129, len( linear.pdf.cosines ) )
        self.assertEqual( 129, len( linear.pdf.values ) )
        self.assertEqual( 1, len( linear.pdf.boundaries ) )
        self.assertEqual( 1, len( linear.pdf.interpolants ) )
        self.assertEqual( 128, linear.pdf.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, linear.pdf.interpolants[0] )
        self.assertAlmostEqual( -1. , linear.pdf.cosines[0] )
        self.assertAlmostEqual(  1. , linear.pdf.cosines[-1] )
        self.assertAlmostEqual( 1.280130036188690E-03, linear.pdf.values[0] )
        self.assertAlmostEqual( 4.028356130036190E+00, linear.pdf.values[-1] )
        self.assertEqual( True, linear.pdf.is_linearised )

    def test_component( self ) :

        chunk = IncoherentElasticAngularDistribution(
                  incident = 1.,
                  debye_waller_integral = 2.013538 )

        self.verify_chunk( chunk )

    def test_comparison( self ) :

        left = IncoherentElasticAngularDistribution( 1e-5, 2.013538 )
        equal = IncoherentElasticAngularDistribution( 1e-5, 2.013538 )
        different = IncoherentElasticAngularDistribution( 1e-5, 3. )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
