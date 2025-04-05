// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createLegendreAngularDistribution.hpp"

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/readAxes.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const std::pair< std::optional< double >, LegendreAngularDistribution >& );

SCENARIO( "createLegendreAngularDistribution" ) {

  GIVEN( "GNDS average energy node from electroatomic data" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                   child( "outputChannel" ).child( "products" ).
                                   find_child_by_attribute( "product", "pid", "n" ).
                                   child( "distribution" ).child( "angularTwoBody" ).
                                   child( "XYs2d" );

    auto axes = format::gnds::readAxes( node.child( "axes" ) );
    pugi::xml_node legendre = node.child( "function1ds" ).child( "Legendre" );

    WHEN( "a single average energy node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createLegendreAngularDistribution( legendre, axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk(  const std::pair< std::optional< double >, LegendreAngularDistribution >& chunk ) {

  // outer domain value and unit
  CHECK( 1e-5 == chunk.first );

  // Legendre angular distribution
  auto pdf = chunk.second.pdf();
  CHECK_THAT( -1., WithinRel( pdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( pdf.upperCosineLimit() ) );
  CHECK( 6 == pdf.order() );
  CHECK( 7 == pdf.coefficients().size() );
  CHECK_THAT( 0.5               , WithinRel( pdf.coefficients()[0] ) );
  CHECK_THAT( 1.5 * -1.1674e-14 , WithinRel( pdf.coefficients()[1] ) );
  CHECK_THAT( 2.5 * -1.01123e-16, WithinRel( pdf.coefficients()[2] ) );
  CHECK_THAT( 3.5 * -1.82863e-17, WithinRel( pdf.coefficients()[3] ) );
  CHECK_THAT( 4.5 * 3.03417e-17 , WithinRel( pdf.coefficients()[4] ) );
  CHECK_THAT( 5.5 * -3.10313e-18, WithinRel( pdf.coefficients()[5] ) );
  CHECK_THAT( 6.5 * 3.93859e-18 , WithinRel( pdf.coefficients()[6] ) );

  auto cdf = chunk.second.cdf();
  CHECK_THAT( -1., WithinRel( cdf.lowerCosineLimit() ) );
  CHECK_THAT(  1., WithinRel( cdf.upperCosineLimit() ) );
  CHECK( 7 == cdf.order() );
  CHECK( 8 == cdf.coefficients().size() );
  CHECK_THAT( 0., WithinRel( cdf( -1. ) ) );
  CHECK_THAT( 1., WithinRel( cdf(  1. ) ) );
}
