# standard imports
import unittest

# third party imports

# local imports
import numpy
from dryad.covariance import is_square, is_symmetric

class Test_dryad_covariance_matrix( unittest.TestCase ) :
    """Unit test for matrix functions."""

    def test_diagonal_covariance_block( self ) :

        square_symmetric = numpy.array( [ [ 1., 2. ], [ 2., 4. ] ] )
        square_notsymmetric = numpy.array( [ [ 1., 2. ], [ 1000., 4. ] ] )
        notsquare = numpy.array( [ [ 1., 2. ], [ 2., 4. ], [ 3., 6. ] ] )

        # verify
        self.assertEqual( True, is_square( square_symmetric ) )
        self.assertEqual( True, is_square( square_notsymmetric ) )
        self.assertEqual( False, is_square( notsquare ) )

        self.assertEqual( True, is_symmetric( square_symmetric ) )
        self.assertEqual( False, is_symmetric( square_notsymmetric ) )
        self.assertEqual( False, is_symmetric( notsquare ) )

if __name__ == '__main__' :

    unittest.main()
