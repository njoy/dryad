// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/resonances/lrf7/createSpinGroups.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include <iostream>
// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunkCl35( const std::vector< SpinGroup >& );

SCENARIO( "createSpinGroups" ) {

  GIVEN( "ENDF MF2 MT151 RML data - Cl35" ) {

    // Cl35 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - Z for n,gamma is set to 0.0 (should be 17.0)
    //                      - spin groups are not unitque (1- and 2- occur
    //                        multiple times)

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );

    WHEN( "a set of parsed LRF7 data from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile = id::ParticleID::neutron();
        id::ParticleID target = id::ParticleID( "Cl35" );
        auto chunk = format::endf::resonances::lrf7::createSpinGroups( projectile, target, parameters );

        verifyChunkCl35( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkCl35( const std::vector< SpinGroup >& chunk ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto proton = id::ParticleID::proton();
  auto cl35 = id::ParticleID( "Cl35" );
  auto cl35_e1 = id::ParticleID( "Cl35_e1" );
  auto cl36 = id::ParticleID( "Cl36[all]" );
  auto s35 = id::ParticleID( "S35" );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  // spin groups
  CHECK( 6 == chunk.size() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  auto spingroup = chunk[0];

  // channels
  auto channels = spingroup.channels();

  CHECK( 2 == channels.size() );
  for ( const auto& channel : channels ) {

    std::cout << channel.identifier().symbol() << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0, channel 0: capture (eliminated)
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  auto channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  auto incident = channel0.incidentParticlePair();
  CHECK( neutron == incident.particle().identifier() );
  CHECK_THAT( constants::neutron_mass, WithinRel( incident.particle().mass() ) );
  CHECK( 0 == incident.particle().charge() );
  CHECK( 0.5 == incident.particle().spin() );
  CHECK( +1 == incident.particle().parity() );
  CHECK( cl35 == incident.residual().identifier() );
  CHECK_THAT( 34.66845 * constants::neutron_mass, WithinRel( incident.residual().mass() ) );
  CHECK( 17 == incident.residual().charge() );
  CHECK( 1.5 == incident.residual().spin() );
  CHECK( +1 == incident.residual().parity() );

  // outgoing particle pair
  auto outgoing = channel0.outgoingParticlePair().value();
  CHECK( photon == outgoing.particle().identifier() );
  CHECK_THAT( 0., WithinRel( outgoing.particle().mass() ) );
  CHECK( 0 == outgoing.particle().charge() );
  CHECK( 1 == outgoing.particle().spin() );
  CHECK( +1 == outgoing.particle().parity() );
  CHECK( cl36 == outgoing.residual().identifier() );
  CHECK_THAT( 35.65932 * constants::neutron_mass, WithinRel( outgoing.residual().mass() ) );
  CHECK( 17 == outgoing.residual().charge() );
  CHECK( 0 == outgoing.residual().spin() );
  CHECK( +1 == outgoing.residual().parity() );

  // radii
  auto radii = channel0.channelRadii();
  CHECK_THAT( 0., WithinRel( radii.calculatePenetrabilityRadius( 1e-5 ) ) );
  CHECK_THAT( 0., WithinRel( radii.calculateShiftFactorRadius( 1e-5 ) ) );
  CHECK_THAT( 0., WithinRel( radii.calculatePhaseShiftRadius( 1e-5 ) ) );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0, channel 1: elastic
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  auto channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  incident = channel1.incidentParticlePair();
  CHECK( neutron == incident.particle().identifier() );
  CHECK_THAT( constants::neutron_mass, WithinRel( incident.particle().mass() ) );
  CHECK( 0 == incident.particle().charge() );
  CHECK( 0.5 == incident.particle().spin() );
  CHECK( +1 == incident.particle().parity() );
  CHECK( cl35 == incident.residual().identifier() );
  CHECK_THAT( 34.66845 * constants::neutron_mass, WithinRel( incident.residual().mass() ) );
  CHECK( 17 == incident.residual().charge() );
  CHECK( 1.5 == incident.residual().spin() );
  CHECK( +1 == incident.residual().parity() );

  // outgoing particle pair
  outgoing = channel1.outgoingParticlePair().value();
  CHECK( neutron == outgoing.particle().identifier() );
  CHECK_THAT( constants::neutron_mass, WithinRel( outgoing.particle().mass() ) );
  CHECK( 0 == outgoing.particle().charge() );
  CHECK( 0.5 == outgoing.particle().spin() );
  CHECK( +1 == outgoing.particle().parity() );
  CHECK( cl35 == outgoing.residual().identifier() );
  CHECK_THAT( 34.66845 * constants::neutron_mass, WithinRel( outgoing.residual().mass() ) );
  CHECK( 17 == outgoing.residual().charge() );
  CHECK( 1.5 == outgoing.residual().spin() );
  CHECK( +1 == outgoing.residual().parity() );

  // radii
  radii = channel1.channelRadii();
  CHECK_THAT( 4.822220, WithinRel( radii.calculatePenetrabilityRadius( 1e-5 ) ) );
  CHECK_THAT( 4.822220, WithinRel( radii.calculateShiftFactorRadius( 1e-5 ) ) );
  CHECK_THAT( 4.888750, WithinRel( radii.calculatePhaseShiftRadius( 1e-5 ) ) );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0, resonance table
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  auto table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 9 == table.numberResonances() );

  auto energies = table.energies();
  CHECK_THAT( 2.239640e+4, WithinRel( energies.front() ) );
  CHECK_THAT( 5.478545e+5, WithinRel( energies.back() ) );

  auto resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 1.724800 / 2. ), WithinRel( resonances[0].front() ) );
  CHECK_THAT( std::sqrt( 0.86 / 2. ), WithinRel( resonances[0].back() ) );
  CHECK_THAT( std::sqrt( .9663670 / 2. / channel1.penetrability( 2.239640e+4 ) ), WithinRel( resonances[1].front() ) );
  CHECK_THAT( std::sqrt( 7.640130e+2 / 2. / channel1.penetrability( 5.478545e+5 ) ),WithinRel( resonances[1].back() ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[1];

  // channels
  channels = spingroup.channels();

  CHECK( 5 == channels.size() );
  std::cout << " - - - - - - - - - - - - " << std::endl;
  for ( const auto& channel : channels ) {

    std::cout << channel.identifier().symbol() << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[2];

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );
  std::cout << " - - - - - - - - - - - - " << std::endl;
  for ( const auto& channel : channels ) {

    std::cout << channel.identifier().symbol() << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[3];

  // channels
  channels = spingroup.channels();

  CHECK( 5 == channels.size() );
  std::cout << " - - - - - - - - - - - - " << std::endl;
  for ( const auto& channel : channels ) {

    std::cout << channel.identifier().symbol() << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[4];

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );
  std::cout << " - - - - - - - - - - - - " << std::endl;
  for ( const auto& channel : channels ) {

    std::cout << channel.identifier().symbol() << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 5
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[5];

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );
  std::cout << " - - - - - - - - - - - - " << std::endl;
  for ( const auto& channel : channels ) {

    std::cout << channel.identifier().symbol() << std::endl;
  }

}
