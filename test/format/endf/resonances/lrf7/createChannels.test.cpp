// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/resonances/lrf7/createChannels.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const std::vector< Channel >& );

SCENARIO( "createChannels" ) {

  GIVEN( "ENDF MF2 MT151 sections" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >(
                        section.isotopes().front().resonanceRanges().front().parameters() );
    auto channels = parameters.spinGroups().front().channels();

    WHEN( "a single parsed scattering radius from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        std::vector< id::ReactionID > reactions = {

          id::ReactionID( "n,Cl35->g,Cl36[all]" ),
          id::ReactionID( "n,Cl35->n,Cl35" ),
          id::ReactionID( "n,Cl35->p,S35" )
        };
        std::vector< std::optional< resonances::ParticlePair > > pairs = {

          resonances::ParticlePair
          { resonances::Particle( id::ParticleID::photon(), 0, 1, +1 ),
            resonances::Particle( id::ParticleID( "Cl36[all]" ),
                                  35.65932 * constants::neutron_mass, 0, +1 ) },
          resonances::ParticlePair
          { resonances::Particle( id::ParticleID::neutron(), constants::neutron_mass, 0.5, +1 ),
            resonances::Particle( id::ParticleID( "Cl35" ),
                                  34.66845 * constants::neutron_mass, 1.5, +1 ) },
          resonances::ParticlePair
          { resonances::Particle( id::ParticleID::proton(), .9986235 * constants::neutron_mass, 0.5, +1 ),
            resonances::Particle( id::ParticleID( "S35" ),
                                  34.66863 * constants::neutron_mass, 1.5, +1 ) }
        };
        ParticlePair incident = pairs[1].value();
        std::vector< double > qvalues = { 0, 0, 615220 };
        bool boundaries = false;

        auto chunk = format::endf::resonances::lrf7::createChannels(
                       incident, pairs, reactions, qvalues, boundaries, channels );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::vector< Channel >& chunk ) {

  CHECK( 3 == chunk.size() );

  CHECK( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ) == chunk[0].identifier() );
  auto incident = chunk[0].incidentParticlePair();
  CHECK( id::ParticleID::neutron() == incident.particle().identifier() );
  CHECK( 0 == incident.particle().charge() );
  CHECK( constants::neutron_mass == incident.particle().mass() );
  CHECK( 0.5 == incident.particle().spin() );
  CHECK( +1 == incident.particle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == incident.residual().identifier() );
  CHECK( 17 == incident.residual().charge() );
  CHECK( 34.66845 * constants::neutron_mass == incident.residual().mass() );
  CHECK( 1.5 == incident.residual().spin() );
  CHECK( +1 == incident.residual().parity() );
  auto outgoing = chunk[0].outgoingParticlePair().value();
  CHECK( id::ParticleID::photon() == outgoing.particle().identifier() );
  CHECK( 0 == outgoing.particle().charge() );
  CHECK( 0 == outgoing.particle().mass() );
  CHECK( 1 == outgoing.particle().spin() );
  CHECK( +1 == outgoing.particle().parity() );
  CHECK( id::ParticleID( "Cl36[all]" ) == outgoing.residual().identifier() );
  CHECK( 17 == outgoing.residual().charge() );
  CHECK( 35.65932 * constants::neutron_mass == outgoing.residual().mass() );
  CHECK( 0 == outgoing.residual().spin() );
  CHECK( +1 == outgoing.residual().parity() );
  CHECK( false == chunk[0].isIncidentChannel() );
  CHECK( 0 == chunk[0].qValue() );
  CHECK( std::nullopt == chunk[0].boundaryCondition() );
  CHECK( resonances::ChannelRadii( 0., 0. ) == chunk[0].channelRadii() );

  CHECK( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) == chunk[1].identifier() );
  incident = chunk[1].incidentParticlePair();
  CHECK( id::ParticleID::neutron() == incident.particle().identifier() );
  CHECK( 0 == incident.particle().charge() );
  CHECK( constants::neutron_mass == incident.particle().mass() );
  CHECK( 0.5 == incident.particle().spin() );
  CHECK( +1 == incident.particle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == incident.residual().identifier() );
  CHECK( 17 == incident.residual().charge() );
  CHECK( 34.66845 * constants::neutron_mass == incident.residual().mass() );
  CHECK( 1.5 == incident.residual().spin() );
  CHECK( +1 == incident.residual().parity() );
  outgoing = chunk[1].outgoingParticlePair().value();
  CHECK( id::ParticleID::neutron() == outgoing.particle().identifier() );
  CHECK( 0 == outgoing.particle().charge() );
  CHECK( constants::neutron_mass == outgoing.particle().mass() );
  CHECK( 0.5 == outgoing.particle().spin() );
  CHECK( +1 == outgoing.particle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == outgoing.residual().identifier() );
  CHECK( 17 == outgoing.residual().charge() );
  CHECK( 34.66845 * constants::neutron_mass == outgoing.residual().mass() );
  CHECK( 1.5 == outgoing.residual().spin() );
  CHECK( +1 == outgoing.residual().parity() );
  CHECK( true == chunk[1].isIncidentChannel() );
  CHECK( 0 == chunk[1].qValue() );
  CHECK( std::nullopt == chunk[1].boundaryCondition() );
  CHECK( resonances::ChannelRadii( 3.66798, 4.82222 ) == chunk[1].channelRadii() );

  CHECK( id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) == chunk[2].identifier() );
  incident = chunk[2].incidentParticlePair();
  CHECK( id::ParticleID::neutron() == incident.particle().identifier() );
  CHECK( 0 == incident.particle().charge() );
  CHECK( constants::neutron_mass == incident.particle().mass() );
  CHECK( 0.5 == incident.particle().spin() );
  CHECK( +1 == incident.particle().parity() );
  CHECK( id::ParticleID( "Cl35" ) == incident.residual().identifier() );
  CHECK( 17 == incident.residual().charge() );
  CHECK( 34.66845 * constants::neutron_mass == incident.residual().mass() );
  CHECK( 1.5 == incident.residual().spin() );
  CHECK( +1 == incident.residual().parity() );
  outgoing = chunk[2].outgoingParticlePair().value();
  CHECK( id::ParticleID::proton() == outgoing.particle().identifier() );
  CHECK( 1 == outgoing.particle().charge() );
  CHECK( .9986235 * constants::neutron_mass == outgoing.particle().mass() );
  CHECK( 0.5 == outgoing.particle().spin() );
  CHECK( +1 == outgoing.particle().parity() );
  CHECK( id::ParticleID( "S35" ) == outgoing.residual().identifier() );
  CHECK( 16 == outgoing.residual().charge() );
  CHECK( 34.66863 * constants::neutron_mass == outgoing.residual().mass() );
  CHECK( 1.5 == outgoing.residual().spin() );
  CHECK( +1 == outgoing.residual().parity() );
  CHECK( false == chunk[2].isIncidentChannel() );
  CHECK( 615220 == chunk[2].qValue() );
  CHECK( std::nullopt == chunk[2].boundaryCondition() );
  CHECK( resonances::ChannelRadii( 3.66798, 4.82222 ) == chunk[2].channelRadii() );
}
