// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/resonances/rmatrix/insertSpinGroup.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertSpinGroup" ) {

  auto photon = id::ParticleID::photon();
  auto neutron = id::ParticleID::neutron();
  auto si29 = id::ParticleID( "Si29" );
  auto si30 = id::ParticleID( "Si30[all]" );

  resonances::ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                        Particle( si30, 29.728 * njoy::constants::neutron_mass, 0, +1 ) );
  resonances::ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                         Particle( si29, 28.728 * njoy::constants::neutron_mass, 0.5, +1 ) );

  resonances::ChannelRadii zero_radii( 0., 0. );
  resonances::ChannelRadii radii( 4.221, 4.221 );

  resonances::SpinGroup group( { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                   neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                 { id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ),
                                   neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                               { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                   id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ) },
                                 { 3.740320e+5, 6.007182e+5 },
                                 { { 1., 2. },
                                   { 1.1, 2.1 } } },
                               resonances::Formalism::ReichMoore,
                               resonances::BoundaryCondition::ShiftFactor );

  GIVEN( "a parent node and a spingroup, using reduced widths" ) {

    gnds::write::Options options;

    THEN( "a spinGroup node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertSpinGroup( parent, options, group, 1e-5, 1.2e+6, "eval", true );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and a spingroup, using full widths" ) {

    gnds::write::Options options;

    THEN( "a spinGroup node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertSpinGroup( parent, options, group, 1e-5, 1.2e+6, "eval", false );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<spinGroup label=\"0-\" spin=\"0\" parity=\"-1\">\n"
         "  <channels>\n"
         "    <channel label=\"n,Si29->g,Si30[all]{0,0,0-}\" resonanceReaction=\"n,Si29->g,Si30[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
         "      <scatteringRadius>\n"
         "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </scatteringRadius>\n"
         "    </channel>\n"
         "    <channel label=\"n,Si29->n,Si29{1,1,0-}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"1\" channelSpin=\"1\" columnIndex=\"2\">\n"
         "      <scatteringRadius>\n"
         "        <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </scatteringRadius>\n"
         "    </channel>\n"
         "  </channels>\n"
         "  <resonanceParameters>\n"
         "    <table rows=\"2\" columns=\"3\">\n"
         "      <columnHeaders>\n"
         "        <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
         "        <column index=\"1\" name=\"n,Si29->g,Si30[all]{0,0,0-} width\" unit=\"eV**(1/2)\" />\n"
         "        <column index=\"2\" name=\"n,Si29->n,Si29{1,1,0-} width\" unit=\"eV**(1/2)\" />\n"
         "      </columnHeaders>\n"
         "      <data>\n"
         "        374032 1 1.1\n"
         "        600718.2 2 2.1\n"
         "      </data>\n"
         "    </table>\n"
         "  </resonanceParameters>\n"
         "</spinGroup>\n";
}

std::string chunk2() {

  return "<spinGroup label=\"0-\" spin=\"0\" parity=\"-1\">\n"
         "  <channels>\n"
         "    <channel label=\"n,Si29->g,Si30[all]{0,0,0-}\" resonanceReaction=\"n,Si29->g,Si30[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
         "      <scatteringRadius>\n"
         "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </scatteringRadius>\n"
         "    </channel>\n"
         "    <channel label=\"n,Si29->n,Si29{1,1,0-}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"1\" channelSpin=\"1\" columnIndex=\"2\">\n"
         "      <scatteringRadius>\n"
         "        <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </scatteringRadius>\n"
         "    </channel>\n"
         "  </channels>\n"
         "  <resonanceParameters>\n"
         "    <table rows=\"2\" columns=\"3\">\n"
         "      <columnHeaders>\n"
         "        <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
         "        <column index=\"1\" name=\"n,Si29->g,Si30[all]{0,0,0-} width\" unit=\"eV\" />\n"
         "        <column index=\"2\" name=\"n,Si29->n,Si29{1,1,0-} width\" unit=\"eV\" />\n"
         "      </columnHeaders>\n"
         "      <data>\n"
         "        374032 2 0.306312855\n"
         "        600718.2 8 1.993262119\n"
         "      </data>\n"
         "    </table>\n"
         "  </resonanceParameters>\n"
         "</spinGroup>\n";
}
