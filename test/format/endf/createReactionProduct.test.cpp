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

void verifyElectronlargeAngleElasticElectronProduct( const ReactionProduct&, bool );
void verifyElectronBremsstrahlungPhotonProduct( const ReactionProduct&, bool );
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
        ReactionProduct electron_elastic1 = format::endf::createReactionProduct( projectile, target, product, 525, false );
        ReactionProduct electron_elastic2 = format::endf::createReactionProduct( projectile, target, product, 525, true );
        verifyElectronlargeAngleElasticElectronProduct( electron_elastic1, false );
        verifyElectronlargeAngleElasticElectronProduct( electron_elastic2, true );

        product = bremsstrahlung.reactionProducts()[0];
        ReactionProduct photon_bremsstrahlung1 = format::endf::createReactionProduct( projectile, target, product, 527, false );
        ReactionProduct photon_bremsstrahlung2 = format::endf::createReactionProduct( projectile, target, product, 527, true );
        verifyElectronBremsstrahlungPhotonProduct( photon_bremsstrahlung1, false );
        verifyElectronBremsstrahlungPhotonProduct( photon_bremsstrahlung2, true );

        product = bremsstrahlung.reactionProducts()[1];
        ReactionProduct electron_bremsstrahlung1 = format::endf::createReactionProduct( projectile, target, product, 527, false );
        ReactionProduct electron_bremsstrahlung2 = format::endf::createReactionProduct( projectile, target, product, 527, true );
        verifyElectronBremsstrahlungElectronProduct( electron_bremsstrahlung1 );
        verifyElectronBremsstrahlungElectronProduct( electron_bremsstrahlung2 );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF reaction products - photo-atomic interactions" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "photoat-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF reaction product is given" ) {

      THEN( "a Reaction can be created" ) {

        auto coherent = tape.materials().front().section( 27, 502 ).parse< 27 >();
        auto real = std::make_optional( tape.materials().front().section( 27, 506 ).parse< 27 >() );
        auto imaginary = std::make_optional( tape.materials().front().section( 27, 505 ).parse< 27 >() );
        auto incoherent = tape.materials().front().section( 27, 504 ).parse< 27 >();

        id::ParticleID projectile( "g" );
        id::ParticleID target( "H1" );

        ReactionProduct coherent_product1 = format::endf::createReactionProduct( projectile, target, coherent, real, imaginary, 502, false );
        ReactionProduct coherent_product2 = format::endf::createReactionProduct( projectile, target, coherent, real, imaginary, 502, true );
        verifyPhotonCoherentProduct( coherent_product1 );
        verifyPhotonCoherentProduct( coherent_product2 );

        ReactionProduct incoherent_product1 = format::endf::createReactionProduct( projectile, target, incoherent, 504, false );
        ReactionProduct incoherent_product2 = format::endf::createReactionProduct( projectile, target, incoherent, 504, false );
        verifyPhotonIncoherentProduct( incoherent_product1 );
        verifyPhotonIncoherentProduct( incoherent_product2 );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyElectronlargeAngleElasticElectronProduct( const ReactionProduct& chunk,
                                                     bool normalise ) {

  CHECK( id::ParticleID( "e-" ) == chunk.identifier() );
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

  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double normalisation00 = normalise ? 0.9999995 : 1.;
  double normalisation01 = normalise ? 1.00000016366000 : 1.;
  double normalisation14 = normalise ? 1.00000048323214 : 1.;
  double normalisation15 = normalise ? 1.00000000937718 : 1.;

  CHECK_THAT( -1.                           , WithinRel( angle.distributions()[0].pdf().cosines()[0] ) );
  CHECK_THAT(  0.999999                     , WithinRel( angle.distributions()[0].pdf().cosines()[1] ) );
  CHECK_THAT(  0.5 / normalisation00        , WithinRel( angle.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(  0.5 / normalisation00        , WithinRel( angle.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( -1.                           , WithinRel( angle.distributions()[1].pdf().cosines()[0] ) );
  CHECK_THAT( -0.93                         , WithinRel( angle.distributions()[1].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9962001                    , WithinRel( angle.distributions()[1].pdf().cosines()[28] ) );
  CHECK_THAT(  0.999999                     , WithinRel( angle.distributions()[1].pdf().cosines()[29] ) );
  CHECK_THAT(  0.00293923 / normalisation01 , WithinRel( angle.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(  0.00314865 / normalisation01 , WithinRel( angle.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( 42.358      / normalisation01 , WithinRel( angle.distributions()[1].pdf().values()[28] ) );
  CHECK_THAT( 62.1102     / normalisation01 , WithinRel( angle.distributions()[1].pdf().values()[29] ) );
  CHECK_THAT( -1.                           , WithinRel( angle.distributions()[14].pdf().cosines()[0] ) );
  CHECK_THAT( -0.995                        , WithinRel( angle.distributions()[14].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                    , WithinRel( angle.distributions()[14].pdf().cosines()[93] ) );
  CHECK_THAT(  0.999999                     , WithinRel( angle.distributions()[14].pdf().cosines()[94] ) );
  CHECK_THAT(  1.51157e-11 / normalisation14, WithinRel( angle.distributions()[14].pdf().values()[0] ) );
  CHECK_THAT(  6.43040e-10 / normalisation14, WithinRel( angle.distributions()[14].pdf().values()[1] ) );
  CHECK_THAT(  8.14179e+5 / normalisation14 , WithinRel( angle.distributions()[14].pdf().values()[93] ) );
  CHECK_THAT(  9.84753e+5 / normalisation14 , WithinRel( angle.distributions()[14].pdf().values()[94] ) );
  CHECK_THAT( -1.                           , WithinRel( angle.distributions()[15].pdf().cosines()[0] ) );
  CHECK_THAT( -0.9999                       , WithinRel( angle.distributions()[15].pdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                    , WithinRel( angle.distributions()[15].pdf().cosines()[94] ) );
  CHECK_THAT(  0.999999                     , WithinRel( angle.distributions()[15].pdf().cosines()[95] ) );
  CHECK_THAT(  6.25670e-13 / normalisation15, WithinRel( angle.distributions()[15].pdf().values()[0] ) );
  CHECK_THAT(  1.25808e-11 / normalisation15, WithinRel( angle.distributions()[15].pdf().values()[1] ) );
  CHECK_THAT(  8.15658e+5 / normalisation15 , WithinRel( angle.distributions()[15].pdf().values()[94] ) );
  CHECK_THAT(  9.86945e+5 / normalisation15 , WithinRel( angle.distributions()[15].pdf().values()[95] ) );

  CHECK(  2 == angle.distributions()[0].cdf().cosines().size() );
  CHECK(  2 == angle.distributions()[0].cdf().values().size() );
  CHECK( 30 == angle.distributions()[1].cdf().cosines().size() );
  CHECK( 30 == angle.distributions()[1].cdf().values().size() );
  CHECK( 95 == angle.distributions()[14].cdf().cosines().size() );
  CHECK( 95 == angle.distributions()[14].cdf().values().size() );
  CHECK( 96 == angle.distributions()[15].cdf().cosines().size() );
  CHECK( 96 == angle.distributions()[15].cdf().values().size() );

  CHECK_THAT( -1.                                    , WithinRel( angle.distributions()[0].cdf().cosines()[0] ) );
  CHECK_THAT(  0.999999                              , WithinRel( angle.distributions()[0].cdf().cosines()[1] ) );
  CHECK_THAT(  0.            / normalisation00       , WithinRel( angle.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(  1.999999 / 2. / normalisation00       , WithinRel( angle.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT( -1.                                    , WithinRel( angle.distributions()[1].cdf().cosines()[0] ) );
  CHECK_THAT( -0.93                                  , WithinRel( angle.distributions()[1].cdf().cosines()[1] ) );
  CHECK_THAT(  0.9962001                             , WithinRel( angle.distributions()[1].cdf().cosines()[28] ) );
  CHECK_THAT(  0.999999                              , WithinRel( angle.distributions()[1].cdf().cosines()[29] ) );
  CHECK_THAT(  0.0           / normalisation01       , WithinRel( angle.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(  0.0002130758  / normalisation01       , WithinRel( angle.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT(  0.80156804117 / normalisation01       , WithinRel( angle.distributions()[1].cdf().values()[28] ) );
  CHECK_THAT(  1.00000016366 / normalisation01       , WithinRel( angle.distributions()[1].cdf().values()[29] ) );
  CHECK_THAT( -1.                                    , WithinRel( angle.distributions()[14].cdf().cosines()[0] ) );
  CHECK_THAT( -0.995                                 , WithinRel( angle.distributions()[14].cdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                             , WithinRel( angle.distributions()[14].cdf().cosines()[93] ) );
  CHECK_THAT(  0.999999                              , WithinRel( angle.distributions()[14].cdf().cosines()[94] ) );
  CHECK_THAT(  0.               / normalisation14    , WithinRel( angle.distributions()[14].cdf().values()[0] ) );
  CHECK_THAT(  1.645389250e-12  / normalisation14    , WithinRel( angle.distributions()[14].cdf().values()[1] ) );
  CHECK_THAT(  0.91005388327948 / normalisation14    , WithinRel( angle.distributions()[14].cdf().values()[93] ) );
  CHECK_THAT(  1.00000048323214 / normalisation14    , WithinRel( angle.distributions()[14].cdf().values()[94] ) );
  CHECK_THAT( -1.                                    , WithinRel( angle.distributions()[15].cdf().cosines()[0] ) );
  CHECK_THAT( -0.9999                                , WithinRel( angle.distributions()[15].cdf().cosines()[1] ) );
  CHECK_THAT(  0.9999989                             , WithinRel( angle.distributions()[15].cdf().cosines()[94] ) );
  CHECK_THAT(  0.999999                              , WithinRel( angle.distributions()[15].cdf().cosines()[95] ) );
  CHECK_THAT(  0.                   / normalisation15, WithinRel( angle.distributions()[15].cdf().values()[0] ) );
  CHECK_THAT(  6.60323499999927e-16 / normalisation15, WithinRel( angle.distributions()[15].cdf().values()[1] ) );
  CHECK_THAT(  0.90986985942462     / normalisation15, WithinRel( angle.distributions()[15].cdf().values()[94] ) );
  CHECK_THAT(  1.00000000937718     / normalisation15, WithinRel( angle.distributions()[15].cdf().values()[95] ) );

  CHECK( 15 == angle.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );
}

void verifyElectronBremsstrahlungPhotonProduct( const ReactionProduct& chunk,
                                                bool normalise ) {

  CHECK( id::ParticleID( "g" ) == chunk.identifier() );
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

  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double normalisation00 = normalise ? 0.99999998809250 : 1.;
  double normalisation01 = normalise ? 0.99999998353900 : 1.;
  double normalisation08 = normalise ? 0.99999973884057 : 1.;
  double normalisation09 = normalise ? 0.99999993564706 : 1.;

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
  CHECK_THAT(        0.1        , WithinRel( energy.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT(        0.133352   , WithinRel( energy.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT(        9.9        , WithinRel( energy.distributions()[0].pdf().energies()[15] ) );
  CHECK_THAT(       10.         , WithinRel( energy.distributions()[0].pdf().energies()[16] ) );
  CHECK_THAT(        2.1394     / normalisation00, WithinRel( energy.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT(        1.60421    / normalisation00, WithinRel( energy.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT(         .0214392  / normalisation00, WithinRel( energy.distributions()[0].pdf().values()[15] ) );
  CHECK_THAT(         .0212245  / normalisation00, WithinRel( energy.distributions()[0].pdf().values()[16] ) );
  CHECK_THAT(       0.1         , WithinRel( energy.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT(       0.14608     , WithinRel( energy.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT(      20.5286      , WithinRel( energy.distributions()[1].pdf().energies()[17] ) );
  CHECK_THAT(      20.736       , WithinRel( energy.distributions()[1].pdf().energies()[18] ) );
  CHECK_THAT(       1.84823     / normalisation01, WithinRel( energy.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT(       1.26507     / normalisation01, WithinRel( energy.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT(        .00885527  / normalisation01, WithinRel( energy.distributions()[1].pdf().values()[17] ) );
  CHECK_THAT(        .00876641  / normalisation01, WithinRel( energy.distributions()[1].pdf().values()[18] ) );
  CHECK_THAT(        .100000000 , WithinRel( energy.distributions()[8].pdf().energies()[0] ) );
  CHECK_THAT(        .128640000 , WithinRel( energy.distributions()[8].pdf().energies()[1] ) );
  CHECK_THAT( 9981470.          , WithinRel( energy.distributions()[8].pdf().energies()[83] ) );
  CHECK_THAT(    1e+7           , WithinRel( energy.distributions()[8].pdf().energies()[84] ) );
  CHECK_THAT(        .608334000 / normalisation08, WithinRel( energy.distributions()[8].pdf().values()[0] ) );
  CHECK_THAT(        .472898000 / normalisation08, WithinRel( energy.distributions()[8].pdf().values()[1] ) );
  CHECK_THAT(       9.28343e-12 / normalisation08, WithinRel( energy.distributions()[8].pdf().values()[83] ) );
  CHECK_THAT(       5.8374e-12  / normalisation08, WithinRel( energy.distributions()[8].pdf().values()[84] ) );
  CHECK_THAT(        .100000000 , WithinRel( energy.distributions()[9].pdf().energies()[0] ) );
  CHECK_THAT(        .148551000 , WithinRel( energy.distributions()[9].pdf().energies()[1] ) );
  CHECK_THAT(       9.99082E+10 , WithinRel( energy.distributions()[9].pdf().energies()[109] ) );
  CHECK_THAT(   1e+11           , WithinRel( energy.distributions()[9].pdf().energies()[110] ) );
  CHECK_THAT(       .365591000  / normalisation09, WithinRel( energy.distributions()[9].pdf().values()[0] ) );
  CHECK_THAT(       .246105000  / normalisation09, WithinRel( energy.distributions()[9].pdf().values()[1] ) );
  CHECK_THAT(      9.06486E-16  / normalisation09, WithinRel( energy.distributions()[9].pdf().values()[109] ) );
  CHECK_THAT(      5.16344E-16  / normalisation09, WithinRel( energy.distributions()[9].pdf().values()[110] ) );
  CHECK(  17 == energy.distributions()[0].cdf().energies().size() );
  CHECK(  17 == energy.distributions()[0].cdf().values().size() );
  CHECK(  19 == energy.distributions()[1].cdf().energies().size() );
  CHECK(  19 == energy.distributions()[1].cdf().values().size() );
  CHECK(  85 == energy.distributions()[8].cdf().energies().size() );
  CHECK(  85 == energy.distributions()[8].cdf().values().size() );
  CHECK( 111 == energy.distributions()[9].cdf().energies().size() );
  CHECK( 111 == energy.distributions()[9].cdf().values().size() );
  CHECK_THAT(        0.1        , WithinRel( energy.distributions()[0].cdf().energies()[0] ) );
  CHECK_THAT(        0.133352   , WithinRel( energy.distributions()[0].cdf().energies()[1] ) );
  CHECK_THAT(        9.9        , WithinRel( energy.distributions()[0].cdf().energies()[15] ) );
  CHECK_THAT(       10.         , WithinRel( energy.distributions()[0].cdf().energies()[16] ) );
  CHECK_THAT(   0.              / normalisation00, WithinRel( energy.distributions()[0].cdf().values()[0] ) );
  CHECK_THAT(   0.06242844036   / normalisation00, WithinRel( energy.distributions()[0].cdf().values()[1] ) );
  CHECK_THAT(   0.9978668030925 / normalisation00, WithinRel( energy.distributions()[0].cdf().values()[15] ) );
  CHECK_THAT(   0.9999999880925 / normalisation00, WithinRel( energy.distributions()[0].cdf().values()[16] ) );
  CHECK_THAT(       0.1         , WithinRel( energy.distributions()[1].cdf().energies()[0] ) );
  CHECK_THAT(       0.14608     , WithinRel( energy.distributions()[1].cdf().energies()[1] ) );
  CHECK_THAT(      20.5286      , WithinRel( energy.distributions()[1].cdf().energies()[17] ) );
  CHECK_THAT(      20.736       , WithinRel( energy.distributions()[1].cdf().energies()[18] ) );
  CHECK_THAT(   0.              / normalisation01, WithinRel( energy.distributions()[1].cdf().values()[0] ) );
  CHECK_THAT(   0.071730432     / normalisation01, WithinRel( energy.distributions()[1].cdf().values()[1] ) );
  CHECK_THAT(   0.998172615323  / normalisation01, WithinRel( energy.distributions()[1].cdf().values()[17] ) );
  CHECK_THAT(   0.9999999835390 / normalisation01, WithinRel( energy.distributions()[1].cdf().values()[18] ) );
  CHECK_THAT(        .100000000 , WithinRel( energy.distributions()[8].cdf().energies()[0] ) );
  CHECK_THAT(        .128640000 , WithinRel( energy.distributions()[8].cdf().energies()[1] ) );
  CHECK_THAT( 9981470.          , WithinRel( energy.distributions()[8].cdf().energies()[83] ) );
  CHECK_THAT(    1e+7           , WithinRel( energy.distributions()[8].cdf().energies()[84] ) );
  CHECK_THAT(   0.              / normalisation08, WithinRel( energy.distributions()[8].cdf().values()[0] ) );
  CHECK_THAT(   0.01548324224   / normalisation08, WithinRel( energy.distributions()[8].cdf().values()[1] ) );
  CHECK_THAT(   0.99999959874608 / normalisation08, WithinRel( energy.distributions()[8].cdf().values()[83] ) );
  CHECK_THAT(   0.99999973884057 / normalisation08, WithinRel( energy.distributions()[8].cdf().values()[84] ) );
  CHECK_THAT(        .100000000 , WithinRel( energy.distributions()[9].cdf().energies()[0] ) );
  CHECK_THAT(        .148551000 , WithinRel( energy.distributions()[9].cdf().energies()[1] ) );
  CHECK_THAT(       9.99082E+10 , WithinRel( energy.distributions()[9].cdf().energies()[109] ) );
  CHECK_THAT(   1e+11           , WithinRel( energy.distributions()[9].cdf().energies()[110] ) );
  CHECK_THAT(   0.              / normalisation09, WithinRel( energy.distributions()[9].cdf().values()[0] ) );
  CHECK_THAT(   0.014849226248  / normalisation09, WithinRel( energy.distributions()[9].cdf().values()[1] ) );
  CHECK_THAT(   0.99999987033916 / normalisation09, WithinRel( energy.distributions()[9].cdf().values()[109] ) );
  CHECK_THAT(   0.99999993564706 / normalisation09, WithinRel( energy.distributions()[9].cdf().values()[110] ) );
  CHECK( 9 == energy.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == energy.interpolants()[0] );
}

void verifyElectronBremsstrahlungElectronProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "e-" ) == chunk.identifier() );
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
  CHECK( ReferenceFrame::Laboratory == data.frame() );

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
  CHECK_THAT( -1.00260813, WithinRel( factor.values()[0] ) );
  CHECK_THAT( -1.01054501, WithinRel( factor.values()[1] ) );
  CHECK_THAT( 2.8024E-11, WithinRel( factor.values()[295] ) );
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
  CHECK_THAT( 0.        , WithinRel( factor.values()[0] ) );
  CHECK_THAT( 0.        , WithinRel( factor.values()[1] ) );
  CHECK_THAT( 8.9767E-15, WithinRel( factor.values()[295] ) );
  CHECK_THAT( 0.        , WithinRel( factor.values()[296] ) );
  CHECK( 296 == factor.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == factor.interpolants()[0] );
  CHECK( true == factor.isLinearised() );
}

void verifyPhotonIncoherentProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "g" ) == chunk.identifier() );
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
  CHECK( ReferenceFrame::Laboratory == data.frame() );

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
