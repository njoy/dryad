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
from njoy.psychic.covariance import DiagonalCorrelations

class Test_DiagonalCorrelations( unittest.TestCase ) :
    """Unit test for the DiagonalCorrelations class."""

    def test_component( self ) :

        test = DiagonalCorrelations()

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               correlations = numpy.array( [ [ 1., 1., 1. ],
                                                                             [ 1., 1., 1. ],
                                                                             [ 1., 1., 1. ] ] ),
                                               deviations = [ 1., 2., 3. ] )

        self.assertEqual( TestStatus.Success, test( matrix ) )

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               correlations = numpy.array( [ [ 1., 1., 1. ],
                                                                             [ 1., 1., 1. ],
                                                                             [ 1., 1., 1.00000000005 ] ] ),
                                               deviations = [ 1., 2., 3. ] )

        self.assertEqual( TestStatus.Warning, test( matrix ) )

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               correlations = numpy.array( [ [ 1., 1., 1. ],
                                                                             [ 1., 1., 1. ],
                                                                             [ 1., 1., 1.5 ] ] ),
                                               deviations = [ 1., 2., 3. ] )

        self.assertEqual( TestStatus.Fail, test( matrix ) )

if __name__ == '__main__' :

    unittest.main()
