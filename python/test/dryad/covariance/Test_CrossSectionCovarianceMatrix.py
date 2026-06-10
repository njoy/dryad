# standard imports
import unittest

# third party imports

# local imports
import numpy
from njoy.dryad.covariance import CrossSectionCovarianceMatrix
from njoy.dryad.covariance import CrossSectionMetadata
from njoy.dryad.covariance import ScalingType
from njoy.dryad.covariance import VarianceScaling
from njoy.dryad.id import ReactionID

class Test_CrossSectionCovarianceMatrix( unittest.TestCase ) :
    """Unit test for the CrossSectionCovarianceMatrix class."""

    def test_diagonal_covariance_block( self ) :

        # the data is given explicitly - for a diagonal block without scaling
        chunk = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                    [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                              covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                           [ 2., 4., 6. ],
                                                                           [ 3., 6., 9. ] ] ) )

        # verify content
        self.assertEqual( chunk.row_metadata, chunk.column_metadata )
        self.assertEqual( 1, len( chunk.row_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( False, chunk.has_variance_scaling )
        self.assertIsNone( chunk.variance_scaling )

        self.assertEqual( True, chunk.is_relative_matrix )
        self.assertEqual( False, chunk.is_absolute_matrix )
        self.assertEqual( False, chunk.is_off_diagonal )
        self.assertEqual( True, chunk.is_on_diagonal )

        self.assertIsNotNone( chunk.standard_deviations )
        self.assertIsNotNone( chunk.correlations )
        self.assertIsNotNone( chunk.eigenvalues )

        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[0,1] )
        self.assertAlmostEqual( 3., chunk.covariances[0,2] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 4., chunk.covariances[1,1] )
        self.assertAlmostEqual( 6., chunk.covariances[1,2] )
        self.assertAlmostEqual( 3., chunk.covariances[2,0] )
        self.assertAlmostEqual( 6., chunk.covariances[2,1] )
        self.assertAlmostEqual( 9., chunk.covariances[2,2] )

        self.assertAlmostEqual( 1., chunk.standard_deviations[0] )
        self.assertAlmostEqual( 2., chunk.standard_deviations[1] )
        self.assertAlmostEqual( 3., chunk.standard_deviations[2] )

        self.assertAlmostEqual( 1., chunk.correlations[0,0] )
        self.assertAlmostEqual( 1., chunk.correlations[0,1] )
        self.assertAlmostEqual( 1., chunk.correlations[0,2] )
        self.assertAlmostEqual( 1., chunk.correlations[1,0] )
        self.assertAlmostEqual( 1., chunk.correlations[1,1] )
        self.assertAlmostEqual( 1., chunk.correlations[1,2] )
        self.assertAlmostEqual( 1., chunk.correlations[2,0] )
        self.assertAlmostEqual( 1., chunk.correlations[2,1] )
        self.assertAlmostEqual( 1., chunk.correlations[2,2] )

        self.assertAlmostEqual( 14., chunk.eigenvalues[0] )
        self.assertAlmostEqual(  0., chunk.eigenvalues[1] )
        self.assertAlmostEqual(  0., chunk.eigenvalues[2] )

        self.assertAlmostEqual( 0.2672612419124246, chunk.eigenvectors[0][0] )
        self.assertAlmostEqual( 0.5345224838248487, chunk.eigenvectors[0][1] )
        self.assertAlmostEqual( 0.8017837257372732, chunk.eigenvectors[0][2] )

        # the data is given explicitly - for a diagonal block with scaling
        chunk = CrossSectionCovarianceMatrix( CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                    [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                              covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                           [ 2., 4., 6. ],
                                                                           [ 3., 6., 9. ] ] ),
                                              scaling = VarianceScaling( ScalingType.Inverse,
                                                                         [ 1e-5, 5., 2e+7 ],
                                                                         [ 0.001, 0.1 ] ) )

        # verify content
        self.assertEqual( chunk.row_metadata, chunk.column_metadata )
        self.assertEqual( 1, len( chunk.row_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( True, chunk.has_variance_scaling )
        self.assertEqual( 2, chunk.variance_scaling.number_groups )
        self.assertEqual( 3, len( chunk.variance_scaling.energies ) )
        self.assertEqual( 2, len( chunk.variance_scaling.factors ) )
        self.assertAlmostEqual( 1e-5, chunk.variance_scaling.energies[0] )
        self.assertAlmostEqual( 5.  , chunk.variance_scaling.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.variance_scaling.energies[2] )
        self.assertAlmostEqual(  0.001, chunk.variance_scaling.factors[0] )
        self.assertAlmostEqual(  0.1  , chunk.variance_scaling.factors[1] )

        self.assertEqual( True, chunk.is_relative_matrix )
        self.assertEqual( False, chunk.is_absolute_matrix )
        self.assertEqual( False, chunk.is_off_diagonal )
        self.assertEqual( True, chunk.is_on_diagonal )

        self.assertIsNotNone( chunk.standard_deviations )
        self.assertIsNotNone( chunk.correlations )
        self.assertIsNotNone( chunk.eigenvalues )

        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[0,1] )
        self.assertAlmostEqual( 3., chunk.covariances[0,2] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 4., chunk.covariances[1,1] )
        self.assertAlmostEqual( 6., chunk.covariances[1,2] )
        self.assertAlmostEqual( 3., chunk.covariances[2,0] )
        self.assertAlmostEqual( 6., chunk.covariances[2,1] )
        self.assertAlmostEqual( 9., chunk.covariances[2,2] )

        self.assertAlmostEqual( 1., chunk.standard_deviations[0] )
        self.assertAlmostEqual( 2., chunk.standard_deviations[1] )
        self.assertAlmostEqual( 3., chunk.standard_deviations[2] )

        self.assertAlmostEqual( 1., chunk.correlations[0,0] )
        self.assertAlmostEqual( 1., chunk.correlations[0,1] )
        self.assertAlmostEqual( 1., chunk.correlations[0,2] )
        self.assertAlmostEqual( 1., chunk.correlations[1,0] )
        self.assertAlmostEqual( 1., chunk.correlations[1,1] )
        self.assertAlmostEqual( 1., chunk.correlations[1,2] )
        self.assertAlmostEqual( 1., chunk.correlations[2,0] )
        self.assertAlmostEqual( 1., chunk.correlations[2,1] )
        self.assertAlmostEqual( 1., chunk.correlations[2,2] )

        self.assertAlmostEqual( 14., chunk.eigenvalues[0] )
        self.assertAlmostEqual(  0., chunk.eigenvalues[1] )
        self.assertAlmostEqual(  0., chunk.eigenvalues[2] )

        self.assertAlmostEqual( 0.2672612419124246, chunk.eigenvectors[0][0] )
        self.assertAlmostEqual( 0.5345224838248487, chunk.eigenvectors[0][1] )
        self.assertAlmostEqual( 0.8017837257372732, chunk.eigenvectors[0][2] )

    def test_off_diagonal_covariance_block( self ) :

        # the data is given explicitly
        chunk = CrossSectionCovarianceMatrix( row_metadata = CrossSectionMetadata( [ ReactionID( 'n,U235->n,U235' ) ],
                                                                                   [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                              column_metadata = CrossSectionMetadata( [ ReactionID( 'n,U235->fission(t)' ) ],
                                                                                      [ 1e-5, 2., 2e+7 ] ),
                                              covariances = numpy.array( [ [ 1., 2. ],
                                                                           [ 2., 4. ],
                                                                           [ 3., 6. ] ] ) )

        # verify content
        self.assertNotEqual( chunk.row_metadata, chunk.column_metadata )

        self.assertEqual( 1, len( chunk.row_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( 1, len( chunk.column_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->fission(t)' ), chunk.column_metadata.reaction_identifiers[0] )
        self.assertEqual( 3, len( chunk.column_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 2.  , chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.column_metadata.energies[2] )

        self.assertEqual( False, chunk.has_variance_scaling )
        self.assertIsNone( chunk.variance_scaling )

        self.assertEqual( True, chunk.is_relative_matrix )
        self.assertEqual( False, chunk.is_absolute_matrix )
        self.assertEqual( True, chunk.is_off_diagonal )
        self.assertEqual( False, chunk.is_on_diagonal )

        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )
        self.assertIsNone( chunk.eigenvectors )

        self.assertAlmostEqual( 1., chunk.covariances[0,0] )
        self.assertAlmostEqual( 2., chunk.covariances[0,1] )
        self.assertAlmostEqual( 2., chunk.covariances[1,0] )
        self.assertAlmostEqual( 4., chunk.covariances[1,1] )
        self.assertAlmostEqual( 3., chunk.covariances[2,0] )
        self.assertAlmostEqual( 6., chunk.covariances[2,1] )

        chunk.calculate_standard_deviations()
        self.assertIsNone( chunk.standard_deviations )

        chunk.calculate_correlations( [ 1., 2., 3. ], [ 1., 2. ] )
        self.assertAlmostEqual( 1., chunk.correlations[0,0] )
        self.assertAlmostEqual( 1., chunk.correlations[0,1] )
        self.assertAlmostEqual( 1., chunk.correlations[1,0] )
        self.assertAlmostEqual( 1., chunk.correlations[1,1] )
        self.assertAlmostEqual( 1., chunk.correlations[2,0] )
        self.assertAlmostEqual( 1., chunk.correlations[2,1] )

        chunk.calculate_eigenvalues()
        self.assertIsNone( chunk.eigenvalues )
        self.assertIsNone( chunk.eigenvectors )

if __name__ == '__main__' :

    unittest.main()
