// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/UncorrelatedDistributionData.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyIsotropicAndTabulatedChunk( const UncorrelatedDistributionData& );
void verifyLegendreAndTabulatedChunk( const UncorrelatedDistributionData& );
void verifyTabulatedAndTabulatedChunk( const UncorrelatedDistributionData& );

SCENARIO( "UncorrelatedDistributionData" ) {

  GIVEN( "valid data for uncorrelated distribution data with fully isotropic "
         "angular and tabulated energy distributions" ) {

    WHEN( "the data is given explicitly" ) {

      ReferenceFrame frame = ReferenceFrame::CentreOfMass;
      IsotropicAngularDistributions angle;
      TabulatedEnergyDistributions energy(

        { 1e-5, 20. },
        { { { 1e-5, 20. }, { 0., 0. } },
          { { 1e-5, 20. }, { 0., 1. } } }
      );

      UncorrelatedDistributionData chunk( std::move( frame ), std::move( angle ),
                                          std::move( energy ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifyIsotropicAndTabulatedChunk( chunk );
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
      TabulatedEnergyDistributions energy(

        { 1e-5, 20. },
        { { { 1e-5, 20. }, { 0., 0. } },
          { { 1e-5, 20. }, { 0., 1. } } }
      );

      UncorrelatedDistributionData chunk( std::move( frame ), std::move( angle ),
                                          std::move( energy ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifyLegendreAndTabulatedChunk( chunk );
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
      TabulatedEnergyDistributions energy(

        { 1e-5, 20. },
        { { { 1e-5, 20. }, { 0., 0. } },
          { { 1e-5, 20. }, { 0., 1. } } }
      );

      UncorrelatedDistributionData chunk( std::move( frame ), std::move( angle ),
                                          std::move( energy ) );

      THEN( "a Reaction can be constructed and members can be tested" ) {

        verifyTabulatedAndTabulatedChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyIsotropicAndTabulatedChunk( const UncorrelatedDistributionData& chunk ) {

  CHECK( DistributionDataType::Uncorrelated == chunk.type() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.frame() );

  CHECK( true == std::holds_alternative< IsotropicAngularDistributions >( chunk.angle() ) );
  CHECK( true == std::holds_alternative< TabulatedEnergyDistributions >( chunk.energy() ) );

  TabulatedEnergyDistributions energy = std::get< TabulatedEnergyDistributions >( chunk.energy() );
  CHECK( 2 == energy.numberPoints() );
  CHECK( 1 == energy.numberRegions() );
  CHECK( 2 == energy.grid().size() );
  CHECK( 2 == energy.distributions().size() );
  CHECK( 1 == energy.boundaries().size() );
  CHECK( 1 == energy.interpolants().size() );
  CHECK_THAT( 1e-5, WithinRel( energy.grid()[0] ) );
  CHECK_THAT( 20. , WithinRel( energy.grid()[1] ) );
  CHECK( 2 == energy.distributions()[0].energies().size() );
  CHECK( 2 == energy.distributions()[0].values().size() );
  CHECK( 2 == energy.distributions()[1].energies().size() );
  CHECK( 2 == energy.distributions()[1].values().size() );
  CHECK_THAT( 1e-5, WithinRel( energy.distributions()[0].energies()[0] ) );
  CHECK_THAT( 20. , WithinRel( energy.distributions()[0].energies()[1] ) );
  CHECK_THAT(  0. , WithinRel( energy.distributions()[0].values()[0] ) );
  CHECK_THAT(  0. , WithinRel( energy.distributions()[0].values()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( energy.distributions()[1].energies()[0] ) );
  CHECK_THAT( 20. , WithinRel( energy.distributions()[1].energies()[1] ) );
  CHECK_THAT(  0. , WithinRel( energy.distributions()[1].values()[0] ) );
  CHECK_THAT(  1. , WithinRel( energy.distributions()[1].values()[1] ) );
  CHECK( 1 == energy.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );
}

void verifyLegendreAndTabulatedChunk( const UncorrelatedDistributionData& chunk ) {

  CHECK( DistributionDataType::Uncorrelated == chunk.type() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.frame() );

  CHECK( true == std::holds_alternative< LegendreAngularDistributions >( chunk.angle() ) );
  CHECK( true == std::holds_alternative< TabulatedEnergyDistributions >( chunk.energy() ) );

  LegendreAngularDistributions angle = std::get< LegendreAngularDistributions >( chunk.angle() );
  CHECK( 2 == angle.numberPoints() );
  CHECK( 1 == angle.numberRegions() );
  CHECK( 2 == angle.grid().size() );
  CHECK( 2 == angle.distributions().size() );
  CHECK( 1 == angle.boundaries().size() );
  CHECK( 1 == angle.interpolants().size() );
  CHECK_THAT( 1e-5, WithinRel( angle.grid()[0] ) );
  CHECK_THAT( 20., WithinRel( angle.grid()[1] ) );
  CHECK( 1 == angle.distributions()[0].coefficients().size() );
  CHECK( 2 == angle.distributions()[1].coefficients().size() );
  CHECK_THAT( 0.5 , WithinRel( angle.distributions()[0].coefficients()[0] ) );
  CHECK_THAT( 0.5 , WithinRel( angle.distributions()[1].coefficients()[0] ) );
  CHECK_THAT( 0.1, WithinRel( angle.distributions()[1].coefficients()[1] ) );
  CHECK( 1 == angle.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );

  TabulatedEnergyDistributions energy = std::get< TabulatedEnergyDistributions >( chunk.energy() );
  CHECK( 2 == energy.numberPoints() );
  CHECK( 1 == energy.numberRegions() );
  CHECK( 2 == energy.grid().size() );
  CHECK( 2 == energy.distributions().size() );
  CHECK( 1 == energy.boundaries().size() );
  CHECK( 1 == energy.interpolants().size() );
  CHECK_THAT( 1e-5, WithinRel( energy.grid()[0] ) );
  CHECK_THAT( 20. , WithinRel( energy.grid()[1] ) );
  CHECK( 2 == energy.distributions()[0].energies().size() );
  CHECK( 2 == energy.distributions()[0].values().size() );
  CHECK( 2 == energy.distributions()[1].energies().size() );
  CHECK( 2 == energy.distributions()[1].values().size() );
  CHECK_THAT( 1e-5, WithinRel( energy.distributions()[0].energies()[0] ) );
  CHECK_THAT( 20. , WithinRel( energy.distributions()[0].energies()[1] ) );
  CHECK_THAT(  0. , WithinRel( energy.distributions()[0].values()[0] ) );
  CHECK_THAT(  0. , WithinRel( energy.distributions()[0].values()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( energy.distributions()[1].energies()[0] ) );
  CHECK_THAT( 20. , WithinRel( energy.distributions()[1].energies()[1] ) );
  CHECK_THAT(  0. , WithinRel( energy.distributions()[1].values()[0] ) );
  CHECK_THAT(  1. , WithinRel( energy.distributions()[1].values()[1] ) );
  CHECK( 1 == energy.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );
}

void verifyTabulatedAndTabulatedChunk( const UncorrelatedDistributionData& chunk ) {

  CHECK( DistributionDataType::Uncorrelated == chunk.type() );
  CHECK( ReferenceFrame::CentreOfMass == chunk.frame() );

  CHECK( true == std::holds_alternative< TabulatedAngularDistributions >( chunk.angle() ) );
  CHECK( true == std::holds_alternative< TabulatedEnergyDistributions >( chunk.energy() ) );

  TabulatedAngularDistributions angle = std::get< TabulatedAngularDistributions >( chunk.angle() );
  CHECK( 2 == angle.numberPoints() );
  CHECK( 1 == angle.numberRegions() );
  CHECK( 2 == angle.grid().size() );
  CHECK( 2 == angle.distributions().size() );
  CHECK( 1 == angle.boundaries().size() );
  CHECK( 1 == angle.interpolants().size() );
  CHECK_THAT( 1e-5, WithinRel( angle.grid()[0] ) );
  CHECK_THAT( 20., WithinRel( angle.grid()[1] ) );
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

  TabulatedEnergyDistributions energy = std::get< TabulatedEnergyDistributions >( chunk.energy() );
  CHECK( 2 == energy.numberPoints() );
  CHECK( 1 == energy.numberRegions() );
  CHECK( 2 == energy.grid().size() );
  CHECK( 2 == energy.distributions().size() );
  CHECK( 1 == energy.boundaries().size() );
  CHECK( 1 == energy.interpolants().size() );
  CHECK_THAT( 1e-5, WithinRel( energy.grid()[0] ) );
  CHECK_THAT( 20. , WithinRel( energy.grid()[1] ) );
  CHECK( 2 == energy.distributions()[0].energies().size() );
  CHECK( 2 == energy.distributions()[0].values().size() );
  CHECK( 2 == energy.distributions()[1].energies().size() );
  CHECK( 2 == energy.distributions()[1].values().size() );
  CHECK_THAT( 1e-5, WithinRel( energy.distributions()[0].energies()[0] ) );
  CHECK_THAT( 20. , WithinRel( energy.distributions()[0].energies()[1] ) );
  CHECK_THAT(  0. , WithinRel( energy.distributions()[0].values()[0] ) );
  CHECK_THAT(  0. , WithinRel( energy.distributions()[0].values()[1] ) );
  CHECK_THAT( 1e-5, WithinRel( energy.distributions()[1].energies()[0] ) );
  CHECK_THAT( 20. , WithinRel( energy.distributions()[1].energies()[1] ) );
  CHECK_THAT(  0. , WithinRel( energy.distributions()[1].values()[0] ) );
  CHECK_THAT(  1. , WithinRel( energy.distributions()[1].values()[1] ) );
  CHECK( 1 == energy.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );
}