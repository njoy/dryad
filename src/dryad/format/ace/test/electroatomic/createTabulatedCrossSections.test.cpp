// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/electroatomic/createTabulatedCrossSections.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createTabulatedCrossSections" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "tabulated cross sections can be derived" ) {

        auto xs = format::ace::electroatomic::createTabulatedCrossSections( table );

        CHECK( 0 == xs.size() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "tabulated cross sections can be derived" ) {

        auto xs = format::ace::electroatomic::createTabulatedCrossSections( table );

        CHECK( 6 == xs.size() );

        // total - MT501
        CHECK_THAT(   10., WithinRel( xs[0].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[0].upperEnergyLimit() ) );
        CHECK( 342 == xs[0].numberPoints() );
        CHECK( 1 == xs[0].numberRegions() );
        CHECK( 342 == xs[0].energies().size() );
        CHECK( 342 == xs[0].values().size() );
        CHECK( 1 == xs[0].boundaries().size() );
        CHECK( 1 == xs[0].interpolants().size() );
        CHECK_THAT(            10., WithinRel( xs[0].energies()[0] ) );
        CHECK_THAT(          1e+11, WithinRel( xs[0].energies()[341] ) );
        CHECK_THAT( 274896029.7832, WithinRel( xs[0].values()[0] ) );
        CHECK_THAT( 164334.9906341, WithinRel( xs[0].values()[341] ) );
        CHECK( 341 == xs[0].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[0].interpolants()[0] );
        CHECK( true == xs[0].isLinearised() );

        // ionisation - MT522
        CHECK_THAT(   10., WithinRel( xs[1].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[1].upperEnergyLimit() ) );
        CHECK( 342 == xs[1].numberPoints() );
        CHECK( 1 == xs[1].numberRegions() );
        CHECK( 342 == xs[1].energies().size() );
        CHECK( 342 == xs[1].values().size() );
        CHECK( 1 == xs[1].boundaries().size() );
        CHECK( 1 == xs[1].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[1].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[1].energies()[341] ) );
        CHECK_THAT(          0., WithinRel( xs[1].values()[0] ) );
        CHECK_THAT( 8.289240e+4, WithinRel( xs[1].values()[341] ) );
        CHECK( 341 == xs[1].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[1].interpolants()[0] );
        CHECK( true == xs[1].isLinearised() );

        // total elastic - MT526
        CHECK_THAT(   10., WithinRel( xs[2].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[2].upperEnergyLimit() ) );
        CHECK( 342 == xs[2].numberPoints() );
        CHECK( 1 == xs[2].numberRegions() );
        CHECK( 342 == xs[2].energies().size() );
        CHECK( 342 == xs[2].values().size() );
        CHECK( 1 == xs[2].boundaries().size() );
        CHECK( 1 == xs[2].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[2].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[2].energies()[341] ) );
        CHECK_THAT( 2.748960e+8, WithinRel( xs[2].values()[0] ) );
        CHECK_THAT( 1.311760e-5, WithinRel( xs[2].values()[341] ) );
        CHECK( 341 == xs[2].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[2].interpolants()[0] );
        CHECK( true == xs[2].isLinearised() );

        // bremsstrahlung - MT527
        CHECK_THAT(   10., WithinRel( xs[3].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[3].upperEnergyLimit() ) );
        CHECK( 342 == xs[3].numberPoints() );
        CHECK( 1 == xs[3].numberRegions() );
        CHECK( 342 == xs[3].energies().size() );
        CHECK( 342 == xs[3].values().size() );
        CHECK( 1 == xs[3].boundaries().size() );
        CHECK( 1 == xs[3].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[3].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[3].energies()[341] ) );
        CHECK_THAT( 2.978320e+1, WithinRel( xs[3].values()[0] ) );
        CHECK_THAT( 9.906210e-1, WithinRel( xs[3].values()[341] ) );
        CHECK( 341 == xs[3].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[3].interpolants()[0] );
        CHECK( true == xs[3].isLinearised() );

        // excitation - MT528
        CHECK_THAT(   10., WithinRel( xs[4].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[4].upperEnergyLimit() ) );
        CHECK( 342 == xs[4].numberPoints() );
        CHECK( 1 == xs[4].numberRegions() );
        CHECK( 342 == xs[4].energies().size() );
        CHECK( 342 == xs[4].values().size() );
        CHECK( 1 == xs[4].boundaries().size() );
        CHECK( 1 == xs[4].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[4].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[4].energies()[341] ) );
        CHECK_THAT(          0., WithinRel( xs[4].values()[0] ) );
        CHECK_THAT( 8.144160e+4, WithinRel( xs[4].values()[341] ) );
        CHECK( 341 == xs[4].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[4].interpolants()[0] );
        CHECK( true == xs[4].isLinearised() );

        // subshell ionisation - MT534
        CHECK_THAT(   10., WithinRel( xs[5].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[5].upperEnergyLimit() ) );
        CHECK( 342 == xs[5].numberPoints() );
        CHECK( 1 == xs[5].numberRegions() );
        CHECK( 342 == xs[5].energies().size() );
        CHECK( 342 == xs[5].values().size() );
        CHECK( 1 == xs[5].boundaries().size() );
        CHECK( 1 == xs[5].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[5].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[5].energies()[341] ) );
        CHECK_THAT(          0., WithinRel( xs[5].values()[0] ) );
        CHECK_THAT( 8.289240e+4, WithinRel( xs[5].values()[341] ) );
        CHECK( 341 == xs[5].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[5].interpolants()[0] );
        CHECK( true == xs[5].isLinearised() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "tabulated cross sections can be derived" ) {

        auto xs = format::ace::electroatomic::createTabulatedCrossSections( table );

        CHECK( 8 == xs.size() );

        // total - MT501
        CHECK_THAT(   10., WithinRel( xs[0].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[0].upperEnergyLimit() ) );
        CHECK( 342 == xs[0].numberPoints() );
        CHECK( 1 == xs[0].numberRegions() );
        CHECK( 342 == xs[0].energies().size() );
        CHECK( 342 == xs[0].values().size() );
        CHECK( 1 == xs[0].boundaries().size() );
        CHECK( 1 == xs[0].interpolants().size() );
        CHECK_THAT(            10., WithinRel( xs[0].energies()[0] ) );
        CHECK_THAT(          1e+11, WithinRel( xs[0].energies()[341] ) );
        CHECK_THAT( 274896029.7832, WithinRel( xs[0].values()[0] ) );
        CHECK_THAT( 164334.9906341, WithinRel( xs[0].values()[341] ) );
        CHECK( 341 == xs[0].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[0].interpolants()[0] );
        CHECK( true == xs[0].isLinearised() );

        // ionisation - MT522
        CHECK_THAT(   10., WithinRel( xs[1].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[1].upperEnergyLimit() ) );
        CHECK( 342 == xs[1].numberPoints() );
        CHECK( 1 == xs[1].numberRegions() );
        CHECK( 342 == xs[1].energies().size() );
        CHECK( 342 == xs[1].values().size() );
        CHECK( 1 == xs[1].boundaries().size() );
        CHECK( 1 == xs[1].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[1].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[1].energies()[341] ) );
        CHECK_THAT(          0., WithinRel( xs[1].values()[0] ) );
        CHECK_THAT( 8.289240e+4, WithinRel( xs[1].values()[341] ) );
        CHECK( 341 == xs[1].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[1].interpolants()[0] );
        CHECK( true == xs[1].isLinearised() );

        // large angle elastic - MT525
        CHECK_THAT(   10., WithinRel( xs[2].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[2].upperEnergyLimit() ) );
        CHECK( 342 == xs[2].numberPoints() );
        CHECK( 1 == xs[2].numberRegions() );
        CHECK( 342 == xs[2].energies().size() );
        CHECK( 342 == xs[2].values().size() );
        CHECK( 1 == xs[2].boundaries().size() );
        CHECK( 1 == xs[2].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[2].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[2].energies()[341] ) );
        CHECK_THAT( 2.748960e+8, WithinRel( xs[2].values()[0] ) );
        CHECK_THAT( 4.33534e-10, WithinRel( xs[2].values()[341] ) );
        CHECK( 341 == xs[2].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[2].interpolants()[0] );
        CHECK( true == xs[2].isLinearised() );

        // total elastic - MT526
        CHECK_THAT(   10., WithinRel( xs[3].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[3].upperEnergyLimit() ) );
        CHECK( 342 == xs[3].numberPoints() );
        CHECK( 1 == xs[3].numberRegions() );
        CHECK( 342 == xs[3].energies().size() );
        CHECK( 342 == xs[3].values().size() );
        CHECK( 1 == xs[3].boundaries().size() );
        CHECK( 1 == xs[3].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[3].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[3].energies()[341] ) );
        CHECK_THAT( 2.748960e+8, WithinRel( xs[3].values()[0] ) );
        CHECK_THAT( 1.298710e+4, WithinRel( xs[3].values()[341] ) );
        CHECK( 341 == xs[3].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[3].interpolants()[0] );
        CHECK( true == xs[3].isLinearised() );

        // bremsstrahlung - MT527
        CHECK_THAT(   10., WithinRel( xs[4].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[4].upperEnergyLimit() ) );
        CHECK( 342 == xs[4].numberPoints() );
        CHECK( 1 == xs[4].numberRegions() );
        CHECK( 342 == xs[4].energies().size() );
        CHECK( 342 == xs[4].values().size() );
        CHECK( 1 == xs[4].boundaries().size() );
        CHECK( 1 == xs[4].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[4].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[4].energies()[341] ) );
        CHECK_THAT( 2.978320e+1, WithinRel( xs[4].values()[0] ) );
        CHECK_THAT( 9.906210e-1, WithinRel( xs[4].values()[341] ) );
        CHECK( 341 == xs[4].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[4].interpolants()[0] );
        CHECK( true == xs[4].isLinearised() );

        // excitation - MT528
        CHECK_THAT(   10., WithinRel( xs[5].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[5].upperEnergyLimit() ) );
        CHECK( 342 == xs[5].numberPoints() );
        CHECK( 1 == xs[5].numberRegions() );
        CHECK( 342 == xs[5].energies().size() );
        CHECK( 342 == xs[5].values().size() );
        CHECK( 1 == xs[5].boundaries().size() );
        CHECK( 1 == xs[5].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[5].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[5].energies()[341] ) );
        CHECK_THAT(          0., WithinRel( xs[5].values()[0] ) );
        CHECK_THAT( 8.144160e+4, WithinRel( xs[5].values()[341] ) );
        CHECK( 341 == xs[5].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[5].interpolants()[0] );
        CHECK( true == xs[5].isLinearised() );

        // subshell ionisation - MT534
        CHECK_THAT(   10., WithinRel( xs[6].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[6].upperEnergyLimit() ) );
        CHECK( 342 == xs[6].numberPoints() );
        CHECK( 1 == xs[6].numberRegions() );
        CHECK( 342 == xs[6].energies().size() );
        CHECK( 342 == xs[6].values().size() );
        CHECK( 1 == xs[6].boundaries().size() );
        CHECK( 1 == xs[6].interpolants().size() );
        CHECK_THAT(         10., WithinRel( xs[6].energies()[0] ) );
        CHECK_THAT(       1e+11, WithinRel( xs[6].energies()[341] ) );
        CHECK_THAT(          0., WithinRel( xs[6].values()[0] ) );
        CHECK_THAT( 8.289240e+4, WithinRel( xs[6].values()[341] ) );
        CHECK( 341 == xs[6].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[6].interpolants()[0] );
        CHECK( true == xs[6].isLinearised() );

        // elastic deficit
        CHECK_THAT(   10., WithinRel( xs[7].lowerEnergyLimit() ) );
        CHECK_THAT( 1e+11, WithinRel( xs[7].upperEnergyLimit() ) );
        CHECK( 342 == xs[7].numberPoints() );
        CHECK( 1 == xs[7].numberRegions() );
        CHECK( 342 == xs[7].energies().size() );
        CHECK( 342 == xs[7].values().size() );
        CHECK( 1 == xs[7].boundaries().size() );
        CHECK( 1 == xs[7].interpolants().size() );
        CHECK_THAT(              10., WithinRel( xs[7].energies()[0] ) );
        CHECK_THAT(            1e+11, WithinRel( xs[7].energies()[341] ) );
        CHECK_THAT(               0., WithinRel( xs[7].values()[0] ) );
        CHECK_THAT( 12987.0999999996, WithinRel( xs[7].values()[341] ) );
        CHECK( 341 == xs[7].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[7].interpolants()[0] );
        CHECK( true == xs[7].isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
