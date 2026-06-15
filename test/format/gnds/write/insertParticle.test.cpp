// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertParticle.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include <iostream>
// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "insertParticle" ) {

  GIVEN( "a parent node and a set of particles" ) {

    pugi::xml_document parent;
    gnds::write::Options options;

    auto photon = Particle::defaultParticle( id::ParticleID::photon() );
    auto electron = Particle::defaultParticle( id::ParticleID::electron() );
    auto neutron = Particle::defaultParticle( id::ParticleID::neutron() );
    auto u235 = Particle::defaultParticle( id::ParticleID( "U235" ) );
    auto u235_e1 = Particle::defaultParticle( id::ParticleID( "U235_e1" ) );

    THEN( "a double node can be inserted" ) {

      auto node1 = gnds::write::insertParticle( parent, options, "gaugeBoson", photon );

      auto node2 = gnds::write::insertParticle( parent, options, "lepton", electron );

      auto node3 = gnds::write::insertParticle( parent, options, "baryon", neutron );

      auto node4 = gnds::write::insertParticle( parent, options, "nuclide", u235 );

      auto node5 = gnds::write::insertParticle( parent, options, "nuclide", u235_e1 );

      CHECK_THROWS( gnds::write::insertParticle( parent, options, "nuclide", u235_e1 ) );
    } // THEN
  } // GIVEN
} // SCENARIO
