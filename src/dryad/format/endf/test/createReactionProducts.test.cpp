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
void verifyPhotonCoherentProduct( const ReactionProduct& );

SCENARIO( "createReactionProducts" ) {

  GIVEN( "ENDF reaction products - electro-atomic interactions" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material is given" ) {

      THEN( "a reaction products can be created" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H1" );

        std::vector< ReactionProduct > products = format::endf::createReactionProducts( projectile, target, material, 527 );

        CHECK( 2 == products.size() );
        verifyElectronBremsstrahlungPhotonProduct( products[0] );
        verifyElectronBremsstrahlungElectronProduct( products[1] );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF reaction products - photo-atomic interactions" ) {

    auto tape = njoy::ENDFtk::tree::fromFile( "photoat-001_H_000.endf" );
    auto material = tape.materials().front();

    WHEN( "a single ENDF material is given" ) {

      THEN( "a reaction products can be created" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H1" );

        std::vector< ReactionProduct > products = format::endf::createReactionProducts( projectile, target, material, 502 );

        CHECK( 1 == products.size() );
        verifyPhotonCoherentProduct( products[0] );
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
  CHECK(  17 == energy.distributions()[0].pdf().energies().size() );
  CHECK(  17 == energy.distributions()[0].pdf().values().size() );
  CHECK(  19 == energy.distributions()[1].pdf().energies().size() );
  CHECK(  19 == energy.distributions()[1].pdf().values().size() );
  CHECK(  85 == energy.distributions()[8].pdf().energies().size() );
  CHECK(  85 == energy.distributions()[8].pdf().values().size() );
  CHECK( 111 == energy.distributions()[9].pdf().energies().size() );
  CHECK( 111 == energy.distributions()[9].pdf().values().size() );

  // dryad normalises distributions upon construction
  // the numbers in the tests given below are the values as found in the test
  // file so they need to be normalised. the following values are the scaling
  // factors that need to be applied (calculated by integrating the distributions
  // in excel).
  double scale00 = 1. / 0.99999998809250;
  double scale01 = 1. / 0.99999998353900;
  double scale08 = 1. / 0.99999973884057;
  double scale09 = 1. / 0.99999993564706;

  CHECK_THAT(            0.1       , WithinRel( energy.distributions()[0].pdf().energies()[0] ) );
  CHECK_THAT(            0.133352  , WithinRel( energy.distributions()[0].pdf().energies()[1] ) );
  CHECK_THAT(            9.9       , WithinRel( energy.distributions()[0].pdf().energies()[15] ) );
  CHECK_THAT(           10.        , WithinRel( energy.distributions()[0].pdf().energies()[16] ) );
  CHECK_THAT( scale00 *  2.1394    , WithinRel( energy.distributions()[0].pdf().values()[0] ) );
  CHECK_THAT( scale00 *  1.60421   , WithinRel( energy.distributions()[0].pdf().values()[1] ) );
  CHECK_THAT( scale00 *   .0214392 , WithinRel( energy.distributions()[0].pdf().values()[15] ) );
  CHECK_THAT( scale00 *   .0212245 , WithinRel( energy.distributions()[0].pdf().values()[16] ) );
  CHECK_THAT(            0.1       , WithinRel( energy.distributions()[1].pdf().energies()[0] ) );
  CHECK_THAT(            0.14608   , WithinRel( energy.distributions()[1].pdf().energies()[1] ) );
  CHECK_THAT(           20.5286    , WithinRel( energy.distributions()[1].pdf().energies()[17] ) );
  CHECK_THAT(           20.736     , WithinRel( energy.distributions()[1].pdf().energies()[18] ) );
  CHECK_THAT( scale01 * 1.84823    , WithinRel( energy.distributions()[1].pdf().values()[0] ) );
  CHECK_THAT( scale01 * 1.26507    , WithinRel( energy.distributions()[1].pdf().values()[1] ) );
  CHECK_THAT( scale01 *  .00885527 , WithinRel( energy.distributions()[1].pdf().values()[17] ) );
  CHECK_THAT( scale01 *  .00876641 , WithinRel( energy.distributions()[1].pdf().values()[18] ) );
  CHECK_THAT(           .100000000 , WithinRel( energy.distributions()[8].pdf().energies()[0] ) );
  CHECK_THAT(           .128640000 , WithinRel( energy.distributions()[8].pdf().energies()[1] ) );
  CHECK_THAT(            9981470.  , WithinRel( energy.distributions()[8].pdf().energies()[83] ) );
  CHECK_THAT(            1e+7      , WithinRel( energy.distributions()[8].pdf().energies()[84] ) );
  CHECK_THAT( scale08 * .608334000 , WithinRel( energy.distributions()[8].pdf().values()[0] ) );
  CHECK_THAT( scale08 * .472898000 , WithinRel( energy.distributions()[8].pdf().values()[1] ) );
  CHECK_THAT( scale08 * 9.28343e-12, WithinRel( energy.distributions()[8].pdf().values()[83] ) );
  CHECK_THAT( scale08 * 5.8374e-12 , WithinRel( energy.distributions()[8].pdf().values()[84] ) );
  CHECK_THAT(            .100000000, WithinRel( energy.distributions()[9].pdf().energies()[0] ) );
  CHECK_THAT(            .148551000, WithinRel( energy.distributions()[9].pdf().energies()[1] ) );
  CHECK_THAT(           9.99082E+10, WithinRel( energy.distributions()[9].pdf().energies()[109] ) );
  CHECK_THAT(                 1e+11, WithinRel( energy.distributions()[9].pdf().energies()[110] ) );
  CHECK_THAT( scale09 *  .365591000, WithinRel( energy.distributions()[9].pdf().values()[0] ) );
  CHECK_THAT( scale09 *  .246105000, WithinRel( energy.distributions()[9].pdf().values()[1] ) );
  CHECK_THAT( scale09 * 9.06486E-16, WithinRel( energy.distributions()[9].pdf().values()[109] ) );
  CHECK_THAT( scale09 * 5.16344E-16, WithinRel( energy.distributions()[9].pdf().values()[110] ) );
  CHECK( false == energy.distributions()[0].hasCdf() );
  CHECK( false == energy.distributions()[1].hasCdf() );
  CHECK( false == energy.distributions()[8].hasCdf() );
  CHECK( false == energy.distributions()[9].hasCdf() );
  CHECK_THROWS( energy.distributions()[0].cdf() );
  CHECK_THROWS( energy.distributions()[1].cdf() );
  CHECK_THROWS( energy.distributions()[8].cdf() );
  CHECK_THROWS( energy.distributions()[9].cdf() );
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
