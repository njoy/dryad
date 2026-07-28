// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/insertProjectileEnergyDomain.hpp"

// other includes
#include <sstream>
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();

SCENARIO( "insertProjectileEnergyDomain" ) {

  GIVEN( "a parent node" ) {

    gnds::write::Options options;

    THEN( "a projectileEnergyDomain node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::insertProjectileEnergyDomain( parent, options, 1e-5, 2e+7, "eV" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunk1() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunk1() {

  return "<projectileEnergyDomain min=\"1e-05\" max=\"20000000\" unit=\"eV\" />\n";
}
