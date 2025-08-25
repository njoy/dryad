# standard imports
import unittest

# third party imports

# local imports
import numpy
from dryad.covariance import CrossSectionCovarianceBlock
from dryad.covariance import CrossSectionMetadata
from dryad.covariance import ScalingType
from dryad.covariance import VarianceScaling
from dryad.id import ParticleID
from dryad.id import ReactionID
from dryad.id import ReactionType

class Test_codex_CrossSectionCovarianceBlock( unittest.TestCase ) :
    """Unit test for the CrossSectionCovarianceBlock class."""

    def test_diagonal_covariance_block( self ) :

        # not using CrossSectionMetadata

        # the data is given explicitly - for a diagonal block without scaling
        chunk = CrossSectionCovarianceBlock( projectile = ParticleID( 'n' ),
                                             target = ParticleID( 'U235' ),
                                             reaction = ReactionID( 'n,U235->n,U235' ),
                                             energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                             covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                          [ 2., 4., 6. ],
                                                                          [ 3., 6., 9. ] ] ) )

        # verify content
        self.assertEqual( ParticleID( 'n' ), chunk.row_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.row_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.row_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertEqual( 3, chunk.row_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( ParticleID( 'n' ), chunk.column_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.column_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.column_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.column_metadata.energies ) )
        self.assertEqual( 3, chunk.column_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.column_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.column_metadata.energies[3] )

        self.assertEqual( False, chunk.has_variance_scaling )
        self.assertIsNone( chunk.variance_scaling )

        self.assertEqual( True, chunk.is_relative_block )
        self.assertEqual( False, chunk.is_absolute_block )
        self.assertEqual( False, chunk.is_off_diagonal_block )
        self.assertEqual( True, chunk.is_diagonal_block )

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

        chunk.calculate_standard_deviations()
        self.assertAlmostEqual( 1., chunk.standard_deviations[0] )
        self.assertAlmostEqual( 2., chunk.standard_deviations[1] )
        self.assertAlmostEqual( 3., chunk.standard_deviations[2] )

        chunk.calculate_correlations()
        self.assertAlmostEqual( 1., chunk.correlations[0,0] )
        self.assertAlmostEqual( 1., chunk.correlations[0,1] )
        self.assertAlmostEqual( 1., chunk.correlations[0,2] )
        self.assertAlmostEqual( 1., chunk.correlations[1,0] )
        self.assertAlmostEqual( 1., chunk.correlations[1,1] )
        self.assertAlmostEqual( 1., chunk.correlations[1,2] )
        self.assertAlmostEqual( 1., chunk.correlations[2,0] )
        self.assertAlmostEqual( 1., chunk.correlations[2,1] )
        self.assertAlmostEqual( 1., chunk.correlations[2,2] )

        chunk.calculate_eigenvalues()
        self.assertAlmostEqual( 0., chunk.eigenvalues[0] )
        self.assertAlmostEqual( 0., chunk.eigenvalues[1] )
        self.assertAlmostEqual( 14., chunk.eigenvalues[2] )

        # the data is given explicitly - for a diagonal block with scaling
        chunk = CrossSectionCovarianceBlock( projectile = ParticleID( 'n' ),
                                             target = ParticleID( 'U235' ),
                                             reaction = ReactionID( 'n,U235->n,U235' ),
                                             energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                             covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                          [ 2., 4., 6. ],
                                                                          [ 3., 6., 9. ] ] ),
                                             scaling = VarianceScaling( ScalingType.Inverse,
                                                                        [ 1e-5, 5., 2e+7 ],
                                                                        [ 0.001, 0.1 ] ),
                                             relative = True )

        # verify content
        self.assertEqual( ParticleID( 'n' ), chunk.row_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.row_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.row_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertEqual( 3, chunk.row_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( ParticleID( 'n' ), chunk.column_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.column_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.column_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.column_metadata.energies ) )
        self.assertEqual( 3, chunk.column_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.column_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.column_metadata.energies[3] )

        self.assertEqual( True, chunk.has_variance_scaling )
        self.assertEqual( 2, chunk.variance_scaling.number_groups )
        self.assertEqual( 3, len( chunk.variance_scaling.energies ) )
        self.assertEqual( 2, len( chunk.variance_scaling.factors ) )
        self.assertAlmostEqual( 1e-5, chunk.variance_scaling.energies[0] )
        self.assertAlmostEqual( 5.  , chunk.variance_scaling.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.variance_scaling.energies[2] )
        self.assertAlmostEqual(  0.001, chunk.variance_scaling.factors[0] )
        self.assertAlmostEqual(  0.1  , chunk.variance_scaling.factors[1] )

        self.assertEqual( True, chunk.is_relative_block )
        self.assertEqual( False, chunk.is_absolute_block )
        self.assertEqual( False, chunk.is_off_diagonal_block )
        self.assertEqual( True, chunk.is_diagonal_block )

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

        chunk.calculate_standard_deviations()
        self.assertAlmostEqual( 1., chunk.standard_deviations[0] )
        self.assertAlmostEqual( 2., chunk.standard_deviations[1] )
        self.assertAlmostEqual( 3., chunk.standard_deviations[2] )

        chunk.calculate_correlations()
        self.assertAlmostEqual( 1., chunk.correlations[0,0] )
        self.assertAlmostEqual( 1., chunk.correlations[0,1] )
        self.assertAlmostEqual( 1., chunk.correlations[0,2] )
        self.assertAlmostEqual( 1., chunk.correlations[1,0] )
        self.assertAlmostEqual( 1., chunk.correlations[1,1] )
        self.assertAlmostEqual( 1., chunk.correlations[1,2] )
        self.assertAlmostEqual( 1., chunk.correlations[2,0] )
        self.assertAlmostEqual( 1., chunk.correlations[2,1] )
        self.assertAlmostEqual( 1., chunk.correlations[2,2] )

        chunk.calculate_eigenvalues()
        self.assertAlmostEqual( 0., chunk.eigenvalues[0] )
        self.assertAlmostEqual( 0., chunk.eigenvalues[1] )
        self.assertAlmostEqual( 14., chunk.eigenvalues[2] )

        # using CrossSectionMetadata

        # the data is given explicitly - for a diagonal block without scaling
        chunk = CrossSectionCovarianceBlock( CrossSectionMetadata( ParticleID( 'n' ),
                                                                   ParticleID( 'U235' ),
                                                                   ReactionID( 'n,U235->n,U235' ),
                                                                   [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                             covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                          [ 2., 4., 6. ],
                                                                          [ 3., 6., 9. ] ] ) )

        # verify content
        self.assertEqual( ParticleID( 'n' ), chunk.row_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.row_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.row_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertEqual( 3, chunk.row_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( ParticleID( 'n' ), chunk.column_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.column_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.column_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.column_metadata.energies ) )
        self.assertEqual( 3, chunk.column_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.column_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.column_metadata.energies[3] )

        self.assertEqual( False, chunk.has_variance_scaling )
        self.assertIsNone( chunk.variance_scaling )

        self.assertEqual( True, chunk.is_relative_block )
        self.assertEqual( False, chunk.is_absolute_block )
        self.assertEqual( False, chunk.is_off_diagonal_block )
        self.assertEqual( True, chunk.is_diagonal_block )

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

        chunk.calculate_standard_deviations()
        self.assertAlmostEqual( 1., chunk.standard_deviations[0] )
        self.assertAlmostEqual( 2., chunk.standard_deviations[1] )
        self.assertAlmostEqual( 3., chunk.standard_deviations[2] )

        chunk.calculate_correlations()
        self.assertAlmostEqual( 1., chunk.correlations[0,0] )
        self.assertAlmostEqual( 1., chunk.correlations[0,1] )
        self.assertAlmostEqual( 1., chunk.correlations[0,2] )
        self.assertAlmostEqual( 1., chunk.correlations[1,0] )
        self.assertAlmostEqual( 1., chunk.correlations[1,1] )
        self.assertAlmostEqual( 1., chunk.correlations[1,2] )
        self.assertAlmostEqual( 1., chunk.correlations[2,0] )
        self.assertAlmostEqual( 1., chunk.correlations[2,1] )
        self.assertAlmostEqual( 1., chunk.correlations[2,2] )

        chunk.calculate_eigenvalues()
        self.assertAlmostEqual( 0., chunk.eigenvalues[0] )
        self.assertAlmostEqual( 0., chunk.eigenvalues[1] )
        self.assertAlmostEqual( 14., chunk.eigenvalues[2] )

        # the data is given explicitly - for a diagonal block with scaling
        chunk = CrossSectionCovarianceBlock( CrossSectionMetadata( ParticleID( 'n' ),
                                                                   ParticleID( 'U235' ),
                                                                   ReactionID( 'n,U235->n,U235' ),
                                                                   [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                             covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                          [ 2., 4., 6. ],
                                                                          [ 3., 6., 9. ] ] ),
                                             scaling = VarianceScaling( ScalingType.Inverse,
                                                                        [ 1e-5, 5., 2e+7 ],
                                                                        [ 0.001, 0.1 ] ) )

        # verify content
        self.assertEqual( ParticleID( 'n' ), chunk.row_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.row_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.row_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertEqual( 3, chunk.row_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( ParticleID( 'n' ), chunk.column_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.column_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.column_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.column_metadata.energies ) )
        self.assertEqual( 3, chunk.column_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.column_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.column_metadata.energies[3] )

        self.assertEqual( True, chunk.has_variance_scaling )
        self.assertEqual( 2, chunk.variance_scaling.number_groups )
        self.assertEqual( 3, len( chunk.variance_scaling.energies ) )
        self.assertEqual( 2, len( chunk.variance_scaling.factors ) )
        self.assertAlmostEqual( 1e-5, chunk.variance_scaling.energies[0] )
        self.assertAlmostEqual( 5.  , chunk.variance_scaling.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.variance_scaling.energies[2] )
        self.assertAlmostEqual(  0.001, chunk.variance_scaling.factors[0] )
        self.assertAlmostEqual(  0.1  , chunk.variance_scaling.factors[1] )

        self.assertEqual( True, chunk.is_relative_block )
        self.assertEqual( False, chunk.is_absolute_block )
        self.assertEqual( False, chunk.is_off_diagonal_block )
        self.assertEqual( True, chunk.is_diagonal_block )

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

        chunk.calculate_standard_deviations()
        self.assertAlmostEqual( 1., chunk.standard_deviations[0] )
        self.assertAlmostEqual( 2., chunk.standard_deviations[1] )
        self.assertAlmostEqual( 3., chunk.standard_deviations[2] )

        chunk.calculate_correlations()
        self.assertAlmostEqual( 1., chunk.correlations[0,0] )
        self.assertAlmostEqual( 1., chunk.correlations[0,1] )
        self.assertAlmostEqual( 1., chunk.correlations[0,2] )
        self.assertAlmostEqual( 1., chunk.correlations[1,0] )
        self.assertAlmostEqual( 1., chunk.correlations[1,1] )
        self.assertAlmostEqual( 1., chunk.correlations[1,2] )
        self.assertAlmostEqual( 1., chunk.correlations[2,0] )
        self.assertAlmostEqual( 1., chunk.correlations[2,1] )
        self.assertAlmostEqual( 1., chunk.correlations[2,2] )

        chunk.calculate_eigenvalues()
        self.assertAlmostEqual( 0., chunk.eigenvalues[0] )
        self.assertAlmostEqual( 0., chunk.eigenvalues[1] )
        self.assertAlmostEqual( 14., chunk.eigenvalues[2] )

    def test_off_diagonal_covariance_block( self ) :

        n = ParticleID.neutron()
        u235 = ParticleID( 92235 )

        ReactionID( n, u235, ReactionType( n, 2 ) )
        ReactionID( n, u235, ReactionType( n, 18 ) )

        # not using CrossSectionMetadata

        # the data is given explicitly
        chunk = CrossSectionCovarianceBlock( row_projectile = ParticleID( 'n' ),
                                             row_target = ParticleID( 'U235' ),
                                             row_reaction = ReactionID( 'n,U235->n,U235' ),
                                             row_energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                             column_projectile = ParticleID( 'n' ),
                                             column_target = ParticleID( 'U238' ),
                                             column_reaction = ReactionID( 'n,U235->fission(t)' ),
                                             column_energies = [ 1e-5, 2., 2e+7 ],
                                             covariances = numpy.array( [ [ 1., 2. ],
                                                                          [ 2., 4. ],
                                                                          [ 3., 6. ] ] ) )

        # verify content
        self.assertEqual( ParticleID( 'n' ), chunk.row_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.row_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.row_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertEqual( 3, chunk.row_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( ParticleID( 'n' ), chunk.column_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U238' ), chunk.column_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->fission(t)' ), chunk.column_metadata.reaction_identifier )
        self.assertEqual( 3, len( chunk.column_metadata.energies ) )
        self.assertEqual( 2, chunk.column_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 2.  , chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.column_metadata.energies[2] )

        self.assertEqual( False, chunk.has_variance_scaling )
        self.assertIsNone( chunk.variance_scaling )

        self.assertEqual( True, chunk.is_relative_block )
        self.assertEqual( False, chunk.is_absolute_block )
        self.assertEqual( True, chunk.is_off_diagonal_block )
        self.assertEqual( False, chunk.is_diagonal_block )

        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )

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

        # using CrossSectionMetadata

        # the data is given explicitly
        chunk = CrossSectionCovarianceBlock( row_metadata = CrossSectionMetadata( ParticleID( 'n' ),
                                                                                  ParticleID( 'U235' ),
                                                                                  ReactionID( 'n,U235->n,U235' ),
                                                                                  [ 1e-5, 1., 1e+6, 2e+7 ] ),
                                             column_metadata = CrossSectionMetadata( ParticleID( 'n' ),
                                                                                    ParticleID( 'U238' ),
                                                                                    ReactionID( 'n,U235->fission(t)' ),
                                                                                     [ 1e-5, 2., 2e+7 ] ),
                                             covariances = numpy.array( [ [ 1., 2. ],
                                                                          [ 2., 4. ],
                                                                          [ 3., 6. ] ] ) )

        # verify content
        self.assertEqual( ParticleID( 'n' ), chunk.row_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U235' ), chunk.row_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->n,U235' ), chunk.row_metadata.reaction_identifier )
        self.assertEqual( 4, len( chunk.row_metadata.energies ) )
        self.assertEqual( 3, chunk.row_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1.  , chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[2] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[3] )

        self.assertEqual( ParticleID( 'n' ), chunk.column_metadata.projectile_identifier )
        self.assertEqual( ParticleID( 'U238' ), chunk.column_metadata.target_identifier )
        self.assertEqual( ReactionID( 'n,U235->fission(t)' ), chunk.column_metadata.reaction_identifier )
        self.assertEqual( 3, len( chunk.column_metadata.energies ) )
        self.assertEqual( 2, chunk.column_metadata.number_groups )
        self.assertAlmostEqual( 1e-5, chunk.column_metadata.energies[0] )
        self.assertAlmostEqual( 2.  , chunk.column_metadata.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.column_metadata.energies[2] )

        self.assertEqual( False, chunk.has_variance_scaling )
        self.assertIsNone( chunk.variance_scaling )

        self.assertEqual( True, chunk.is_relative_block )
        self.assertEqual( False, chunk.is_absolute_block )
        self.assertEqual( True, chunk.is_off_diagonal_block )
        self.assertEqual( False, chunk.is_diagonal_block )

        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )

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

    def test_failures( self ) :

        print( '\n' )

        # the matrix is not square for a diagonal covariance block
        with self.assertRaises( Exception ) :

            chunk = CrossSectionCovarianceBlock( projectile = ParticleID( 'n' ),
                                                 target = ParticleID( 'U235' ),
                                                 reaction = ReactionID( 'n,U235->n,U235' ),
                                                 energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                                 covariances = numpy.array( [ [ 1., 2. ],
                                                                              [ 3., 4. ],
                                                                              [ 5., 6. ] ] ) )

        # the matrix is not symmetric for a diagonal covariance block
        with self.assertRaises( Exception ) :

            chunk = CrossSectionCovarianceBlock( projectile = ParticleID( 'n' ),
                                                 target = ParticleID( 'U235' ),
                                                 reaction = ReactionID( 'n,U235->n,U235' ),
                                                 energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                                 covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                              [ 2., 4., 6. ],
                                                                              [ 100000., 6., 9. ] ] ) )

        # the matrix order is not consistent with the energy boundaries for a diagonal covariance block
        with self.assertRaises( Exception ) :

            chunk = CrossSectionCovarianceBlock( projectile = ParticleID( 'n' ),
                                                 target = ParticleID( 'U235' ),
                                                 reaction = ReactionID( 'n,U235->n,U235' ),
                                                 energies = [ 1e-5, 1., 2e+7 ],
                                                 covariances = numpy.array( [ [ 1., 2., 3. ],
                                                                              [ 2., 4., 6. ],
                                                                              [ 3., 6., 9. ] ] ) )

        # the matrix order is not consistent with the energy boundaries for an off-diagonal covariance block (rows)
        with self.assertRaises( Exception ) :

            chunk = CrossSectionCovarianceBlock( row_projectile = ParticleID( 'n' ),
                                                 row_target = ParticleID( 'U235' ),
                                                 row_reaction = ReactionID( 'n,U235->n,U235' ),
                                                 row_energies = [ 1e-5, 1., 2e+7 ],
                                                 column_projectile = ParticleID( 'n' ),
                                                 column_target = ParticleID( 'U238' ),
                                                 column_reaction = ReactionID( 'n,U235->fission(t)' ),
                                                 column_energies = [ 1e-5, 2., 2e+7 ],
                                                 covariances = numpy.array( [ [ 1., 2. ],
                                                                              [ 2., 4. ],
                                                                              [ 3., 6. ] ] ) )

        # the matrix order is not consistent with the energy boundaries for an off-diagonal covariance block (columns)
        with self.assertRaises( Exception ) :

            chunk = CrossSectionCovarianceBlock( row_projectile = ParticleID( 'n' ),
                                                 row_target = ParticleID( 'U235' ),
                                                 row_reaction = ReactionID( 'n,U235->n,U235' ),
                                                 row_energies = [ 1e-5, 1., 1e+6, 2e+7 ],
                                                 column_projectile = ParticleID( 'n' ),
                                                 column_target = ParticleID( 'U238' ),
                                                 column_reaction = ReactionID( 'n,U235->fission(t)' ),
                                                 column_energies = [ 1e-5, 2e+7 ],
                                                 covariances = numpy.array( [ [ 1., 2. ],
                                                                              [ 2., 4. ],
                                                                              [ 3., 6. ] ] ) )

if __name__ == '__main__' :

    unittest.main()
