// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/read/resonances/lrf7/createChannels.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createBoundaryCondition.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;
using namespace njoy::constants;

void verifyChunk( const std::vector< resonances::Channel >& );
void verifyChunkWithBackground( const std::vector< resonances::Channel >& );

SCENARIO( "createChannels" ) {

  GIVEN( "ENDF MF2 MT151 sections - no background elements" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );
    auto pairs = parameters.particlePairs();
    auto channels = parameters.spinGroups().front().channels();
    auto background = parameters.spinGroups().front().background();

    WHEN( "a single parsed scattering radius from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Cl35" );
        auto boundary_condition = endf::read::resonances::lrf7::createBoundaryCondition( pairs );
        auto kinematics = resonances::Kinematics::NonRelativistic;
        auto chunk = endf::read::resonances::lrf7::createChannels(
                       projectile, target, boundary_condition, kinematics, pairs, channels, background );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF2 MT151 sections - with background elements" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-038_Sr_088.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );
    auto pairs = parameters.particlePairs();
    auto channels = parameters.spinGroups().front().channels();
    auto background = parameters.spinGroups().front().background();

    WHEN( "a single parsed scattering radius from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Sr88" );
        auto boundary_condition = endf::read::resonances::lrf7::createBoundaryCondition( pairs );
        auto kinematics = resonances::Kinematics::NonRelativistic;
        auto chunk = endf::read::resonances::lrf7::createChannels(
                       projectile, target, boundary_condition, kinematics, pairs, channels, background );

        verifyChunkWithBackground( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::vector< resonances::Channel >& chunk ) {

  CHECK( 3 == chunk.size() );

  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ) == chunk[0].identifier() );
  auto incident = chunk[0].incidentParticlePair();
  CHECK( id::ParticleID::neutron() == incident.lightParticle().identifier() );
  CHECK( 0 == incident.lightParticle().charge() );
  CHECK( neutron_mass == incident.lightParticle().mass() );
  CHECK( 0.5 == incident.lightParticle().spin() );
  CHECK( +1 == incident.lightParticle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == incident.heavyParticle().identifier() );
  CHECK( 17 == incident.heavyParticle().charge() );
  CHECK( 34.66845 * neutron_mass == incident.heavyParticle().mass() );
  CHECK( 1.5 == incident.heavyParticle().spin() );
  CHECK( +1 == incident.heavyParticle().parity() );
  auto outgoing = chunk[0].outgoingParticlePair().value();
  CHECK( id::ParticleID::photon() == outgoing.lightParticle().identifier() );
  CHECK( 0 == outgoing.lightParticle().charge() );
  CHECK( 0 == outgoing.lightParticle().mass() );
  CHECK( 1 == outgoing.lightParticle().spin() );
  CHECK( +1 == outgoing.lightParticle().parity() );
  CHECK( id::ParticleID( "Cl36[all]" ) == outgoing.heavyParticle().identifier() );
  CHECK( 17 == outgoing.heavyParticle().charge() );
  CHECK( 35.65932 * neutron_mass == outgoing.heavyParticle().mass() );
  CHECK( 0 == outgoing.heavyParticle().spin() );
  CHECK( +1 == outgoing.heavyParticle().parity() );
  CHECK( false == chunk[0].isIncidentChannel() );
  CHECK( 0 == chunk[0].qValue() );
  CHECK( std::nullopt == chunk[0].boundaryCondition() );
  CHECK( std::nullopt == chunk[0].background() );
  CHECK_THAT( 0., WithinRel( std::get<double>( chunk[0].channelRadii().penetrabilityRadius() ) ) );
  CHECK( std::nullopt == chunk[0].channelRadii().shiftFactorRadius() );
  CHECK_THAT( 0., WithinRel( std::get<double>( chunk[0].channelRadii().phaseShiftRadius().value() ) ) );
  CHECK( resonances::Kinematics::NonRelativistic == chunk[0].kinematicsType() );

  CHECK( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) == chunk[1].identifier() );
  incident = chunk[1].incidentParticlePair();
  CHECK( id::ParticleID::neutron() == incident.lightParticle().identifier() );
  CHECK( 0 == incident.lightParticle().charge() );
  CHECK( neutron_mass == incident.lightParticle().mass() );
  CHECK( 0.5 == incident.lightParticle().spin() );
  CHECK( +1 == incident.lightParticle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == incident.heavyParticle().identifier() );
  CHECK( 17 == incident.heavyParticle().charge() );
  CHECK( 34.66845 * neutron_mass == incident.heavyParticle().mass() );
  CHECK( 1.5 == incident.heavyParticle().spin() );
  CHECK( +1 == incident.heavyParticle().parity() );
  outgoing = chunk[1].outgoingParticlePair().value();
  CHECK( id::ParticleID::neutron() == outgoing.lightParticle().identifier() );
  CHECK( 0 == outgoing.lightParticle().charge() );
  CHECK( neutron_mass == outgoing.lightParticle().mass() );
  CHECK( 0.5 == outgoing.lightParticle().spin() );
  CHECK( +1 == outgoing.lightParticle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == outgoing.heavyParticle().identifier() );
  CHECK( 17 == outgoing.heavyParticle().charge() );
  CHECK( 34.66845 * neutron_mass == outgoing.heavyParticle().mass() );
  CHECK( 1.5 == outgoing.heavyParticle().spin() );
  CHECK( +1 == outgoing.heavyParticle().parity() );
  CHECK( true == chunk[1].isIncidentChannel() );
  CHECK( 0 == chunk[1].qValue() );
  CHECK( std::nullopt == chunk[1].boundaryCondition() );
  CHECK( std::nullopt == chunk[1].background() );
  CHECK_THAT( 4.82222, WithinRel( std::get<double>( chunk[1].channelRadii().penetrabilityRadius() ) ) );
  CHECK( std::nullopt == chunk[1].channelRadii().shiftFactorRadius() );
  CHECK_THAT( 3.66798, WithinRel( std::get<double>( chunk[1].channelRadii().phaseShiftRadius().value() ) ) );
  CHECK( resonances::Kinematics::NonRelativistic == chunk[1].kinematicsType() );

  CHECK( id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) == chunk[2].identifier() );
  incident = chunk[2].incidentParticlePair();
  CHECK( id::ParticleID::neutron() == incident.lightParticle().identifier() );
  CHECK( 0 == incident.lightParticle().charge() );
  CHECK( neutron_mass == incident.lightParticle().mass() );
  CHECK( 0.5 == incident.lightParticle().spin() );
  CHECK( +1 == incident.lightParticle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == incident.heavyParticle().identifier() );
  CHECK( 17 == incident.heavyParticle().charge() );
  CHECK( 34.66845 * neutron_mass == incident.heavyParticle().mass() );
  CHECK( 1.5 == incident.heavyParticle().spin() );
  CHECK( +1 == incident.heavyParticle().parity() );
  outgoing = chunk[2].outgoingParticlePair().value();
  CHECK( id::ParticleID::proton() == outgoing.lightParticle().identifier() );
  CHECK( 1 == outgoing.lightParticle().charge() );
  CHECK( .9986235 * neutron_mass == outgoing.lightParticle().mass() );
  CHECK( 0.5 == outgoing.lightParticle().spin() );
  CHECK( +1 == outgoing.lightParticle().parity() );
  CHECK( id::ParticleID( "S35" ) == outgoing.heavyParticle().identifier() );
  CHECK( 16 == outgoing.heavyParticle().charge() );
  CHECK( 34.66863 * neutron_mass == outgoing.heavyParticle().mass() );
  CHECK( 1.5 == outgoing.heavyParticle().spin() );
  CHECK( +1 == outgoing.heavyParticle().parity() );
  CHECK( false == chunk[2].isIncidentChannel() );
  CHECK( 615220 == chunk[2].qValue() );
  CHECK( std::nullopt == chunk[2].boundaryCondition() );
  CHECK( std::nullopt == chunk[0].background() );
  CHECK_THAT( 4.82222, WithinRel( std::get<double>( chunk[2].channelRadii().penetrabilityRadius() ) ) );
  CHECK( std::nullopt == chunk[2].channelRadii().shiftFactorRadius() );
  CHECK_THAT( 3.66798, WithinRel( std::get<double>( chunk[2].channelRadii().phaseShiftRadius().value() ) ) );
  CHECK( resonances::Kinematics::NonRelativistic == chunk[2].kinematicsType() );
}

void verifyChunkWithBackground( const std::vector< resonances::Channel >& chunk ) {

  CHECK( 2 == chunk.size() );

  CHECK( id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2+}" ) == chunk[0].identifier() );
  auto incident = chunk[0].incidentParticlePair();
  CHECK( id::ParticleID::neutron() == incident.lightParticle().identifier() );
  CHECK( 0 == incident.lightParticle().charge() );
  CHECK( neutron_mass == incident.lightParticle().mass() );
  CHECK( 0.5 == incident.lightParticle().spin() );
  CHECK( +1 == incident.lightParticle().parity() );
  CHECK( id::ParticleID( "Sr88" ) == incident.heavyParticle().identifier() );
  CHECK( 38 == incident.heavyParticle().charge() );
  CHECK( 87.15046 * neutron_mass == incident.heavyParticle().mass() );
  CHECK( 0 == incident.heavyParticle().spin() );
  CHECK( +1 == incident.heavyParticle().parity() );
  auto outgoing = chunk[0].outgoingParticlePair().value();
  CHECK( id::ParticleID::photon() == outgoing.lightParticle().identifier() );
  CHECK( 0 == outgoing.lightParticle().charge() );
  CHECK( 0 == outgoing.lightParticle().mass() );
  CHECK( 1 == outgoing.lightParticle().spin() );
  CHECK( +1 == outgoing.lightParticle().parity() );
  CHECK( id::ParticleID( "Sr89[all]" ) == outgoing.heavyParticle().identifier() );
  CHECK( 38 == outgoing.heavyParticle().charge() );
  CHECK( 88.15046 * neutron_mass == outgoing.heavyParticle().mass() );
  CHECK( 0 == outgoing.heavyParticle().spin() );
  CHECK( +1 == outgoing.heavyParticle().parity() );
  CHECK( false == chunk[0].isIncidentChannel() );
  CHECK( 0 == chunk[0].qValue() );
  CHECK( std::nullopt == chunk[0].boundaryCondition() );
  CHECK( std::nullopt == chunk[0].background() );
  CHECK_THAT( 0., WithinRel( std::get<double>( chunk[0].channelRadii().penetrabilityRadius() ) ) );
  CHECK( std::nullopt == chunk[0].channelRadii().shiftFactorRadius() );
  CHECK_THAT( 0., WithinRel( std::get<double>( chunk[0].channelRadii().phaseShiftRadius().value() ) ) );
  CHECK( resonances::Kinematics::NonRelativistic == chunk[0].kinematicsType() );

  CHECK( id::ChannelID( "n,Sr88->n,Sr88{0,1/2,1/2+}" ) == chunk[1].identifier() );
  incident = chunk[1].incidentParticlePair();
  CHECK( id::ParticleID::neutron() == incident.lightParticle().identifier() );
  CHECK( 0 == incident.lightParticle().charge() );
  CHECK( neutron_mass == incident.lightParticle().mass() );
  CHECK( 0.5 == incident.lightParticle().spin() );
  CHECK( +1 == incident.lightParticle().parity() );
  CHECK( id::ParticleID( "Sr88" ) == incident.heavyParticle().identifier() );
  CHECK( 38 == incident.heavyParticle().charge() );
  CHECK( 87.15046 * neutron_mass == incident.heavyParticle().mass() );
  CHECK( 0 == incident.heavyParticle().spin() );
  CHECK( +1 == incident.heavyParticle().parity() );
  outgoing = chunk[1].outgoingParticlePair().value();
  CHECK( id::ParticleID::neutron() == outgoing.lightParticle().identifier() );
  CHECK( 0 == outgoing.lightParticle().charge() );
  CHECK( neutron_mass == outgoing.lightParticle().mass() );
  CHECK( 0.5 == outgoing.lightParticle().spin() );
  CHECK( +1 == outgoing.lightParticle().parity() );
  CHECK( id::ParticleID( "Sr88" ) == outgoing.heavyParticle().identifier() );
  CHECK( 38 == outgoing.heavyParticle().charge() );
  CHECK( 87.15046 * neutron_mass == outgoing.heavyParticle().mass() );
  CHECK( 0 == outgoing.heavyParticle().spin() );
  CHECK( +1 == outgoing.heavyParticle().parity() );
  CHECK( true == chunk[1].isIncidentChannel() );
  CHECK( 0 == chunk[1].qValue() );
  CHECK( std::nullopt == chunk[1].boundaryCondition() );
  CHECK_THAT( 7.1, WithinRel( std::get<double>( chunk[1].channelRadii().penetrabilityRadius() ) ) );
  CHECK( std::nullopt == chunk[1].channelRadii().shiftFactorRadius() );
  CHECK_THAT( 6.8, WithinRel( std::get<double>( chunk[1].channelRadii().phaseShiftRadius().value() ) ) );
  CHECK( resonances::Kinematics::NonRelativistic == chunk[1].kinematicsType() );
  CHECK( std::nullopt != chunk[1].background() );
  auto background = std::get< resonances::SammyBackground >( chunk[1].background().value() );
  CHECK_THAT( -0.043, WithinRel( background.polynomialCoefficients()[0] ) );
  CHECK_THAT( 2.8e-8, WithinRel( background.polynomialCoefficients()[1] ) );
  CHECK_THAT( 0.    , WithinRel( background.polynomialCoefficients()[2] ) );
  CHECK_THAT( 0.01  , WithinRel( background.logarithmicCoefficients()[0] ) );
  CHECK_THAT( 0.    , WithinRel( background.logarithmicCoefficients()[1] ) );
  CHECK_THAT( 0.    , WithinRel( background.lowerSingularity() ) );
  CHECK_THAT( 9.55e5, WithinRel( background.upperSingularity() ) );
}