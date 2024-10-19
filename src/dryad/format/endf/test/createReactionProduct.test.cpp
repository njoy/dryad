// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createReactionProduct.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyElectronlargeAngleElasticElectronProduct( const ReactionProduct& );
void verifyElectronBremsstrahlungPhotonProduct( const ReactionProduct& );
void verifyElectronBremsstrahlungElectronProduct( const ReactionProduct& );

SCENARIO( "createReactionProduct" ) {

  GIVEN( "ENDF reaction products - electro-atomic interactions" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF reaction product is given" ) {

      THEN( "a Reaction can be created" ) {

        auto elastic = tape.materials().front().section( 26, 525 ).parse< 26 >();
        auto bremsstrahlung = tape.materials().front().section( 26, 527 ).parse< 26 >();

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H1" );

        auto product = elastic.reactionProducts()[0];
        ReactionProduct electron_elastic = format::endf::createReactionProduct( projectile, target, product, 525 );
        verifyElectronlargeAngleElasticElectronProduct( electron_elastic );

        product = bremsstrahlung.reactionProducts()[0];
        ReactionProduct photon_bremsstrahlung = format::endf::createReactionProduct( projectile, target, product, 527 );
        verifyElectronBremsstrahlungPhotonProduct( photon_bremsstrahlung );

        product = bremsstrahlung.reactionProducts()[1];
        ReactionProduct electron_bremsstrahlung = format::endf::createReactionProduct( projectile, target, product, 527 );
        verifyElectronBremsstrahlungElectronProduct( electron_bremsstrahlung );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyElectronlargeAngleElasticElectronProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "e-" ) == chunk.identifier() );
  CHECK( true == chunk.isLinearised() );
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( true == chunk.hasDistributionData() );

  CHECK( true == std::holds_alternative< int >( chunk.multiplicity() ) );
  auto multiplicity = std::get< int >( chunk.multiplicity() );
  CHECK( 1 == multiplicity );

  CHECK( std::nullopt == chunk.averageEnergy() );

  CHECK( std::nullopt != chunk.distributionData() );
  CHECK( true == std::holds_alternative< TwoBodyDistributionData >( chunk.distributionData().value() ) );
  auto data = std::get< TwoBodyDistributionData >( chunk.distributionData().value() );
  CHECK( DistributionDataType::TwoBody == data.type() );
  CHECK( true == std::holds_alternative< TabulatedAngularDistributions >( data.angle() ) );
  auto angle = std::get< TabulatedAngularDistributions >( data.angle() );
  CHECK( 16 == angle.numberPoints() );
  CHECK( 1 == angle.numberRegions() );
  CHECK( 16 == angle.grid().size() );
  CHECK( 16 == angle.distributions().size() );
  CHECK( 1 == angle.boundaries().size() );
  CHECK( 1 == angle.interpolants().size() );
  CHECK_THAT(       10., WithinRel( angle.grid()[0] ) );
  CHECK_THAT(     1000., WithinRel( angle.grid()[1] ) );
  CHECK_THAT( 66250000., WithinRel( angle.grid()[14] ) );
  CHECK_THAT(     1e+11, WithinRel( angle.grid()[15] ) );
  CHECK(  2 == angle.distributions()[0].cosines().size() );
  CHECK(  2 == angle.distributions()[0].values().size() );
  CHECK( 30 == angle.distributions()[1].cosines().size() );
  CHECK( 30 == angle.distributions()[1].values().size() );
  CHECK( 95 == angle.distributions()[14].cosines().size() );
  CHECK( 95 == angle.distributions()[14].values().size() );
  CHECK( 96 == angle.distributions()[15].cosines().size() );
  CHECK( 96 == angle.distributions()[15].values().size() );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[0].cosines()[0] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[0].cosines()[1] ) );
  CHECK_THAT(  0.5         , WithinRel( angle.distributions()[0].values()[0] ) );
  CHECK_THAT(  0.5         , WithinRel( angle.distributions()[0].values()[1] ) );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[1].cosines()[0] ) );
  CHECK_THAT( -0.93        , WithinRel( angle.distributions()[1].cosines()[1] ) );
  CHECK_THAT(  0.9962001   , WithinRel( angle.distributions()[1].cosines()[28] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[1].cosines()[29] ) );
  CHECK_THAT(  0.00293923  , WithinRel( angle.distributions()[1].values()[0] ) );
  CHECK_THAT(  0.00314865  , WithinRel( angle.distributions()[1].values()[1] ) );
  CHECK_THAT( 42.358       , WithinRel( angle.distributions()[1].values()[28] ) );
  CHECK_THAT( 62.1102      , WithinRel( angle.distributions()[1].values()[29] ) );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[14].cosines()[0] ) );
  CHECK_THAT( -0.995       , WithinRel( angle.distributions()[14].cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( angle.distributions()[14].cosines()[93] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[14].cosines()[94] ) );
  CHECK_THAT(  1.51157e-11 , WithinRel( angle.distributions()[14].values()[0] ) );
  CHECK_THAT(  6.43040e-10 , WithinRel( angle.distributions()[14].values()[1] ) );
  CHECK_THAT(   8.14179e+5 , WithinRel( angle.distributions()[14].values()[93] ) );
  CHECK_THAT(   9.84753e+5 , WithinRel( angle.distributions()[14].values()[94] ) );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[15].cosines()[0] ) );
  CHECK_THAT( -0.9999      , WithinRel( angle.distributions()[15].cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( angle.distributions()[15].cosines()[94] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[15].cosines()[95] ) );
  CHECK_THAT(  6.25670e-13 , WithinRel( angle.distributions()[15].values()[0] ) );
  CHECK_THAT(  1.25808e-11 , WithinRel( angle.distributions()[15].values()[1] ) );
  CHECK_THAT(   8.15658e+5 , WithinRel( angle.distributions()[15].values()[94] ) );
  CHECK_THAT(   9.86945e+5 , WithinRel( angle.distributions()[15].values()[95] ) );
  CHECK( 15 == angle.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );
}

void verifyElectronBremsstrahlungPhotonProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "g" ) == chunk.identifier() );
  CHECK( true == chunk.isLinearised() );
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( true == chunk.hasDistributionData() );

  CHECK( true == std::holds_alternative< int >( chunk.multiplicity() ) );
  auto multiplicity = std::get< int >( chunk.multiplicity() );
  CHECK( 1 == multiplicity );

  CHECK( std::nullopt == chunk.averageEnergy() );

  CHECK( std::nullopt != chunk.distributionData() );
  CHECK( true == std::holds_alternative< UncorrelatedDistributionData >( chunk.distributionData().value() ) );
  auto data = std::get< UncorrelatedDistributionData >( chunk.distributionData().value() );
  CHECK( DistributionDataType::Uncorrelated == data.type() );
  CHECK( true == std::holds_alternative< IsotropicAngularDistributions >( data.angle() ) );
  CHECK( true == std::holds_alternative< TabulatedEnergyDistributions >( data.energy() ) );
  auto energy = std::get< TabulatedEnergyDistributions >( data.energy() );
  CHECK( 10 == energy.numberPoints() );
  CHECK( 1 == energy.numberRegions() );
  CHECK( 10 == energy.grid().size() );
  CHECK( 10 == energy.distributions().size() );
  CHECK( 1 == energy.boundaries().size() );
  CHECK( 1 == energy.interpolants().size() );
  CHECK_THAT(   10.   , WithinRel( energy.grid()[0] ) );
  CHECK_THAT(   20.736, WithinRel( energy.grid()[1] ) );
  CHECK_THAT(   1e+7  , WithinRel( energy.grid()[8] ) );
  CHECK_THAT(   1e+11 , WithinRel( energy.grid()[9] ) );
  CHECK(  17 == energy.distributions()[0].energies().size() );
  CHECK(  17 == energy.distributions()[0].values().size() );
  CHECK(  19 == energy.distributions()[1].energies().size() );
  CHECK(  19 == energy.distributions()[1].values().size() );
  CHECK(  85 == energy.distributions()[8].energies().size() );
  CHECK(  85 == energy.distributions()[8].values().size() );
  CHECK( 111 == energy.distributions()[9].energies().size() );
  CHECK( 111 == energy.distributions()[9].values().size() );
  CHECK_THAT(  0.1       , WithinRel( energy.distributions()[0].energies()[0] ) );
  CHECK_THAT(  0.133352  , WithinRel( energy.distributions()[0].energies()[1] ) );
  CHECK_THAT(  9.9       , WithinRel( energy.distributions()[0].energies()[15] ) );
  CHECK_THAT( 10.        , WithinRel( energy.distributions()[0].energies()[16] ) );
  CHECK_THAT( 2.1394     , WithinRel( energy.distributions()[0].values()[0] ) );
  CHECK_THAT( 1.60421    , WithinRel( energy.distributions()[0].values()[1] ) );
  CHECK_THAT(  .0214392  , WithinRel( energy.distributions()[0].values()[15] ) );
  CHECK_THAT(  .0212245  , WithinRel( energy.distributions()[0].values()[16] ) );
  CHECK_THAT(  0.1       , WithinRel( energy.distributions()[1].energies()[0] ) );
  CHECK_THAT(  0.14608   , WithinRel( energy.distributions()[1].energies()[1] ) );
  CHECK_THAT( 20.5286    , WithinRel( energy.distributions()[1].energies()[17] ) );
  CHECK_THAT( 20.736     , WithinRel( energy.distributions()[1].energies()[18] ) );
  CHECK_THAT( 1.84823    , WithinRel( energy.distributions()[1].values()[0] ) );
  CHECK_THAT( 1.26507    , WithinRel( energy.distributions()[1].values()[1] ) );
  CHECK_THAT(  .00885527 , WithinRel( energy.distributions()[1].values()[17] ) );
  CHECK_THAT(  .00876641 , WithinRel( energy.distributions()[1].values()[18] ) );
  CHECK_THAT( .100000000 , WithinRel( energy.distributions()[8].energies()[0] ) );
  CHECK_THAT( .128640000 , WithinRel( energy.distributions()[8].energies()[1] ) );
  CHECK_THAT(  9981470.  , WithinRel( energy.distributions()[8].energies()[83] ) );
  CHECK_THAT(  1e+7      , WithinRel( energy.distributions()[8].energies()[84] ) );
  CHECK_THAT( .608334000 , WithinRel( energy.distributions()[8].values()[0] ) );
  CHECK_THAT( .472898000 , WithinRel( energy.distributions()[8].values()[1] ) );
  CHECK_THAT( 9.28343e-12, WithinRel( energy.distributions()[8].values()[83] ) );
  CHECK_THAT( 5.8374e-12 , WithinRel( energy.distributions()[8].values()[84] ) );
  CHECK_THAT(  .100000000, WithinRel( energy.distributions()[9].energies()[0] ) );
  CHECK_THAT(  .148551000, WithinRel( energy.distributions()[9].energies()[1] ) );
  CHECK_THAT( 9.99082E+10, WithinRel( energy.distributions()[9].energies()[109] ) );
  CHECK_THAT(       1e+11, WithinRel( energy.distributions()[9].energies()[110] ) );
  CHECK_THAT(  .365591000, WithinRel( energy.distributions()[9].values()[0] ) );
  CHECK_THAT(  .246105000, WithinRel( energy.distributions()[9].values()[1] ) );
  CHECK_THAT( 9.06486E-16, WithinRel( energy.distributions()[9].values()[109] ) );
  CHECK_THAT( 5.16344E-16, WithinRel( energy.distributions()[9].values()[110] ) );
  CHECK( 9 == energy.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );
}

void verifyElectronBremsstrahlungElectronProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "e-" ) == chunk.identifier() );
  CHECK( true == chunk.isLinearised() );
  CHECK( true == chunk.hasAverageEnergy() );
  CHECK( false == chunk.hasDistributionData() );

  CHECK( true == std::holds_alternative< int >( chunk.multiplicity() ) );
  auto multiplicity = std::get< int >( chunk.multiplicity() );
  CHECK( 1 == multiplicity );

  CHECK( std::nullopt != chunk.averageEnergy() );
  auto average = chunk.averageEnergy().value();
  CHECK( true == average.isLinearised() );
  CHECK( 82 == average.numberPoints() );
  CHECK( 1 == average.numberRegions() );
  CHECK( 82 == average.energies().size() );
  CHECK( 82 == average.values().size() );
  CHECK( 1 == average.boundaries().size() );
  CHECK( 1 == average.interpolants().size() );
  CHECK( 81 == average.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == average.interpolants()[0] );
  CHECK_THAT( 10.        , WithinRel( average.energies()[0] ) );
  CHECK_THAT( 14.4       , WithinRel( average.energies()[1] ) );
  CHECK_THAT( 7.86876E+10, WithinRel( average.energies()[80] ) );
  CHECK_THAT(       1e+11, WithinRel( average.energies()[81] ) );
  CHECK_THAT(  10.         - 2.14426   , WithinRel( average.values()[0] ) );
  CHECK_THAT(  14.4        - 2.87181   , WithinRel( average.values()[1] ) );
  CHECK_THAT(  7.86876E+10 - 2.11850E+9, WithinRel( average.values()[80] ) );
  CHECK_THAT(  1e+11       - 2.66810E+9, WithinRel( average.values()[81] ) );

  CHECK( std::nullopt == chunk.distributionData() );
}
