// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/resonances/rmatrix/createResonanceReaction.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunkWithoutAdditionalInformation( const format::gnds::resonances::rmatrix::ResonanceReaction& );
void verifyChunkWithAdditionalInformation( const format::gnds::resonances::rmatrix::ResonanceReaction& );

SCENARIO( "createResonanceReaction" ) {

  GIVEN( "GNDS resonance reaction node without additional information" ) {

    pugi::xml_document document;
    document.load_file( "n-013_Al_027.endf.gnds.xml" );
    pugi::xml_node reaction = document.child( "reactionSuite" ).child( "resonances" ).
                                       child( "resolved" ).child( "RMatrix" ).
                                       child( "resonanceReactions" ).child( "resonanceReaction" );

    WHEN( "a resonance reaction node is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Al27" );
        ChannelRadii radii( 4.3226 );
        std::string style = "eval";

        auto chunk = format::gnds::resonances::rmatrix::createResonanceReaction( projectile, target,
                                                                                 reaction, radii, style );

        verifyChunkWithoutAdditionalInformation( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS resonance reaction node with additional information" ) {

    pugi::xml_document document;
    document.load_file( "n-017_Cl_035.endf.gnds.xml" );
    pugi::xml_node reaction = document.child( "reactionSuite" ).child( "resonances" ).
                                       child( "resolved" ).child( "RMatrix" ).
                                       child( "resonanceReactions" ).
                                       find_child_by_attribute( "resonanceReaction",
                                                                "label", "H1 + S35" );

    WHEN( "a resonance reaction node is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "Cl35" );
        ChannelRadii radii( 4.82222 );
        std::string style = "eval";

        auto chunk = format::gnds::resonances::rmatrix::createResonanceReaction( projectile, target,
                                                                                 reaction, radii, style );

        verifyChunkWithAdditionalInformation( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunkWithoutAdditionalInformation( const format::gnds::resonances::rmatrix::ResonanceReaction& chunk ) {

  CHECK( id::ReactionID( "n,Al27->g(t)" ) == std::get< 0 >( chunk ) );
  CHECK_THAT( 7725200, WithinRel( std::get< 1 >( chunk ) ) );
  CHECK( ChannelRadii( 4.3226 ) == std::get< 2 >( chunk ) );
}

void verifyChunkWithAdditionalInformation( const format::gnds::resonances::rmatrix::ResonanceReaction& chunk ) {

  CHECK( id::ReactionID( "n,Cl35->p(0)" ) == std::get< 0 >( chunk ) );
  CHECK_THAT( 615220, WithinRel( std::get< 1 >( chunk ) ) );
  CHECK( ChannelRadii( 4.82222, 4.88875 ) == std::get< 2 >( chunk ) );
}
