// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/covariance/createCrossSectionCovarianceMatrix.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;
using namespace njoy::ENDFtk;

SCENARIO( "createCrossSectionCovarianceMatrix" ) {

  GIVEN( "a GENDF MF33 section" ) {

    using GTape = njoy::ENDFtk::tree::GTape;
    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.gendf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 2 ).parse< 33 >();

    WHEN( "constructing covariance matrices" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      bool relative = true;
      std::vector< double > boundaries = {

        1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0, 8.320000e+0,
        2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2, 1.235000e+3, 3.350000e+3,
        9.120000e+3, 2.480000e+4, 6.760000e+4, 1.840000e+5, 3.030000e+5, 5.000000e+5,
        8.230000e+5, 1.353000e+6, 1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6,
        6.070000e+6, 7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
        1.700000e+7
      };

      auto chunk = gendf::read::covariance::createCrossSectionCovarianceMatrix(
                     projectile, target, boundaries, relative, section );

      THEN( "covariance matrices can be created and members can be tested" ) {

        CHECK( 10 == chunk.size() );

        CHECK( chunk[0].rowMetadata() == chunk[0].columnMetadata() );
        CHECK( 1 == chunk[0].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[0].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[0].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[0].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[0].rowMetadata().energies()[30] ) );
        CHECK( false == chunk[0].hasVarianceScaling() );
        CHECK( true == chunk[0].isRelativeMatrix() );
        CHECK( false == chunk[0].isAbsoluteMatrix() );
        CHECK( false == chunk[0].isOffDiagonal() );
        CHECK( true == chunk[0].isOnDiagonal() );
        CHECK( 30 == chunk[0].covariances().rows() );
        CHECK( 30 ==chunk[0].covariances().cols() );

        CHECK( chunk[1].rowMetadata() != chunk[1].columnMetadata() );
        CHECK( 1 == chunk[1].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[1].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[1].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[1].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[1].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[1].columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n(t)" ) == chunk[1].columnMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[1].columnMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[1].columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[1].columnMetadata().energies()[30] ) );
        CHECK( false == chunk[1].hasVarianceScaling() );
        CHECK( true == chunk[1].isRelativeMatrix() );
        CHECK( false == chunk[1].isAbsoluteMatrix() );
        CHECK( true == chunk[1].isOffDiagonal() );
        CHECK( false == chunk[1].isOnDiagonal() );
        CHECK( 30 == chunk[1].covariances().rows() );
        CHECK( 30 ==chunk[1].covariances().cols() );

        CHECK( chunk[2].rowMetadata() != chunk[2].columnMetadata() );
        CHECK( 1 == chunk[2].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[2].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[2].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[2].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[2].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[2].columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->anything" ) == chunk[2].columnMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[2].columnMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[2].columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[2].columnMetadata().energies()[30] ) );
        CHECK( false == chunk[2].hasVarianceScaling() );
        CHECK( true == chunk[2].isRelativeMatrix() );
        CHECK( false == chunk[2].isAbsoluteMatrix() );
        CHECK( true == chunk[2].isOffDiagonal() );
        CHECK( false == chunk[2].isOnDiagonal() );
        CHECK( 30 == chunk[2].covariances().rows() );
        CHECK( 30 ==chunk[2].covariances().cols() );

        CHECK( chunk[3].rowMetadata() != chunk[3].columnMetadata() );
        CHECK( 1 == chunk[3].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[3].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[3].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[3].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[3].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[3].columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->2n(t)" ) == chunk[3].columnMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[3].columnMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[3].columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[3].columnMetadata().energies()[30] ) );
        CHECK( false == chunk[3].hasVarianceScaling() );
        CHECK( true == chunk[3].isRelativeMatrix() );
        CHECK( false == chunk[3].isAbsoluteMatrix() );
        CHECK( true == chunk[3].isOffDiagonal() );
        CHECK( false == chunk[3].isOnDiagonal() );
        CHECK( 30 == chunk[3].covariances().rows() );
        CHECK( 30 ==chunk[3].covariances().cols() );

        CHECK( chunk[4].rowMetadata() != chunk[4].columnMetadata() );
        CHECK( 1 == chunk[4].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[4].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[4].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[4].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[4].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[4].columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->3n(t)" ) == chunk[4].columnMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[4].columnMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[4].columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[4].columnMetadata().energies()[30] ) );
        CHECK( false == chunk[4].hasVarianceScaling() );
        CHECK( true == chunk[4].isRelativeMatrix() );
        CHECK( false == chunk[4].isAbsoluteMatrix() );
        CHECK( true == chunk[4].isOffDiagonal() );
        CHECK( false == chunk[4].isOnDiagonal() );
        CHECK( 30 == chunk[4].covariances().rows() );
        CHECK( 30 ==chunk[4].covariances().cols() );

        CHECK( chunk[5].rowMetadata() != chunk[5].columnMetadata() );
        CHECK( 1 == chunk[5].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[5].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[5].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[5].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[5].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[5].columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->fission" ) == chunk[5].columnMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[5].columnMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[5].columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[5].columnMetadata().energies()[30] ) );
        CHECK( false == chunk[5].hasVarianceScaling() );
        CHECK( true == chunk[5].isRelativeMatrix() );
        CHECK( false == chunk[5].isAbsoluteMatrix() );
        CHECK( true == chunk[5].isOffDiagonal() );
        CHECK( false == chunk[5].isOnDiagonal() );
        CHECK( 30 == chunk[5].covariances().rows() );
        CHECK( 30 ==chunk[5].covariances().cols() );

        CHECK( chunk[6].rowMetadata() != chunk[6].columnMetadata() );
        CHECK( 1 == chunk[6].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[6].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[6].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[6].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[6].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[6].columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n(1)" ) == chunk[6].columnMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[6].columnMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[6].columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[6].columnMetadata().energies()[30] ) );
        CHECK( false == chunk[6].hasVarianceScaling() );
        CHECK( true == chunk[6].isRelativeMatrix() );
        CHECK( false == chunk[6].isAbsoluteMatrix() );
        CHECK( true == chunk[6].isOffDiagonal() );
        CHECK( false == chunk[6].isOnDiagonal() );
        CHECK( 30 == chunk[6].covariances().rows() );
        CHECK( 30 ==chunk[6].covariances().cols() );

        CHECK( chunk[7].rowMetadata() != chunk[7].columnMetadata() );
        CHECK( 1 == chunk[7].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[7].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[7].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[7].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[7].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[7].columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->capture" ) == chunk[7].columnMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[7].columnMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[7].columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[7].columnMetadata().energies()[30] ) );
        CHECK( false == chunk[7].hasVarianceScaling() );
        CHECK( true == chunk[7].isRelativeMatrix() );
        CHECK( false == chunk[7].isAbsoluteMatrix() );
        CHECK( true == chunk[7].isOffDiagonal() );
        CHECK( false == chunk[7].isOnDiagonal() );
        CHECK( 30 == chunk[7].covariances().rows() );
        CHECK( 30 ==chunk[7].covariances().cols() );

        CHECK( chunk[8].rowMetadata() != chunk[8].columnMetadata() );
        CHECK( 1 == chunk[8].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[8].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[8].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[8].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[8].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[8].columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->lumped1" ) == chunk[8].columnMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[8].columnMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[8].columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[8].columnMetadata().energies()[30] ) );
        CHECK( false == chunk[8].hasVarianceScaling() );
        CHECK( true == chunk[8].isRelativeMatrix() );
        CHECK( false == chunk[8].isAbsoluteMatrix() );
        CHECK( true == chunk[8].isOffDiagonal() );
        CHECK( false == chunk[8].isOnDiagonal() );
        CHECK( 30 == chunk[8].covariances().rows() );
        CHECK( 30 ==chunk[8].covariances().cols() );

        CHECK( chunk[9].rowMetadata() != chunk[9].columnMetadata() );
        CHECK( 1 == chunk[9].rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk[9].rowMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[9].rowMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[9].rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[9].rowMetadata().energies()[30] ) );
        CHECK( 1 == chunk[9].columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,U235->lumped2" ) == chunk[9].columnMetadata().reactionIdentifiers()[0] );
        CHECK( 31 == chunk[9].columnMetadata().energies().size() );
        CHECK_THAT( 1.390000e-4, WithinRel( chunk[9].columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk[9].columnMetadata().energies()[30] ) );
        CHECK( false == chunk[9].hasVarianceScaling() );
        CHECK( true == chunk[9].isRelativeMatrix() );
        CHECK( false == chunk[9].isAbsoluteMatrix() );
        CHECK( true == chunk[9].isOffDiagonal() );
        CHECK( false == chunk[9].isOnDiagonal() );
        CHECK( 30 == chunk[9].covariances().rows() );
        CHECK( 30 ==chunk[9].covariances().cols() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
