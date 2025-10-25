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
  SpinGroup spingroup2( { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                            neutron_pair, photon_pair, 0., std::nullopt,
                            zero_radii },
                          { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                            neutron_pair, neutron_pair, 0., std::nullopt,
                            radii2 },
                          { id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ),
                            neutron_pair, proton_pair, 615220, std::nullopt,
                            radii2 } },
                        { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                            id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                            id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) },
                          { 21. }, { { 22. }, { 23. }, { 24. } } } );
  SpinGroup spingroup3( { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,2-}" ),
                            neutron_pair, photon_pair, 0., std::nullopt,
                            zero_radii },
                          { id::ChannelID( "n,Cl35->n,Cl35{1,1,2-}" ),
                            neutron_pair, neutron_pair, 0., std::nullopt,
                            radii1 },
                          { id::ChannelID( "n,Cl35->p,S35{1,1,2-}" ),
                            neutron_pair, proton_pair, 615220, std::nullopt,
                            radii1 },
                          { id::ChannelID( "n,Cl35->n,Cl35{1,2,2-}" ),
                            neutron_pair, neutron_pair, 0., std::nullopt,
                            radii1 },
                          { id::ChannelID( "n,Cl35->p,S35{1,2,2-}" ),
                            neutron_pair, proton_pair, 615220, std::nullopt,
                            radii1 } },
                        { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,2-}" ),
                            id::ChannelID( "n,Cl35->n,Cl35{1,1,2-}" ),
                            id::ChannelID( "n,Cl35->p,S35{1,1,2-}" ),
                            id::ChannelID( "n,Cl35->n,Cl35{1,2,2-}" ),
                            id::ChannelID( "n,Cl35->p,S35{1,2,2-}" ) },
                          { 31. }, { { 32. }, { 33. }, { 34. }, { 35. }, { 36. } } } );
  SpinGroup spingroup4( { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
                            neutron_pair, photon_pair, 0., std::nullopt,
                            zero_radii },
                          { id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ),
                            neutron_pair, neutron_pair, 0., std::nullopt,
                            radii2 },
                          { id::ChannelID( "n,Cl35->p,S35{0,2,2+}" ),
                            neutron_pair, proton_pair, 615220, std::nullopt,
                            radii2 } },
                        { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
                            id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ),
                            id::ChannelID( "n,Cl35->p,S35{0,2,2+}" ) },
                          { 41. }, { { 42. }, { 43. }, { 44. } } } );
  SpinGroup spingroup5( { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,3-}" ),
                            neutron_pair, photon_pair, 0., std::nullopt,
                            zero_radii },
                          { id::ChannelID( "n,Cl35->n,Cl35{1,2,3-}" ),
                            neutron_pair, neutron_pair, 0., std::nullopt,
                            radii1 },
                          { id::ChannelID( "n,Cl35->p,S35{1,2,3-}" ),
                            neutron_pair, proton_pair, 615220, std::nullopt,
                            radii1 } },
                        { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,3-}" ),
                            id::ChannelID( "n,Cl35->n,Cl35{1,2,3-}" ),
                            id::ChannelID( "n,Cl35->p,S35{1,2,3-}" ) },
                          { 51. }, { { 52. }, { 53. }, { 54. } } } );

    THEN( "a CompoundSystem can be constructed - with ordered spin groups" ) {

      CompoundSystem chunk( { spingroup0, spingroup1, spingroup2, spingroup3, spingroup4, spingroup5 } );

      verifyChunk( chunk );
    } // THEN

    THEN( "a CompoundSystem can be constructed - with unordered spin groups" ) {

      CompoundSystem chunk( { spingroup5, spingroup4, spingroup3, spingroup2, spingroup1, spingroup0 } );

      verifyChunk( chunk );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of CompoundSystem are given" ) {


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

      SpinGroup left( { spingroup0 } );
      SpinGroup equal( { spingroup0 } );
      SpinGroup different( { spingroup1 } );

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
  CHECK( 6 == groups.size() );

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

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 1 == table.numberEnergies() );

  auto energies = table.energies();
  CHECK_THAT( 1, WithinRel( energies[0] ) );

  auto resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( 2, WithinRel( resonances[0][0] ) );
  CHECK_THAT( 3, WithinRel( resonances[1][0] ) );

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

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 5 == table.numberChannels() );
  CHECK( 1 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 11, WithinRel( energies[0] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( 12, WithinRel( resonances[0][0] ) );
  CHECK_THAT( 13, WithinRel( resonances[1][0] ) );
  CHECK_THAT( 14, WithinRel( resonances[2][0] ) );
  CHECK_THAT( 15, WithinRel( resonances[3][0] ) );
  CHECK_THAT( 16, WithinRel( resonances[4][0] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[2];

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ) == channel0.identifier() );
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
  // spin group 2, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 2: proton emission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) == channel2.identifier() );
  CHECK( false == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( proton_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 1 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 21, WithinRel( energies[0] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( 22, WithinRel( resonances[0][0] ) );
  CHECK_THAT( 23, WithinRel( resonances[1][0] ) );
  CHECK_THAT( 24, WithinRel( resonances[2][0] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[3];

  // channels
  channels = spingroup.channels();

  CHECK( 5 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,2-}" ) == channel0.identifier() );
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
  // spin group 3, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,1,2-}" ) == channel1.identifier() );
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
  // spin group 3, channel 2: proton emission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Cl35->p,S35{1,1,2-}" ) == channel2.identifier() );
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
  // spin group 3, channel 3: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel3 = channels[3];
  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,2,2-}" ) == channel3.identifier() );
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
  CHECK_THAT( 0.0, WithinRel( channel3.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 4: proton emission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel4 = channels[4];
  CHECK( id::ChannelID( "n,Cl35->p,S35{1,2,2-}" ) == channel4.identifier() );
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

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 5 == table.numberChannels() );
  CHECK( 1 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 31, WithinRel( energies[0] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( 32, WithinRel( resonances[0][0] ) );
  CHECK_THAT( 33, WithinRel( resonances[1][0] ) );
  CHECK_THAT( 34, WithinRel( resonances[2][0] ) );
  CHECK_THAT( 35, WithinRel( resonances[3][0] ) );
  CHECK_THAT( 36, WithinRel( resonances[4][0] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[4];

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ) == channel0.identifier() );
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
  // spin group 4, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 2: proton emission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Cl35->p,S35{0,2,2+}" ) == channel2.identifier() );
  CHECK( false == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( proton_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 1 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 41, WithinRel( energies[0] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( 42, WithinRel( resonances[0][0] ) );
  CHECK_THAT( 43, WithinRel( resonances[1][0] ) );
  CHECK_THAT( 44, WithinRel( resonances[2][0] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 5
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[5];

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,3-}" ) == channel0.identifier() );
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
  // spin group 5, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,2,3-}" ) == channel1.identifier() );
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
  CHECK_THAT( 0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 2: proton emission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Cl35->p,S35{1,2,3-}" ) == channel2.identifier() );
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
  // spin group 5, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 1 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 51, WithinRel( energies[0] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( 52, WithinRel( resonances[0][0] ) );
  CHECK_THAT( 53, WithinRel( resonances[1][0] ) );
  CHECK_THAT( 54, WithinRel( resonances[2][0] ) );
}
