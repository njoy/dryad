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
        { { { 0., 20. }, { 0., 0.1 } },
          { { 0., 20. }, { 0.05, 0.05 } } }
      );

      UncorrelatedDistributionData chunk( std::move( frame ), std::move( angle ),
                                          std::move( energy ) );

      THEN( "an UncorrelatedDistributionData can be constructed and members can be tested" ) {

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
        { { { 0., 20. }, { 0., 0.1 } },
          { { 0., 20. }, { 0.05, 0.05 } } }
      );

      UncorrelatedDistributionData chunk( std::move( frame ), std::move( angle ),
                                          std::move( energy ) );

      THEN( "an UncorrelatedDistributionData can be constructed and members can be tested" ) {

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
        { { { 0., 20. }, { 0., 0.1 } },
          { { 0., 20. }, { 0.05, 0.05 } } }
      );

      UncorrelatedDistributionData chunk( std::move( frame ), std::move( angle ),
                                          std::move( energy ) );

      THEN( "an UncorrelatedDistributionData can be constructed and members can be tested" ) {

        verifyTabulatedAndTabulatedChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of UncorrelatedDistributionData is given" ) {

      UncorrelatedDistributionData chunk( ReferenceFrame::CentreOfMass,
                                          IsotropicAngularDistributions(),
                                          TabulatedEnergyDistributions(
                                            { 1e-5, 20. },
                                            { { { 0., 20. }, { 0., 0.1 } },
                                              { { 0., 20. }, { 0.05, 0.05 } } } ) );

      THEN( "the reference frame can be changed" ) {

        ReferenceFrame newframe = ReferenceFrame::Laboratory;
        ReferenceFrame original = ReferenceFrame::CentreOfMass;

        chunk.frame( newframe );

        CHECK( newframe == chunk.frame() );

        chunk.frame( original );

        verifyIsotropicAndTabulatedChunk( chunk );
      } // THEN

      THEN( "the distribution data can be changed" ) {

        UncorrelatedDistributionData::AngularDistributions
        newangle = LegendreAngularDistributions( { 1e-5, 20. },
                                                 { { { 0.5 } }, { { 0.5, 0.1 } } } );
        UncorrelatedDistributionData::EnergyDistributions
        newenergy = TabulatedEnergyDistributions( { 1e-5, 20. },
                                                  { { { 0., 10. }, { 0., 0.1 } },
                                                    { { 0., 10. }, { 0.05, 0.05 } } } );
        UncorrelatedDistributionData::AngularDistributions
        originalangle = IsotropicAngularDistributions();
        UncorrelatedDistributionData::EnergyDistributions
        originalenergy = TabulatedEnergyDistributions( { 1e-5, 20. },
                                                       { { { 0., 20. }, { 0., 0.1 } },
                                                         { { 0., 20. }, { 0.05, 0.05 } } } );

        chunk.angle( newangle );
        chunk.energy( newenergy );

        CHECK( newangle == chunk.angle() );
        CHECK( newenergy == chunk.energy() );

        chunk.angle( originalangle );
        chunk.energy( originalenergy );

        verifyIsotropicAndTabulatedChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of UncorrelatedDistributionData are given" ) {

      UncorrelatedDistributionData left( ReferenceFrame::CentreOfMass,
                                         IsotropicAngularDistributions(),
                                         TabulatedEnergyDistributions( { 1e-5, 20. },
                                                                       { { { 0., 20. }, { 0., 0.1 } },
                                                                         { { 0., 20. }, { 0.05, 0.05 } } } ) );
      UncorrelatedDistributionData equal( ReferenceFrame::CentreOfMass,
                                          IsotropicAngularDistributions(),
                                          TabulatedEnergyDistributions( { 1e-5, 20. },
                                                                        { { { 0., 20. }, { 0., 0.1 } },
                                                                          { { 0., 20. }, { 0.05, 0.05 } } } ) );
      UncorrelatedDistributionData different( ReferenceFrame::CentreOfMass,
                                              TabulatedAngularDistributions( { 1e-5, 20. },
                                                                             { { { -1., 1. }, { 0.5, 0.5 } },
                                                                               { { -1., 1. }, { 0.5, 0.5 } } } ),
                                              TabulatedEnergyDistributions( { 1e-5, 20. },
                                                                            { { { 0., 20. }, { 0., 0.1 } },
                                                                              { { 0., 20. }, { 0.05, 0.05 } } } ) );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
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
  CHECK( 2 == energy.distributions()[0].pdf().energies().size() );
  CHECK( 2 == energy.distributions()[0].pdf().values().size() );
  CHECK( 2 == energy.distributions()[1].pdf().energies().size() );
  CHECK( 2 == energy.distributions()[1].pdf().values().size() );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0.1 , WithinRel( energy.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT(  0.05, WithinRel( energy.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0.05, WithinRel( energy.distributions()[1].pdf().values()[1] ) );
  CHECK( 2 == energy.distributions()[0].cdf().energies().size() );
  CHECK( 2 == energy.distributions()[0].cdf().values().size() );
  CHECK( 2 == energy.distributions()[1].cdf().energies().size() );
  CHECK( 2 == energy.distributions()[1].cdf().values().size() );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(  1.  , WithinRel( energy.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(  1.  , WithinRel( energy.distributions()[1].cdf().values()[1] ) );
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
  CHECK( 1 == angle.distributions()[0].pdf().coefficients().size() );
  CHECK( 2 == angle.distributions()[1].pdf().coefficients().size() );
  CHECK_THAT( 0.5, WithinRel( angle.distributions()[0].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.5, WithinRel( angle.distributions()[1].pdf().coefficients()[0] ) );
  CHECK_THAT( 0.1, WithinRel( angle.distributions()[1].pdf().coefficients()[1] ) );
  CHECK( 2 == angle.distributions()[0].cdf().coefficients().size() );
  CHECK( 3 == angle.distributions()[1].cdf().coefficients().size() );
  CHECK_THAT( 0.5               , WithinRel( angle.distributions()[0].cdf().coefficients()[0] ) );
  CHECK_THAT( 0.5               , WithinRel( angle.distributions()[0].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.4666666666666666, WithinRel( angle.distributions()[1].cdf().coefficients()[0] ) );
  CHECK_THAT( 0.5               , WithinRel( angle.distributions()[1].cdf().coefficients()[1] ) );
  CHECK_THAT( 0.0333333333333333, WithinRel( angle.distributions()[1].cdf().coefficients()[2] ) );
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
  CHECK( 2 == energy.distributions()[0].pdf().energies().size() );
  CHECK( 2 == energy.distributions()[0].pdf().values().size() );
  CHECK( 2 == energy.distributions()[1].pdf().energies().size() );
  CHECK( 2 == energy.distributions()[1].pdf().values().size() );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0.1 , WithinRel( energy.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT(  0.05, WithinRel( energy.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0.05, WithinRel( energy.distributions()[1].pdf().values()[1] ) );
  CHECK( 2 == energy.distributions()[0].cdf().energies().size() );
  CHECK( 2 == energy.distributions()[0].cdf().values().size() );
  CHECK( 2 == energy.distributions()[1].cdf().energies().size() );
  CHECK( 2 == energy.distributions()[1].cdf().values().size() );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(  1.  , WithinRel( energy.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(  1.  , WithinRel( energy.distributions()[1].cdf().values()[1] ) );
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
  CHECK( 2 == angle.distributions()[0].pdf().cosines().size() );
  CHECK( 2 == angle.distributions()[0].pdf().values().size() );
  CHECK( 2 == angle.distributions()[1].pdf().cosines().size() );
  CHECK( 2 == angle.distributions()[1].pdf().values().size() );
  CHECK_THAT( -1.  , WithinRel( angle.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT(  1.  , WithinRel( angle.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT(  0.5 , WithinRel( angle.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0.5 , WithinRel( angle.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( -1.  , WithinRel( angle.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT(  1.  , WithinRel( angle.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT(  0.4 , WithinRel( angle.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0.6 , WithinRel( angle.distributions()[1].pdf().values()[1] ) );
  CHECK( 2 == angle.distributions()[0].cdf().cosines().size() );
  CHECK( 2 == angle.distributions()[0].cdf().values().size() );
  CHECK( 2 == angle.distributions()[1].cdf().cosines().size() );
  CHECK( 2 == angle.distributions()[1].cdf().values().size() );
  CHECK_THAT( -1.  , WithinRel( angle.distributions()[0].cdf().cosines()[0] ) );
  CHECK_THAT(  1.  , WithinRel( angle.distributions()[0].cdf().cosines()[1] ) );
  CHECK_THAT(  0.  , WithinRel( angle.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(  1.  , WithinRel( angle.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT( -1.  , WithinRel( angle.distributions()[1].cdf().cosines()[0] ) );
  CHECK_THAT(  1.  , WithinRel( angle.distributions()[1].cdf().cosines()[1] ) );
  CHECK_THAT(  0.  , WithinRel( angle.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(  1.  , WithinRel( angle.distributions()[1].cdf().values()[1] ) );
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
  CHECK( 2 == energy.distributions()[0].pdf().energies().size() );
  CHECK( 2 == energy.distributions()[0].pdf().values().size() );
  CHECK( 2 == energy.distributions()[1].pdf().energies().size() );
  CHECK( 2 == energy.distributions()[1].pdf().values().size() );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0.1 , WithinRel( energy.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT(  0.05, WithinRel( energy.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0.05, WithinRel( energy.distributions()[1].pdf().values()[1] ) );
  CHECK( 2 == energy.distributions()[0].cdf().energies().size() );
  CHECK( 2 == energy.distributions()[0].cdf().values().size() );
  CHECK( 2 == energy.distributions()[1].cdf().energies().size() );
  CHECK( 2 == energy.distributions()[1].cdf().values().size() );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(  1.  , WithinRel( energy.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT( 20.  , WithinRel( energy.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT(  0.  , WithinRel( energy.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(  1.  , WithinRel( energy.distributions()[1].cdf().values()[1] ) );
  CHECK( 1 == energy.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );
}
