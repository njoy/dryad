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
void verifyPhotonCoherentProduct( const ReactionProduct& );
void verifyPhotonIncoherentProduct( const ReactionProduct& );

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

  GIVEN( "ENDF reaction products - photo-atomic interactions" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "photoat-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF reaction product is given" ) {

      THEN( "a Reaction can be created" ) {

        auto coherent = tape.materials().front().section( 27, 502 ).parse< 27 >();
        auto real = std::make_optional( tape.materials().front().section( 27, 505 ).parse< 27 >() );
        auto imaginary = std::make_optional( tape.materials().front().section( 27, 506 ).parse< 27 >() );
        auto incoherent = tape.materials().front().section( 27, 504 ).parse< 27 >();

        id::ParticleID projectile( "g" );
        id::ParticleID target( "H1" );

        ReactionProduct coherent_product = format::endf::createReactionProduct( projectile, target, coherent, real, imaginary, 502 );
        verifyPhotonCoherentProduct( coherent_product );

        ReactionProduct incoherent_product = format::endf::createReactionProduct( projectile, target, incoherent, 504 );
        verifyPhotonIncoherentProduct( incoherent_product );
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
  CHECK(  2 == angle.distributions()[0].pdf().cosines().size() );
  CHECK(  2 == angle.distributions()[0].pdf().values().size() );
  CHECK( 30 == angle.distributions()[1].pdf().cosines().size() );
  CHECK( 30 == angle.distributions()[1].pdf().values().size() );
  CHECK( 95 == angle.distributions()[14].pdf().cosines().size() );
  CHECK( 95 == angle.distributions()[14].pdf().values().size() );
  CHECK( 96 == angle.distributions()[15].pdf().cosines().size() );
  CHECK( 96 == angle.distributions()[15].pdf().values().size() );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT(  0.5         , WithinRel( angle.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0.5         , WithinRel( angle.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT( -0.93        , WithinRel( angle.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9962001   , WithinRel( angle.distributions()[1].pdf().cosines()[28] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[1].pdf().cosines()[29] ) );
  CHECK_THAT(  0.00293923  , WithinRel( angle.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0.00314865  , WithinRel( angle.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 42.358       , WithinRel( angle.distributions()[1].pdf().values()[28] ) );
  CHECK_THAT( 62.1102      , WithinRel( angle.distributions()[1].pdf().values()[29] ) );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[14].pdf().cosines()[0] ) );
  CHECK_THAT( -0.995       , WithinRel( angle.distributions()[14].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( angle.distributions()[14].pdf().cosines()[93] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[14].pdf().cosines()[94] ) );
  CHECK_THAT(  1.51157e-11 , WithinRel( angle.distributions()[14].pdf().values()[0] ) );
  CHECK_THAT(  6.43040e-10 , WithinRel( angle.distributions()[14].pdf().values()[1] ) );
  CHECK_THAT(   8.14179e+5 , WithinRel( angle.distributions()[14].pdf().values()[93] ) );
  CHECK_THAT(   9.84753e+5 , WithinRel( angle.distributions()[14].pdf().values()[94] ) );
  CHECK_THAT( -1.          , WithinRel( angle.distributions()[15].pdf().cosines()[0] ) );
  CHECK_THAT( -0.9999      , WithinRel( angle.distributions()[15].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989   , WithinRel( angle.distributions()[15].pdf().cosines()[94] ) );
  CHECK_THAT(  0.999999    , WithinRel( angle.distributions()[15].pdf().cosines()[95] ) );
  CHECK_THAT(  6.25670e-13 , WithinRel( angle.distributions()[15].pdf().values()[0] ) );
  CHECK_THAT(  1.25808e-11 , WithinRel( angle.distributions()[15].pdf().values()[1] ) );
  CHECK_THAT(   8.15658e+5 , WithinRel( angle.distributions()[15].pdf().values()[94] ) );
  CHECK_THAT(   9.86945e+5 , WithinRel( angle.distributions()[15].pdf().values()[95] ) );
  CHECK( std::nullopt == angle.distributions()[0].cdf() );
  CHECK( std::nullopt == angle.distributions()[1].cdf() );
  CHECK( std::nullopt == angle.distributions()[94].cdf() );
  CHECK( std::nullopt == angle.distributions()[95].cdf() );
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
  CHECK(  17 == energy.distributions()[0].pdf().energies().size() );
  CHECK(  17 == energy.distributions()[0].pdf().values().size() );
  CHECK(  19 == energy.distributions()[1].pdf().energies().size() );
  CHECK(  19 == energy.distributions()[1].pdf().values().size() );
  CHECK(  85 == energy.distributions()[8].pdf().energies().size() );
  CHECK(  85 == energy.distributions()[8].pdf().values().size() );
  CHECK( 111 == energy.distributions()[9].pdf().energies().size() );
  CHECK( 111 == energy.distributions()[9].pdf().values().size() );
  CHECK_THAT(  0.1       , WithinRel( energy.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT(  0.133352  , WithinRel( energy.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT(  9.9       , WithinRel( energy.distributions()[0].pdf().energies()[15] ) );
  CHECK_THAT( 10.        , WithinRel( energy.distributions()[0].pdf().energies()[16] ) );
  CHECK_THAT( 2.1394     , WithinRel( energy.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( 1.60421    , WithinRel( energy.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT(  .0214392  , WithinRel( energy.distributions()[0].pdf().values()[15] ) );
  CHECK_THAT(  .0212245  , WithinRel( energy.distributions()[0].pdf().values()[16] ) );
  CHECK_THAT(  0.1       , WithinRel( energy.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT(  0.14608   , WithinRel( energy.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT( 20.5286    , WithinRel( energy.distributions()[1].pdf().energies()[17] ) );
  CHECK_THAT( 20.736     , WithinRel( energy.distributions()[1].pdf().energies()[18] ) );
  CHECK_THAT( 1.84823    , WithinRel( energy.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT( 1.26507    , WithinRel( energy.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT(  .00885527 , WithinRel( energy.distributions()[1].pdf().values()[17] ) );
  CHECK_THAT(  .00876641 , WithinRel( energy.distributions()[1].pdf().values()[18] ) );
  CHECK_THAT( .100000000 , WithinRel( energy.distributions()[8].pdf().energies()[0] ) );
  CHECK_THAT( .128640000 , WithinRel( energy.distributions()[8].pdf().energies()[1] ) );
  CHECK_THAT(  9981470.  , WithinRel( energy.distributions()[8].pdf().energies()[83] ) );
  CHECK_THAT(  1e+7      , WithinRel( energy.distributions()[8].pdf().energies()[84] ) );
  CHECK_THAT( .608334000 , WithinRel( energy.distributions()[8].pdf().values()[0] ) );
  CHECK_THAT( .472898000 , WithinRel( energy.distributions()[8].pdf().values()[1] ) );
  CHECK_THAT( 9.28343e-12, WithinRel( energy.distributions()[8].pdf().values()[83] ) );
  CHECK_THAT( 5.8374e-12 , WithinRel( energy.distributions()[8].pdf().values()[84] ) );
  CHECK_THAT(  .100000000, WithinRel( energy.distributions()[9].pdf().energies()[0] ) );
  CHECK_THAT(  .148551000, WithinRel( energy.distributions()[9].pdf().energies()[1] ) );
  CHECK_THAT( 9.99082E+10, WithinRel( energy.distributions()[9].pdf().energies()[109] ) );
  CHECK_THAT(       1e+11, WithinRel( energy.distributions()[9].pdf().energies()[110] ) );
  CHECK_THAT(  .365591000, WithinRel( energy.distributions()[9].pdf().values()[0] ) );
  CHECK_THAT(  .246105000, WithinRel( energy.distributions()[9].pdf().values()[1] ) );
  CHECK_THAT( 9.06486E-16, WithinRel( energy.distributions()[9].pdf().values()[109] ) );
  CHECK_THAT( 5.16344E-16, WithinRel( energy.distributions()[9].pdf().values()[110] ) );
  CHECK( std::nullopt == energy.distributions()[0].cdf() );
  CHECK( std::nullopt == energy.distributions()[1].cdf() );
  CHECK( std::nullopt == energy.distributions()[8].cdf() );
  CHECK( std::nullopt == energy.distributions()[9].cdf() );
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

void verifyPhotonCoherentProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "g" ) == chunk.identifier() );
  CHECK( true == chunk.isLinearised() );
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( true == chunk.hasDistributionData() );

  CHECK( true == std::holds_alternative< int >( chunk.multiplicity() ) );
  auto multiplicity = std::get< int >( chunk.multiplicity() );
  CHECK( 1 == multiplicity );

  CHECK( std::nullopt == chunk.averageEnergy() );

  CHECK( std::nullopt != chunk.distributionData() );
  CHECK( true == std::holds_alternative< CoherentDistributionData >( chunk.distributionData().value() ) );
  auto data = std::get< CoherentDistributionData >( chunk.distributionData().value() );

  CHECK( DistributionDataType::Coherent == data.type() );
  CHECK( ReferenceFrame::CentreOfMass == data.frame() );

  CHECK_THAT( 0.  , WithinRel( data.scatteringFunction().lowerInverseLengthLimit() ) );
  CHECK_THAT( 1e+9, WithinRel( data.scatteringFunction().upperInverseLengthLimit() ) );
  CHECK( 1253 == data.scatteringFunction().inverseLengths().size() );
  CHECK( 1253 == data.scatteringFunction().values().size() );
  CHECK( 1 == data.scatteringFunction().boundaries().size() );
  CHECK( 1 == data.scatteringFunction().interpolants().size() );
  CHECK_THAT( 0.       , WithinRel( data.scatteringFunction().inverseLengths()[0] ) );
  CHECK_THAT( 0.001    , WithinRel( data.scatteringFunction().inverseLengths()[1] ) );
  CHECK_THAT( 512000000, WithinRel( data.scatteringFunction().inverseLengths()[1251] ) );
  CHECK_THAT( 1e+9     , WithinRel( data.scatteringFunction().inverseLengths()[1252] ) );
  CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[0] ) );
  CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[1] ) );
  CHECK_THAT( 1.1908E-37, WithinRel( data.scatteringFunction().values()[1251] ) );
  CHECK_THAT( 8.1829e-39, WithinRel( data.scatteringFunction().values()[1252] ) );
  CHECK( 1252 == data.scatteringFunction().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == data.scatteringFunction().interpolants()[0] );
  CHECK( true == data.scatteringFunction().isLinearised() );

  CHECK( std::nullopt != data.realAnomolousFormFactor() );
  auto factor = data.realAnomolousFormFactor().value();
  CHECK_THAT( 1.  , WithinRel( factor.lowerEnergyLimit() ) );
  CHECK_THAT( 1e+7, WithinRel( factor.upperEnergyLimit() ) );
  CHECK( 297 == factor.energies().size() );
  CHECK( 297 == factor.values().size() );
  CHECK( 1 == factor.boundaries().size() );
  CHECK( 1 == factor.interpolants().size() );
  CHECK_THAT( 1.        , WithinRel( factor.energies()[0] ) );
  CHECK_THAT( 2.        , WithinRel( factor.energies()[1] ) );
  CHECK_THAT( 9549925.86, WithinRel( factor.energies()[295] ) );
  CHECK_THAT( 1e+7      , WithinRel( factor.energies()[296] ) );
  CHECK_THAT( 0.        , WithinRel( factor.values()[0] ) );
  CHECK_THAT( 0.        , WithinRel( factor.values()[1] ) );
  CHECK_THAT( 8.9767E-15, WithinRel( factor.values()[295] ) );
  CHECK_THAT( 0.        , WithinRel( factor.values()[296] ) );
  CHECK( 296 == factor.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == factor.interpolants()[0] );
  CHECK( true == factor.isLinearised() );

  CHECK( std::nullopt != data.imaginaryAnomolousFormFactor() );
  factor = data.imaginaryAnomolousFormFactor().value();
  CHECK_THAT( 1.  , WithinRel( factor.lowerEnergyLimit() ) );
  CHECK_THAT( 1e+7, WithinRel( factor.upperEnergyLimit() ) );
  CHECK( 297 == factor.energies().size() );
  CHECK( 297 == factor.values().size() );
  CHECK( 1 == factor.boundaries().size() );
  CHECK( 1 == factor.interpolants().size() );
  CHECK_THAT( 1.        , WithinRel( factor.energies()[0] ) );
  CHECK_THAT( 2.        , WithinRel( factor.energies()[1] ) );
  CHECK_THAT( 9549925.86, WithinRel( factor.energies()[295] ) );
  CHECK_THAT( 1e+7      , WithinRel( factor.energies()[296] ) );
  CHECK_THAT( -1.00260813, WithinRel( factor.values()[0] ) );
  CHECK_THAT( -1.01054501, WithinRel( factor.values()[1] ) );
  CHECK_THAT( 2.8024E-11, WithinRel( factor.values()[295] ) );
  CHECK_THAT( 0.        , WithinRel( factor.values()[296] ) );
  CHECK( 296 == factor.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == factor.interpolants()[0] );
  CHECK( true == factor.isLinearised() );
}

void verifyPhotonIncoherentProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "g" ) == chunk.identifier() );
  CHECK( true == chunk.isLinearised() );
  CHECK( false == chunk.hasAverageEnergy() );
  CHECK( true == chunk.hasDistributionData() );

  CHECK( true == std::holds_alternative< int >( chunk.multiplicity() ) );
  auto multiplicity = std::get< int >( chunk.multiplicity() );
  CHECK( 1 == multiplicity );

  CHECK( std::nullopt == chunk.averageEnergy() );

  CHECK( std::nullopt != chunk.distributionData() );
  CHECK( true == std::holds_alternative< IncoherentDistributionData >( chunk.distributionData().value() ) );
  auto data = std::get< IncoherentDistributionData >( chunk.distributionData().value() );

  CHECK( DistributionDataType::Incoherent == data.type() );
  CHECK( ReferenceFrame::CentreOfMass == data.frame() );

  CHECK_THAT( 0.  , WithinRel( data.scatteringFunction().lowerInverseLengthLimit() ) );
  CHECK_THAT( 1e+9, WithinRel( data.scatteringFunction().upperInverseLengthLimit() ) );
  CHECK( 398 == data.scatteringFunction().inverseLengths().size() );
  CHECK( 398 == data.scatteringFunction().values().size() );
  CHECK( 1 == data.scatteringFunction().boundaries().size() );
  CHECK( 1 == data.scatteringFunction().interpolants().size() );
  CHECK_THAT( 0.       , WithinRel( data.scatteringFunction().inverseLengths()[0] ) );
  CHECK_THAT( 1e-7     , WithinRel( data.scatteringFunction().inverseLengths()[1] ) );
  CHECK_THAT( 512000000, WithinRel( data.scatteringFunction().inverseLengths()[396] ) );
  CHECK_THAT( 1e+9     , WithinRel( data.scatteringFunction().inverseLengths()[397] ) );
  CHECK_THAT( 0.        , WithinRel( data.scatteringFunction().values()[0] ) );
  CHECK_THAT( 4.4097E-13, WithinRel( data.scatteringFunction().values()[1] ) );
  CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[396] ) );
  CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[397] ) );
  CHECK( 397 == data.scatteringFunction().boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == data.scatteringFunction().interpolants()[0] );
  CHECK( true == data.scatteringFunction().isLinearised() );
}
