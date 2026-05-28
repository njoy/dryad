// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/UnresolvedSpinGroup.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const UnresolvedSpinGroup& );

SCENARIO( "UnresolvedSpinGroup" ) {

  GIVEN( "valid data for an UnresolvedSpinGroup" ) {

    // identifiers
    id::ChannelID elasticID( "n,Cl35->n,Cl35{0,1,1+}" );
    id::ChannelID inelasticID( "n,Cl35->n,Cl35_e1{0,1,1+}" );
    id::ChannelID captureID( "n,Cl35->g,Cl36[all]{0,0,1+}" );
    id::ChannelID protonID( "n,Cl35->p,S35{0,1,1+}" );

    // particles
    Particle g( id::ParticleID::photon(), 0, 1, +1 );
    Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
    Particle p( id::ParticleID::proton(), 1.00727646662, 0.5, +1 );
    Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
    Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );
    Particle cl35_e1( id::ParticleID( "Cl35_e1" ), 34.9688491981, 1.5, +1 );
    Particle s35( id::ParticleID( "S35" ), 34.9690307578, 1.5, +1 );

    // particle pairs
    ParticlePair elasticPair( n, cl35 );
    ParticlePair inelasticPair( n, cl35_e1 );
    ParticlePair capturePair( g, cl36 );
    ParticlePair protonPair( p, s35 );

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

    // channels
    Channel capture( captureID, elasticPair, capturePair,
                     captureQ, captureBoundary, captureRadii );
    Channel elastic( elasticID, elasticPair, elasticPair,
                     elasticQ, elasticBoundary, elasticRadii );
    Channel inelastic( inelasticID, elasticPair, inelasticPair,
                       inelasticQ, inelasticBoundary, inelasticRadii );
    Channel proton( protonID, elasticPair, protonPair,
                    protonQ, protonBoundary, protonRadii );

    // unresolved resonance table
    UnresolvedResonanceTable table(
        { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
          id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
          id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
          id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) },
        { 1., 2., 3., 4. },
        { 10., 11., 12., 13. },
        { { 0.11, 0.12, 0.13, 0.14 },
          { 0.21, 0.22, 0.23, 0.24 },
          { 0.31, 0.32, 0.33, 0.34 },
          { 0.41, 0.42, 0.43, 0.44 } } );

    THEN( "an UnresolvedSpinGroup can be constructed" ) {

      UnresolvedSpinGroup chunk( { capture, elastic, inelastic, proton }, table );

      verifyChunk( chunk );
    } // THEN
    THEN( "an UnresolvedSpinGroup can be constructed from unordered channels" ) {
      UnresolvedSpinGroup chunk( { proton, capture, inelastic, elastic }, table );
      verifyChunk( chunk );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of UnresolvedSpinGroup are given" ) {

      // identifiers
      id::ChannelID elasticID( "n,Cl35->n,Cl35{0,1,1+}" );
      id::ChannelID inelasticID( "n,Cl35->n,Cl35_e1{0,1,1+}" );
      id::ChannelID captureID( "n,Cl35->g,Cl36[all]{0,0,1+}" );
      id::ChannelID protonID( "n,Cl35->p,S35{0,1,1+}" );

      // particles
      Particle g( id::ParticleID::photon(), 0, 1, +1 );
      Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
      Particle p( id::ParticleID::proton(), 1.00727646662, 0.5, +1 );
      Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
      Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );
      Particle cl35_e1( id::ParticleID( "Cl35_e1" ), 34.9688491981, 1.5, +1 );
      Particle s35( id::ParticleID( "S35" ), 34.9690307578, 1.5, +1 );

      // particle pairs
      ParticlePair elasticPair( n, cl35 );
      ParticlePair inelasticPair( n, cl35_e1 );
      ParticlePair capturePair( g, cl36 );
      ParticlePair protonPair( p, s35 );

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

      // channels
      Channel capture( captureID, elasticPair, capturePair,
                       captureQ, captureBoundary, captureRadii );
      Channel elastic( elasticID, elasticPair, elasticPair,
                       elasticQ, elasticBoundary, elasticRadii );
      Channel inelastic( inelasticID, elasticPair, inelasticPair,
                         inelasticQ, inelasticBoundary, inelasticRadii );
      Channel proton( protonID, elasticPair, protonPair,
                      protonQ, protonBoundary, protonRadii );

      // unresolved resonance tables
      UnresolvedResonanceTable table1(
          { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
            id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
            id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
            id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) },
          { 1., 2., 3., 4. },
          { 10., 11., 12., 13. },
          { { 0.11, 0.12, 0.13, 0.14 },
            { 0.21, 0.22, 0.23, 0.24 },
            { 0.31, 0.32, 0.33, 0.34 },
            { 0.41, 0.42, 0.43, 0.44 } } );
      UnresolvedResonanceTable table2(
          { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
            id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
            id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ) },
          { 1., 2., 3., 4. },
          { 10., 11., 12., 13. },
          { { 0.11, 0.12, 0.13, 0.14 },
            { 0.21, 0.22, 0.23, 0.24 },
            { 0.31, 0.32, 0.33, 0.34 } } );

      UnresolvedSpinGroup left( { capture, elastic, inelastic, proton }, table1 );
      UnresolvedSpinGroup equal( { capture, elastic, inelastic, proton }, table1 );
      UnresolvedSpinGroup different( { capture, elastic, inelastic }, table2 );

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

  // TODO: add a scenario covering average infinitely dilute cross sections
  //       once UnresolvedSpinGroup::crossSections is implemented.
  // TODO: add a scenario covering ResonanceTable sampling once
  //       UnresolvedSpinGroup::sampleResonanceTable is implemented.
} // SCENARIO

void verifyChunk( const UnresolvedSpinGroup& chunk ) {

  // identifiers
  id::ChannelID elasticID( "n,Cl35->n,Cl35{0,1,1+}" );
  id::ChannelID inelasticID( "n,Cl35->n,Cl35_e1{0,1,1+}" );
  id::ChannelID captureID( "n,Cl35->g,Cl36[all]{0,0,1+}" );
  id::ChannelID protonID( "n,Cl35->p,S35{0,1,1+}" );

  // particles
  Particle g( id::ParticleID::photon(), 0, 1, +1 );
  Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
  Particle p( id::ParticleID::proton(), 1.00727646662, 0.5, +1 );
  Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
  Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );
  Particle cl35_e1( id::ParticleID( "Cl35_e1" ), 34.9688491981, 1.5, +1 );
  Particle s35( id::ParticleID( "S35" ), 34.9690307578, 1.5, +1 );

  // particle pairs
  ParticlePair elasticPair( n, cl35 );
  ParticlePair inelasticPair( n, cl35_e1 );
  ParticlePair capturePair( g, cl36 );
  ParticlePair protonPair( p, s35 );

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

  // channels
  Channel capture( captureID, elasticPair, capturePair,
                   captureQ, captureBoundary, captureRadii );
  Channel elastic( elasticID, elasticPair, elasticPair,
                   elasticQ, elasticBoundary, elasticRadii );
  Channel inelastic( inelasticID, elasticPair, inelasticPair,
                     inelasticQ, inelasticBoundary, inelasticRadii );
  Channel proton( protonID, elasticPair, protonPair,
                  protonQ, protonBoundary, protonRadii );

  // unresolved resonance table
  UnresolvedResonanceTable table(
      { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
        id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
        id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
        id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) },
      { 1., 2., 3., 4. },
      { 10., 11., 12., 13. },
      { { 0.11, 0.12, 0.13, 0.14 },
        { 0.21, 0.22, 0.23, 0.24 },
        { 0.31, 0.32, 0.33, 0.34 },
        { 0.41, 0.42, 0.43, 0.44 } } );

  CHECK( 1 == chunk.totalAngularMomentum() );
  CHECK( +1 == chunk.parity() );

  CHECK( Kinematics::NonRelativistic == chunk.kinematicsType() );
  CHECK( false == chunk.hasChannelsWithBackground() );

  CHECK( 4 == chunk.reactions().size() );
  CHECK( id::ReactionID( "n,Cl35->g,Cl36[all]" ) == chunk.reactions()[0] );
  CHECK( id::ReactionID( "n,Cl35->n,Cl35" ) == chunk.reactions()[1] );
  CHECK( id::ReactionID( "n,Cl35->n,Cl35_e1" ) == chunk.reactions()[2] );
  CHECK( id::ReactionID( "n,Cl35->p,S35" ) == chunk.reactions()[3] );

  CHECK( capture == chunk.channels()[0] );
  CHECK( elastic == chunk.channels()[1] );
  CHECK( inelastic == chunk.channels()[2] );
  CHECK( proton == chunk.channels()[3] );

  CHECK( table == chunk.resonanceTable() );
}