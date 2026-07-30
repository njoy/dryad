// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertTabulatedFunction.hpp"

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
std::string chunk4();
std::string chunk5();
std::string chunk6();
std::string chunk7();
std::string chunk8();
std::string chunk9();
std::string chunk10();
std::string chunk11();
std::string chunk12();

SCENARIO( "insertTabulatedFunction" ) {

  GIVEN( "a parent node and data with a single interpolation zone" ) {

    gnds::write::Options options;

    THEN( "an XYs1d node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12. },
                                                        { 5 },
                                                        { InterpolationType::LogLog },
                                                        "incidentEnergy", "crossSection", "eV", "b" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN

    THEN( "an XYs1d node can be inserted - with an index" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12. },
                                                        { 5 },
                                                        { InterpolationType::LinearLinear },
                                                        "incidentEnergy", "crossSection", "eV", "b",
                                                        std::nullopt, 0 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk2() );
    } // THEN

    THEN( "an XYs1d node can be inserted - with an outer domain value" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12. },
                                                        { 5 },
                                                        { InterpolationType::LinearLinear },
                                                        "incidentEnergy", "crossSection", "eV", "b",
                                                        std::nullopt, std::nullopt, 1e-5 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk3() );
    } // THEN

    THEN( "an XYs1d node can be inserted - with a label" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12. },
                                                        { 5 },
                                                        { InterpolationType::LinearLinear },
                                                        "incidentEnergy", "crossSection", "eV", "b",
                                                        "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk4() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and data with multiple interpolation zones but no discontinuities" ) {

    gnds::write::Options options;

    THEN( "a regions1d node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12. },
                                                        { 3, 5 },
                                                        { InterpolationType::LinearLinear, InterpolationType::LogLog },
                                                        "incidentEnergy", "crossSection", "eV", "b" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk5() );
    } // THEN

    THEN( "a regions1d node can be inserted - with an index" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12. },
                                                        { 3, 5 },
                                                        { InterpolationType::LinearLinear, InterpolationType::LogLog },
                                                        "incidentEnergy", "crossSection", "eV", "b",
                                                        std::nullopt, 0 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk6() );
    } // THEN

    THEN( "a regions1d node can be inserted - with an outer domain value" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12. },
                                                        { 3, 5 },
                                                        { InterpolationType::LinearLinear, InterpolationType::LogLog },
                                                        "incidentEnergy", "crossSection", "eV", "b",
                                                        std::nullopt, std::nullopt, 1e-5 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk7() );
    } // THEN

    THEN( "a regions1d node can be inserted - with a label" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12. },
                                                        { 3, 5 },
                                                        { InterpolationType::LinearLinear, InterpolationType::LogLog },
                                                        "incidentEnergy", "crossSection", "eV", "b",
                                                        "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk8() );
    } // THEN
  } // GIVEN

  GIVEN( "a parent node and data with multiple interpolation zone with discontinuities" ) {

    gnds::write::Options options;

    THEN( "a regions1d node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  4., 5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12., 13. },
                                                        { 3, 6 },
                                                        { InterpolationType::LinearLinear, InterpolationType::LogLog },
                                                        "incidentEnergy", "crossSection", "eV", "b" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk9() );
    } // THEN

    THEN( "a regions1d node can be inserted - with an index" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  4., 5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12., 13. },
                                                        { 3, 6 },
                                                        { InterpolationType::LinearLinear, InterpolationType::LogLog },
                                                        "incidentEnergy", "crossSection", "eV", "b",
                                                        std::nullopt, 0 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk10() );
    } // THEN

    THEN( "a regions1d node can be inserted - with an outer domain value" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  4., 5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12., 13. },
                                                        { 3, 6 },
                                                        { InterpolationType::LinearLinear, InterpolationType::LogLog },
                                                        "incidentEnergy", "crossSection", "eV", "b",
                                                        std::nullopt, std::nullopt, 1e-5 );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk11() );
    } // THEN

    THEN( "a regions1d node can be inserted - with a label" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertTabulatedFunction( parent, options,
                                                        {  1.,  2.,  3.,  4.,  4., 5.,  6. },
                                                        {  7.,  8.,  9., 10., 11., 12., 13. },
                                                        { 3, 6 },
                                                        { InterpolationType::LinearLinear, InterpolationType::LogLog },
                                                        "incidentEnergy", "crossSection", "eV", "b",
                                                        "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk12() );
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
         "    1 7 2 8 3 9\n"
         "    4 10 5 11 6 12\n"
         "  </values>\n"
         "</XYs1d>\n";
}

std::string chunk2() {

  return "<XYs1d index=\"0\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <values>\n"
         "    1 7 2 8 3 9\n"
         "    4 10 5 11 6 12\n"
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
         "    1 7 2 8 3 9\n"
         "    4 10 5 11 6 12\n"
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
         "    1 7 2 8 3 9\n"
         "    4 10 5 11 6 12\n"
         "  </values>\n"
         "</XYs1d>\n";
}

std::string chunk5() {

  return "<regions1d>\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <function1ds>\n"
         "    <XYs1d index=\"0\">\n"
         "      <values>\n"
         "        1 7 2 8 3 9\n"
         "        4 10\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "    <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "      <values>\n"
         "        4 10 5 11 6 12\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "  </function1ds>\n"
         "</regions1d>\n";
}

std::string chunk6() {

  return "<regions1d index=\"0\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <function1ds>\n"
         "    <XYs1d index=\"0\">\n"
         "      <values>\n"
         "        1 7 2 8 3 9\n"
         "        4 10\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "    <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "      <values>\n"
         "        4 10 5 11 6 12\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "  </function1ds>\n"
         "</regions1d>\n";
}

std::string chunk7() {

  return "<regions1d outerDomainValue=\"1e-05\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <function1ds>\n"
         "    <XYs1d index=\"0\">\n"
         "      <values>\n"
         "        1 7 2 8 3 9\n"
         "        4 10\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "    <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "      <values>\n"
         "        4 10 5 11 6 12\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "  </function1ds>\n"
         "</regions1d>\n";
}

std::string chunk8() {

  return "<regions1d label=\"eval\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <function1ds>\n"
         "    <XYs1d index=\"0\">\n"
         "      <values>\n"
         "        1 7 2 8 3 9\n"
         "        4 10\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "    <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "      <values>\n"
         "        4 10 5 11 6 12\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "  </function1ds>\n"
         "</regions1d>\n";
}

std::string chunk9() {

  return "<regions1d>\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <function1ds>\n"
         "    <XYs1d index=\"0\">\n"
         "      <values>\n"
         "        1 7 2 8 3 9\n"
         "        4 10\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "    <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "      <values>\n"
         "        4 11 5 12 6 13\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "  </function1ds>\n"
         "</regions1d>\n";
}

std::string chunk10() {

  return "<regions1d index=\"0\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <function1ds>\n"
         "    <XYs1d index=\"0\">\n"
         "      <values>\n"
         "        1 7 2 8 3 9\n"
         "        4 10\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "    <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "      <values>\n"
         "        4 11 5 12 6 13\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "  </function1ds>\n"
         "</regions1d>\n";
}

std::string chunk11() {

  return "<regions1d outerDomainValue=\"1e-05\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <function1ds>\n"
         "    <XYs1d index=\"0\">\n"
         "      <values>\n"
         "        1 7 2 8 3 9\n"
         "        4 10\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "    <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "      <values>\n"
         "        4 11 5 12 6 13\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "  </function1ds>\n"
         "</regions1d>\n";
}

std::string chunk12() {

  return "<regions1d label=\"eval\">\n"
         "  <axes>\n"
         "    <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
         "    <axis index=\"0\" label=\"crossSection\" unit=\"b\" />\n"
         "  </axes>\n"
         "  <function1ds>\n"
         "    <XYs1d index=\"0\">\n"
         "      <values>\n"
         "        1 7 2 8 3 9\n"
         "        4 10\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "    <XYs1d index=\"1\" interpolation=\"log-log\">\n"
         "      <values>\n"
         "        4 11 5 12 6 13\n"
         "      </values>\n"
         "    </XYs1d>\n"
         "  </function1ds>\n"
         "</regions1d>\n";
}
