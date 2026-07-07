// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/collectParticleIdentifiers.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/createReactions.hpp"

// convenience typedefs
using namespace njoy::format;
using namespace njoy::dryad;

SCENARIO( "collectParticleIdentifiers" ) {

  GIVEN( "reactions" ) {

    WHEN( "a vector of Reaction instances is given" ) {

      pugi::xml_document document;
      document.load_file( "n-038_Sr_088.endf.gnds.xml" );
      pugi::xml_node suite = document.child( "reactionSuite" );

      id::ParticleID projectile( "n" );
      id::ParticleID target( "Sr88" );
      std::vector< Reaction > reactions = gnds::read::createReactions( projectile, target, suite, false );

      THEN( "the particle identifiers can be collected" ) {

        auto chunk = collectParticleIdentifiers( reactions );

        CHECK( 41 == chunk.size() );
        CHECK( id::ParticleID( "g" )                == chunk[0] );
        CHECK( id::ParticleID( "n" )                == chunk[1] );
        CHECK( id::ParticleID( "p" )                == chunk[2] );
        CHECK( id::ParticleID( "d" )                == chunk[3] );
        CHECK( id::ParticleID( "t" )                == chunk[4] );
        CHECK( id::ParticleID( "h" )                == chunk[5] );
        CHECK( id::ParticleID( "a" )                == chunk[6] );
        CHECK( id::ParticleID( "Kr84[all]" )        == chunk[7] );
        CHECK( id::ParticleID( "Kr85[all]" )        == chunk[8] );
        CHECK( id::ParticleID( "Kr86[all]" )        == chunk[9] );
        CHECK( id::ParticleID( "Rb86[all]" )        == chunk[10] );
        CHECK( id::ParticleID( "Rb87[all]" )        == chunk[11] );
        CHECK( id::ParticleID( "Rb88[all]" )        == chunk[12] );
        CHECK( id::ParticleID( "Sr86[all]" )        == chunk[13] );
        CHECK( id::ParticleID( "Sr87[all]" )        == chunk[14] );
        CHECK( id::ParticleID( "Sr88" )             == chunk[15] );
        CHECK( id::ParticleID( "Sr88_e1" )          == chunk[16] );
        CHECK( id::ParticleID( "Sr88_e2" )          == chunk[17] );
        CHECK( id::ParticleID( "Sr88_e3" )          == chunk[18] );
        CHECK( id::ParticleID( "Sr88_e4" )          == chunk[19] );
        CHECK( id::ParticleID( "Sr88_e5" )          == chunk[20] );
        CHECK( id::ParticleID( "Sr88_e6" )          == chunk[21] );
        CHECK( id::ParticleID( "Sr88_e7" )          == chunk[22] );
        CHECK( id::ParticleID( "Sr88_e8" )          == chunk[23] );
        CHECK( id::ParticleID( "Sr88_e9" )          == chunk[24] );
        CHECK( id::ParticleID( "Sr88_e10" )         == chunk[25] );
        CHECK( id::ParticleID( "Sr88_e11" )         == chunk[26] );
        CHECK( id::ParticleID( "Sr88_e12" )         == chunk[27] );
        CHECK( id::ParticleID( "Sr88_e13" )         == chunk[28] );
        CHECK( id::ParticleID( "Sr88_e14" )         == chunk[29] );
        CHECK( id::ParticleID( "Sr88_e15" )         == chunk[30] );
        CHECK( id::ParticleID( "Sr88_e16" )         == chunk[31] );
        CHECK( id::ParticleID( "Sr88_e17" )         == chunk[32] );
        CHECK( id::ParticleID( "Sr88_e18" )         == chunk[33] );
        CHECK( id::ParticleID( "Sr88_e19" )         == chunk[34] );
        CHECK( id::ParticleID( "Sr88_e20" )         == chunk[35] );
        CHECK( id::ParticleID( "Sr88_e21" )         == chunk[36] );
        CHECK( id::ParticleID( "Sr88_e22" )         == chunk[37] );
        CHECK( id::ParticleID( "Sr88[continuum]" )  == chunk[38] );
        CHECK( id::ParticleID( "Sr88[all]" )        == chunk[39] );
        CHECK( id::ParticleID( "Sr89[all]" )        == chunk[40] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
