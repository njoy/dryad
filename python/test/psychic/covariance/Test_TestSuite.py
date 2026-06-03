# standard imports
import unittest
import sys

# third party imports

# local imports
import numpy
from njoy.dryad.covariance import CrossSectionCovarianceMatrix
from njoy.dryad.covariance import CrossSectionMetadata
from njoy.dryad.id import ReactionID
from njoy.psychic import TestStatus
from njoy.psychic.covariance import TestSuite

class Test_TestSuite( unittest.TestCase ) :
    """Unit test for the TestSuite class."""

    def test_component( self ) :

        test = TestSuite()

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                            [ 2., 4., 6. ],
                                                                            [ 3., 6., 9. ] ] ) )

        self.assertEqual( TestStatus.Success, test( matrix ) )
        self.assertEqual( TestStatus.Success, test.positive_variances.status )
        self.assertEqual( TestStatus.Success, test.positive_semi_definite.status )
        self.assertEqual( TestStatus.Success, test.bounded_correlations.status )
        self.assertEqual( TestStatus.Success, test.diagonal_correlations.status )

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1.           , 2., 3.00000000005 ],
                                                                            [ 2.           , 4., 6.            ],
                                                                            [ 3.00000000005, 6., 9.            ] ] ) )

        self.assertEqual( TestStatus.Warning, test( matrix ) )
        self.assertEqual( TestStatus.Success, test.positive_variances.status )
        self.assertEqual( TestStatus.Warning, test.positive_semi_definite.status )
        self.assertEqual( TestStatus.Warning, test.bounded_correlations.status )
        self.assertEqual( TestStatus.Success, test.diagonal_correlations.status )

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1. , 2., 3.5 ],
                                                                            [ 2. , 4., 6.  ],
                                                                            [ 3.5, 6., 9.  ] ] ) )

        self.assertEqual( TestStatus.Fail, test( matrix ) )
        self.assertEqual( TestStatus.Success, test.positive_variances.status )
        self.assertEqual( TestStatus.Fail, test.positive_semi_definite.status )
        self.assertEqual( TestStatus.Fail, test.bounded_correlations.status )
        self.assertEqual( TestStatus.Success, test.diagonal_correlations.status )

if __name__ == '__main__' :

    unittest.main()
