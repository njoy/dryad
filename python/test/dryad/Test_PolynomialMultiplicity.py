# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import PolynomialMultiplicity
from njoy.dryad import InterpolationType

class Test_PolynomialMultiplicity( unittest.TestCase ) :
    """Unit test for the PolynomialMultiplicity class."""

    def verify_chunk( self, chunk ) :

        self.assertAlmostEqual( 1e-5, chunk.lower_energy_limit )
        self.assertAlmostEqual( 2e+7, chunk.upper_energy_limit )

        self.assertEqual( 1, chunk.order )
        self.assertEqual( 2, len( chunk.coefficients ) )
        self.assertAlmostEqual( 2.  , chunk.coefficients[0] )
        self.assertAlmostEqual( 1e-6, chunk.coefficients[1] )

        self.assertAlmostEqual( 2. + 1e-11, chunk( 1e-5 ) )
        self.assertAlmostEqual(   2.000003, chunk( 3. ) )
        self.assertAlmostEqual(       22.0, chunk( 2.0e+7 ) )

        linear = chunk.linearise()
        self.assertEqual( 2, linear.number_points )
        self.assertEqual( 1, linear.number_regions )
        self.assertEqual( 2, len( linear.energies ) )
        self.assertEqual( 2, len( linear.values ) )
        self.assertEqual( 1, len( linear.boundaries ) )
        self.assertEqual( 1, len( linear.interpolants ) )
        self.assertEqual( 1, linear.boundaries[0] )
        self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
        self.assertAlmostEqual( 1e-5, linear.energies[0] )
        self.assertAlmostEqual( 2e+7, linear.energies[-1] )
        self.assertAlmostEqual( 2. + 1e-11, linear.values[0] )
        self.assertAlmostEqual( 22.       , linear.values[-1] )
        self.assertEqual( True, linear.is_linearised )

    def test_component( self ) :

        chunk = PolynomialMultiplicity(
                  lower = 1e-5,
                  upper = 2e+7,
                  coefficients = [ 2., 1e-6 ] )

        self.verify_chunk( chunk )

    def test_comparison( self ) :

        left = PolynomialMultiplicity( 1e-5, 2e+7, [ 2., 1e-6 ] )
        equal = PolynomialMultiplicity( 1e-5, 2e+7, [ 2., 1e-6 ] )
        different = PolynomialMultiplicity( 1e-5, 2e+7, [ 2., 1e-3 ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
