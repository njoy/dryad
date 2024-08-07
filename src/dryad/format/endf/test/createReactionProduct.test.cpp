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
        ReactionProduct electron_elastic = format::endf::createReactionProduct( projectile, target, product );
        verifyElectronlargeAngleElasticElectronProduct( electron_elastic );

        product = bremsstrahlung.reactionProducts()[0];
        ReactionProduct photon_bremsstrahlung = format::endf::createReactionProduct( projectile, target, product );
        verifyElectronBremsstrahlungPhotonProduct( photon_bremsstrahlung );

        product = bremsstrahlung.reactionProducts()[1];
        ReactionProduct electron_bremsstrahlung = format::endf::createReactionProduct( projectile, target, product );
        verifyElectronBremsstrahlungElectronProduct( electron_bremsstrahlung );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyElectronlargeAngleElasticElectronProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "e-" ) == chunk.identifier() );
}

void verifyElectronBremsstrahlungPhotonProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "g" ) == chunk.identifier() );
}

void verifyElectronBremsstrahlungElectronProduct( const ReactionProduct& chunk ) {

  CHECK( id::ParticleID( "e-" ) == chunk.identifier() );
}
