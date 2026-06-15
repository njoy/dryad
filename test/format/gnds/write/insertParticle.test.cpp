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

parent.print( std::cout );

      auto parity = node.child( "parity" );
      CHECK( false == parity.empty() );
      data = parity.child( "integer" );
      CHECK( false == data.attribute( "label" ).empty() );
      CHECK( false == data.attribute( "value" ).empty() );
      CHECK( true == data.attribute( "unit" ).empty() );
      CHECK( 0 == strcmp( "eval", data.attribute( "label" ).as_string() ) );
      CHECK( 0 == strcmp( "1", data.attribute( "value" ).as_string() ) );

//      auto charge = node.child( "charge" );
//      CHECK( false == charge.empty() );
//      CHECK( 0 == strcmp( "0", charge.attribute( "value" ).as_string() ) );
//      CHECK( 0 == strcmp( "e", charge.attribute( "unit" ).as_string() ) );
//
//      auto energy = node.child( "energy" );
//      CHECK( true == energy.empty() );
    } // THEN

//    THEN( "a lepton can be inserted" ) {
//
//      auto electron = Particle::defaultParticle( id::ParticleID::electron() );
//      auto node = gnds::write::insertParticle( parent, options, "lepton", electron );
//
//      CHECK( 0 == strcmp( "lepton", node.name() ) );
//      CHECK( 0 == strcmp( "e-", node.attribute( "id" ).as_string() ) );
//
//      auto mass = node.child( "mass" );
//      CHECK( false == mass.empty() );
//      CHECK( false == mass.attribute( "value" ).empty() );
//      CHECK( 0 == strcmp( "amu", mass.attribute( "unit" ).as_string() ) );
//
//      auto spin = node.child( "spin" );
//      CHECK( false == spin.empty() );
//      CHECK( 0 == strcmp( "1/2", spin.attribute( "value" ).as_string() ) );
//
//      auto parity = node.child( "parity" );
//      CHECK( false == parity.empty() );
//      CHECK( false == parity.attribute( "value" ).empty() );
//
//      auto charge = node.child( "charge" );
//      CHECK( false == charge.empty() );
//      CHECK( 0 == strcmp( "-1", charge.attribute( "value" ).as_string() ) );
//      CHECK( 0 == strcmp( "e", charge.attribute( "unit" ).as_string() ) );
//
//      auto energy = node.child( "energy" );
//      CHECK( true == energy.empty() );
//    } // THEN
//
//    THEN( "a baryon can be inserted" ) {
//
//      auto neutron = Particle::defaultParticle( id::ParticleID::neutron() );
//      auto node = gnds::write::insertParticle( parent, options, "baryon", neutron );
//
//      CHECK( 0 == strcmp( "baryon", node.name() ) );
//      CHECK( 0 == strcmp( "n", node.attribute( "id" ).as_string() ) );
//
//      auto mass = node.child( "mass" );
//      CHECK( false == mass.empty() );
//      CHECK( false == mass.attribute( "value" ).empty() );
//      CHECK( 0 == strcmp( "amu", mass.attribute( "unit" ).as_string() ) );
//
//      auto spin = node.child( "spin" );
//      CHECK( false == spin.empty() );
//      CHECK( 0 == strcmp( "1/2", spin.attribute( "value" ).as_string() ) );
//
//      auto parity = node.child( "parity" );
//      CHECK( false == parity.empty() );
//      CHECK( 0 == strcmp( "1", parity.attribute( "value" ).as_string() ) );
//
//      auto charge = node.child( "charge" );
//      CHECK( false == charge.empty() );
//      CHECK( 0 == strcmp( "0", charge.attribute( "value" ).as_string() ) );
//      CHECK( 0 == strcmp( "e", charge.attribute( "unit" ).as_string() ) );
//
//      auto energy = node.child( "energy" );
//      CHECK( true == energy.empty() );
//    } // THEN
//
//    THEN( "a nuclide can be inserted" ) {
//
//      auto u235 = Particle::defaultParticle( id::ParticleID( "U235" ) );
//      auto node = gnds::write::insertParticle( parent, options, "nuclide", u235 );
//
//      CHECK( 0 == strcmp( "nuclide", node.name() ) );
//      CHECK( 0 == strcmp( "U235", node.attribute( "id" ).as_string() ) );
//
//      auto mass = node.child( "mass" );
//      CHECK( false == mass.empty() );
//      CHECK( false == mass.attribute( "value" ).empty() );
//      CHECK( 0 == strcmp( "amu", mass.attribute( "unit" ).as_string() ) );
//
//      auto nuclideCharge = node.child( "charge" );
//      CHECK( false == nuclideCharge.empty() );
//      CHECK( 0 == strcmp( "0", nuclideCharge.attribute( "value" ).as_string() ) );
//      CHECK( 0 == strcmp( "e", nuclideCharge.attribute( "unit" ).as_string() ) );
//
//      auto nucleus = node.child( "nucleus" );
//      CHECK( false == nucleus.empty() );
//      CHECK( 0 == strcmp( "u235", nucleus.attribute( "id" ).as_string() ) );
//
//      auto nucleusSpin = nucleus.child( "spin" );
//      CHECK( false == nucleusSpin.empty() );
//      CHECK( false == nucleusSpin.attribute( "value" ).empty() );
//
//      auto nucleusParity = nucleus.child( "parity" );
//      CHECK( false == nucleusParity.empty() );
//      CHECK( false == nucleusParity.attribute( "value" ).empty() );
//
//      auto nucleusCharge = nucleus.child( "charge" );
//      CHECK( false == nucleusCharge.empty() );
//      CHECK( 0 == strcmp( "92", nucleusCharge.attribute( "value" ).as_string() ) );
//      CHECK( 0 == strcmp( "e", nucleusCharge.attribute( "unit" ).as_string() ) );
//
//      auto nucleusEnergy = nucleus.child( "energy" );
//      CHECK( true == nucleusEnergy.empty() );
//    } // THEN
//
//    THEN( "an excited state nuclide can be inserted" ) {
//
//      auto u235_e1 = Particle::defaultParticle( id::ParticleID( "U235_e1" ) );
//      auto node = gnds::write::insertParticle( parent, options, "nuclide", u235_e1 );
//
//      CHECK( 0 == strcmp( "nuclide", node.name() ) );
//      CHECK( 0 == strcmp( "U235_e1", node.attribute( "id" ).as_string() ) );
//
//      auto mass = node.child( "mass" );
//      CHECK( false == mass.empty() );
//
//      auto nuclideCharge = node.child( "charge" );
//      CHECK( false == nuclideCharge.empty() );
//
//      auto nucleus = node.child( "nucleus" );
//      CHECK( false == nucleus.empty() );
//      CHECK( 0 == strcmp( "u235_e1", nucleus.attribute( "id" ).as_string() ) );
//
//      auto nucleusSpin = nucleus.child( "spin" );
//      CHECK( false == nucleusSpin.empty() );
//
//      auto nucleusParity = nucleus.child( "parity" );
//      CHECK( false == nucleusParity.empty() );
//
//      auto nucleusCharge = nucleus.child( "charge" );
//      CHECK( false == nucleusCharge.empty() );
//      CHECK( 0 == strcmp( "92", nucleusCharge.attribute( "value" ).as_string() ) );
//
//      auto nucleusEnergy = nucleus.child( "energy" );
//      CHECK( false == nucleusEnergy.empty() );
//      CHECK( false == nucleusEnergy.attribute( "value" ).empty() );
//      CHECK( 0 == strcmp( "eV", nucleusEnergy.attribute( "unit" ).as_string() ) );
//    } // THEN

    THEN( "an invalid node name throws" ) {

      auto u235 = Particle::defaultParticle( id::ParticleID( "U235" ) );
      CHECK_THROWS( gnds::write::insertParticle( parent, options, "invalid", u235 ) );
      CHECK_THROWS( gnds::write::insertParticle( parent, options, "atom", u235 ) );
      CHECK_THROWS( gnds::write::insertParticle( parent, options, "blabla", u235 ) );
    } // THEN
  } // GIVEN
} // SCENARIO
