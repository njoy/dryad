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
from njoy.psychic.covariance import EigenvalueRatio

class Test_EigenvalueRatio( unittest.TestCase ) :
    """Unit test for the EigenvalueRatio class."""

    def test_component( self ) :

        test = EigenvalueRatio()

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 100.,  0.,  0. ],
                                                                            [   0., 50.,  0. ],
                                                                            [   0.,  0., 10. ] ] ) )

        self.assertEqual( TestStatus.Success, test( matrix ) )

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1., 0.,    0. ],
                                                                            [ 0., 1.,    0. ],
                                                                            [ 0., 0., 1e-10 ] ] ) )

        self.assertEqual( TestStatus.Fail, test( matrix ) )

if __name__ == '__main__' :

    unittest.main()
