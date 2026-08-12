// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/resonances/rmatrix/insertExternalRMatrix.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();

SCENARIO( "insertExternalRMatrix" ) {

  GIVEN( "a parent node and a froehner background" ) {

    gnds::write::Options options;

    resonances::FrohnerBackground froehner( 1., 2., 3., 4., 5. );

    THEN( "a resonanceReactions node can be inserted - fullResonanceData = true" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertExternalRMatrix( parent, options, froehner );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and a sammy background" ) {

    gnds::write::Options options;

    resonances::SammyBackground sammy( { 0.45, 3.2e-7, 0. }, { 0.075, 0. }, 0., 9.55e+5 );

    THEN( "a resonanceReactions node can be inserted - fullResonanceData = true" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertExternalRMatrix( parent, options, sammy );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<externalRMatrix type=\"Froehner\">\n"
          "  <double label=\"averageRadiationWidth\" value=\"3\" unit=\"eV\" />\n"
          "  <double label=\"constantExternalR\" value=\"1\" />\n"
          "  <double label=\"poleStrength\" value=\"2\" />\n"
          "  <double label=\"singularityEnergyBelow\" value=\"4\" unit=\"eV\" />\n"
          "  <double label=\"singularityEnergyAbove\" value=\"5\" unit=\"eV\" />\n"
          "</externalRMatrix>\n";
}

std::string chunk2() {

  return "<externalRMatrix type=\"SAMMY\">\n"
          "  <double label=\"constantExternalR\" value=\"0.45\" />\n"
          "  <double label=\"linearExternalR\" value=\"3.2e-07\" unit=\"1/eV\" />\n"
          "  <double label=\"quadraticExternalR\" value=\"0\" unit=\"1/eV**2\" />\n"
          "  <double label=\"constantLogarithmicCoefficient\" value=\"0.075\" />\n"
          "  <double label=\"linearLogarithmicCoefficient\" value=\"0\" unit=\"1/eV\" />\n"
          "  <double label=\"singularityEnergyBelow\" value=\"0\" unit=\"eV\" />\n"
          "  <double label=\"singularityEnergyAbove\" value=\"955000\" unit=\"eV\" />\n"
          "</externalRMatrix>\n";
}
