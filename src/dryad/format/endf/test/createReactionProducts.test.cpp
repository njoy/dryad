// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createReactionProducts.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyElectronBremsstrahlungPhotonProduct( const ReactionProduct& );
void verifyElectronBremsstrahlungElectronProduct( const ReactionProduct& );

SCENARIO( "createReactionProducts" ) {

  GIVEN( "ENDF reaction products - electro-atomic interactions" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material is given" ) {

      THEN( "a reaction products can be created" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H1" );

        std::vector< ReactionProduct > products = format::endf::createReactionProducts( projectile, target, material, 527 );

        verifyElectronBremsstrahlungPhotonProduct( products[0] );
        verifyElectronBremsstrahlungElectronProduct( products[1] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

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