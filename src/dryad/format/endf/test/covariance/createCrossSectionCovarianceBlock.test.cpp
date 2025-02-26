// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/format/endf/covariance/createCrossSectionCovarianceBlock.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::ENDFtk;
using CovariancePairs = section::CovariancePairs;
using SquareMatrix = section::SquareMatrix;
using CrossSectionCovarianceBlock = covariance::CrossSectionCovarianceBlock;

SCENARIO( "createMatrix" ) {

  GIVEN( "an instance of CovariancePairs using LB=0/1 (diagonal elements)" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
    CovariancePairs covariance = std::get< CovariancePairs >( section.reactions()[0].explicitCovariances()[0] );

    WHEN( "creating a matric from the CovariancePairs instance" ) {

      id::ParticleID projectile = "n";
      id::ParticleID target = "F19";
      id::ReactionID reaction = "4";

      auto chunk = format::endf::covariance::createCrossSectionCovarianceBlock(
                     projectile, target, reaction, covariance );

      THEN( "a matrix can be created and members can be tested" ) {

        CHECK( "n" == chunk.rowMetadata().projectileIdentifier() );
        CHECK( "F19" == chunk.rowMetadata().targetIdentifier() );
        CHECK( "4" == chunk.rowMetadata().reactionIdentifier() );
        CHECK( 9 == chunk.rowMetadata().energies().size() );
        CHECK( 8 == chunk.rowMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.158400e+5, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 2.074600e+5, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 3.000000e+5, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 4.500000e+5, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 6.000000e+5, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 1.100000e+6, WithinRel( chunk.rowMetadata().energies()[6] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( chunk.rowMetadata().energies()[7] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[8] ) );

        CHECK( "n" == chunk.columnMetadata().projectileIdentifier() );
        CHECK( "F19" == chunk.columnMetadata().targetIdentifier() );
        CHECK( "4" == chunk.columnMetadata().reactionIdentifier() );
        CHECK( 9 == chunk.columnMetadata().energies().size() );
        CHECK( 8 == chunk.columnMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.158400e+5, WithinRel( chunk.columnMetadata().energies()[1] ) );
        CHECK_THAT( 2.074600e+5, WithinRel( chunk.columnMetadata().energies()[2] ) );
        CHECK_THAT( 3.000000e+5, WithinRel( chunk.columnMetadata().energies()[3] ) );
        CHECK_THAT( 4.500000e+5, WithinRel( chunk.columnMetadata().energies()[4] ) );
        CHECK_THAT( 6.000000e+5, WithinRel( chunk.columnMetadata().energies()[5] ) );
        CHECK_THAT( 1.100000e+6, WithinRel( chunk.columnMetadata().energies()[6] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( chunk.columnMetadata().energies()[7] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.columnMetadata().energies()[8] ) );

        CHECK( true == chunk.isRelativeBlock() );
        CHECK( false == chunk.isOffDiagonalBlock() );
        CHECK( true == chunk.isDiagonalBlock() );

        CHECK( std::nullopt != chunk.covariances() );
        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 8 == chunk.covariances().value().rows() );
        CHECK( 8 ==chunk.covariances().value().cols() );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,7) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,0) ) );
        CHECK_THAT( 4.000000e-2, WithinRel( chunk.covariances().value()(1,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,7) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,1) ) );
        CHECK_THAT( 6.250000e-2, WithinRel( chunk.covariances().value()(2,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,7) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,2) ) );
        CHECK_THAT( 4.000000e-2, WithinRel( chunk.covariances().value()(3,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,7) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,3) ) );
        CHECK_THAT( 2.250000e-2, WithinRel( chunk.covariances().value()(4,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,7) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,4) ) );
        CHECK_THAT( 4.000000e-2, WithinRel( chunk.covariances().value()(5,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,7) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,5) ) );
        CHECK_THAT( 2.250000e-2, WithinRel( chunk.covariances().value()(6,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,7) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,5) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,6) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,7) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an instance of SquareMatrix that is symmetric" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
    SquareMatrix covariance = std::get< SquareMatrix >( section.reactions()[0].explicitCovariances()[1] );

    WHEN( "constructing a diagonal CovarianceBlock from a SquareMatrix" ) {

      id::ParticleID projectile = "n";
      id::ParticleID target = "F19";
      id::ReactionID reaction = "4";

      auto chunk = format::endf::covariance::createCrossSectionCovarianceBlock(
        projectile, target, reaction, covariance );

      THEN( "a matrix can be created and members can be tested" ) {

        CHECK( "n" == chunk.rowMetadata().projectileIdentifier() );
        CHECK( "F19" == chunk.rowMetadata().targetIdentifier() );
        CHECK( "4" == chunk.rowMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.rowMetadata().energies().size() );
        CHECK( 6 == chunk.rowMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 3.000000e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 6.000000e+6, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[6] ) );

        CHECK( "n" == chunk.columnMetadata().projectileIdentifier() );
        CHECK( "F19" == chunk.columnMetadata().targetIdentifier() );
        CHECK( "4" == chunk.columnMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.columnMetadata().energies().size() );
        CHECK( 6 == chunk.columnMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( chunk.columnMetadata().energies()[1] ) );
        CHECK_THAT( 3.000000e+6, WithinRel( chunk.columnMetadata().energies()[2] ) );
        CHECK_THAT( 6.000000e+6, WithinRel( chunk.columnMetadata().energies()[3] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( chunk.columnMetadata().energies()[4] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.columnMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.columnMetadata().energies()[6] ) );

        CHECK( true == chunk.isRelativeBlock() );
        CHECK( false == chunk.isOffDiagonalBlock() );
        CHECK( true == chunk.isDiagonalBlock() );

        CHECK( std::nullopt != chunk.covariances() );
        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 6 ==chunk.covariances().value().rows() );
        CHECK( 6 ==chunk.covariances().value().cols() );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,5) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,0) ) );
        CHECK_THAT( 1.251800e-2, WithinRel( chunk.covariances().value()(1,1) ) );
        CHECK_THAT( 1.372900e-2, WithinRel( chunk.covariances().value()(1,2) ) );
        CHECK_THAT( 3.462100e-3, WithinRel( chunk.covariances().value()(1,3) ) );
        CHECK_THAT( 4.176900e-3, WithinRel( chunk.covariances().value()(1,4) ) );
        CHECK_THAT( 3.404000e-3, WithinRel( chunk.covariances().value()(1,5) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,0) ) );
        CHECK_THAT( 1.372900e-2, WithinRel( chunk.covariances().value()(2,1) ) );
        CHECK_THAT( 1.557300e-2, WithinRel( chunk.covariances().value()(2,2) ) );
        CHECK_THAT( 5.634300e-3, WithinRel( chunk.covariances().value()(2,3) ) );
        CHECK_THAT( 5.288200e-3, WithinRel( chunk.covariances().value()(2,4) ) );
        CHECK_THAT( 3.863500e-3, WithinRel( chunk.covariances().value()(2,5) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,0) ) );
        CHECK_THAT( 3.462100e-3, WithinRel( chunk.covariances().value()(3,1) ) );
        CHECK_THAT( 5.634300e-3, WithinRel( chunk.covariances().value()(3,2) ) );
        CHECK_THAT( 8.970100e-3, WithinRel( chunk.covariances().value()(3,3) ) );
        CHECK_THAT( 4.898600e-3, WithinRel( chunk.covariances().value()(3,4) ) );
        CHECK_THAT( 1.896700e-3, WithinRel( chunk.covariances().value()(3,5) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,0) ) );
        CHECK_THAT( 4.176900e-3, WithinRel( chunk.covariances().value()(4,1) ) );
        CHECK_THAT( 5.288200e-3, WithinRel( chunk.covariances().value()(4,2) ) );
        CHECK_THAT( 4.898600e-3, WithinRel( chunk.covariances().value()(4,3) ) );
        CHECK_THAT( 3.694600e-3, WithinRel( chunk.covariances().value()(4,4) ) );
        CHECK_THAT( 1.726800e-3, WithinRel( chunk.covariances().value()(4,5) ) );

        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,0) ) );
        CHECK_THAT( 3.404000e-3, WithinRel( chunk.covariances().value()(5,1) ) );
        CHECK_THAT( 3.863500e-3, WithinRel( chunk.covariances().value()(5,2) ) );
        CHECK_THAT( 1.896700e-3, WithinRel( chunk.covariances().value()(5,3) ) );
        CHECK_THAT( 1.726800e-3, WithinRel( chunk.covariances().value()(5,4) ) );
        CHECK_THAT( 1.144800e-3, WithinRel( chunk.covariances().value()(5,5) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an instance of SquareMatrix that is asymmetric" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
    SquareMatrix covariance = std::get< SquareMatrix >( section.reactions()[1].explicitCovariances()[0] );

    WHEN( "constructing a diagonal CovarianceBlock from a SquareMatrix" ) {

      id::ParticleID rowProjectile = "n";
      id::ParticleID rowTarget = "F19";
      id::ReactionID rowReaction = "4";
      id::ParticleID columnProjectile = "n";
      id::ParticleID columnTarget = "F19";
      id::ReactionID columnReaction = "16";

      auto chunk = format::endf::covariance::createCrossSectionCovarianceBlock(
        rowProjectile, rowTarget, rowReaction,
        columnProjectile, columnTarget, columnReaction,
        covariance );

      THEN( "a matrix can be created and members can be tested" ) {

        CHECK( "n" == chunk.rowMetadata().projectileIdentifier() );
        CHECK( "F19" == chunk.rowMetadata().targetIdentifier() );
        CHECK( "4" == chunk.rowMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.rowMetadata().energies().size() );
        CHECK( 6 == chunk.rowMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[6] ) );

        CHECK( "n" == chunk.columnMetadata().projectileIdentifier() );
        CHECK( "F19" == chunk.columnMetadata().targetIdentifier() );
        CHECK( "16" == chunk.columnMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.columnMetadata().energies().size() );
        CHECK( 6 == chunk.columnMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( chunk.columnMetadata().energies()[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.columnMetadata().energies()[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.columnMetadata().energies()[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.columnMetadata().energies()[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.columnMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.columnMetadata().energies()[6] ) );

        CHECK( true == chunk.isRelativeBlock() );
        CHECK( true == chunk.isOffDiagonalBlock() );
        CHECK( false == chunk.isDiagonalBlock() );

        CHECK( std::nullopt != chunk.covariances() );
        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 6 ==chunk.covariances().value().rows() );
        CHECK( 6 ==chunk.covariances().value().cols() );
        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(0,0) ) );
        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(0,1) ) );
        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(0,2) ) );
        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(0,3) ) );
        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(0,4) ) );
        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(0,5) ) );

        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(1,0) ) );
        CHECK_THAT( -2.732300e-3, WithinRel( chunk.covariances().value()(1,1) ) );
        CHECK_THAT( -8.431200e-4, WithinRel( chunk.covariances().value()(1,2) ) );
        CHECK_THAT(  1.625000e-3, WithinRel( chunk.covariances().value()(1,3) ) );
        CHECK_THAT(  2.647600e-3, WithinRel( chunk.covariances().value()(1,4) ) );
        CHECK_THAT(  4.939500e-3, WithinRel( chunk.covariances().value()(1,5) ) );

        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(2,0) ) );
        CHECK_THAT( -1.625700e-3, WithinRel( chunk.covariances().value()(2,1) ) );
        CHECK_THAT( -3.558100e-4, WithinRel( chunk.covariances().value()(2,2) ) );
        CHECK_THAT(  1.459800e-3, WithinRel( chunk.covariances().value()(2,3) ) );
        CHECK_THAT(  2.437400e-3, WithinRel( chunk.covariances().value()(2,4) ) );
        CHECK_THAT(  3.772000e-3, WithinRel( chunk.covariances().value()(2,5) ) );

        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(3,0) ) );
        CHECK_THAT( -2.314700e-4, WithinRel( chunk.covariances().value()(3,1) ) );
        CHECK_THAT(  3.051500e-4, WithinRel( chunk.covariances().value()(3,2) ) );
        CHECK_THAT(  1.292200e-3, WithinRel( chunk.covariances().value()(3,3) ) );
        CHECK_THAT(  2.152300e-3, WithinRel( chunk.covariances().value()(3,4) ) );
        CHECK_THAT(  2.538300e-3, WithinRel( chunk.covariances().value()(3,5) ) );

        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(4,0) ) );
        CHECK_THAT(  3.229600e-4, WithinRel( chunk.covariances().value()(4,1) ) );
        CHECK_THAT(  6.356200e-4, WithinRel( chunk.covariances().value()(4,2) ) );
        CHECK_THAT(  1.308700e-3, WithinRel( chunk.covariances().value()(4,3) ) );
        CHECK_THAT(  1.986300e-3, WithinRel( chunk.covariances().value()(4,4) ) );
        CHECK_THAT(  2.439300e-3, WithinRel( chunk.covariances().value()(4,5) ) );

        CHECK_THAT(  0., WithinRel( chunk.covariances().value()(5,0) ) );
        CHECK_THAT(  4.981700e-4, WithinRel( chunk.covariances().value()(5,1) ) );
        CHECK_THAT(  8.811700e-4, WithinRel( chunk.covariances().value()(5,2) ) );
        CHECK_THAT(  1.559200e-3, WithinRel( chunk.covariances().value()(5,3) ) );
        CHECK_THAT(  2.135100e-3, WithinRel( chunk.covariances().value()(5,4) ) );
        CHECK_THAT(  2.953900e-3, WithinRel( chunk.covariances().value()(5,5) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
