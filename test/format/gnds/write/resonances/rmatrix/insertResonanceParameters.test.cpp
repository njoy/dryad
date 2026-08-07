// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/resonances/rmatrix/insertResonanceParameters.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertResonanceParameters" ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto proton = id::ParticleID::proton();
  auto cu63 = id::ParticleID( "Cu63" );
  auto cu64 = id::ParticleID( "Cu64[all]" );

  resonances::ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                        Particle( cu64, 63.389 * njoy::constants::neutron_mass, 0, +1 ) );
  resonances::ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                         Particle( cu63, 62.389 * njoy::constants::neutron_mass, 1.5, -1 ) );

  resonances::ChannelRadii zero_radii( 0., 0. );
  resonances::ChannelRadii radii( 6.7, 6.7 );

  resonances::SpinGroup group( { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ),
                                   neutron_pair, photon_pair, 0., 0, zero_radii },
                                 { id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ),
                                   neutron_pair, neutron_pair, 0., -1, radii },
                                 { id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ),
                                   neutron_pair, neutron_pair, 0., -1, radii } },
                               { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ),
                                   id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ),
                                   id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ) },
                                 { -3.811148e+3, 2.993903e+5 },
                                 { { 1., 2. },
                                   { 1.1, -2.1 },
                                   { 1.2, 2.2 } } },
                               resonances::Formalism::ReichMoore,
                               resonances::BoundaryCondition::ShiftFactor );

  GIVEN( "a parent node and a spin group, using reduced widths" ) {

    gnds::write::Options options;

    THEN( "a resonanceParameters node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertResonanceParameters( parent, options, group, true );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and a spin group, using reduced widths" ) {

    gnds::write::Options options;

    THEN( "a resonanceParameters node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertResonanceParameters( parent, options, group, false );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<resonanceParameters>\n"
         "  <table rows=\"2\" columns=\"4\">\n"
         "    <columnHeaders>\n"
         "      <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <column index=\"1\" name=\"n,Cu63->g,Cu64[all]{0,0,1+} width\" unit=\"eV^1/2\" />\n"
         "      <column index=\"2\" name=\"n,Cu63->n,Cu63{1,1,1+} width\" unit=\"eV^1/2\" />\n"
         "      <column index=\"3\" name=\"n,Cu63->n,Cu63{1,2,1+} width\" unit=\"eV^1/2\" />\n"
         "    </columnHeaders>\n"
         "    <data>\n"
         "      -3811.148 1 1.1 1.2\n"
         "      299390.3 2 -2.1 2.2\n"
         "    </data>\n"
         "  </table>\n"
         "</resonanceParameters>\n";
}

std::string chunk2() {

  return "<resonanceParameters>\n"
         "  <table rows=\"2\" columns=\"4\">\n"
         "    <columnHeaders>\n"
         "      <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <column index=\"1\" name=\"n,Cu63->g,Cu64[all]{0,0,1+} width\" unit=\"eV\" />\n"
         "      <column index=\"2\" name=\"n,Cu63->n,Cu63{1,1,1+} width\" unit=\"eV\" />\n"
         "      <column index=\"3\" name=\"n,Cu63->n,Cu63{1,2,1+} width\" unit=\"eV\" />\n"
         "    </columnHeaders>\n"
         "    <data>\n"
         "      -3811.148 2 0.001717205802 0.002043616822\n"
         "      299390.3 8 -2.697593503 2.960624162\n"
         "    </data>\n"
         "  </table>\n"
         "</resonanceParameters>\n";
}
