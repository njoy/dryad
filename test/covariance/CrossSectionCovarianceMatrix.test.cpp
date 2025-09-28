// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/covariance/CrossSectionCovarianceBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::covariance;

SCENARIO( "CrossSectionCovarianceBlock" ) {

  GIVEN( "valid covariance data for a diagonal CrossSectionCovarianceBlock without "
         "variance scaling information" ) {

    id::ParticleID projectile( "n" );
    id::ParticleID target( "U235" );
    id::ReactionID reaction( "n,U235->n,U235" );
    std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

    Matrix< double > matrix( 3, 3 );
    matrix << 1., 2., 3.,
              2., 4., 6.,
              3., 6., 9.;

    CrossSectionCovarianceBlock chunk( std::move( projectile ), std::move( target ),
                                       std::move( reaction ), std::move( energies ),
                                       std::move( matrix ) );

    THEN( "a CrossSectionCovarianceBlock can be constructed and members can be tested" ) {

      CHECK( id::ParticleID( "n" ) == chunk.rowMetadata().projectileIdentifier() );
      CHECK( id::ParticleID( "U235" ) == chunk.rowMetadata().targetIdentifier() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifier() );
      CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK( 3 == chunk.rowMetadata().numberGroups() );
      CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );

      CHECK( id::ParticleID( "n" ) == chunk.columnMetadata().projectileIdentifier() );
      CHECK( id::ParticleID( "U235" ) == chunk.columnMetadata().targetIdentifier() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.columnMetadata().reactionIdentifier() );
      CHECK( 4 == chunk.columnMetadata().energies().size() );
      CHECK( 3 == chunk.columnMetadata().numberGroups() );
      CHECK_THAT( 1e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.columnMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.columnMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.columnMetadata().energies()[3] ) );

      CHECK( false == chunk.hasVarianceScaling() );
      CHECK( std::nullopt == chunk.varianceScaling() );

      CHECK( true == chunk.isRelativeBlock() );
      CHECK( false == chunk.isAbsoluteBlock() );
      CHECK( false == chunk.isOffDiagonalBlock() );
      CHECK( true == chunk.isDiagonalBlock() );

      CHECK( std::nullopt != chunk.covariances() );
      CHECK( std::nullopt == chunk.standardDeviations() );
      CHECK( std::nullopt == chunk.correlations() );
      CHECK( std::nullopt == chunk.eigenvalues() );

      CHECK( 3 == chunk.covariances().value().rows() );
      CHECK( 3 == chunk.covariances().value().cols() );
      CHECK( 1. == chunk.covariances().value()(0,0) );
      CHECK( 2. == chunk.covariances().value()(0,1) );
      CHECK( 3. == chunk.covariances().value()(0,2) );
      CHECK( 2. == chunk.covariances().value()(1,0) );
      CHECK( 4. == chunk.covariances().value()(1,1) );
      CHECK( 6. == chunk.covariances().value()(1,2) );
      CHECK( 3. == chunk.covariances().value()(2,0) );
      CHECK( 6. == chunk.covariances().value()(2,1) );
      CHECK( 9. == chunk.covariances().value()(2,2) );
    } // THEN

    chunk.calculateStandardDeviations();

    THEN( "Standard deviations can be calculated" ) {

      CHECK( std::nullopt != chunk.standardDeviations() );

      CHECK( 3 == chunk.standardDeviations().value().size() );
      CHECK_THAT( 1., WithinRel( chunk.standardDeviations().value()[0] ) );
      CHECK_THAT( 2., WithinRel( chunk.standardDeviations().value()[1] ) );
      CHECK_THAT( 3., WithinRel( chunk.standardDeviations().value()[2] ) );
    } // THEN

    chunk.calculateCorrelations();

    THEN( "Correlations can be calculated" ) {

      CHECK( std::nullopt != chunk.correlations() );

      CHECK( 3 == chunk.correlations().value().rows() );
      CHECK( 3 == chunk.correlations().value().cols() );
      CHECK( 1. == chunk.correlations().value()(0,0) );
      CHECK( 1. == chunk.correlations().value()(0,1) );
      CHECK( 1. == chunk.correlations().value()(0,2) );
      CHECK( 1. == chunk.correlations().value()(1,0) );
      CHECK( 1. == chunk.correlations().value()(1,1) );
      CHECK( 1. == chunk.correlations().value()(1,2) );
      CHECK( 1. == chunk.correlations().value()(2,0) );
      CHECK( 1. == chunk.correlations().value()(2,1) );
      CHECK( 1. == chunk.correlations().value()(2,2) );
    } // THEN

    chunk.calculateEigenvalues();

    THEN( "Eigenvalues can be calculated" ) {

      CHECK( std::nullopt != chunk.eigenvalues() );

      CHECK( 3 == chunk.eigenvalues().value().size() );
      CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[0], 1e-12 ) );
      CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[1], 1e-12 ) );
      CHECK_THAT( 14., WithinRel( chunk.eigenvalues().value()[2] ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid covariance data for a diagonal CrossSectionCovarianceBlock with "
         "variance scaling information" ) {

    id::ParticleID projectile( "n" );
    id::ParticleID target( "U235" );
    id::ReactionID reaction( "n,U235->n,U235" );
    std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

    Matrix< double > matrix( 3, 3 );
    matrix << 1., 2., 3.,
              2., 4., 6.,
              3., 6., 9.;

    bool relative = true;
    VarianceScaling scaling( ScalingType::Inverse,
                             { 1e-5, 5., 2e+7 }, { 0.001, 0.1 } );

    CrossSectionCovarianceBlock chunk( std::move( projectile ), std::move( target ),
                                       std::move( reaction ), std::move( energies ),
                                       std::move( matrix ), relative, std::move( scaling ) );

    THEN( "a CrossSectionCovarianceBlock can be constructed and members can be tested" ) {

     CHECK( id::ParticleID( "n" ) == chunk.rowMetadata().projectileIdentifier() );
     CHECK( id::ParticleID( "U235" ) == chunk.rowMetadata().targetIdentifier() );
     CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifier() );
     CHECK( 4 == chunk.rowMetadata().energies().size() );
     CHECK( 3 == chunk.rowMetadata().numberGroups() );
     CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
     CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
     CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
     CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );

     CHECK( id::ParticleID( "n" ) == chunk.columnMetadata().projectileIdentifier() );
     CHECK( id::ParticleID( "U235" ) == chunk.columnMetadata().targetIdentifier() );
     CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.columnMetadata().reactionIdentifier() );
     CHECK( 4 == chunk.columnMetadata().energies().size() );
     CHECK( 3 == chunk.columnMetadata().numberGroups() );
     CHECK_THAT( 1e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
     CHECK_THAT( 1.  , WithinRel( chunk.columnMetadata().energies()[1] ) );
     CHECK_THAT( 1e+6, WithinRel( chunk.columnMetadata().energies()[2] ) );
     CHECK_THAT( 2e+7, WithinRel( chunk.columnMetadata().energies()[3] ) );

     CHECK( true == chunk.hasVarianceScaling() );
     CHECK( std::nullopt != chunk.varianceScaling() );
     auto scaling = chunk.varianceScaling().value();
     CHECK( 2 == scaling.numberGroups() );
     CHECK( 3 == scaling.energies().size() );
     CHECK_THAT( 1e-5, WithinRel( scaling.energies()[0] ) );
     CHECK_THAT( 5.  , WithinRel( scaling.energies()[1] ) );
     CHECK_THAT( 2e+7, WithinRel( scaling.energies()[2] ) );
     CHECK( 2 == scaling.factors().size() );
     CHECK_THAT( 0.001, WithinRel( scaling.factors()[0] ) );
     CHECK_THAT( 0.1  , WithinRel( scaling.factors()[1] ) );
     CHECK( ScalingType::Inverse == scaling.type() );

     CHECK( true == chunk.isRelativeBlock() );
     CHECK( false == chunk.isAbsoluteBlock() );
     CHECK( false == chunk.isOffDiagonalBlock() );
     CHECK( true == chunk.isDiagonalBlock() );

     CHECK( std::nullopt != chunk.covariances() );
     CHECK( std::nullopt == chunk.standardDeviations() );
     CHECK( std::nullopt == chunk.correlations() );
     CHECK( std::nullopt == chunk.eigenvalues() );

     CHECK( 3 == chunk.covariances().value().rows() );
     CHECK( 3 == chunk.covariances().value().cols() );
     CHECK( 1. == chunk.covariances().value()(0,0) );
     CHECK( 2. == chunk.covariances().value()(0,1) );
     CHECK( 3. == chunk.covariances().value()(0,2) );
     CHECK( 2. == chunk.covariances().value()(1,0) );
     CHECK( 4. == chunk.covariances().value()(1,1) );
     CHECK( 6. == chunk.covariances().value()(1,2) );
     CHECK( 3. == chunk.covariances().value()(2,0) );
     CHECK( 6. == chunk.covariances().value()(2,1) );
     CHECK( 9. == chunk.covariances().value()(2,2) );
    } // THEN

    chunk.calculateStandardDeviations();

    THEN( "Standard deviations can be calculated" ) {

     CHECK( std::nullopt != chunk.standardDeviations() );

     CHECK( 3 == chunk.standardDeviations().value().size() );
     CHECK_THAT( 1., WithinRel( chunk.standardDeviations().value()[0] ) );
     CHECK_THAT( 2., WithinRel( chunk.standardDeviations().value()[1] ) );
     CHECK_THAT( 3., WithinRel( chunk.standardDeviations().value()[2] ) );
    } // THEN

    chunk.calculateCorrelations();

    THEN( "Correlations can be calculated" ) {

     CHECK( std::nullopt != chunk.correlations() );

     CHECK( 3 == chunk.correlations().value().rows() );
     CHECK( 3 == chunk.correlations().value().cols() );
     CHECK( 1. == chunk.correlations().value()(0,0) );
     CHECK( 1. == chunk.correlations().value()(0,1) );
     CHECK( 1. == chunk.correlations().value()(0,2) );
     CHECK( 1. == chunk.correlations().value()(1,0) );
     CHECK( 1. == chunk.correlations().value()(1,1) );
     CHECK( 1. == chunk.correlations().value()(1,2) );
     CHECK( 1. == chunk.correlations().value()(2,0) );
     CHECK( 1. == chunk.correlations().value()(2,1) );
     CHECK( 1. == chunk.correlations().value()(2,2) );
    } // THEN

    chunk.calculateEigenvalues();

    THEN( "Eigenvalues can be calculated" ) {

     CHECK( std::nullopt != chunk.eigenvalues() );

     CHECK( 3 == chunk.eigenvalues().value().size() );
     CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[0], 1e-12 ) );
     CHECK_THAT( 0., WithinAbs( chunk.eigenvalues().value()[1], 1e-12 ) );
     CHECK_THAT( 14., WithinRel( chunk.eigenvalues().value()[2] ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an off-diagonal CrossSectionCovarianceBlock" ) {

    id::ParticleID rowProjectile( "n" );
    id::ParticleID rowTarget( "U235" );
    id::ReactionID rowReaction( "n,U235->n,U235" );
    std::vector< double > rowEnergies = { 1e-5, 1., 1e+6, 2e+7 };
    id::ParticleID columnProjectile( "n" );
    id::ParticleID columnTarget( "U238" );
    id::ReactionID columnReaction( "n,U235->fission(t)" );
    std::vector< double > columnEnergies = { 1e-5, 2., 2e+7 };

    Matrix< double > matrix( 3, 2 );
    matrix << 1., 2.,
              2., 4.,
              3., 6.;

    CrossSectionCovarianceBlock chunk( std::move( rowProjectile ),
                                       std::move( rowTarget ),
                                       std::move( rowReaction ),
                                       std::move( rowEnergies ),
                                       std::move( columnProjectile ),
                                       std::move( columnTarget ),
                                       std::move( columnReaction ),
                                       std::move( columnEnergies ),
                                       std::move( matrix ) );

    THEN( "a CrossSectionCovarianceBlock can be constructed and members can be tested" ) {

      CHECK( id::ParticleID( "n" ) == chunk.rowMetadata().projectileIdentifier() );
      CHECK( id::ParticleID( "U235" ) == chunk.rowMetadata().targetIdentifier() );
      CHECK( id::ReactionID( "n,U235->n,U235" ) == chunk.rowMetadata().reactionIdentifier() );
       CHECK( 4 == chunk.rowMetadata().energies().size() );
      CHECK( 3 == chunk.rowMetadata().numberGroups() );
      CHECK_THAT( 1e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
      CHECK_THAT( 1.  , WithinRel( chunk.rowMetadata().energies()[1] ) );
      CHECK_THAT( 1e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );

      CHECK( id::ParticleID( "n" ) == chunk.columnMetadata().projectileIdentifier() );
      CHECK( id::ParticleID( "U238" ) == chunk.columnMetadata().targetIdentifier() );
      CHECK( id::ReactionID( "n,U235->fission(t)" ) == chunk.columnMetadata().reactionIdentifier() );
       CHECK( 3 == chunk.columnMetadata().energies().size() );
      CHECK( 2 == chunk.columnMetadata().numberGroups() );
      CHECK_THAT( 1e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
      CHECK_THAT( 2.  , WithinRel( chunk.columnMetadata().energies()[1] ) );
      CHECK_THAT( 2e+7, WithinRel( chunk.columnMetadata().energies()[2] ) );

      CHECK( std::nullopt == chunk.varianceScaling() );

      CHECK( true == chunk.isRelativeBlock() );
      CHECK( false == chunk.isAbsoluteBlock() );
      CHECK( true == chunk.isOffDiagonalBlock() );
      CHECK( false == chunk.isDiagonalBlock() );

      CHECK( std::nullopt != chunk.covariances() );
      CHECK( std::nullopt == chunk.standardDeviations() );
      CHECK( std::nullopt == chunk.correlations() );

      CHECK( 3 == chunk.covariances().value().rows() );
      CHECK( 2 == chunk.covariances().value().cols() );
      CHECK( 1. == chunk.covariances().value()(0,0) );
      CHECK( 2. == chunk.covariances().value()(0,1) );
      CHECK( 2. == chunk.covariances().value()(1,0) );
      CHECK( 4. == chunk.covariances().value()(1,1) );
      CHECK( 3. == chunk.covariances().value()(2,0) );
      CHECK( 6. == chunk.covariances().value()(2,1) );
    } // THEN

    chunk.calculateStandardDeviations();

    THEN( "Standard deviations cannot be calculated" ) {

      CHECK( std::nullopt == chunk.standardDeviations() );
    } // THEN

    std::vector< double > row = { 1., 2., 3. };
    std::vector< double > column = { 1., 2. };
    chunk.calculateCorrelations( row, column );

    THEN( "Correlations can be calculated" ) {

      CHECK( std::nullopt != chunk.correlations() );

      CHECK( 3 == chunk.correlations().value().rows() );
      CHECK( 2 == chunk.correlations().value().cols() );
      CHECK( 1. == chunk.correlations().value()(0,0) );
      CHECK( 1. == chunk.correlations().value()(0,1) );
      CHECK( 1. == chunk.correlations().value()(1,0) );
      CHECK( 1. == chunk.correlations().value()(1,1) );
      CHECK( 1. == chunk.correlations().value()(2,0) );
      CHECK( 1. == chunk.correlations().value()(2,1) );
    } // THEN

    chunk.calculateEigenvalues();

    THEN( "Eigenvalues cannot be calculated" ) {

      CHECK( std::nullopt == chunk.eigenvalues() );
    } // THEN
  } // GIVEN

  GIVEN( "invalid data for a CrossSectionCovarianceBlock" ) {

    WHEN( "the matrix is not square for a diagonal covariance block" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      id::ReactionID reaction( "n,U235->n,U235" );
      std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSectionCovarianceBlock( std::move( projectile ),
                                                   std::move( target ),
                                                   std::move( reaction ),
                                                   std::move( energies ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix is not symmetric for a diagonal covariance block" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      id::ReactionID reaction( "n,U235->n,U235" );
      std::vector< double > energies = { 1e-5, 1., 1e+6, 2e+7 };

      Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 6.,
           100000., 6., 9.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSectionCovarianceBlock( std::move( projectile ),
                                                   std::move( target ),
                                                   std::move( reaction ),
                                                   std::move( energies ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the energy boundaries "
          "for a diagonal covariance block" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      id::ReactionID reaction( "n,U235->n,U235" );
      std::vector< double > energies = { 1e-5, 1., 2e+7 };

      Matrix< double > matrix( 3, 3 );
      matrix << 1., 2., 3.,
                2., 4., 5.,
                3., 5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSectionCovarianceBlock( std::move( projectile ),
                                                   std::move( target ),
                                                   std::move( reaction ),
                                                   std::move( energies ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the energy boundaries "
          "for an off-diagonal covariance block (rows)" ) {

      id::ParticleID rowProjectile( "n" );
      id::ParticleID rowTarget( "U235" );
      id::ReactionID rowReaction( "n,U235->n,U235" );
      std::vector< double > rowEnergies = { 1e-5, 1., 2e+7 };
      id::ParticleID columnProjectile( "n" );
      id::ParticleID columnTarget( "U238" );
      id::ReactionID columnReaction( "n,U235->fission(t)" );
      std::vector< double > columnEnergies = { 1e-5, 2., 2e+7 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSectionCovarianceBlock( std::move( rowProjectile ),
                                                   std::move( rowTarget ),
                                                   std::move( rowReaction ),
                                                   std::move( rowEnergies ),
                                                   std::move( columnProjectile ),
                                                   std::move( columnTarget ),
                                                   std::move( columnReaction ),
                                                   std::move( columnEnergies ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN

    WHEN( "the matrix order is not consistent with the energy boundaries "
          "for an off-diagonal covariance block (columns)" ) {

      id::ParticleID rowProjectile( "n" );
      id::ParticleID rowTarget( "U235" );
      id::ReactionID rowReaction( "n,U235->n,U235" );
      std::vector< double > rowEnergies = { 1e-5, 1., 1e+6, 2e+7 };
      id::ParticleID columnProjectile( "n" );
      id::ParticleID columnTarget( "U238" );
      id::ReactionID columnReaction( "n,U235->fission(t)" );
      std::vector< double > columnEnergies = { 1e-5, 2e+7 };

      Matrix< double > matrix( 3, 2 );
      matrix << 1., 2.,
                3., 4.,
                5., 6.;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( CrossSectionCovarianceBlock( std::move( rowProjectile ),
                                                   std::move( rowTarget ),
                                                   std::move( rowReaction ),
                                                   std::move( rowEnergies ),
                                                   std::move( columnProjectile ),
                                                   std::move( columnTarget ),
                                                   std::move( columnReaction ),
                                                   std::move( columnEnergies ),
                                                   std::move( matrix ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO