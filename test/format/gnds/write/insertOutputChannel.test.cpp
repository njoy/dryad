// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertOutputChannel.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertOutputChannel" ) {

  GIVEN( "a parent node and reaction with products" ) {

    gnds::write::Options options;

    THEN( "a reactions node can be inserted" ) {

      Reaction reaction( id::ReactionID( "n,U235->n,U235" ),
                         TabulatedCrossSection( {  1.,  2.,  3.,  4.,  5., 12. }, {  7.,  8.,  9., 10., 11., 12. } ),
                         { ReactionProduct( id::ParticleID::neutron(), 1 ), ReactionProduct( id::ParticleID( "U235" ), 1 ) },
                         std::nullopt, 0. );

      pugi::xml_document parent;
      auto node = gnds::write::insertOutputChannel( parent, options, reaction, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and reaction without products" ) {

    gnds::write::Options options;

    THEN( "a reactions node can be inserted" ) {

      Reaction reaction( id::ReactionID( "n,U235->n,U235" ),
                         TabulatedCrossSection( {  1.,  2.,  3.,  4.,  5., 12. }, {  7.,  8.,  9., 10., 11., 12. } ),
                         {}, std::nullopt, 0. );

      pugi::xml_document parent;
      auto node = gnds::write::insertOutputChannel( parent, options, reaction, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<outputChannel>\n"
         "  <Q>\n"
         "    <constant1d label=\"eval\" value=\"0\" domainMin=\"1\" domainMax=\"12\">\n"
         "      <axes>\n"
         "        <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "        <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "      </axes>\n"
         "    </constant1d>\n"
         "  </Q>\n"
         "  <products>\n"
         "    <product pid=\"n\" label=\"n\">\n"
         "      <multiplicity>\n"
         "        <constant1d label=\"eval\" value=\"1\" domainMin=\"1\" domainMax=\"12\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"multiplicity\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </multiplicity>\n"
         "      <distribution>\n"
         "        <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "      </distribution>\n"
         "    </product>\n"
         "    <product pid=\"U235\" label=\"U235\">\n"
         "      <multiplicity>\n"
         "        <constant1d label=\"eval\" value=\"1\" domainMin=\"1\" domainMax=\"12\">\n"
         "          <axes>\n"
         "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "            <axis index=\"0\" label=\"multiplicity\" />\n"
         "          </axes>\n"
         "        </constant1d>\n"
         "      </multiplicity>\n"
         "      <distribution>\n"
         "        <unspecified label=\"eval\" productFrame=\"lab\" />\n"
         "      </distribution>\n"
         "    </product>\n"
         "  </products>\n"
         "</outputChannel>\n";
}

std::string chunk2() {

  return "<outputChannel>\n"
         "  <Q>\n"
         "    <constant1d label=\"eval\" value=\"0\" domainMin=\"1\" domainMax=\"12\">\n"
         "      <axes>\n"
         "        <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "        <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
         "      </axes>\n"
         "    </constant1d>\n"
         "  </Q>\n"
         "</outputChannel>\n";
}
