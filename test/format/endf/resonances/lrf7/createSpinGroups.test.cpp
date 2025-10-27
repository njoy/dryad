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

void verifyChunkCu63( const std::vector< SpinGroup >& );
void verifyChunkCl35( const std::vector< SpinGroup >& );

SCENARIO( "createSpinGroups" ) {

  //! @todo add a test using Sr88 since it has background elements in it.

  GIVEN( "ENDF MF2 MT151 RML data - Cu63" ) {

    // Cu63 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - 2 channels, neutron only, constant boundary condition

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-029_Cu_063.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );

    WHEN( "a set of parsed LRF7 data from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile = id::ParticleID::neutron();
        id::ParticleID target = id::ParticleID( "Cu63" );
        auto chunk = format::endf::resonances::lrf7::createSpinGroups( projectile, target, parameters );

        verifyChunkCu63( chunk );
      } // THEN
    } // WHEN
  }

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

void verifyChunkCu63( const std::vector< SpinGroup >& chunk ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto proton = id::ParticleID::proton();
  auto cu63 = id::ParticleID( "Cu63" );
  auto cu64 = id::ParticleID( "Cu64[all]" );

  ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                            Particle( cu64, 63.389 * constants::neutron_mass, 0, +1 ) );
  ParticlePair neutron_pair( Particle( neutron, constants::neutron_mass, 0.5, +1 ),
                             Particle( cu63, 62.389 * constants::neutron_mass, 1.5, -1 ) );

  ChannelRadii zero_radii( 0., 0. );
  ChannelRadii radii1( 6.7, 6.7 );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  // spin groups
  CHECK( 6 == chunk.size() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  auto spingroup = chunk[0];
  CHECK( 0 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  auto channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,0+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel0.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cu63->n,Cu63{1,1,0+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel1.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 99 == table.numberEnergies() );

  auto energies = table.energies();
  CHECK_THAT( 2.216315e+3, WithinRel( energies[0] ) );
  CHECK_THAT( 2.981944e+5, WithinRel( energies[98] ) );

  auto resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 6.310807e-1 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 4.436942e+0 / 2. ), WithinRel( resonances[0][98] ) );
  CHECK_THAT( std::sqrt( 7.586839e-2 / 2. / channel1.penetrability( 2.216315e+3 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 6.869913e+4 / 2. / channel1.penetrability( 2.981944e+5 ) ),WithinRel( resonances[1][98] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[1];
  CHECK( 1 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1-}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel0.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cu63->n,Cu63{0,1,1-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel1.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 219 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( -3.709301e+4, WithinRel( energies[0] ) );
  CHECK_THAT(  3.282861e+5, WithinRel( energies[218] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 3.055291e-2 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 5.088833e-1 / 2. ), WithinRel( resonances[0][218] ) );
  CHECK_THAT( std::sqrt( 3.985125e+3 / 2. / channel1.penetrability( -3.709301e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 2.749173e+4 / 2. / channel1.penetrability(  3.282861e+5 ) ),WithinRel( resonances[1][218] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[2];
  CHECK( 1 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel0.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel1.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel2 = channels[2];
  CHECK( id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ) == channel2.identifier() );
  CHECK( true == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel2.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel2.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 291 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 3.811148e+3, WithinRel( energies[0] ) );
  CHECK_THAT( 2.993903e+5, WithinRel( energies[290] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 1.041912e-1 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 3.697500e-1 / 2. ), WithinRel( resonances[0][290] ) );
  CHECK_THAT( std::sqrt( 1.203147e-3 / 2. / channel1.penetrability( 3.811148e+3 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 4.133072e-1 / 2. / channel1.penetrability( 2.993903e+5 ) ),WithinRel( resonances[1][290] ) );
  CHECK_THAT( std::sqrt( 1.203163e-3 / 2. / channel2.penetrability( 3.811148e+3 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 4.132118e-1 / 2. / channel2.penetrability( 2.993903e+5 ) ),WithinRel( resonances[2][290] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[3];
  CHECK( 2 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,2-}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel0.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cu63->n,Cu63{0,2,2-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel1.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 194 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( -5.334625e+4, WithinRel( energies[0] ) );
  CHECK_THAT(  3.316735e+5, WithinRel( energies[193] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 3.382957e-2 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 5.249574e-1 / 2. ), WithinRel( resonances[0][193] ) );
  CHECK_THAT( std::sqrt( 6.331238e+3 / 2. / channel1.penetrability( -5.334625e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 4.844076e+4 / 2. / channel1.penetrability(  3.316735e+5 ) ),WithinRel( resonances[1][193] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[4];
  CHECK( 2 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,2+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel0.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cu63->n,Cu63{1,1,2+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel1.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Cu63->n,Cu63{1,2,2+}" ) == channel2.identifier() );
  CHECK( true == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel2.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel2.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 192 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 1.054117e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 2.989878e+5, WithinRel( energies[191] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 9.495851e-1 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 1.218805e+0 / 2. ), WithinRel( resonances[0][191] ) );
  CHECK_THAT( std::sqrt( 3.478491e-3 / 2. / channel1.penetrability( 1.054117e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 4.108667e+1 / 2. / channel1.penetrability( 2.989878e+5 ) ),WithinRel( resonances[1][191] ) );
  CHECK_THAT( std::sqrt( 3.478497e-3 / 2. / channel2.penetrability( 1.054117e+4 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 4.108700e+1 / 2. / channel2.penetrability( 2.989878e+5 ) ),WithinRel( resonances[2][191] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 5
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[5];
  CHECK( 3 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,3+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel0.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cu63->n,Cu63{1,2,3+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii1 == channel1.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel1.boundaryCondition() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 177 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 4.018230e+2, WithinRel( energies[0] ) );
  CHECK_THAT( 3.006336e+5, WithinRel( energies[176] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 3.094839e-2 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 6.065143e-1 / 2. ), WithinRel( resonances[0][176] ) );
  CHECK_THAT( std::sqrt( 1.641969e-4 / 2. / channel1.penetrability( 4.018230e+2 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 9.099094e+2 / 2. / channel1.penetrability( 3.006336e+5 ) ),WithinRel( resonances[1][176] ) );
}

void verifyChunkCl35( const std::vector< SpinGroup >& chunk ) {

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

  // spin groups
  CHECK( 6 == chunk.size() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  auto spingroup = chunk[0];
  CHECK( 0 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

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
  CHECK( 9 == table.numberEnergies() );

  auto energies = table.energies();
  CHECK_THAT( 2.239640e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 5.478545e+5, WithinRel( energies[8] ) );

  auto resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 1.724800 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.86 / 2. ), WithinRel( resonances[0][8] ) );
  CHECK_THAT( std::sqrt( .9663670 / 2. / channel1.penetrability( 2.239640e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 7.640130e+2 / 2. / channel1.penetrability( 5.478545e+5 ) ),WithinRel( resonances[1][8] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[1];
  CHECK( 1 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

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
  CHECK( 56 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 4.250762e+3, WithinRel( energies[0] ) );
  CHECK_THAT( 1.435502e+6, WithinRel( energies[55] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 0.472 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.860 / 2. ), WithinRel( resonances[0][55] ) );
  CHECK_THAT( std::sqrt( .628 / 2. / channel1.penetrability( 4.250762e+3 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 5.365630e+3 / 2. / channel1.penetrability( 1.435502e+6 ) ), WithinRel( resonances[1][55] ) );
  CHECK_THAT( std::sqrt( .23 / 2. / channel2.penetrability( 4.250762e+3 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 1.435502e+6 ) ), WithinRel( resonances[2][55] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel3.penetrability( 4.250762e+3 ) ), WithinRel( resonances[3][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel3.penetrability( 1.435502e+6 ) ), WithinRel( resonances[3][55] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( 4.250762e+3 ) ), WithinRel( resonances[4][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( 1.435502e+6 ) ), WithinRel( resonances[4][55] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[2];
  CHECK( 1 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

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
  CHECK( 23 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 5.493200e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 1.205687e+6, WithinRel( energies[22] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 0.36726 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.606 / 2. ), WithinRel( resonances[0][22] ) );
  CHECK_THAT( std::sqrt( 46.44240 / 2. / channel1.penetrability( 5.493200e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 642.5840 / 2. / channel1.penetrability( 1.205687e+6 ) ), WithinRel( resonances[1][22] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 5.493200e+4 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 1.205687e+6 ) ), WithinRel( resonances[2][22] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[3];
  CHECK( 2 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

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
  CHECK( 95 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( -3.369334e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 1.441365e+6, WithinRel( energies[94] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 0.53401 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.860 / 2. ), WithinRel( resonances[0][94] ) );
  CHECK_THAT( std::sqrt( 3.820180e+4 / 2. / channel1.penetrability( -3.369334e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel1.penetrability( 1.441365e+6 ) ), WithinRel( resonances[1][94] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( -3.369334e+5 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 1.441365e+6 ) ), WithinRel( resonances[2][94] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel3.penetrability( -3.369334e+5 ) ), WithinRel( resonances[3][0] ) );
  CHECK_THAT( std::sqrt( 1.608740e+3 / 2. / channel3.penetrability( 1.441365e+6 ) ), WithinRel( resonances[3][94] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( -3.369334e+5 ) ), WithinRel( resonances[4][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( 1.441365e+6 ) ), WithinRel( resonances[4][94] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[4];
  CHECK( 2 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

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
  CHECK( 32 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( -1.806500e+2, WithinRel( energies[0] ) );
  CHECK_THAT(  7.563145e+6, WithinRel( energies[31] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 0.53015 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.38398 / 2. ), WithinRel( resonances[0][31] ) );
  CHECK_THAT( std::sqrt( 13.277 / 2. / channel1.penetrability( -1.806500e+2 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 6.219050e+5 / 2. / channel1.penetrability( 7.563145e+6 ) ), WithinRel( resonances[1][31] ) );
  CHECK_THAT( std::sqrt( 5.992300e-3 / 2. / channel2.penetrability( -1.806500e+2 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 1000. / 2. / channel2.penetrability( 7.563145e+6 ) ), WithinRel( resonances[2][31] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 5
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[5];
  CHECK( 3 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

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
  CHECK( 57 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 1.635612e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 1.485128e+6, WithinRel( energies[56] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 0.3865 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.86 / 2. ), WithinRel( resonances[0][31] ) );
  CHECK_THAT( std::sqrt( 5.9818 / 2. / channel1.penetrability( 1.635612e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 1.054090e+4 / 2. / channel1.penetrability( 1.485128e+6 ) ), WithinRel( resonances[1][56] ) );
  CHECK_THAT( std::sqrt( 0.164019 / 2. / channel2.penetrability( 1.635612e+4 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( 1.485128e+6 ) ), WithinRel( resonances[2][56] ) );
}
