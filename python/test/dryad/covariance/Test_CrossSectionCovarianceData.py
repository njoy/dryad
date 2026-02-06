# standard imports
import unittest
import sys

# third party imports
import numpy

# local imports
from njoy.dryad.covariance import CrossSectionCovarianceData
from njoy.dryad.covariance import CrossSectionCovarianceMatrix
from njoy.dryad.covariance import CrossSectionMetadata
from njoy.dryad.id import ReactionID

class Test_CrossSectionCovarianceData( unittest.TestCase ) :
    """Unit test for the CrossSectionCovarianceData class."""

    def verify_chunk( self, chunk ) :

        capture = ReactionID( 'n,H1->g,H2' )
        elastic = ReactionID( 'n,H1->n,H1' )

        self.assertEqual( True, chunk.has_covariance_matrix( capture ) )
        self.assertEqual( True, chunk.has_covariance_matrix( capture, capture ) )
        self.assertEqual( True, chunk.has_covariance_matrix( elastic ) )
        self.assertEqual( True, chunk.has_covariance_matrix( elastic, elastic ) )
        self.assertEqual( True, chunk.has_covariance_matrix( capture, elastic ) )
        self.assertEqual( False, chunk.has_covariance_matrix( elastic, capture ) )

        self.assertEqual( 2, chunk.number_reactions )
        self.assertEqual( 2, len( chunk.number_indentifiers ) )
        self.assertEqual( capture, chunk.number_indentifiers[0] )
        self.assertEqual( elastic, chunk.number_indentifiers[1] )

        self.assertEqual( 2, chunk.number_coveriance_matrices )
        self.assertEqual( 2, len( chunk.covariances ) )

        matrix = chunk.covariances[0]
        self.assertEqual( matrix.row_metadata, chunk.column_metadata )
        self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
        self.assertEqual( capture, matrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 3, len( matrix.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
        self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[2] )
        self.assertIsNone( chunk.variance_scaling )
        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )
        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[0,1] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 3., chunk.covariances[1,1] )

        matrix = chunk.covariances[1]
        self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
        self.assertEqual( capture, matrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 5, len( matrix.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
        self.assertAlmostEqual( 0.5 , matrix.row_metadata.energies[1] )
        self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[2] )
        self.assertAlmostEqual( 5.  , matrix.row_metadata.energies[3] )
        self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[4] )
        self.assertEqual( 1, len( matrix.column_metadata.reaction_identifiers ) )
        self.assertEqual( elastic, matrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 2, len( matrix.column_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, matrix.column_metadata.energies[0] )
        self.assertAlmostEqual( 2e+7, matrix.column_metadata.energies[1] )
        self.assertIsNone( chunk.variance_scaling )
        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )
        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 3., chunk.covariances[2,0] )
        self.assertAlmostEqual( 4., chunk.covariances[3,0] )

        matrix = chunk.covariances[2]
        self.assertEqual( matrix.row_metadata, chunk.column_metadata )
        self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
        self.assertEqual( elastic, matrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 4, len( matrix.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, matrix.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[3] )
        self.assertIsNone( chunk.variance_scaling )
        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )
        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[0,1] )
        self.assertAlmostEqual( 3., chunk.covariances[0,2] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 4., chunk.covariances[1,1] )
        self.assertAlmostEqual( 6., chunk.covariances[1,2] )
        self.assertAlmostEqual( 3., chunk.covariances[2,0] )
        self.assertAlmostEqual( 6., chunk.covariances[2,1] )
        self.assertAlmostEqual( 9., chunk.covariances[2,2] )


        matrix = chunk.covariance_matrix( capture )
        self.assertEqual( matrix.row_metadata, chunk.column_metadata )
        self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
        self.assertEqual( capture, matrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 3, len( matrix.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
        self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[2] )
        self.assertIsNone( chunk.variance_scaling )
        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )
        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[0,1] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 3., chunk.covariances[1,1] )

        matrix = chunk.covariance_matrix( capture, elastic )
        self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
        self.assertEqual( capture, matrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 5, len( matrix.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
        self.assertAlmostEqual( 0.5 , matrix.row_metadata.energies[1] )
        self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[2] )
        self.assertAlmostEqual( 5.  , matrix.row_metadata.energies[3] )
        self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[4] )
        self.assertEqual( 1, len( matrix.column_metadata.reaction_identifiers ) )
        self.assertEqual( elastic, matrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 2, len( matrix.column_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, matrix.column_metadata.energies[0] )
        self.assertAlmostEqual( 2e+7, matrix.column_metadata.energies[1] )
        self.assertIsNone( chunk.variance_scaling )
        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )
        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 3., chunk.covariances[2,0] )
        self.assertAlmostEqual( 4., chunk.covariances[3,0] )

        matrix = chunk.covariance_matrix( elastic )
        self.assertEqual( matrix.row_metadata, chunk.column_metadata )
        self.assertEqual( 1, len( matrix.row_metadata.reaction_identifiers ) )
        self.assertEqual( elastic, matrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 4, len( matrix.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, matrix.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , matrix.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, matrix.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, matrix.row_metadata.energies[3] )
        self.assertIsNone( chunk.variance_scaling )
        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )
        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[0,1] )
        self.assertAlmostEqual( 3., chunk.covariances[0,2] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 4., chunk.covariances[1,1] )
        self.assertAlmostEqual( 6., chunk.covariances[1,2] )
        self.assertAlmostEqual( 3., chunk.covariances[2,0] )
        self.assertAlmostEqual( 6., chunk.covariances[2,1] )
        self.assertAlmostEqual( 9., chunk.covariances[2,2] )

    def test_component( self ) :

        capture = ReactionID( 'n,H1->g,H2' )
        elastic = ReactionID( 'n,H1->n,H1' )

        # the data is given explicitly
        chunk = CrossSectionCovarianceData( matrices = [

                                              CrossSectionCovarianceMatrix( CrossSectionMetadata( capture, [ 1e-5, 1., 2e+7 ] ),
                                                                            numpy.array( [ [ 1., 2. ],
                                                                                           [ 2., 3. ] ] ) ),
                                              CrossSectionCovarianceMatrix( CrossSectionMetadata( capture, [ 1e-5, 0.5, 1., 5., 2e+7 ] ),
                                                                            CrossSectionMetadata( elastic, [ 1e-5, 2e+7 ] ),
                                                                            numpy.array( [ [ 1. ],
                                                                                           [ 2.],
                                                                                           [ 3.],
                                                                                           [ 4.] ] ) ),
                                              CrossSectionCovarianceMatrix( CrossSectionMetadata( elastic, [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                                                            numpy.array( [ [ 1., 2., 3. ],
                                                                                           [ 2., 4., 6. ],
                                                                                           [ 3., 6., 9. ] ] ) ),
                                            ] )

        #verify_chunk( self, chunk )

    def test_comparison( self ) :

        capture = ReactionID( 'n,H1->g,H2' )
        elastic = ReactionID( 'n,H1->n,H1' )

        left = CrossSectionCovarianceData( matrices = [

                                             CrossSectionCovarianceMatrix( CrossSectionMetadata( capture, [ 1e-5, 1., 2e+7 ] ),
                                                                           numpy.array( [ [ 1., 2. ],
                                                                                          [ 2., 3. ] ] ) ),
                                             CrossSectionCovarianceMatrix( CrossSectionMetadata( capture, [ 1e-5, 0.5, 1., 5., 2e+7 ] ),
                                                                           CrossSectionMetadata( elastic, [ 1e-5, 2e+7 ] ),
                                                                           numpy.array( [ [ 1. ],
                                                                                          [ 2.],
                                                                                          [ 3.],
                                                                                          [ 4.] ] ) ),
                                             CrossSectionCovarianceMatrix( CrossSectionMetadata( elastic, [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                                                           numpy.array( [ [ 1., 2., 3. ],
                                                                                          [ 2., 4., 6. ],
                                                                                          [ 3., 6., 9. ] ] ) ),
                                           ] )
        equal = CrossSectionCovarianceData( matrices = [

                                              CrossSectionCovarianceMatrix( CrossSectionMetadata( capture, [ 1e-5, 1., 2e+7 ] ),
                                                                            numpy.array( [ [ 1., 2. ],
                                                                                           [ 2., 3. ] ] ) ),
                                              CrossSectionCovarianceMatrix( CrossSectionMetadata( capture, [ 1e-5, 0.5, 1., 5., 2e+7 ] ),
                                                                            CrossSectionMetadata( elastic, [ 1e-5, 2e+7 ] ),
                                                                            numpy.array( [ [ 1. ],
                                                                                           [ 2.],
                                                                                           [ 3.],
                                                                                           [ 4.] ] ) ),
                                              CrossSectionCovarianceMatrix( CrossSectionMetadata( elastic, [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                                                            numpy.array( [ [ 1., 2., 3. ],
                                                                                           [ 2., 4., 6. ],
                                                                                           [ 3., 6., 9. ] ] ) ),
                                            ] )
        different = CrossSectionCovarianceData( matrices = [

                                                  CrossSectionCovarianceMatrix( CrossSectionMetadata( elastic, [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                                                                numpy.array( [ [ 1., 2., 3. ],
                                                                                               [ 2., 4., 6. ],
                                                                                               [ 3., 6., 9. ] ] ) ),
                                                ] )

        self.assertEqual( True, ( left == left ) )
        self.assertEqual( True, ( left == equal ) )
        self.assertEqual( False, ( left == different ) )

        self.assertEqual( False, ( left != left ) )
        self.assertEqual( False, ( left != equal ) )
        self.assertEqual( True, ( left != different ) )

if __name__ == '__main__' :

    unittest.main()
