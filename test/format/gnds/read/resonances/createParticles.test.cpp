// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/resonances/createParticles.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const ParticleDatabase& );

SCENARIO( "createParticles" ) {

  GIVEN( "a list of identifiers" ) {

    pugi::xml_document document;
    document.load_file( "n-013_Al_027.endf.gnds.xml" );
    pugi::xml_node global_pops = document.child( "reactionSuite" ).child( "PoPs" );
    pugi::xml_node local_pops = document.child( "reactionSuite" ).child( "resonances" ).
                                         child( "resolved" ).child( "RMatrix" ).
                                         child( "PoPs" );

    WHEN( "a global and local particle database node is given" ) {

      THEN( "it can be converted" ) {

        std::vector< id::ParticleID > identifiers = {

          id::ParticleID( "g" ),
          id::ParticleID( "n" ),
          id::ParticleID( "Al27" ),
          id::ParticleID( "Al28[all]" )
        };
        ParticleDatabase global = gnds::read::pops::createParticleDatabase( global_pops, identifiers, "eval" );
        ParticleDatabase local = gnds::read::pops::createParticleDatabase( local_pops, identifiers, "eval" );

        auto chunk = gnds::read::resonances::createParticles( global, local, identifiers );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const ParticleDatabase& chunk ) {

  CHECK( 4 == chunk.numberParticles() );
}
