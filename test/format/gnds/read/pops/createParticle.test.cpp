// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/pops/createParticle.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;
using namespace njoy::dryad;

SCENARIO( "createParticle" ) {

  GIVEN( "GNDS nodes for Particle data" ) {

    pugi::xml_document document;
    document.load_file( "n-038_Sr_088.endf.gnds.xml" );
    pugi::xml_node pops = document.child( "reactionSuite" ).
                                   child( "PoPs" );
    pugi::xml_node boson = pops.child( "gaugeBosons" ).child( "gaugeBoson" );
    pugi::xml_node baryon = pops.child( "baryons" ).child( "baryon" );
    pugi::xml_node element = pops.child( "chemicalElements" ).child( "chemicalElement" );
    pugi::xml_node nuclide = pops.child( "chemicalElements" ).child( "chemicalElement" ).
                                  child( "isotopes" ).child( "isotope" ).
                                  child( "nuclides" ).child( "nuclide" );
    pugi::xml_node nuclid_no_mass = pops.child( "chemicalElements" ).
                                         find_child_by_attribute( "chemicalElement", "symbol", "Kr" ).
                                         child( "isotopes" ).child( "isotope" ).
                                         child( "nuclides" ).child( "nuclide" );

    WHEN( "a single node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::pops::createParticle( boson, "eval" );

        CHECK( id::ParticleID::photon() == chunk.identifier() );
        CHECK_THAT( 0., WithinRel( chunk.mass().value() ) );
        CHECK( 1 == chunk.spin() );
        CHECK( 1 == chunk.parity() );
        CHECK( std::nullopt == chunk.nuclearMass() );
        CHECK( std::nullopt == chunk.energy() );
        CHECK( std::nullopt == chunk.massUncertainty() );
        CHECK( std::nullopt == chunk.nuclearMassUncertainty() );
        CHECK( std::nullopt == chunk.energyUncertainty() );

        chunk = gnds::read::pops::createParticle( baryon, "eval" );

        CHECK( id::ParticleID::neutron() == chunk.identifier() );
        CHECK_THAT( 1.00866491574, WithinRel( chunk.mass().value() ) );
        CHECK( 0.5 == chunk.spin() );
        CHECK( 1 == chunk.parity() );
        CHECK( std::nullopt == chunk.nuclearMass() );
        CHECK( std::nullopt == chunk.energy() );
        CHECK( std::nullopt == chunk.massUncertainty() );
        CHECK( std::nullopt == chunk.nuclearMassUncertainty() );
        CHECK( std::nullopt == chunk.energyUncertainty() );

        chunk = gnds::read::pops::createParticle( nuclide, "eval" );

        CHECK( id::ParticleID( "H1" ) == chunk.identifier() );
        CHECK_THAT( 1.00782503223, WithinRel( chunk.mass().value() ) );
        CHECK( 0.5 == chunk.spin() );
        CHECK( 1 == chunk.parity() );
        CHECK_THAT( 1.00727646662, WithinRel( chunk.nuclearMass().value() ) );
        CHECK( 0. == chunk.energy() );
        CHECK( std::nullopt == chunk.massUncertainty() );
        CHECK( std::nullopt == chunk.nuclearMassUncertainty() );
        CHECK( std::nullopt == chunk.energyUncertainty() );

        chunk = gnds::read::pops::createParticle( nuclid_no_mass, "eval" );

        CHECK( id::ParticleID( "Kr84" ) == chunk.identifier() );
        CHECK( std::nullopt == chunk.mass() );
        CHECK( std::nullopt == chunk.spin() );
        CHECK( std::nullopt == chunk.parity() );
        CHECK( std::nullopt == chunk.nuclearMass() );
        CHECK( 0. == chunk.energy() );
        CHECK( std::nullopt == chunk.massUncertainty() );
        CHECK( std::nullopt == chunk.nuclearMassUncertainty() );
        CHECK( std::nullopt == chunk.energyUncertainty() );

        chunk = gnds::read::pops::createParticle( element, "eval" );

        CHECK( id::ParticleID( "H" ) == chunk.identifier() );
        CHECK( std::nullopt == chunk.mass() );
        CHECK( std::nullopt == chunk.spin() );
        CHECK( std::nullopt == chunk.parity() );
        CHECK( std::nullopt == chunk.nuclearMass() );
        CHECK( std::nullopt == chunk.energy() );
        CHECK( std::nullopt == chunk.massUncertainty() );
        CHECK( std::nullopt == chunk.nuclearMassUncertainty() );
        CHECK( std::nullopt == chunk.energyUncertainty() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
