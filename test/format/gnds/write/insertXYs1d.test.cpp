// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertXYs1d.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();
std::string chunk2();
std::string chunk3();
std::string chunk4();

SCENARIO( "insertXYs1d" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "an XYs1d node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertXYs1d( parent, options,
                                            {  1.,  2.,  3.,  4.,  5.,  6. },
                                            {  7.,  8.,  9., 10., 11., 12. },
                                            "incidentEnergy", "crossSection", "eV", "b",
                                            "log-log" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "an XYs1d node can be inserted - with an index and no axes" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertXYs1d( parent, options,
                                            {  1.,  2.,  3.,  4.,  5.,  6. },
                                            {  7.,  8.,  9., 10., 11., 12. },
                                            std::nullopt, std::nullopt, std::nullopt, std::nullopt,
                                            std::nullopt, std::nullopt, 0 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN

    THEN( "an XYs1d node can be inserted - with an outer domain value" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertXYs1d( parent, options,
                                            {  1.,  2.,  3.,  4.,  5.,  6. },
                                            {  7.,  8.,  9., 10., 11., 12. },
                                            "incidentEnergy", "crossSection", "eV", "b",
                                            std::nullopt, std::nullopt, std::nullopt, 1e-5 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk3() );
    } // THEN

    THEN( "an XYs1d node can be inserted - with a label" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertXYs1d( parent, options,
                                            {  1.,  2.,  3.,  4.,  5.,  6. },
                                            {  7.,  8.,  9., 10., 11., 12. },
                                            "incidentEnergy", "crossSection", "eV", "b",
                                            std::nullopt, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk4() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<XYs1d interpolation=\"log-log\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <values>\n"
         "    1 7 2 8 3 9 4 10 5 11 6 12\n"
         "  </values>\n"
         "</XYs1d>\n";
}

std::string chunk2() {

  return "<XYs1d index=\"0\">\n"
         "  <values>\n"
         "    1 7 2 8 3 9 4 10 5 11 6 12\n"
         "  </values>\n"
         "</XYs1d>\n";
}

std::string chunk3() {

  return "<XYs1d outerDomainValue=\"1e-05\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <values>\n"
         "    1 7 2 8 3 9 4 10 5 11 6 12\n"
         "  </values>\n"
         "</XYs1d>\n";
}

std::string chunk4() {

  return "<XYs1d label=\"eval\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <values>\n"
         "    1 7 2 8 3 9 4 10 5 11 6 12\n"
         "  </values>\n"
         "</XYs1d>\n";
}
