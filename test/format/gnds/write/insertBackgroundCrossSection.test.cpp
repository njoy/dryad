// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertBackgroundCrossSection.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertBackgroundCrossSection" ) {

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
   resonances::ResonanceParameters resonances( std::move( resolved ) );

  GIVEN( "a parent node, resonance parameters and xs - upper resolved present" ) {

    gnds::write::Options options;

    THEN( "a crossSection node using a resonancesWithBackground can be inserted" ) {

      TabulatedCrossSection table( {  1.,  2.,  3.,  4.,  5., 6. }, {  7.,  8.,  9., 10., 11., 12. } );

      pugi::xml_document parent;
      auto node = gnds::write::insertBackgroundCrossSection( parent, options, table, resonances, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node, resonance parameters and xs - upper resolved not present" ) {

    gnds::write::Options options;

    THEN( "a crossSection node using a resonancesWithBackground can be inserted" ) {

      TabulatedCrossSection table( {  1.,  2.,  3.,  4.,  6. }, {  7.,  8.,  9., 10., 12. } );

      pugi::xml_document parent;
      auto node = gnds::write::insertBackgroundCrossSection( parent, options, table, resonances, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node, resonance parameters and xs - upper resolved present as a discontinuity" ) {

    gnds::write::Options options;

    THEN( "a crossSection node using a resonancesWithBackground can be inserted" ) {

      TabulatedCrossSection table( {  1.,  2.,  3.,  4.,  5., 5., 6. }, {  7.,  8.,  9., 10., 11., 12., 13. } );

      pugi::xml_document parent;
      auto node = gnds::write::insertBackgroundCrossSection( parent, options, table, resonances, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<crossSection>\n"
         "  <resonancesWithBackground label=\"eval\">\n"
         "    <resonances href=\"/reactionSuite/resonances\" />\n"
         "    <background>\n"
         "      <resolvedRegion>\n"
         "        <XYs1d>\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "          </axes>\n"
         "          <values>\n"
         "            1 7 2 8 3 9 4 10 5 11\n"
         "          </values>\n"
         "        </XYs1d>\n"
         "      </resolvedRegion>\n"
         "      <fastRegion>\n"
         "        <XYs1d>\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "          </axes>\n"
         "          <values>\n"
         "            5 11 6 12\n"
         "          </values>\n"
         "        </XYs1d>\n"
         "      </fastRegion>\n"
         "    </background>\n"
         "  </resonancesWithBackground>\n"
         "</crossSection>\n";
}

std::string chunk2() {

  return "<crossSection>\n"
         "  <resonancesWithBackground label=\"eval\">\n"
         "    <resonances href=\"/reactionSuite/resonances\" />\n"
         "    <background>\n"
         "      <resolvedRegion>\n"
         "        <XYs1d>\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "          </axes>\n"
         "          <values>\n"
         "            1 7 2 8 3 9 4 10 5 11\n"
         "          </values>\n"
         "        </XYs1d>\n"
         "      </resolvedRegion>\n"
         "      <fastRegion>\n"
         "        <XYs1d>\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "          </axes>\n"
         "          <values>\n"
         "            5 12 6 13\n"
         "          </values>\n"
         "        </XYs1d>\n"
         "      </fastRegion>\n"
         "    </background>\n"
         "  </resonancesWithBackground>\n"
         "</crossSection>\n";
}
