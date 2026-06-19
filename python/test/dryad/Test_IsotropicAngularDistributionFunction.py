# standard imports
import unittest
import sys

# third party imports

# local imports
from njoy.dryad import IsotropicAngularDistributionFunction

class Test_IsotropicAngularDistributionFunction( unittest.TestCase ) :
    """Unit test for the IsotropicAngularDistributionFunction class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_cosine_limit )
            self.assertAlmostEqual(  1., chunk.upper_cosine_limit )

            # verify evaluation
            self.assertAlmostEqual( 0.5, chunk( cosine = -1.0 ) )
            self.assertAlmostEqual( 0.5, chunk( cosine = -0.5 ) )
            self.assertAlmostEqual( 0.5, chunk( cosine =  0.0 ) )
            self.assertAlmostEqual( 0.5, chunk( cosine =  0.5 ) )
            self.assertAlmostEqual( 0.5, chunk( cosine =  1.0 ) )

            # values outside the domain
            self.assertAlmostEqual( 0.0, chunk( cosine = -2.0 ) )
            self.assertAlmostEqual( 0.0, chunk( cosine =  2.0 ) )

            # verify integration
            self.assertAlmostEqual( 1.0, chunk.integral )

            # verify mean
            self.assertAlmostEqual( 0.0, chunk.mean )

            # verify normalise
            chunk.normalise()
            self.assertAlmostEqual( 1.0, chunk.integral )
            self.assertAlmostEqual( 0.5, chunk( cosine = 0.0 ) )

            # verify conversion to Legendre distribution
            legendre = chunk.to_legendre_distribution()

            self.assertEqual( 0, legendre.order )
            self.assertEqual( 1, len( legendre.coefficients ) )
            self.assertAlmostEqual( 0.5, legendre.coefficients[0] )

            # verify conversion to tabulated distribution
            tabulated = chunk.to_tabulated_distribution()

            self.assertEqual( 2, tabulated.number_points )
            self.assertEqual( 1, tabulated.number_regions )
            self.assertEqual( 2, len( tabulated.cosines ) )
            self.assertEqual( 2, len( tabulated.values ) )

            self.assertAlmostEqual( -1.0, tabulated.cosines[0] )
            self.assertAlmostEqual(  1.0, tabulated.cosines[1] )
            self.assertAlmostEqual(  0.5, tabulated.values[0] )
            self.assertAlmostEqual(  0.5, tabulated.values[1] )

            # verify linearise
            linear = chunk.linearise()

            self.assertEqual( 2, linear.number_points )
            self.assertEqual( 1, linear.number_regions )
            self.assertEqual( 2, len( linear.cosines ) )
            self.assertEqual( 2, len( linear.values ) )

            self.assertAlmostEqual( -1.0, linear.cosines[0] )
            self.assertAlmostEqual(  1.0, linear.cosines[1] )
            self.assertAlmostEqual(  0.5, linear.values[0] )
            self.assertAlmostEqual(  0.5, linear.values[1] )

            self.assertEqual( True, linear.is_linearised )

        # the data is constructed with no arguments
        chunk = IsotropicAngularDistributionFunction()

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        left = IsotropicAngularDistributionFunction()
        right = IsotropicAngularDistributionFunction()

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == right ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != right ) )

if __name__ == '__main__' :

    unittest.main()
