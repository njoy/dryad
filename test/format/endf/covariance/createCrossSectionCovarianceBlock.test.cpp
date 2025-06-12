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
using ReactionBlock = section::ReactionBlock;

SCENARIO( "createCrossSectionCovarianceBlock" ) {

//  GIVEN( "an instance of CovariancePairs using LB=0/1 (diagonal elements)" ) {
//
//    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
//    auto material = tape.materials().front();
//    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
//    CovariancePairs covariance = std::get< CovariancePairs >( section.reactions()[0].explicitCovariances()[0] );
//
//    WHEN( "creating a matric from the CovariancePairs instance" ) {
//
//      id::ParticleID projectile = "n";
//      id::ParticleID target = "F19";
//      id::ReactionID reaction = "4";
//
//      auto chunk = format::endf::covariance::createCrossSectionCovarianceBlock(
//                     projectile, target, reaction, covariance );
//
//      THEN( "a matrix can be created and members can be tested" ) {
//
//        CHECK( "n" == chunk.rowMetadata().projectileIdentifier() );
//        CHECK( "F19" == chunk.rowMetadata().targetIdentifier() );
//        CHECK( "4" == chunk.rowMetadata().reactionIdentifier() );
//        CHECK( 9 == chunk.rowMetadata().energies().size() );
//        CHECK( 8 == chunk.rowMetadata().numberGroups() );
//        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
//        CHECK_THAT( 1.158400e+5, WithinRel( chunk.rowMetadata().energies()[1] ) );
//        CHECK_THAT( 2.074600e+5, WithinRel( chunk.rowMetadata().energies()[2] ) );
//        CHECK_THAT( 3.000000e+5, WithinRel( chunk.rowMetadata().energies()[3] ) );
//        CHECK_THAT( 4.500000e+5, WithinRel( chunk.rowMetadata().energies()[4] ) );
//        CHECK_THAT( 6.000000e+5, WithinRel( chunk.rowMetadata().energies()[5] ) );
//        CHECK_THAT( 1.100000e+6, WithinRel( chunk.rowMetadata().energies()[6] ) );
//        CHECK_THAT( 1.500000e+6, WithinRel( chunk.rowMetadata().energies()[7] ) );
//        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[8] ) );
//
//        CHECK( "n" == chunk.columnMetadata().projectileIdentifier() );
//        CHECK( "F19" == chunk.columnMetadata().targetIdentifier() );
//        CHECK( "4" == chunk.columnMetadata().reactionIdentifier() );
//        CHECK( 9 == chunk.columnMetadata().energies().size() );
//        CHECK( 8 == chunk.columnMetadata().numberGroups() );
//        CHECK_THAT( 1.000000e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
//        CHECK_THAT( 1.158400e+5, WithinRel( chunk.columnMetadata().energies()[1] ) );
//        CHECK_THAT( 2.074600e+5, WithinRel( chunk.columnMetadata().energies()[2] ) );
//        CHECK_THAT( 3.000000e+5, WithinRel( chunk.columnMetadata().energies()[3] ) );
//        CHECK_THAT( 4.500000e+5, WithinRel( chunk.columnMetadata().energies()[4] ) );
//        CHECK_THAT( 6.000000e+5, WithinRel( chunk.columnMetadata().energies()[5] ) );
//        CHECK_THAT( 1.100000e+6, WithinRel( chunk.columnMetadata().energies()[6] ) );
//        CHECK_THAT( 1.500000e+6, WithinRel( chunk.columnMetadata().energies()[7] ) );
//        CHECK_THAT( 2.000000e+7, WithinRel( chunk.columnMetadata().energies()[8] ) );
//
//        CHECK( true == chunk.isRelativeBlock() );
//        CHECK( false == chunk.isAbsoluteBlock() );
//        CHECK( false == chunk.isOffDiagonalBlock() );
//        CHECK( true == chunk.isDiagonalBlock() );
//
//        CHECK( std::nullopt != chunk.covariances() );
//        CHECK( std::nullopt == chunk.standardDeviations() );
//        CHECK( std::nullopt == chunk.correlations() );
//        CHECK( std::nullopt == chunk.eigenvalues() );
//
//        CHECK( 8 == chunk.covariances().value().rows() );
//        CHECK( 8 ==chunk.covariances().value().cols() );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,0) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,1) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,2) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,3) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,4) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,5) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,6) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,7) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,0) ) );
//        CHECK_THAT( 4.000000e-2, WithinRel( chunk.covariances().value()(1,1) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,2) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,3) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,4) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,5) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,6) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,7) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,0) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,1) ) );
//        CHECK_THAT( 6.250000e-2, WithinRel( chunk.covariances().value()(2,2) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,3) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,4) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,5) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,6) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,7) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,0) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,1) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,2) ) );
//        CHECK_THAT( 4.000000e-2, WithinRel( chunk.covariances().value()(3,3) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,4) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,5) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,6) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,7) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,0) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,1) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,2) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,3) ) );
//        CHECK_THAT( 2.250000e-2, WithinRel( chunk.covariances().value()(4,4) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,5) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,6) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,7) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,0) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,1) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,2) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,3) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,4) ) );
//        CHECK_THAT( 4.000000e-2, WithinRel( chunk.covariances().value()(5,5) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,6) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,7) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,0) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,1) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,2) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,3) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,4) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,5) ) );
//        CHECK_THAT( 2.250000e-2, WithinRel( chunk.covariances().value()(6,6) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(6,7) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,0) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,1) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,2) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,3) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,4) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,5) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,6) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(7,7) ) );
//      } // THEN
//    } // WHEN
//  } // GIVEN
//
//  GIVEN( "an instance of SquareMatrix that is symmetric" ) {
//
//    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
//    auto material = tape.materials().front();
//    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
//    SquareMatrix covariance = std::get< SquareMatrix >( section.reactions()[0].explicitCovariances()[1] );
//
//    WHEN( "constructing a diagonal CovarianceBlock from a SquareMatrix" ) {
//
//      id::ParticleID projectile = "n";
//      id::ParticleID target = "F19";
//      id::ReactionID reaction = "4";
//
//      auto chunk = format::endf::covariance::createCrossSectionCovarianceBlock(
//                     projectile, target, reaction, covariance );
//
//      THEN( "a matrix can be created and members can be tested" ) {
//
//        CHECK( "n" == chunk.rowMetadata().projectileIdentifier() );
//        CHECK( "F19" == chunk.rowMetadata().targetIdentifier() );
//        CHECK( "4" == chunk.rowMetadata().reactionIdentifier() );
//        CHECK( 7 == chunk.rowMetadata().energies().size() );
//        CHECK( 6 == chunk.rowMetadata().numberGroups() );
//        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
//        CHECK_THAT( 1.500000e+6, WithinRel( chunk.rowMetadata().energies()[1] ) );
//        CHECK_THAT( 3.000000e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
//        CHECK_THAT( 6.000000e+6, WithinRel( chunk.rowMetadata().energies()[3] ) );
//        CHECK_THAT( 1.000000e+7, WithinRel( chunk.rowMetadata().energies()[4] ) );
//        CHECK_THAT( 1.400000e+7, WithinRel( chunk.rowMetadata().energies()[5] ) );
//        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[6] ) );
//
//        CHECK( "n" == chunk.columnMetadata().projectileIdentifier() );
//        CHECK( "F19" == chunk.columnMetadata().targetIdentifier() );
//        CHECK( "4" == chunk.columnMetadata().reactionIdentifier() );
//        CHECK( 7 == chunk.columnMetadata().energies().size() );
//        CHECK( 6 == chunk.columnMetadata().numberGroups() );
//        CHECK_THAT( 1.000000e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
//        CHECK_THAT( 1.500000e+6, WithinRel( chunk.columnMetadata().energies()[1] ) );
//        CHECK_THAT( 3.000000e+6, WithinRel( chunk.columnMetadata().energies()[2] ) );
//        CHECK_THAT( 6.000000e+6, WithinRel( chunk.columnMetadata().energies()[3] ) );
//        CHECK_THAT( 1.000000e+7, WithinRel( chunk.columnMetadata().energies()[4] ) );
//        CHECK_THAT( 1.400000e+7, WithinRel( chunk.columnMetadata().energies()[5] ) );
//        CHECK_THAT( 2.000000e+7, WithinRel( chunk.columnMetadata().energies()[6] ) );
//
//        CHECK( true == chunk.isRelativeBlock() );
//        CHECK( false == chunk.isAbsoluteBlock() );
//        CHECK( false == chunk.isOffDiagonalBlock() );
//        CHECK( true == chunk.isDiagonalBlock() );
//
//        CHECK( std::nullopt != chunk.covariances() );
//        CHECK( std::nullopt == chunk.standardDeviations() );
//        CHECK( std::nullopt == chunk.correlations() );
//        CHECK( std::nullopt == chunk.eigenvalues() );
//
//        CHECK( 6 ==chunk.covariances().value().rows() );
//        CHECK( 6 ==chunk.covariances().value().cols() );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,0) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,1) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,2) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,3) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,4) ) );
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,5) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(1,0) ) );
//        CHECK_THAT( 1.251800e-2, WithinRel( chunk.covariances().value()(1,1) ) );
//        CHECK_THAT( 1.372900e-2, WithinRel( chunk.covariances().value()(1,2) ) );
//        CHECK_THAT( 3.462100e-3, WithinRel( chunk.covariances().value()(1,3) ) );
//        CHECK_THAT( 4.176900e-3, WithinRel( chunk.covariances().value()(1,4) ) );
//        CHECK_THAT( 3.404000e-3, WithinRel( chunk.covariances().value()(1,5) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(2,0) ) );
//        CHECK_THAT( 1.372900e-2, WithinRel( chunk.covariances().value()(2,1) ) );
//        CHECK_THAT( 1.557300e-2, WithinRel( chunk.covariances().value()(2,2) ) );
//        CHECK_THAT( 5.634300e-3, WithinRel( chunk.covariances().value()(2,3) ) );
//        CHECK_THAT( 5.288200e-3, WithinRel( chunk.covariances().value()(2,4) ) );
//        CHECK_THAT( 3.863500e-3, WithinRel( chunk.covariances().value()(2,5) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(3,0) ) );
//        CHECK_THAT( 3.462100e-3, WithinRel( chunk.covariances().value()(3,1) ) );
//        CHECK_THAT( 5.634300e-3, WithinRel( chunk.covariances().value()(3,2) ) );
//        CHECK_THAT( 8.970100e-3, WithinRel( chunk.covariances().value()(3,3) ) );
//        CHECK_THAT( 4.898600e-3, WithinRel( chunk.covariances().value()(3,4) ) );
//        CHECK_THAT( 1.896700e-3, WithinRel( chunk.covariances().value()(3,5) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(4,0) ) );
//        CHECK_THAT( 4.176900e-3, WithinRel( chunk.covariances().value()(4,1) ) );
//        CHECK_THAT( 5.288200e-3, WithinRel( chunk.covariances().value()(4,2) ) );
//        CHECK_THAT( 4.898600e-3, WithinRel( chunk.covariances().value()(4,3) ) );
//        CHECK_THAT( 3.694600e-3, WithinRel( chunk.covariances().value()(4,4) ) );
//        CHECK_THAT( 1.726800e-3, WithinRel( chunk.covariances().value()(4,5) ) );
//
//        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(5,0) ) );
//        CHECK_THAT( 3.404000e-3, WithinRel( chunk.covariances().value()(5,1) ) );
//        CHECK_THAT( 3.863500e-3, WithinRel( chunk.covariances().value()(5,2) ) );
//        CHECK_THAT( 1.896700e-3, WithinRel( chunk.covariances().value()(5,3) ) );
//        CHECK_THAT( 1.726800e-3, WithinRel( chunk.covariances().value()(5,4) ) );
//        CHECK_THAT( 1.144800e-3, WithinRel( chunk.covariances().value()(5,5) ) );
//      } // THEN
//    } // WHEN
//  } // GIVEN

  GIVEN( "an instance of an off-diagonal ReactionBlock with a single symmetric "
         "SquareMatrix and variance scaling information" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 16 ).parse< 33 >();
    ReactionBlock covariance = section.reactions()[0];

    WHEN( "constructing a CovarianceBlock" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "F19" );
      id::ReactionID reaction( "16" );

      auto chunk = format::endf::covariance::createCrossSectionCovarianceBlock(
                     projectile, target, reaction, covariance );

      THEN( "a CovarianceBlock can be created and members can be tested" ) {

        CHECK( id::ParticleID( "n" ) == chunk.rowMetadata().projectileIdentifier() );
        CHECK( id::ParticleID( "F19" ) == chunk.rowMetadata().targetIdentifier() );
        CHECK( id::ReactionID( "16" ) == chunk.rowMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.rowMetadata().energies().size() );
        CHECK( 6 == chunk.rowMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[6] ) );

        CHECK( id::ParticleID( "n" ) == chunk.columnMetadata().projectileIdentifier() );
        CHECK( id::ParticleID( "F19" ) == chunk.columnMetadata().targetIdentifier() );
        CHECK( id::ReactionID( "16" ) == chunk.columnMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.columnMetadata().energies().size() );
        CHECK( 6 == chunk.columnMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( chunk.columnMetadata().energies()[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.columnMetadata().energies()[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.columnMetadata().energies()[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.columnMetadata().energies()[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.columnMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.columnMetadata().energies()[6] ) );

        CHECK( true == chunk.hasVarianceScaling() );
        CHECK( 6 == chunk.varianceScaling().value().numberGroups() );
        CHECK( 7 == chunk.varianceScaling().value().energies().size() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.varianceScaling().value().energies()[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( chunk.varianceScaling().value().energies()[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.varianceScaling().value().energies()[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.varianceScaling().value().energies()[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.varianceScaling().value().energies()[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.varianceScaling().value().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.varianceScaling().value().energies()[6] ) );
        CHECK( 6 == chunk.varianceScaling().value().factors().size() );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.varianceScaling().value().factors()[0] ) );
        CHECK_THAT( 3.27450e-12, WithinRel( chunk.varianceScaling().value().factors()[1] ) );
        CHECK_THAT( 6.83710e-10, WithinRel( chunk.varianceScaling().value().factors()[2] ) );
        CHECK_THAT( 3.147600e-9, WithinRel( chunk.varianceScaling().value().factors()[3] ) );
        CHECK_THAT( 6.996100e-9, WithinRel( chunk.varianceScaling().value().factors()[4] ) );
        CHECK_THAT( 1.354600e-8, WithinRel( chunk.varianceScaling().value().factors()[5] ) );
        CHECK( njoy::dryad::covariance::ScalingType::Inverse == chunk.varianceScaling().value().type() );

        CHECK( true == chunk.isRelativeBlock() );
        CHECK( false == chunk.isAbsoluteBlock() );
        CHECK( false == chunk.isOffDiagonalBlock() );
        CHECK( true == chunk.isDiagonalBlock() );

        CHECK( std::nullopt != chunk.covariances() );
        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 6 == chunk.covariances().value().rows() );
        CHECK( 6 ==chunk.covariances().value().cols() );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(1,0) ) );
        CHECK_THAT( 1.518700e-2, WithinRel( chunk.covariances().value()(1,1) ) );
        CHECK_THAT( 1.286200e-2, WithinRel( chunk.covariances().value()(1,2) ) );
        CHECK_THAT( 9.165500e-3, WithinRel( chunk.covariances().value()(1,3) ) );
        CHECK_THAT( 8.352600e-3, WithinRel( chunk.covariances().value()(1,4) ) );
        CHECK_THAT( 7.201700e-3, WithinRel( chunk.covariances().value()(1,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(2,0) ) );
        CHECK_THAT( 1.286200e-2, WithinRel( chunk.covariances().value()(2,1) ) );
        CHECK_THAT( 1.187400e-2, WithinRel( chunk.covariances().value()(2,2) ) );
        CHECK_THAT( 9.705600e-3, WithinRel( chunk.covariances().value()(2,3) ) );
        CHECK_THAT( 9.303000e-3, WithinRel( chunk.covariances().value()(2,4) ) );
        CHECK_THAT( 9.035000e-3, WithinRel( chunk.covariances().value()(2,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(3,0) ) );
        CHECK_THAT( 9.165500e-3, WithinRel( chunk.covariances().value()(3,1) ) );
        CHECK_THAT( 9.705600e-3, WithinRel( chunk.covariances().value()(3,2) ) );
        CHECK_THAT( 9.608200e-3, WithinRel( chunk.covariances().value()(3,3) ) );
        CHECK_THAT( 9.997800e-3, WithinRel( chunk.covariances().value()(3,4) ) );
        CHECK_THAT( 1.075800e-2, WithinRel( chunk.covariances().value()(3,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(4,0) ) );
        CHECK_THAT( 8.352600e-3, WithinRel( chunk.covariances().value()(4,1) ) );
        CHECK_THAT( 9.303000e-3, WithinRel( chunk.covariances().value()(4,2) ) );
        CHECK_THAT( 9.997800e-3, WithinRel( chunk.covariances().value()(4,3) ) );
        CHECK_THAT( 1.098800e-2, WithinRel( chunk.covariances().value()(4,4) ) );
        CHECK_THAT( 1.209200e-2, WithinRel( chunk.covariances().value()(4,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(5,0) ) );
        CHECK_THAT( 7.201700e-3, WithinRel( chunk.covariances().value()(5,1) ) );
        CHECK_THAT( 9.035000e-3, WithinRel( chunk.covariances().value()(5,2) ) );
        CHECK_THAT( 1.075800e-2, WithinRel( chunk.covariances().value()(5,3) ) );
        CHECK_THAT( 1.209200e-2, WithinRel( chunk.covariances().value()(5,4) ) );
        CHECK_THAT( 1.445200e-2, WithinRel( chunk.covariances().value()(5,5) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an instance of an off-diagonal ReactionBlock with a single symmetric "
         "SquareMatrix and without variance scaling information" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 104 ).parse< 33 >();
    ReactionBlock covariance = section.reactions()[0];

    WHEN( "constructing a CovarianceBlock" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "F19" );
      id::ReactionID reaction( "104" );

      auto chunk = format::endf::covariance::createCrossSectionCovarianceBlock(
                     projectile, target, reaction, covariance );

      THEN( "a CovarianceBlock can be created and members can be tested" ) {

        CHECK( id::ParticleID( "n" ) == chunk.rowMetadata().projectileIdentifier() );
        CHECK( id::ParticleID( "F19" ) == chunk.rowMetadata().targetIdentifier() );
        CHECK( id::ReactionID( "104" ) == chunk.rowMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.rowMetadata().energies().size() );
        CHECK( 6 == chunk.rowMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 6.074200e+6, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 8.000000e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 1.500000e+7, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[6] ) );

        CHECK( id::ParticleID( "n" ) == chunk.columnMetadata().projectileIdentifier() );
        CHECK( id::ParticleID( "F19" ) == chunk.columnMetadata().targetIdentifier() );
        CHECK( id::ReactionID( "104" ) == chunk.columnMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.columnMetadata().energies().size() );
        CHECK( 6 == chunk.columnMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
        CHECK_THAT( 6.074200e+6, WithinRel( chunk.columnMetadata().energies()[1] ) );
        CHECK_THAT( 8.000000e+6, WithinRel( chunk.columnMetadata().energies()[2] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( chunk.columnMetadata().energies()[3] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.columnMetadata().energies()[4] ) );
        CHECK_THAT( 1.500000e+7, WithinRel( chunk.columnMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.columnMetadata().energies()[6] ) );

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

        CHECK( 6 == chunk.covariances().value().rows() );
        CHECK( 6 ==chunk.covariances().value().cols() );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,0) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,1) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,2) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,3) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,4) ) );
        CHECK_THAT( 0., WithinRel( chunk.covariances().value()(0,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(1,0) ) );
        CHECK_THAT( 9.000000e-2, WithinRel( chunk.covariances().value()(1,1) ) );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(1,2) ) );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(1,3) ) );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(1,4) ) );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(1,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(2,0) ) );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(2,1) ) );
        CHECK_THAT( 9.000000e-2, WithinRel( chunk.covariances().value()(2,2) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(2,3) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(2,4) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(2,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(3,0) ) );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(3,1) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(3,2) ) );
        CHECK_THAT( 9.000000e-2, WithinRel( chunk.covariances().value()(3,3) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(3,4) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(3,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(4,0) ) );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(4,1) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(4,2) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(4,3) ) );
        CHECK_THAT( 9.000000e-2, WithinRel( chunk.covariances().value()(4,4) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(4,5) ) );

        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(5,0) ) );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.covariances().value()(5,1) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(5,2) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(5,3) ) );
        CHECK_THAT( 4.500000e-2, WithinRel( chunk.covariances().value()(5,4) ) );
        CHECK_THAT( 9.000000e-2, WithinRel( chunk.covariances().value()(5,5) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an instance of an off-diagonal ReactionBlock with a single asymmetric "
         "SquareMatrix" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
    ReactionBlock covariance = section.reactions()[1];

    WHEN( "constructing a CovarianceBlock" ) {

      id::ParticleID rowProjectile( "n" );
      id::ParticleID rowTarget( "F19" );
      id::ReactionID rowReaction( "4" );
      id::ParticleID columnProjectile( "n" );
      id::ParticleID columnTarget( "F19" );
      id::ReactionID columnReaction( "16" );

      auto chunk = format::endf::covariance::createCrossSectionCovarianceBlock(
                     rowProjectile, rowTarget, rowReaction,
                     columnProjectile, columnTarget, columnReaction,
                     covariance );

      THEN( "a CovarianceBlock can be created and members can be tested" ) {

        CHECK( id::ParticleID( "n" ) == chunk.rowMetadata().projectileIdentifier() );
        CHECK( id::ParticleID( "F19" ) == chunk.rowMetadata().targetIdentifier() );
        CHECK( id::ReactionID( "4" ) == chunk.rowMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.rowMetadata().energies().size() );
        CHECK( 6 == chunk.rowMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.rowMetadata().energies()[6] ) );

        CHECK( id::ParticleID( "n" ) == chunk.columnMetadata().projectileIdentifier() );
        CHECK( id::ParticleID( "F19" ) == chunk.columnMetadata().targetIdentifier() );
        CHECK( id::ReactionID( "16" ) == chunk.columnMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.columnMetadata().energies().size() );
        CHECK( 6 == chunk.columnMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
        CHECK_THAT( 1.098500e+7, WithinRel( chunk.columnMetadata().energies()[1] ) );
        CHECK_THAT( 1.200000e+7, WithinRel( chunk.columnMetadata().energies()[2] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.columnMetadata().energies()[3] ) );
        CHECK_THAT( 1.600000e+7, WithinRel( chunk.columnMetadata().energies()[4] ) );
        CHECK_THAT( 1.800000e+7, WithinRel( chunk.columnMetadata().energies()[5] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.columnMetadata().energies()[6] ) );

        CHECK( false == chunk.hasVarianceScaling() );
        CHECK( std::nullopt == chunk.varianceScaling() );

        CHECK( true == chunk.isRelativeBlock() );
        CHECK( false == chunk.isAbsoluteBlock() );
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

  GIVEN( "an instance of an off-diagonal ReactionBlock with a single RectangularMatrix" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-010_Ne_022.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 16 ).parse< 33 >();
    ReactionBlock covariance = section.reactions()[1];

    WHEN( "constructing a CovarianceBlock" ) {

      id::ParticleID rowProjectile( "n" );
      id::ParticleID rowTarget( "Ne22" );
      id::ReactionID rowReaction( "16" );
      id::ParticleID columnProjectile( "n" );
      id::ParticleID columnTarget( "Ne22" );
      id::ReactionID columnReaction( "51" );

      auto chunk = format::endf::covariance::createCrossSectionCovarianceBlock(
                     rowProjectile, rowTarget, rowReaction,
                     columnProjectile, columnTarget, columnReaction,
                     covariance );

      THEN( "a CovarianceBlock can be created and members can be tested" ) {

        CHECK( id::ParticleID( "n" ) == chunk.rowMetadata().projectileIdentifier() );
        CHECK( id::ParticleID( "Ne22" ) == chunk.rowMetadata().targetIdentifier() );
        CHECK( id::ReactionID( "16" ) == chunk.rowMetadata().reactionIdentifier() );
        CHECK( 7 == chunk.rowMetadata().energies().size() );
        CHECK( 6 == chunk.rowMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 1.083960e+7, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 1.350000e+7, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 2.100000e+7, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 2.500000e+7, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 2.900000e+7, WithinRel( chunk.rowMetadata().energies()[6] ) );

        CHECK( id::ParticleID( "n" ) == chunk.columnMetadata().projectileIdentifier() );
        CHECK( id::ParticleID( "Ne22" ) == chunk.columnMetadata().targetIdentifier() );
        CHECK( id::ReactionID( "51" ) == chunk.columnMetadata().reactionIdentifier() );
        CHECK( 11 == chunk.columnMetadata().energies().size() );
        CHECK( 10 == chunk.columnMetadata().numberGroups() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.columnMetadata().energies()[0] ) );
        CHECK_THAT( 2.000000e+6, WithinRel( chunk.columnMetadata().energies()[1] ) );
        CHECK_THAT( 2.800000e+6, WithinRel( chunk.columnMetadata().energies()[2] ) );
        CHECK_THAT( 4.800000e+6, WithinRel( chunk.columnMetadata().energies()[3] ) );
        CHECK_THAT( 6.800000e+6, WithinRel( chunk.columnMetadata().energies()[4] ) );
        CHECK_THAT( 9.500000e+6, WithinRel( chunk.columnMetadata().energies()[5] ) );
        CHECK_THAT( 1.350000e+7, WithinRel( chunk.columnMetadata().energies()[6] ) );
        CHECK_THAT( 1.700000e+7, WithinRel( chunk.columnMetadata().energies()[7] ) );
        CHECK_THAT( 2.100000e+7, WithinRel( chunk.columnMetadata().energies()[8] ) );
        CHECK_THAT( 2.500000e+7, WithinRel( chunk.columnMetadata().energies()[9] ) );
        CHECK_THAT( 2.900000e+7, WithinRel( chunk.columnMetadata().energies()[10] ) );

        CHECK( false == chunk.hasVarianceScaling() );
        CHECK( std::nullopt == chunk.varianceScaling() );

        CHECK( true == chunk.isRelativeBlock() );
        CHECK( false == chunk.isAbsoluteBlock() );
        CHECK( true == chunk.isOffDiagonalBlock() );
        CHECK( false == chunk.isDiagonalBlock() );

        CHECK( std::nullopt != chunk.covariances() );
        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );

        CHECK( 6 == chunk.covariances().value().rows() );
        CHECK( 10 == chunk.covariances().value().cols() );
        CHECK_THAT(  8.705930e-3, WithinRel( chunk.covariances().value()(0,0) ) );
        CHECK_THAT(  5.219980e-3, WithinRel( chunk.covariances().value()(0,1) ) );
        CHECK_THAT(  4.176120e-3, WithinRel( chunk.covariances().value()(0,2) ) );
        CHECK_THAT( -7.644270e-3, WithinRel( chunk.covariances().value()(0,3) ) );
        CHECK_THAT( -2.693350e-2, WithinRel( chunk.covariances().value()(0,4) ) );
        CHECK_THAT( -3.783350e-2, WithinRel( chunk.covariances().value()(0,5) ) );
        CHECK_THAT( -3.370650e-2, WithinRel( chunk.covariances().value()(0,6) ) );
        CHECK_THAT( -2.969770e-2, WithinRel( chunk.covariances().value()(0,7) ) );
        CHECK_THAT( -2.657030e-2, WithinRel( chunk.covariances().value()(0,8) ) );
        CHECK_THAT( -2.357700e-2, WithinRel( chunk.covariances().value()(0,9) ) );

        CHECK_THAT(  7.572530e-3, WithinRel( chunk.covariances().value()(1,0) ) );
        CHECK_THAT(  4.663230e-3, WithinRel( chunk.covariances().value()(1,1) ) );
        CHECK_THAT(  3.625630e-3, WithinRel( chunk.covariances().value()(1,2) ) );
        CHECK_THAT( -4.591400e-3, WithinRel( chunk.covariances().value()(1,3) ) );
        CHECK_THAT( -1.838380e-2, WithinRel( chunk.covariances().value()(1,4) ) );
        CHECK_THAT( -2.690270e-2, WithinRel( chunk.covariances().value()(1,5) ) );
        CHECK_THAT( -2.438550e-2, WithinRel( chunk.covariances().value()(1,6) ) );
        CHECK_THAT( -2.185160e-2, WithinRel( chunk.covariances().value()(1,7) ) );
        CHECK_THAT( -1.988540e-2, WithinRel( chunk.covariances().value()(1,8) ) );
        CHECK_THAT( -1.789060e-2, WithinRel( chunk.covariances().value()(1,9) ) );

        CHECK_THAT(  3.173510e-3, WithinRel( chunk.covariances().value()(2,0) ) );
        CHECK_THAT(  1.829920e-3, WithinRel( chunk.covariances().value()(2,1) ) );
        CHECK_THAT(  1.904540e-3, WithinRel( chunk.covariances().value()(2,2) ) );
        CHECK_THAT( -8.009500e-3, WithinRel( chunk.covariances().value()(2,3) ) );
        CHECK_THAT( -2.535940e-2, WithinRel( chunk.covariances().value()(2,4) ) );
        CHECK_THAT( -3.697080e-2, WithinRel( chunk.covariances().value()(2,5) ) );
        CHECK_THAT( -3.579090e-2, WithinRel( chunk.covariances().value()(2,6) ) );
        CHECK_THAT( -3.356390e-2, WithinRel( chunk.covariances().value()(2,7) ) );
        CHECK_THAT( -3.136120e-2, WithinRel( chunk.covariances().value()(2,8) ) );
        CHECK_THAT( -2.904260e-2, WithinRel( chunk.covariances().value()(2,9) ) );

        CHECK_THAT(  4.127170e-3, WithinRel( chunk.covariances().value()(3,0) ) );
        CHECK_THAT(  2.451630e-3, WithinRel( chunk.covariances().value()(3,1) ) );
        CHECK_THAT(  2.347220e-3, WithinRel( chunk.covariances().value()(3,2) ) );
        CHECK_THAT( -7.512620e-3, WithinRel( chunk.covariances().value()(3,3) ) );
        CHECK_THAT( -2.517820e-2, WithinRel( chunk.covariances().value()(3,4) ) );
        CHECK_THAT( -3.763630e-2, WithinRel( chunk.covariances().value()(3,5) ) );
        CHECK_THAT( -3.665900e-2, WithinRel( chunk.covariances().value()(3,6) ) );
        CHECK_THAT( -3.464710e-2, WithinRel( chunk.covariances().value()(3,7) ) );
        CHECK_THAT( -3.267620e-2, WithinRel( chunk.covariances().value()(3,8) ) );
        CHECK_THAT( -3.050560e-2, WithinRel( chunk.covariances().value()(3,9) ) );

        CHECK_THAT(  7.038500e-3, WithinRel( chunk.covariances().value()(4,0) ) );
        CHECK_THAT(  4.370350e-3, WithinRel( chunk.covariances().value()(4,1) ) );
        CHECK_THAT(  3.589780e-3, WithinRel( chunk.covariances().value()(4,2) ) );
        CHECK_THAT( -5.475460e-3, WithinRel( chunk.covariances().value()(4,3) ) );
        CHECK_THAT( -2.233250e-2, WithinRel( chunk.covariances().value()(4,4) ) );
        CHECK_THAT( -3.478520e-2, WithinRel( chunk.covariances().value()(4,5) ) );
        CHECK_THAT( -3.334560e-2, WithinRel( chunk.covariances().value()(4,6) ) );
        CHECK_THAT( -3.145680e-2, WithinRel( chunk.covariances().value()(4,7) ) );
        CHECK_THAT( -2.992890e-2, WithinRel( chunk.covariances().value()(4,8) ) );
        CHECK_THAT( -2.812090e-2, WithinRel( chunk.covariances().value()(4,9) ) );

        CHECK_THAT(  1.168570e-2, WithinRel( chunk.covariances().value()(5,0) ) );
        CHECK_THAT(  7.446400e-3, WithinRel( chunk.covariances().value()(5,1) ) );
        CHECK_THAT(  5.540070e-3, WithinRel( chunk.covariances().value()(5,2) ) );
        CHECK_THAT( -1.959040e-3, WithinRel( chunk.covariances().value()(5,3) ) );
        CHECK_THAT( -1.660210e-2, WithinRel( chunk.covariances().value()(5,4) ) );
        CHECK_THAT( -2.786470e-2, WithinRel( chunk.covariances().value()(5,5) ) );
        CHECK_THAT( -2.536210e-2, WithinRel( chunk.covariances().value()(5,6) ) );
        CHECK_THAT( -2.349130e-2, WithinRel( chunk.covariances().value()(5,7) ) );
        CHECK_THAT( -2.257240e-2, WithinRel( chunk.covariances().value()(5,8) ) );
        CHECK_THAT( -2.131920e-2, WithinRel( chunk.covariances().value()(5,9) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
