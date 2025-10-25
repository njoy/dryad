// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/CompoundSystem.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const CompoundSystem& );

SCENARIO( "CompoundSystem" ) {

  GIVEN( "valid data for a SpinGroup" ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto proton = id::ParticleID::proton();
  auto cl35 = id::ParticleID( "Cl35" );
  auto cl35_e1 = id::ParticleID( "Cl35_e1" );
  auto cl36 = id::ParticleID( "Cl36[all]" );
  auto s35 = id::ParticleID( "S35" );

  ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                            Particle( cl36, 35.65932 * constants::neutron_mass, 0, +1 ) );
  ParticlePair neutron_pair( Particle( neutron, constants::neutron_mass, 0.5, +1 ),
                             Particle( cl35, 34.66845 * constants::neutron_mass, 1.5, +1 ) );
  ParticlePair proton_pair( Particle( proton, .9986235 * constants::neutron_mass, 0.5, +1 ),
                            Particle( s35, 34.66863 * constants::neutron_mass, 1.5, +1 ) );

  ChannelRadii zero_radii( 0., 0. );
  ChannelRadii radii1( 4.822220, 4.888750 );
  ChannelRadii radii2( 4.822220, 3.667980 );

  SpinGroup spingroup0( { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ),
                            neutron_pair, photon_pair, 0., std::nullopt,
                            zero_radii },
                          { id::ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ),
                            neutron_pair, neutron_pair, 0., std::nullopt,
                            radii1 } },
                        { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ),
                            id::ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ) },
                            { 1. }, { { 2. }, { 3. } } } );
  SpinGroup spingroup1( { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ),
                            neutron_pair, photon_pair, 0., std::nullopt,
                            zero_radii },
                          { id::ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ),
                            neutron_pair, neutron_pair, 0., std::nullopt,
                            radii1 },
                          { id::ChannelID( "n,Cl35->p,S35{1,1,1-}" ),
                            neutron_pair, proton_pair, 615220, std::nullopt,
                            radii1 },
                          { id::ChannelID( "n,Cl35->n,Cl35{1,2,1-}" ),
                            neutron_pair, neutron_pair, 0., std::nullopt,
                            radii1 },
                          { id::ChannelID( "n,Cl35->p,S35{1,2,1-}" ),
                            neutron_pair, proton_pair, 615220, std::nullopt,
                            radii1 } },
                        { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ),
                            id::ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ),
                            id::ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ),
                            id::ChannelID( "n,Cl35->n,Cl35{1,2,1-}" ),
                            id::ChannelID( "n,Cl35->p,S35{1,2,1-}" ) },
                            { 11. }, { { 12. }, { 13. }, { 14. }, { 15. }, { 16. } } } );

    THEN( "a CompoundSystem can be constructed - with ordered spin groups" ) {

      CompoundSystem chunk( { spingroup0, spingroup1 } );

      verifyChunk( chunk );
    } // THEN

    THEN( "a CompoundSystem can be constructed - with unordered spin groups" ) {

      CompoundSystem chunk( { spingroup1, spingroup0 } );

      verifyChunk( chunk );
    } // THEN
  } // GIVEN

//  GIVEN( "comparison operators" ) {
//
//    WHEN( "two instances of Channel are given" ) {
//
//      // identifiers
//      id::ChannelID elasticID( "n,Cl35->n,Cl35{0,1,1+}" );
//      id::ChannelID inelasticID( "n,Cl35->n,Cl35_e1{0,1,1+}" );
//      id::ChannelID captureID( "n,Cl35->g,Cl36[all]{0,0,1+}" );
//      id::ChannelID protonID( "n,Cl35->p,S35{0,1,1+}" );
//
//      // particles
//      Particle g( id::ParticleID::photon(), 0, 1, +1 );
//      Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
//      Particle p( id::ParticleID::proton(), 1.00727646662, 0.5, +1 );
//      Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
//      Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );
//      Particle cl35_e1( id::ParticleID( "Cl35_e1" ), 34.9688491981, 1.5, +1 );
//      Particle s35( id::ParticleID( "S35" ), 34.9690307578, 1.5, +1 );
//
//      // particle pairs
//      ParticlePair elasticPair( n, cl35 );
//      ParticlePair inelasticPair( n, cl35_e1 );
//      ParticlePair capturePair( g, cl36 );
//      ParticlePair protonPair( p, s35 );
//
//      // Q values
//      double elasticQ = 0.0;
//      double inelasticQ = -1.219440e+6;
//      double captureQ = 0.0;
//      double protonQ = 6.150729e+5;
//
//      // boundary conditions
//      std::optional< double > elasticBoundary = std::nullopt;
//      std::optional< double > inelasticBoundary = std::nullopt;
//      std::optional< double > captureBoundary = std::nullopt;
//      std::optional< double > protonBoundary = std::nullopt;
//
//      // channel radii
//      ChannelRadii elasticRadii( 4.822220, 3.667980 );
//      ChannelRadii inelasticRadii( 4.822220, 3.667980 );
//      ChannelRadii captureRadii( 0. );
//      ChannelRadii protonRadii( 4.822220, 3.667980 );
//
//      // channels
//      Channel capture( captureID, elasticPair, capturePair,
//                       captureQ, captureBoundary, captureRadii );
//      Channel elastic( elasticID, elasticPair, elasticPair,
//                       elasticQ, elasticBoundary, elasticRadii );
//      Channel inelastic( inelasticID, elasticPair, inelasticPair,
//                         inelasticQ, inelasticBoundary, inelasticRadii );
//      Channel proton( protonID, elasticPair, protonPair,
//                      protonQ, protonBoundary, protonRadii );
//
//      // resonance tables
//      ResonanceTable table1( { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
//                               id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
//                               id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
//                               id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) },
//                             { 1., 2., 3., 4. },
//                             { { 11., 12., 13., 14. },
//                               { 21., 22., 23., 24. },
//                               { 31., 32., 33., 34. },
//                               { 41., 42., 43., 44. } } );
//      ResonanceTable table2( { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
//                               id::ChannelID( "n,Cl35->n,Cl35_e1{0,1,1+}" ),
//                               id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ) },
//                             { 1., 2., 3., 4. },
//                             { { 11., 12., 13., 14. },
//                               { 21., 22., 23., 24. },
//                               { 31., 32., 33., 34. } } );
//
//      SpinGroup left( { capture, elastic, inelastic, proton }, table1 );
//      SpinGroup equal( { capture, elastic, inelastic, proton }, table1 );
//      SpinGroup different( { capture, elastic, inelastic }, table2 );
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
//    } // WHEN
//  } // GIVEN
} // SCENARIO

void verifyChunk( const CompoundSystem& chunk ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto proton = id::ParticleID::proton();
  auto cl35 = id::ParticleID( "Cl35" );
  auto cl35_e1 = id::ParticleID( "Cl35_e1" );
  auto cl36 = id::ParticleID( "Cl36[all]" );
  auto s35 = id::ParticleID( "S35" );

  ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                            Particle( cl36, 35.65932 * constants::neutron_mass, 0, +1 ) );
  ParticlePair neutron_pair( Particle( neutron, constants::neutron_mass, 0.5, +1 ),
                             Particle( cl35, 34.66845 * constants::neutron_mass, 1.5, +1 ) );
  ParticlePair proton_pair( Particle( proton, .9986235 * constants::neutron_mass, 0.5, +1 ),
                            Particle( s35, 34.66863 * constants::neutron_mass, 1.5, +1 ) );

  ChannelRadii zero_radii( 0., 0. );
  ChannelRadii radii1( 4.822220, 4.888750 );
  ChannelRadii radii2( 4.822220, 3.667980 );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  auto groups = chunk.spinGroups();

  // spin groups
  CHECK( 2 == groups.size() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  auto spingroup = groups[0];

  // channels
  auto channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 0, resonance table
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  auto table = spingroup.resonanceTable();
//  CHECK( 2 == table.numberChannels() );
//  CHECK( 9 == table.numberEnergies() );
//
//  auto energies = table.energies();
//  CHECK_THAT( 2.239640e+4, WithinRel( energies[0] ) );
//  CHECK_THAT( 5.478545e+5, WithinRel( energies[8] ) );
//
//  auto resonances = table.reducedWidthAmplitudes();
//  CHECK_THAT( std::sqrt( 1.724800 / 2. ), WithinRel( resonances[0][0] ) );
//  CHECK_THAT( std::sqrt( 0.86 / 2. ), WithinRel( resonances[0][8] ) );
//  CHECK_THAT( std::sqrt( .9663670 / 2. / channel1.penetrability( 2.239640e+4 ) ), WithinRel( resonances[1][0] ) );
//  CHECK_THAT( std::sqrt( 7.640130e+2 / 2. / channel1.penetrability( 5.478545e+5 ) ),WithinRel( resonances[1][8] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[1];

  // channels
  channels = spingroup.channels();

  CHECK( 5 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 2: proton emission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel2 = channels[2];
  CHECK( id::ChannelID( "n,Cl35->p,S35{1,1,1-}" ) == channel2.identifier() );
  CHECK( false == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( proton_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 3: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel3 = channels[3];
  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,2,1-}" ) == channel3.identifier() );
  CHECK( true == channel3.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel3.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel3.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel3.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel3.boundaryCondition() );

  // Q value
  CHECK_THAT( 0, WithinRel( channel3.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 4: proton emission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel4 = channels[4];
  CHECK( id::ChannelID( "n,Cl35->p,S35{1,2,1-}" ) == channel4.identifier() );
  CHECK( false == channel4.isIncidentChannel() );

    // incident particle pair
  CHECK( neutron_pair == channel4.incidentParticlePair() );

  // outgoing particle pair
  CHECK( proton_pair == channel4.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel4.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel4.boundaryCondition() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel4.qValue() ) );

//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 1, resonance table
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  table = spingroup.resonanceTable();
//  CHECK( 5 == table.numberChannels() );
//  CHECK( 56 == table.numberEnergies() );
//
//  energies = table.energies();
//  CHECK_THAT( 4.250762e+3, WithinRel( energies[0] ) );
//  CHECK_THAT( 1.435502e+6, WithinRel( energies[55] ) );
//
//  resonances = table.reducedWidthAmplitudes();
//  CHECK_THAT( std::sqrt( 0.472 / 2. ), WithinRel( resonances[0][0] ) );
//  CHECK_THAT( std::sqrt( 0.860 / 2. ), WithinRel( resonances[0][55] ) );
//  CHECK_THAT( std::sqrt( .628 / 2. / channel1.penetrability( 4.250762e+3 ) ), WithinRel( resonances[1][0] ) );
//  CHECK_THAT( std::sqrt( 5.365630e+3 / 2. / channel1.penetrability( 1.435502e+6 ) ), WithinRel( resonances[1][55] ) );
//  CHECK_THAT( std::sqrt( .23 / 2. / channel2.penetrability( 4.250762e+3 ) ), WithinRel( resonances[2][0] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 1.435502e+6 ) ), WithinRel( resonances[2][55] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel3.penetrability( 4.250762e+3 ) ), WithinRel( resonances[3][0] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel3.penetrability( 1.435502e+6 ) ), WithinRel( resonances[3][55] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( 4.250762e+3 ) ), WithinRel( resonances[4][0] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( 1.435502e+6 ) ), WithinRel( resonances[4][55] ) );
//
//  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  // spin group 2
//  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  spingroup = chunk[2];
//
//  // channels
//  channels = spingroup.channels();
//
//  CHECK( 3 == channels.size() );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 2, channel 0: capture (eliminated)
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel0 = channels[0];
//  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ) == channel0.identifier() );
//  CHECK( false == channel0.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel0.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( photon_pair == channel0.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( zero_radii == channel0.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel0.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 2, channel 1: elastic
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel1 = channels[1];
//  CHECK( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) == channel1.identifier() );
//  CHECK( true == channel1.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel1.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii2 == channel1.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel1.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 2, channel 2: proton emission
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel2 = channels[2];
//  CHECK( id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) == channel2.identifier() );
//  CHECK( false == channel2.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel2.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( proton_pair == channel2.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii2 == channel2.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel2.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 2, resonance table
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  table = spingroup.resonanceTable();
//  CHECK( 3 == table.numberChannels() );
//  CHECK( 23 == table.numberEnergies() );
//
//  energies = table.energies();
//  CHECK_THAT( 5.493200e+4, WithinRel( energies[0] ) );
//  CHECK_THAT( 1.205687e+6, WithinRel( energies[22] ) );
//
//  resonances = table.reducedWidthAmplitudes();
//  CHECK_THAT( std::sqrt( 0.36726 / 2. ), WithinRel( resonances[0][0] ) );
//  CHECK_THAT( std::sqrt( 0.606 / 2. ), WithinRel( resonances[0][22] ) );
//  CHECK_THAT( std::sqrt( 46.44240 / 2. / channel1.penetrability( 5.493200e+4 ) ), WithinRel( resonances[1][0] ) );
//  CHECK_THAT( std::sqrt( 642.5840 / 2. / channel1.penetrability( 1.205687e+6 ) ), WithinRel( resonances[1][22] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 5.493200e+4 ) ), WithinRel( resonances[2][0] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 1.205687e+6 ) ), WithinRel( resonances[2][22] ) );
//
//  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  // spin group 3
//  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  spingroup = chunk[3];
//
//  // channels
//  channels = spingroup.channels();
//
//  CHECK( 5 == channels.size() );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 3, channel 0: capture (eliminated)
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel0 = channels[0];
//  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,2-}" ) == channel0.identifier() );
//  CHECK( false == channel0.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel0.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( photon_pair == channel0.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( zero_radii == channel0.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel0.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 3, channel 1: elastic
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel1 = channels[1];
//  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,1,2-}" ) == channel1.identifier() );
//  CHECK( true == channel1.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel1.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii1 == channel1.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel1.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 3, channel 2: proton emission
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel2 = channels[2];
//  CHECK( id::ChannelID( "n,Cl35->p,S35{1,1,2-}" ) == channel2.identifier() );
//  CHECK( false == channel2.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel2.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( proton_pair == channel2.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii1 == channel2.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel2.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 3, channel 3: elastic
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel3 = channels[3];
//  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,2,2-}" ) == channel3.identifier() );
//  CHECK( true == channel3.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel3.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( neutron_pair == channel3.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii1 == channel3.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel3.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 0.0, WithinRel( channel3.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 3, channel 4: proton emission
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel4 = channels[4];
//  CHECK( id::ChannelID( "n,Cl35->p,S35{1,2,2-}" ) == channel4.identifier() );
//  CHECK( false == channel4.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel4.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( proton_pair == channel4.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii1 == channel4.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel4.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 615220, WithinRel( channel4.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 3, resonance table
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  table = spingroup.resonanceTable();
//  CHECK( 5 == table.numberChannels() );
//  CHECK( 95 == table.numberEnergies() );
//
//  energies = table.energies();
//  CHECK_THAT( -3.369334e+5, WithinRel( energies[0] ) );
//  CHECK_THAT( 1.441365e+6, WithinRel( energies[94] ) );
//
//  resonances = table.reducedWidthAmplitudes();
//  CHECK_THAT( std::sqrt( 0.53401 / 2. ), WithinRel( resonances[0][0] ) );
//  CHECK_THAT( std::sqrt( 0.860 / 2. ), WithinRel( resonances[0][94] ) );
//  CHECK_THAT( std::sqrt( 3.820180e+4 / 2. / channel1.penetrability( -3.369334e+5 ) ), WithinRel( resonances[1][0] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel1.penetrability( 1.441365e+6 ) ), WithinRel( resonances[1][94] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( -3.369334e+5 ) ), WithinRel( resonances[2][0] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 1.441365e+6 ) ), WithinRel( resonances[2][94] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel3.penetrability( -3.369334e+5 ) ), WithinRel( resonances[3][0] ) );
//  CHECK_THAT( std::sqrt( 1.608740e+3 / 2. / channel3.penetrability( 1.441365e+6 ) ), WithinRel( resonances[3][94] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( -3.369334e+5 ) ), WithinRel( resonances[4][0] ) );
//  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( 1.441365e+6 ) ), WithinRel( resonances[4][94] ) );
//
//  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  // spin group 4
//  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  spingroup = chunk[4];
//
//  // channels
//  channels = spingroup.channels();
//
//  CHECK( 3 == channels.size() );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 4, channel 0: capture (eliminated)
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel0 = channels[0];
//  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ) == channel0.identifier() );
//  CHECK( false == channel0.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel0.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( photon_pair == channel0.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( zero_radii == channel0.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel0.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 4, channel 1: elastic
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel1 = channels[1];
//  CHECK( id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ) == channel1.identifier() );
//  CHECK( true == channel1.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel1.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii2 == channel1.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel1.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 4, channel 2: proton emission
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel2 = channels[2];
//  CHECK( id::ChannelID( "n,Cl35->p,S35{0,2,2+}" ) == channel2.identifier() );
//  CHECK( false == channel2.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel2.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( proton_pair == channel2.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii2 == channel2.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel2.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 4, resonance table
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  table = spingroup.resonanceTable();
//  CHECK( 3 == table.numberChannels() );
//  CHECK( 32 == table.numberEnergies() );
//
//  energies = table.energies();
//  CHECK_THAT( -1.806500e+2, WithinRel( energies[0] ) );
//  CHECK_THAT(  7.563145e+6, WithinRel( energies[31] ) );
//
//  resonances = table.reducedWidthAmplitudes();
//  CHECK_THAT( std::sqrt( 0.53015 / 2. ), WithinRel( resonances[0][0] ) );
//  CHECK_THAT( std::sqrt( 0.38398 / 2. ), WithinRel( resonances[0][31] ) );
//  CHECK_THAT( std::sqrt( 13.277 / 2. / channel1.penetrability( -1.806500e+2 ) ), WithinRel( resonances[1][0] ) );
//  CHECK_THAT( std::sqrt( 6.219050e+5 / 2. / channel1.penetrability( 7.563145e+6 ) ), WithinRel( resonances[1][31] ) );
//  CHECK_THAT( std::sqrt( 5.992300e-3 / 2. / channel2.penetrability( -1.806500e+2 ) ), WithinRel( resonances[2][0] ) );
//  CHECK_THAT( std::sqrt( 1000. / 2. / channel2.penetrability( 7.563145e+6 ) ), WithinRel( resonances[2][31] ) );
//
//  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  // spin group 5
//  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  spingroup = chunk[5];
//
//  // channels
//  channels = spingroup.channels();
//
//  CHECK( 3 == channels.size() );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 5, channel 0: capture (eliminated)
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel0 = channels[0];
//  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,3-}" ) == channel0.identifier() );
//  CHECK( false == channel0.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel0.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( photon_pair == channel0.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( zero_radii == channel0.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel0.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 5, channel 1: elastic
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel1 = channels[1];
//  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,2,3-}" ) == channel1.identifier() );
//  CHECK( true == channel1.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel1.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii1 == channel1.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel1.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 0, WithinRel( channel1.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 5, channel 2: proton emission
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  channel2 = channels[2];
//  CHECK( id::ChannelID( "n,Cl35->p,S35{1,2,3-}" ) == channel2.identifier() );
//  CHECK( false == channel2.isIncidentChannel() );
//
//  // incident particle pair
//  CHECK( neutron_pair == channel2.incidentParticlePair() );
//
//  // outgoing particle pair
//  CHECK( proton_pair == channel2.outgoingParticlePair().value() );
//
//  // radii
//  CHECK( radii1 == channel2.channelRadii() );
//
//  // boundary conditions
//  CHECK( std::nullopt == channel2.boundaryCondition() );
//
//  // Q value
//  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );
//
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//  // spin group 5, resonance table
//  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
//
//  table = spingroup.resonanceTable();
//  CHECK( 3 == table.numberChannels() );
//  CHECK( 57 == table.numberEnergies() );
//
//  energies = table.energies();
//  CHECK_THAT( 1.635612e+4, WithinRel( energies[0] ) );
//  CHECK_THAT( 1.485128e+6, WithinRel( energies[56] ) );
//
//  resonances = table.reducedWidthAmplitudes();
//  CHECK_THAT( std::sqrt( 0.3865 / 2. ), WithinRel( resonances[0][0] ) );
//  CHECK_THAT( std::sqrt( 0.86 / 2. ), WithinRel( resonances[0][31] ) );
//  CHECK_THAT( std::sqrt( 5.9818 / 2. / channel1.penetrability( 1.635612e+4 ) ), WithinRel( resonances[1][0] ) );
//  CHECK_THAT( std::sqrt( 1.054090e+4 / 2. / channel1.penetrability( 1.485128e+6 ) ), WithinRel( resonances[1][56] ) );
//  CHECK_THAT( std::sqrt( 0.164019 / 2. / channel2.penetrability( 1.635612e+4 ) ), WithinRel( resonances[2][0] ) );
//  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( 1.485128e+6 ) ), WithinRel( resonances[2][56] ) );
}
