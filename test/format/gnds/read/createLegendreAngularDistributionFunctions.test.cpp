// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/createLegendreAngularDistributionFunctions.hpp"

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

void verifyChunk( const std::pair< std::vector< std::optional< double > >,
                                   std::vector< LegendreAngularDistributionFunction > >& );

SCENARIO( "createLegendreAngularDistributionFunctions" ) {

  GIVEN( "GNDS function1ds node from incident neutron data" ) {

    pugi::xml_document document;
    document.load_file( "n-001_H_001.endf.gnds.xml" );
    pugi::xml_node node = document.child( "reactionSuite" ).child( "reactions" ).
                                   find_child_by_attribute( "reaction", "ENDF_MT", "2" ).
                                   child( "outputChannel" ).child( "products" ).
                                   find_child_by_attribute( "product", "pid", "n" ).
                                   child( "distribution" ).child( "angularTwoBody" ).
                                   child( "XYs2d" );

    auto axes = gnds::read::readAxes( node.child( "axes" ) );
    pugi::xml_node function1ds = node.child( "function1ds" );

    WHEN( "a single average energy node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::createLegendreAngularDistributionFunctions( function1ds, axes );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const std::pair< std::vector< std::optional< double > >,
                                   std::vector< LegendreAngularDistributionFunction > >& chunk ) {

  CHECK( 153 == chunk.first.size() );
  CHECK( 153 == chunk.second.size() );

  CHECK_THAT( 1e-5   , WithinRel( chunk.first[0].value() ) );
  CHECK_THAT( 2e-5   , WithinRel( chunk.first[1].value() ) );
  CHECK_THAT( 1.95e+7, WithinRel( chunk.first[151].value() ) );
  CHECK_THAT( 2e+7   , WithinRel( chunk.first[152].value() ) );
  CHECK( 7 == chunk.second[0].coefficients().size() );
  CHECK( 7 == chunk.second[1].coefficients().size() );
  CHECK( 7 == chunk.second[151].coefficients().size() );
  CHECK( 7 == chunk.second[152].coefficients().size() );
  CHECK_THAT( 0.5             , WithinRel( chunk.second[0].coefficients()[0] ) );
  CHECK_THAT( -1.7511000E-14  , WithinRel( chunk.second[0].coefficients()[1] ) );
  CHECK_THAT( -2.5280750E-16  , WithinRel( chunk.second[0].coefficients()[2] ) );
  CHECK_THAT( -6.4002050E-17  , WithinRel( chunk.second[0].coefficients()[3] ) );
  CHECK_THAT(  1.3653765E-16  , WithinRel( chunk.second[0].coefficients()[4] ) );
  CHECK_THAT( -1.7067215E-17  , WithinRel( chunk.second[0].coefficients()[5] ) );
  CHECK_THAT(  2.5600835E-17  , WithinRel( chunk.second[0].coefficients()[6] ) );
  CHECK_THAT( 0.5             , WithinRel( chunk.second[1].coefficients()[0] ) );
  CHECK_THAT( -3.4846950E-14  , WithinRel( chunk.second[1].coefficients()[1] ) );
  CHECK_THAT( -1.7387225E-16  , WithinRel( chunk.second[1].coefficients()[2] ) );
  CHECK_THAT( -9.1736400E-17  , WithinRel( chunk.second[1].coefficients()[3] ) );
  CHECK_THAT( -2.9867625E-17  , WithinRel( chunk.second[1].coefficients()[4] ) );
  CHECK_THAT( -3.4134430E-17  , WithinRel( chunk.second[1].coefficients()[5] ) );
  CHECK_THAT(  1.8773950E-16  , WithinRel( chunk.second[1].coefficients()[6] ) );
  CHECK_THAT( 0.5             , WithinRel( chunk.second[151].coefficients()[0] ) );
  CHECK_THAT( -2.4240045E-02  , WithinRel( chunk.second[151].coefficients()[1] ) );
  CHECK_THAT(  1.7942750E-02  , WithinRel( chunk.second[151].coefficients()[2] ) );
  CHECK_THAT( -2.54685165E-03 , WithinRel( chunk.second[151].coefficients()[3] ) );
  CHECK_THAT(  1.54781595E-03 , WithinRel( chunk.second[151].coefficients()[4] ) );
  CHECK_THAT(  4.91773975E-05 , WithinRel( chunk.second[151].coefficients()[5] ) );
  CHECK_THAT(  3.82748535E-05 , WithinRel( chunk.second[151].coefficients()[6] ) );
  CHECK_THAT( 0.5             , WithinRel( chunk.second[152].coefficients()[0] ) );
  CHECK_THAT( -2.41945200E-02 , WithinRel( chunk.second[152].coefficients()[1] ) );
  CHECK_THAT(  1.95173075E-02 , WithinRel( chunk.second[152].coefficients()[2] ) );
  CHECK_THAT( -2.71943700E-03 , WithinRel( chunk.second[152].coefficients()[3] ) );
  CHECK_THAT(  1.69449750E-03 , WithinRel( chunk.second[152].coefficients()[4] ) );
  CHECK_THAT(  5.25219970E-05 , WithinRel( chunk.second[152].coefficients()[5] ) );
  CHECK_THAT(  4.48370065E-05 , WithinRel( chunk.second[152].coefficients()[6] ) );
}
