// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

#include <iostream>

// what we are testing
#include "njoy/format/endf/read/resonances/urr/caseC/createCompoundSystem.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::format;
using namespace njoy::dryad;
using namespace njoy::constants;

void verifyChunkEu156( const resonances::UnresolvedCompoundSystem& );

SCENARIO( "createCompoundSystem" ) {

  GIVEN( "ENDF MF2 MT151 fully energy-dependent unresolved (Case C) data" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-063_Eu_156-endf80.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::UnresolvedEnergyDependent >(
                        section.isotopes().front().resonanceRanges().front().parameters() );

    WHEN( "a set of parsed Case C data from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile = id::ParticleID::neutron();
        id::ParticleID target = id::ParticleID( "Eu156" );
        auto chunk = endf::read::resonances::urr::caseC::createCompoundSystem( projectile, target, 1., 1e5, 0, std::nullopt, parameters );

        verifyChunkEu156( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkEu156( const resonances::UnresolvedCompoundSystem& chunk ) {

  // Eu156 ENDF/B-VIII.1 LRF=2 unresolved resonance evaluation

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto eu156 = id::ParticleID( "Eu156" );
  auto eu157 = id::ParticleID( "Eu157[all]" );

  resonances::ParticlePair photon_pair( Particle( photon, 0, 0, +1 ),
                            Particle( eu157, 0 * neutron_mass, 0, +1 ) );
  resonances::ParticlePair neutron_pair( Particle( neutron, neutron_mass, 0.5, +1 ),
                             Particle( eu156, 154.586 * neutron_mass, 0, +1 ) );

  double mass = 154.586 * neutron_mass;
  double a = 7.420296947236985;
  double ap = 7.0741;
  resonances::ChannelRadii zero_radii( 0., 0. );
  resonances::ChannelRadii elastic_radii( a, ap );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  // energies
  CHECK_THAT( 1.  , WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 1e5 , WithinRel( chunk.upperEnergyLimit() ) );

  // spin groups
  auto groups = chunk.spinGroups();
  CHECK( 5 == groups.size() );

  auto spingroup = groups[0];
  CHECK_THAT( 0.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( -1 == spingroup.parity() );

  auto channels = spingroup.channels();

  CHECK( 3 == channels.size() );


  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel0 = channels[0];
  CHECK( id::ChannelID("n,Eu156->g,Eu157[all]{0,0,1/2-}" ) == channel0.identifier() );

  CHECK( neutron_pair == channel0.incidentParticlePair() );
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  CHECK( zero_radii == channel0.channelRadii() );


  CHECK( false == channel0.hasPenetrability() );
  CHECK( false == channel0.hasShiftFactor() );
  CHECK( false == channel0.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel1 = channels[1];
  CHECK( id::ChannelID( "n,Eu156->n,Eu156{1,1/2,1/2-}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 2: competitive
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  
  auto channel2 = channels[2];
  CHECK( id::ChannelID( "n,Eu156->competitive{0,0,1/2-}" ) == channel2.identifier() );

  CHECK( neutron_pair == channel2.incidentParticlePair() );
  CHECK( std::nullopt == channel2.outgoingParticlePair() );

  CHECK( zero_radii == channel2.channelRadii() );

  CHECK( false == channel2.hasPenetrability() );
  CHECK( false == channel2.hasShiftFactor() );
  CHECK( false == channel2.hasPhaseShift() );


  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto table = spingroup.resonanceTable();

  CHECK( 3 == table.channels().size() );
  CHECK( 3 == table.widths().size() );

  auto widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );
  CHECK_THAT( 1.5316, WithinRel( widths[2].degreesOfFreedom().value() ) );

  CHECK( 28 == widths[0].energies().size() );
  CHECK_THAT( 1.  , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5 , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 6.812000e-4, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 1.140300e-3, WithinRel( widths[1].values().back() ) );
  CHECK_THAT( 0.000000e-1, WithinRel( widths[2].values().front() ) );
  CHECK_THAT( 6.816400e-1, WithinRel( widths[2].values().back() ) );

  auto spacing = table.spacings();
  CHECK( 28 == spacing.energies().size() );
  CHECK_THAT( 1.3100000000e+1, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 2.1928000000e+1, WithinRel( spacing.values().back() ) );


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  spingroup = groups[1];
  CHECK_THAT( 0.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( +1 == spingroup.parity() );

  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  channel0 = channels[0];
  CHECK( id::ChannelID("n,Eu156->g,Eu157[all]{0,0,1/2+}" ) == channel0.identifier() );

  CHECK( neutron_pair == channel0.incidentParticlePair() );
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  CHECK( zero_radii == channel0.channelRadii() );


  CHECK( false == channel0.hasPenetrability() );
  CHECK( false == channel0.hasShiftFactor() );
  CHECK( false == channel0.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Eu156->n,Eu156{0,1/2,1/2+}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 1: competitive
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID("n,Eu156->competitive{0,0,1/2+}")  == channel2.identifier() );

  CHECK( neutron_pair == channel2.incidentParticlePair() );
  CHECK( std::nullopt == channel2.outgoingParticlePair() );

  CHECK( zero_radii == channel2.channelRadii() );

  CHECK( false == channel2.hasPenetrability() );
  CHECK( false == channel2.hasShiftFactor() );
  CHECK( false == channel2.hasPhaseShift() );


  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();

  CHECK( 3 == table.channels().size() );
  CHECK( 3 == table.widths().size() );

  widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );
  CHECK_THAT( 2., WithinRel( widths[2].degreesOfFreedom().value() ) );


  CHECK( 28 == widths[0].energies().size() );
  CHECK_THAT( 1.  , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5 , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 3.013000e-3, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 5.043400e-3, WithinRel( widths[1].values().back() ) );
  CHECK_THAT( 0.000000e-1, WithinRel( widths[2].values().front() ) );
  CHECK_THAT( 2.559300e+0, WithinRel( widths[2].values().back() ) );

  spacing = table.spacings();
  CHECK( 28 == spacing.energies().size() );
  CHECK_THAT( 1.3100000000e+1, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 2.1928000000e+1, WithinRel( spacing.values().back() ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  spingroup = groups[2];
  CHECK_THAT( 1.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( -1 == spingroup.parity() );

  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Eu156->g,Eu157[all]{0,0,3/2-}" ) == channel0.identifier() );

  CHECK( neutron_pair == channel0.incidentParticlePair() );
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  CHECK( zero_radii == channel0.channelRadii() );

  CHECK( false == channel0.hasPenetrability() );
  CHECK( false == channel0.hasShiftFactor() );
  CHECK( false == channel0.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Eu156->n,Eu156{1,1/2,3/2-}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 2: competitive
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Eu156->competitive{0,0,3/2-}" ) == channel2.identifier() );

  CHECK( neutron_pair == channel2.incidentParticlePair() );
  CHECK( std::nullopt == channel2.outgoingParticlePair() );

  CHECK( zero_radii == channel2.channelRadii() );

  CHECK( false == channel2.hasPenetrability() );
  CHECK( false == channel2.hasShiftFactor() );
  CHECK( false == channel2.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.channels().size() );
  CHECK( 3 == table.widths().size() );

  widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );
  CHECK_THAT( 1.5319, WithinRel( widths[2].degreesOfFreedom().value() ) );

  CHECK( 28 == widths[0].energies().size() );
  CHECK_THAT( 1.  , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5 , WithinRel( widths[0].energies().back() ) );

  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 3.4060000000e-4, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 5.7013000000e-4, WithinRel( widths[1].values().back() ) );
  CHECK_THAT( 0.000000e-1, WithinRel( widths[2].values().front() ) );
  CHECK_THAT( 3.4085000000e-1, WithinRel( widths[2].values().back() ) );

  spacing = table.spacings();
  CHECK( 28 == spacing.energies().size() );
  CHECK_THAT( 6.5500000000e+0, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 1.0964000000e+1, WithinRel( spacing.values().back() ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[3];
  CHECK_THAT( 1.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( +1 == spingroup.parity() );

  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Eu156->g,Eu157[all]{0,0,3/2+}" ) == channel0.identifier() );

  CHECK( neutron_pair == channel0.incidentParticlePair() );
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  CHECK( zero_radii == channel0.channelRadii() );

  CHECK( false == channel0.hasPenetrability() );
  CHECK( false == channel0.hasShiftFactor() );
  CHECK( false == channel0.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Eu156->n,Eu156{2,1/2,3/2+}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 2: competitive
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Eu156->competitive{0,0,3/2+}" ) == channel2.identifier() );

  CHECK( neutron_pair == channel2.incidentParticlePair() );
  CHECK( std::nullopt == channel2.outgoingParticlePair() );

  CHECK( zero_radii == channel2.channelRadii() );

  CHECK( false == channel2.hasPenetrability() );
  CHECK( false == channel2.hasShiftFactor() );
  CHECK( false == channel2.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.channels().size() );
  CHECK( 3 == table.widths().size() );

  widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );
  CHECK_THAT( 1.0314, WithinRel( widths[2].degreesOfFreedom().value() ) );

  CHECK( 28 == widths[0].energies().size() );
  CHECK_THAT( 1.  , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5 , WithinRel( widths[0].energies().back() ) );

  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 1.5720000000e-3, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 2.6314000000e-3, WithinRel( widths[1].values().back() ) );
  CHECK_THAT( 0.0000000000e-1, WithinRel( widths[2].values().front() ) );
  CHECK_THAT( 7.1116000000e-1, WithinRel( widths[2].values().back() ) );

  spacing = table.spacings();
  CHECK( 28 == spacing.energies().size() );
  CHECK_THAT( 6.5500000000e+0, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 1.0964000000e+1, WithinRel( spacing.values().back() ) );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[4];
  CHECK_THAT( 2.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( +1 == spingroup.parity() );

  channels = spingroup.channels();

  CHECK( 3 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Eu156->g,Eu157[all]{0,0,5/2+}" ) == channel0.identifier() );

  CHECK( neutron_pair == channel0.incidentParticlePair() );
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  CHECK( zero_radii == channel0.channelRadii() );

  CHECK( false == channel0.hasPenetrability() );
  CHECK( false == channel0.hasShiftFactor() );
  CHECK( false == channel0.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Eu156->n,Eu156{2,1/2,5/2+}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 2: competitive
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Eu156->competitive{0,0,5/2+}" ) == channel2.identifier() );

  CHECK( neutron_pair == channel2.incidentParticlePair() );
  CHECK( std::nullopt == channel2.outgoingParticlePair() );

  CHECK( zero_radii == channel2.channelRadii() );

  CHECK( false == channel2.hasPenetrability() );
  CHECK( false == channel2.hasShiftFactor() );
  CHECK( false == channel2.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();
  CHECK( 3 == table.channels().size() );
  CHECK( 3 == table.widths().size() );

  widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );
  CHECK_THAT( 2., WithinRel( widths[2].degreesOfFreedom().value() ) );

  CHECK( 28 == widths[0].energies().size() );
  CHECK_THAT( 1.  , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5 , WithinRel( widths[0].energies().back() ) );

  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 1.0000000000e-1, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 1.0480000000e-3, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 1.7542000000e-3, WithinRel( widths[1].values().back() ) );
  CHECK( 0. == widths[2].values().front() );
  CHECK_THAT( 6.0693000000e-3, WithinRel( widths[2].values().back() ) );

  spacing = table.spacings();
  CHECK( 28 == spacing.energies().size() );
  CHECK_THAT( 4.3667000000e+0, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 7.3093000000e+0, WithinRel( spacing.values().back() ) );

}

