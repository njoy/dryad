# standard imports
import unittest

# third party imports

# local imports
import numpy
from njoy.dryad.covariance import ProductMultiplicityMetadata
from njoy.dryad.covariance import ProductMultiplicityCovarianceMatrix
from njoy.dryad.id import ParticleID
from njoy.dryad.id import ReactionID
from njoy.dryad.id import EnergyGroup

class Test_codex_ProductMultiplicityCovarianceMatrix( unittest.TestCase ) :
    """Unit test for the ProductMultiplicityCovarianceMatrix class."""

    def test_matrix( self ) :

        # valid covariance data for product multiplicities
        chunk = ProductMultiplicityCovarianceMatrix(
                    metadata = ProductMultiplicityMetadata( [ ReactionID( 'n,U235->fission' ) ],
                                                            [ 1e-5, 1e+6, 2e+7 ],
                                                            [ ParticleID( 'Y99' ), ParticleID( 'Mo99' ),
                                                              ParticleID( 'Pr148' ), ParticleID( 'Pr148_e1' ) ] ),
                    covariances = numpy.array( [ [  3.350497e-07,  3.086034e-07,  1.031271e-06, -3.468670e-10, 1.186658e-07,  1.953402e-07,  8.550732e-08, -1.352565e-09 ],
                                                 [  3.086034e-07,  1.390798e-06,  7.070720e-07,  8.186300e-10, -2.261425e-08,  4.553737e-07, -3.459165e-07, -9.048060e-10 ],
                                                 [  1.031271e-06,  7.070720e-07,  4.132664e-06, -4.264964e-09, 9.952311e-07,  1.147504e-06,  3.036135e-06, -2.642949e-09 ],
                                                 [ -3.468670e-10,  8.186300e-10, -4.264964e-09,  3.727600e-10, 3.071510e-10,  3.816056e-09,  5.460586e-09,  3.336860e-10 ],
                                                 [  1.186658e-07, -2.261425e-08,  9.952311e-07,  3.071510e-10, 2.792847e-07,  2.435102e-07,  4.742642e-07, -1.127960e-09 ],
                                                 [  1.953402e-07,  4.553737e-07,  1.147504e-06,  3.816056e-09, 2.435102e-07,  9.364803e-07,  1.744701e-07, -2.394143e-09 ],
                                                 [  8.550732e-08, -3.459165e-07,  3.036135e-06,  5.460586e-09, 4.742642e-07,  1.744701e-07,  4.887436e-06, -2.686310e-10 ],
                                                 [ -1.352565e-09, -9.048060e-10, -2.642949e-09,  3.336860e-10, -1.127960e-09, -2.394143e-09, -2.686310e-10,  3.280511e-09 ] ] ) )

        # verify content
        self.assertEqual( 1, len( chunk.row_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->fission' ), chunk.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 3, len( chunk.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[2] )
        self.assertEqual( 4, len( chunk.row_metadata.product_identifiers ) )
        self.assertEqual( ParticleID( 'Y99' ), chunk.row_metadata.product_identifiers[0] )
        self.assertEqual( ParticleID( 'Mo99' ), chunk.row_metadata.product_identifiers[1] )
        self.assertEqual( ParticleID( 'Pr148' ), chunk.row_metadata.product_identifiers[2] )
        self.assertEqual( ParticleID( 'Pr148_e1' ), chunk.row_metadata.product_identifiers[3] )
        self.assertEqual( chunk.row_metadata, chunk.column_metadata )

        self.assertEqual( True, chunk.is_relative_matrix )
        self.assertEqual( False, chunk.is_absolute_matrix )
        self.assertEqual( False, chunk.is_off_diagonal )
        self.assertEqual( True, chunk.is_on_diagonal )

        self.assertIsNone( chunk.standard_deviations )
        self.assertIsNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )

        self.assertAlmostEqual(  3.350497e-07, chunk.covariances[0,0] )
        self.assertAlmostEqual(  3.086034e-07, chunk.covariances[0,1] )
        self.assertAlmostEqual(  1.031271e-06, chunk.covariances[0,2] )
        self.assertAlmostEqual( -3.468670e-10, chunk.covariances[0,3] )
        self.assertAlmostEqual(  1.186658e-07, chunk.covariances[0,4] )
        self.assertAlmostEqual(  1.953402e-07, chunk.covariances[0,5] )
        self.assertAlmostEqual(  8.550732e-08, chunk.covariances[0,6] )
        self.assertAlmostEqual( -1.352565e-09, chunk.covariances[0,7] )
        self.assertAlmostEqual(  3.086034e-07, chunk.covariances[1,0] )
        self.assertAlmostEqual(  1.390798e-06, chunk.covariances[1,1] )
        self.assertAlmostEqual(  7.070720e-07, chunk.covariances[1,2] )
        self.assertAlmostEqual(  8.186300e-10, chunk.covariances[1,3] )
        self.assertAlmostEqual( -2.261425e-08, chunk.covariances[1,4] )
        self.assertAlmostEqual(  4.553737e-07, chunk.covariances[1,5] )
        self.assertAlmostEqual( -3.459165e-07, chunk.covariances[1,6] )
        self.assertAlmostEqual( -9.048060e-10, chunk.covariances[1,7] )
        self.assertAlmostEqual(  1.031271e-06, chunk.covariances[2,0] )
        self.assertAlmostEqual(  7.070720e-07, chunk.covariances[2,1] )
        self.assertAlmostEqual(  4.132664e-06, chunk.covariances[2,2] )
        self.assertAlmostEqual( -4.264964e-09, chunk.covariances[2,3] )
        self.assertAlmostEqual(  9.952311e-07, chunk.covariances[2,4] )
        self.assertAlmostEqual(  1.147504e-06, chunk.covariances[2,5] )
        self.assertAlmostEqual(  3.036135e-06, chunk.covariances[2,6] )
        self.assertAlmostEqual( -2.642949e-09, chunk.covariances[2,7] )
        self.assertAlmostEqual( -3.468670e-10, chunk.covariances[3,0] )
        self.assertAlmostEqual(  8.186300e-10, chunk.covariances[3,1] )
        self.assertAlmostEqual( -4.264964e-09, chunk.covariances[3,2] )
        self.assertAlmostEqual(  3.727600e-10, chunk.covariances[3,3] )
        self.assertAlmostEqual(  3.071510e-10, chunk.covariances[3,4] )
        self.assertAlmostEqual(  3.816056e-09, chunk.covariances[3,5] )
        self.assertAlmostEqual(  5.460586e-09, chunk.covariances[3,6] )
        self.assertAlmostEqual(  3.336860e-10, chunk.covariances[3,7] )
        self.assertAlmostEqual(  1.186658e-07, chunk.covariances[4,0] )
        self.assertAlmostEqual( -2.261425e-08, chunk.covariances[4,1] )
        self.assertAlmostEqual(  9.952311e-07, chunk.covariances[4,2] )
        self.assertAlmostEqual(  3.071510e-10, chunk.covariances[4,3] )
        self.assertAlmostEqual(  2.792847e-07, chunk.covariances[4,4] )
        self.assertAlmostEqual(  2.435102e-07, chunk.covariances[4,5] )
        self.assertAlmostEqual(  4.742642e-07, chunk.covariances[4,6] )
        self.assertAlmostEqual( -1.127960e-09, chunk.covariances[4,7] )
        self.assertAlmostEqual(  1.953402e-07, chunk.covariances[5,0] )
        self.assertAlmostEqual(  4.553737e-07, chunk.covariances[5,1] )
        self.assertAlmostEqual(  1.147504e-06, chunk.covariances[5,2] )
        self.assertAlmostEqual(  3.816056e-09, chunk.covariances[5,3] )
        self.assertAlmostEqual(  2.435102e-07, chunk.covariances[5,4] )
        self.assertAlmostEqual(  9.364803e-07, chunk.covariances[5,5] )
        self.assertAlmostEqual(  1.744701e-07, chunk.covariances[5,6] )
        self.assertAlmostEqual( -2.394143e-09, chunk.covariances[5,7] )
        self.assertAlmostEqual(  8.550732e-08, chunk.covariances[6,0] )
        self.assertAlmostEqual( -3.459165e-07, chunk.covariances[6,1] )
        self.assertAlmostEqual(  3.036135e-06, chunk.covariances[6,2] )
        self.assertAlmostEqual(  5.460586e-09, chunk.covariances[6,3] )
        self.assertAlmostEqual(  4.742642e-07, chunk.covariances[6,4] )
        self.assertAlmostEqual(  1.744701e-07, chunk.covariances[6,5] )
        self.assertAlmostEqual(  4.887436e-06, chunk.covariances[6,6] )
        self.assertAlmostEqual( -2.686310e-10, chunk.covariances[6,7] )
        self.assertAlmostEqual( -1.352565e-09, chunk.covariances[7,0] )
        self.assertAlmostEqual( -9.048060e-10, chunk.covariances[7,1] )
        self.assertAlmostEqual( -2.642949e-09, chunk.covariances[7,2] )
        self.assertAlmostEqual(  3.336860e-10, chunk.covariances[7,3] )
        self.assertAlmostEqual( -1.127960e-09, chunk.covariances[7,4] )
        self.assertAlmostEqual( -2.394143e-09, chunk.covariances[7,5] )
        self.assertAlmostEqual( -2.686310e-10, chunk.covariances[7,6] )
        self.assertAlmostEqual(  3.280511e-09, chunk.covariances[7,7] )

        chunk.calculate_standard_deviations()
        self.assertAlmostEqual( 5.78834777807968e-04, chunk.standard_deviations[0] )
        self.assertAlmostEqual( 1.17932099107919e-03, chunk.standard_deviations[1] )
        self.assertAlmostEqual( 2.03289547198079e-03, chunk.standard_deviations[2] )
        self.assertAlmostEqual( 1.93069935515605e-05, chunk.standard_deviations[3] )
        self.assertAlmostEqual( 5.28473935024236e-04, chunk.standard_deviations[4] )
        self.assertAlmostEqual( 9.67719122473045e-04, chunk.standard_deviations[5] )
        self.assertAlmostEqual( 2.21075462229529e-03, chunk.standard_deviations[6] )
        self.assertAlmostEqual( 5.72757453028767e-05, chunk.standard_deviations[7] )

        chunk.calculate_correlations()
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[0,0] )
        self.assertAlmostEqual(  4.52078716301036e-01, chunk.correlations[0,1] )
        self.assertAlmostEqual(  8.76401556189488e-01, chunk.correlations[0,2] )
        self.assertAlmostEqual( -3.10379990825034e-02, chunk.correlations[0,3] )
        self.assertAlmostEqual(  3.87924654926139e-01, chunk.correlations[0,4] )
        self.assertAlmostEqual(  3.48728698045195e-01, chunk.correlations[0,5] )
        self.assertAlmostEqual(  6.68202561925324e-02, chunk.correlations[0,6] )
        self.assertAlmostEqual( -4.07974274908842e-02, chunk.correlations[0,7] )
        self.assertAlmostEqual(  4.52078716301036e-01, chunk.correlations[1,0] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[1,1] )
        self.assertAlmostEqual(  2.94928377943159e-01, chunk.correlations[1,2] )
        self.assertAlmostEqual(  3.59534835487576e-02, chunk.correlations[1,3] )
        self.assertAlmostEqual( -3.62849549313329e-02, chunk.correlations[1,4] )
        self.assertAlmostEqual(  3.99012584110026e-01, chunk.correlations[1,5] )
        self.assertAlmostEqual( -1.32677936246521e-01, chunk.correlations[1,6] )
        self.assertAlmostEqual( -1.33953076941197e-02, chunk.correlations[1,7] )
        self.assertAlmostEqual(  8.76401556189488e-01, chunk.correlations[2,0] )
        self.assertAlmostEqual(  2.94928377943159e-01, chunk.correlations[2,1] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[2,2] )
        self.assertAlmostEqual( -1.08663995484036e-01, chunk.correlations[2,3] )
        self.assertAlmostEqual(  9.26371782910094e-01, chunk.correlations[2,4] )
        self.assertAlmostEqual(  5.83297126018077e-01, chunk.correlations[2,5] )
        self.assertAlmostEqual(  6.75562428243337e-01, chunk.correlations[2,6] )
        self.assertAlmostEqual( -2.26988045368907e-02, chunk.correlations[2,7] )
        self.assertAlmostEqual( -3.10379990825034e-02, chunk.correlations[3,0] )
        self.assertAlmostEqual(  3.59534835487576e-02, chunk.correlations[3,1] )
        self.assertAlmostEqual( -1.08663995484036e-01, chunk.correlations[3,2] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[3,3] )
        self.assertAlmostEqual(  3.01032724933124e-02, chunk.correlations[3,4] )
        self.assertAlmostEqual(  2.04244685455433e-01, chunk.correlations[3,5] )
        self.assertAlmostEqual(  1.27933434186385e-01, chunk.correlations[3,6] )
        self.assertAlmostEqual(  3.01753686987760e-01, chunk.correlations[3,7] )
        self.assertAlmostEqual(  3.87924654926139e-01, chunk.correlations[4,0] )
        self.assertAlmostEqual( -3.62849549313329e-02, chunk.correlations[4,1] )
        self.assertAlmostEqual(  9.26371782910094e-01, chunk.correlations[4,2] )
        self.assertAlmostEqual(  3.01032724933124e-02, chunk.correlations[4,3] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[4,4] )
        self.assertAlmostEqual(  4.76150519164124e-01, chunk.correlations[4,5] )
        self.assertAlmostEqual(  4.05934748518847e-01, chunk.correlations[4,6] )
        self.assertAlmostEqual( -3.72648500015370e-02, chunk.correlations[4,7] )
        self.assertAlmostEqual(  3.48728698045195e-01, chunk.correlations[5,0] )
        self.assertAlmostEqual(  3.99012584110026e-01, chunk.correlations[5,1] )
        self.assertAlmostEqual(  5.83297126018077e-01, chunk.correlations[5,2] )
        self.assertAlmostEqual(  2.04244685455433e-01, chunk.correlations[5,3] )
        self.assertAlmostEqual(  4.76150519164124e-01, chunk.correlations[5,4] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[5,5] )
        self.assertAlmostEqual(  8.15513482313117e-02, chunk.correlations[5,6] )
        self.assertAlmostEqual( -4.31946555113209e-02, chunk.correlations[5,7] )
        self.assertAlmostEqual(  6.68202561925324e-02, chunk.correlations[6,0] )
        self.assertAlmostEqual( -1.32677936246521e-01, chunk.correlations[6,1] )
        self.assertAlmostEqual(  6.75562428243337e-01, chunk.correlations[6,2] )
        self.assertAlmostEqual(  1.27933434186385e-01, chunk.correlations[6,3] )
        self.assertAlmostEqual(  4.05934748518847e-01, chunk.correlations[6,4] )
        self.assertAlmostEqual(  8.15513482313117e-02, chunk.correlations[6,5] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[6,6] )
        self.assertAlmostEqual( -2.12150880161591e-03, chunk.correlations[6,7] )
        self.assertAlmostEqual( -4.07974274908842e-02, chunk.correlations[7,0] )
        self.assertAlmostEqual( -1.33953076941197e-02, chunk.correlations[7,1] )
        self.assertAlmostEqual( -2.26988045368907e-02, chunk.correlations[7,2] )
        self.assertAlmostEqual(  3.01753686987760e-01, chunk.correlations[7,3] )
        self.assertAlmostEqual( -3.72648500015370e-02, chunk.correlations[7,4] )
        self.assertAlmostEqual( -4.31946555113209e-02, chunk.correlations[7,5] )
        self.assertAlmostEqual( -2.12150880161591e-03, chunk.correlations[7,6] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[7,7] )

        chunk.calculate_eigenvalues()
        self.assertAlmostEqual( -2.39076849693257e-07, chunk.eigenvalues[0] )
        self.assertAlmostEqual(  3.43367202411662e-10, chunk.eigenvalues[1] )
        self.assertAlmostEqual(  3.31256655183549e-09, chunk.eigenvalues[2] )
        self.assertAlmostEqual(  1.08751047007600e-07, chunk.eigenvalues[3] )
        self.assertAlmostEqual(  5.09348096171567e-07, chunk.eigenvalues[4] )
        self.assertAlmostEqual(  8.72998692347036e-07, chunk.eigenvalues[5] )
        self.assertAlmostEqual(  2.77607998044769e-06, chunk.eigenvalues[6] )
        self.assertAlmostEqual(  7.93360907096512e-06, chunk.eigenvalues[7] )

        # valid correlation data for product multiplicities
        chunk = ProductMultiplicityCovarianceMatrix(
                    metadata = ProductMultiplicityMetadata( [ ReactionID( 'n,U235->fission' ) ],
                                                            [ 1e-5, 1e+6, 2e+7 ],
                                                            [ ParticleID( 'Y99' ), ParticleID( 'Mo99' ),
                                                              ParticleID( 'Pr148' ), ParticleID( 'Pr148_e1' ) ] ),
                    deviations = [ 5.78834777807968e-04, 1.17932099107919e-03,
                                   2.03289547198079e-03, 1.93069935515605e-05,
                                   5.28473935024236e-04, 9.67719122473045e-04,
                                   2.21075462229529e-03, 5.72757453028767e-05 ],
                    correlations = numpy.array( [ [  1.00000000000000e+00,  4.52078716301036e-01,  8.76401556189488e-01, -3.10379990825034e-02,
                                                     3.87924654926139e-01,  3.48728698045195e-01,  6.68202561925324e-02, -4.07974274908842e-02 ],
                                                  [  4.52078716301036e-01,  1.00000000000000e+00,  2.94928377943159e-01,  3.59534835487576e-02,
                                                    -3.62849549313329e-02,  3.99012584110026e-01, -1.32677936246521e-01, -1.33953076941197e-02 ],
                                                  [  8.76401556189488e-01,  2.94928377943159e-01,  1.00000000000000e+00, -1.08663995484036e-01,
                                                     9.26371782910094e-01,  5.83297126018077e-01,  6.75562428243337e-01, -2.26988045368907e-02 ],
                                                  [ -3.10379990825034e-02,  3.59534835487576e-02, -1.08663995484036e-01,  1.00000000000000e+00,
                                                    3.01032724933124e-02,  2.04244685455433e-01,  1.27933434186385e-01,  3.01753686987760e-01 ],
                                                  [ 3.87924654926139e-01, -3.62849549313329e-02,  9.26371782910094e-01,  3.01032724933124e-02,
                                                    1.00000000000000e+00,  4.76150519164124e-01,  4.05934748518847e-01, -3.72648500015370e-02 ],
                                                  [ 3.48728698045195e-01,  3.99012584110026e-01,  5.83297126018077e-01,  2.04244685455433e-01,
                                                    4.76150519164124e-01,  1.00000000000000e+00,  8.15513482313117e-02, -4.31946555113209e-02 ],
                                                  [ 6.68202561925324e-02, -1.32677936246521e-01,  6.75562428243337e-01,  1.27933434186385e-01,
                                                    4.05934748518847e-01,  8.15513482313117e-02,  1.00000000000000e+00, -2.12150880161591e-03 ],
                                                  [ -4.07974274908842e-02, -1.33953076941197e-02, -2.26988045368907e-02,  3.01753686987760e-01,
                                                    -3.72648500015370e-02, -4.31946555113209e-02, -2.12150880161591e-03,  1.00000000000000e+00 ] ] ) )

        # verify content
        self.assertEqual( 1, len( chunk.row_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->fission' ), chunk.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 3, len( chunk.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, chunk.row_metadata.energies[0] )
        self.assertAlmostEqual( 1e+6, chunk.row_metadata.energies[1] )
        self.assertAlmostEqual( 2e+7, chunk.row_metadata.energies[2] )
        self.assertEqual( 4, len( chunk.row_metadata.product_identifiers ) )
        self.assertEqual( ParticleID( 'Y99' ), chunk.row_metadata.product_identifiers[0] )
        self.assertEqual( ParticleID( 'Mo99' ), chunk.row_metadata.product_identifiers[1] )
        self.assertEqual( ParticleID( 'Pr148' ), chunk.row_metadata.product_identifiers[2] )
        self.assertEqual( ParticleID( 'Pr148_e1' ), chunk.row_metadata.product_identifiers[3] )
        self.assertEqual( chunk.row_metadata, chunk.column_metadata )

        self.assertEqual( True, chunk.is_relative_matrix )
        self.assertEqual( False, chunk.is_absolute_matrix )
        self.assertEqual( False, chunk.is_off_diagonal )
        self.assertEqual( True, chunk.is_on_diagonal )

        self.assertIsNotNone( chunk.standard_deviations )
        self.assertIsNotNone( chunk.correlations )
        self.assertIsNone( chunk.eigenvalues )

        self.assertAlmostEqual(  3.350497e-07, chunk.covariances[0,0] )
        self.assertAlmostEqual(  3.086034e-07, chunk.covariances[0,1] )
        self.assertAlmostEqual(  1.031271e-06, chunk.covariances[0,2] )
        self.assertAlmostEqual( -3.468670e-10, chunk.covariances[0,3] )
        self.assertAlmostEqual(  1.186658e-07, chunk.covariances[0,4] )
        self.assertAlmostEqual(  1.953402e-07, chunk.covariances[0,5] )
        self.assertAlmostEqual(  8.550732e-08, chunk.covariances[0,6] )
        self.assertAlmostEqual( -1.352565e-09, chunk.covariances[0,7] )
        self.assertAlmostEqual(  3.086034e-07, chunk.covariances[1,0] )
        self.assertAlmostEqual(  1.390798e-06, chunk.covariances[1,1] )
        self.assertAlmostEqual(  7.070720e-07, chunk.covariances[1,2] )
        self.assertAlmostEqual(  8.186300e-10, chunk.covariances[1,3] )
        self.assertAlmostEqual( -2.261425e-08, chunk.covariances[1,4] )
        self.assertAlmostEqual(  4.553737e-07, chunk.covariances[1,5] )
        self.assertAlmostEqual( -3.459165e-07, chunk.covariances[1,6] )
        self.assertAlmostEqual( -9.048060e-10, chunk.covariances[1,7] )
        self.assertAlmostEqual(  1.031271e-06, chunk.covariances[2,0] )
        self.assertAlmostEqual(  7.070720e-07, chunk.covariances[2,1] )
        self.assertAlmostEqual(  4.132664e-06, chunk.covariances[2,2] )
        self.assertAlmostEqual( -4.264964e-09, chunk.covariances[2,3] )
        self.assertAlmostEqual(  9.952311e-07, chunk.covariances[2,4] )
        self.assertAlmostEqual(  1.147504e-06, chunk.covariances[2,5] )
        self.assertAlmostEqual(  3.036135e-06, chunk.covariances[2,6] )
        self.assertAlmostEqual( -2.642949e-09, chunk.covariances[2,7] )
        self.assertAlmostEqual( -3.468670e-10, chunk.covariances[3,0] )
        self.assertAlmostEqual(  8.186300e-10, chunk.covariances[3,1] )
        self.assertAlmostEqual( -4.264964e-09, chunk.covariances[3,2] )
        self.assertAlmostEqual(  3.727600e-10, chunk.covariances[3,3] )
        self.assertAlmostEqual(  3.071510e-10, chunk.covariances[3,4] )
        self.assertAlmostEqual(  3.816056e-09, chunk.covariances[3,5] )
        self.assertAlmostEqual(  5.460586e-09, chunk.covariances[3,6] )
        self.assertAlmostEqual(  3.336860e-10, chunk.covariances[3,7] )
        self.assertAlmostEqual(  1.186658e-07, chunk.covariances[4,0] )
        self.assertAlmostEqual( -2.261425e-08, chunk.covariances[4,1] )
        self.assertAlmostEqual(  9.952311e-07, chunk.covariances[4,2] )
        self.assertAlmostEqual(  3.071510e-10, chunk.covariances[4,3] )
        self.assertAlmostEqual(  2.792847e-07, chunk.covariances[4,4] )
        self.assertAlmostEqual(  2.435102e-07, chunk.covariances[4,5] )
        self.assertAlmostEqual(  4.742642e-07, chunk.covariances[4,6] )
        self.assertAlmostEqual( -1.127960e-09, chunk.covariances[4,7] )
        self.assertAlmostEqual(  1.953402e-07, chunk.covariances[5,0] )
        self.assertAlmostEqual(  4.553737e-07, chunk.covariances[5,1] )
        self.assertAlmostEqual(  1.147504e-06, chunk.covariances[5,2] )
        self.assertAlmostEqual(  3.816056e-09, chunk.covariances[5,3] )
        self.assertAlmostEqual(  2.435102e-07, chunk.covariances[5,4] )
        self.assertAlmostEqual(  9.364803e-07, chunk.covariances[5,5] )
        self.assertAlmostEqual(  1.744701e-07, chunk.covariances[5,6] )
        self.assertAlmostEqual( -2.394143e-09, chunk.covariances[5,7] )
        self.assertAlmostEqual(  8.550732e-08, chunk.covariances[6,0] )
        self.assertAlmostEqual( -3.459165e-07, chunk.covariances[6,1] )
        self.assertAlmostEqual(  3.036135e-06, chunk.covariances[6,2] )
        self.assertAlmostEqual(  5.460586e-09, chunk.covariances[6,3] )
        self.assertAlmostEqual(  4.742642e-07, chunk.covariances[6,4] )
        self.assertAlmostEqual(  1.744701e-07, chunk.covariances[6,5] )
        self.assertAlmostEqual(  4.887436e-06, chunk.covariances[6,6] )
        self.assertAlmostEqual( -2.686310e-10, chunk.covariances[6,7] )
        self.assertAlmostEqual( -1.352565e-09, chunk.covariances[7,0] )
        self.assertAlmostEqual( -9.048060e-10, chunk.covariances[7,1] )
        self.assertAlmostEqual( -2.642949e-09, chunk.covariances[7,2] )
        self.assertAlmostEqual(  3.336860e-10, chunk.covariances[7,3] )
        self.assertAlmostEqual( -1.127960e-09, chunk.covariances[7,4] )
        self.assertAlmostEqual( -2.394143e-09, chunk.covariances[7,5] )
        self.assertAlmostEqual( -2.686310e-10, chunk.covariances[7,6] )
        self.assertAlmostEqual(  3.280511e-09, chunk.covariances[7,7] )

        self.assertAlmostEqual( 5.78834777807968e-04, chunk.standard_deviations[0] )
        self.assertAlmostEqual( 1.17932099107919e-03, chunk.standard_deviations[1] )
        self.assertAlmostEqual( 2.03289547198079e-03, chunk.standard_deviations[2] )
        self.assertAlmostEqual( 1.93069935515605e-05, chunk.standard_deviations[3] )
        self.assertAlmostEqual( 5.28473935024236e-04, chunk.standard_deviations[4] )
        self.assertAlmostEqual( 9.67719122473045e-04, chunk.standard_deviations[5] )
        self.assertAlmostEqual( 2.21075462229529e-03, chunk.standard_deviations[6] )
        self.assertAlmostEqual( 5.72757453028767e-05, chunk.standard_deviations[7] )

        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[0,0] )
        self.assertAlmostEqual(  4.52078716301036e-01, chunk.correlations[0,1] )
        self.assertAlmostEqual(  8.76401556189488e-01, chunk.correlations[0,2] )
        self.assertAlmostEqual( -3.10379990825034e-02, chunk.correlations[0,3] )
        self.assertAlmostEqual(  3.87924654926139e-01, chunk.correlations[0,4] )
        self.assertAlmostEqual(  3.48728698045195e-01, chunk.correlations[0,5] )
        self.assertAlmostEqual(  6.68202561925324e-02, chunk.correlations[0,6] )
        self.assertAlmostEqual( -4.07974274908842e-02, chunk.correlations[0,7] )
        self.assertAlmostEqual(  4.52078716301036e-01, chunk.correlations[1,0] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[1,1] )
        self.assertAlmostEqual(  2.94928377943159e-01, chunk.correlations[1,2] )
        self.assertAlmostEqual(  3.59534835487576e-02, chunk.correlations[1,3] )
        self.assertAlmostEqual( -3.62849549313329e-02, chunk.correlations[1,4] )
        self.assertAlmostEqual(  3.99012584110026e-01, chunk.correlations[1,5] )
        self.assertAlmostEqual( -1.32677936246521e-01, chunk.correlations[1,6] )
        self.assertAlmostEqual( -1.33953076941197e-02, chunk.correlations[1,7] )
        self.assertAlmostEqual(  8.76401556189488e-01, chunk.correlations[2,0] )
        self.assertAlmostEqual(  2.94928377943159e-01, chunk.correlations[2,1] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[2,2] )
        self.assertAlmostEqual( -1.08663995484036e-01, chunk.correlations[2,3] )
        self.assertAlmostEqual(  9.26371782910094e-01, chunk.correlations[2,4] )
        self.assertAlmostEqual(  5.83297126018077e-01, chunk.correlations[2,5] )
        self.assertAlmostEqual(  6.75562428243337e-01, chunk.correlations[2,6] )
        self.assertAlmostEqual( -2.26988045368907e-02, chunk.correlations[2,7] )
        self.assertAlmostEqual( -3.10379990825034e-02, chunk.correlations[3,0] )
        self.assertAlmostEqual(  3.59534835487576e-02, chunk.correlations[3,1] )
        self.assertAlmostEqual( -1.08663995484036e-01, chunk.correlations[3,2] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[3,3] )
        self.assertAlmostEqual(  3.01032724933124e-02, chunk.correlations[3,4] )
        self.assertAlmostEqual(  2.04244685455433e-01, chunk.correlations[3,5] )
        self.assertAlmostEqual(  1.27933434186385e-01, chunk.correlations[3,6] )
        self.assertAlmostEqual(  3.01753686987760e-01, chunk.correlations[3,7] )
        self.assertAlmostEqual(  3.87924654926139e-01, chunk.correlations[4,0] )
        self.assertAlmostEqual( -3.62849549313329e-02, chunk.correlations[4,1] )
        self.assertAlmostEqual(  9.26371782910094e-01, chunk.correlations[4,2] )
        self.assertAlmostEqual(  3.01032724933124e-02, chunk.correlations[4,3] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[4,4] )
        self.assertAlmostEqual(  4.76150519164124e-01, chunk.correlations[4,5] )
        self.assertAlmostEqual(  4.05934748518847e-01, chunk.correlations[4,6] )
        self.assertAlmostEqual( -3.72648500015370e-02, chunk.correlations[4,7] )
        self.assertAlmostEqual(  3.48728698045195e-01, chunk.correlations[5,0] )
        self.assertAlmostEqual(  3.99012584110026e-01, chunk.correlations[5,1] )
        self.assertAlmostEqual(  5.83297126018077e-01, chunk.correlations[5,2] )
        self.assertAlmostEqual(  2.04244685455433e-01, chunk.correlations[5,3] )
        self.assertAlmostEqual(  4.76150519164124e-01, chunk.correlations[5,4] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[5,5] )
        self.assertAlmostEqual(  8.15513482313117e-02, chunk.correlations[5,6] )
        self.assertAlmostEqual( -4.31946555113209e-02, chunk.correlations[5,7] )
        self.assertAlmostEqual(  6.68202561925324e-02, chunk.correlations[6,0] )
        self.assertAlmostEqual( -1.32677936246521e-01, chunk.correlations[6,1] )
        self.assertAlmostEqual(  6.75562428243337e-01, chunk.correlations[6,2] )
        self.assertAlmostEqual(  1.27933434186385e-01, chunk.correlations[6,3] )
        self.assertAlmostEqual(  4.05934748518847e-01, chunk.correlations[6,4] )
        self.assertAlmostEqual(  8.15513482313117e-02, chunk.correlations[6,5] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[6,6] )
        self.assertAlmostEqual( -2.12150880161591e-03, chunk.correlations[6,7] )
        self.assertAlmostEqual( -4.07974274908842e-02, chunk.correlations[7,0] )
        self.assertAlmostEqual( -1.33953076941197e-02, chunk.correlations[7,1] )
        self.assertAlmostEqual( -2.26988045368907e-02, chunk.correlations[7,2] )
        self.assertAlmostEqual(  3.01753686987760e-01, chunk.correlations[7,3] )
        self.assertAlmostEqual( -3.72648500015370e-02, chunk.correlations[7,4] )
        self.assertAlmostEqual( -4.31946555113209e-02, chunk.correlations[7,5] )
        self.assertAlmostEqual( -2.12150880161591e-03, chunk.correlations[7,6] )
        self.assertAlmostEqual(  1.00000000000000e+00, chunk.correlations[7,7] )

        chunk.calculate_eigenvalues()
        self.assertAlmostEqual( -2.39076849693257e-07, chunk.eigenvalues[0] )
        self.assertAlmostEqual(  3.43367202411662e-10, chunk.eigenvalues[1] )
        self.assertAlmostEqual(  3.31256655183549e-09, chunk.eigenvalues[2] )
        self.assertAlmostEqual(  1.08751047007600e-07, chunk.eigenvalues[3] )
        self.assertAlmostEqual(  5.09348096171567e-07, chunk.eigenvalues[4] )
        self.assertAlmostEqual(  8.72998692347036e-07, chunk.eigenvalues[5] )
        self.assertAlmostEqual(  2.77607998044769e-06, chunk.eigenvalues[6] )
        self.assertAlmostEqual(  7.93360907096512e-06, chunk.eigenvalues[7] )

    def test_extract( self ) :

        # valid covariance data for product multiplicities
        chunk = ProductMultiplicityCovarianceMatrix(
                    metadata = ProductMultiplicityMetadata( [ ReactionID( 'n,U235->fission' ) ],
                                                            [ 1e-5, 1e+6, 2e+7 ],
                                                            [ ParticleID( 'Y99' ), ParticleID( 'Mo99' ),
                                                              ParticleID( 'Pr148' ), ParticleID( 'Pr148_e1' ) ] ),
                    covariances = numpy.array( [ [  3.350497e-07,  3.086034e-07,  1.031271e-06, -3.468670e-10, 1.186658e-07,  1.953402e-07,  8.550732e-08, -1.352565e-09 ],
                                                 [  3.086034e-07,  1.390798e-06,  7.070720e-07,  8.186300e-10, -2.261425e-08,  4.553737e-07, -3.459165e-07, -9.048060e-10 ],
                                                 [  1.031271e-06,  7.070720e-07,  4.132664e-06, -4.264964e-09, 9.952311e-07,  1.147504e-06,  3.036135e-06, -2.642949e-09 ],
                                                 [ -3.468670e-10,  8.186300e-10, -4.264964e-09,  3.727600e-10, 3.071510e-10,  3.816056e-09,  5.460586e-09,  3.336860e-10 ],
                                                 [  1.186658e-07, -2.261425e-08,  9.952311e-07,  3.071510e-10, 2.792847e-07,  2.435102e-07,  4.742642e-07, -1.127960e-09 ],
                                                 [  1.953402e-07,  4.553737e-07,  1.147504e-06,  3.816056e-09, 2.435102e-07,  9.364803e-07,  1.744701e-07, -2.394143e-09 ],
                                                 [  8.550732e-08, -3.459165e-07,  3.036135e-06,  5.460586e-09, 4.742642e-07,  1.744701e-07,  4.887436e-06, -2.686310e-10 ],
                                                 [ -1.352565e-09, -9.048060e-10, -2.642949e-09,  3.336860e-10, -1.127960e-09, -2.394143e-09, -2.686310e-10,  3.280511e-09 ] ] ),
                    relative = False )

        reaction = ReactionID( 'n,U235->fission' )
        group1 = EnergyGroup( 1e-5, 1e+6 )
        group2 = EnergyGroup( 1e+6, 2e+7 )
        product1 = ParticleID( 'Y99' )
        product2 = ParticleID( 'Mo99' )
        product3 = ParticleID( 'Pr148' )
        product4 = ParticleID( 'Pr148_e1' )

        # extracting a covariance matrix for a single product over all groups
        submatrix = chunk.extract( reaction, None, product3 )

        # verify content
        self.assertEqual( 1, len( submatrix.row_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->fission' ), submatrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 3, len( submatrix.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, submatrix.row_metadata.energies[0] )
        self.assertAlmostEqual( 1e+6, submatrix.row_metadata.energies[1] )
        self.assertAlmostEqual( 2e+7, submatrix.row_metadata.energies[2] )
        self.assertEqual( 1, len( submatrix.row_metadata.product_identifiers ) )
        self.assertEqual( ParticleID( 'Pr148' ), submatrix.row_metadata.product_identifiers[0] )
        self.assertEqual( chunk.row_metadata, chunk.column_metadata )

        self.assertEqual( False, submatrix.is_relative_matrix )
        self.assertEqual( True, submatrix.is_absolute_matrix )
        self.assertEqual( False, submatrix.is_off_diagonal )
        self.assertEqual( True, submatrix.is_on_diagonal )

        self.assertIsNone( submatrix.standard_deviations )
        self.assertIsNone( submatrix.correlations )
        self.assertIsNone( submatrix.eigenvalues )

        self.assertAlmostEqual(  4.132664e-06, submatrix.covariances[0,0] )
        self.assertAlmostEqual(  3.036135e-06, submatrix.covariances[0,1] )
        self.assertAlmostEqual(  3.036135e-06, submatrix.covariances[1,0] )
        self.assertAlmostEqual(  4.887436e-06, submatrix.covariances[1,1] )

        # extracting a covariance matrix for a single group
        submatrix = chunk.extract( reaction, group2, None )

        # verify content
        self.assertEqual( 1, len( submatrix.row_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->fission' ), submatrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 2, len( submatrix.row_metadata.energies ) )
        self.assertAlmostEqual( 1e+6, submatrix.row_metadata.energies[0] )
        self.assertAlmostEqual( 2e+7, submatrix.row_metadata.energies[1] )
        self.assertEqual( 4, len( submatrix.row_metadata.product_identifiers ) )
        self.assertEqual( ParticleID( 'Y99' ), submatrix.row_metadata.product_identifiers[0] )
        self.assertEqual( ParticleID( 'Mo99' ), submatrix.row_metadata.product_identifiers[1] )
        self.assertEqual( ParticleID( 'Pr148' ), submatrix.row_metadata.product_identifiers[2] )
        self.assertEqual( ParticleID( 'Pr148_e1' ), submatrix.row_metadata.product_identifiers[3] )
        self.assertEqual( chunk.row_metadata, chunk.column_metadata )

        self.assertEqual( False, submatrix.is_relative_matrix )
        self.assertEqual( True, submatrix.is_absolute_matrix )
        self.assertEqual( False, submatrix.is_off_diagonal )
        self.assertEqual( True, submatrix.is_on_diagonal )

        self.assertIsNone( submatrix.standard_deviations )
        self.assertIsNone( submatrix.correlations )
        self.assertIsNone( submatrix.eigenvalues )

        self.assertAlmostEqual(  2.792847e-07, submatrix.covariances[0,0] )
        self.assertAlmostEqual(  2.435102e-07, submatrix.covariances[0,1] )
        self.assertAlmostEqual(  4.742642e-07, submatrix.covariances[0,2] )
        self.assertAlmostEqual( -1.127960e-09, submatrix.covariances[0,3] )
        self.assertAlmostEqual(  2.435102e-07, submatrix.covariances[1,0] )
        self.assertAlmostEqual(  9.364803e-07, submatrix.covariances[1,1] )
        self.assertAlmostEqual(  1.744701e-07, submatrix.covariances[1,2] )
        self.assertAlmostEqual( -2.394143e-09, submatrix.covariances[1,3] )
        self.assertAlmostEqual(  4.742642e-07, submatrix.covariances[2,0] )
        self.assertAlmostEqual(  1.744701e-07, submatrix.covariances[2,1] )
        self.assertAlmostEqual(  4.887436e-06, submatrix.covariances[2,2] )
        self.assertAlmostEqual( -2.686310e-10, submatrix.covariances[2,3] )
        self.assertAlmostEqual( -1.127960e-09, submatrix.covariances[3,0] )
        self.assertAlmostEqual( -2.394143e-09, submatrix.covariances[3,1] )
        self.assertAlmostEqual( -2.686310e-10, submatrix.covariances[3,2] )
        self.assertAlmostEqual(  3.280511e-09, submatrix.covariances[3,3] )

        # extracting a covariance matrix for an energy cross term
        submatrix = chunk.extract( reaction, group1, None,
                                   reaction, group2, None )

        # verify content
        self.assertEqual( 1, len( submatrix.row_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->fission' ), submatrix.row_metadata.reaction_identifiers[0] )
        self.assertEqual( 2, len( submatrix.row_metadata.energies ) )
        self.assertAlmostEqual( 1e-5, submatrix.row_metadata.energies[0] )
        self.assertAlmostEqual( 1e+6, submatrix.row_metadata.energies[1] )
        self.assertEqual( 4, len( submatrix.row_metadata.product_identifiers ) )
        self.assertEqual( ParticleID( 'Y99' ), submatrix.row_metadata.product_identifiers[0] )
        self.assertEqual( ParticleID( 'Mo99' ), submatrix.row_metadata.product_identifiers[1] )
        self.assertEqual( ParticleID( 'Pr148' ), submatrix.row_metadata.product_identifiers[2] )
        self.assertEqual( ParticleID( 'Pr148_e1' ), submatrix.row_metadata.product_identifiers[3] )

        self.assertEqual( 1, len( submatrix.column_metadata.reaction_identifiers ) )
        self.assertEqual( ReactionID( 'n,U235->fission' ), submatrix.column_metadata.reaction_identifiers[0] )
        self.assertEqual( 2, len( submatrix.column_metadata.energies ) )
        self.assertAlmostEqual( 1e+6, submatrix.column_metadata.energies[0] )
        self.assertAlmostEqual( 2e+7, submatrix.column_metadata.energies[1] )
        self.assertEqual( 4, len( submatrix.column_metadata.product_identifiers ) )
        self.assertEqual( ParticleID( 'Y99' ), submatrix.column_metadata.product_identifiers[0] )
        self.assertEqual( ParticleID( 'Mo99' ), submatrix.column_metadata.product_identifiers[1] )
        self.assertEqual( ParticleID( 'Pr148' ), submatrix.column_metadata.product_identifiers[2] )
        self.assertEqual( ParticleID( 'Pr148_e1' ), submatrix.column_metadata.product_identifiers[3] )

        self.assertEqual( False, submatrix.is_relative_matrix )
        self.assertEqual( True, submatrix.is_absolute_matrix )
        self.assertEqual( True, submatrix.is_off_diagonal )
        self.assertEqual( False, submatrix.is_on_diagonal )

        self.assertIsNone( submatrix.standard_deviations )
        self.assertIsNone( submatrix.correlations )
        self.assertIsNone( submatrix.eigenvalues )

        self.assertAlmostEqual(  1.186658e-07, submatrix.covariances[0,0] )
        self.assertAlmostEqual(  1.953402e-07, submatrix.covariances[0,1] )
        self.assertAlmostEqual(  8.550732e-08, submatrix.covariances[0,2] )
        self.assertAlmostEqual( -1.352565e-09, submatrix.covariances[0,3] )
        self.assertAlmostEqual( -2.261425e-08, submatrix.covariances[1,0] )
        self.assertAlmostEqual(  4.553737e-07, submatrix.covariances[1,1] )
        self.assertAlmostEqual( -3.459165e-07, submatrix.covariances[1,2] )
        self.assertAlmostEqual( -9.048060e-10, submatrix.covariances[1,3] )
        self.assertAlmostEqual(  9.952311e-07, submatrix.covariances[2,0] )
        self.assertAlmostEqual(  1.147504e-06, submatrix.covariances[2,1] )
        self.assertAlmostEqual(  3.036135e-06, submatrix.covariances[2,2] )
        self.assertAlmostEqual( -2.642949e-09, submatrix.covariances[2,3] )
        self.assertAlmostEqual(  3.071510e-10, submatrix.covariances[3,0] )
        self.assertAlmostEqual(  3.816056e-09, submatrix.covariances[3,1] )
        self.assertAlmostEqual(  5.460586e-09, submatrix.covariances[3,2] )
        self.assertAlmostEqual(  3.336860e-10, submatrix.covariances[3,3] )

if __name__ == '__main__' :

    unittest.main()
