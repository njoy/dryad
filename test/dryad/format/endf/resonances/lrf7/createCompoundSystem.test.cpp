// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf7/createCompoundSystem.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy;
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunkSr88( const CompoundSystem& );
void verifyChunkSi29( const CompoundSystem& );
void verifyChunkCu63( const CompoundSystem& );
void verifyChunkCl35( const CompoundSystem& );

SCENARIO( "createSpinGroups" ) {

  GIVEN( "ENDF MF2 MT151 RML data - Si29" ) {

    // Si29 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - empty spin group that contribute only potential scattering

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-014_Si_029.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );

    WHEN( "a set of parsed LRF7 data from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile = id::ParticleID::neutron();
        id::ParticleID target = id::ParticleID( "Si29" );
        auto chunk = format::endf::resonances::lrf7::createCompoundSystem( projectile, target, 1e-5, 1.3e+6, parameters );

        verifyChunkSi29( chunk );
      } // THEN
    } // WHEN
  }

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
        auto chunk = format::endf::resonances::lrf7::createCompoundSystem( projectile, target, 1e-5, 1e+5, parameters );

        verifyChunkCu63( chunk );
      } // THEN
    } // WHEN
  }

  GIVEN( "ENDF MF2 MT151 RML data - Cl35" ) {

    // Cl35 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - Z for n,gamma is set to 0.0 (should be 17.0)
    //                      - spin groups are not unique (1- and 2- occur
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
        auto chunk = format::endf::resonances::lrf7::createCompoundSystem( projectile, target, 1e-5, 1.2e+6, parameters );

        verifyChunkCl35( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF2 MT151 RML data - Sr88" ) {

    // Sr88 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - Sammy parametrisation for channel background

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-038_Sr_088.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );

    WHEN( "a set of parsed LRF7 data from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile = id::ParticleID::neutron();
        id::ParticleID target = id::ParticleID( "Sr88" );
        auto chunk = format::endf::resonances::lrf7::createCompoundSystem( projectile, target, 1e-5, 9.5e+5, parameters );

        verifyChunkSr88( chunk );
      } // THEN
    } // WHEN
  }
} // SCENARIO

void verifyChunkSi29( const CompoundSystem& chunk ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto si29 = id::ParticleID( "Si29" );
  auto si30 = id::ParticleID( "Si30[all]" );

  ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                            Particle( si30, 29.728 * constants::neutron_mass, 0, +1 ) );
  ParticlePair neutron_pair( Particle( neutron, constants::neutron_mass, 0.5, +1 ),
                             Particle( si29, 28.728 * constants::neutron_mass, 0.5, +1 ) );

  ChannelRadii zero_radii( 0., 0. );
  ChannelRadii radii( 4.221, 4.221 );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  // energies
  CHECK_THAT( 1e-5  , WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 1.3e+6, WithinRel( chunk.upperEnergyLimit() ) );

  // spin groups
  auto groups = chunk.spinGroups();
  CHECK( 7 == groups.size() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  auto spingroup = groups[0];
  CHECK( 0 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  auto channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel0 = channels[0];
  CHECK( id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel1 = channels[1];
  CHECK( id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 3 == table.numberEnergies() );

  auto energies = table.energies();
  CHECK_THAT( 3.740320e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 6.007182e+5, WithinRel( energies[2] ) );

  auto resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 4.623200 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 2.       / 2. ), WithinRel( resonances[0][2] ) );
  CHECK_THAT( std::sqrt( 1.072200e+5 / 2. / channel1.penetrability( 3.740320e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 3.885600e+4 / 2. / channel1.penetrability( 6.007182e+5 ) ), WithinRel( resonances[1][2] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[1];
  CHECK( 0 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Si29->g,Si30[all]{0,0,0+}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Si29->n,Si29{0,0,0+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 5 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( -2.041700e+6, WithinRel( energies[0] ) );
  CHECK_THAT(  2.248487e+6, WithinRel( energies[4] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 70.94582 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 3.       / 2. ), WithinRel( resonances[0][4] ) );
  CHECK_THAT( std::sqrt( 2.061100e+6 / 2. / channel1.penetrability( -2.041700e+6 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 1.693200e+2 / 2. / channel1.penetrability(  2.248487e+6 ) ), WithinRel( resonances[1][4] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[2];
  CHECK( 1 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Si29->g,Si30[all]{0,0,1-}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Si29->n,Si29{1,0,1-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel2 = channels[2];
  CHECK( id::ChannelID( "n,Si29->n,Si29{1,1,1-}" ) == channel2.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK(  3 == table.numberChannels() );
  CHECK( 11 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 1.529411e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 1.240000e+6, WithinRel( energies[10] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 1.265200 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.3      / 2. ), WithinRel( resonances[0][10] ) );
  CHECK_THAT( std::sqrt( 5.011500 / 2. / channel1.penetrability( 1.529411e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 9924.200 / 2. / channel1.penetrability( 1.240000e+6 ) ), WithinRel( resonances[1][10] ) );
  CHECK_THAT( 0., WithinRel( resonances[2][0] ) );
  CHECK_THAT( 0., WithinRel( resonances[2][10] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[3];
  CHECK( 1 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Si29->g,Si30[all]{0,0,1+}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Si29->n,Si29{0,1,1+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Si29->n,Si29{2,1,1+}" ) == channel2.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 4 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 3.842219e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 1.388859e+6, WithinRel( energies[3] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 5.173 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 3.    / 2. ), WithinRel( resonances[0][3] ) );
  CHECK_THAT( std::sqrt( 8910.4 / 2. / channel1.penetrability( 3.842219e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( 0., WithinRel( resonances[1][3] ) );
  CHECK_THAT( 0., WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt(4271.4 / 2. / channel2.penetrability( 1.388859e+6 ) ), WithinRel( resonances[2][3] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[4];
  CHECK( 2 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Si29->g,Si30[all]{0,0,2-}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Si29->n,Si29{1,1,2-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 7 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 3.883377e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 1.207629e+6, WithinRel( energies[6] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 2.2409 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.3    / 2. ), WithinRel( resonances[0][6] ) );
  CHECK_THAT( std::sqrt( 87.755 / 2. / channel1.penetrability( 3.883377e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 29571. / 2. / channel1.penetrability( 1.207629e+6 ) ), WithinRel( resonances[1][6] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 5
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[5];
  CHECK( 2 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Si29->g,Si30[all]{0,0,2+}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Si29->n,Si29{2,0,2+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Si29->n,Si29{2,1,2+}" ) == channel2.identifier() );
  CHECK( true == channel2.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel2.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel2.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel2.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.numberChannels() );
  CHECK( 0 == table.numberEnergies() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 6
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[6];
  CHECK( 3 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Si29->g,Si30[all]{0,0,3+}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Si29->n,Si29{2,1,3+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 1 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 6.203529e+5, WithinRel( energies[0] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 1.5944 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 843.2 / 2. / channel1.penetrability( 6.203529e+5 ) ), WithinRel( resonances[1][0] ) );
}

void verifyChunkCu63( const CompoundSystem& chunk ) {

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
  ChannelRadii radii( 6.7, 6.7 );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  // energies
  CHECK_THAT( 1e-5, WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 1e+5, WithinRel( chunk.upperEnergyLimit() ) );

  // spin groups
  auto groups = chunk.spinGroups();
  CHECK( 6 == groups.size() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  auto spingroup = groups[0];
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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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
  CHECK_THAT( std::sqrt( 6.869913e+4 / 2. / channel1.penetrability( 2.981944e+5 ) ), WithinRel( resonances[1][98] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[1];
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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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
  CHECK_THAT( std::sqrt( 2.749173e+4 / 2. / channel1.penetrability(  3.282861e+5 ) ), WithinRel( resonances[1][218] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[2];
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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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
  CHECK( radii == channel2.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

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
  CHECK_THAT( std::sqrt( 4.133072e-1 / 2. / channel1.penetrability( 2.993903e+5 ) ), WithinRel( resonances[1][290] ) );
  CHECK_THAT( std::sqrt( 1.203163e-3 / 2. / channel2.penetrability( 3.811148e+3 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 4.132118e-1 / 2. / channel2.penetrability( 2.993903e+5 ) ), WithinRel( resonances[2][290] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[3];
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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( 0 == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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
  CHECK_THAT( std::sqrt( 4.844076e+4 / 2. / channel1.penetrability(  3.316735e+5 ) ), WithinRel( resonances[1][193] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[4];
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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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
  CHECK( radii == channel2.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel2.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

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
  CHECK_THAT( std::sqrt( 4.108667e+1 / 2. / channel1.penetrability( 2.989878e+5 ) ), WithinRel( resonances[1][191] ) );
  CHECK_THAT( std::sqrt( 3.478497e-3 / 2. / channel2.penetrability( 1.054117e+4 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 4.108700e+1 / 2. / channel2.penetrability( 2.989878e+5 ) ), WithinRel( resonances[2][191] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 5
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[5];
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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Cu63->n,Cu63{1,2,3+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( -1 == channel1.boundaryCondition() );

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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
  CHECK_THAT( std::sqrt( 9.099094e+2 / 2. / channel1.penetrability( 3.006336e+5 ) ), WithinRel( resonances[1][176] ) );
}

void verifyChunkCl35( const CompoundSystem& chunk ) {

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

  // energies
  CHECK_THAT( 1e-5, WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 1.2e+6, WithinRel( chunk.upperEnergyLimit() ) );

  // spin groups
  auto groups = chunk.spinGroups();
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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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
  CHECK_THAT( std::sqrt( 7.640130e+2 / 2. / channel1.penetrability( 5.478545e+5 ) ), WithinRel( resonances[1][8] ) );

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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel3 = channels[2];
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

  // background
  CHECK( std::nullopt == channel3.background() );

  // Q value
  CHECK_THAT( 0, WithinRel( channel3.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel3.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 3: proton emission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel2 = channels[3];
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

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel4.background() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel4.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel4.kinematicsType() );

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
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel3.penetrability( 4.250762e+3 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel3.penetrability( 1.435502e+6 ) ), WithinRel( resonances[2][55] ) );
  CHECK_THAT( std::sqrt( .23 / 2. / channel2.penetrability( 4.250762e+3 ) ), WithinRel( resonances[3][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 1.435502e+6 ) ), WithinRel( resonances[3][55] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( 4.250762e+3 ) ), WithinRel( resonances[4][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( 1.435502e+6 ) ), WithinRel( resonances[4][55] ) );

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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 2: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel3 = channels[2];
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

  // background
  CHECK( std::nullopt == channel3.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel3.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel3.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 3: proton emission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[3];
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

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel4.background() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel4.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel4.kinematicsType() );

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
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel3.penetrability( -3.369334e+5 ) ), WithinRel( resonances[2][0] ) );
  CHECK_THAT( std::sqrt( 1.608740e+3 / 2. / channel3.penetrability( 1.441365e+6 ) ), WithinRel( resonances[2][94] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( -3.369334e+5 ) ), WithinRel( resonances[3][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel2.penetrability( 1.441365e+6 ) ), WithinRel( resonances[3][94] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( -3.369334e+5 ) ), WithinRel( resonances[4][0] ) );
  CHECK_THAT( std::sqrt( 0.0 / 2. / channel4.penetrability( 1.441365e+6 ) ), WithinRel( resonances[4][94] ) );

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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel0.background() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel0.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel1.background() );

  // Q value
  CHECK_THAT( 0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

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

  // background
  CHECK( std::nullopt == channel2.background() );

  // Q value
  CHECK_THAT( 615220, WithinRel( channel2.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel2.kinematicsType() );

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

void verifyChunkSr88( const CompoundSystem& chunk ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto sr88 = id::ParticleID( "Sr88" );
  auto sr89 = id::ParticleID( "Sr89[all]" );

  ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                            Particle( sr89, 88.15046 * constants::neutron_mass, 0, +1 ) );
  ParticlePair neutron_pair( Particle( neutron, constants::neutron_mass, 0.5, +1 ),
                             Particle( sr88, 87.15046 * constants::neutron_mass, 0, +1 ) );

  ChannelRadii zero_radii( 0., 0. );
  ChannelRadii equal_radii( 7.1, 7.1 );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  // energies
  CHECK_THAT( 1e-5  , WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 9.5e+5, WithinRel( chunk.upperEnergyLimit() ) );

  // spin groups
  auto groups = chunk.spinGroups();
  CHECK( 7 == groups.size() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  auto spingroup = groups[0];
  CHECK( 0.5 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  auto channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel0 = channels[0];
  CHECK( id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel1 = channels[1];
  CHECK( id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( equal_radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  auto background = SammyBackground( { 0.45, 3.2e-7, 0. }, { 0.075, 0. }, 0., 9.55e+5 );
  CHECK( Channel::Background( background ) == channel1.background().value() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 70 == table.numberEnergies() );

  auto energies = table.energies();
  CHECK_THAT( 1.241000e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 8.331700e+5, WithinRel( energies[69] ) );

  auto resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 0.4462 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.22   / 2. ), WithinRel( resonances[0][69] ) );
  CHECK_THAT( std::sqrt( 20.86 / 2. / channel1.penetrability( 1.241000e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 1331. / 2. / channel1.penetrability( 8.331700e+5 ) ), WithinRel( resonances[1][69] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[1];
  CHECK( 0.5 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2+}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Sr88->n,Sr88{0,1/2,1/2+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  auto radii = channel1.channelRadii();
  CHECK_THAT( 7.1, WithinRel( std::get< double >( radii.penetrabilityRadius() ) ) );
  CHECK( std::nullopt == radii.shiftFactorRadius() );
  CHECK_THAT( 6.8, WithinRel( std::get< double >( radii.phaseShiftRadius().value() ) ) );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  background = SammyBackground( { -0.043, 2.8e-8, 0. }, { 0.01, 0. }, 0., 9.55e+5 );
  CHECK( Channel::Background( background ) == channel1.background().value() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 66 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 1.3840e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 9.4334e+5, WithinRel( energies[65] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 0.0805 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.19   / 2. ), WithinRel( resonances[0][65] ) );
  CHECK_THAT( std::sqrt( 194.15 / 2. / channel1.penetrability( 1.3840e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 199.   / 2. / channel1.penetrability( 9.4334e+5 ) ), WithinRel( resonances[1][65] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[2];
  CHECK( 1.5 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2-}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Sr88->n,Sr88{1,1/2,3/2-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( equal_radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  background = SammyBackground( { 0.43, -1.8e-7, 0. }, { 0.22, 0. }, 0., 9.55e+5 );
  CHECK( Channel::Background( background ) == channel1.background().value() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 104 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 1.8210e+4, WithinRel( energies[0] ) );
  CHECK_THAT( 9.4823e+5, WithinRel( energies[103] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 0.28 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 0.28 / 2. ), WithinRel( resonances[0][103] ) );
  CHECK_THAT( std::sqrt( 8.5000e-4 / 2. / channel1.penetrability( 1.8210e+4 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 1.0135e+4 / 2. / channel1.penetrability( 9.4823e+5 ) ), WithinRel( resonances[1][103] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[3];
  CHECK( 1.5 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2+}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Sr88->n,Sr88{2,1/2,3/2+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( equal_radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  background = SammyBackground( { -0.7, 2.3e-6, 0. }, { 0.041, 0. }, 0., 9.55e+5 );
  CHECK( Channel::Background( background ) == channel1.background().value() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 30 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 2.6653e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 8.7494e+5, WithinRel( energies[29] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 1.21e-1 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 2.80e-1 / 2. ), WithinRel( resonances[0][29] ) );
  CHECK_THAT( std::sqrt( 2.525e+1 / 2. / channel1.penetrability( 2.6653e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 1.506e+3 / 2. / channel1.penetrability( 8.7494e+5 ) ), WithinRel( resonances[1][29] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[4];
  CHECK( 2.5 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2-}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Sr88->n,Sr88{3,1/2,5/2-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( equal_radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  background = SammyBackground( { 0.001, 4.6e-7, 0. }, { 0.24, 0. }, 0., 9.55e+5 );
  CHECK( Channel::Background( background ) == channel1.background().value() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 90 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 4.0846e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 8.9944e+5, WithinRel( energies[89] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 2.8e-1 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 2.8e-1 / 2. ), WithinRel( resonances[0][89] ) );
  CHECK_THAT( std::sqrt( 1.0600e+1 / 2. / channel1.penetrability( 4.0846e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 1.2933e+2 / 2. / channel1.penetrability( 8.9944e+5 ) ), WithinRel( resonances[1][89] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 5
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[5];
  CHECK( 2.5 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2+}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Sr88->n,Sr88{2,1/2,5/2+}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( equal_radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  background = SammyBackground( { -2.5, 3.3e-6, 0. }, { 0.0026, 0. }, 0., 9.55e+5 );
  CHECK( Channel::Background( background ) == channel1.background().value() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 5, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 10 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 4.0982e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 8.4961e+5, WithinRel( energies[9] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 2.8e-1 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 2.8e-1 / 2. ), WithinRel( resonances[0][9] ) );
  CHECK_THAT( std::sqrt( 3.6333e+0 / 2. / channel1.penetrability( 4.0982e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 7.1667e+1 / 2. / channel1.penetrability( 8.4961e+5 ) ), WithinRel( resonances[1][9] ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 6
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[6];
  CHECK( 3.5 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  // channels
  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, channel 0: capture (eliminated)
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,7/2-}" ) == channel0.identifier() );
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
  CHECK( Kinematics::NonRelativistic == channel0.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Sr88->n,Sr88{3,1/2,7/2-}" ) == channel1.identifier() );
  CHECK( true == channel1.isIncidentChannel() );

  // incident particle pair
  CHECK( neutron_pair == channel1.incidentParticlePair() );

  // outgoing particle pair
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  // radii
  CHECK( equal_radii == channel1.channelRadii() );

  // boundary conditions
  CHECK( std::nullopt == channel1.boundaryCondition() );

  // background
  background = SammyBackground( { 0.001, 9e-8, 0. }, { 0.19, 0. }, 0., 9.55e+5 );
  CHECK( Channel::Background( background ) == channel1.background().value() );

  // Q value
  CHECK_THAT( 0.0, WithinRel( channel1.qValue() ) );

  // kinematics type
  CHECK( Kinematics::NonRelativistic == channel1.kinematicsType() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 6, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 2 == table.numberChannels() );
  CHECK( 73 == table.numberEnergies() );

  energies = table.energies();
  CHECK_THAT( 5.2884e+5, WithinRel( energies[0] ) );
  CHECK_THAT( 9.4756e+5, WithinRel( energies[72] ) );

  resonances = table.reducedWidthAmplitudes();
  CHECK_THAT( std::sqrt( 2.8e-1 / 2. ), WithinRel( resonances[0][0] ) );
  CHECK_THAT( std::sqrt( 2.8e-1 / 2. ), WithinRel( resonances[0][72] ) );
  CHECK_THAT( std::sqrt( 5.995e+1 / 2. / channel1.penetrability( 5.2884e+5 ) ), WithinRel( resonances[1][0] ) );
  CHECK_THAT( std::sqrt( 8.750e+0 / 2. / channel1.penetrability( 9.4756e+5 ) ), WithinRel( resonances[1][72] ) );
}