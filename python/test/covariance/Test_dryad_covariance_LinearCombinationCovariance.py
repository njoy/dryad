# standard imports
import unittest

# third party imports

# local imports
from dryad.covariance import LinearCombinationCovariance

class Test_dryad_covariance_LinearCombinationCovariance( unittest.TestCase ) :
    """Unit test for the LinearCombinationCovariance class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.number_reactions )
            self.assertEqual( 3, len( chunk.reactions ) )
            self.assertEqual( 3, len( chunk.coefficients ) )
            self.assertAlmostEqual( '2', chunk.reactions[0] )
            self.assertAlmostEqual( '4', chunk.reactions[1] )
            self.assertAlmostEqual( '16', chunk.reactions[2] )
            self.assertAlmostEqual(  0.1, chunk.coefficients[0] )
            self.assertAlmostEqual(  0.2, chunk.coefficients[1] )
            self.assertAlmostEqual(  0.3, chunk.coefficients[2] )

        # the data is given explicitly
        chunk = LinearCombinationCovariance( reactions = [ '2', '4', '16' ],
                                             coefficients = [ 0.1, 0.2, 0.3 ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the number of reactions and coefficients is not consistent or both are zero
        with self.assertRaises( Exception ) :

            chunk = LinearCombinationCovariance( reactions = [],
                                                 coefficients = [ 0.1, 0.2, 0.3 ] )

        with self.assertRaises( Exception ) :

            chunk = LinearCombinationCovariance( reactions = [ '2', '4', '16'],
                                                 coefficients = [] )

        with self.assertRaises( Exception ) :

            chunk = LinearCombinationCovariance( reactions = [],
                                                 coefficients = [] )

if __name__ == '__main__' :

    unittest.main()
