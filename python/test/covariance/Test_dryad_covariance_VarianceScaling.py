# standard imports
import unittest

# third party imports

# local imports
from dryad.covariance import VarianceScaling
from dryad.covariance import ScalingType

class Test_dryad_covariance_VarianceScaling( unittest.TestCase ) :
    """Unit test for the VarianceScaling class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.number_groups )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 3, len( chunk.factors ) )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 1.  , chunk.energies[1] )
            self.assertAlmostEqual( 1e+6, chunk.energies[2] )
            self.assertAlmostEqual( 2e+7, chunk.energies[3] )
            self.assertAlmostEqual(  0.1, chunk.factors[0] )
            self.assertAlmostEqual(  0.2, chunk.factors[1] )
            self.assertAlmostEqual(  0.3, chunk.factors[2] )

        # the data is given explicitly
        chunk = VarianceScaling( type = ScalingType.Inverse, energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                 factors = [ 0.1, 0.2, 0.3 ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the energy grid does not have at least 2 elements
        with self.assertRaises( Exception ) :

            chunk = VarianceScaling( type = ScalingType.Inverse, energies = [],
                                     factors = [ 0.1, 0.2, 0.3 ] )

        with self.assertRaises( Exception ) :

            chunk = VarianceScaling( type = ScalingType.Inverse, energies = [ 1. ],
                                     factors = [ 0.1, 0.2, 0.3 ] )

        # the energy grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = VarianceScaling( type = ScalingType.Inverse, energies = [ 1., 1e-5, 1e+6, 2e+7 ],
                                     factors = [ 0.1, 0.2, 0.3 ] )

        # the energy grid has duplicate points
        with self.assertRaises( Exception ) :

            chunk = VarianceScaling( type = ScalingType.Inverse, energies = [ 1e-5, 1e-5, 1e+6, 2e+7 ],
                                     factors = [ 0.1, 0.2, 0.3 ] )

        # the number of energy groups and number of scaling factors is not the same
        with self.assertRaises( Exception ) :

            chunk = VarianceScaling( type = ScalingType.Inverse, energies = [ 1e-5, 1e+6, 2e+7 ],
                                     factors = [ 0.1, 0.2, 0.3 ] )

if __name__ == '__main__' :

    unittest.main()
