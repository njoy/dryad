// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/gnds/pops/createParticleDatabase.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createParticleDatabase" ) {

  GIVEN( "GNDS energy node" ) {

    pugi::xml_document document;
    document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node suite = document.child( "reactionSuite" );
    pugi::xml_node pops = suite.child( "PoPs" );

    std::vector< id::ParticleID > particles = {

      id::ParticleID( "g" ),         id::ParticleID( "n" ),         id::ParticleID( "p" ),
      id::ParticleID( "d" ),         id::ParticleID( "t" ),         id::ParticleID( "h" ),
      id::ParticleID( "a" ),         id::ParticleID( "Kr84[all]" ), id::ParticleID( "Kr85[all]" ),
      id::ParticleID( "Kr86[all]" ), id::ParticleID( "Rb86[all]" ), id::ParticleID( "Rb87[all]" ),
      id::ParticleID( "Rb88[all]" ), id::ParticleID( "Sr86[all]" ), id::ParticleID( "Sr87[all]" ),
      id::ParticleID( "Sr88" ),      id::ParticleID( "Sr88_e1" ),   id::ParticleID( "Sr88_e2" )  ,
      id::ParticleID( "Sr88_e3" ),   id::ParticleID( "Sr88_e4" ),   id::ParticleID( "Sr88_e5" ),
      id::ParticleID( "Sr88_e6" ),   id::ParticleID( "Sr88_e7" ),   id::ParticleID( "Sr88_e8" ),
      id::ParticleID( "Sr88_e9" ),   id::ParticleID( "Sr88_e10" ),  id::ParticleID( "Sr88_e11" ),
      id::ParticleID( "Sr88_e12" ),  id::ParticleID( "Sr88_e13" ),  id::ParticleID( "Sr88_e14" ),
      id::ParticleID( "Sr88_e15" ),  id::ParticleID( "Sr88_e16" ),  id::ParticleID( "Sr88_e17" ),
      id::ParticleID( "Sr88_e18" ),  id::ParticleID( "Sr88_e19" ),  id::ParticleID( "Sr88_e20" ),
      id::ParticleID( "Sr88_e21" ),  id::ParticleID( "Sr88_e22" ),  id::ParticleID( "Sr88[continuum]" ),
      id::ParticleID( "Sr88[all]" ), id::ParticleID( "Sr89[all]" )
    };

    WHEN( "a single pops node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::pops::createParticleDatabase( pops, "eval" );

        CHECK( 45 == chunk.numberParticles() );

        CHECK( true == chunk.hasParticle( id::ParticleID( "g" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "n" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "p" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "H1" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "H2" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "H3" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "He3" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "He4" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Kr84" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Kr85" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Kr86" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Rb86" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Rb87" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Rb88" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr86" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr87" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e1" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e2" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e3" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e4" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e5" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e6" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e7" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e8" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e9" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e10" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e11" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e12" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e13" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e14" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e15" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e16" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e17" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e18" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e19" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e20" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e21" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e22" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr89" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "H" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "He" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Kr" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Rb" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr" ) ) );

        // Sr88 has a mass node in the GNDS file, excited states do not
        decltype(auto) sr88 = chunk.particle( id::ParticleID( "Sr88" ) );
        CHECK_THAT( 87.9051474067, WithinRel( sr88.mass().value() ) );
        CHECK_THAT( 0., WithinRel( sr88.energy().value() ) );
        CHECK(  0 == sr88.spin() );
        CHECK( +1 == sr88.parity() );
        CHECK( std::nullopt == sr88.nuclearMass() );
        CHECK( std::nullopt == sr88.massUncertainty() );
        CHECK( std::nullopt == sr88.nuclearMassUncertainty() );
        CHECK( std::nullopt == sr88.energyUncertainty() );

        decltype(auto) sr88_e1 = chunk.particle( id::ParticleID( "Sr88_e1" ) );
        CHECK_THAT( 87.9051474067, WithinRel( sr88_e1.mass().value() ) );
        CHECK_THAT( 1.8361e6, WithinRel( sr88_e1.energy().value() ) );
        CHECK( std::nullopt == sr88_e1.spin() );
        CHECK( std::nullopt == sr88_e1.parity() );
        CHECK( std::nullopt == sr88_e1.nuclearMass() );
        CHECK( std::nullopt == sr88_e1.massUncertainty() );
        CHECK( std::nullopt == sr88_e1.nuclearMassUncertainty() );
        CHECK( std::nullopt == sr88_e1.energyUncertainty() );
      } // THEN
    } // WHEN

    WHEN( "a single pops node is given along with a list of identifiers" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::pops::createParticleDatabase( pops, particles, "eval" );

        CHECK( 41 == chunk.numberParticles() );

        CHECK( true == chunk.hasParticle( id::ParticleID( "g" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "n" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "p" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "d" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "t" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "h" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "a" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Kr84[all]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Kr85[all]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Kr86[all]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Rb86[all]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Rb87[all]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Rb88[all]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr86[all]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr87[all]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e1" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e2" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e3" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e4" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e5" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e6" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e7" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e8" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e9" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e10" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e11" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e12" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e13" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e14" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e15" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e16" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e17" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e18" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e19" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e20" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e21" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88_e22" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88[continuum]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr88[all]" ) ) );
        CHECK( true == chunk.hasParticle( id::ParticleID( "Sr89[all]" ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
