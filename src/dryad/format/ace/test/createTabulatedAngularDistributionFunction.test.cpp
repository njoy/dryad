// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/createTabulatedAngularDistributionFunction.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createTabulatedAngularDistributionFunction" ) {

  GIVEN( "instances of cdfs" ) {

    njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

    WHEN( "an instance of photoatomic ACE ElasticAngularDistributionBlock" ) {

      auto distribution = table.electronElasticAngularDistributionBlock().value().distributions()[0];

      THEN( "a cdf can be derived" ) {

        auto cdf = format::ace::createTabulatedAngularDistributionFunction( distribution );

        CHECK_THAT( -1.      , WithinRel( cdf.lowerCosineLimit() ) );
        CHECK_THAT(  0.999999, WithinRel( cdf.upperCosineLimit() ) );
        CHECK( 2 == cdf.numberPoints() );
        CHECK( 1 == cdf.numberRegions() );
        CHECK( 2 == cdf.cosines().size() );
        CHECK( 2 == cdf.values().size() );
        CHECK( 1 == cdf.boundaries().size() );
        CHECK( 1 == cdf.interpolants().size() );
        CHECK_THAT( -1.      , WithinRel( cdf.cosines()[0] ) );
        CHECK_THAT(  0.999999, WithinRel( cdf.cosines()[1] ) );
        CHECK_THAT(  0.      , WithinRel( cdf.values()[0] ) );
        CHECK_THAT(  1.      , WithinRel( cdf.values()[1] ) );
        CHECK( 1 == cdf.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
        CHECK( true == cdf.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
