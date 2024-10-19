// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/TwoBodyDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyIsotropicChunk( const TwoBodyDistributionData& );
void verifyLegendreChunk( const TwoBodyDistributionData& );
void verifyTabulatedChunk( const TwoBodyDistributionData& );

SCENARIO( "TwoBodyDistributionData" ) {

  GIVEN( "valid data for two body distribution data that is fully isotropic" ) {

    WHEN( "the data is given explicitly" ) {

      ReferenceFrame frame = ReferenceFrame::CentreOfMass;
      IsotropicAngularDistributions angle;

      TwoBodyDistributionData chunk( std::move( frame ), std::move( angle ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifyIsotropicChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for two body distribution data using Legendre distributions" ) {

    WHEN( "the data is given explicitly" ) {

      ReferenceFrame frame = ReferenceFrame::CentreOfMass;
      LegendreAngularDistributions angle(

        { 1e-5, 20. },
        { { { 0.5 } }, { { 0.5, 0.1 } } }
      );

      TwoBodyDistributionData chunk( std::move( frame ), std::move( angle ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifyLegendreChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for two body distribution data using tabulated distributions" ) {

    WHEN( "the data is given explicitly" ) {

      ReferenceFrame frame = ReferenceFrame::CentreOfMass;
      TabulatedAngularDistributions angle(

        { 1e-5, 20. },
        { { { -1., +1. }, { 0.5, 0.5 } },
          { { -1., +1. }, { 0.4, 0.6 } } }
      );

      TwoBodyDistributionData chunk( std::move( frame ), std::move( angle ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifyTabulatedChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyIsotropicChunk( const TwoBodyDistributionData& chunk ) {

  CHECK( DistributionDataType::TwoBody == chunk.type() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.frame() );

  CHECK( true == std::holds_alternative< IsotropicAngularDistributions >( chunk.angle() ) );
}

void verifyLegendreChunk( const TwoBodyDistributionData& chunk ) {

  CHECK( DistributionDataType::TwoBody == chunk.type() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.frame() );

  CHECK( true == std::holds_alternative< LegendreAngularDistributions >( chunk.angle() ) );

  LegendreAngularDistributions angle = std::get< LegendreAngularDistributions >( chunk.angle() );
  CHECK( 2 == angle.numberPoints() );
  CHECK( 1 == angle.numberRegions() );
  CHECK( 2 == angle.grid().size() );
  CHECK( 2 == angle.distributions().size() );
  CHECK( 1 == angle.boundaries().size() );
  CHECK( 1 == angle.interpolants().size() );
  CHECK_THAT( 1e-5, WithinRel( angle.grid()[0] ) );
  CHECK_THAT( 20. , WithinRel( angle.grid()[1] ) );
  CHECK( 1 == angle.distributions()[0].coefficients().size() );
  CHECK( 2 == angle.distributions()[1].coefficients().size() );
  CHECK_THAT( 0.5 , WithinRel( angle.distributions()[0].coefficients()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( angle.distributions()[1].coefficients()[0] ) );
  CHECK_THAT( 0.1, WithinRel( angle.distributions()[1].coefficients()[1] ) );
  CHECK( 1 == angle.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );
}

void verifyTabulatedChunk( const TwoBodyDistributionData& chunk ) {

  CHECK( DistributionDataType::TwoBody == chunk.type() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.frame() );

  CHECK( true == std::holds_alternative< TabulatedAngularDistributions >( chunk.angle() ) );

  TabulatedAngularDistributions angle = std::get< TabulatedAngularDistributions >( chunk.angle() );
  CHECK( 2 == angle.numberPoints() );
  CHECK( 1 == angle.numberRegions() );
  CHECK( 2 == angle.grid().size() );
  CHECK( 2 == angle.distributions().size() );
  CHECK( 1 == angle.boundaries().size() );
  CHECK( 1 == angle.interpolants().size() );
  CHECK_THAT( 1e-5, WithinRel( angle.grid()[0] ) );
  CHECK_THAT( 20. , WithinRel( angle.grid()[1] ) );
  CHECK( 2 == angle.distributions()[0].cosines().size() );
  CHECK( 2 == angle.distributions()[0].values().size() );
  CHECK( 2 == angle.distributions()[1].cosines().size() );
  CHECK( 2 == angle.distributions()[1].values().size() );
  CHECK_THAT( -1.  , WithinRel( angle.distributions()[0].cosines()[0] ) );
  CHECK_THAT(  1.  , WithinRel( angle.distributions()[0].cosines()[1] ) );
  CHECK_THAT(  0.5 , WithinRel( angle.distributions()[0].values()[0] ) );
  CHECK_THAT(  0.5 , WithinRel( angle.distributions()[0].values()[1] ) );
  CHECK_THAT( -1.  , WithinRel( angle.distributions()[1].cosines()[0] ) );
  CHECK_THAT(  1.  , WithinRel( angle.distributions()[1].cosines()[1] ) );
  CHECK_THAT(  0.4 , WithinRel( angle.distributions()[1].values()[0] ) );
  CHECK_THAT(  0.6 , WithinRel( angle.distributions()[1].values()[1] ) );
  CHECK( 1 == angle.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );
}