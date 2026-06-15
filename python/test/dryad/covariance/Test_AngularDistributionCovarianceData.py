# standard imports
import unittest
import sys

# third party imports
import numpy

# local imports
from njoy.dryad.covariance import AngularDistributionCovarianceData
from njoy.dryad.covariance import AngularDistributionCovarianceMatrix
from njoy.dryad.covariance import AngularDistributionMetadata
from njoy.dryad.id import ReactionID
from njoy.dryad import ReferenceFrame

class Test_AngularDistributionCovarianceData( unittest.TestCase ) :
    """Unit test for the AngularDistributionCovarianceData class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            elastic = ReactionID( 'n,H1->n(0)' )
            inelastic = ReactionID( 'n,H1->n(1)' )

            self.assertEqual( True, chunk.has_covariance_matrix( elastic ) )
            self.assertEqual( True, chunk.has_covariance_matrix( elastic, elastic ) )
            self.assertEqual( True, chunk.has_covariance_matrix( inelastic ) )
            self.assertEqual( True, chunk.has_covariance_matrix( inelastic, inelastic ) )
            self.assertEqual( True, chunk.has_covariance_matrix( elastic, inelastic ) )
            self.assertEqual( False, chunk.has_covariance_matrix( inelastic, elastic ) )

            self.assertEqual( 2, chunk.number_reactions )
            self.assertEqual( 2, len( chunk.reaction_identifiers ) )
            self.assertEqual( elastic, chunk.reaction_identifiers[0] )
            self.assertEqual( inelastic, chunk.reaction_identifiers[1] )

            self.assertEqual( 3, chunk.number_covariance_matrices )
            self.assertEqual( 3, len( chunk.covariances ) )

            matrix = chunk.covariances[0]
            self.assertEqual( matrix.row_metadata, matrix.column_metadata )
            self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
            self.assertEqual( elastic, matrix.row_metadata.reaction_identifiers[0] )
            self.assertEqual( 3, len( matrix.row_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
            self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
            self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[2] )
            self.assertEqual( 1, len( matrix.row_metadata.moments ) )
            self.assertEqual( 1, matrix.row_metadata.moments[0] )
            self.assertIsNotNone( matrix.standard_deviations )
            self.assertIsNotNone( matrix.correlations )
            self.assertIsNotNone( matrix.eigenvalues )
            self.assertIsNotNone( matrix.eigenvectors )
            self.assertAlmostEqual( 1., matrix.covariances[0,0] )
            self.assertAlmostEqual( 2., matrix.covariances[0,1] )
            self.assertAlmostEqual( 2., matrix.covariances[1,0] )
            self.assertAlmostEqual( 3., matrix.covariances[1,1] )

            matrix = chunk.covariances[1]
            self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
            self.assertEqual( elastic, matrix.row_metadata.reaction_identifiers[0] )
            self.assertEqual( 5, len( matrix.row_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
            self.assertAlmostEqual( 0.5 , matrix.row_metadata.energies[1] )
            self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[2] )
            self.assertAlmostEqual( 5.  , matrix.row_metadata.energies[3] )
            self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[4] )
            self.assertEqual( 1, len( matrix.row_metadata.moments ) )
            self.assertEqual( 1, matrix.row_metadata.moments[0] )
            self.assertEqual( 1, len( matrix.column_metadata.reaction_identifiers ) )
            self.assertEqual( inelastic, matrix.column_metadata.reaction_identifiers[0] )
            self.assertEqual( 2, len( matrix.column_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.column_metadata.energies[0] )
            self.assertAlmostEqual( 2e+7, matrix.column_metadata.energies[1] )
            self.assertEqual( 1, len( matrix.column_metadata.moments ) )
            self.assertEqual( 2, matrix.column_metadata.moments[0] )
            self.assertIsNone( matrix.standard_deviations )
            self.assertIsNone( matrix.correlations )
            self.assertIsNone( matrix.eigenvalues )
            self.assertIsNone( matrix.eigenvectors )
            self.assertAlmostEqual( 1., matrix.covariances[0,0] )
            self.assertAlmostEqual( 2., matrix.covariances[1,0] )
            self.assertAlmostEqual( 3., matrix.covariances[2,0] )
            self.assertAlmostEqual( 4., matrix.covariances[3,0] )

            matrix = chunk.covariances[2]
            self.assertEqual( matrix.row_metadata, matrix.column_metadata )
            self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
            self.assertEqual( inelastic, matrix.row_metadata.reaction_identifiers[0] )
            self.assertEqual( 4, len( matrix.row_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
            self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
            self.assertAlmostEqual( 1e+6, matrix.row_metadata.energies[2] )
            self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[3] )
            self.assertEqual( 1, len( matrix.row_metadata.moments ) )
            self.assertEqual( 2, matrix.row_metadata.moments[0] )
            self.assertIsNotNone( matrix.standard_deviations )
            self.assertIsNotNone( matrix.correlations )
            self.assertIsNotNone( matrix.eigenvalues )
            self.assertIsNotNone( matrix.eigenvectors )
            self.assertAlmostEqual( 1., matrix.covariances[0,0] )
            self.assertAlmostEqual( 2., matrix.covariances[0,1] )
            self.assertAlmostEqual( 3., matrix.covariances[0,2] )
            self.assertAlmostEqual( 2., matrix.covariances[1,0] )
            self.assertAlmostEqual( 4., matrix.covariances[1,1] )
            self.assertAlmostEqual( 6., matrix.covariances[1,2] )
            self.assertAlmostEqual( 3., matrix.covariances[2,0] )
            self.assertAlmostEqual( 6., matrix.covariances[2,1] )
            self.assertAlmostEqual( 9., matrix.covariances[2,2] )

            matrix = chunk.covariance_matrix( elastic )
            self.assertEqual( matrix.row_metadata, matrix.column_metadata )
            self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
            self.assertEqual( elastic, matrix.row_metadata.reaction_identifiers[0] )
            self.assertEqual( 3, len( matrix.row_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
            self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
            self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[2] )
            self.assertEqual( 1, len( matrix.row_metadata.moments ) )
            self.assertEqual( 1, matrix.row_metadata.moments[0] )
            self.assertIsNotNone( matrix.standard_deviations )
            self.assertIsNotNone( matrix.correlations )
            self.assertIsNotNone( matrix.eigenvalues )
            self.assertIsNotNone( matrix.eigenvectors )
            self.assertAlmostEqual( 1., matrix.covariances[0,0] )
            self.assertAlmostEqual( 2., matrix.covariances[0,1] )
            self.assertAlmostEqual( 2., matrix.covariances[1,0] )
            self.assertAlmostEqual( 3., matrix.covariances[1,1] )

            matrix = chunk.covariance_matrix( elastic, inelastic )
            self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
            self.assertEqual( elastic, matrix.row_metadata.reaction_identifiers[0] )
            self.assertEqual( 5, len( matrix.row_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
            self.assertAlmostEqual( 0.5 , matrix.row_metadata.energies[1] )
            self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[2] )
            self.assertAlmostEqual( 5.  , matrix.row_metadata.energies[3] )
            self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[4] )
            self.assertEqual( 1, len( matrix.row_metadata.moments ) )
            self.assertEqual( 1, matrix.row_metadata.moments[0] )
            self.assertEqual( 1, len( matrix.column_metadata.reaction_identifiers ) )
            self.assertEqual( inelastic, matrix.column_metadata.reaction_identifiers[0] )
            self.assertEqual( 2, len( matrix.column_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.column_metadata.energies[0] )
            self.assertAlmostEqual( 2e+7, matrix.column_metadata.energies[1] )
            self.assertEqual( 1, len( matrix.column_metadata.moments ) )
            self.assertEqual( 2, matrix.column_metadata.moments[0] )
            self.assertIsNone( matrix.standard_deviations )
            self.assertIsNone( matrix.correlations )
            self.assertIsNone( matrix.eigenvalues )
            self.assertIsNone( matrix.eigenvectors )
            self.assertAlmostEqual( 1., matrix.covariances[0,0] )
            self.assertAlmostEqual( 2., matrix.covariances[1,0] )
            self.assertAlmostEqual( 3., matrix.covariances[2,0] )
            self.assertAlmostEqual( 4., matrix.covariances[3,0] )

            matrix = chunk.covariance_matrix( inelastic )
            self.assertEqual( matrix.row_metadata, matrix.column_metadata )
            self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
            self.assertEqual( inelastic, matrix.row_metadata.reaction_identifiers[0] )
            self.assertEqual( 4, len( matrix.row_metadata.energies ) )
            self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
            self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
            self.assertAlmostEqual( 1e+6, matrix.row_metadata.energies[2] )
            self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[3] )
            self.assertEqual( 1, len( matrix.row_metadata.moments ) )
            self.assertEqual( 2, matrix.row_metadata.moments[0] )
            self.assertIsNotNone( matrix.standard_deviations )
            self.assertIsNotNone( matrix.correlations )
            self.assertIsNotNone( matrix.eigenvalues )
            self.assertIsNotNone( matrix.eigenvectors )
            self.assertAlmostEqual( 1., matrix.covariances[0,0] )
            self.assertAlmostEqual( 2., matrix.covariances[0,1] )
            self.assertAlmostEqual( 3., matrix.covariances[0,2] )
            self.assertAlmostEqual( 2., matrix.covariances[1,0] )
            self.assertAlmostEqual( 4., matrix.covariances[1,1] )
            self.assertAlmostEqual( 6., matrix.covariances[1,2] )
            self.assertAlmostEqual( 3., matrix.covariances[2,0] )
            self.assertAlmostEqual( 6., matrix.covariances[2,1] )
            self.assertAlmostEqual( 9., matrix.covariances[2,2] )

        elastic = ReactionID( 'n,H1->n(0)' )
        inelastic = ReactionID( 'n,H1->n(1)' )

        # the data is given explicitly
        chunk = AngularDistributionCovarianceData(
                  matrices = [ AngularDistributionCovarianceMatrix( AngularDistributionMetadata( elastic, 1, [ 1e-5, 1., 2e+7 ] ),
                                                                    numpy.array( [ [ 1., 2. ],
                                                                                   [ 2., 3. ] ] ) ),
                               AngularDistributionCovarianceMatrix( AngularDistributionMetadata( elastic, 1, [ 1e-5, 0.5, 1., 5., 2e+7 ] ),
                                                                    AngularDistributionMetadata( inelastic, 2, [ 1e-5, 2e+7 ] ),
                                                                    numpy.array( [ [ 1. ],
                                                                                   [ 2.],
                                                                                   [ 3.],
                                                                                   [ 4.] ] ) ),
                               AngularDistributionCovarianceMatrix( AngularDistributionMetadata( inelastic, 2, [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                                                    numpy.array( [ [ 1., 2., 3. ],
                                                                                   [ 2., 4., 6. ],
                                                                                   [ 3., 6., 9. ] ] ) )
                             ] )

        verify_chunk( self, chunk )

    def test_comparison( self ) :

        elastic = ReactionID( 'n,H1->n(0)' )
        inelastic = ReactionID( 'n,H1->n(1)' )

        left = AngularDistributionCovarianceData(
                 matrices = [ AngularDistributionCovarianceMatrix( AngularDistributionMetadata( elastic, 1, [ 1e-5, 1., 2e+7 ] ),
                                                                   numpy.array( [ [ 1., 2. ],
                                                                                  [ 2., 3. ] ] ) ),
                              AngularDistributionCovarianceMatrix( AngularDistributionMetadata( elastic, 1, [ 1e-5, 0.5, 1., 5., 2e+7 ] ),
                                                                   AngularDistributionMetadata( inelastic, 2, [ 1e-5, 2e+7 ] ),
                                                                   numpy.array( [ [ 1. ],
                                                                                  [ 2.],
                                                                                  [ 3.],
                                                                                  [ 4.] ] ) ),
                              AngularDistributionCovarianceMatrix( AngularDistributionMetadata( inelastic, 2, [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                                                   numpy.array( [ [ 1., 2., 3. ],
                                                                                  [ 2., 4., 6. ],
                                                                                  [ 3., 6., 9. ] ] ) )
                            ] )
        equal = AngularDistributionCovarianceData(
                  matrices = [ AngularDistributionCovarianceMatrix( AngularDistributionMetadata( elastic, 1, [ 1e-5, 1., 2e+7 ] ),
                                                                    numpy.array( [ [ 1., 2. ],
                                                                                   [ 2., 3. ] ] ) ),
                               AngularDistributionCovarianceMatrix( AngularDistributionMetadata( elastic, 1, [ 1e-5, 0.5, 1., 5., 2e+7 ] ),
                                                                    AngularDistributionMetadata( inelastic, 2, [ 1e-5, 2e+7 ] ),
                                                                    numpy.array( [ [ 1. ],
                                                                                   [ 2.],
                                                                                   [ 3.],
                                                                                   [ 4.] ] ) ),
                               AngularDistributionCovarianceMatrix( AngularDistributionMetadata( inelastic, 2, [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                                                    numpy.array( [ [ 1., 2., 3. ],
                                                                                   [ 2., 4., 6. ],
                                                                                   [ 3., 6., 9. ] ] ) )
                             ] )
        different = AngularDistributionCovarianceData(
                      matrices = [ AngularDistributionCovarianceMatrix( AngularDistributionMetadata( inelastic, 2, [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                                                        numpy.array( [ [ 1., 2., 3. ],
                                                                                       [ 2., 4., 6. ],
                                                                                       [ 3., 6., 9. ] ] ) )
                                 ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
