// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/UnresolvedChannel.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "UnresolvedChannel" ) {

  GIVEN( "valid data for an UnresolvedChannel" ) {

    // identifiers
    id::ChannelID elasticID( "n,Cl35->n,Cl35{0,1,1+}" );
    id::ChannelID captureID( "n,Cl35->g,Cl36[all]{0,0,1+}" );

    id::ReactionID elasticRID( "n,Cl35->n,Cl35" );
    id::ReactionID captureRID( "n,Cl35->g,Cl36[all]" );

    // particles
    Particle g( id::ParticleID::photon(), 0, 1, +1 );
    Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
    Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
    Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );

    // particle pairs
    ParticlePair elasticPair( n, cl35 );
    ParticlePair capturePair( g, cl36 );

    // Q values
    double elasticQ = 0.0;
    double captureQ = 0.0;

    // boundary conditions
    std::optional< double > elasticBoundary = std::nullopt;
    std::optional< double > captureBoundary = std::nullopt;

    // channel radii
    ChannelRadii elasticRadii( 4.822220, 3.667980 );
    ChannelRadii captureRadii( 0. );

    // channels
    Channel elastic( elasticID, elasticPair, elasticPair,
                     elasticQ, elasticBoundary, elasticRadii );
    Channel capture( captureID, elasticPair, capturePair,
                     captureQ, captureBoundary, captureRadii );

    // the reduced widths are defined at a reference energy of 1 eV
    double reference = 1.;

    THEN( "an UnresolvedChannel can be constructed for a neutron channel" ) {

      UnresolvedChannel chunk( elastic, reference );

      CHECK( elastic == chunk.channel() );
      CHECK( elasticID == chunk.identifier() );
      CHECK( elasticRID == chunk.reaction() );
      CHECK( elasticPair == chunk.outgoingParticlePair() );
      CHECK( elasticRadii == chunk.channelRadii() );
      CHECK_THAT( reference, WithinRel( chunk.referenceEnergy() ) );

      // the elastic channel is a neutron channel, so a reduced neutron width
      // conversion is applied. it is an l = 0 channel ( P_l / P_0 = 1 ), so the
      // conversion factor reduces to sqrt( E / E_ref )
      CHECK_THAT( 3.1622776601683794e-3, WithinRel( chunk.widthConversionFactor( 1e-5 ) ) );
      CHECK_THAT( 1.,                    WithinRel( chunk.widthConversionFactor( 1.   ) ) );
      CHECK_THAT( 10.,                   WithinRel( chunk.widthConversionFactor( 100. ) ) );
    } // THEN

    THEN( "an UnresolvedChannel can be constructed for a capture channel" ) {

      UnresolvedChannel chunk( capture, reference );

      CHECK( capture == chunk.channel() );
      CHECK( captureID == chunk.identifier() );
      CHECK( captureRID == chunk.reaction() );
      CHECK( capturePair == chunk.outgoingParticlePair() );
      CHECK( captureRadii == chunk.channelRadii() );
      CHECK_THAT( reference, WithinRel( chunk.referenceEnergy() ) );

      // the capture channel is not a neutron channel, so a constant width
      // conversion is applied: the conversion factor is 1 at every energy
      CHECK_THAT( 1., WithinRel( chunk.widthConversionFactor( 1e-5 ) ) );
      CHECK_THAT( 1., WithinRel( chunk.widthConversionFactor( 1.   ) ) );
      CHECK_THAT( 1., WithinRel( chunk.widthConversionFactor( 100. ) ) );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of UnresolvedChannel are given" ) {

      // identifiers
      id::ChannelID elasticID( "n,Cl35->n,Cl35{0,1,1+}" );
      id::ChannelID captureID( "n,Cl35->g,Cl36[all]{0,0,1+}" );

      // particles
      Particle g( id::ParticleID::photon(), 0, 1, +1 );
      Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
      Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
      Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );

      // particle pairs
      ParticlePair elasticPair( n, cl35 );
      ParticlePair capturePair( g, cl36 );

      // Q values
      double elasticQ = 0.0;
      double captureQ = 0.0;

      // boundary conditions
      std::optional< double > elasticBoundary = std::nullopt;
      std::optional< double > captureBoundary = std::nullopt;

      // channel radii
      ChannelRadii elasticRadii( 4.822220, 3.667980 );
      ChannelRadii captureRadii( 0. );

      // channels
      Channel elastic( elasticID, elasticPair, elasticPair,
                       elasticQ, elasticBoundary, elasticRadii );
      Channel capture( captureID, elasticPair, capturePair,
                       captureQ, captureBoundary, captureRadii );

      UnresolvedChannel left( elastic, 1. );
      UnresolvedChannel equal( elastic, 1. );
      UnresolvedChannel differentChannel( capture, 1. );
      UnresolvedChannel differentReference( elastic, 2. );

      THEN( "they can be compared" ) {

        CHECK( true  == ( left == left ) );
        CHECK( true  == ( left == equal ) );
        CHECK( false == ( left == differentChannel ) );
        CHECK( false == ( left == differentReference ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true  == ( left != differentChannel ) );
        CHECK( true  == ( left != differentReference ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
