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
from njoy.psychic.covariance import IsPositiveSemiDefinite

class Test_IsPositiveSemiDefinite( unittest.TestCase ) :
    """Unit test for the IsPositiveSemiDefinite class."""

    def test_component( self ) :

        test = IsPositiveSemiDefinite()

        # positive semi-definite matrix
        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                            [ 2., 4., 6. ],
                                                                            [ 3., 6., 9. ] ] ) )

        self.assertEqual( TestStatus.Success, test( matrix ) )

        # considered positive semi-definite matrix but with very small negative eigenvalue
        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1.           , 2., 3.00000000005 ],
                                                                            [ 2.           , 4., 6.            ],
                                                                            [ 3.00000000005, 6., 9.            ] ] ) )

        self.assertEqual( TestStatus.Warning, test( matrix ) )

        # not a positive semi-definite matrix
        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1. , 2., 3.5 ],
                                                                            [ 2. , 4., 6.  ],
                                                                            [ 3.5, 6., 9.  ] ] ) )

        self.assertEqual( TestStatus.Fail, test( matrix ) )

if __name__ == '__main__' :

    unittest.main()
