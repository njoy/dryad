// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/readGrid.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const format::gnds::Grid&, int index );

SCENARIO( "readAxes" ) {

  GIVEN( "a GNDS grid xml node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node axes = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                   find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                   child( "mixed" ).child( "shortRangeSelfScalingVariance" ).
                                   child( "gridded2d" ).child( "axes" );

    WHEN( "a single GNDS grid node with a values node is used" ) {

      pugi::xml_node grid = axes.find_child_by_attribute( "grid", "index", "2" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readGrid( grid );

        verifyChunk( chunk, 2 );
      } // THEN
    } // WHEN

    WHEN( "a single GNDS grid node with a link node is used" ) {

      pugi::xml_node grid = axes.find_child_by_attribute( "grid", "index", "1" );

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::readGrid( grid );

        verifyChunk( chunk, 1 );
      } // THEN
    } // WHEN

    WHEN( "incorrect nodes are given" ) {

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( format::gnds::readGrid( axes ) );                      // wrong node
        CHECK_THROWS( format::gnds::readGrid( axes.child( "undefined" ) ) ); // undefined node
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const format::gnds::Grid& chunk, int index ) {

  CHECK( index == std::get< 0 >( chunk ) );
  CHECK( "eV"  == std::get< 1 >( chunk ) );

  CHECK( 13 == std::get< 2 >( chunk ).size() );

  CHECK_THAT( 1e-5   , WithinRel( std::get< 2 >( chunk )[0] ) );
  CHECK_THAT( 115840 , WithinRel( std::get< 2 >( chunk )[1] ) );
  CHECK_THAT( 207460 , WithinRel( std::get< 2 >( chunk )[2] ) );
  CHECK_THAT( 3e5    , WithinRel( std::get< 2 >( chunk )[3] ) );
  CHECK_THAT( 4.5e5  , WithinRel( std::get< 2 >( chunk )[4] ) );
  CHECK_THAT( 6e5    , WithinRel( std::get< 2 >( chunk )[5] ) );
  CHECK_THAT( 1.1e6  , WithinRel( std::get< 2 >( chunk )[6] ) );
  CHECK_THAT( 1.5e6  , WithinRel( std::get< 2 >( chunk )[7] ) );
  CHECK_THAT( 3e6    , WithinRel( std::get< 2 >( chunk )[8] ) );
  CHECK_THAT( 6e6    , WithinRel( std::get< 2 >( chunk )[9] ) );
  CHECK_THAT( 1e7    , WithinRel( std::get< 2 >( chunk )[10] ) );
  CHECK_THAT( 1.4e7  , WithinRel( std::get< 2 >( chunk )[11] ) );
  CHECK_THAT( 2e7    , WithinRel( std::get< 2 >( chunk )[12] ) );
}
