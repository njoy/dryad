// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

#include <iostream>

// what we are testing
#include "njoy/format/endf/read/resonances/urr/caseB/createCompoundSystem.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::format;
using namespace njoy::dryad;
using namespace njoy::constants;

void verifyChunkPu238( const resonances::UnresolvedCompoundSystem& );

SCENARIO( "createCompoundSystem" ) {

  GIVEN( "ENDF MF2 MT151 energy-dependent-fission-width unresolved (Case B) data" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-094_Pu_238-endf70.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::UnresolvedEnergyDependentFissionWidths >(
                        section.isotopes().front().resonanceRanges().back().parameters() );

    WHEN( "a set of parsed Case B data from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile = id::ParticleID::neutron();
        id::ParticleID target = id::ParticleID( "Pu238" );
        auto chunk = endf::read::resonances::urr::caseB::createCompoundSystem( projectile, target, 200., 1e4, 0, std::nullopt, parameters );

        verifyChunkPu238( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkPu238( const resonances::UnresolvedCompoundSystem& chunk ) {

  // Pu238 ENDF/B-VII.0 LRF=1 LFW=1 unresolved resonance evaluation

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto pu238 = id::ParticleID( "Pu238" );
  auto pu239 = id::ParticleID( "Pu239[all]" );

  resonances::ParticlePair photon_pair( Particle( photon, 0, 0, +1 ),
                            Particle( pu239, 0 * neutron_mass, 0, +1 ) );
  resonances::ParticlePair neutron_pair( Particle( neutron, neutron_mass, 0.5, +1 ),
                             Particle( pu238, 236.0045 * neutron_mass, 0, +1 ) );

  double mass = 236.0045 * neutron_mass;
  double a = 8.4230279330264572;
  double ap = 9.309;
  resonances::ChannelRadii zero_radii( 0., 0. );
  resonances::ChannelRadii elastic_radii( a, ap );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  // energies
  CHECK_THAT( 200., WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 1e4 , WithinRel( chunk.upperEnergyLimit() ) );

  // spin groups
  auto groups = chunk.spinGroups();
  CHECK( 3 == groups.size() );

  auto spingroup = groups[0];
  CHECK_THAT( 0.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( -1 == spingroup.parity() );

  auto channels = spingroup.channels();

  CHECK( 3 == channels.size() );


  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel0 = channels[0];
  CHECK( id::ChannelID("n,Pu238->g,Pu239[all]{0,0,1/2-}" ) == channel0.identifier() );

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
  CHECK( id::ChannelID( "n,Pu238->n,Pu238{1,1/2,1/2-}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 2: fission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel2 = channels[2];
  CHECK( id::ChannelID( "n,Pu238->fission(t){0,0,1/2-}" ) == channel2.identifier() );

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
  CHECK_THAT( 3., WithinRel( widths[2].degreesOfFreedom().value() ) );

  // capture and elastic average widths are energy independent (flat, 2 points)
  CHECK( 2 == widths[0].energies().size() );
  CHECK_THAT( 200., WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e4 , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 3.480000e-2, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 3.480000e-2, WithinRel( widths[0].values().back() ) );

  CHECK( 2 == widths[1].energies().size() );
  CHECK_THAT( 1.610000e-3, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 1.610000e-3, WithinRel( widths[1].values().back() ) );

  // the fission average width is energy dependent (3 points)
  CHECK( 3 == widths[2].energies().size() );
  CHECK_THAT( 200., WithinRel( widths[2].energies().front() ) );
  CHECK_THAT( 1e4 , WithinRel( widths[2].energies().back() ) );
  CHECK_THAT( 7.810000e-3, WithinRel( widths[2].values().front() ) );
  CHECK_THAT( 9.025000e-2, WithinRel( widths[2].values().back() ) );

  auto spacing = table.spacings();
  CHECK( 2 == spacing.energies().size() );
  CHECK_THAT( 1.3700000000e+1, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 1.3700000000e+1, WithinRel( spacing.values().back() ) );


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
  CHECK( id::ChannelID("n,Pu238->g,Pu239[all]{0,0,1/2+}" ) == channel0.identifier() );

  CHECK( neutron_pair == channel0.incidentParticlePair() );
  CHECK( photon_pair == channel0.outgoingParticlePair().value() );

  CHECK( zero_radii == channel0.channelRadii() );


  CHECK( false == channel0.hasPenetrability() );
  CHECK( false == channel0.hasShiftFactor() );
  CHECK( false == channel0.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 1: elastic
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel1 = channels[1];
  CHECK( id::ChannelID( "n,Pu238->n,Pu238{0,1/2,1/2+}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 2: fission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID("n,Pu238->fission(t){0,0,1/2+}")  == channel2.identifier() );

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
  CHECK_THAT( 3., WithinRel( widths[2].degreesOfFreedom().value() ) );

  CHECK( 2 == widths[0].energies().size() );
  CHECK_THAT( 200., WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e4 , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 3.480000e-2, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 3.480000e-2, WithinRel( widths[0].values().back() ) );

  CHECK( 2 == widths[1].energies().size() );
  CHECK_THAT( 2.556000e-3, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 2.556000e-3, WithinRel( widths[1].values().back() ) );

  CHECK( 3 == widths[2].energies().size() );
  CHECK_THAT( 200., WithinRel( widths[2].energies().front() ) );
  CHECK_THAT( 1e4 , WithinRel( widths[2].energies().back() ) );
  CHECK_THAT( 7.810000e-3, WithinRel( widths[2].values().front() ) );
  CHECK_THAT( 9.025000e-2, WithinRel( widths[2].values().back() ) );

  spacing = table.spacings();
  CHECK( 2 == spacing.energies().size() );
  CHECK_THAT( 1.3700000000e+1, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 1.3700000000e+1, WithinRel( spacing.values().back() ) );


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
  CHECK( id::ChannelID( "n,Pu238->g,Pu239[all]{0,0,3/2-}" ) == channel0.identifier() );

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
  CHECK( id::ChannelID( "n,Pu238->n,Pu238{1,1/2,3/2-}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 2: fission
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel2 = channels[2];
  CHECK( id::ChannelID( "n,Pu238->fission(t){0,0,3/2-}" ) == channel2.identifier() );

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
  CHECK_THAT( 3., WithinRel( widths[2].degreesOfFreedom().value() ) );

  CHECK( 2 == widths[0].energies().size() );
  CHECK_THAT( 200., WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e4 , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 3.480000e-2, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 3.480000e-2, WithinRel( widths[0].values().back() ) );

  CHECK( 2 == widths[1].energies().size() );
  CHECK_THAT( 8.390000e-4, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 8.390000e-4, WithinRel( widths[1].values().back() ) );

  CHECK( 3 == widths[2].energies().size() );
  CHECK_THAT( 200., WithinRel( widths[2].energies().front() ) );
  CHECK_THAT( 1e4 , WithinRel( widths[2].energies().back() ) );
  CHECK_THAT( 3.910000e-3, WithinRel( widths[2].values().front() ) );
  CHECK_THAT( 4.518000e-2, WithinRel( widths[2].values().back() ) );

  spacing = table.spacings();
  CHECK( 2 == spacing.energies().size() );
  CHECK_THAT( 6.8500000000e+0, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 6.8500000000e+0, WithinRel( spacing.values().back() ) );

}
