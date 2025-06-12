// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/electroatomic/createPdfFromCdf.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"
#include "dryad/format/ace/createTabulatedAngularDistributionFunction.hpp"
#include "dryad/format/ace/createTabulatedEnergyDistributionFunction.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createPdfFromCdf" ) {

  GIVEN( "instances of cdfs" ) {

    njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

    WHEN( "an elastic angular cdf from eprdata14 is given" ) {

      auto distribution = table.electronElasticAngularDistributionBlock().value().distributions()[0];
      auto cdf = format::ace::createTabulatedAngularDistributionFunction( distribution );

      THEN( "reaction numbers can be derived" ) {

        auto pdf = format::ace::electroatomic::createPdfFromCdf( cdf );

        CHECK_THAT( -1.      , WithinRel( pdf.lowerCosineLimit() ) );
        CHECK_THAT(  0.999999, WithinRel( pdf.upperCosineLimit() ) );
        CHECK( 2 == pdf.numberPoints() );
        CHECK( 1 == pdf.numberRegions() );
        CHECK( 2 == pdf.cosines().size() );
        CHECK( 2 == pdf.values().size() );
        CHECK( 1 == pdf.boundaries().size() );
        CHECK( 1 == pdf.interpolants().size() );
        CHECK_THAT( -1.               , WithinRel( pdf.cosines()[0] ) );
        CHECK_THAT(  0.999999         , WithinRel( pdf.cosines()[1] ) );
        CHECK_THAT(  0.500000250000125, WithinRel( pdf.values()[0] ) );
        CHECK_THAT(  0.500000250000125, WithinRel( pdf.values()[1] ) );
        CHECK( 1 == pdf.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );
        CHECK( true == pdf.isLinearised() );
      } // THEN
    } // WHEN

    WHEN( "an elastic angular cdf from eprdata14 is given" ) {

      auto distribution = table.bremsstrahlungEnergyDistributionBlock().value().distributions()[0];
      auto cdf = format::ace::createTabulatedEnergyDistributionFunction( distribution );

      THEN( "reaction numbers can be derived" ) {

        auto pdf = format::ace::electroatomic::createPdfFromCdf( cdf );

        CHECK_THAT(  0.09999999999999999, WithinRel( pdf.lowerEnergyLimit() ) );
        CHECK_THAT( 10.                 , WithinRel( pdf.upperEnergyLimit() ) );
        CHECK( 32 == pdf.numberPoints() );
        CHECK( 16 == pdf.numberRegions() );
        CHECK( 32 == pdf.energies().size() );
        CHECK( 32 == pdf.values().size() );
        CHECK( 16 == pdf.boundaries().size() );
        CHECK( 16 == pdf.interpolants().size() );
        CHECK_THAT(  0.09999999999999999, WithinRel( pdf.energies()[0] ) );
        CHECK_THAT(  0.133352           , WithinRel( pdf.energies()[1] ) );
        CHECK_THAT(  0.133352           , WithinRel( pdf.energies()[2] ) );
        CHECK_THAT(  0.165482           , WithinRel( pdf.energies()[3] ) );
        CHECK_THAT(  8.                 , WithinRel( pdf.energies()[28] ) );
        CHECK_THAT(  9.9                , WithinRel( pdf.energies()[29] ) );
        CHECK_THAT(  9.9                , WithinRel( pdf.energies()[30] ) );
        CHECK_THAT(  10.                , WithinRel( pdf.energies()[31] ) );
        CHECK_THAT( 1.871805022288618   , WithinRel( pdf.values()[0] ) );
        CHECK_THAT( 1.871805022288618   , WithinRel( pdf.values()[1] ) );
        CHECK_THAT( 1.448445017246499   , WithinRel( pdf.values()[2] ) );
        CHECK_THAT( 1.448445017246499   , WithinRel( pdf.values()[3] ) );
        CHECK_THAT( 0.023991650285684174, WithinRel( pdf.values()[28] ) );
        CHECK_THAT( 0.023991650285684174, WithinRel( pdf.values()[29] ) );
        CHECK_THAT( 0.021331850254000605, WithinRel( pdf.values()[30] ) );
        CHECK_THAT( 0.021331850254000605, WithinRel( pdf.values()[31] ) );
        CHECK( 1 == pdf.boundaries()[0] );
        CHECK( 3 == pdf.boundaries()[1] );
        CHECK( 29 == pdf.boundaries()[14] );
        CHECK( 31 == pdf.boundaries()[15] );
        CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );
        CHECK( true == pdf.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
