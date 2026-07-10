// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertParticle.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

SCENARIO( "insertParticle" ) {

  GIVEN( "a parent node and a set of particles" ) {

    pugi::xml_document parent;
    gnds::write::Options options;

    THEN( "a gauge boson can be inserted" ) {

      auto photon = Particle::defaultParticle( id::ParticleID::photon() );
      auto node = gnds::write::insertParticle( parent, options, "gaugeBoson", photon );

      CHECK( 0 == strcmp( "gaugeBoson", node.name() ) );
      CHECK( 0 == strcmp( "g", node.attribute( "id" ).as_string() ) );

      auto mass = node.child( "mass" );
      CHECK( false == mass.empty() );
      auto data = mass.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "0", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "amu", data.attribute( "unit" ).as_string() ) );

      auto spin = node.child( "spin" );
      CHECK( false == spin.empty() );
      data = spin.child( "fraction" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "hbar", data.attribute( "unit" ).as_string() ) );

      auto parity = node.child( "parity" );
      CHECK( false == parity.empty() );
      data = parity.child( "integer" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( true == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1", data.attribute( "value" ).as_string() ) );

      auto charge = node.child( "charge" );
      CHECK( false == charge.empty() );
      data = charge.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "0", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "e", data.attribute( "unit" ).as_string() ) );

      auto energy = node.child( "energy" );
      CHECK( true == energy.empty() );
    } // THEN

    THEN( "a lepton can be inserted" ) {

      auto electron = Particle::defaultParticle( id::ParticleID::electron() );
      auto node = gnds::write::insertParticle( parent, options, "lepton", electron );

      CHECK( 0 == strcmp( "lepton", node.name() ) );
      CHECK( 0 == strcmp( "e-", node.attribute( "id" ).as_string() ) );

      auto mass = node.child( "mass" );
      CHECK( false == mass.empty() );
      auto data = mass.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "0.000548579909", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "amu", data.attribute( "unit" ).as_string() ) );

      auto spin = node.child( "spin" );
      CHECK( false == spin.empty() );
      data = spin.child( "fraction" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1/2", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "hbar", data.attribute( "unit" ).as_string() ) );

      auto parity = node.child( "parity" );
      CHECK( false == parity.empty() );
      data = parity.child( "integer" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( true == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1", data.attribute( "value" ).as_string() ) );

      auto charge = node.child( "charge" );
      CHECK( false == charge.empty() );
      data = charge.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "-1", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "e", data.attribute( "unit" ).as_string() ) );

      auto energy = node.child( "energy" );
      CHECK( true == energy.empty() );
    } // THEN

    THEN( "a baryon can be inserted" ) {

      auto neutron = Particle::defaultParticle( id::ParticleID::neutron() );
      auto node = gnds::write::insertParticle( parent, options, "baryon", neutron );

      CHECK( 0 == strcmp( "baryon", node.name() ) );
      CHECK( 0 == strcmp( "n", node.attribute( "id" ).as_string() ) );

      auto mass = node.child( "mass" );
      CHECK( false == mass.empty() );
      auto data = mass.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1.008664916", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "amu", data.attribute( "unit" ).as_string() ) );

      auto spin = node.child( "spin" );
      CHECK( false == spin.empty() );
      data = spin.child( "fraction" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1/2", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "hbar", data.attribute( "unit" ).as_string() ) );

      auto parity = node.child( "parity" );
      CHECK( false == parity.empty() );
      data = parity.child( "integer" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( true == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1", data.attribute( "value" ).as_string() ) );

      auto charge = node.child( "charge" );
      CHECK( false == charge.empty() );
      data = charge.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "0", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "e", data.attribute( "unit" ).as_string() ) );

      auto energy = node.child( "energy" );
      CHECK( true == energy.empty() );
    } // THEN

    THEN( "a nuclide can be inserted" ) {

      auto u235 = Particle::defaultParticle( id::ParticleID( "U235" ) );
      auto node = gnds::write::insertParticle( parent, options, "nuclide", u235 );

      CHECK( 0 == strcmp( "nuclide", node.name() ) );
      CHECK( 0 == strcmp( "U235", node.attribute( "id" ).as_string() ) );

      auto mass = node.child( "mass" );
      CHECK( false == mass.empty() );
      auto data = mass.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "235.0439281", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "amu", data.attribute( "unit" ).as_string() ) );

      auto charge = node.child( "charge" );
      CHECK( false == charge.empty() );
      data = charge.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "0", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "e", data.attribute( "unit" ).as_string() ) );

      auto nucleus = node.child( "nucleus" );
      CHECK( false == nucleus.empty() );

      auto spin = nucleus.child( "spin" );
      CHECK( false == spin.empty() );
      data = spin.child( "fraction" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "7/2", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "hbar", data.attribute( "unit" ).as_string() ) );

      auto parity = nucleus.child( "parity" );
      CHECK( false == parity.empty() );
      data = parity.child( "integer" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( true == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "-1", data.attribute( "value" ).as_string() ) );

      charge = nucleus.child( "charge" );
      CHECK( false == charge.empty() );
      data = charge.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "92", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "e", data.attribute( "unit" ).as_string() ) );

      auto energy = nucleus.child( "energy" );
      CHECK( false == energy.empty() );
      data = energy.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "0", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "eV", data.attribute( "unit" ).as_string() ) );
    } // THEN

    THEN( "an excited state nuclide can be inserted" ) {

      auto u235_e1 = Particle::defaultParticle( id::ParticleID( "U235_e1" ) );
      auto node = gnds::write::insertParticle( parent, options, "nuclide", u235_e1 );

      CHECK( 0 == strcmp( "nuclide", node.name() ) );
      CHECK( 0 == strcmp( "U235_e1", node.attribute( "id" ).as_string() ) );

      auto mass = node.child( "mass" );
      CHECK( false == mass.empty() );
      auto data = mass.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "235.0439281", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "amu", data.attribute( "unit" ).as_string() ) );

      auto charge = node.child( "charge" );
      CHECK( false == charge.empty() );
      data = charge.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "0", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "e", data.attribute( "unit" ).as_string() ) );

      auto nucleus = node.child( "nucleus" );
      CHECK( false == nucleus.empty() );

      auto spin = nucleus.child( "spin" );
      CHECK( false == spin.empty() );
      data = spin.child( "fraction" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1/2", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "hbar", data.attribute( "unit" ).as_string() ) );

      auto parity = nucleus.child( "parity" );
      CHECK( false == parity.empty() );
      data = parity.child( "integer" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( true == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1", data.attribute( "value" ).as_string() ) );

      charge = nucleus.child( "charge" );
      CHECK( false == charge.empty() );
      data = charge.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "92", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "e", data.attribute( "unit" ).as_string() ) );

      auto energy = nucleus.child( "energy" );
      CHECK( false == energy.empty() );
      data = energy.child( "double" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( false == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "76", data.attribute( "value" ).as_string() ) );
      CHECK( 0 == strcmp( "eV", data.attribute( "unit" ).as_string() ) );
    } // THEN

    THEN( "an invalid node name throws" ) {

      auto u235 = Particle::defaultParticle( id::ParticleID( "U235" ) );
      CHECK_THROWS( gnds::write::insertParticle( parent, options, "invalid", u235 ) );
      CHECK_THROWS( gnds::write::insertParticle( parent, options, "atom", u235 ) );
      CHECK_THROWS( gnds::write::insertParticle( parent, options, "blabla", u235 ) );
    } // THEN
  } // GIVEN
} // SCENARIO
