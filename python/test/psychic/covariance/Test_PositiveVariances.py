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
from njoy.psychic.covariance import PositiveVariances

class Test_PositiveVariances( unittest.TestCase ) :
    """Unit test for the PositiveVariances class."""

    def test_component( self ) :

        test = PositiveVariances()

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                            [ 2., 4., 6. ],
                                                                            [ 3., 6., 9. ] ] ) )

        self.assertEqual( TestStatus.Success, test( matrix ) )

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                            [ 2., 4., 6. ],
                                                                            [ 3., 6., 0. ] ] ) )

        self.assertEqual( TestStatus.Warning, test( matrix ) )

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1., 2.,  3. ],
                                                                            [ 2., 4.,  6. ],
                                                                            [ 3., 6., -9. ] ] ) )

        self.assertEqual( TestStatus.Fail, test( matrix ) )

if __name__ == '__main__' :

    unittest.main()
