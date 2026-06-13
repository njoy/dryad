// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/resonances/lrf3/createSpinGroups.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::format;
using namespace njoy::dryad;
using namespace njoy::constants;

void verifyChunkAl27( const std::vector< resonances::SpinGroup >& );

SCENARIO( "createChannelData" ) {

  GIVEN( "ENDF MF2 MT151 sections" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-013_Al_027.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::ReichMoore >(
                        section.isotopes().front().resonanceRanges().front().parameters() );

    WHEN( "a single parsed Reich-Moore l-value from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile = id::ParticleID::neutron();
        id::ParticleID target = id::ParticleID( "Al27" );
        int naps = 1;
        std::optional< resonances::TabulatedRadius > nro = std::nullopt;
        auto chunk = endf::read::resonances::lrf3::createSpinGroups( projectile, target,
                                                                     naps, nro, parameters );

        verifyChunkAl27( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkAl27( const std::vector< resonances::SpinGroup >& chunk ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto al27 = id::ParticleID( "Al27" );
  auto al28 = id::ParticleID( "Al28[all]" );

  resonances::ParticlePair photon_pair( Particle( photon, 0, 0, +1 ),
                                        Particle( al28, 0 * neutron_mass, 0, +1 ) );
  resonances::ParticlePair neutron_pair( Particle( neutron, neutron_mass, 0.5, +1 ),
                                         Particle( al27, 26.75 * neutron_mass, 2.5, +1 ) );

  resonances::ChannelRadii zero_radii( 0., 0. );
  resonances::ChannelRadii radii1( 4.3226 );
  resonances::ChannelRadii radii2( 6.064 );
  resonances::ChannelRadii radii3( 4.396 );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  // spin groups
  CHECK( 10 == chunk.size() );

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
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,0+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,2,0+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 2 == table.numberEnergies() );

  auto energies = table.energies();
  CHECK_THAT( 3.603444e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 5.212374e+5, WithinRel( energies[1] ) );

  auto resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 8.371 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 3.348 / 2. ), WithinRel( resonances[0][1] ) );
  CHECK_THAT( std::sqrt( 266.8 / 2. / channel1.penetrability( 3.603444e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 35913 / 2. / channel1.penetrability( 5.212374e+5 ) ), WithinRel( resonances[1][1] ) );

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
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,1-}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{1,2,1-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 10 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 5.904677e+3, WithinRel( energies[0] ) );
  CHECK_THAT( 1.300000e+6, WithinRel( energies[9] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( .60876 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 2. / 2. ), WithinRel( resonances[0][9] ) );
  CHECK_THAT( std::sqrt( 16.695 / 2. / channel1.penetrability( 5.904677e+3 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt(  81305 / 2. / channel1.penetrability( 1.300000e+6 ) ), WithinRel( resonances[1][9] ) );

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
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,1+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,2,1+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel2 = channels[2];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,3,1+}" ) == channel2.identifier() );
  CHECK( true == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel2.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 5 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 3.150492e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 6.989209e+5, WithinRel( energies[4] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 2.4354 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 1.09 / 2. ), WithinRel( resonances[0][4] ) );
  CHECK_THAT( std::sqrt( 8154.2 / 2. / channel1.penetrability( 3.150492e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt(  53.55 / 2. / channel1.penetrability( 6.989209e+5 ) ), WithinRel( resonances[1][4] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( 3.150492e+5 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( 6.989209e+5 ) ), WithinRel( resonances[2][4] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[3];
  CHECK( 2 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,2-}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{1,2,2-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Al27->n,Al27{1,3,2-}" ) == channel2.identifier() );
  CHECK( true == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel2.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 12 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 9.124852e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 1.100000e+6, WithinRel( energies[11] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( .367 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt(   2. / 2. ), WithinRel( resonances[0][11] ) );
  CHECK_THAT( std::sqrt( 201.8 / 2. / channel1.penetrability( 9.124852e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt(  3400 / 2. / channel1.penetrability( 1.100000e+6 ) ), WithinRel( resonances[1][11] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( 9.124852e+4 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( 1.100000e+6 ) ), WithinRel( resonances[2][11] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[4];
  CHECK( 2 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 4 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,2+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{0,2,2+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK_THAT( 4.3226, WithinRel( std::get< double >( channel1.channelRadii().penetrabilityRadius() ) ) );
  CHECK( std::nullopt == channel1.channelRadii().shiftFactorRadius() );
  CHECK( std::nullopt == channel1.channelRadii().phaseShiftRadius() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,2,2+}" ) == channel2.identifier() );
  CHECK( true == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel2.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 3: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel3 = channels[3];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,3,2+}" ) == channel3.identifier() );
  CHECK( true == channel3.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel3.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel3.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel3.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel3.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel3.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel3.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel3.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 4 == table.numberChannels() );
  CHECK( 14 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( -4.585600e+6, WithinRel( energies[0] ) );
  CHECK_THAT(  1.630000e+6, WithinRel( energies[13] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( .99675 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt(   2. / 2. ), WithinRel( resonances[0][13] ) );
  CHECK_THAT( std::sqrt( 3291200 / 2. / channel1.penetrability( -4.585600e+6 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt(   37262 / 2. / channel1.penetrability(  1.630000e+6 ) ), WithinRel( resonances[1][13] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( -4.585600e+6 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability(  1.630000e+6 ) ), WithinRel( resonances[2][13] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel3.penetrability( -4.585600e+6 ) ), WithinRel( resonances[3][0] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel3.penetrability(  1.630000e+6 ) ), WithinRel( resonances[3][13] ) );

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
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,3-}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{1,2,3-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Al27->n,Al27{1,3,3-}" ) == channel2.identifier() );
  CHECK( true == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel2.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 8 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 1.200072e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 9.483662e+5, WithinRel( energies[7] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 2.1605 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt(   1.13 / 2. ), WithinRel( resonances[0][7] ) );
  CHECK_THAT( std::sqrt( 2815.2 / 2. / channel1.penetrability( 1.200072e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 149270 / 2. / channel1.penetrability( 9.483662e+5 ) ), WithinRel( resonances[1][7] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( 1.200072e+5 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( 9.483662e+5 ) ), WithinRel( resonances[2][7] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 6
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[6];
  CHECK( 3 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 4 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,3+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{0,3,3+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK_THAT( 4.3226, WithinRel( std::get< double >( channel1.channelRadii().penetrabilityRadius() ) ) );
  CHECK( std::nullopt == channel1.channelRadii().shiftFactorRadius() );
  CHECK( std::nullopt == channel1.channelRadii().phaseShiftRadius() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,2,3+}" ) == channel2.identifier() );
  CHECK( true == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel2.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, channel 3: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel3 = channels[3];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,3,3+}" ) == channel3.identifier() );
  CHECK( true == channel3.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel3.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel3.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel3.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel3.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel3.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel3.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel3.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 4 == table.numberChannels() );
  CHECK( 19 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( -3.129100e+5, WithinRel( energies[0] ) );
  CHECK_THAT(  1.460000e+6, WithinRel( energies[18] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( .99595 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt(     2. / 2. ), WithinRel( resonances[0][18] ) );
  CHECK_THAT( std::sqrt( 14705 / 2. / channel1.penetrability( -3.129100e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 38615 / 2. / channel1.penetrability(  1.460000e+6 ) ), WithinRel( resonances[1][18] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability( -3.129100e+5 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel2.penetrability(  1.460000e+6 ) ), WithinRel( resonances[2][18] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel3.penetrability( -3.129100e+5 ) ), WithinRel( resonances[3][0] ) );
  CHECK_THAT( std::sqrt( 0. / 2. / channel3.penetrability(  1.460000e+6 ) ), WithinRel( resonances[3][18] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 7
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[7];
  CHECK( 4 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 7, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,4-}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 7, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{1,3,4-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii2 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 7, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 3 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 3.668482e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 8.581069e+5, WithinRel( energies[2] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 1.518 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 1.13  / 2. ), WithinRel( resonances[0][2] ) );
  CHECK_THAT( std::sqrt( 4619 / 2. / channel1.penetrability( 3.668482e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 4380 / 2. / channel1.penetrability( 8.581069e+5 ) ), WithinRel( resonances[1][2] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 8
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[8];
  CHECK( 4 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 8, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,4+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 8, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,2,4+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 8, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,3,4+}" ) == channel2.identifier() );
  CHECK( true == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel2.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 8, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 4 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 5.927221e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 8.635064e+5, WithinRel( energies[3] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( .35  / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 1.09 / 2. ), WithinRel( resonances[0][3] ) );
  CHECK_THAT( std::sqrt( 0 / 2. / channel1.penetrability( 5.927221e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 0 / 2. / channel1.penetrability( 8.635064e+5 ) ), WithinRel( resonances[1][3] ) );
  CHECK_THAT( std::sqrt(   4.4 / 2. / channel2.penetrability( 5.927221e+5 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 83.02 / 2. / channel2.penetrability( 8.635064e+5 ) ), WithinRel( resonances[2][3] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 9
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = chunk[9];
  CHECK( 5 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 9, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Al27->g,Al28[all]{0,0,5+}" ) == channel0.identifier() );
  CHECK( false == channel0.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel0.incidentParticlePair() );

  // outgoing particle pair
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  // radii
  CHECK( zero_radii == channel0.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel0.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 9, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Al27->n,Al27{2,3,5+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii3 == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( resonances::Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 9, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 2 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 7.063424e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 7.861062e+5, WithinRel( energies[1] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 1.09 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 1.09 / 2. ), WithinRel( resonances[0][1] ) );
  CHECK_THAT( std::sqrt( 1295.8 / 2. / channel1.penetrability( 7.063424e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt(  11137 / 2. / channel1.penetrability( 7.861062e+5 ) ), WithinRel( resonances[1][1] ) );
}