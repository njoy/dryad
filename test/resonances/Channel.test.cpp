// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/Channel.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "Channel" ) {

  GIVEN( "valid data for a Channel" ) {

    // identifiers
    id::ChannelID elasticID( "n,Cl35->n,Cl35{0,1,1+}" );
    id::ChannelID inelasticID( "n,Cl35->n,Cl35_e1{0,1,1+}" );
    id::ChannelID captureID( "n,Cl35->g,Cl36[all]{0,0,1+}" );
    id::ChannelID protonID( "n,Cl35->p,S35{0,1,1+}" );

    id::ReactionID elasticRID( "n,Cl35->n,Cl35" );
    id::ReactionID inelasticRID( "n,Cl35->n,Cl35_e1" );
    id::ReactionID captureRID( "n,Cl35->g,Cl36[all]" );
    id::ReactionID protonRID( "n,Cl35->p,S35" );

    ChannelQuantumNumbers elasticNumbers( 0, 1, 1, +1 );
    ChannelQuantumNumbers inelasticNumbers( 0, 1, 1, +1 );
    ChannelQuantumNumbers captureNumbers( 0, 0, 1, +1 );
    ChannelQuantumNumbers protonNumbers( 0, 1, 1, +1 );

    // particles
    Particle photon( id::ParticleID::photon(), 0, 1, +1 );
    Particle neutron( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
    Particle proton( id::ParticleID::proton(), 1.00727646662, 0.5, +1 );
    Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
    Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );
    Particle cl35_e1( id::ParticleID( "Cl35_e1" ), 34.9688491981, 1.5, +1 );
    Particle s35( id::ParticleID( "S35" ), 34.9690307578, 1.5, +1 );

    // particle pairs
    ParticlePair elasticPair( neutron, cl35 );
    ParticlePair inelasticPair( neutron, cl35_e1 );
    ParticlePair capturePair( photon, cl36 );
    ParticlePair protonPair( proton, s35 );

    // Q values
    double elasticQ = 0.0;
    double inelasticQ = -1.219440e+6;
    double captureQ = 0.0;
    double protonQ = 6.150729e+5;

    // boundary conditions
    std::optional< double > elasticBoundary = std::nullopt;
    std::optional< double > inelasticBoundary = std::nullopt;
    std::optional< double > captureBoundary = std::nullopt;
    std::optional< double > protonBoundary = std::nullopt;

    // channel radii
    ChannelRadii elasticRadii( 4.822220, 3.667980 );
    ChannelRadii inelasticRadii( 4.822220, 3.667980 );
    ChannelRadii captureRadii( 0. );
    ChannelRadii protonRadii( 4.822220, 3.667980 );

    THEN( "a Channel can be constructed without wave functions" ) {

      Channel elastic( elasticID, elasticPair, elasticPair,
                       elasticQ, elasticBoundary, elasticRadii );
      Channel inelastic( inelasticID, elasticPair, inelasticPair,
                         inelasticQ, inelasticBoundary, inelasticRadii );
      Channel proton( protonID, elasticPair, protonPair,
                      protonQ, protonBoundary, protonRadii );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of Channel are given" ) {

//      ChannelRadii left( .1 );
//      ChannelRadii equal( .1 );
//      ChannelRadii different( .2 );
//
//      THEN( "they can be compared" ) {
//
//        CHECK( true == ( left == left ) );
//        CHECK( true == ( left == equal ) );
//        CHECK( false == ( left == different ) );
//
//        CHECK( false == ( left != left ) );
//        CHECK( false == ( left != equal ) );
//        CHECK( true == ( left != different ) );
//      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
