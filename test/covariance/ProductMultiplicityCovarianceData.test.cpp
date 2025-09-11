// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/ProductMultiplicityCovarianceData.hpp"

// other includes
#include <iostream>
#include <iomanip>
// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "CovarianceMatrix" ) {

  GIVEN( "valid covariance data for product multiplicities" ) {

    // matrix and test results provided by Amanda Lewis

    std::vector< double > energies{ 1e-5, 1e+6, 2e+7 };
    std::vector< id::ParticleID > products{ id::ParticleID( "Y99" ), id::ParticleID( "Mo99" ),
                                            id::ParticleID( "Pr148" ), id::ParticleID( "Pr148_e1" ) };

    Matrix< double > matrix( 8, 8 );
    matrix <<   3.350497e-07,  3.086034e-07,  1.031271e-06, -3.468670e-10, 1.186658e-07,  1.953402e-07,  8.550732e-08, -1.352565e-09,
                3.086034e-07,  1.390798e-06,  7.070720e-07,  8.186300e-10, -2.261425e-08,  4.553737e-07, -3.459165e-07, -9.048060e-10,
                1.031271e-06,  7.070720e-07,  4.132664e-06, -4.264964e-09, 9.952311e-07,  1.147504e-06,  3.036135e-06, -2.642949e-09,
               -3.468670e-10,  8.186300e-10, -4.264964e-09,  3.727600e-10, 3.071510e-10,  3.816056e-09,  5.460586e-09,  3.336860e-10,
                1.186658e-07, -2.261425e-08,  9.952311e-07,  3.071510e-10, 2.792847e-07,  2.435102e-07,  4.742642e-07, -1.127960e-09,
                1.953402e-07,  4.553737e-07,  1.147504e-06,  3.816056e-09, 2.435102e-07,  9.364803e-07,  1.744701e-07, -2.394143e-09,
                8.550732e-08, -3.459165e-07,  3.036135e-06,  5.460586e-09, 4.742642e-07,  1.744701e-07,  4.887436e-06, -2.686310e-10,
               -1.352565e-09, -9.048060e-10, -2.642949e-09,  3.336860e-10, -1.127960e-09, -2.394143e-09, -2.686310e-10,  3.280511e-09;

    ProductMultiplicityCovarianceData chunk( std::move( energies ), std::move( products ),
                                             std::move( matrix ), false );

    THEN( "a CovarianceMatrix can be constructed and members can be tested" ) {

      CHECK( 8 == chunk.rowKeys().size() );
      CHECK( 8 == chunk.columnKeys().size() );

      CHECK( true == chunk.isRelativeBlock() );
      CHECK( false == chunk.isAbsoluteBlock() );

      CHECK( std::nullopt != chunk.covariances() );
      CHECK( std::nullopt == chunk.standardDeviations() );
      CHECK( std::nullopt == chunk.correlations() );
      CHECK( std::nullopt == chunk.eigenvalues() );

      CHECK_THAT(  3.350497e-07, WithinRel( chunk.covariances().value()(0,0) ) );
      CHECK_THAT(  3.086034e-07, WithinRel( chunk.covariances().value()(0,1) ) );
      CHECK_THAT(  1.031271e-06, WithinRel( chunk.covariances().value()(0,2) ) );
      CHECK_THAT( -3.468670e-10, WithinRel( chunk.covariances().value()(0,3) ) );
      CHECK_THAT(  1.186658e-07, WithinRel( chunk.covariances().value()(0,4) ) );
      CHECK_THAT(  1.953402e-07, WithinRel( chunk.covariances().value()(0,5) ) );
      CHECK_THAT(  8.550732e-08, WithinRel( chunk.covariances().value()(0,6) ) );
      CHECK_THAT( -1.352565e-09, WithinRel( chunk.covariances().value()(0,7) ) );
      CHECK_THAT(  3.086034e-07, WithinRel( chunk.covariances().value()(1,0) ) );
      CHECK_THAT(  1.390798e-06, WithinRel( chunk.covariances().value()(1,1) ) );
      CHECK_THAT(  7.070720e-07, WithinRel( chunk.covariances().value()(1,2) ) );
      CHECK_THAT(  8.186300e-10, WithinRel( chunk.covariances().value()(1,3) ) );
      CHECK_THAT( -2.261425e-08, WithinRel( chunk.covariances().value()(1,4) ) );
      CHECK_THAT(  4.553737e-07, WithinRel( chunk.covariances().value()(1,5) ) );
      CHECK_THAT( -3.459165e-07, WithinRel( chunk.covariances().value()(1,6) ) );
      CHECK_THAT( -9.048060e-10, WithinRel( chunk.covariances().value()(1,7) ) );
      CHECK_THAT(  1.031271e-06, WithinRel( chunk.covariances().value()(2,0) ) );
      CHECK_THAT(  7.070720e-07, WithinRel( chunk.covariances().value()(2,1) ) );
      CHECK_THAT(  4.132664e-06, WithinRel( chunk.covariances().value()(2,2) ) );
      CHECK_THAT( -4.264964e-09, WithinRel( chunk.covariances().value()(2,3) ) );
      CHECK_THAT(  9.952311e-07, WithinRel( chunk.covariances().value()(2,4) ) );
      CHECK_THAT(  1.147504e-06, WithinRel( chunk.covariances().value()(2,5) ) );
      CHECK_THAT(  3.036135e-06, WithinRel( chunk.covariances().value()(2,6) ) );
      CHECK_THAT( -2.642949e-09, WithinRel( chunk.covariances().value()(2,7) ) );
      CHECK_THAT( -3.468670e-10, WithinRel( chunk.covariances().value()(3,0) ) );
      CHECK_THAT(  8.186300e-10, WithinRel( chunk.covariances().value()(3,1) ) );
      CHECK_THAT( -4.264964e-09, WithinRel( chunk.covariances().value()(3,2) ) );
      CHECK_THAT(  3.727600e-10, WithinRel( chunk.covariances().value()(3,3) ) );
      CHECK_THAT(  3.071510e-10, WithinRel( chunk.covariances().value()(3,4) ) );
      CHECK_THAT(  3.816056e-09, WithinRel( chunk.covariances().value()(3,5) ) );
      CHECK_THAT(  5.460586e-09, WithinRel( chunk.covariances().value()(3,6) ) );
      CHECK_THAT(  3.336860e-10, WithinRel( chunk.covariances().value()(3,7) ) );
      CHECK_THAT(  1.186658e-07, WithinRel( chunk.covariances().value()(4,0) ) );
      CHECK_THAT( -2.261425e-08, WithinRel( chunk.covariances().value()(4,1) ) );
      CHECK_THAT(  9.952311e-07, WithinRel( chunk.covariances().value()(4,2) ) );
      CHECK_THAT(  3.071510e-10, WithinRel( chunk.covariances().value()(4,3) ) );
      CHECK_THAT(  2.792847e-07, WithinRel( chunk.covariances().value()(4,4) ) );
      CHECK_THAT(  2.435102e-07, WithinRel( chunk.covariances().value()(4,5) ) );
      CHECK_THAT(  4.742642e-07, WithinRel( chunk.covariances().value()(4,6) ) );
      CHECK_THAT( -1.127960e-09, WithinRel( chunk.covariances().value()(4,7) ) );
      CHECK_THAT(  1.953402e-07, WithinRel( chunk.covariances().value()(5,0) ) );
      CHECK_THAT(  4.553737e-07, WithinRel( chunk.covariances().value()(5,1) ) );
      CHECK_THAT(  1.147504e-06, WithinRel( chunk.covariances().value()(5,2) ) );
      CHECK_THAT(  3.816056e-09, WithinRel( chunk.covariances().value()(5,3) ) );
      CHECK_THAT(  2.435102e-07, WithinRel( chunk.covariances().value()(5,4) ) );
      CHECK_THAT(  9.364803e-07, WithinRel( chunk.covariances().value()(5,5) ) );
      CHECK_THAT(  1.744701e-07, WithinRel( chunk.covariances().value()(5,6) ) );
      CHECK_THAT( -2.394143e-09, WithinRel( chunk.covariances().value()(5,7) ) );
      CHECK_THAT(  8.550732e-08, WithinRel( chunk.covariances().value()(6,0) ) );
      CHECK_THAT( -3.459165e-07, WithinRel( chunk.covariances().value()(6,1) ) );
      CHECK_THAT(  3.036135e-06, WithinRel( chunk.covariances().value()(6,2) ) );
      CHECK_THAT(  5.460586e-09, WithinRel( chunk.covariances().value()(6,3) ) );
      CHECK_THAT(  4.742642e-07, WithinRel( chunk.covariances().value()(6,4) ) );
      CHECK_THAT(  1.744701e-07, WithinRel( chunk.covariances().value()(6,5) ) );
      CHECK_THAT(  4.887436e-06, WithinRel( chunk.covariances().value()(6,6) ) );
      CHECK_THAT( -2.686310e-10, WithinRel( chunk.covariances().value()(6,7) ) );
      CHECK_THAT( -1.352565e-09, WithinRel( chunk.covariances().value()(7,0) ) );
      CHECK_THAT( -9.048060e-10, WithinRel( chunk.covariances().value()(7,1) ) );
      CHECK_THAT( -2.642949e-09, WithinRel( chunk.covariances().value()(7,2) ) );
      CHECK_THAT(  3.336860e-10, WithinRel( chunk.covariances().value()(7,3) ) );
      CHECK_THAT( -1.127960e-09, WithinRel( chunk.covariances().value()(7,4) ) );
      CHECK_THAT( -2.394143e-09, WithinRel( chunk.covariances().value()(7,5) ) );
      CHECK_THAT( -2.686310e-10, WithinRel( chunk.covariances().value()(7,6) ) );
      CHECK_THAT(  3.280511e-09, WithinRel( chunk.covariances().value()(7,7) ) );
    } // THEN

    chunk.calculateStandardDeviations();

    THEN( "Standard deviations can be calculated" ) {

      CHECK( std::nullopt != chunk.standardDeviations() );

      CHECK( 8 == chunk.standardDeviations().value().size() );
      CHECK_THAT( 5.78834777807968e-04, WithinRel( chunk.standardDeviations().value()[0] ) );
      CHECK_THAT( 1.17932099107919e-03, WithinRel( chunk.standardDeviations().value()[1] ) );
      CHECK_THAT( 2.03289547198079e-03, WithinRel( chunk.standardDeviations().value()[2] ) );
      CHECK_THAT( 1.93069935515605e-05, WithinRel( chunk.standardDeviations().value()[3] ) );
      CHECK_THAT( 5.28473935024236e-04, WithinRel( chunk.standardDeviations().value()[4] ) );
      CHECK_THAT( 9.67719122473045e-04, WithinRel( chunk.standardDeviations().value()[5] ) );
      CHECK_THAT( 2.21075462229529e-03, WithinRel( chunk.standardDeviations().value()[6] ) );
      CHECK_THAT( 5.72757453028767e-05, WithinRel( chunk.standardDeviations().value()[7] ) );
    } // THEN

    chunk.calculateCorrelations();

    THEN( "Correlations can be calculated" ) {

      CHECK( std::nullopt != chunk.correlations() );

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
    } // THEN

    chunk.calculateEigenvalues();

    THEN( "Eigenvalues can be calculated" ) {

      CHECK( std::nullopt != chunk.eigenvalues() );

      CHECK( 8 == chunk.eigenvalues().value().size() );
      CHECK_THAT( -2.39076849693257e-07, WithinRel( chunk.eigenvalues().value()[0] ) );
      CHECK_THAT(  3.43367202411662e-10, WithinRel( chunk.eigenvalues().value()[1] ) );
      CHECK_THAT(  3.31256655183549e-09, WithinRel( chunk.eigenvalues().value()[2] ) );
      CHECK_THAT(  1.08751047007600e-07, WithinRel( chunk.eigenvalues().value()[3] ) );
      CHECK_THAT(  5.09348096171567e-07, WithinRel( chunk.eigenvalues().value()[4] ) );
      CHECK_THAT(  8.72998692347036e-07, WithinRel( chunk.eigenvalues().value()[5] ) );
      CHECK_THAT(  2.77607998044769e-06, WithinRel( chunk.eigenvalues().value()[6] ) );
      CHECK_THAT(  7.93360907096512e-06, WithinRel( chunk.eigenvalues().value()[7] ) );

    } // THEN
  } // GIVEN
} // SCENARIO