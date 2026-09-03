// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/pops/insertParticle.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunkGaugeBoson();
std::string chunkLepton();
std::string chunkBaryon();
std::string chunkNuclide();
std::string chunkNuclideWithExcitedState();

SCENARIO( "insertParticle" ) {

  GIVEN( "a parent node and a set of particles" ) {

    gnds::write::Options options;

    THEN( "a gauge boson can be inserted" ) {

      pugi::xml_document parent;
      auto photon = Particle::defaultParticle( id::ParticleID::photon() );
      auto node = gnds::write::pops::insertParticle( parent, options, "gaugeBoson", photon );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkGaugeBoson() );
    } // THEN

    THEN( "a lepton can be inserted" ) {

      pugi::xml_document parent;
      auto electron = Particle::defaultParticle( id::ParticleID::electron() );
      auto node = gnds::write::pops::insertParticle( parent, options, "lepton", electron );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkLepton() );
    } // THEN

    THEN( "a baryon can be inserted" ) {

      pugi::xml_document parent;
      auto neutron = Particle::defaultParticle( id::ParticleID::neutron() );
      auto node = gnds::write::pops::insertParticle( parent, options, "baryon", neutron );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkBaryon() );
    } // THEN

    THEN( "a nuclide can be inserted" ) {

      pugi::xml_document parent;
      auto u235 = Particle::defaultParticle( id::ParticleID( "U235" ) );
      auto node = gnds::write::pops::insertParticle( parent, options, "nuclide", u235 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkNuclide() );
    } // THEN

    THEN( "an excited state nuclide can be inserted" ) {

      pugi::xml_document parent;
      auto u235_e1 = Particle::defaultParticle( id::ParticleID( "U235_e1" ) );
      auto node = gnds::write::pops::insertParticle( parent, options, "nuclide", u235_e1 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkNuclideWithExcitedState() );
    } // THEN

    THEN( "an invalid node name throws" ) {

      pugi::xml_document parent;
      auto u235 = Particle::defaultParticle( id::ParticleID( "U235" ) );
      CHECK_THROWS( gnds::write::pops::insertParticle( parent, options, "invalid", u235 ) );
      CHECK_THROWS( gnds::write::pops::insertParticle( parent, options, "atom", u235 ) );
      CHECK_THROWS( gnds::write::pops::insertParticle( parent, options, "blabla", u235 ) );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunkGaugeBoson() {

  return "<gaugeBoson id=\"g\">\n"
         "  <mass>\n"
         "    <double label=\"eval\" value=\"0\" unit=\"amu\" />\n"
         "  </mass>\n"
         "  <spin>\n"
         "    <fraction label=\"eval\" value=\"1\" unit=\"hbar\" />\n"
         "  </spin>\n"
         "  <parity>\n"
         "    <integer label=\"eval\" value=\"1\" />\n"
         "  </parity>\n"
         "  <charge>\n"
         "    <integer label=\"eval\" value=\"0\" unit=\"e\" />\n"
         "  </charge>\n"
         "</gaugeBoson>\n";
}

std::string chunkLepton() {

  return "<lepton id=\"e-\">\n"
         "  <mass>\n"
         "    <double label=\"eval\" value=\"0.000548579909\" unit=\"amu\" />\n"
         "  </mass>\n"
         "  <spin>\n"
         "    <fraction label=\"eval\" value=\"1/2\" unit=\"hbar\" />\n"
         "  </spin>\n"
         "  <parity>\n"
         "    <integer label=\"eval\" value=\"1\" />\n"
         "  </parity>\n"
         "  <charge>\n"
         "    <integer label=\"eval\" value=\"-1\" unit=\"e\" />\n"
         "  </charge>\n"
         "</lepton>\n";
}

std::string chunkBaryon() {

  return "<baryon id=\"n\">\n"
         "  <mass>\n"
         "    <double label=\"eval\" value=\"1.008664916\" unit=\"amu\" />\n"
         "  </mass>\n"
         "  <spin>\n"
         "    <fraction label=\"eval\" value=\"1/2\" unit=\"hbar\" />\n"
         "  </spin>\n"
         "  <parity>\n"
         "    <integer label=\"eval\" value=\"1\" />\n"
         "  </parity>\n"
         "  <charge>\n"
         "    <integer label=\"eval\" value=\"0\" unit=\"e\" />\n"
         "  </charge>\n"
         "</baryon>\n";
}

std::string chunkNuclide() {

  return "<nuclide id=\"U235\">\n"
         "  <mass>\n"
         "    <double label=\"eval\" value=\"235.0439281\" unit=\"amu\" />\n"
         "  </mass>\n"
         "  <charge>\n"
         "    <integer label=\"eval\" value=\"0\" unit=\"e\" />\n"
         "  </charge>\n"
         "  <nucleus id=\"u235\" index=\"0\">\n"
         "    <spin>\n"
         "      <fraction label=\"eval\" value=\"7/2\" unit=\"hbar\" />\n"
         "    </spin>\n"
         "    <parity>\n"
         "      <integer label=\"eval\" value=\"-1\" />\n"
         "    </parity>\n"
         "    <charge>\n"
         "      <integer label=\"eval\" value=\"92\" unit=\"e\" />\n"
         "    </charge>\n"
         "    <energy>\n"
         "      <double label=\"eval\" value=\"0\" unit=\"eV\" />\n"
         "    </energy>\n"
         "  </nucleus>\n"
         "</nuclide>\n";
}

std::string chunkNuclideWithExcitedState() {

  return "<nuclide id=\"U235_e1\">\n"
         "  <mass>\n"
         "    <double label=\"eval\" value=\"235.0439281\" unit=\"amu\" />\n"
         "  </mass>\n"
         "  <charge>\n"
         "    <integer label=\"eval\" value=\"0\" unit=\"e\" />\n"
         "  </charge>\n"
         "  <nucleus id=\"u235_e1\" index=\"1\">\n"
         "    <spin>\n"
         "      <fraction label=\"eval\" value=\"1/2\" unit=\"hbar\" />\n"
         "    </spin>\n"
         "    <parity>\n"
         "      <integer label=\"eval\" value=\"1\" />\n"
         "    </parity>\n"
         "    <charge>\n"
         "      <integer label=\"eval\" value=\"92\" unit=\"e\" />\n"
         "    </charge>\n"
         "    <energy>\n"
         "      <double label=\"eval\" value=\"76\" unit=\"eV\" />\n"
         "    </energy>\n"
         "  </nucleus>\n"
         "</nuclide>\n";
}
