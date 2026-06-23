// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createLegendreAngularDistributionFunction.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const std::pair< std::optional< double >, LegendreAngularDistributionFunction >& );

SCENARIO( "createLegendreAngularDistributionFunction" ) {

  GIVEN( "GNDS Legendre node from incident neutron data" ) {

    pugi::xml_document document;
    document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                   child( "outputChannel" ).child( "products" ).
                                   find_child_by_attribute( "product", "pid", "n" ).
                                   child( "distribution" ).child( "angularTwoBody" ).
                                   child( "XYs2d" );

    auto axes = gnds::read::readAxes( node.child( "axes" ) );
    pugi::xml_node legendre = node.child( "function1ds" ).child( "Legendre" );

    WHEN( "a single average energy node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::createLegendreAngularDistributionFunction( legendre, axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk(  const std::pair< std::optional< double >,
                                    LegendreAngularDistributionFunction >& chunk ) {

  // outer domain value and unit
  CHECK( 1e-5 == chunk.first );

  // Legendre angular distribution
  CHECK_THAT( -1., WithinRel( chunk.second.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( chunk.second.upperCosineLimit() ) );
  CHECK( 6 == chunk.second.order() );
  CHECK( 7 == chunk.second.coefficients().size() );
  CHECK_THAT( 0.5               , WithinRel( chunk.second.coefficients()[0] ) );
  CHECK_THAT( 1.5 * -1.1674e-14 , WithinRel( chunk.second.coefficients()[1] ) );
  CHECK_THAT( 2.5 * -1.01123e-16, WithinRel( chunk.second.coefficients()[2] ) );
  CHECK_THAT( 3.5 * -1.82863e-17, WithinRel( chunk.second.coefficients()[3] ) );
  CHECK_THAT( 4.5 * 3.03417e-17 , WithinRel( chunk.second.coefficients()[4] ) );
  CHECK_THAT( 5.5 * -3.10313e-18, WithinRel( chunk.second.coefficients()[5] ) );
  CHECK_THAT( 6.5 * 3.93859e-18 , WithinRel( chunk.second.coefficients()[6] ) );
}
