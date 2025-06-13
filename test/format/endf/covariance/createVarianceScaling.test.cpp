// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/format/endf/covariance/createVarianceScaling.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::ENDFtk;
using CovariancePairs = section::CovariancePairs;
using VarianceScaling = covariance::VarianceScaling;
using ScalingType = covariance::ScalingType;

SCENARIO( "createVarianceScaling" ) {

  GIVEN( "an instance of CovariancePairs using LB=8/9" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
    CovariancePairs covariance = std::get< CovariancePairs >( section.reactions()[0].explicitCovariances()[2] );

    WHEN( "creating a VarianceScaling from the CovariancePairs instance" ) {

      auto chunk = format::endf::covariance::createVarianceScaling( covariance );

      THEN( "a VarianceScaling instance can be created and members can be tested" ) {

        CHECK( 12 == chunk.numberGroups() );

        CHECK( 13 == chunk.energies().size() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 1.158400e+5, WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2.074600e+5, WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3.000000e+5, WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4.500000e+5, WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 6.000000e+5, WithinRel( chunk.energies()[5] ) );
        CHECK_THAT( 1.100000e+6, WithinRel( chunk.energies()[6] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( chunk.energies()[7] ) );
        CHECK_THAT( 3.000000e+6, WithinRel( chunk.energies()[8] ) );
        CHECK_THAT( 6.000000e+6, WithinRel( chunk.energies()[9] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( chunk.energies()[10] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.energies()[11] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.energies()[12] ) );

        CHECK( 12 == chunk.factors().size() );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.factors()[0] ) );
        CHECK_THAT( 2.223500e-6, WithinRel( chunk.factors()[1] ) );
        CHECK_THAT( 5.134300e-5, WithinRel( chunk.factors()[2] ) );
        CHECK_THAT( 1.469900e-5, WithinRel( chunk.factors()[3] ) );
        CHECK_THAT( 2.514800e-6, WithinRel( chunk.factors()[4] ) );
        CHECK_THAT( 4.884600e-6, WithinRel( chunk.factors()[5] ) );
        CHECK_THAT( 2.141300e-6, WithinRel( chunk.factors()[6] ) );
        CHECK_THAT( 1.365400e-6, WithinRel( chunk.factors()[7] ) );
        CHECK_THAT( 8.511600e-7, WithinRel( chunk.factors()[8] ) );
        CHECK_THAT( 3.476300e-7, WithinRel( chunk.factors()[9] ) );
        CHECK_THAT( 2.993200e-8, WithinRel( chunk.factors()[10] ) );
        CHECK_THAT( 4.138200e-9, WithinRel( chunk.factors()[11] ) );

        CHECK( ScalingType::Inverse == chunk.type() );
        } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "an instance of CovariancePairs not using LB=8/9" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "n-009_F_019.endf" );
    auto material = tape.materials().front();
    auto section = material.file( 33 ).section( 4 ).parse< 33 >();
    CovariancePairs covariance = std::get< CovariancePairs >( section.reactions()[0].explicitCovariances()[0] );

    WHEN( "creating a VarianceScaling from the CovariancePairs instance" ) {

      THEN( "an exception should be thrown" ) {

        CHECK_THROWS( format::endf::covariance::createVarianceScaling( covariance ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
