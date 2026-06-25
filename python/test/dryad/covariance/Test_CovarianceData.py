# standard imports
import unittest
import sys

# third party imports
import numpy

# local imports
from njoy.dryad.covariance import CovarianceData
from njoy.dryad.covariance import CrossSectionCovarianceData
from njoy.dryad.covariance import CrossSectionCovarianceMatrix
from njoy.dryad.covariance import CrossSectionMetadata
from njoy.dryad.covariance import AngularDistributionCovarianceData
from njoy.dryad.covariance import AngularDistributionCovarianceMatrix
from njoy.dryad.covariance import AngularDistributionMetadata
from njoy.dryad.id import ReactionID
from njoy.dryad import ReferenceFrame

class Test_CrossSectionCovarianceData( unittest.TestCase ) :
    """Unit test for the CrossSectionCovarianceData class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            capture = ReactionID( 'n,H1->g,H2' )
            elastic = ReactionID( 'n,H1->n,H1' )

            self.assertIsNotNone( chunk.cross_section )
            self.assertEqual( True, chunk.has_cross_section_covariances )
            self.assertEqual( True, chunk.has_angular_distribution_covariances )

            xs = chunk.cross_section

            self.assertEqual( True, xs.has_covariance_matrix( capture ) )
            self.assertEqual( False, xs.has_covariance_matrix( elastic ) )

            self.assertEqual( 1, xs.number_reactions )
            self.assertEqual( 1, len( xs.reaction_identifiers ) )
            self.assertEqual( capture, xs.reaction_identifiers[0] )

            self.assertEqual( 1, xs.number_covariance_matrices )
            self.assertEqual( 1, len( xs.covariances ) )

            matrix = xs.covariance_matrix( capture )
            self.assertEqual( matrix.row_metadata, matrix.column_metadata )
            self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
            self.assertEqual( capture, matrix.row_metadata.reaction_identifiers[0] )
            self.assertEqual( 3, len( matrix.row_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
            self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
            self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[2] )
            self.assertIsNone( matrix.variance_scaling )
            self.assertIsNotNone( matrix.standard_deviations )
            self.assertIsNotNone( matrix.correlations )
            self.assertIsNotNone( matrix.eigenvalues )
            self.assertAlmostEqual( 1., matrix.covariances[0,0] )
            self.assertAlmostEqual( 2., matrix.covariances[0,1] )
            self.assertAlmostEqual( 2., matrix.covariances[1,0] )
            self.assertAlmostEqual( 3., matrix.covariances[1,1] )

            angular = chunk.angular_distribution

            self.assertEqual( False, angular.has_covariance_matrix( capture ) )
            self.assertEqual( True, angular.has_covariance_matrix( elastic ) )

            self.assertEqual( 1, angular.number_reactions )
            self.assertEqual( 1, len( angular.reaction_identifiers ) )
            self.assertEqual( elastic, angular.reaction_identifiers[0] )

            self.assertEqual( 1, angular.number_covariance_matrices )
            self.assertEqual( 1, len( angular.covariances ) )

            matrix = angular.covariance_matrix( elastic )
            self.assertEqual( matrix.row_metadata, matrix.column_metadata )
            self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
            self.assertEqual( elastic, matrix.row_metadata.reaction_identifiers[0] )
            self.assertEqual( 1, len( matrix.row_metadata.moments ) )
            self.assertEqual( 1, matrix.row_metadata.moments[0] )
            self.assertEqual( 4, len( matrix.row_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
            self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
            self.assertAlmostEqual( 10. , matrix.row_metadata.energies[2] )
            self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[3] )
            self.assertIsNotNone( matrix.standard_deviations )
            self.assertIsNotNone( matrix.correlations )
            self.assertIsNotNone( matrix.eigenvalues )
            self.assertAlmostEqual( 1., matrix.covariances[0,0] )
            self.assertAlmostEqual( 2., matrix.covariances[0,1] )
            self.assertAlmostEqual( 3., matrix.covariances[0,2] )
            self.assertAlmostEqual( 2., matrix.covariances[1,0] )
            self.assertAlmostEqual( 4., matrix.covariances[1,1] )
            self.assertAlmostEqual( 5., matrix.covariances[1,2] )
            self.assertAlmostEqual( 3., matrix.covariances[2,0] )
            self.assertAlmostEqual( 5., matrix.covariances[2,1] )
            self.assertAlmostEqual( 6., matrix.covariances[2,2] )

        capture = ReactionID( 'n,H1->g,H2' )
        elastic = ReactionID( 'n,H1->n,H1' )

        # the data is given explicitly
        chunk = CovarianceData(
                    xs = CrossSectionCovarianceData(
                           [ CrossSectionCovarianceMatrix(
                               CrossSectionMetadata( capture, [ 1e-5, 1., 2e+7 ] ),
                                                     numpy.array( [ [ 1., 2. ],
                                                                    [ 2., 3. ] ] ) ) ] ),
                    angular = AngularDistributionCovarianceData(
                                [ AngularDistributionCovarianceMatrix(
                                    ReferenceFrame.Laboratory,
                                    AngularDistributionMetadata( elastic, 1, [ 1e-5, 1., 10., 2e+7 ] ),
                                                                 numpy.array( [ [ 1., 2., 3. ],
                                                                                [ 2., 4., 5. ],
                                                                                [ 3., 5., 6. ] ] ) ) ] ) )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        capture = ReactionID( 'n,H1->g,H2' )

        left = CovarianceData(
                   xs = CrossSectionCovarianceData( [ CrossSectionCovarianceMatrix(
                                                      CrossSectionMetadata( capture, [ 1e-5, 1., 2e+7 ] ),
                                                                            numpy.array( [ [ 1., 2. ],
                                                                                           [ 2., 3. ] ] ) ) ] ),
                   angular = None )

        equal = CovarianceData(
                    xs = CrossSectionCovarianceData( [ CrossSectionCovarianceMatrix(
                                                       CrossSectionMetadata( capture, [ 1e-5, 1., 2e+7 ] ),
                                                                             numpy.array( [ [ 1., 2. ],
                                                                                            [ 2., 3. ] ] ) ) ] ),
                    angular = None )

        different = CovarianceData( xs = None, angular = None )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
