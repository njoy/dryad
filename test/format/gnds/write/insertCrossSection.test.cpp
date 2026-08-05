// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertCrossSection.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk1();
std::string chunk2();
std::string chunk3();

SCENARIO( "insertCrossSection" ) {

  GIVEN( "a parent node and xs with a single interpolation zone" ) {

    gnds::write::Options options;

    THEN( "a crossSection node using an XYs1d can be inserted - with a label" ) {

      TabulatedCrossSection table( {  1.,  2.,  3.,  4.,  5.,  6. },
                                   {  7.,  8.,  9., 10., 11., 12. },
                                   InterpolationType::LinearLinear );

      pugi::xml_document parent;
      auto node = gnds::write::insertCrossSection( parent, options, table, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and xs with multiple interpolation zones but no discontinuities" ) {

    gnds::write::Options options;

    THEN( "a crossSection node using a regions1d node can be inserted - with a label" ) {

      TabulatedCrossSection table( {  1.,  2.,  3.,  4.,  5.,  6. },
                                   {  7.,  8.,  9., 10., 11., 12. },
                                   { 3, 5 },
                                   { InterpolationType::LinearLinear, InterpolationType::LogLog } );

      pugi::xml_document parent;
      auto node = gnds::write::insertCrossSection( parent, options, table, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and data with multiple interpolation zone with discontinuities" ) {

    gnds::write::Options options;

    THEN( "a crossSection node using a regions1d node can be inserted - with a label" ) {

      TabulatedCrossSection table( {  1.,  2.,  3.,  4.,  4., 5.,  6. },
                                   {  7.,  8.,  9., 10., 11., 12., 13. },
                                   { 3, 6 },
                                   { InterpolationType::LinearLinear, InterpolationType::LogLog } );

      pugi::xml_document parent;
      auto node = gnds::write::insertCrossSection( parent, options, table, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk3() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<crossSection>\n"
         "  <XYs1d label=\"eval\">\n"
         "    <axes>\n"
         "      <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "    </axes>\n"
         "    <values>\n"
         "      1 7 2 8 3 9\n"
         "      4 10 5 11 6 12\n"
         "    </values>\n"
         "  </XYs1d>\n"
         "</crossSection>\n";
}

std::string chunk2() {

  return "<crossSection>\n"
         "  <regions1d label=\"eval\">\n"
         "    <axes>\n"
         "      <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "    </axes>\n"
         "    <function1ds>\n"
         "      <XYs1d index=\"0\">\n"
         "        <values>\n"
         "          1 7 2 8 3 9\n"
         "          4 10\n"
         "        </values>\n"
         "      </XYs1d>\n"
         "      <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "        <values>\n"
         "          4 10 5 11 6 12\n"
         "        </values>\n"
         "      </XYs1d>\n"
         "    </function1ds>\n"
         "  </regions1d>\n"
         "</crossSection>\n";
}

std::string chunk3() {

  return "<crossSection>\n"
         "  <regions1d label=\"eval\">\n"
         "    <axes>\n"
         "      <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "      <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "    </axes>\n"
         "    <function1ds>\n"
         "      <XYs1d index=\"0\">\n"
         "        <values>\n"
         "          1 7 2 8 3 9\n"
         "          4 10\n"
         "        </values>\n"
         "      </XYs1d>\n"
         "      <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "        <values>\n"
         "          4 11 5 12 6 13\n"
         "        </values>\n"
         "      </XYs1d>\n"
         "    </function1ds>\n"
         "  </regions1d>\n"
         "</crossSection>\n";
}
