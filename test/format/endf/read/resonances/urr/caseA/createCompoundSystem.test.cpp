// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/resonances/urr/caseA/createCompoundSystem.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::format;
using namespace njoy::dryad;
using namespace njoy::constants;

void verifyChunkBa140( const resonances::UnresolvedCompoundSystem& );

SCENARIO( "createCompoundSystem" ) {

  GIVEN( "ENDF MF2 MT151 energy-independent unresolved (Case A) data" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-056_Ba_140-endf80.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::UnresolvedEnergyIndependent >(
                        section.isotopes().front().resonanceRanges().back().parameters() );

    WHEN( "a set of parsed Case A data from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile = id::ParticleID::neutron();
        id::ParticleID target = id::ParticleID( "Ba140" );
        auto chunk = endf::read::resonances::urr::caseA::createCompoundSystem( projectile, target, 23000., 1e5, 0, std::nullopt, parameters );

        verifyChunkBa140( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkBa140( const resonances::UnresolvedCompoundSystem& chunk ) {

  // Ba140 ENDF/B-VIII.1 LRF=1 unresolved resonance evaluation

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto ba140 = id::ParticleID( "Ba140" );
  auto ba141 = id::ParticleID( "Ba141[all]" );

  resonances::ParticlePair photon_pair( Particle( photon, 0, 0, +1 ),
                            Particle( ba141, 0 * neutron_mass, 0, +1 ) );
  resonances::ParticlePair neutron_pair( Particle( neutron, neutron_mass, 0.5, +1 ),
                             Particle( ba140, 138.709 * neutron_mass, 0, +1 ) );

  double a = 1.23 * std::pow( 138.709 * neutron_mass, 1. / 3. ) + 0.8;
  double ap = 6.233;
  resonances::ChannelRadii zero_radii( 0., 0. );
  resonances::ChannelRadii elastic_radii( a, ap );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  // energies
  CHECK_THAT( 23000. , WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 1e5    , WithinRel( chunk.upperEnergyLimit() ) );

  // spin groups
  auto groups = chunk.spinGroups();
  CHECK( 5 == groups.size() );

  auto spingroup = groups[0];
  CHECK_THAT( 0.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( -1 == spingroup.parity() );

  auto channels = spingroup.channels();

  CHECK( 2 == channels.size() );


  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto channel0 = channels[0];
  CHECK( id::ChannelID( "n,Ba140->g,Ba141[all]{0,0,1/2-}" ) == channel0.identifier() );

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
  CHECK( id::ChannelID( "n,Ba140->n,Ba140{1,1/2,1/2-}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 0, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  auto table = spingroup.resonanceTable();

  CHECK( 2 == table.channels().size() );
  CHECK( 2 == table.widths().size() );

  auto widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );

  CHECK( 2 == widths[0].energies().size() );
  CHECK_THAT( 23000. , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5    , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 9.0000000000e-2, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 9.0000000000e-2, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 5.2800000000e-1, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 5.2800000000e-1, WithinRel( widths[1].values().back() ) );

  auto spacing = table.spacings();
  CHECK( 2 == spacing.energies().size() );
  CHECK_THAT( 4.4000000000e+3, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 4.4000000000e+3, WithinRel( spacing.values().back() ) );


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  spingroup = groups[1];
  CHECK_THAT( 0.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( +1 == spingroup.parity() );

  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Ba140->g,Ba141[all]{0,0,1/2+}" ) == channel0.identifier() );

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
  CHECK( id::ChannelID( "n,Ba140->n,Ba140{0,1/2,1/2+}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 1, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();

  CHECK( 2 == table.channels().size() );
  CHECK( 2 == table.widths().size() );

  widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );

  CHECK( 2 == widths[0].energies().size() );
  CHECK_THAT( 23000. , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5    , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 5.0000000000e-2, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 5.0000000000e-2, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 4.4000000000e-1, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 4.4000000000e-1, WithinRel( widths[1].values().back() ) );

  spacing = table.spacings();
  CHECK( 2 == spacing.energies().size() );
  CHECK_THAT( 4.4000000000e+3, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 4.4000000000e+3, WithinRel( spacing.values().back() ) );


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  spingroup = groups[2];
  CHECK_THAT( 1.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( -1 == spingroup.parity() );

  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Ba140->g,Ba141[all]{0,0,3/2-}" ) == channel0.identifier() );

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
  CHECK( id::ChannelID( "n,Ba140->n,Ba140{1,1/2,3/2-}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 2, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();

  CHECK( 2 == table.channels().size() );
  CHECK( 2 == table.widths().size() );

  widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );

  CHECK( 2 == widths[0].energies().size() );
  CHECK_THAT( 23000. , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5    , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 9.0000000000e-2, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 9.0000000000e-2, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 2.6400000000e-1, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 2.6400000000e-1, WithinRel( widths[1].values().back() ) );

  spacing = table.spacings();
  CHECK( 2 == spacing.energies().size() );
  CHECK_THAT( 2.2000000000e+3, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 2.2000000000e+3, WithinRel( spacing.values().back() ) );


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  spingroup = groups[3];
  CHECK_THAT( 1.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( +1 == spingroup.parity() );

  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Ba140->g,Ba141[all]{0,0,3/2+}" ) == channel0.identifier() );

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
  CHECK( id::ChannelID( "n,Ba140->n,Ba140{2,1/2,3/2+}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 3, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();

  CHECK( 2 == table.channels().size() );
  CHECK( 2 == table.widths().size() );

  widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );

  CHECK( 2 == widths[0].energies().size() );
  CHECK_THAT( 23000. , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5    , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 5.0000000000e-2, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 5.0000000000e-2, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 3.3000000000e-2, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 3.3000000000e-2, WithinRel( widths[1].values().back() ) );

  spacing = table.spacings();
  CHECK( 2 == spacing.energies().size() );
  CHECK_THAT( 2.2000000000e+3, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 2.2000000000e+3, WithinRel( spacing.values().back() ) );


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 4
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  spingroup = groups[4];
  CHECK_THAT( 2.5, WithinRel( spingroup.totalAngularMomentum() ) );
  CHECK( +1 == spingroup.parity() );

  channels = spingroup.channels();

  CHECK( 2 == channels.size() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, channel 0: capture
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  channel0 = channels[0];
  CHECK( id::ChannelID( "n,Ba140->g,Ba141[all]{0,0,5/2+}" ) == channel0.identifier() );

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
  CHECK( id::ChannelID( "n,Ba140->n,Ba140{2,1/2,5/2+}" ) == channel1.identifier() );

  CHECK( neutron_pair == channel1.incidentParticlePair() );
  CHECK( neutron_pair == channel1.outgoingParticlePair().value() );

  CHECK( elastic_radii == channel1.channelRadii() );

  CHECK( true == channel1.hasPenetrability() );
  CHECK( true == channel1.hasShiftFactor() );
  CHECK( true == channel1.hasPhaseShift() );

  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *
  // spin group 4, resonance table
  // - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - *

  table = spingroup.resonanceTable();

  CHECK( 2 == table.channels().size() );
  CHECK( 2 == table.widths().size() );

  widths = table.widths();
  CHECK_THAT( 0., WithinRel( widths[0].degreesOfFreedom().value() ) );
  CHECK_THAT( 1., WithinRel( widths[1].degreesOfFreedom().value() ) );

  CHECK( 2 == widths[0].energies().size() );
  CHECK_THAT( 23000. , WithinRel( widths[0].energies().front() ) );
  CHECK_THAT( 1e5    , WithinRel( widths[0].energies().back() ) );
  CHECK_THAT( 5.0000000000e-2, WithinRel( widths[0].values().front() ) );
  CHECK_THAT( 5.0000000000e-2, WithinRel( widths[0].values().back() ) );
  CHECK_THAT( 2.2000000000e-2, WithinRel( widths[1].values().front() ) );
  CHECK_THAT( 2.2000000000e-2, WithinRel( widths[1].values().back() ) );

  spacing = table.spacings();
  CHECK( 2 == spacing.energies().size() );
  CHECK_THAT( 1.4666700000e+3, WithinRel( spacing.values().front() ) );
  CHECK_THAT( 1.4666700000e+3, WithinRel( spacing.values().back() ) );
}
