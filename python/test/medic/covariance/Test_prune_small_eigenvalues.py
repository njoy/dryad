# standard imports
import unittest

# third party imports

# local imports
import numpy
from njoy.medic.covariance import prune_small_eigenvalues
from njoy.dryad.id import ReactionID
from njoy.dryad.covariance import CrossSectionMetadata
from njoy.dryad.covariance import CrossSectionCovarianceMatrix

def create_covariance_matrix() :

    return CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                               [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                         covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                      [ 2., 4., 6. ],
                                                                      [ 3., 6., 9. ] ] ) )

class Test_prune_small_eigenvalues( unittest.TestCase ) :
    """Unit test for the prune_small_eigenvalues function."""

    def test_component( self ) :

        matrix = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                     [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                               covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                            [ 2., 4., 6. ],
                                                                            [ 3., 6., 9. ] ] ) )

        self.assertEqual( 3, len( matrix.eigenvalues ) )
        self.assertEqual( 3, len( matrix.eigenvectors ) )

        # the zero eigenvalues can be pruned
        prune_small_eigenvalues( eigenvalue = 1e-8, covariance = matrix )

        # verify content
        self.assertEqual( 1, len( matrix.eigenvalues ) )
        self.assertEqual( 1, len( matrix.eigenvectors ) )

        self.assertAlmostEqual( 14., matrix.eigenvalues[0] )
        self.assertAlmostEqual( 0.2672612419124246, matrix.eigenvectors[0][0] )
        self.assertAlmostEqual( 0.5345224838248487, matrix.eigenvectors[0][1] )
        self.assertAlmostEqual( 0.8017837257372732, matrix.eigenvectors[0][2] )

if __name__ == '__main__' :

    unittest.main()
