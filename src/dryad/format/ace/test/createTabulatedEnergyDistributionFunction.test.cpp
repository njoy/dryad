// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/createTabulatedEnergyDistributionFunction.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createTabulatedEnergyDistributionFunction" ) {

  GIVEN( "instances of cdfs" ) {

    njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

    WHEN( "an instance of photoatomic ACE ElasticAngularDistributionBlock" ) {

      auto distribution = table.bremsstrahlungEnergyDistributionBlock().value().distributions()[0];

      THEN( "a cdf can be derived" ) {

        auto cdf = format::ace::createTabulatedEnergyDistributionFunction( distribution );

        CHECK_THAT(  0.09999999999999999, WithinRel( cdf.lowerEnergyLimit() ) );
        CHECK_THAT( 10.                 , WithinRel( cdf.upperEnergyLimit() ) );
        CHECK( 17 == cdf.numberPoints() );
        CHECK(  1 == cdf.numberRegions() );
        CHECK( 17 == cdf.energies().size() );
        CHECK( 17 == cdf.values().size() );
        CHECK(  1 == cdf.boundaries().size() );
        CHECK(  1 == cdf.interpolants().size() );
        CHECK_THAT(  0.09999999999999999, WithinRel( cdf.energies()[0] ) );
        CHECK_THAT( 10.                 , WithinRel( cdf.energies()[16] ) );
        CHECK_THAT(  0.                 , WithinRel( cdf.values()[0] ) );
        CHECK_THAT(  1.                 , WithinRel( cdf.values()[16] ) );
        CHECK( 16 == cdf.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
        CHECK( true == cdf.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
