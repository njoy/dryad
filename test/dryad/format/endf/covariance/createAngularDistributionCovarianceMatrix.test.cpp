// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/format/endf/covariance/createAngularDistributionCovarianceMatrix.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::ENDFtk;
using ExplicitCovariance = section::ExplicitCovariance;

SCENARIO( "createAngularDistributionCovarianceMatrix" ) {

  GIVEN( "an instance of an on-diagonal ExplicitCovariance with a single symmetric "
         "SquareMatrix" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-010_Ne_022.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 34 ).section( 2 ).parse< 34 >();
    ExplicitCovariance covariance = section.reactions()[0].legendreBlocks().front().data().front();

    WHEN( "constructing covariance matrices" ) {

      id::ReactionID reaction( "n,Ne22->n(0)" );
      std::size_t moment = 1;

      auto chunk = format::endf::covariance::createAngularDistributionCovarianceMatrix(
                     reaction, reaction, 1, 1, covariance );

      THEN( "covariance matrices can be created and members can be tested" ) {

        CHECK( chunk.rowMetadata() == chunk.columnMetadata() );

        CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,Ne22->n(0)" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
        CHECK( 1 == chunk.rowMetadata().moments().size() );
        CHECK( 1 == chunk.rowMetadata().moments()[0] );
        CHECK( 10 == chunk.rowMetadata().energies().size() );
        CHECK_THAT( 3.0e+5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 5.0e+5, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 1.0e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 2.0e+6, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 2.8e+6, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 3.8e+6, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 4.6e+6, WithinRel( chunk.rowMetadata().energies()[6] ) );
        CHECK_THAT( 5.6e+6, WithinRel( chunk.rowMetadata().energies()[7] ) );
        CHECK_THAT( 6.2e+6, WithinRel( chunk.rowMetadata().energies()[8] ) );
        CHECK_THAT( 2.0e+8, WithinRel( chunk.rowMetadata().energies()[9] ) );

        CHECK( true == chunk.isRelativeMatrix() );
        CHECK( false == chunk.isAbsoluteMatrix() );
        CHECK( false == chunk.isOffDiagonal() );
        CHECK( true == chunk.isOnDiagonal() );

        CHECK( std::nullopt != chunk.standardDeviations() );
        CHECK( std::nullopt != chunk.correlations() );
        CHECK( std::nullopt != chunk.eigenvalues() );
        CHECK( std::nullopt != chunk.eigenvectors() );

        CHECK( 9 == chunk.covariances().rows() );
        CHECK( 9 ==chunk.covariances().cols() );
        CHECK_THAT(  6.461320e-1, WithinRel( chunk.covariances()(0,0) ) );
        CHECK_THAT(  2.611120e-1, WithinRel( chunk.covariances()(0,1) ) );
        CHECK_THAT(  6.755920e-2, WithinRel( chunk.covariances()(0,2) ) );
        CHECK_THAT( -2.278260e-3, WithinRel( chunk.covariances()(0,3) ) );
        CHECK_THAT( -1.077730e-2, WithinRel( chunk.covariances()(0,4) ) );
        CHECK_THAT(  5.378700e-3, WithinRel( chunk.covariances()(0,5) ) );
        CHECK_THAT(  2.724480e-2, WithinRel( chunk.covariances()(0,6) ) );
        CHECK_THAT(  5.840270e-2, WithinRel( chunk.covariances()(0,7) ) );
        CHECK_THAT(  7.195770e-2, WithinRel( chunk.covariances()(0,8) ) );

        CHECK_THAT(  2.611120e-1, WithinRel( chunk.covariances()(1,0) ) );
        CHECK_THAT(  1.227030e-1, WithinRel( chunk.covariances()(1,1) ) );
        CHECK_THAT(  4.864790e-2, WithinRel( chunk.covariances()(1,2) ) );
        CHECK_THAT(  1.937990e-2, WithinRel( chunk.covariances()(1,3) ) );
        CHECK_THAT(  1.320910e-2, WithinRel( chunk.covariances()(1,4) ) );
        CHECK_THAT(  1.652240e-2, WithinRel( chunk.covariances()(1,5) ) );
        CHECK_THAT(  2.353870e-2, WithinRel( chunk.covariances()(1,6) ) );
        CHECK_THAT(  3.384180e-2, WithinRel( chunk.covariances()(1,7) ) );
        CHECK_THAT(  3.813280e-2, WithinRel( chunk.covariances()(1,8) ) );

        CHECK_THAT(  6.755920e-2, WithinRel( chunk.covariances()(2,0) ) );
        CHECK_THAT(  4.864790e-2, WithinRel( chunk.covariances()(2,1) ) );
        CHECK_THAT(  3.369010e-2, WithinRel( chunk.covariances()(2,2) ) );
        CHECK_THAT(  2.518390e-2, WithinRel( chunk.covariances()(2,3) ) );
        CHECK_THAT(  2.092300e-2, WithinRel( chunk.covariances()(2,4) ) );
        CHECK_THAT(  1.859180e-2, WithinRel( chunk.covariances()(2,5) ) );
        CHECK_THAT(  1.856010e-2, WithinRel( chunk.covariances()(2,6) ) );
        CHECK_THAT(  1.886620e-2, WithinRel( chunk.covariances()(2,7) ) );
        CHECK_THAT(  1.875170e-2, WithinRel( chunk.covariances()(2,8) ) );

        CHECK_THAT( -2.278260e-3, WithinRel( chunk.covariances()(3,0) ) );
        CHECK_THAT(  1.937990e-2, WithinRel( chunk.covariances()(3,1) ) );
        CHECK_THAT(  2.518390e-2, WithinRel( chunk.covariances()(3,2) ) );
        CHECK_THAT(  2.441000e-2, WithinRel( chunk.covariances()(3,3) ) );
        CHECK_THAT(  2.127080e-2, WithinRel( chunk.covariances()(3,4) ) );
        CHECK_THAT(  1.737030e-2, WithinRel( chunk.covariances()(3,5) ) );
        CHECK_THAT(  1.502350e-2, WithinRel( chunk.covariances()(3,6) ) );
        CHECK_THAT(  1.196380e-2, WithinRel( chunk.covariances()(3,7) ) );
        CHECK_THAT(  1.037540e-2, WithinRel( chunk.covariances()(3,8) ) );

        CHECK_THAT( -1.077730e-2, WithinRel( chunk.covariances()(4,0) ) );
        CHECK_THAT(  1.320910e-2, WithinRel( chunk.covariances()(4,1) ) );
        CHECK_THAT(  2.092300e-2, WithinRel( chunk.covariances()(4,2) ) );
        CHECK_THAT(  2.127080e-2, WithinRel( chunk.covariances()(4,3) ) );
        CHECK_THAT(  1.870230e-2, WithinRel( chunk.covariances()(4,4) ) );
        CHECK_THAT(  1.511890e-2, WithinRel( chunk.covariances()(4,5) ) );
        CHECK_THAT(  1.277680e-2, WithinRel( chunk.covariances()(4,6) ) );
        CHECK_THAT(  9.649770e-3, WithinRel( chunk.covariances()(4,7) ) );
        CHECK_THAT(  8.050100e-3, WithinRel( chunk.covariances()(4,8) ) );

        CHECK_THAT(  5.378700e-3, WithinRel( chunk.covariances()(5,0) ) );
        CHECK_THAT(  1.652240e-2, WithinRel( chunk.covariances()(5,1) ) );
        CHECK_THAT(  1.859180e-2, WithinRel( chunk.covariances()(5,2) ) );
        CHECK_THAT(  1.737030e-2, WithinRel( chunk.covariances()(5,3) ) );
        CHECK_THAT(  1.511890e-2, WithinRel( chunk.covariances()(5,4) ) );
        CHECK_THAT(  1.260550e-2, WithinRel( chunk.covariances()(5,5) ) );
        CHECK_THAT(  1.122260e-2, WithinRel( chunk.covariances()(5,6) ) );
        CHECK_THAT(  9.387000e-3, WithinRel( chunk.covariances()(5,7) ) );
        CHECK_THAT(  8.374310e-3, WithinRel( chunk.covariances()(5,8) ) );

        CHECK_THAT(  2.724480e-2, WithinRel( chunk.covariances()(6,0) ) );
        CHECK_THAT(  2.353870e-2, WithinRel( chunk.covariances()(6,1) ) );
        CHECK_THAT(  1.856010e-2, WithinRel( chunk.covariances()(6,2) ) );
        CHECK_THAT(  1.502350e-2, WithinRel( chunk.covariances()(6,3) ) );
        CHECK_THAT(  1.277680e-2, WithinRel( chunk.covariances()(6,4) ) );
        CHECK_THAT(  1.122260e-2, WithinRel( chunk.covariances()(6,5) ) );
        CHECK_THAT(  1.088110e-2, WithinRel( chunk.covariances()(6,6) ) );
        CHECK_THAT(  1.051210e-2, WithinRel( chunk.covariances()(6,7) ) );
        CHECK_THAT(  1.016370e-2, WithinRel( chunk.covariances()(6,8) ) );

        CHECK_THAT(  5.840270e-2, WithinRel( chunk.covariances()(7,0) ) );
        CHECK_THAT(  3.384180e-2, WithinRel( chunk.covariances()(7,1) ) );
        CHECK_THAT(  1.886620e-2, WithinRel( chunk.covariances()(7,2) ) );
        CHECK_THAT(  1.196380e-2, WithinRel( chunk.covariances()(7,3) ) );
        CHECK_THAT(  9.649770e-3, WithinRel( chunk.covariances()(7,4) ) );
        CHECK_THAT(  9.387000e-3, WithinRel( chunk.covariances()(7,5) ) );
        CHECK_THAT(  1.051210e-2, WithinRel( chunk.covariances()(7,6) ) );
        CHECK_THAT(  1.226870e-2, WithinRel( chunk.covariances()(7,7) ) );
        CHECK_THAT(  1.290870e-2, WithinRel( chunk.covariances()(7,8) ) );

        CHECK_THAT(  7.195770e-2, WithinRel( chunk.covariances()(8,0) ) );
        CHECK_THAT(  3.813280e-2, WithinRel( chunk.covariances()(8,1) ) );
        CHECK_THAT(  1.875170e-2, WithinRel( chunk.covariances()(8,2) ) );
        CHECK_THAT(  1.037540e-2, WithinRel( chunk.covariances()(8,3) ) );
        CHECK_THAT(  8.050100e-3, WithinRel( chunk.covariances()(8,4) ) );
        CHECK_THAT(  8.374310e-3, WithinRel( chunk.covariances()(8,5) ) );
        CHECK_THAT(  1.016370e-2, WithinRel( chunk.covariances()(8,6) ) );
        CHECK_THAT(  1.290870e-2, WithinRel( chunk.covariances()(8,7) ) );
        CHECK_THAT(  1.402580e-2, WithinRel( chunk.covariances()(8,8) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an instance of an off-diagonal ExplicitCovariance with a single symmetric "
         "SquareMatrix" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-010_Ne_022.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 34 ).section( 2 ).parse< 34 >();
    ExplicitCovariance covariance = section.reactions()[0].legendreBlocks()[1].data()[0];

    WHEN( "constructing covariance matrices" ) {

      id::ReactionID reaction( "n,Ne22->n(0)" );
      std::size_t rowMoment = 1;
      std::size_t columnMoment = 2;

      auto chunk = format::endf::covariance::createAngularDistributionCovarianceMatrix(
                     reaction, reaction, rowMoment, columnMoment, covariance );

      THEN( "covariance matrices can be created and members can be tested" ) {

        CHECK( chunk.rowMetadata() != chunk.columnMetadata() );

        CHECK( 1 == chunk.rowMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,Ne22->n(0)" ) == chunk.rowMetadata().reactionIdentifiers()[0] );
        CHECK( 1 == chunk.rowMetadata().moments().size() );
        CHECK( 1 == chunk.rowMetadata().moments()[0] );
        CHECK( 10 == chunk.rowMetadata().energies().size() );
        CHECK_THAT( 3.0e+5, WithinRel( chunk.rowMetadata().energies()[0] ) );
        CHECK_THAT( 5.0e+5, WithinRel( chunk.rowMetadata().energies()[1] ) );
        CHECK_THAT( 1.0e+6, WithinRel( chunk.rowMetadata().energies()[2] ) );
        CHECK_THAT( 2.0e+6, WithinRel( chunk.rowMetadata().energies()[3] ) );
        CHECK_THAT( 2.8e+6, WithinRel( chunk.rowMetadata().energies()[4] ) );
        CHECK_THAT( 3.8e+6, WithinRel( chunk.rowMetadata().energies()[5] ) );
        CHECK_THAT( 4.6e+6, WithinRel( chunk.rowMetadata().energies()[6] ) );
        CHECK_THAT( 5.6e+6, WithinRel( chunk.rowMetadata().energies()[7] ) );
        CHECK_THAT( 6.2e+6, WithinRel( chunk.rowMetadata().energies()[8] ) );
        CHECK_THAT( 2.0e+8, WithinRel( chunk.rowMetadata().energies()[9] ) );

        CHECK( 1 == chunk.columnMetadata().reactionIdentifiers().size() );
        CHECK( id::ReactionID( "n,Ne22->n(0)" ) == chunk.columnMetadata().reactionIdentifiers()[0] );
        CHECK( 1 == chunk.columnMetadata().moments().size() );
        CHECK( 2 == chunk.columnMetadata().moments()[0] );
        CHECK( 10 == chunk.columnMetadata().energies().size() );
        CHECK_THAT( 3.0e+5, WithinRel( chunk.columnMetadata().energies()[0] ) );
        CHECK_THAT( 5.0e+5, WithinRel( chunk.columnMetadata().energies()[1] ) );
        CHECK_THAT( 1.0e+6, WithinRel( chunk.columnMetadata().energies()[2] ) );
        CHECK_THAT( 2.0e+6, WithinRel( chunk.columnMetadata().energies()[3] ) );
        CHECK_THAT( 2.8e+6, WithinRel( chunk.columnMetadata().energies()[4] ) );
        CHECK_THAT( 3.8e+6, WithinRel( chunk.columnMetadata().energies()[5] ) );
        CHECK_THAT( 4.6e+6, WithinRel( chunk.columnMetadata().energies()[6] ) );
        CHECK_THAT( 5.6e+6, WithinRel( chunk.columnMetadata().energies()[7] ) );
        CHECK_THAT( 6.2e+6, WithinRel( chunk.columnMetadata().energies()[8] ) );
        CHECK_THAT( 2.0e+8, WithinRel( chunk.columnMetadata().energies()[9] ) );

        CHECK( true == chunk.isRelativeMatrix() );
        CHECK( false == chunk.isAbsoluteMatrix() );
        CHECK( true == chunk.isOffDiagonal() );
        CHECK( false == chunk.isOnDiagonal() );

        CHECK( std::nullopt == chunk.standardDeviations() );
        CHECK( std::nullopt == chunk.correlations() );
        CHECK( std::nullopt == chunk.eigenvalues() );
        CHECK( std::nullopt == chunk.eigenvectors() );

        CHECK( 9 == chunk.covariances().rows() );
        CHECK( 9 ==chunk.covariances().cols() );

        CHECK_THAT( -1.917260e-2, WithinRel( chunk.covariances()(0,0) ) );
        CHECK_THAT( -2.587660e-2, WithinRel( chunk.covariances()(0,1) ) );
        CHECK_THAT( -2.291880e-2, WithinRel( chunk.covariances()(0,2) ) );
        CHECK_THAT(  1.878290e-3, WithinRel( chunk.covariances()(0,3) ) );
        CHECK_THAT(  1.809810e-2, WithinRel( chunk.covariances()(0,4) ) );
        CHECK_THAT(  2.419060e-2, WithinRel( chunk.covariances()(0,5) ) );
        CHECK_THAT(  2.283060e-2, WithinRel( chunk.covariances()(0,6) ) );
        CHECK_THAT(  2.387280e-2, WithinRel( chunk.covariances()(0,7) ) );
        CHECK_THAT(  2.804280e-2, WithinRel( chunk.covariances()(0,8) ) );

        CHECK_THAT( -2.587660e-2, WithinRel( chunk.covariances()(1,0) ) );
        CHECK_THAT(  1.961980e-2, WithinRel( chunk.covariances()(1,1) ) );
        CHECK_THAT(  6.429080e-3, WithinRel( chunk.covariances()(1,2) ) );
        CHECK_THAT(  5.215700e-3, WithinRel( chunk.covariances()(1,3) ) );
        CHECK_THAT(  1.073320e-2, WithinRel( chunk.covariances()(1,4) ) );
        CHECK_THAT(  1.550580e-2, WithinRel( chunk.covariances()(1,5) ) );
        CHECK_THAT(  1.708450e-2, WithinRel( chunk.covariances()(1,6) ) );
        CHECK_THAT(  1.877040e-2, WithinRel( chunk.covariances()(1,7) ) );
        CHECK_THAT(  2.045200e-2, WithinRel( chunk.covariances()(1,8) ) );

        CHECK_THAT( -2.291880e-2, WithinRel( chunk.covariances()(2,0) ) );
        CHECK_THAT(  6.429080e-3, WithinRel( chunk.covariances()(2,1) ) );
        CHECK_THAT(  1.708590e-2, WithinRel( chunk.covariances()(2,2) ) );
        CHECK_THAT(  5.506340e-3, WithinRel( chunk.covariances()(2,3) ) );
        CHECK_THAT(  5.867540e-3, WithinRel( chunk.covariances()(2,4) ) );
        CHECK_THAT(  9.428110e-3, WithinRel( chunk.covariances()(2,5) ) );
        CHECK_THAT(  1.199150e-2, WithinRel( chunk.covariances()(2,6) ) );
        CHECK_THAT(  1.372820e-2, WithinRel( chunk.covariances()(2,7) ) );
        CHECK_THAT(  1.418100e-2, WithinRel( chunk.covariances()(2,8) ) );

        CHECK_THAT(  1.878290e-3, WithinRel( chunk.covariances()(3,0) ) );
        CHECK_THAT(  5.215700e-3, WithinRel( chunk.covariances()(3,1) ) );
        CHECK_THAT(  5.506340e-3, WithinRel( chunk.covariances()(3,2) ) );
        CHECK_THAT(  4.814790e-3, WithinRel( chunk.covariances()(3,3) ) );
        CHECK_THAT(  3.420820e-3, WithinRel( chunk.covariances()(3,4) ) );
        CHECK_THAT(  6.231410e-3, WithinRel( chunk.covariances()(3,5) ) );
        CHECK_THAT(  8.875970e-3, WithinRel( chunk.covariances()(3,6) ) );
        CHECK_THAT(  1.048080e-2, WithinRel( chunk.covariances()(3,7) ) );
        CHECK_THAT(  1.050090e-2, WithinRel( chunk.covariances()(3,8) ) );

        CHECK_THAT(  1.809810e-2, WithinRel( chunk.covariances()(4,0) ) );
        CHECK_THAT(  1.073320e-2, WithinRel( chunk.covariances()(4,1) ) );
        CHECK_THAT(  5.867540e-3, WithinRel( chunk.covariances()(4,2) ) );
        CHECK_THAT(  3.420820e-3, WithinRel( chunk.covariances()(4,3) ) );
        CHECK_THAT(  2.532970e-3, WithinRel( chunk.covariances()(4,4) ) );
        CHECK_THAT(  4.931270e-3, WithinRel( chunk.covariances()(4,5) ) );
        CHECK_THAT(  7.283570e-3, WithinRel( chunk.covariances()(4,6) ) );
        CHECK_THAT(  8.698490e-3, WithinRel( chunk.covariances()(4,7) ) );
        CHECK_THAT(  8.673870e-3, WithinRel( chunk.covariances()(4,8) ) );

        CHECK_THAT(  2.419060e-2, WithinRel( chunk.covariances()(5,0) ) );
        CHECK_THAT(  1.550580e-2, WithinRel( chunk.covariances()(5,1) ) );
        CHECK_THAT(  9.428110e-3, WithinRel( chunk.covariances()(5,2) ) );
        CHECK_THAT(  6.231410e-3, WithinRel( chunk.covariances()(5,3) ) );
        CHECK_THAT(  4.931270e-3, WithinRel( chunk.covariances()(5,4) ) );
        CHECK_THAT(  4.543630e-3, WithinRel( chunk.covariances()(5,5) ) );
        CHECK_THAT(  6.472460e-3, WithinRel( chunk.covariances()(5,6) ) );
        CHECK_THAT(  7.680620e-3, WithinRel( chunk.covariances()(5,7) ) );
        CHECK_THAT(  7.764970e-3, WithinRel( chunk.covariances()(5,8) ) );

        CHECK_THAT(  2.283060e-2, WithinRel( chunk.covariances()(6,0) ) );
        CHECK_THAT(  1.708450e-2, WithinRel( chunk.covariances()(6,1) ) );
        CHECK_THAT(  1.199150e-2, WithinRel( chunk.covariances()(6,2) ) );
        CHECK_THAT(  8.875970e-3, WithinRel( chunk.covariances()(6,3) ) );
        CHECK_THAT(  7.283570e-3, WithinRel( chunk.covariances()(6,4) ) );
        CHECK_THAT(  6.472460e-3, WithinRel( chunk.covariances()(6,5) ) );
        CHECK_THAT(  6.615180e-3, WithinRel( chunk.covariances()(6,6) ) );
        CHECK_THAT(  7.710210e-3, WithinRel( chunk.covariances()(6,7) ) );
        CHECK_THAT(  7.934700e-3, WithinRel( chunk.covariances()(6,8) ) );

        CHECK_THAT(  2.387280e-2, WithinRel( chunk.covariances()(7,0) ) );
        CHECK_THAT(  1.877040e-2, WithinRel( chunk.covariances()(7,1) ) );
        CHECK_THAT(  1.372820e-2, WithinRel( chunk.covariances()(7,2) ) );
        CHECK_THAT(  1.048080e-2, WithinRel( chunk.covariances()(7,3) ) );
        CHECK_THAT(  8.698490e-3, WithinRel( chunk.covariances()(7,4) ) );
        CHECK_THAT(  7.680620e-3, WithinRel( chunk.covariances()(7,5) ) );
        CHECK_THAT(  7.710210e-3, WithinRel( chunk.covariances()(7,6) ) );
        CHECK_THAT(  8.016310e-3, WithinRel( chunk.covariances()(7,7) ) );
        CHECK_THAT(  8.435620e-3, WithinRel( chunk.covariances()(7,8) ) );

        CHECK_THAT(  2.804280e-2, WithinRel( chunk.covariances()(8,0) ) );
        CHECK_THAT(  2.045200e-2, WithinRel( chunk.covariances()(8,1) ) );
        CHECK_THAT(  1.418100e-2, WithinRel( chunk.covariances()(8,2) ) );
        CHECK_THAT(  1.050090e-2, WithinRel( chunk.covariances()(8,3) ) );
        CHECK_THAT(  8.673870e-3, WithinRel( chunk.covariances()(8,4) ) );
        CHECK_THAT(  7.764970e-3, WithinRel( chunk.covariances()(8,5) ) );
        CHECK_THAT(  7.934700e-3, WithinRel( chunk.covariances()(8,6) ) );
        CHECK_THAT(  8.435620e-3, WithinRel( chunk.covariances()(8,7) ) );
        CHECK_THAT(  8.603500e-3, WithinRel( chunk.covariances()(8,8) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
