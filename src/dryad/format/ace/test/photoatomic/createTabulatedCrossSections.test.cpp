// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/photoatomic/createTabulatedCrossSections.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createTabulatedCrossSections" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "it can be converted" ) {

        auto xs = format::ace::photoatomic::createTabulatedCrossSections( table );

        CHECK( 5 == xs.size() );

        // total - MT501
        CHECK_THAT( 1000., WithinRel( xs[0].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[0].upperEnergyLimit(), 1e-10 ) );
        CHECK( 278 == xs[0].numberPoints() );
        CHECK( 1 == xs[0].numberRegions() );
        CHECK( 278 == xs[0].energies().size() );
        CHECK( 278 == xs[0].values().size() );
        CHECK( 1 == xs[0].boundaries().size() );
        CHECK( 1 == xs[0].interpolants().size() );
        CHECK_THAT(       1000., WithinRel( xs[0].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[0].energies()[277], 1e-10 ) );
        CHECK_THAT( 1.207455e+1, WithinRel( xs[0].values()[0], 1e-6 ) );
        CHECK_THAT( 2.071804e-2, WithinRel( xs[0].values()[277], 1e-6 ) );
        CHECK( 277 == xs[0].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[0].interpolants()[0] );
        CHECK( true == xs[0].isLinearised() );

        // coherent - MT502
        CHECK_THAT( 1000., WithinRel( xs[1].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[1].upperEnergyLimit(), 1e-10 ) );
        CHECK( 278 == xs[1].numberPoints() );
        CHECK( 1 == xs[1].numberRegions() );
        CHECK( 278 == xs[1].energies().size() );
        CHECK( 278 == xs[1].values().size() );
        CHECK( 1 == xs[1].boundaries().size() );
        CHECK( 1 == xs[1].interpolants().size() );
        CHECK_THAT(          1000., WithinRel( xs[1].energies()[0], 1e-10 ) );
        CHECK_THAT(          1e+11, WithinRel( xs[1].energies()[277], 1e-10 ) );
        CHECK_THAT( 5.817904841e-1, WithinRel( xs[1].values()[0], 1e-10 ) );
        CHECK_THAT(    4.62616e-16, WithinRel( xs[1].values()[277], 1e-10 ) );
        CHECK( 277 == xs[1].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[1].interpolants()[0] );
        CHECK( true == xs[1].isLinearised() );

        // incoherent - MT504
        CHECK_THAT( 1000., WithinRel( xs[2].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[2].upperEnergyLimit(), 1e-10 ) );
        CHECK( 278 == xs[2].numberPoints() );
        CHECK( 1 == xs[2].numberRegions() );
        CHECK( 278 == xs[2].energies().size() );
        CHECK( 278 == xs[2].values().size() );
        CHECK( 1 == xs[2].boundaries().size() );
        CHECK( 1 == xs[2].interpolants().size() );
        CHECK_THAT(       1000., WithinRel( xs[2].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[2].energies()[277], 1e-10 ) );
        CHECK_THAT( 8.434300e-2, WithinRel( xs[2].values()[0], 1e-10 ) );
        CHECK_THAT( 1.704200e-5, WithinRel( xs[2].values()[277], 1e-10 ) );
        CHECK( 277 == xs[2].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[2].interpolants()[0] );
        CHECK( true == xs[2].isLinearised() );

        // pair production - MT516 (sum of MT515 and MT517)
        CHECK_THAT( 1000., WithinRel( xs[3].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[3].upperEnergyLimit(), 1e-10 ) );
        CHECK( 278 == xs[3].numberPoints() );
        CHECK( 1 == xs[3].numberRegions() );
        CHECK( 278 == xs[3].energies().size() );
        CHECK( 278 == xs[3].values().size() );
        CHECK( 1 == xs[3].boundaries().size() );
        CHECK( 1 == xs[3].interpolants().size() );
        CHECK_THAT(       1000., WithinRel( xs[3].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[3].energies()[277], 1e-10 ) );
        CHECK_THAT(          0., WithinRel( xs[3].values()[0], 1e-10 ) );
        CHECK_THAT( 2.070100e-2, WithinRel( xs[3].values()[277], 1e-10 ) );
        CHECK( 277 == xs[3].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[3].interpolants()[0] );
        CHECK( true == xs[3].isLinearised() );

        // photoelectric - MT522 (sum of MT534 and up)
        CHECK_THAT( 1000., WithinRel( xs[4].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[4].upperEnergyLimit(), 1e-10 ) );
        CHECK( 278 == xs[4].numberPoints() );
        CHECK( 1 == xs[4].numberRegions() );
        CHECK( 278 == xs[4].energies().size() );
        CHECK( 278 == xs[4].values().size() );
        CHECK( 1 == xs[4].boundaries().size() );
        CHECK( 1 == xs[4].interpolants().size() );
        CHECK_THAT(        1000., WithinRel( xs[4].energies()[0], 1e-10 ) );
        CHECK_THAT(        1e+11, WithinRel( xs[4].energies()[277], 1e-10 ) );
        CHECK_THAT( 11.408415496, WithinRel( xs[4].values()[0], 1e-10 ) );
        CHECK_THAT(  7.73600e-15, WithinRel( xs[4].values()[277], 1e-10 ) );
        CHECK( 277 == xs[4].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[4].interpolants()[0] );
        CHECK( true == xs[4].isLinearised() );

      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "it can be converted" ) {

        auto xs = format::ace::photoatomic::createTabulatedCrossSections( table );

        CHECK( 6 == xs.size() );

        // total - MT501
        CHECK_THAT(    1., WithinRel( xs[0].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[0].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[0].numberPoints() );
        CHECK( 1 == xs[0].numberRegions() );
        CHECK( 647 == xs[0].energies().size() );
        CHECK( 647 == xs[0].values().size() );
        CHECK( 1 == xs[0].boundaries().size() );
        CHECK( 1 == xs[0].interpolants().size() );
        CHECK_THAT(           1., WithinRel( xs[0].energies()[0], 1e-10 ) );
        CHECK_THAT(        1e+11, WithinRel( xs[0].energies()[646], 1e-10 ) );
        CHECK_THAT(  9.983176e-6, WithinRel( xs[0].values()[0], 1e-10 ) );
        CHECK_THAT( 2.0718042e-2, WithinRel( xs[0].values()[646], 1e-10 ) );
        CHECK( 646 == xs[0].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[0].interpolants()[0] );
        CHECK( true == xs[0].isLinearised() );

        // coherent - MT502
        CHECK_THAT(    1., WithinRel( xs[1].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[1].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[1].numberPoints() );
        CHECK( 1 == xs[1].numberRegions() );
        CHECK( 647 == xs[1].energies().size() );
        CHECK( 647 == xs[1].values().size() );
        CHECK( 1 == xs[1].boundaries().size() );
        CHECK( 1 == xs[1].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[1].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[1].energies()[646], 1e-10 ) );
        CHECK_THAT( 9.887553e-6, WithinRel( xs[1].values()[0], 1e-10 ) );
        CHECK_THAT( 4.62616e-16, WithinRel( xs[1].values()[646], 1e-10 ) );
        CHECK( 646 == xs[1].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[1].interpolants()[0] );
        CHECK( true == xs[1].isLinearised() );

        // incoherent - MT504
        CHECK_THAT(    1., WithinRel( xs[2].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[2].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[2].numberPoints() );
        CHECK( 1 == xs[2].numberRegions() );
        CHECK( 647 == xs[2].energies().size() );
        CHECK( 647 == xs[2].values().size() );
        CHECK( 1 == xs[2].boundaries().size() );
        CHECK( 1 == xs[2].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[2].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[2].energies()[646], 1e-10 ) );
        CHECK_THAT( 9.562300e-8, WithinRel( xs[2].values()[0], 1e-10 ) );
        CHECK_THAT( 1.704200e-5, WithinRel( xs[2].values()[646], 1e-10 ) );
        CHECK( 646 == xs[2].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[2].interpolants()[0] );
        CHECK( true == xs[2].isLinearised() );

        // pair production - MT516 (sum of MT515 and MT517)
        CHECK_THAT(    1., WithinRel( xs[3].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[3].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[3].numberPoints() );
        CHECK( 1 == xs[3].numberRegions() );
        CHECK( 647 == xs[3].energies().size() );
        CHECK( 647 == xs[3].values().size() );
        CHECK( 1 == xs[3].boundaries().size() );
        CHECK( 1 == xs[3].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[3].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[3].energies()[646], 1e-10 ) );
        CHECK_THAT(          0., WithinRel( xs[3].values()[0], 1e-10 ) );
        CHECK_THAT( 2.070100e-2, WithinRel( xs[3].values()[646], 1e-10 ) );
        CHECK( 646 == xs[3].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[3].interpolants()[0] );
        CHECK( true == xs[3].isLinearised() );

        // photoelectric - MT522 (sum of MT534 and up)
        CHECK_THAT(    1., WithinRel( xs[4].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[4].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[4].numberPoints() );
        CHECK( 1 == xs[4].numberRegions() );
        CHECK( 647 == xs[4].energies().size() );
        CHECK( 647 == xs[4].values().size() );
        CHECK( 1 == xs[4].boundaries().size() );
        CHECK( 1 == xs[4].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[4].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[4].energies()[646], 1e-10 ) );
        CHECK_THAT(          0., WithinRel( xs[4].values()[0], 1e-10 ) );
        CHECK_THAT( 7.73600e-15, WithinRel( xs[4].values()[646], 1e-10 ) );
        CHECK( 646 == xs[4].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[4].interpolants()[0] );
        CHECK( true == xs[4].isLinearised() );

        // subshell photoelectric - MT534
        CHECK_THAT(    1., WithinRel( xs[5].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[5].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[5].numberPoints() );
        CHECK( 1 == xs[5].numberRegions() );
        CHECK( 647 == xs[5].energies().size() );
        CHECK( 647 == xs[5].values().size() );
        CHECK( 1 == xs[5].boundaries().size() );
        CHECK( 1 == xs[5].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[5].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[5].energies()[646], 1e-10 ) );
        CHECK_THAT(          0., WithinRel( xs[5].values()[0], 1e-10 ) );
        CHECK_THAT( 7.73600e-15, WithinRel( xs[5].values()[646], 1e-10 ) );
        CHECK( 646 == xs[5].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[5].interpolants()[0] );
        CHECK( true == xs[5].isLinearised() );

      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "it can be converted" ) {

        auto xs = format::ace::photoatomic::createTabulatedCrossSections( table );

        CHECK( 6 == xs.size() );

        // total - MT501
        CHECK_THAT(    1., WithinRel( xs[0].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[0].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[0].numberPoints() );
        CHECK( 1 == xs[0].numberRegions() );
        CHECK( 647 == xs[0].energies().size() );
        CHECK( 647 == xs[0].values().size() );
        CHECK( 1 == xs[0].boundaries().size() );
        CHECK( 1 == xs[0].interpolants().size() );
        CHECK_THAT(           1., WithinRel( xs[0].energies()[0], 1e-10 ) );
        CHECK_THAT(        1e+11, WithinRel( xs[0].energies()[646], 1e-10 ) );
        CHECK_THAT(  9.983176e-6, WithinRel( xs[0].values()[0], 1e-10 ) );
        CHECK_THAT( 2.0718042e-2, WithinRel( xs[0].values()[646], 1e-10 ) );
        CHECK( 646 == xs[0].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[0].interpolants()[0] );
        CHECK( true == xs[0].isLinearised() );

        // coherent - MT502
        CHECK_THAT(    1., WithinRel( xs[1].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[1].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[1].numberPoints() );
        CHECK( 1 == xs[1].numberRegions() );
        CHECK( 647 == xs[1].energies().size() );
        CHECK( 647 == xs[1].values().size() );
        CHECK( 1 == xs[1].boundaries().size() );
        CHECK( 1 == xs[1].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[1].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[1].energies()[646], 1e-10 ) );
        CHECK_THAT( 9.887553e-6, WithinRel( xs[1].values()[0], 1e-10 ) );
        CHECK_THAT( 4.62616e-16, WithinRel( xs[1].values()[646], 1e-10 ) );
        CHECK( 646 == xs[1].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[1].interpolants()[0] );
        CHECK( true == xs[1].isLinearised() );

        // incoherent - MT504
        CHECK_THAT(    1., WithinRel( xs[2].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[2].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[2].numberPoints() );
        CHECK( 1 == xs[2].numberRegions() );
        CHECK( 647 == xs[2].energies().size() );
        CHECK( 647 == xs[2].values().size() );
        CHECK( 1 == xs[2].boundaries().size() );
        CHECK( 1 == xs[2].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[2].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[2].energies()[646], 1e-10 ) );
        CHECK_THAT( 9.562300e-8, WithinRel( xs[2].values()[0], 1e-10 ) );
        CHECK_THAT( 1.704200e-5, WithinRel( xs[2].values()[646], 1e-10 ) );
        CHECK( 646 == xs[2].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[2].interpolants()[0] );
        CHECK( true == xs[2].isLinearised() );

        // pair production - MT516 (sum of MT515 and MT517)
        CHECK_THAT(    1., WithinRel( xs[3].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[3].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[3].numberPoints() );
        CHECK( 1 == xs[3].numberRegions() );
        CHECK( 647 == xs[3].energies().size() );
        CHECK( 647 == xs[3].values().size() );
        CHECK( 1 == xs[3].boundaries().size() );
        CHECK( 1 == xs[3].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[3].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[3].energies()[646], 1e-10 ) );
        CHECK_THAT(          0., WithinRel( xs[3].values()[0], 1e-10 ) );
        CHECK_THAT( 2.070100e-2, WithinRel( xs[3].values()[646], 1e-10 ) );
        CHECK( 646 == xs[3].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[3].interpolants()[0] );
        CHECK( true == xs[3].isLinearised() );

        // photoelectric - MT522 (sum of MT534 and up)
        CHECK_THAT(    1., WithinRel( xs[4].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[4].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[4].numberPoints() );
        CHECK( 1 == xs[4].numberRegions() );
        CHECK( 647 == xs[4].energies().size() );
        CHECK( 647 == xs[4].values().size() );
        CHECK( 1 == xs[4].boundaries().size() );
        CHECK( 1 == xs[4].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[4].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[4].energies()[646], 1e-10 ) );
        CHECK_THAT(          0., WithinRel( xs[4].values()[0], 1e-10 ) );
        CHECK_THAT( 7.73600e-15, WithinRel( xs[4].values()[646], 1e-10 ) );
        CHECK( 646 == xs[4].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[4].interpolants()[0] );
        CHECK( true == xs[4].isLinearised() );

        // subshell photoelectric - MT534
        CHECK_THAT(    1., WithinRel( xs[5].lowerEnergyLimit(), 1e-10 ) );
        CHECK_THAT( 1e+11, WithinRel( xs[5].upperEnergyLimit(), 1e-10 ) );
        CHECK( 647 == xs[5].numberPoints() );
        CHECK( 1 == xs[5].numberRegions() );
        CHECK( 647 == xs[5].energies().size() );
        CHECK( 647 == xs[5].values().size() );
        CHECK( 1 == xs[5].boundaries().size() );
        CHECK( 1 == xs[5].interpolants().size() );
        CHECK_THAT(          1., WithinRel( xs[5].energies()[0], 1e-10 ) );
        CHECK_THAT(       1e+11, WithinRel( xs[5].energies()[646], 1e-10 ) );
        CHECK_THAT(          0., WithinRel( xs[5].values()[0], 1e-10 ) );
        CHECK_THAT( 7.73600e-15, WithinRel( xs[5].values()[646], 1e-10 ) );
        CHECK( 646 == xs[5].boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == xs[5].interpolants()[0] );
        CHECK( true == xs[5].isLinearised() );

      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
