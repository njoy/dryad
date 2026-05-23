// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix.hpp"

// other includes

// convenience typedefs
using namespace njoy::matrix;
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "ProductMultiplicityCovarianceMatrix" ) {

  GIVEN( "valid covariance data for product multiplicities" ) {

    // matrix and test results provided by Amanda Lewis
    // eigenvectors from numpy

    ProductMultiplicityMetadata metadata( { id::ReactionID( "n,U235->fission" ) },
                                          { 1e-5, 1e+6, 2e+7 },
                                          { id::ParticleID( "Y99" ), id::ParticleID( "Mo99" ),
                                            id::ParticleID( "Pr148" ), id::ParticleID( "Pr148_e1" ) } );

    Matrix< double > matrix( 8, 8 );
    matrix <<   3.350497e-07,  3.086034e-07,  1.031271e-06, -3.468670e-10, 1.186658e-07,  1.953402e-07,  8.550732e-08, -1.352565e-09,
                3.086034e-07,  1.390798e-06,  7.070720e-07,  8.186300e-10, -2.261425e-08,  4.553737e-07, -3.459165e-07, -9.048060e-10,
                1.031271e-06,  7.070720e-07,  4.132664e-06, -4.264964e-09, 9.952311e-07,  1.147504e-06,  3.036135e-06, -2.642949e-09,
               -3.468670e-10,  8.186300e-10, -4.264964e-09,  3.727600e-10, 3.071510e-10,  3.816056e-09,  5.460586e-09,  3.336860e-10,
                1.186658e-07, -2.261425e-08,  9.952311e-07,  3.071510e-10, 2.792847e-07,  2.435102e-07,  4.742642e-07, -1.127960e-09,
                1.953402e-07,  4.553737e-07,  1.147504e-06,  3.816056e-09, 2.435102e-07,  9.364803e-07,  1.744701e-07, -2.394143e-09,
                8.550732e-08, -3.459165e-07,  3.036135e-06,  5.460586e-09, 4.742642e-07,  1.744701e-07,  4.887436e-06, -2.686310e-10,
               -1.352565e-09, -9.048060e-10, -2.642949e-09,  3.336860e-10, -1.127960e-09, -2.394143e-09, -2.686310e-10,  3.280511e-09;

    ProductMultiplicityCovarianceMatrix chunk( std::move( metadata ),
                                               std::move( matrix ),
                                               false );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->fission" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 3 == chunk.rowMetadata().energies().size() );
      CHECK( 1e-5 == chunk.rowMetadata().energies()[0] );
      CHECK( 1e+6 == chunk.rowMetadata().energies()[1] );
      CHECK( 2e+7 == chunk.rowMetadata().energies()[2] );
      CHECK( 4 == chunk.rowMetadata().productIdentifiers().size() );
      CHECK( id::ParticleID( "Y99" ) == chunk.rowMetadata().productIdentifiers()[0] );
      CHECK( id::ParticleID( "Mo99" ) == chunk.rowMetadata().productIdentifiers()[1] );
      CHECK( id::ParticleID( "Pr148" ) == chunk.rowMetadata().productIdentifiers()[2] );
      CHECK( id::ParticleID( "Pr148_e1" ) == chunk.rowMetadata().productIdentifiers()[3] );
      CHECK( chunk.rowMetadata() == chunk.columnMetadata() );

      CHECK( false == chunk.isRelativeMatrix() );
      CHECK( true == chunk.isAbsoluteMatrix() );
      CHECK( true == chunk.isOnDiagonal() );
      CHECK( false == chunk.isOffDiagonal() );

      CHECK( std::nullopt != chunk.standardDeviations() );
      CHECK( std::nullopt != chunk.correlations() );
      CHECK( std::nullopt != chunk.eigenvalues() );
      CHECK( std::nullopt != chunk.eigenvectors() );
      CHECK( std::nullopt != std::get< 0 >( chunk.eigendata() ) );
      CHECK( std::nullopt != std::get< 1 >( chunk.eigendata() ) );

      CHECK_THAT(  3.350497e-07, WithinRel( chunk.covariances()(0,0) ) );
      CHECK_THAT(  3.086034e-07, WithinRel( chunk.covariances()(0,1) ) );
      CHECK_THAT(  1.031271e-06, WithinRel( chunk.covariances()(0,2) ) );
      CHECK_THAT( -3.468670e-10, WithinRel( chunk.covariances()(0,3) ) );
      CHECK_THAT(  1.186658e-07, WithinRel( chunk.covariances()(0,4) ) );
      CHECK_THAT(  1.953402e-07, WithinRel( chunk.covariances()(0,5) ) );
      CHECK_THAT(  8.550732e-08, WithinRel( chunk.covariances()(0,6) ) );
      CHECK_THAT( -1.352565e-09, WithinRel( chunk.covariances()(0,7) ) );
      CHECK_THAT(  3.086034e-07, WithinRel( chunk.covariances()(1,0) ) );
      CHECK_THAT(  1.390798e-06, WithinRel( chunk.covariances()(1,1) ) );
      CHECK_THAT(  7.070720e-07, WithinRel( chunk.covariances()(1,2) ) );
      CHECK_THAT(  8.186300e-10, WithinRel( chunk.covariances()(1,3) ) );
      CHECK_THAT( -2.261425e-08, WithinRel( chunk.covariances()(1,4) ) );
      CHECK_THAT(  4.553737e-07, WithinRel( chunk.covariances()(1,5) ) );
      CHECK_THAT( -3.459165e-07, WithinRel( chunk.covariances()(1,6) ) );
      CHECK_THAT( -9.048060e-10, WithinRel( chunk.covariances()(1,7) ) );
      CHECK_THAT(  1.031271e-06, WithinRel( chunk.covariances()(2,0) ) );
      CHECK_THAT(  7.070720e-07, WithinRel( chunk.covariances()(2,1) ) );
      CHECK_THAT(  4.132664e-06, WithinRel( chunk.covariances()(2,2) ) );
      CHECK_THAT( -4.264964e-09, WithinRel( chunk.covariances()(2,3) ) );
      CHECK_THAT(  9.952311e-07, WithinRel( chunk.covariances()(2,4) ) );
      CHECK_THAT(  1.147504e-06, WithinRel( chunk.covariances()(2,5) ) );
      CHECK_THAT(  3.036135e-06, WithinRel( chunk.covariances()(2,6) ) );
      CHECK_THAT( -2.642949e-09, WithinRel( chunk.covariances()(2,7) ) );
      CHECK_THAT( -3.468670e-10, WithinRel( chunk.covariances()(3,0) ) );
      CHECK_THAT(  8.186300e-10, WithinRel( chunk.covariances()(3,1) ) );
      CHECK_THAT( -4.264964e-09, WithinRel( chunk.covariances()(3,2) ) );
      CHECK_THAT(  3.727600e-10, WithinRel( chunk.covariances()(3,3) ) );
      CHECK_THAT(  3.071510e-10, WithinRel( chunk.covariances()(3,4) ) );
      CHECK_THAT(  3.816056e-09, WithinRel( chunk.covariances()(3,5) ) );
      CHECK_THAT(  5.460586e-09, WithinRel( chunk.covariances()(3,6) ) );
      CHECK_THAT(  3.336860e-10, WithinRel( chunk.covariances()(3,7) ) );
      CHECK_THAT(  1.186658e-07, WithinRel( chunk.covariances()(4,0) ) );
      CHECK_THAT( -2.261425e-08, WithinRel( chunk.covariances()(4,1) ) );
      CHECK_THAT(  9.952311e-07, WithinRel( chunk.covariances()(4,2) ) );
      CHECK_THAT(  3.071510e-10, WithinRel( chunk.covariances()(4,3) ) );
      CHECK_THAT(  2.792847e-07, WithinRel( chunk.covariances()(4,4) ) );
      CHECK_THAT(  2.435102e-07, WithinRel( chunk.covariances()(4,5) ) );
      CHECK_THAT(  4.742642e-07, WithinRel( chunk.covariances()(4,6) ) );
      CHECK_THAT( -1.127960e-09, WithinRel( chunk.covariances()(4,7) ) );
      CHECK_THAT(  1.953402e-07, WithinRel( chunk.covariances()(5,0) ) );
      CHECK_THAT(  4.553737e-07, WithinRel( chunk.covariances()(5,1) ) );
      CHECK_THAT(  1.147504e-06, WithinRel( chunk.covariances()(5,2) ) );
      CHECK_THAT(  3.816056e-09, WithinRel( chunk.covariances()(5,3) ) );
      CHECK_THAT(  2.435102e-07, WithinRel( chunk.covariances()(5,4) ) );
      CHECK_THAT(  9.364803e-07, WithinRel( chunk.covariances()(5,5) ) );
      CHECK_THAT(  1.744701e-07, WithinRel( chunk.covariances()(5,6) ) );
      CHECK_THAT( -2.394143e-09, WithinRel( chunk.covariances()(5,7) ) );
      CHECK_THAT(  8.550732e-08, WithinRel( chunk.covariances()(6,0) ) );
      CHECK_THAT( -3.459165e-07, WithinRel( chunk.covariances()(6,1) ) );
      CHECK_THAT(  3.036135e-06, WithinRel( chunk.covariances()(6,2) ) );
      CHECK_THAT(  5.460586e-09, WithinRel( chunk.covariances()(6,3) ) );
      CHECK_THAT(  4.742642e-07, WithinRel( chunk.covariances()(6,4) ) );
      CHECK_THAT(  1.744701e-07, WithinRel( chunk.covariances()(6,5) ) );
      CHECK_THAT(  4.887436e-06, WithinRel( chunk.covariances()(6,6) ) );
      CHECK_THAT( -2.686310e-10, WithinRel( chunk.covariances()(6,7) ) );
      CHECK_THAT( -1.352565e-09, WithinRel( chunk.covariances()(7,0) ) );
      CHECK_THAT( -9.048060e-10, WithinRel( chunk.covariances()(7,1) ) );
      CHECK_THAT( -2.642949e-09, WithinRel( chunk.covariances()(7,2) ) );
      CHECK_THAT(  3.336860e-10, WithinRel( chunk.covariances()(7,3) ) );
      CHECK_THAT( -1.127960e-09, WithinRel( chunk.covariances()(7,4) ) );
      CHECK_THAT( -2.394143e-09, WithinRel( chunk.covariances()(7,5) ) );
      CHECK_THAT( -2.686310e-10, WithinRel( chunk.covariances()(7,6) ) );
      CHECK_THAT(  3.280511e-09, WithinRel( chunk.covariances()(7,7) ) );

      CHECK( 8 == chunk.standardDeviations().value().size() );
      CHECK_THAT( 5.78834777807968e-04, WithinRel( chunk.standardDeviations().value()[0] ) );
      CHECK_THAT( 1.17932099107919e-03, WithinRel( chunk.standardDeviations().value()[1] ) );
      CHECK_THAT( 2.03289547198079e-03, WithinRel( chunk.standardDeviations().value()[2] ) );
      CHECK_THAT( 1.93069935515605e-05, WithinRel( chunk.standardDeviations().value()[3] ) );
      CHECK_THAT( 5.28473935024236e-04, WithinRel( chunk.standardDeviations().value()[4] ) );
      CHECK_THAT( 9.67719122473045e-04, WithinRel( chunk.standardDeviations().value()[5] ) );
      CHECK_THAT( 2.21075462229529e-03, WithinRel( chunk.standardDeviations().value()[6] ) );
      CHECK_THAT( 5.72757453028767e-05, WithinRel( chunk.standardDeviations().value()[7] ) );

      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(0,0) ) );
      CHECK_THAT(  4.52078716301036e-01, WithinRel( chunk.correlations().value()(0,1) ) );
      CHECK_THAT(  8.76401556189488e-01, WithinRel( chunk.correlations().value()(0,2) ) );
      CHECK_THAT( -3.10379990825034e-02, WithinRel( chunk.correlations().value()(0,3) ) );
      CHECK_THAT(  3.87924654926139e-01, WithinRel( chunk.correlations().value()(0,4) ) );
      CHECK_THAT(  3.48728698045195e-01, WithinRel( chunk.correlations().value()(0,5) ) );
      CHECK_THAT(  6.68202561925324e-02, WithinRel( chunk.correlations().value()(0,6) ) );
      CHECK_THAT( -4.07974274908842e-02, WithinRel( chunk.correlations().value()(0,7) ) );
      CHECK_THAT(  4.52078716301036e-01, WithinRel( chunk.correlations().value()(1,0) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(1,1) ) );
      CHECK_THAT(  2.94928377943159e-01, WithinRel( chunk.correlations().value()(1,2) ) );
      CHECK_THAT(  3.59534835487576e-02, WithinRel( chunk.correlations().value()(1,3) ) );
      CHECK_THAT( -3.62849549313329e-02, WithinRel( chunk.correlations().value()(1,4) ) );
      CHECK_THAT(  3.99012584110026e-01, WithinRel( chunk.correlations().value()(1,5) ) );
      CHECK_THAT( -1.32677936246521e-01, WithinRel( chunk.correlations().value()(1,6) ) );
      CHECK_THAT( -1.33953076941197e-02, WithinRel( chunk.correlations().value()(1,7) ) );
      CHECK_THAT(  8.76401556189488e-01, WithinRel( chunk.correlations().value()(2,0) ) );
      CHECK_THAT(  2.94928377943159e-01, WithinRel( chunk.correlations().value()(2,1) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(2,2) ) );
      CHECK_THAT( -1.08663995484036e-01, WithinRel( chunk.correlations().value()(2,3) ) );
      CHECK_THAT(  9.26371782910094e-01, WithinRel( chunk.correlations().value()(2,4) ) );
      CHECK_THAT(  5.83297126018077e-01, WithinRel( chunk.correlations().value()(2,5) ) );
      CHECK_THAT(  6.75562428243337e-01, WithinRel( chunk.correlations().value()(2,6) ) );
      CHECK_THAT( -2.26988045368907e-02, WithinRel( chunk.correlations().value()(2,7) ) );
      CHECK_THAT( -3.10379990825034e-02, WithinRel( chunk.correlations().value()(3,0) ) );
      CHECK_THAT(  3.59534835487576e-02, WithinRel( chunk.correlations().value()(3,1) ) );
      CHECK_THAT( -1.08663995484036e-01, WithinRel( chunk.correlations().value()(3,2) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(3,3) ) );
      CHECK_THAT(  3.01032724933124e-02, WithinRel( chunk.correlations().value()(3,4) ) );
      CHECK_THAT(  2.04244685455433e-01, WithinRel( chunk.correlations().value()(3,5) ) );
      CHECK_THAT(  1.27933434186385e-01, WithinRel( chunk.correlations().value()(3,6) ) );
      CHECK_THAT(  3.01753686987760e-01, WithinRel( chunk.correlations().value()(3,7) ) );
      CHECK_THAT(  3.87924654926139e-01, WithinRel( chunk.correlations().value()(4,0) ) );
      CHECK_THAT( -3.62849549313329e-02, WithinRel( chunk.correlations().value()(4,1) ) );
      CHECK_THAT(  9.26371782910094e-01, WithinRel( chunk.correlations().value()(4,2) ) );
      CHECK_THAT(  3.01032724933124e-02, WithinRel( chunk.correlations().value()(4,3) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(4,4) ) );
      CHECK_THAT(  4.76150519164124e-01, WithinRel( chunk.correlations().value()(4,5) ) );
      CHECK_THAT(  4.05934748518847e-01, WithinRel( chunk.correlations().value()(4,6) ) );
      CHECK_THAT( -3.72648500015370e-02, WithinRel( chunk.correlations().value()(4,7) ) );
      CHECK_THAT(  3.48728698045195e-01, WithinRel( chunk.correlations().value()(5,0) ) );
      CHECK_THAT(  3.99012584110026e-01, WithinRel( chunk.correlations().value()(5,1) ) );
      CHECK_THAT(  5.83297126018077e-01, WithinRel( chunk.correlations().value()(5,2) ) );
      CHECK_THAT(  2.04244685455433e-01, WithinRel( chunk.correlations().value()(5,3) ) );
      CHECK_THAT(  4.76150519164124e-01, WithinRel( chunk.correlations().value()(5,4) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(5,5) ) );
      CHECK_THAT(  8.15513482313117e-02, WithinRel( chunk.correlations().value()(5,6) ) );
      CHECK_THAT( -4.31946555113209e-02, WithinRel( chunk.correlations().value()(5,7) ) );
      CHECK_THAT(  6.68202561925324e-02, WithinRel( chunk.correlations().value()(6,0) ) );
      CHECK_THAT( -1.32677936246521e-01, WithinRel( chunk.correlations().value()(6,1) ) );
      CHECK_THAT(  6.75562428243337e-01, WithinRel( chunk.correlations().value()(6,2) ) );
      CHECK_THAT(  1.27933434186385e-01, WithinRel( chunk.correlations().value()(6,3) ) );
      CHECK_THAT(  4.05934748518847e-01, WithinRel( chunk.correlations().value()(6,4) ) );
      CHECK_THAT(  8.15513482313117e-02, WithinRel( chunk.correlations().value()(6,5) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(6,6) ) );
      CHECK_THAT( -2.12150880161591e-03, WithinRel( chunk.correlations().value()(6,7) ) );
      CHECK_THAT( -4.07974274908842e-02, WithinRel( chunk.correlations().value()(7,0) ) );
      CHECK_THAT( -1.33953076941197e-02, WithinRel( chunk.correlations().value()(7,1) ) );
      CHECK_THAT( -2.26988045368907e-02, WithinRel( chunk.correlations().value()(7,2) ) );
      CHECK_THAT(  3.01753686987760e-01, WithinRel( chunk.correlations().value()(7,3) ) );
      CHECK_THAT( -3.72648500015370e-02, WithinRel( chunk.correlations().value()(7,4) ) );
      CHECK_THAT( -4.31946555113209e-02, WithinRel( chunk.correlations().value()(7,5) ) );
      CHECK_THAT( -2.12150880161591e-03, WithinRel( chunk.correlations().value()(7,6) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(7,7) ) );

      CHECK( 8 == chunk.eigenvalues().value().size() );
      CHECK_THAT(  7.93360907096512e-06, WithinRel( chunk.eigenvalues().value()[0] ) );
      CHECK_THAT(  2.77607998044769e-06, WithinRel( chunk.eigenvalues().value()[1] ) );
      CHECK_THAT(  8.72998692347036e-07, WithinRel( chunk.eigenvalues().value()[2] ) );
      CHECK_THAT(  5.09348096171567e-07, WithinRel( chunk.eigenvalues().value()[3] ) );
      CHECK_THAT(  1.08751047007600e-07, WithinRel( chunk.eigenvalues().value()[4] ) );
      CHECK_THAT(  3.31256655183549e-09, WithinRel( chunk.eigenvalues().value()[5] ) );
      // some CI machines have differences in the last 4 digits of the next eigenvalue
      CHECK_THAT(  3.43367202411662e-10, WithinRel( chunk.eigenvalues().value()[6], 1e-11 ) );
      CHECK_THAT( -2.39076849693257e-07, WithinRel( chunk.eigenvalues().value()[7] ) );

      // eigenvector result provided by numpy
      CHECK( 8 == chunk.eigenvectors().value().size() );
      CHECK_THAT(  1.074034990154796e-01, WithinRel( chunk.eigenvectors().value()[0](0), 1e-12 ) );
      CHECK_THAT(  5.031741433412550e-02, WithinRel( chunk.eigenvectors().value()[0](1), 1e-12 ) );
      CHECK_THAT(  6.760345784347225e-01, WithinRel( chunk.eigenvectors().value()[0](2), 1e-12 ) );
      CHECK_THAT(  1.915401875474548e-04, WithinRel( chunk.eigenvectors().value()[0](3), 1e-12 ) );
      CHECK_THAT(  1.372508574710749e-01, WithinRel( chunk.eigenvectors().value()[0](4), 1e-12 ) );
      CHECK_THAT(  1.393826996793074e-01, WithinRel( chunk.eigenvectors().value()[0](5), 1e-12 ) );
      CHECK_THAT(  7.004601426407556e-01, WithinRel( chunk.eigenvectors().value()[0](6), 1e-12 ) );
      CHECK_THAT( -3.346821750524192e-04, WithinRel( chunk.eigenvectors().value()[0](7), 1e-12 ) );
      CHECK_THAT( -2.571527009424175e-01, WithinRel( chunk.eigenvectors().value()[1](0), 1e-12 ) );
      CHECK_THAT( -5.332339693289101e-01, WithinRel( chunk.eigenvectors().value()[1](1), 1e-12 ) );
      CHECK_THAT( -4.136479111214138e-01, WithinRel( chunk.eigenvectors().value()[1](2), 1e-12 ) );
      CHECK_THAT(  1.106338368001530e-03, WithinRel( chunk.eigenvectors().value()[1](3), 1e-12 ) );
      CHECK_THAT( -1.004221706751696e-01, WithinRel( chunk.eigenvectors().value()[1](4), 1e-12 ) );
      CHECK_THAT( -3.764142026504751e-01, WithinRel( chunk.eigenvectors().value()[1](5), 1e-12 ) );
      CHECK_THAT(  5.715373399614007e-01, WithinRel( chunk.eigenvectors().value()[1](6), 1e-12 ) );
      CHECK_THAT(  1.004341476548398e-03, WithinRel( chunk.eigenvectors().value()[1](7), 1e-12 ) );
      CHECK_THAT(  1.371275274983361e-01, WithinRel( chunk.eigenvectors().value()[2](0), 1e-12 ) );
      CHECK_THAT( -8.140382248203513e-01, WithinRel( chunk.eigenvectors().value()[2](1), 1e-12 ) );
      CHECK_THAT(  2.691481835902044e-01, WithinRel( chunk.eigenvectors().value()[2](2), 1e-12 ) );
      CHECK_THAT( -3.231353088691460e-03, WithinRel( chunk.eigenvectors().value()[2](3), 1e-12 ) );
      CHECK_THAT(  3.273381875688864e-01, WithinRel( chunk.eigenvectors().value()[2](4), 1e-12 ) );
      CHECK_THAT(  1.854210583626488e-01, WithinRel( chunk.eigenvectors().value()[2](5), 1e-12 ) );
      CHECK_THAT( -3.233486103311739e-01, WithinRel( chunk.eigenvectors().value()[2](6), 1e-12 ) );
      CHECK_THAT( -1.020603999800658e-03, WithinRel( chunk.eigenvectors().value()[2](7), 1e-12 ) );
      CHECK_THAT( -4.574278897433420e-01, WithinRel( chunk.eigenvectors().value()[3](0), 1e-12 ) );
      CHECK_THAT( -3.768700535852441e-02, WithinRel( chunk.eigenvectors().value()[3](1), 1e-12 ) );
      CHECK_THAT( -2.313850741112828e-01, WithinRel( chunk.eigenvectors().value()[3](2), 1e-12 ) );
      CHECK_THAT(  9.976800706566397e-03, WithinRel( chunk.eigenvectors().value()[3](3), 1e-12 ) );
      CHECK_THAT( -5.343662614796370e-02, WithinRel( chunk.eigenvectors().value()[3](4), 1e-12 ) );
      CHECK_THAT(  8.447798233267908e-01, WithinRel( chunk.eigenvectors().value()[3](5), 1e-12 ) );
      CHECK_THAT(  1.385291026888882e-01, WithinRel( chunk.eigenvectors().value()[3](6), 1e-12 ) );
      CHECK_THAT( -1.446040223355744e-03, WithinRel( chunk.eigenvectors().value()[3](7), 1e-12 ) );
      CHECK_THAT( -5.439389015604769e-01, WithinRel( chunk.eigenvectors().value()[4](0), 1e-12 ) );
      CHECK_THAT(  1.996774457251580e-01, WithinRel( chunk.eigenvectors().value()[4](1), 1e-12 ) );
      CHECK_THAT(  1.639440644799666e-02, WithinRel( chunk.eigenvectors().value()[4](2), 1e-12 ) );
      CHECK_THAT( -5.814555639788057e-03, WithinRel( chunk.eigenvectors().value()[4](3), 1e-12 ) );
      CHECK_THAT(  7.818950572395391e-01, WithinRel( chunk.eigenvectors().value()[4](4), 1e-12 ) );
      CHECK_THAT( -2.224672713971068e-01, WithinRel( chunk.eigenvectors().value()[4](5), 1e-12 ) );
      CHECK_THAT( -5.569982161307497e-02, WithinRel( chunk.eigenvectors().value()[4](6), 1e-12 ) );
      CHECK_THAT(  1.663102992474408e-03, WithinRel( chunk.eigenvectors().value()[4](7), 1e-12 ) );
      CHECK_THAT( -1.752926246655574e-04, WithinRel( chunk.eigenvectors().value()[5](0), 1e-12 ) );
      CHECK_THAT(  8.279317505192949e-04, WithinRel( chunk.eigenvectors().value()[5](1), 1e-12 ) );
      CHECK_THAT( -1.518618778550783e-03, WithinRel( chunk.eigenvectors().value()[5](2), 1e-12 ) );
      CHECK_THAT( -1.096637382643716e-01, WithinRel( chunk.eigenvectors().value()[5](3), 1e-12 ) );
      CHECK_THAT(  7.862304135582416e-04, WithinRel( chunk.eigenvectors().value()[5](4), 1e-12 ) );
      CHECK_THAT( -9.998834737042516e-04, WithinRel( chunk.eigenvectors().value()[5](5), 1e-12 ) );
      CHECK_THAT(  1.033041611015811e-03, WithinRel( chunk.eigenvectors().value()[5](6), 1e-12 ) );
      CHECK_THAT( -9.939658731607474e-01, WithinRel( chunk.eigenvectors().value()[5](7), 1e-12 ) );
      CHECK_THAT(  1.322444642228740e-02, WithinRel( chunk.eigenvectors().value()[6](0), 1e-12 ) );
      CHECK_THAT(  1.263506076818510e-03, WithinRel( chunk.eigenvectors().value()[6](1), 1e-12 ) );
      CHECK_THAT( -5.277719337954416e-03, WithinRel( chunk.eigenvectors().value()[6](2), 1e-12 ) );
      CHECK_THAT(  9.937414417323501e-01, WithinRel( chunk.eigenvectors().value()[6](3), 1e-12 ) );
      CHECK_THAT(  1.515135480819192e-02, WithinRel( chunk.eigenvectors().value()[6](4), 1e-12 ) );
      CHECK_THAT( -5.315067279801203e-03, WithinRel( chunk.eigenvectors().value()[6](5), 1e-12 ) );
      CHECK_THAT(  7.398811740866554e-04, WithinRel( chunk.eigenvectors().value()[6](6), 1e-12 ) );
      CHECK_THAT( -1.096140926827119e-01, WithinRel( chunk.eigenvectors().value()[6](7), 1e-12 ) );
      CHECK_THAT(  6.310691708068932e-01, WithinRel( chunk.eigenvectors().value()[7](0), 1e-12 ) );
      CHECK_THAT(  9.580076031528753e-02, WithinRel( chunk.eigenvectors().value()[7](1), 1e-12 ) );
      CHECK_THAT( -4.955743335231361e-01, WithinRel( chunk.eigenvectors().value()[7](2), 1e-12 ) );
      CHECK_THAT( -1.751466725221130e-02, WithinRel( chunk.eigenvectors().value()[7](3), 1e-12 ) );
      CHECK_THAT(  4.994814966132097e-01, WithinRel( chunk.eigenvectors().value()[7](4), 1e-12 ) );
      CHECK_THAT(  2.032977022465391e-01, WithinRel( chunk.eigenvectors().value()[7](5), 1e-12 ) );
      CHECK_THAT(  2.363301436122759e-01, WithinRel( chunk.eigenvectors().value()[7](6), 1e-12 ) );
      CHECK_THAT(  3.094250598081331e-03, WithinRel( chunk.eigenvectors().value()[7](7), 1e-12 ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid correlation data for product multiplicities" ) {

    // matrix and test results provided by Amanda Lewis
    // eigenvectors from numpy

    ProductMultiplicityMetadata metadata( { id::ReactionID( "n,U235->fission" ) },
                                          { 1e-5, 1e+6, 2e+7 },
                                          { id::ParticleID( "Y99" ), id::ParticleID( "Mo99" ),
                                            id::ParticleID( "Pr148" ), id::ParticleID( "Pr148_e1" ) } );

    std::vector< double > deviations = {  5.78834777807968e-04, 1.17932099107919e-03,
                                          2.03289547198079e-03, 1.93069935515605e-05,
                                          5.28473935024236e-04, 9.67719122473045e-04,
                                          2.21075462229529e-03, 5.72757453028767e-05 };
    Matrix< double > matrix( 8, 8 );
    matrix <<  1.00000000000000e+00,  4.52078716301036e-01,  8.76401556189488e-01, -3.10379990825034e-02,
               3.87924654926139e-01,  3.48728698045195e-01,  6.68202561925324e-02, -4.07974274908842e-02,
               4.52078716301036e-01,  1.00000000000000e+00,  2.94928377943159e-01,  3.59534835487576e-02,
              -3.62849549313329e-02,  3.99012584110026e-01, -1.32677936246521e-01, -1.33953076941197e-02,
               8.76401556189488e-01,  2.94928377943159e-01,  1.00000000000000e+00, -1.08663995484036e-01,
               9.26371782910094e-01,  5.83297126018077e-01,  6.75562428243337e-01, -2.26988045368907e-02,
              -3.10379990825034e-02,  3.59534835487576e-02, -1.08663995484036e-01,  1.00000000000000e+00,
               3.01032724933124e-02,  2.04244685455433e-01,  1.27933434186385e-01,  3.01753686987760e-01,
               3.87924654926139e-01, -3.62849549313329e-02,  9.26371782910094e-01,  3.01032724933124e-02,
               1.00000000000000e+00,  4.76150519164124e-01,  4.05934748518847e-01, -3.72648500015370e-02,
               3.48728698045195e-01,  3.99012584110026e-01,  5.83297126018077e-01,  2.04244685455433e-01,
               4.76150519164124e-01,  1.00000000000000e+00,  8.15513482313117e-02, -4.31946555113209e-02,
               6.68202561925324e-02, -1.32677936246521e-01,  6.75562428243337e-01,  1.27933434186385e-01,
               4.05934748518847e-01,  8.15513482313117e-02,  1.00000000000000e+00, -2.12150880161591e-03,
              -4.07974274908842e-02, -1.33953076941197e-02, -2.26988045368907e-02,  3.01753686987760e-01,
              -3.72648500015370e-02, -4.31946555113209e-02, -2.12150880161591e-03,  1.00000000000000e+00;

    ProductMultiplicityCovarianceMatrix chunk( std::move( metadata ), std::move( deviations ),
                                               std::move( matrix ), false );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      // test variables
      id::EnergyGroup group1( 1e-5, 1e+6 );
      id::EnergyGroup group2( 1e+6, 2e+7 );
      id::ParticleID product1( "Y99" );
      id::ParticleID product2( "Mo99" );
      id::ParticleID product3( "Pr148" );
      id::ParticleID product4( "Pr148_e1" );

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->fission" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 3 == chunk.rowMetadata().energies().size() );
      CHECK( 1e-5 == chunk.rowMetadata().energies()[0] );
      CHECK( 1e+6 == chunk.rowMetadata().energies()[1] );
      CHECK( 2e+7 == chunk.rowMetadata().energies()[2] );
      CHECK( 4 == chunk.rowMetadata().productIdentifiers().size() );
      CHECK( id::ParticleID( "Y99" ) == chunk.rowMetadata().productIdentifiers()[0] );
      CHECK( id::ParticleID( "Mo99" ) == chunk.rowMetadata().productIdentifiers()[1] );
      CHECK( id::ParticleID( "Pr148" ) == chunk.rowMetadata().productIdentifiers()[2] );
      CHECK( id::ParticleID( "Pr148_e1" ) == chunk.rowMetadata().productIdentifiers()[3] );
      CHECK( chunk.rowMetadata() == chunk.columnMetadata() );

      CHECK( false == chunk.isRelativeMatrix() );
      CHECK( true == chunk.isAbsoluteMatrix() );
      CHECK( true == chunk.isOnDiagonal() );
      CHECK( false == chunk.isOffDiagonal() );

      CHECK( std::nullopt != chunk.standardDeviations() );
      CHECK( std::nullopt != chunk.correlations() );
      CHECK( std::nullopt != chunk.eigenvalues() );
      CHECK( std::nullopt != chunk.eigenvectors() );
      CHECK( std::nullopt != std::get< 0 >( chunk.eigendata() ) );
      CHECK( std::nullopt != std::get< 1 >( chunk.eigendata() ) );

      CHECK( 8 == chunk.covariances().rows() );
      CHECK( 8 == chunk.covariances().cols() );
      CHECK_THAT(  3.350497e-07, WithinRel( chunk.covariances()(0,0) ) );
      CHECK_THAT(  3.086034e-07, WithinRel( chunk.covariances()(0,1) ) );
      CHECK_THAT(  1.031271e-06, WithinRel( chunk.covariances()(0,2) ) );
      CHECK_THAT( -3.468670e-10, WithinRel( chunk.covariances()(0,3) ) );
      CHECK_THAT(  1.186658e-07, WithinRel( chunk.covariances()(0,4) ) );
      CHECK_THAT(  1.953402e-07, WithinRel( chunk.covariances()(0,5) ) );
      CHECK_THAT(  8.550732e-08, WithinRel( chunk.covariances()(0,6) ) );
      CHECK_THAT( -1.352565e-09, WithinRel( chunk.covariances()(0,7) ) );
      CHECK_THAT(  3.086034e-07, WithinRel( chunk.covariances()(1,0) ) );
      CHECK_THAT(  1.390798e-06, WithinRel( chunk.covariances()(1,1) ) );
      CHECK_THAT(  7.070720e-07, WithinRel( chunk.covariances()(1,2) ) );
      CHECK_THAT(  8.186300e-10, WithinRel( chunk.covariances()(1,3) ) );
      CHECK_THAT( -2.261425e-08, WithinRel( chunk.covariances()(1,4) ) );
      CHECK_THAT(  4.553737e-07, WithinRel( chunk.covariances()(1,5) ) );
      CHECK_THAT( -3.459165e-07, WithinRel( chunk.covariances()(1,6) ) );
      CHECK_THAT( -9.048060e-10, WithinRel( chunk.covariances()(1,7) ) );
      CHECK_THAT(  1.031271e-06, WithinRel( chunk.covariances()(2,0) ) );
      CHECK_THAT(  7.070720e-07, WithinRel( chunk.covariances()(2,1) ) );
      CHECK_THAT(  4.132664e-06, WithinRel( chunk.covariances()(2,2) ) );
      CHECK_THAT( -4.264964e-09, WithinRel( chunk.covariances()(2,3) ) );
      CHECK_THAT(  9.952311e-07, WithinRel( chunk.covariances()(2,4) ) );
      CHECK_THAT(  1.147504e-06, WithinRel( chunk.covariances()(2,5) ) );
      CHECK_THAT(  3.036135e-06, WithinRel( chunk.covariances()(2,6) ) );
      CHECK_THAT( -2.642949e-09, WithinRel( chunk.covariances()(2,7) ) );
      CHECK_THAT( -3.468670e-10, WithinRel( chunk.covariances()(3,0) ) );
      CHECK_THAT(  8.186300e-10, WithinRel( chunk.covariances()(3,1) ) );
      CHECK_THAT( -4.264964e-09, WithinRel( chunk.covariances()(3,2) ) );
      CHECK_THAT(  3.727600e-10, WithinRel( chunk.covariances()(3,3) ) );
      CHECK_THAT(  3.071510e-10, WithinRel( chunk.covariances()(3,4) ) );
      CHECK_THAT(  3.816056e-09, WithinRel( chunk.covariances()(3,5) ) );
      CHECK_THAT(  5.460586e-09, WithinRel( chunk.covariances()(3,6) ) );
      CHECK_THAT(  3.336860e-10, WithinRel( chunk.covariances()(3,7) ) );
      CHECK_THAT(  1.186658e-07, WithinRel( chunk.covariances()(4,0) ) );
      CHECK_THAT( -2.261425e-08, WithinRel( chunk.covariances()(4,1) ) );
      CHECK_THAT(  9.952311e-07, WithinRel( chunk.covariances()(4,2) ) );
      CHECK_THAT(  3.071510e-10, WithinRel( chunk.covariances()(4,3) ) );
      CHECK_THAT(  2.792847e-07, WithinRel( chunk.covariances()(4,4) ) );
      CHECK_THAT(  2.435102e-07, WithinRel( chunk.covariances()(4,5) ) );
      CHECK_THAT(  4.742642e-07, WithinRel( chunk.covariances()(4,6) ) );
      CHECK_THAT( -1.127960e-09, WithinRel( chunk.covariances()(4,7) ) );
      CHECK_THAT(  1.953402e-07, WithinRel( chunk.covariances()(5,0) ) );
      CHECK_THAT(  4.553737e-07, WithinRel( chunk.covariances()(5,1) ) );
      CHECK_THAT(  1.147504e-06, WithinRel( chunk.covariances()(5,2) ) );
      CHECK_THAT(  3.816056e-09, WithinRel( chunk.covariances()(5,3) ) );
      CHECK_THAT(  2.435102e-07, WithinRel( chunk.covariances()(5,4) ) );
      CHECK_THAT(  9.364803e-07, WithinRel( chunk.covariances()(5,5) ) );
      CHECK_THAT(  1.744701e-07, WithinRel( chunk.covariances()(5,6) ) );
      CHECK_THAT( -2.394143e-09, WithinRel( chunk.covariances()(5,7) ) );
      CHECK_THAT(  8.550732e-08, WithinRel( chunk.covariances()(6,0) ) );
      CHECK_THAT( -3.459165e-07, WithinRel( chunk.covariances()(6,1) ) );
      CHECK_THAT(  3.036135e-06, WithinRel( chunk.covariances()(6,2) ) );
      CHECK_THAT(  5.460586e-09, WithinRel( chunk.covariances()(6,3) ) );
      CHECK_THAT(  4.742642e-07, WithinRel( chunk.covariances()(6,4) ) );
      CHECK_THAT(  1.744701e-07, WithinRel( chunk.covariances()(6,5) ) );
      CHECK_THAT(  4.887436e-06, WithinRel( chunk.covariances()(6,6) ) );
      CHECK_THAT( -2.686310e-10, WithinRel( chunk.covariances()(6,7) ) );
      CHECK_THAT( -1.352565e-09, WithinRel( chunk.covariances()(7,0) ) );
      CHECK_THAT( -9.048060e-10, WithinRel( chunk.covariances()(7,1) ) );
      CHECK_THAT( -2.642949e-09, WithinRel( chunk.covariances()(7,2) ) );
      CHECK_THAT(  3.336860e-10, WithinRel( chunk.covariances()(7,3) ) );
      CHECK_THAT( -1.127960e-09, WithinRel( chunk.covariances()(7,4) ) );
      CHECK_THAT( -2.394143e-09, WithinRel( chunk.covariances()(7,5) ) );
      CHECK_THAT( -2.686310e-10, WithinRel( chunk.covariances()(7,6) ) );
      CHECK_THAT(  3.280511e-09, WithinRel( chunk.covariances()(7,7) ) );

      CHECK( 8 == chunk.standardDeviations().value().size() );
      CHECK_THAT( 5.78834777807968e-04, WithinRel( chunk.standardDeviations().value()[0] ) );
      CHECK_THAT( 1.17932099107919e-03, WithinRel( chunk.standardDeviations().value()[1] ) );
      CHECK_THAT( 2.03289547198079e-03, WithinRel( chunk.standardDeviations().value()[2] ) );
      CHECK_THAT( 1.93069935515605e-05, WithinRel( chunk.standardDeviations().value()[3] ) );
      CHECK_THAT( 5.28473935024236e-04, WithinRel( chunk.standardDeviations().value()[4] ) );
      CHECK_THAT( 9.67719122473045e-04, WithinRel( chunk.standardDeviations().value()[5] ) );
      CHECK_THAT( 2.21075462229529e-03, WithinRel( chunk.standardDeviations().value()[6] ) );
      CHECK_THAT( 5.72757453028767e-05, WithinRel( chunk.standardDeviations().value()[7] ) );

      CHECK( 8 == chunk.correlations().value().rows() );
      CHECK( 8 == chunk.correlations().value().cols() );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(0,0) ) );
      CHECK_THAT(  4.52078716301036e-01, WithinRel( chunk.correlations().value()(0,1) ) );
      CHECK_THAT(  8.76401556189488e-01, WithinRel( chunk.correlations().value()(0,2) ) );
      CHECK_THAT( -3.10379990825034e-02, WithinRel( chunk.correlations().value()(0,3) ) );
      CHECK_THAT(  3.87924654926139e-01, WithinRel( chunk.correlations().value()(0,4) ) );
      CHECK_THAT(  3.48728698045195e-01, WithinRel( chunk.correlations().value()(0,5) ) );
      CHECK_THAT(  6.68202561925324e-02, WithinRel( chunk.correlations().value()(0,6) ) );
      CHECK_THAT( -4.07974274908842e-02, WithinRel( chunk.correlations().value()(0,7) ) );
      CHECK_THAT(  4.52078716301036e-01, WithinRel( chunk.correlations().value()(1,0) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(1,1) ) );
      CHECK_THAT(  2.94928377943159e-01, WithinRel( chunk.correlations().value()(1,2) ) );
      CHECK_THAT(  3.59534835487576e-02, WithinRel( chunk.correlations().value()(1,3) ) );
      CHECK_THAT( -3.62849549313329e-02, WithinRel( chunk.correlations().value()(1,4) ) );
      CHECK_THAT(  3.99012584110026e-01, WithinRel( chunk.correlations().value()(1,5) ) );
      CHECK_THAT( -1.32677936246521e-01, WithinRel( chunk.correlations().value()(1,6) ) );
      CHECK_THAT( -1.33953076941197e-02, WithinRel( chunk.correlations().value()(1,7) ) );
      CHECK_THAT(  8.76401556189488e-01, WithinRel( chunk.correlations().value()(2,0) ) );
      CHECK_THAT(  2.94928377943159e-01, WithinRel( chunk.correlations().value()(2,1) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(2,2) ) );
      CHECK_THAT( -1.08663995484036e-01, WithinRel( chunk.correlations().value()(2,3) ) );
      CHECK_THAT(  9.26371782910094e-01, WithinRel( chunk.correlations().value()(2,4) ) );
      CHECK_THAT(  5.83297126018077e-01, WithinRel( chunk.correlations().value()(2,5) ) );
      CHECK_THAT(  6.75562428243337e-01, WithinRel( chunk.correlations().value()(2,6) ) );
      CHECK_THAT( -2.26988045368907e-02, WithinRel( chunk.correlations().value()(2,7) ) );
      CHECK_THAT( -3.10379990825034e-02, WithinRel( chunk.correlations().value()(3,0) ) );
      CHECK_THAT(  3.59534835487576e-02, WithinRel( chunk.correlations().value()(3,1) ) );
      CHECK_THAT( -1.08663995484036e-01, WithinRel( chunk.correlations().value()(3,2) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(3,3) ) );
      CHECK_THAT(  3.01032724933124e-02, WithinRel( chunk.correlations().value()(3,4) ) );
      CHECK_THAT(  2.04244685455433e-01, WithinRel( chunk.correlations().value()(3,5) ) );
      CHECK_THAT(  1.27933434186385e-01, WithinRel( chunk.correlations().value()(3,6) ) );
      CHECK_THAT(  3.01753686987760e-01, WithinRel( chunk.correlations().value()(3,7) ) );
      CHECK_THAT(  3.87924654926139e-01, WithinRel( chunk.correlations().value()(4,0) ) );
      CHECK_THAT( -3.62849549313329e-02, WithinRel( chunk.correlations().value()(4,1) ) );
      CHECK_THAT(  9.26371782910094e-01, WithinRel( chunk.correlations().value()(4,2) ) );
      CHECK_THAT(  3.01032724933124e-02, WithinRel( chunk.correlations().value()(4,3) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(4,4) ) );
      CHECK_THAT(  4.76150519164124e-01, WithinRel( chunk.correlations().value()(4,5) ) );
      CHECK_THAT(  4.05934748518847e-01, WithinRel( chunk.correlations().value()(4,6) ) );
      CHECK_THAT( -3.72648500015370e-02, WithinRel( chunk.correlations().value()(4,7) ) );
      CHECK_THAT(  3.48728698045195e-01, WithinRel( chunk.correlations().value()(5,0) ) );
      CHECK_THAT(  3.99012584110026e-01, WithinRel( chunk.correlations().value()(5,1) ) );
      CHECK_THAT(  5.83297126018077e-01, WithinRel( chunk.correlations().value()(5,2) ) );
      CHECK_THAT(  2.04244685455433e-01, WithinRel( chunk.correlations().value()(5,3) ) );
      CHECK_THAT(  4.76150519164124e-01, WithinRel( chunk.correlations().value()(5,4) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(5,5) ) );
      CHECK_THAT(  8.15513482313117e-02, WithinRel( chunk.correlations().value()(5,6) ) );
      CHECK_THAT( -4.31946555113209e-02, WithinRel( chunk.correlations().value()(5,7) ) );
      CHECK_THAT(  6.68202561925324e-02, WithinRel( chunk.correlations().value()(6,0) ) );
      CHECK_THAT( -1.32677936246521e-01, WithinRel( chunk.correlations().value()(6,1) ) );
      CHECK_THAT(  6.75562428243337e-01, WithinRel( chunk.correlations().value()(6,2) ) );
      CHECK_THAT(  1.27933434186385e-01, WithinRel( chunk.correlations().value()(6,3) ) );
      CHECK_THAT(  4.05934748518847e-01, WithinRel( chunk.correlations().value()(6,4) ) );
      CHECK_THAT(  8.15513482313117e-02, WithinRel( chunk.correlations().value()(6,5) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(6,6) ) );
      CHECK_THAT( -2.12150880161591e-03, WithinRel( chunk.correlations().value()(6,7) ) );
      CHECK_THAT( -4.07974274908842e-02, WithinRel( chunk.correlations().value()(7,0) ) );
      CHECK_THAT( -1.33953076941197e-02, WithinRel( chunk.correlations().value()(7,1) ) );
      CHECK_THAT( -2.26988045368907e-02, WithinRel( chunk.correlations().value()(7,2) ) );
      CHECK_THAT(  3.01753686987760e-01, WithinRel( chunk.correlations().value()(7,3) ) );
      CHECK_THAT( -3.72648500015370e-02, WithinRel( chunk.correlations().value()(7,4) ) );
      CHECK_THAT( -4.31946555113209e-02, WithinRel( chunk.correlations().value()(7,5) ) );
      CHECK_THAT( -2.12150880161591e-03, WithinRel( chunk.correlations().value()(7,6) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(7,7) ) );

      CHECK( 8 == chunk.eigenvalues().value().size() );
      CHECK_THAT(  7.93360907096512e-06, WithinRel( chunk.eigenvalues().value()[0] ) );
      CHECK_THAT(  2.77607998044769e-06, WithinRel( chunk.eigenvalues().value()[1] ) );
      CHECK_THAT(  8.72998692347036e-07, WithinRel( chunk.eigenvalues().value()[2] ) );
      CHECK_THAT(  5.09348096171567e-07, WithinRel( chunk.eigenvalues().value()[3] ) );
      CHECK_THAT(  1.08751047007600e-07, WithinRel( chunk.eigenvalues().value()[4] ) );
      CHECK_THAT(  3.31256655183549e-09, WithinRel( chunk.eigenvalues().value()[5] ) );
      // some CI machines have differences in the last 4 digits of the next eigenvalue
      CHECK_THAT(  3.43367202411662e-10, WithinRel( chunk.eigenvalues().value()[6], 1e-11 ) );
      CHECK_THAT( -2.39076849693257e-07, WithinRel( chunk.eigenvalues().value()[7] ) );

      // eigenvector result provided by numpy
      CHECK( 8 == chunk.eigenvectors().value().size() );
      CHECK_THAT(  1.074034990154797e-01, WithinRel( chunk.eigenvectors().value()[0](0), 1e-12 ) );
      CHECK_THAT(  5.031741433412508e-02, WithinRel( chunk.eigenvectors().value()[0](1), 1e-12 ) );
      CHECK_THAT(  6.760345784347230e-01, WithinRel( chunk.eigenvectors().value()[0](2), 1e-12 ) );
      CHECK_THAT(  1.915401875474596e-04, WithinRel( chunk.eigenvectors().value()[0](3), 1e-12 ) );
      CHECK_THAT(  1.372508574710752e-01, WithinRel( chunk.eigenvectors().value()[0](4), 1e-12 ) );
      CHECK_THAT(  1.393826996793076e-01, WithinRel( chunk.eigenvectors().value()[0](5), 1e-12 ) );
      CHECK_THAT(  7.004601426407554e-01, WithinRel( chunk.eigenvectors().value()[0](6), 1e-12 ) );
      CHECK_THAT( -3.346821750524192e-04, WithinRel( chunk.eigenvectors().value()[0](7), 1e-12 ) );
      CHECK_THAT( -2.571527009424179e-01, WithinRel( chunk.eigenvectors().value()[1](0), 1e-12 ) );
      CHECK_THAT( -5.332339693289121e-01, WithinRel( chunk.eigenvectors().value()[1](1), 1e-12 ) );
      CHECK_THAT( -4.136479111214130e-01, WithinRel( chunk.eigenvectors().value()[1](2), 1e-12 ) );
      CHECK_THAT(  1.106338368001554e-03, WithinRel( chunk.eigenvectors().value()[1](3), 1e-12 ) );
      CHECK_THAT( -1.004221706751696e-01, WithinRel( chunk.eigenvectors().value()[1](4), 1e-12 ) );
      CHECK_THAT( -3.764142026504758e-01, WithinRel( chunk.eigenvectors().value()[1](5), 1e-12 ) );
      CHECK_THAT(  5.715373399614003e-01, WithinRel( chunk.eigenvectors().value()[1](6), 1e-12 ) );
      CHECK_THAT(  1.004341476548397e-03, WithinRel( chunk.eigenvectors().value()[1](7), 1e-12 ) );
      CHECK_THAT(  1.371275274983367e-01, WithinRel( chunk.eigenvectors().value()[2](0), 1e-12 ) );
      CHECK_THAT( -8.140382248203507e-01, WithinRel( chunk.eigenvectors().value()[2](1), 1e-12 ) );
      CHECK_THAT(  2.691481835902048e-01, WithinRel( chunk.eigenvectors().value()[2](2), 1e-12 ) );
      CHECK_THAT( -3.231353088691554e-03, WithinRel( chunk.eigenvectors().value()[2](3), 1e-12 ) );
      CHECK_THAT(  3.273381875688868e-01, WithinRel( chunk.eigenvectors().value()[2](4), 1e-12 ) );
      CHECK_THAT(  1.854210583626489e-01, WithinRel( chunk.eigenvectors().value()[2](5), 1e-12 ) );
      CHECK_THAT( -3.233486103311748e-01, WithinRel( chunk.eigenvectors().value()[2](6), 1e-12 ) );
      CHECK_THAT( -1.020603999800658e-03, WithinRel( chunk.eigenvectors().value()[2](7), 1e-12 ) );
      CHECK_THAT( -4.574278897433420e-01, WithinRel( chunk.eigenvectors().value()[3](0), 1e-12 ) );
      CHECK_THAT( -3.768700535852364e-02, WithinRel( chunk.eigenvectors().value()[3](1), 1e-12 ) );
      CHECK_THAT( -2.313850741112833e-01, WithinRel( chunk.eigenvectors().value()[3](2), 1e-12 ) );
      CHECK_THAT(  9.976800706566235e-03, WithinRel( chunk.eigenvectors().value()[3](3), 1e-12 ) );
      CHECK_THAT( -5.343662614796388e-02, WithinRel( chunk.eigenvectors().value()[3](4), 1e-12 ) );
      CHECK_THAT(  8.447798233267909e-01, WithinRel( chunk.eigenvectors().value()[3](5), 1e-12 ) );
      CHECK_THAT(  1.385291026888886e-01, WithinRel( chunk.eigenvectors().value()[3](6), 1e-12 ) );
      CHECK_THAT( -1.446040223355744e-03, WithinRel( chunk.eigenvectors().value()[3](7), 1e-12 ) );
      CHECK_THAT( -5.439389015604781e-01, WithinRel( chunk.eigenvectors().value()[4](0), 1e-12 ) );
      CHECK_THAT(  1.996774457251584e-01, WithinRel( chunk.eigenvectors().value()[4](1), 1e-12 ) );
      CHECK_THAT(  1.639440644799672e-02, WithinRel( chunk.eigenvectors().value()[4](2), 1e-12 ) );
      CHECK_THAT( -5.814555639788589e-03, WithinRel( chunk.eigenvectors().value()[4](3), 1e-12 ) );
      CHECK_THAT(  7.818950572395386e-01, WithinRel( chunk.eigenvectors().value()[4](4), 1e-12 ) );
      CHECK_THAT( -2.224672713971069e-01, WithinRel( chunk.eigenvectors().value()[4](5), 1e-12 ) );
      CHECK_THAT( -5.569982161307516e-02, WithinRel( chunk.eigenvectors().value()[4](6), 1e-12 ) );
      CHECK_THAT(  1.663102992474412e-03, WithinRel( chunk.eigenvectors().value()[4](7), 1e-12 ) );
      CHECK_THAT( -1.752926246654827e-04, WithinRel( chunk.eigenvectors().value()[5](0), 1e-12 ) );
      CHECK_THAT(  8.279317505192994e-04, WithinRel( chunk.eigenvectors().value()[5](1), 1e-12 ) );
      CHECK_THAT( -1.518618778550807e-03, WithinRel( chunk.eigenvectors().value()[5](2), 1e-12 ) );
      CHECK_THAT( -1.096637382643695e-01, WithinRel( chunk.eigenvectors().value()[5](3), 1e-12 ) );
      CHECK_THAT(  7.862304135582435e-04, WithinRel( chunk.eigenvectors().value()[5](4), 1e-12 ) );
      CHECK_THAT( -9.998834737042694e-04, WithinRel( chunk.eigenvectors().value()[5](5), 1e-12 ) );
      CHECK_THAT(  1.033041611015826e-03, WithinRel( chunk.eigenvectors().value()[5](6), 1e-12 ) );
      CHECK_THAT( -9.939658731607477e-01, WithinRel( chunk.eigenvectors().value()[5](7), 1e-12 ) );
      CHECK_THAT(  1.322444642228684e-02, WithinRel( chunk.eigenvectors().value()[6](0), 1e-12 ) );
      CHECK_THAT(  1.263506076818620e-03, WithinRel( chunk.eigenvectors().value()[6](1), 1e-12 ) );
      CHECK_THAT( -5.277719337954276e-03, WithinRel( chunk.eigenvectors().value()[6](2), 1e-12 ) );
      CHECK_THAT(  9.937414417323504e-01, WithinRel( chunk.eigenvectors().value()[6](3), 1e-12 ) );
      CHECK_THAT(  1.515135480819228e-02, WithinRel( chunk.eigenvectors().value()[6](4), 1e-12 ) );
      CHECK_THAT( -5.315067279801292e-03, WithinRel( chunk.eigenvectors().value()[6](5), 1e-12 ) );
      CHECK_THAT(  7.398811740865364e-04, WithinRel( chunk.eigenvectors().value()[6](6), 1e-12 ) );
      CHECK_THAT( -1.096140926827097e-01, WithinRel( chunk.eigenvectors().value()[6](7), 1e-12 ) );
      CHECK_THAT(  6.310691708068932e-01, WithinRel( chunk.eigenvectors().value()[7](0), 1e-12 ) );
      CHECK_THAT(  9.580076031528753e-02, WithinRel( chunk.eigenvectors().value()[7](1), 1e-12 ) );
      CHECK_THAT( -4.955743335231361e-01, WithinRel( chunk.eigenvectors().value()[7](2), 1e-12 ) );
      CHECK_THAT( -1.751466725221130e-02, WithinRel( chunk.eigenvectors().value()[7](3), 1e-12 ) );
      CHECK_THAT(  4.994814966132097e-01, WithinRel( chunk.eigenvectors().value()[7](4), 1e-12 ) );
      CHECK_THAT(  2.032977022465391e-01, WithinRel( chunk.eigenvectors().value()[7](5), 1e-12 ) );
      CHECK_THAT(  2.363301436122759e-01, WithinRel( chunk.eigenvectors().value()[7](6), 1e-12 ) );
      CHECK_THAT(  3.094250598081331e-03, WithinRel( chunk.eigenvectors().value()[7](7), 1e-12 ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid eigenvalues and eigenvectors for product multiplicities" ) {

    ProductMultiplicityMetadata metadata( { id::ReactionID( "n,U235->fission" ) },
                                          { 1e-5, 1e+6, 2e+7 },
                                          { id::ParticleID( "Y99" ), id::ParticleID( "Mo99" ),
                                            id::ParticleID( "Pr148" ), id::ParticleID( "Pr148_e1" ) } );

    std::vector< double > eigenvalues = { 7.93360907096512e-06, 2.77607998044769e-06, 8.72998692347036e-07,
                                          5.09348096171567e-07, 1.08751047007600e-07, 3.31256655183549e-09,
                                          3.43367202411662e-10, -2.39076849693257e-07 };
    std::vector< Vector< double > > eigenvectors( 8, Vector< double >( 8 ) );
    eigenvectors[0] <<  1.074034990154797e-01,  5.031741433412508e-02,  6.760345784347230e-01,  1.915401875474596e-04,
                        1.372508574710752e-01,  1.393826996793076e-01,  7.004601426407554e-01, -3.346821750524192e-04;
    eigenvectors[1] << -2.571527009424179e-01, -5.332339693289121e-01, -4.136479111214130e-01,  1.106338368001554e-03,
                       -1.004221706751696e-01, -3.764142026504758e-01,  5.715373399614003e-01,  1.004341476548397e-03;
    eigenvectors[2] <<  1.371275274983367e-01, -8.140382248203507e-01,  2.691481835902048e-01, -3.231353088691554e-03,
                        3.273381875688868e-01,  1.854210583626489e-01, -3.233486103311748e-01, -1.020603999800658e-03;
    eigenvectors[3] << -4.574278897433420e-01, -3.768700535852364e-02, -2.313850741112833e-01,  9.976800706566235e-03,
                       -5.343662614796388e-02,  8.447798233267909e-01,  1.385291026888886e-01, -1.446040223355744e-03;
    eigenvectors[4] << -5.439389015604781e-01,  1.996774457251584e-01,  1.639440644799672e-02, -5.814555639788589e-03,
                        7.818950572395386e-01, -2.224672713971069e-01, -5.569982161307516e-02,  1.663102992474412e-03;
    eigenvectors[5] << -1.752926246654827e-04,  8.279317505192994e-04, -1.518618778550807e-03, -1.096637382643695e-01,
                        7.862304135582435e-04, -9.998834737042694e-04,  1.033041611015826e-03, -9.939658731607477e-01;
    eigenvectors[6] <<  1.322444642228684e-02,  1.263506076818620e-03, -5.277719337954276e-03,  9.937414417323504e-01,
                        1.515135480819228e-02, -5.315067279801292e-03,  7.398811740865364e-04, -1.096140926827097e-01;
    eigenvectors[7] <<  6.310691708068932e-01,  9.580076031528753e-02, -4.955743335231361e-01, -1.751466725221130e-02,
                        4.994814966132097e-01,  2.032977022465391e-01,  2.363301436122759e-01,  3.094250598081331e-03;

    ProductMultiplicityCovarianceMatrix chunk( std::move( metadata ), std::move( eigenvalues ),
                                               std::move( eigenvectors ), false );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      // test variables
      id::EnergyGroup group1( 1e-5, 1e+6 );
      id::EnergyGroup group2( 1e+6, 2e+7 );
      id::ParticleID product1( "Y99" );
      id::ParticleID product2( "Mo99" );
      id::ParticleID product3( "Pr148" );
      id::ParticleID product4( "Pr148_e1" );

      CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
      CHECK( id::ReactionID( "n,U235->fission" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
      CHECK( 3 == chunk.rowMetadata().energies().size() );
      CHECK( 1e-5 == chunk.rowMetadata().energies()[0] );
      CHECK( 1e+6 == chunk.rowMetadata().energies()[1] );
      CHECK( 2e+7 == chunk.rowMetadata().energies()[2] );
      CHECK( 4 == chunk.rowMetadata().productIdentifiers().size() );
      CHECK( id::ParticleID( "Y99" ) == chunk.rowMetadata().productIdentifiers()[0] );
      CHECK( id::ParticleID( "Mo99" ) == chunk.rowMetadata().productIdentifiers()[1] );
      CHECK( id::ParticleID( "Pr148" ) == chunk.rowMetadata().productIdentifiers()[2] );
      CHECK( id::ParticleID( "Pr148_e1" ) == chunk.rowMetadata().productIdentifiers()[3] );
      CHECK( chunk.rowMetadata() == chunk.columnMetadata() );

      CHECK( false == chunk.isRelativeMatrix() );
      CHECK( true == chunk.isAbsoluteMatrix() );
      CHECK( true == chunk.isOnDiagonal() );
      CHECK( false == chunk.isOffDiagonal() );

      CHECK( std::nullopt != chunk.standardDeviations() );
      CHECK( std::nullopt != chunk.correlations() );
      CHECK( std::nullopt != chunk.eigenvalues() );
      CHECK( std::nullopt != chunk.eigenvectors() );
      CHECK( std::nullopt != std::get< 0 >( chunk.eigendata() ) );
      CHECK( std::nullopt != std::get< 1 >( chunk.eigendata() ) );

      CHECK( 8 == chunk.covariances().rows() );
      CHECK( 8 == chunk.covariances().cols() );
      CHECK_THAT(  3.350497e-07, WithinRel( chunk.covariances()(0,0) ) );
      CHECK_THAT(  3.086034e-07, WithinRel( chunk.covariances()(0,1) ) );
      CHECK_THAT(  1.031271e-06, WithinRel( chunk.covariances()(0,2) ) );
      CHECK_THAT( -3.468670e-10, WithinRel( chunk.covariances()(0,3), 1e-12 ) );
      CHECK_THAT(  1.186658e-07, WithinRel( chunk.covariances()(0,4) ) );
      CHECK_THAT(  1.953402e-07, WithinRel( chunk.covariances()(0,5) ) );
      CHECK_THAT(  8.550732e-08, WithinRel( chunk.covariances()(0,6) ) );
      CHECK_THAT( -1.352565e-09, WithinRel( chunk.covariances()(0,7) ) );
      CHECK_THAT(  3.086034e-07, WithinRel( chunk.covariances()(1,0) ) );
      CHECK_THAT(  1.390798e-06, WithinRel( chunk.covariances()(1,1) ) );
      CHECK_THAT(  7.070720e-07, WithinRel( chunk.covariances()(1,2) ) );
      CHECK_THAT(  8.186300e-10, WithinRel( chunk.covariances()(1,3), 1e-12 ) );
      CHECK_THAT( -2.261425e-08, WithinRel( chunk.covariances()(1,4), 1e-12 ) );
      CHECK_THAT(  4.553737e-07, WithinRel( chunk.covariances()(1,5) ) );
      CHECK_THAT( -3.459165e-07, WithinRel( chunk.covariances()(1,6) ) );
      CHECK_THAT( -9.048060e-10, WithinRel( chunk.covariances()(1,7) ) );
      CHECK_THAT(  1.031271e-06, WithinRel( chunk.covariances()(2,0) ) );
      CHECK_THAT(  7.070720e-07, WithinRel( chunk.covariances()(2,1) ) );
      CHECK_THAT(  4.132664e-06, WithinRel( chunk.covariances()(2,2) ) );
      CHECK_THAT( -4.264964e-09, WithinRel( chunk.covariances()(2,3), 1e-12 ) );
      CHECK_THAT(  9.952311e-07, WithinRel( chunk.covariances()(2,4) ) );
      CHECK_THAT(  1.147504e-06, WithinRel( chunk.covariances()(2,5) ) );
      CHECK_THAT(  3.036135e-06, WithinRel( chunk.covariances()(2,6) ) );
      CHECK_THAT( -2.642949e-09, WithinRel( chunk.covariances()(2,7) ) );
      CHECK_THAT( -3.468670e-10, WithinRel( chunk.covariances()(3,0), 1e-12 ) );
      CHECK_THAT(  8.186300e-10, WithinRel( chunk.covariances()(3,1), 1e-12 ) );
      CHECK_THAT( -4.264964e-09, WithinRel( chunk.covariances()(3,2), 1e-12 ) );
      CHECK_THAT(  3.727600e-10, WithinRel( chunk.covariances()(3,3), 1e-12 ) );
      CHECK_THAT(  3.071510e-10, WithinRel( chunk.covariances()(3,4), 1e-12 ) );
      CHECK_THAT(  3.816056e-09, WithinRel( chunk.covariances()(3,5), 1e-12 ) );
      CHECK_THAT(  5.460586e-09, WithinRel( chunk.covariances()(3,6), 1e-12 ) );
      CHECK_THAT(  3.336860e-10, WithinRel( chunk.covariances()(3,7), 1e-12 ) );
      CHECK_THAT(  1.186658e-07, WithinRel( chunk.covariances()(4,0) ) );
      CHECK_THAT( -2.261425e-08, WithinRel( chunk.covariances()(4,1), 1e-12 ) );
      CHECK_THAT(  9.952311e-07, WithinRel( chunk.covariances()(4,2) ) );
      CHECK_THAT(  3.071510e-10, WithinRel( chunk.covariances()(4,3), 1e-12 ) );
      CHECK_THAT(  2.792847e-07, WithinRel( chunk.covariances()(4,4) ) );
      CHECK_THAT(  2.435102e-07, WithinRel( chunk.covariances()(4,5) ) );
      CHECK_THAT(  4.742642e-07, WithinRel( chunk.covariances()(4,6) ) );
      CHECK_THAT( -1.127960e-09, WithinRel( chunk.covariances()(4,7) ) );
      CHECK_THAT(  1.953402e-07, WithinRel( chunk.covariances()(5,0) ) );
      CHECK_THAT(  4.553737e-07, WithinRel( chunk.covariances()(5,1) ) );
      CHECK_THAT(  1.147504e-06, WithinRel( chunk.covariances()(5,2) ) );
      CHECK_THAT(  3.816056e-09, WithinRel( chunk.covariances()(5,3), 1e-12 ) );
      CHECK_THAT(  2.435102e-07, WithinRel( chunk.covariances()(5,4) ) );
      CHECK_THAT(  9.364803e-07, WithinRel( chunk.covariances()(5,5) ) );
      CHECK_THAT(  1.744701e-07, WithinRel( chunk.covariances()(5,6) ) );
      CHECK_THAT( -2.394143e-09, WithinRel( chunk.covariances()(5,7) ) );
      CHECK_THAT(  8.550732e-08, WithinRel( chunk.covariances()(6,0) ) );
      CHECK_THAT( -3.459165e-07, WithinRel( chunk.covariances()(6,1) ) );
      CHECK_THAT(  3.036135e-06, WithinRel( chunk.covariances()(6,2) ) );
      CHECK_THAT(  5.460586e-09, WithinRel( chunk.covariances()(6,3), 1e-12 ) );
      CHECK_THAT(  4.742642e-07, WithinRel( chunk.covariances()(6,4) ) );
      CHECK_THAT(  1.744701e-07, WithinRel( chunk.covariances()(6,5) ) );
      CHECK_THAT(  4.887436e-06, WithinRel( chunk.covariances()(6,6) ) );
      CHECK_THAT( -2.686310e-10, WithinRel( chunk.covariances()(6,7) ) );
      CHECK_THAT( -1.352565e-09, WithinRel( chunk.covariances()(7,0) ) );
      CHECK_THAT( -9.048060e-10, WithinRel( chunk.covariances()(7,1) ) );
      CHECK_THAT( -2.642949e-09, WithinRel( chunk.covariances()(7,2) ) );
      CHECK_THAT(  3.336860e-10, WithinRel( chunk.covariances()(7,3), 1e-12 ) );
      CHECK_THAT( -1.127960e-09, WithinRel( chunk.covariances()(7,4) ) );
      CHECK_THAT( -2.394143e-09, WithinRel( chunk.covariances()(7,5) ) );
      CHECK_THAT( -2.686310e-10, WithinRel( chunk.covariances()(7,6) ) );
      CHECK_THAT(  3.280511e-09, WithinRel( chunk.covariances()(7,7) ) );

      CHECK( 8 == chunk.standardDeviations().value().size() );
      CHECK_THAT( 5.78834777807968e-04, WithinRel( chunk.standardDeviations().value()[0] ) );
      CHECK_THAT( 1.17932099107919e-03, WithinRel( chunk.standardDeviations().value()[1] ) );
      CHECK_THAT( 2.03289547198079e-03, WithinRel( chunk.standardDeviations().value()[2] ) );
      CHECK_THAT( 1.93069935515605e-05, WithinRel( chunk.standardDeviations().value()[3], 1e-12 ) );
      CHECK_THAT( 5.28473935024236e-04, WithinRel( chunk.standardDeviations().value()[4] ) );
      CHECK_THAT( 9.67719122473045e-04, WithinRel( chunk.standardDeviations().value()[5] ) );
      CHECK_THAT( 2.21075462229529e-03, WithinRel( chunk.standardDeviations().value()[6] ) );
      CHECK_THAT( 5.72757453028767e-05, WithinRel( chunk.standardDeviations().value()[7] ) );

      CHECK( 8 == chunk.correlations().value().rows() );
      CHECK( 8 == chunk.correlations().value().cols() );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(0,0) ) );
      CHECK_THAT(  4.52078716301036e-01, WithinRel( chunk.correlations().value()(0,1) ) );
      CHECK_THAT(  8.76401556189488e-01, WithinRel( chunk.correlations().value()(0,2) ) );
      CHECK_THAT( -3.10379990825034e-02, WithinRel( chunk.correlations().value()(0,3), 1e-12 ) );
      CHECK_THAT(  3.87924654926139e-01, WithinRel( chunk.correlations().value()(0,4) ) );
      CHECK_THAT(  3.48728698045195e-01, WithinRel( chunk.correlations().value()(0,5) ) );
      CHECK_THAT(  6.68202561925324e-02, WithinRel( chunk.correlations().value()(0,6) ) );
      CHECK_THAT( -4.07974274908842e-02, WithinRel( chunk.correlations().value()(0,7) ) );
      CHECK_THAT(  4.52078716301036e-01, WithinRel( chunk.correlations().value()(1,0) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(1,1) ) );
      CHECK_THAT(  2.94928377943159e-01, WithinRel( chunk.correlations().value()(1,2) ) );
      CHECK_THAT(  3.59534835487576e-02, WithinRel( chunk.correlations().value()(1,3), 1e-12 ) );
      CHECK_THAT( -3.62849549313329e-02, WithinRel( chunk.correlations().value()(1,4), 1e-12 ) );
      CHECK_THAT(  3.99012584110026e-01, WithinRel( chunk.correlations().value()(1,5) ) );
      CHECK_THAT( -1.32677936246521e-01, WithinRel( chunk.correlations().value()(1,6) ) );
      CHECK_THAT( -1.33953076941197e-02, WithinRel( chunk.correlations().value()(1,7) ) );
      CHECK_THAT(  8.76401556189488e-01, WithinRel( chunk.correlations().value()(2,0) ) );
      CHECK_THAT(  2.94928377943159e-01, WithinRel( chunk.correlations().value()(2,1) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(2,2) ) );
      CHECK_THAT( -1.08663995484036e-01, WithinRel( chunk.correlations().value()(2,3), 1e-12 ) );
      CHECK_THAT(  9.26371782910094e-01, WithinRel( chunk.correlations().value()(2,4) ) );
      CHECK_THAT(  5.83297126018077e-01, WithinRel( chunk.correlations().value()(2,5) ) );
      CHECK_THAT(  6.75562428243337e-01, WithinRel( chunk.correlations().value()(2,6) ) );
      CHECK_THAT( -2.26988045368907e-02, WithinRel( chunk.correlations().value()(2,7) ) );
      CHECK_THAT( -3.10379990825034e-02, WithinRel( chunk.correlations().value()(3,0), 1e-12 ) );
      CHECK_THAT(  3.59534835487576e-02, WithinRel( chunk.correlations().value()(3,1), 1e-12 ) );
      CHECK_THAT( -1.08663995484036e-01, WithinRel( chunk.correlations().value()(3,2), 1e-12 ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(3,3), 1e-12 ) );
      CHECK_THAT(  3.01032724933124e-02, WithinRel( chunk.correlations().value()(3,4), 1e-12 ) );
      CHECK_THAT(  2.04244685455433e-01, WithinRel( chunk.correlations().value()(3,5), 1e-12 ) );
      CHECK_THAT(  1.27933434186385e-01, WithinRel( chunk.correlations().value()(3,6), 1e-12 ) );
      CHECK_THAT(  3.01753686987760e-01, WithinRel( chunk.correlations().value()(3,7), 1e-12 ) );
      CHECK_THAT(  3.87924654926139e-01, WithinRel( chunk.correlations().value()(4,0) ) );
      CHECK_THAT( -3.62849549313329e-02, WithinRel( chunk.correlations().value()(4,1), 1e-12 ) );
      CHECK_THAT(  9.26371782910094e-01, WithinRel( chunk.correlations().value()(4,2) ) );
      CHECK_THAT(  3.01032724933124e-02, WithinRel( chunk.correlations().value()(4,3), 1e-12 ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(4,4) ) );
      CHECK_THAT(  4.76150519164124e-01, WithinRel( chunk.correlations().value()(4,5) ) );
      CHECK_THAT(  4.05934748518847e-01, WithinRel( chunk.correlations().value()(4,6) ) );
      CHECK_THAT( -3.72648500015370e-02, WithinRel( chunk.correlations().value()(4,7) ) );
      CHECK_THAT(  3.48728698045195e-01, WithinRel( chunk.correlations().value()(5,0) ) );
      CHECK_THAT(  3.99012584110026e-01, WithinRel( chunk.correlations().value()(5,1) ) );
      CHECK_THAT(  5.83297126018077e-01, WithinRel( chunk.correlations().value()(5,2) ) );
      CHECK_THAT(  2.04244685455433e-01, WithinRel( chunk.correlations().value()(5,3), 1e-12 ) );
      CHECK_THAT(  4.76150519164124e-01, WithinRel( chunk.correlations().value()(5,4) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(5,5) ) );
      CHECK_THAT(  8.15513482313117e-02, WithinRel( chunk.correlations().value()(5,6) ) );
      CHECK_THAT( -4.31946555113209e-02, WithinRel( chunk.correlations().value()(5,7) ) );
      CHECK_THAT(  6.68202561925324e-02, WithinRel( chunk.correlations().value()(6,0) ) );
      CHECK_THAT( -1.32677936246521e-01, WithinRel( chunk.correlations().value()(6,1) ) );
      CHECK_THAT(  6.75562428243337e-01, WithinRel( chunk.correlations().value()(6,2) ) );
      CHECK_THAT(  1.27933434186385e-01, WithinRel( chunk.correlations().value()(6,3), 1e-12 ) );
      CHECK_THAT(  4.05934748518847e-01, WithinRel( chunk.correlations().value()(6,4) ) );
      CHECK_THAT(  8.15513482313117e-02, WithinRel( chunk.correlations().value()(6,5) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(6,6) ) );
      CHECK_THAT( -2.12150880161591e-03, WithinRel( chunk.correlations().value()(6,7) ) );
      CHECK_THAT( -4.07974274908842e-02, WithinRel( chunk.correlations().value()(7,0) ) );
      CHECK_THAT( -1.33953076941197e-02, WithinRel( chunk.correlations().value()(7,1) ) );
      CHECK_THAT( -2.26988045368907e-02, WithinRel( chunk.correlations().value()(7,2) ) );
      CHECK_THAT(  3.01753686987760e-01, WithinRel( chunk.correlations().value()(7,3), 1e-12 ) );
      CHECK_THAT( -3.72648500015370e-02, WithinRel( chunk.correlations().value()(7,4) ) );
      CHECK_THAT( -4.31946555113209e-02, WithinRel( chunk.correlations().value()(7,5) ) );
      CHECK_THAT( -2.12150880161591e-03, WithinRel( chunk.correlations().value()(7,6) ) );
      CHECK_THAT(  1.00000000000000e+00, WithinRel( chunk.correlations().value()(7,7) ) );

      CHECK( 8 == chunk.eigenvalues().value().size() );
      CHECK_THAT(  7.93360907096512e-06, WithinRel( chunk.eigenvalues().value()[0] ) );
      CHECK_THAT(  2.77607998044769e-06, WithinRel( chunk.eigenvalues().value()[1] ) );
      CHECK_THAT(  8.72998692347036e-07, WithinRel( chunk.eigenvalues().value()[2] ) );
      CHECK_THAT(  5.09348096171567e-07, WithinRel( chunk.eigenvalues().value()[3] ) );
      CHECK_THAT(  1.08751047007600e-07, WithinRel( chunk.eigenvalues().value()[4] ) );
      CHECK_THAT(  3.31256655183549e-09, WithinRel( chunk.eigenvalues().value()[5] ) );
      // some CI machines have differences in the last 4 digits of the next eigenvalue
      CHECK_THAT(  3.43367202411662e-10, WithinRel( chunk.eigenvalues().value()[6], 1e-11 ) );

      // eigenvector result provided by numpy
      CHECK( 8 == chunk.eigenvectors().value().size() );
      CHECK_THAT(  1.074034990154797e-01, WithinRel( chunk.eigenvectors().value()[0](0) ) );
      CHECK_THAT(  5.031741433412508e-02, WithinRel( chunk.eigenvectors().value()[0](1) ) );
      CHECK_THAT(  6.760345784347230e-01, WithinRel( chunk.eigenvectors().value()[0](2) ) );
      CHECK_THAT(  1.915401875474596e-04, WithinRel( chunk.eigenvectors().value()[0](3) ) );
      CHECK_THAT(  1.372508574710752e-01, WithinRel( chunk.eigenvectors().value()[0](4) ) );
      CHECK_THAT(  1.393826996793076e-01, WithinRel( chunk.eigenvectors().value()[0](5) ) );
      CHECK_THAT(  7.004601426407554e-01, WithinRel( chunk.eigenvectors().value()[0](6) ) );
      CHECK_THAT( -3.346821750524192e-04, WithinRel( chunk.eigenvectors().value()[0](7) ) );
      CHECK_THAT( -2.571527009424179e-01, WithinRel( chunk.eigenvectors().value()[1](0) ) );
      CHECK_THAT( -5.332339693289121e-01, WithinRel( chunk.eigenvectors().value()[1](1) ) );
      CHECK_THAT( -4.136479111214130e-01, WithinRel( chunk.eigenvectors().value()[1](2) ) );
      CHECK_THAT(  1.106338368001554e-03, WithinRel( chunk.eigenvectors().value()[1](3) ) );
      CHECK_THAT( -1.004221706751696e-01, WithinRel( chunk.eigenvectors().value()[1](4) ) );
      CHECK_THAT( -3.764142026504758e-01, WithinRel( chunk.eigenvectors().value()[1](5) ) );
      CHECK_THAT(  5.715373399614003e-01, WithinRel( chunk.eigenvectors().value()[1](6) ) );
      CHECK_THAT(  1.004341476548397e-03, WithinRel( chunk.eigenvectors().value()[1](7) ) );
      CHECK_THAT(  1.371275274983367e-01, WithinRel( chunk.eigenvectors().value()[2](0) ) );
      CHECK_THAT( -8.140382248203507e-01, WithinRel( chunk.eigenvectors().value()[2](1) ) );
      CHECK_THAT(  2.691481835902048e-01, WithinRel( chunk.eigenvectors().value()[2](2) ) );
      CHECK_THAT( -3.231353088691554e-03, WithinRel( chunk.eigenvectors().value()[2](3) ) );
      CHECK_THAT(  3.273381875688868e-01, WithinRel( chunk.eigenvectors().value()[2](4) ) );
      CHECK_THAT(  1.854210583626489e-01, WithinRel( chunk.eigenvectors().value()[2](5) ) );
      CHECK_THAT( -3.233486103311748e-01, WithinRel( chunk.eigenvectors().value()[2](6) ) );
      CHECK_THAT( -1.020603999800658e-03, WithinRel( chunk.eigenvectors().value()[2](7) ) );
      CHECK_THAT( -4.574278897433420e-01, WithinRel( chunk.eigenvectors().value()[3](0) ) );
      CHECK_THAT( -3.768700535852364e-02, WithinRel( chunk.eigenvectors().value()[3](1) ) );
      CHECK_THAT( -2.313850741112833e-01, WithinRel( chunk.eigenvectors().value()[3](2) ) );
      CHECK_THAT(  9.976800706566235e-03, WithinRel( chunk.eigenvectors().value()[3](3) ) );
      CHECK_THAT( -5.343662614796388e-02, WithinRel( chunk.eigenvectors().value()[3](4) ) );
      CHECK_THAT(  8.447798233267909e-01, WithinRel( chunk.eigenvectors().value()[3](5) ) );
      CHECK_THAT(  1.385291026888886e-01, WithinRel( chunk.eigenvectors().value()[3](6) ) );
      CHECK_THAT( -1.446040223355744e-03, WithinRel( chunk.eigenvectors().value()[3](7) ) );
      CHECK_THAT( -5.439389015604781e-01, WithinRel( chunk.eigenvectors().value()[4](0) ) );
      CHECK_THAT(  1.996774457251584e-01, WithinRel( chunk.eigenvectors().value()[4](1) ) );
      CHECK_THAT(  1.639440644799672e-02, WithinRel( chunk.eigenvectors().value()[4](2) ) );
      CHECK_THAT( -5.814555639788589e-03, WithinRel( chunk.eigenvectors().value()[4](3) ) );
      CHECK_THAT(  7.818950572395386e-01, WithinRel( chunk.eigenvectors().value()[4](4) ) );
      CHECK_THAT( -2.224672713971069e-01, WithinRel( chunk.eigenvectors().value()[4](5) ) );
      CHECK_THAT( -5.569982161307516e-02, WithinRel( chunk.eigenvectors().value()[4](6) ) );
      CHECK_THAT(  1.663102992474412e-03, WithinRel( chunk.eigenvectors().value()[4](7) ) );
      CHECK_THAT( -1.752926246654827e-04, WithinRel( chunk.eigenvectors().value()[5](0) ) );
      CHECK_THAT(  8.279317505192994e-04, WithinRel( chunk.eigenvectors().value()[5](1) ) );
      CHECK_THAT( -1.518618778550807e-03, WithinRel( chunk.eigenvectors().value()[5](2) ) );
      CHECK_THAT( -1.096637382643695e-01, WithinRel( chunk.eigenvectors().value()[5](3) ) );
      CHECK_THAT(  7.862304135582435e-04, WithinRel( chunk.eigenvectors().value()[5](4) ) );
      CHECK_THAT( -9.998834737042694e-04, WithinRel( chunk.eigenvectors().value()[5](5) ) );
      CHECK_THAT(  1.033041611015826e-03, WithinRel( chunk.eigenvectors().value()[5](6) ) );
      CHECK_THAT( -9.939658731607477e-01, WithinRel( chunk.eigenvectors().value()[5](7) ) );
      CHECK_THAT(  1.322444642228684e-02, WithinRel( chunk.eigenvectors().value()[6](0) ) );
      CHECK_THAT(  1.263506076818620e-03, WithinRel( chunk.eigenvectors().value()[6](1) ) );
      CHECK_THAT( -5.277719337954276e-03, WithinRel( chunk.eigenvectors().value()[6](2) ) );
      CHECK_THAT(  9.937414417323504e-01, WithinRel( chunk.eigenvectors().value()[6](3) ) );
      CHECK_THAT(  1.515135480819228e-02, WithinRel( chunk.eigenvectors().value()[6](4) ) );
      CHECK_THAT( -5.315067279801292e-03, WithinRel( chunk.eigenvectors().value()[6](5) ) );
      CHECK_THAT(  7.398811740865364e-04, WithinRel( chunk.eigenvectors().value()[6](6) ) );
      CHECK_THAT( -1.096140926827097e-01, WithinRel( chunk.eigenvectors().value()[6](7) ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid covariance data for product multiplicities" ) {

    // matrix and test results provided by Amanda Lewis

    ProductMultiplicityMetadata metadata( { id::ReactionID( "n,U235->fission" ) },
                                          { 1e-5, 1e+6, 2e+7 },
                                          { id::ParticleID( "Y99" ), id::ParticleID( "Mo99" ),
                                            id::ParticleID( "Pr148" ), id::ParticleID( "Pr148_e1" ) } );

    Matrix< double > matrix( 8, 8 );
    matrix <<   3.350497e-07,  3.086034e-07,  1.031271e-06, -3.468670e-10, 1.186658e-07,  1.953402e-07,  8.550732e-08, -1.352565e-09,
                3.086034e-07,  1.390798e-06,  7.070720e-07,  8.186300e-10, -2.261425e-08,  4.553737e-07, -3.459165e-07, -9.048060e-10,
                1.031271e-06,  7.070720e-07,  4.132664e-06, -4.264964e-09, 9.952311e-07,  1.147504e-06,  3.036135e-06, -2.642949e-09,
               -3.468670e-10,  8.186300e-10, -4.264964e-09,  3.727600e-10, 3.071510e-10,  3.816056e-09,  5.460586e-09,  3.336860e-10,
                1.186658e-07, -2.261425e-08,  9.952311e-07,  3.071510e-10, 2.792847e-07,  2.435102e-07,  4.742642e-07, -1.127960e-09,
                1.953402e-07,  4.553737e-07,  1.147504e-06,  3.816056e-09, 2.435102e-07,  9.364803e-07,  1.744701e-07, -2.394143e-09,
                8.550732e-08, -3.459165e-07,  3.036135e-06,  5.460586e-09, 4.742642e-07,  1.744701e-07,  4.887436e-06, -2.686310e-10,
               -1.352565e-09, -9.048060e-10, -2.642949e-09,  3.336860e-10, -1.127960e-09, -2.394143e-09, -2.686310e-10,  3.280511e-09;

    ProductMultiplicityCovarianceMatrix chunk( std::move( metadata ),
                                               std::move( matrix ),
                                               false );

    // test variables
    id::ReactionID reaction( "n,U235->fission" );
    id::EnergyGroup group1( 1e-5, 1e+6 );
    id::EnergyGroup group2( 1e+6, 2e+7 );
    id::ParticleID product1( "Y99" );
    id::ParticleID product2( "Mo99" );
    id::ParticleID product3( "Pr148" );
    id::ParticleID product4( "Pr148_e1" );

    WHEN( "extracting a covariance matrix for a single product over all groups" ) {

      auto submatrix = chunk.extract( reaction, std::nullopt, product3 );

      THEN( "A submatrix can be extracted" ) {

        CHECK( 1 == submatrix.rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->fission" ) == submatrix.rowMetadata().reactionIdentifiers()[0] );
        CHECK( 3 == submatrix.rowMetadata().energies().size() );
        CHECK( 1e-5 == submatrix.rowMetadata().energies()[0] );
        CHECK( 1e+6 == submatrix.rowMetadata().energies()[1] );
        CHECK( 2e+7 == submatrix.rowMetadata().energies()[2] );
        CHECK( 1 == submatrix.rowMetadata().productIdentifiers().size() );
        CHECK( id::ParticleID( "Pr148" ) == submatrix.rowMetadata().productIdentifiers()[0] );
        CHECK( submatrix.rowMetadata() == submatrix.columnMetadata() );

        CHECK( false == submatrix.isRelativeMatrix() );
        CHECK( true == submatrix.isAbsoluteMatrix() );
        CHECK( true == submatrix.isOnDiagonal() );
        CHECK( false == submatrix.isOffDiagonal() );

        CHECK( std::nullopt != submatrix.standardDeviations() );
        CHECK( std::nullopt != submatrix.correlations() );
        CHECK( std::nullopt != submatrix.eigenvalues() );
        CHECK( std::nullopt != submatrix.eigenvectors() );
        CHECK( std::nullopt != std::get< 0 >( submatrix.eigendata() ) );
        CHECK( std::nullopt != std::get< 1 >( submatrix.eigendata() ) );

        CHECK_THAT(  4.132664e-06, WithinRel( submatrix.covariances()(0,0) ) );
        CHECK_THAT(  3.036135e-06, WithinRel( submatrix.covariances()(0,1) ) );
        CHECK_THAT(  3.036135e-06, WithinRel( submatrix.covariances()(1,0) ) );
        CHECK_THAT(  4.887436e-06, WithinRel( submatrix.covariances()(1,1) ) );
      } // THEN
    } // WHEN

    WHEN( "extracting a covariance matrix for a single group" ) {

      auto submatrix = chunk.extract( reaction, group2, std::nullopt );

      THEN( "A submatrix can be extracted" ) {

        CHECK( 1 == submatrix.rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->fission" ) == submatrix.rowMetadata().reactionIdentifiers()[0] );
        CHECK( 2 == submatrix.rowMetadata().energies().size() );
        CHECK( 1e+6 == submatrix.rowMetadata().energies()[0] );
        CHECK( 2e+7 == submatrix.rowMetadata().energies()[1] );
        CHECK( 4 == submatrix.rowMetadata().productIdentifiers().size() );
        CHECK( id::ParticleID( "Y99" ) == chunk.rowMetadata().productIdentifiers()[0] );
        CHECK( id::ParticleID( "Mo99" ) == chunk.rowMetadata().productIdentifiers()[1] );
        CHECK( id::ParticleID( "Pr148" ) == chunk.rowMetadata().productIdentifiers()[2] );
        CHECK( id::ParticleID( "Pr148_e1" ) == chunk.rowMetadata().productIdentifiers()[3] );
        CHECK( submatrix.rowMetadata() == submatrix.columnMetadata() );

        CHECK( false == submatrix.isRelativeMatrix() );
        CHECK( true == submatrix.isAbsoluteMatrix() );
        CHECK( true == submatrix.isOnDiagonal() );
        CHECK( false == submatrix.isOffDiagonal() );

        CHECK( std::nullopt != submatrix.standardDeviations() );
        CHECK( std::nullopt != submatrix.correlations() );
        CHECK( std::nullopt != submatrix.eigenvalues() );
        CHECK( std::nullopt != submatrix.eigenvectors() );
        CHECK( std::nullopt != std::get< 0 >( submatrix.eigendata() ) );
        CHECK( std::nullopt != std::get< 1 >( submatrix.eigendata() ) );

        CHECK_THAT(  2.792847e-07, WithinRel( submatrix.covariances()(0,0) ) );
        CHECK_THAT(  2.435102e-07, WithinRel( submatrix.covariances()(0,1) ) );
        CHECK_THAT(  4.742642e-07, WithinRel( submatrix.covariances()(0,2) ) );
        CHECK_THAT( -1.127960e-09, WithinRel( submatrix.covariances()(0,3) ) );
        CHECK_THAT(  2.435102e-07, WithinRel( submatrix.covariances()(1,0) ) );
        CHECK_THAT(  9.364803e-07, WithinRel( submatrix.covariances()(1,1) ) );
        CHECK_THAT(  1.744701e-07, WithinRel( submatrix.covariances()(1,2) ) );
        CHECK_THAT( -2.394143e-09, WithinRel( submatrix.covariances()(1,3) ) );
        CHECK_THAT(  4.742642e-07, WithinRel( submatrix.covariances()(2,0) ) );
        CHECK_THAT(  1.744701e-07, WithinRel( submatrix.covariances()(2,1) ) );
        CHECK_THAT(  4.887436e-06, WithinRel( submatrix.covariances()(2,2) ) );
        CHECK_THAT( -2.686310e-10, WithinRel( submatrix.covariances()(2,3) ) );
        CHECK_THAT( -1.127960e-09, WithinRel( submatrix.covariances()(3,0) ) );
        CHECK_THAT( -2.394143e-09, WithinRel( submatrix.covariances()(3,1) ) );
        CHECK_THAT( -2.686310e-10, WithinRel( submatrix.covariances()(3,2) ) );
        CHECK_THAT(  3.280511e-09, WithinRel( submatrix.covariances()(3,3) ) );
      } // THEN
    } // WHEN

    WHEN( "extracting a covariance matrix for an energy cross term" ) {

      auto submatrix = chunk.extract( reaction, group1, std::nullopt,
                                      reaction, group2, std::nullopt );

      THEN( "A submatrix can be extracted" ) {

        CHECK( 1 == submatrix.rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->fission" ) == submatrix.rowMetadata().reactionIdentifiers()[0] );
        CHECK( 2 == submatrix.rowMetadata().energies().size() );
        CHECK( 1e-5 == submatrix.rowMetadata().energies()[0] );
        CHECK( 1e+6 == submatrix.rowMetadata().energies()[1] );
        CHECK( 4 == submatrix.rowMetadata().productIdentifiers().size() );
        CHECK( id::ParticleID( "Y99" ) == chunk.rowMetadata().productIdentifiers()[0] );
        CHECK( id::ParticleID( "Mo99" ) == chunk.rowMetadata().productIdentifiers()[1] );
        CHECK( id::ParticleID( "Pr148" ) == chunk.rowMetadata().productIdentifiers()[2] );
        CHECK( id::ParticleID( "Pr148_e1" ) == chunk.rowMetadata().productIdentifiers()[3] );

        CHECK( 1 == submatrix.columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->fission" ) == submatrix.columnMetadata().reactionIdentifiers()[0] );
        CHECK( 2 == submatrix.columnMetadata().energies().size() );
        CHECK( 1e+6 == submatrix.columnMetadata().energies()[0] );
        CHECK( 2e+7 == submatrix.columnMetadata().energies()[1] );
        CHECK( 4 == submatrix.columnMetadata().productIdentifiers().size() );
        CHECK( id::ParticleID( "Y99" ) == chunk.columnMetadata().productIdentifiers()[0] );
        CHECK( id::ParticleID( "Mo99" ) == chunk.columnMetadata().productIdentifiers()[1] );
        CHECK( id::ParticleID( "Pr148" ) == chunk.columnMetadata().productIdentifiers()[2] );
        CHECK( id::ParticleID( "Pr148_e1" ) == chunk.columnMetadata().productIdentifiers()[3] );

        CHECK( false == submatrix.isRelativeMatrix() );
        CHECK( true == submatrix.isAbsoluteMatrix() );
        CHECK( false == submatrix.isOnDiagonal() );
        CHECK( true == submatrix.isOffDiagonal() );

        CHECK( std::nullopt == submatrix.standardDeviations() );
        CHECK( std::nullopt == submatrix.correlations() );
        CHECK( std::nullopt == submatrix.eigenvalues() );
        CHECK( std::nullopt == submatrix.eigenvectors() );
        CHECK( std::nullopt == std::get< 0 >( submatrix.eigendata() ) );
        CHECK( std::nullopt == std::get< 1 >( submatrix.eigendata() ) );

        CHECK_THAT(  1.186658e-07, WithinRel( submatrix.covariances()(0,0) ) );
        CHECK_THAT(  1.953402e-07, WithinRel( submatrix.covariances()(0,1) ) );
        CHECK_THAT(  8.550732e-08, WithinRel( submatrix.covariances()(0,2) ) );
        CHECK_THAT( -1.352565e-09, WithinRel( submatrix.covariances()(0,3) ) );
        CHECK_THAT( -2.261425e-08, WithinRel( submatrix.covariances()(1,0) ) );
        CHECK_THAT(  4.553737e-07, WithinRel( submatrix.covariances()(1,1) ) );
        CHECK_THAT( -3.459165e-07, WithinRel( submatrix.covariances()(1,2) ) );
        CHECK_THAT( -9.048060e-10, WithinRel( submatrix.covariances()(1,3) ) );
        CHECK_THAT(  9.952311e-07, WithinRel( submatrix.covariances()(2,0) ) );
        CHECK_THAT(  1.147504e-06, WithinRel( submatrix.covariances()(2,1) ) );
        CHECK_THAT(  3.036135e-06, WithinRel( submatrix.covariances()(2,2) ) );
        CHECK_THAT( -2.642949e-09, WithinRel( submatrix.covariances()(2,3) ) );
        CHECK_THAT(  3.071510e-10, WithinRel( submatrix.covariances()(3,0) ) );
        CHECK_THAT(  3.816056e-09, WithinRel( submatrix.covariances()(3,1) ) );
        CHECK_THAT(  5.460586e-09, WithinRel( submatrix.covariances()(3,2) ) );
        CHECK_THAT(  3.336860e-10, WithinRel( submatrix.covariances()(3,3) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
