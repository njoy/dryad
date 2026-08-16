// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/covariance/createAngularDistributionCovarianceMatrix.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "createAngularDistributionCovarianceMatrix" ) {

  GIVEN( "a GENDF MF34 section" ) {

    using GTape = njoy::ENDFtk::tree::GTape;
    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.angular.gendf" );
    auto material = tape.materials().front();
    auto section = material.file( 34 ).section( 251 ).parse< 34 >();

    WHEN( "constructing angular distribution covariance matrix" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      auto frame = ReferenceFrame::Laboratory;
      std::vector< double > boundaries = {

        1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0, 8.320000e+0,
        2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2, 1.235000e+3, 3.350000e+3,
        9.120000e+3, 2.480000e+4, 6.760000e+4, 1.840000e+5, 3.030000e+5, 5.000000e+5,
        8.230000e+5, 1.353000e+6, 1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6,
        6.070000e+6, 7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
        1.700000e+7
      };

      auto chunk = gendf::read::covariance::createAngularDistributionCovarianceMatrix(
                      projectile, target, boundaries, frame, section );

      THEN( "angular distribution covaraince matrix can be created and members tested" ) {

        CHECK( 1 == chunk.size() );

        CHECK( chunk[0].rowMetadata() == chunk[0].columnMetadata() );
        CHECK( 1 == chunk[0].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[0].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[0].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[0].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[0].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[0].rowMetadata().moments().size() );
        CHECK( 1 == chunk[0].rowMetadata().moments()[0] );
        CHECK( true == chunk[0].isRelativeMatrix() );
        CHECK( false == chunk[0].isAbsoluteMatrix() );
        CHECK( false == chunk[0].isOffDiagonal() );
        CHECK( true == chunk[0].isOnDiagonal() );
        CHECK( 30 == chunk[0].covariances().rows() );
        CHECK( 30 == chunk[0].covariances().cols() );
        CHECK_THAT(  0.         , WithinRel( chunk[0].covariances()( 0, 0) ) );
        CHECK_THAT(  0.         , WithinRel( chunk[0].covariances()( 0,29) ) );
        CHECK_THAT(  0.         , WithinRel( chunk[0].covariances()(29, 0) ) );
        CHECK_THAT(  8.028195e-4, WithinRel( chunk[0].covariances()(29,29) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO