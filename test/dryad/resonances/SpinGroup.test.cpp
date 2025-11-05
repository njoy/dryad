// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/SpinGroup.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const SpinGroup& );

SCENARIO( "SpinGroup" ) {

  GIVEN( "valid data for a SpinGroup" ) {

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

    // resonance tables
    ResonanceTable table( { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                            id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
                            id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                            id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) },
                          { 1., 2., 3., 4. },
                          { { 11., 12., 13., 14. },
                            { 21., 22., 23., 24. },
                            { 31., 32., 33., 34. },
                            { 41., 42., 43., 44. } } );
    ResonanceTable captureTable( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                                 { 1., 2., 3., 4. },
                                 { 11., 12., 13., 14. } );
    ResonanceTable elasticTable( id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
                                 { 1., 2., 3., 4. },
                                 { 21., 22., 23., 24. } );
    ResonanceTable inelasticTable( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                                   { 1., 2., 3., 4. },
                                   { 31., 32., 33., 34. } );
    ResonanceTable protonTable( id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ),
                                { 1., 2., 3., 4. },
                                { 41., 42., 43., 44. } );

    Formalism formalism = Formalism::ReichMoore;
    BoundaryCondition boundary = BoundaryCondition::ShiftFactor;

    THEN( "a SpinGroup can be constructed using a single table" ) {

      SpinGroup chunk( { capture, elastic, inelastic, proton }, table,
                       formalism, boundary );

      verifyChunk( chunk );
    } // THEN

    THEN( "a SpinGroup can be constructed using channel data objects" ) {

      SpinGroup chunk( { { capture, captureTable }, { elastic, elasticTable },
                         { inelastic, inelasticTable }, { proton, protonTable } },
                       formalism, boundary );

      verifyChunk( chunk );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of SpinGroup are given" ) {

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

      // resonance tables
      ResonanceTable table1( { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                               id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
                               id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                               id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) },
                             { 1., 2., 3., 4. },
                             { { 11., 12., 13., 14. },
                               { 21., 22., 23., 24. },
                               { 31., 32., 33., 34. },
                               { 41., 42., 43., 44. } } );
      ResonanceTable table2( { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                               id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
                               id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ) },
                             { 1., 2., 3., 4. },
                             { { 11., 12., 13., 14. },
                               { 21., 22., 23., 24. },
                               { 31., 32., 33., 34. } } );

      Formalism formalism = Formalism::ReichMoore;
      BoundaryCondition boundary = BoundaryCondition::ShiftFactor;

      SpinGroup left( { capture, elastic, inelastic, proton }, table1, formalism, boundary );
      SpinGroup equal( { capture, elastic, inelastic, proton }, table1, formalism, boundary );
      SpinGroup different( { capture, elastic, inelastic }, table2, formalism, boundary );

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

void verifyChunk( const SpinGroup& chunk ) {

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

  // resonance tables
  ResonanceTable table( { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                          id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
                          id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                          id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) },
                        { 1., 2., 3., 4. },
                        { { 11., 12., 13., 14. },
                          { 21., 22., 23., 24. },
                          { 31., 32., 33., 34. },
                          { 41., 42., 43., 44. } } );

  CHECK( 1 == chunk.totalAngularMomentum() );
  CHECK( +1 == chunk.parity() );

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
