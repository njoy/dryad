// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertReactions.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk();
std::string chunkWithBackground();

SCENARIO( "insertReactions" ) {

  GIVEN( "a parent node, reactions and no resonance parameters" ) {

    gnds::write::Options options;

    THEN( "a reactions node can be inserted" ) {

      std::vector< Reaction > reactions = {

        Reaction( id::ReactionID( "n,U235->total" ),
                  { id::ReactionID( "n,U235->n,U235" ), id::ReactionID( "n,U235->2n,U234[all]" ) },
                  TabulatedCrossSection( {  1.,  12. }, {  8.,  18. } ) ),
        Reaction( id::ReactionID( "n,U235->non-elastic" ),
                  { id::ReactionID( "n,U235->2n,U234[all]" ) },
                  TabulatedCrossSection( {  7.,  8.,  9., 10., 11., 12. }, {  1.,  2.,  3.,  4.,  5.,  6. } ),
                  { ReactionProduct( id::ParticleID::photon(), 1 ) } ),
        Reaction( id::ReactionID( "n,U235->n,U235" ),
                  TabulatedCrossSection( {  1.,  2.,  3.,  4.,  5., 12. }, {  7.,  8.,  9., 10., 11., 12. } ),
                  { ReactionProduct( id::ParticleID::neutron(), 1 ), ReactionProduct( id::ParticleID( "U235" ), 1 ) },
                  std::nullopt, 0. ),
        Reaction( id::ReactionID( "n,U235->2n,U234[all]" ),
                  TabulatedCrossSection( {  7.,  8.,  9., 10., 11., 12. }, {  1.,  2.,  3.,  4.,  5.,  6. } ),
                  { ReactionProduct( id::ParticleID::neutron(), 2 ), ReactionProduct( id::ParticleID( "U234" ), 1 ) },
                  std::nullopt, 1e+6 )
      };
      std::optional< resonances::ResonanceParameters > resonances = std::nullopt;

      pugi::xml_document parent;
      auto node = gnds::write::insertReactions( parent, options, reactions, resonances, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node, reactions and resonance parameters" ) {

    gnds::write::Options options;

    THEN( "a reactions node can be inserted" ) {

      std::vector< Reaction > reactions = {

        Reaction( id::ReactionID( "n,U235->total" ),
                  { id::ReactionID( "n,U235->n,U235" ), id::ReactionID( "n,U235->2n,U234[all]" ) },
                  TabulatedCrossSection( {  1.,  12. }, {  8.,  18. } ) ),
        Reaction( id::ReactionID( "n,U235->non-elastic" ),
                  { id::ReactionID( "n,U235->2n,U234[all]" ) },
                  TabulatedCrossSection( {  7.,  8.,  9., 10., 11., 12. }, {  1.,  2.,  3.,  4.,  5.,  6. } ),
                  { ReactionProduct( id::ParticleID::photon(), 1 ) } ),
        Reaction( id::ReactionID( "n,U235->n,U235" ),
                  TabulatedCrossSection( {  1.,  2.,  3.,  4.,  5., 12. }, {  7.,  8.,  9., 10., 11., 12. } ),
                  { ReactionProduct( id::ParticleID::neutron(), 1 ), ReactionProduct( id::ParticleID( "U235" ), 1 ) },
                  std::nullopt, 0. ),
        Reaction( id::ReactionID( "n,U235->2n,U234[all]" ),
                  TabulatedCrossSection( {  7.,  8.,  9., 10., 11., 12. }, {  1.,  2.,  3.,  4.,  5.,  6. } ),
                  { ReactionProduct( id::ParticleID::neutron(), 2 ), ReactionProduct( id::ParticleID( "U234" ), 1 ) },
                  std::nullopt, 1e+6 )
      };

      auto photon = id::ParticleID::photon();
      auto neutron = id::ParticleID::neutron();
      auto u235 = id::ParticleID( "U235" );
      auto u236 = id::ParticleID( "U236[all]" );
      resonances::ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                            Particle( u236, 236 * njoy::constants::neutron_mass, 0, +1 ) );
      resonances::ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                             Particle( u235, 235 * njoy::constants::neutron_mass, 0.5, +1 ) );
      resonances::ChannelRadii zero_radii( 0., 0. );
      resonances::ChannelRadii radii( 4.221, 4.221 );
      resonances::CompoundSystem compound( 1, 5,
                                           { { { { id::ChannelID( "n,U235->g,U236[all]{0,0,0-}" ),
                                                   neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                                 { id::ChannelID( "n,U235->n,U235{1,1,0-}" ),
                                                   neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                               { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                                   id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ) },
                                                 { 3.740320e+5, 6.007182e+5 },
                                                 { { 1., 2. },
                                                   { 1.1, 2.1 } } },
                                               resonances::Formalism::ReichMoore,
                                               resonances::BoundaryCondition::ShiftFactor } } );
      std::vector< resonances::CompoundSystem > resolved = { std::move( compound ) };
      std::optional< resonances::ResonanceParameters > resonances( std::move( resolved ) );

      pugi::xml_document parent;
      auto node = gnds::write::insertReactions( parent, options, reactions, resonances, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkWithBackground() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "<reactions>\n"
         "  <reaction label=\"n,U235->n,U235\" ENDF_MT=\"2\">\n"
         "    <crossSection>\n"
         "      <XYs1d label=\"eval\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "        </axes>\n"
         "        <values>\n"
         "          1 7 2 8 3 9 4 10 5 11 12 12\n"
         "        </values>\n"
         "      </XYs1d>\n"
         "    </crossSection>\n"
         "    <outputChannel>\n"
         "      <Q>\n"
         "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1\" domainMax=\"12\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </Q>\n"
         "      <products>\n"
         "        <product pid=\"n\" label=\"n\">\n"
         "          <multiplicity>\n"
         "            <constant1d label=\"eval\" value=\"1\" domainMin=\"1\" domainMax=\"12\">\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"multiplicity\" />\n"
         "              </axes>\n"
         "            </constant1d>\n"
         "          </multiplicity>\n"
         "          <distribution>\n"
         "            <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "          </distribution>\n"
         "        </product>\n"
         "        <product pid=\"U235\" label=\"U235\">\n"
         "          <multiplicity>\n"
         "            <constant1d label=\"eval\" value=\"1\" domainMin=\"1\" domainMax=\"12\">\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"multiplicity\" />\n"
         "              </axes>\n"
         "            </constant1d>\n"
         "          </multiplicity>\n"
         "          <distribution>\n"
         "            <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "          </distribution>\n"
         "        </product>\n"
         "      </products>\n"
         "    </outputChannel>\n"
         "  </reaction>\n"
         "  <reaction label=\"n,U235->2n,U234[all]\" ENDF_MT=\"16\">\n"
         "    <crossSection>\n"
         "      <XYs1d label=\"eval\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "        </axes>\n"
         "        <values>\n"
         "          7 1 8 2 9 3 10 4 11 5 12 6\n"
         "        </values>\n"
         "      </XYs1d>\n"
         "    </crossSection>\n"
         "    <outputChannel>\n"
         "      <Q>\n"
         "        <constant1d label=\"eval\" value=\"1000000\" domainMin=\"7\" domainMax=\"12\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </Q>\n"
         "      <products>\n"
         "        <product pid=\"n\" label=\"n\">\n"
         "          <multiplicity>\n"
         "            <constant1d label=\"eval\" value=\"2\" domainMin=\"7\" domainMax=\"12\">\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"multiplicity\" />\n"
         "              </axes>\n"
         "            </constant1d>\n"
         "          </multiplicity>\n"
         "          <distribution>\n"
         "            <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "          </distribution>\n"
         "        </product>\n"
         "        <product pid=\"U234\" label=\"U234\">\n"
         "          <multiplicity>\n"
         "            <constant1d label=\"eval\" value=\"1\" domainMin=\"7\" domainMax=\"12\">\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"multiplicity\" />\n"
         "              </axes>\n"
         "            </constant1d>\n"
         "          </multiplicity>\n"
         "          <distribution>\n"
         "            <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "          </distribution>\n"
         "        </product>\n"
         "      </products>\n"
         "    </outputChannel>\n"
         "  </reaction>\n"
         "</reactions>\n";
}

std::string chunkWithBackground() {

  return "<reactions>\n"
         "  <reaction label=\"n,U235->n,U235\" ENDF_MT=\"2\">\n"
         "    <crossSection>\n"
         "      <resonancesWithBackground label=\"eval\">\n"
         "        <resonances href=\"/reactionSuite/resonances\" />\n"
         "        <background>\n"
         "          <resolvedRegion>\n"
         "            <XYs1d>\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "              </axes>\n"
         "              <values>\n"
         "                1 7 2 8 3 9 4 10 5 11\n"
         "              </values>\n"
         "            </XYs1d>\n"
         "          </resolvedRegion>\n"
         "          <fastRegion>\n"
         "            <XYs1d>\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "              </axes>\n"
         "              <values>\n"
         "                5 11 12 12\n"
         "              </values>\n"
         "            </XYs1d>\n"
         "          </fastRegion>\n"
         "        </background>\n"
         "      </resonancesWithBackground>\n"
         "    </crossSection>\n"
         "    <outputChannel>\n"
         "      <Q>\n"
         "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1\" domainMax=\"12\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </Q>\n"
         "      <products>\n"
         "        <product pid=\"n\" label=\"n\">\n"
         "          <multiplicity>\n"
         "            <constant1d label=\"eval\" value=\"1\" domainMin=\"1\" domainMax=\"12\">\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"multiplicity\" />\n"
         "              </axes>\n"
         "            </constant1d>\n"
         "          </multiplicity>\n"
         "          <distribution>\n"
         "            <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "          </distribution>\n"
         "        </product>\n"
         "        <product pid=\"U235\" label=\"U235\">\n"
         "          <multiplicity>\n"
         "            <constant1d label=\"eval\" value=\"1\" domainMin=\"1\" domainMax=\"12\">\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"multiplicity\" />\n"
         "              </axes>\n"
         "            </constant1d>\n"
         "          </multiplicity>\n"
         "          <distribution>\n"
         "            <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "          </distribution>\n"
         "        </product>\n"
         "      </products>\n"
         "    </outputChannel>\n"
         "  </reaction>\n"
         "  <reaction label=\"n,U235->2n,U234[all]\" ENDF_MT=\"16\">\n"
         "    <crossSection>\n"
         "      <XYs1d label=\"eval\">\n"
         "        <axes>\n"
         "          <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "          <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "        </axes>\n"
         "        <values>\n"
         "          7 1 8 2 9 3 10 4 11 5 12 6\n"
         "        </values>\n"
         "      </XYs1d>\n"
         "    </crossSection>\n"
         "    <outputChannel>\n"
         "      <Q>\n"
         "        <constant1d label=\"eval\" value=\"1000000\" domainMin=\"7\" domainMax=\"12\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </Q>\n"
         "      <products>\n"
         "        <product pid=\"n\" label=\"n\">\n"
         "          <multiplicity>\n"
         "            <constant1d label=\"eval\" value=\"2\" domainMin=\"7\" domainMax=\"12\">\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"multiplicity\" />\n"
         "              </axes>\n"
         "            </constant1d>\n"
         "          </multiplicity>\n"
         "          <distribution>\n"
         "            <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "          </distribution>\n"
         "        </product>\n"
         "        <product pid=\"U234\" label=\"U234\">\n"
         "          <multiplicity>\n"
         "            <constant1d label=\"eval\" value=\"1\" domainMin=\"7\" domainMax=\"12\">\n"
         "              <axes>\n"
         "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "                <axis index=\"0\" label=\"multiplicity\" />\n"
         "              </axes>\n"
         "            </constant1d>\n"
         "          </multiplicity>\n"
         "          <distribution>\n"
         "            <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "          </distribution>\n"
         "        </product>\n"
         "      </products>\n"
         "    </outputChannel>\n"
         "  </reaction>\n"
         "</reactions>\n";
}
