// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/continuous/createElasticTabulatedCrossSection.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createTabulatedCrossSection" ) {

  GIVEN( "instances of ContinuousEnergyTable" ) {

    WHEN( "a photonuclear table is given" ) {

      njoy::ACEtk::ContinuousEnergyTable table( njoy::ACEtk::fromFile( "1001.10c" ) );

      THEN( "tabulated cross sections can be derived" ) {

        auto xs = format::ace::continuous::createElasticTabulatedCrossSection( table );

        CHECK_THAT( 1e-5, WithinRel( xs.lowerEnergyLimit() ) );
        CHECK_THAT( 2e+7, WithinRel( xs.upperEnergyLimit() ) );
        CHECK( 631 == xs.numberPoints() );
        CHECK( 1 == xs.numberRegions() );
        CHECK( 631 == xs.energies().size() );
        CHECK( 631 == xs.values().size() );
        CHECK( 1 == xs.boundaries().size() );
        CHECK( 1 == xs.interpolants().size() );
        CHECK_THAT( 1e-5, WithinRel( xs.energies().front() ) );
        CHECK_THAT( 2e+7, WithinRel( xs.energies().back() ) );
        CHECK_THAT( 1160.528, WithinRel( xs.values().front() ) );
        CHECK_THAT( .4818408, WithinRel( xs.values().back() ) );
        CHECK( 630 == xs.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs.interpolants()[0] );
        CHECK( true == xs.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
