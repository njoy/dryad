// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertSums.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk();

SCENARIO( "insertSums" ) {

  GIVEN( "a parent node, reactions and resonance parameters" ) {

    gnds::write::Options options;

    THEN( "a crossSectionSums node can be inserted" ) {

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
                  { ReactionProduct( id::ParticleID::neutron(), 1 ), ReactionProduct( id::ParticleID( "U235" ), 2 ) },
                  std::nullopt, 0. ),
        Reaction( id::ReactionID( "n,U235->2n,U234[all]" ),
                  TabulatedCrossSection( {  7.,  8.,  9., 10., 11., 12. }, {  1.,  2.,  3.,  4.,  5.,  6. } ),
                  { ReactionProduct( id::ParticleID::neutron(), 2 ), ReactionProduct( id::ParticleID( "U234" ), 2 ) },
                  std::nullopt, 1e+6 )
      };
      std::optional< resonances::ResonanceParameters > resonances = std::nullopt;

      pugi::xml_document parent;
      auto node = gnds::write::insertSums( parent, options, reactions, resonances, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return "<sums>\n"
         "  <crossSectionSums>\n"
         "    <crossSectionSum label=\"n,U235->total\" ENDF_MT=\"1\">\n"
         "      <summands>\n"
         "        <add href=\"/reactionSuite/reactions/reaction[@label=\'n,U235->n,U235\']/crossSection\" />\n"
         "        <add href=\"/reactionSuite/reactions/reaction[@label=\'n,U235->2n,U234[all]\']/crossSection\" />\n"
         "      </summands>\n"
         "      <crossSection>\n"
         "        <XYs1d label=\"eval\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "          </axes>\n"
         "          <values>\n"
         "            1 8 12 18\n"
         "          </values>\n"
         "        </XYs1d>\n"
         "      </crossSection>\n"
         "    </crossSectionSum>\n"
         "    <crossSectionSum label=\"n,U235->non-elastic\" ENDF_MT=\"3\">\n"
         "      <summands>\n"
         "        <add href=\"/reactionSuite/reactions/reaction[@label=\'n,U235->2n,U234[all]\']/crossSection\" />\n"
         "      </summands>\n"
         "      <crossSection>\n"
         "        <XYs1d label=\"eval\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "          </axes>\n"
         "          <values>\n"
         "            7 1 8 2 9 3 10 4 11 5 12 6\n"
         "          </values>\n"
         "        </XYs1d>\n"
         "      </crossSection>\n"
         "    </crossSectionSum>\n"
         "  </crossSectionSums>\n"
         "</sums>\n";
}
