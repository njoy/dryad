// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/resonances/rmatrix/createResonanceReactions.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const format::gnds::resonances::rmatrix::ResonanceReactions& );
void verifyChunkWithChargedParticles( const format::gnds::resonances::rmatrix::ResonanceReactions& );
void verifyChunkWithFission( const format::gnds::resonances::rmatrix::ResonanceReactions& );

SCENARIO( "createResonanceReactions" ) {

  GIVEN( "GNDS resonance reactions node" ) {

    pugi::xml_document document;
    document.load_file( "n-013_Al_027.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "resonances" ).
                                        child( "resolved" ).child( "RMatrix" ).
                                        child( "resonanceReactions" );

    WHEN( "a resonance reaction node is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Al27" );
        std::vector< Particle > particles = { Particle( id::ParticleID::photon(), 0, 1, +1 ),
                                              Particle( id::ParticleID::neutron(), 1, .5, +1 ),
                                              Particle( id::ParticleID( "Al27" ), 27, 1.5, +1 ),
                                              Particle( id::ParticleID( "Al28[all]" ), 28, 2.5, +1 ) };
        ChannelRadii radii( 4.3226 );
        std::string style = "eval";

        auto chunk = format::gnds::resonances::rmatrix::createResonanceReactions( projectile, target, reactions,
                                                                                  particles, radii, style );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS resonance reactions node with charged particles" ) {

    pugi::xml_document document;
    document.load_file( "n-017_Cl_035.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "resonances" ).
                                        child( "resolved" ).child( "RMatrix" ).
                                        child( "resonanceReactions" );

    WHEN( "a resonance reaction node is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Cl35" );
        std::vector< Particle > particles = { Particle( id::ParticleID::photon(), 0, 1, +1 ),
                                              Particle( id::ParticleID::neutron(), 1, .5, +1 ),
                                              Particle( id::ParticleID::proton(), 1.1, 1, +1 ),
                                              Particle( id::ParticleID( "Cl35" ), 35, 1.5, +1 ),
                                              Particle( id::ParticleID( "Cl36[all]" ), 36, 1.5, +1 ),
                                              Particle( id::ParticleID( "S35" ), 35.1, 2.5, +1 ) };
        ChannelRadii radii( 4.82222 );
        std::string style = "eval";

        auto chunk = format::gnds::resonances::rmatrix::createResonanceReactions( projectile, target, reactions,
                                                                                  particles, radii, style );

        verifyChunkWithChargedParticles( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS resonance reactions node with fission" ) {

    pugi::xml_document document;
    document.load_file( "n-091_Pa_231.endf.gnds.xml" );
    pugi::xml_node reactions = document.child( "reactionSuite" ).child( "resonances" ).
                                        child( "resolved" ).child( "RMatrix" ).
                                        child( "resonanceReactions" );

    WHEN( "a resonance reaction node is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Pa231" );
        std::vector< Particle > particles = { Particle( id::ParticleID::photon(), 0, 1, +1 ),
                                              Particle( id::ParticleID::neutron(), 1, .5, +1 ),
                                              Particle( id::ParticleID( "Pa231" ), 231, 1.5, +1 ),
                                              Particle( id::ParticleID( "Pa232[all]" ), 232, 1.5, +1 ) };
        ChannelRadii radii( 10.4 );
        std::string style = "eval";

        auto chunk = format::gnds::resonances::rmatrix::createResonanceReactions( projectile, target, reactions,
                                                                                  particles, radii, style );

        verifyChunkWithFission( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const format::gnds::resonances::rmatrix::ResonanceReactions& chunk ) {

  CHECK( 2 == chunk.size() );

  auto reaction = chunk.at( "Al28 + photon [inclusive]" );
  CHECK( id::ReactionID( "n,Al27->g(t)" ) == std::get< 0 >( reaction ) );
  CHECK( id::ParticleID::neutron() == std::get< 1 >( reaction ).lightParticle().identifier() );
  CHECK( id::ParticleID( "Al27" ) == std::get< 1 >( reaction ).heavyParticle().identifier() );
  CHECK( id::ParticleID::photon() == std::get< 2 >( reaction )->lightParticle().identifier() );
  CHECK( id::ParticleID( "Al28[all]" ) == std::get< 2 >( reaction )->heavyParticle().identifier() );
  CHECK_THAT( 7725200, WithinRel( std::get< 3 >( reaction ) ) );
  CHECK( ChannelRadii( 4.3226 ) == std::get< 4 >( reaction ) );
  CHECK( std::nullopt == std::get< 5 >( reaction ) );

  reaction = chunk.at( "n + Al27" );
  CHECK( id::ReactionID( "n,Al27->n(0)" ) == std::get< 0 >( reaction ) );
  CHECK( id::ParticleID::neutron() == std::get< 1 >( reaction ).lightParticle().identifier() );
  CHECK( id::ParticleID( "Al27" ) == std::get< 1 >( reaction ).heavyParticle().identifier() );
  CHECK( id::ParticleID::neutron() == std::get< 2 >( reaction )->lightParticle().identifier() );
  CHECK( id::ParticleID( "Al27" ) == std::get< 2 >( reaction )->heavyParticle().identifier() );
  CHECK_THAT( 0, WithinRel( std::get< 3 >( reaction ) ) );
  CHECK( ChannelRadii( 4.3226 ) == std::get< 4 >( reaction ) );
  CHECK( std::nullopt == std::get< 5 >( reaction ) );
}

void verifyChunkWithChargedParticles( const format::gnds::resonances::rmatrix::ResonanceReactions& chunk ) {

  CHECK( 3 == chunk.size() );

  auto reaction = chunk.at( "H1 + S35" );
  CHECK( id::ReactionID( "n,Cl35->p(0)" ) == std::get< 0 >( reaction ) );
  CHECK( id::ParticleID::neutron() == std::get< 1 >( reaction ).lightParticle().identifier() );
  CHECK( id::ParticleID( "Cl35" ) == std::get< 1 >( reaction ).heavyParticle().identifier() );
  CHECK( id::ParticleID::proton() == std::get< 2 >( reaction )->lightParticle().identifier() );
  CHECK( id::ParticleID( "S35" ) == std::get< 2 >( reaction )->heavyParticle().identifier() );
  CHECK_THAT( 615220, WithinRel( std::get< 3 >( reaction ) ) );
  CHECK( ChannelRadii( 4.82222, 4.88875 ) == std::get< 4 >( reaction ) );
  CHECK( std::nullopt == std::get< 5 >( reaction ) );

  reaction = chunk.at( "Cl36 + photon [inclusive]" );
  CHECK( id::ReactionID( "n,Cl35->g(t)" ) == std::get< 0 >( reaction ) );
  CHECK( id::ParticleID::neutron() == std::get< 1 >( reaction ).lightParticle().identifier() );
  CHECK( id::ParticleID( "Cl35" ) == std::get< 1 >( reaction ).heavyParticle().identifier() );
  CHECK( id::ParticleID::photon() == std::get< 2 >( reaction )->lightParticle().identifier() );
  CHECK( id::ParticleID( "Cl36[all]" ) == std::get< 2 >( reaction )->heavyParticle().identifier() );
  CHECK_THAT( 8579907, WithinRel( std::get< 3 >( reaction ) ) );
  CHECK( ChannelRadii( 4.82222 ) == std::get< 4 >( reaction ) );
  CHECK( std::nullopt == std::get< 5 >( reaction ) );

  reaction = chunk.at( "n + Cl35" );
  CHECK( id::ReactionID( "n,Cl35->n(0)" ) == std::get< 0 >( reaction ) );
  CHECK( id::ParticleID::neutron() == std::get< 1 >( reaction ).lightParticle().identifier() );
  CHECK( id::ParticleID( "Cl35" ) == std::get< 1 >( reaction ).heavyParticle().identifier() );
  CHECK( id::ParticleID::neutron() == std::get< 2 >( reaction )->lightParticle().identifier() );
  CHECK( id::ParticleID( "Cl35" ) == std::get< 2 >( reaction )->heavyParticle().identifier() );
  CHECK_THAT( 0, WithinRel( std::get< 3 >( reaction ) ) );
  CHECK( ChannelRadii( 4.82222, 4.88875 ) == std::get< 4 >( reaction ) );
  CHECK( std::nullopt == std::get< 5 >( reaction ) );
}

void verifyChunkWithFission( const format::gnds::resonances::rmatrix::ResonanceReactions& chunk ) {

  CHECK( 3 == chunk.size() );

  auto reaction = chunk.at( "m(E)*n + photon [total fission]" );
  CHECK( id::ReactionID( "n,Pa231->fission(t)" ) == std::get< 0 >( reaction ) );
  CHECK( id::ParticleID::neutron() == std::get< 1 >( reaction ).lightParticle().identifier() );
  CHECK( id::ParticleID( "Pa231" ) == std::get< 1 >( reaction ).heavyParticle().identifier() );
  CHECK( std::nullopt == std::get< 2 >( reaction ) );
  CHECK_THAT( 176518100, WithinRel( std::get< 3 >( reaction ) ) );
  CHECK( ChannelRadii( 10.4 ) == std::get< 4 >( reaction ) );
  CHECK( std::nullopt == std::get< 5 >( reaction ) );

  reaction = chunk.at( "Pa232 + photon [inclusive]" );
  CHECK( id::ReactionID( "n,Pa231->g(t)" ) == std::get< 0 >( reaction ) );
  CHECK( id::ParticleID::neutron() == std::get< 1 >( reaction ).lightParticle().identifier() );
  CHECK( id::ParticleID( "Pa231" ) == std::get< 1 >( reaction ).heavyParticle().identifier() );
  CHECK( id::ParticleID::photon() == std::get< 2 >( reaction )->lightParticle().identifier() );
  CHECK( id::ParticleID( "Pa232[all]" ) == std::get< 2 >( reaction )->heavyParticle().identifier() );
  CHECK_THAT( 5.553e6, WithinRel( std::get< 3 >( reaction ) ) );
  CHECK( ChannelRadii( 10.4 ) == std::get< 4 >( reaction ) );
  CHECK( std::nullopt == std::get< 5 >( reaction ) );

  reaction = chunk.at( "n + Pa231" );
  CHECK( id::ReactionID( "n,Pa231->n(0)" ) == std::get< 0 >( reaction ) );
  CHECK( id::ParticleID::neutron() == std::get< 1 >( reaction ).lightParticle().identifier() );
  CHECK( id::ParticleID( "Pa231" ) == std::get< 1 >( reaction ).heavyParticle().identifier() );
  CHECK( id::ParticleID::neutron() == std::get< 2 >( reaction )->lightParticle().identifier() );
  CHECK( id::ParticleID( "Pa231" ) == std::get< 2 >( reaction )->heavyParticle().identifier() );
  CHECK_THAT( 0, WithinRel( std::get< 3 >( reaction ) ) );
  CHECK( ChannelRadii( 10.4 ) == std::get< 4 >( reaction ) );
  CHECK( std::nullopt == std::get< 5 >( reaction ) );
}
