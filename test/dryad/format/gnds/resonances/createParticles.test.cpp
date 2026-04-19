// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/resonances/createParticles.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const ParticleDatabase& );

SCENARIO( "createParticles" ) {

  GIVEN( "a list of identifiers" ) {

    pugi::xml_document document;
    document.load_file( "n-013_Al_027.endf.gnds.xml" );
    pugi::xml_node pops = document.child( "reactionSuite" ).child( "PoPs" );

    WHEN( "a global and local particle database node is given" ) {

      THEN( "it can be converted" ) {

        std::vector< id::ParticleID > identifiers = {

          id::ParticleID( "g" ),
          id::ParticleID( "n" ),
          id::ParticleID( "Al27" ),
          id::ParticleID( "Al28[all]" )
        };
        ParticleDatabase global = format::gnds::pops::createParticleDatabase( pops, identifiers, "eval" );
        ParticleDatabase local; // no local PoPs

        auto chunk = format::gnds::resonances::createParticles( global, local, identifiers );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const ParticleDatabase& chunk ) {

  CHECK( 4 == chunk.numberParticles() );
}
