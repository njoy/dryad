// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTabulatedAngularDistribution.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyNeutronChunk( const TabulatedAngularDistribution& );
void verifyElectronChunk( const TabulatedAngularDistribution& );

SCENARIO( "createTabulatedAngularDistribution" ) {

  GIVEN( "ENDF MF6 LAW = 2 TabulatedDistribution" ) {

    using DiscreteTwoBodyScattering = njoy::ENDFtk::section::Type< 6 >::DiscreteTwoBodyScattering;
    using TabulatedDistribution = DiscreteTwoBodyScattering::TabulatedDistribution;

    auto tape = njoy::ENDFtk::tree::fromFile( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 6, 51 ).parse< 6 >();
    auto distribution = std::get< DiscreteTwoBodyScattering >( section.reactionProduct( 1 ).distribution() );

    WHEN( "a single parsed MF26 multiplicity is given" ) {

      THEN( "it can be converted" ) {

        auto table = std::get< TabulatedDistribution >( distribution.distributions()[0] );
        auto chunk = format::endf::createTabulatedAngularDistribution( table );

        verifyNeutronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF26 LAW = 2 TabulatedDistribution" ) {

    using DiscreteTwoBodyScattering = njoy::ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering;

    auto tape = njoy::ENDFtk::tree::fromFile( "e-001_H_000.endf" );
    auto section = tape.materials().front().section( 26, 525 ).parse< 26 >();
    auto distribution = std::get< DiscreteTwoBodyScattering >( section.reactionProduct( 11 ).distribution() );

    WHEN( "a single parsed MF26 multiplicity is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::endf::createTabulatedAngularDistribution( distribution.distributions()[0] );

        verifyElectronChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyNeutronChunk( const TabulatedAngularDistribution& chunk ) {

  decltype(auto) pdf = chunk.pdf();
  CHECK( false == pdf.isLinearised() );
  CHECK( 2 == pdf.numberPoints() );
  CHECK( 1 == pdf.numberRegions() );
  CHECK( 2 == pdf.cosines().size() );
  CHECK( 2 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK( 1 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LogLinear == pdf.interpolants()[0] );
  CHECK_THAT( -1., WithinRel( pdf.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( pdf.cosines()[1] ) );
  CHECK_THAT( 0.5, WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 0.5, WithinRel( pdf.values()[1] ) );

  CHECK( false == chunk.hasCdf() );
  CHECK_THROWS( chunk.cdf() );
}

void verifyElectronChunk( const TabulatedAngularDistribution& chunk ) {

  decltype(auto) pdf = chunk.pdf();
  CHECK( true == pdf.isLinearised() );
  CHECK( 2 == pdf.numberPoints() );
  CHECK( 1 == pdf.numberRegions() );
  CHECK( 2 == pdf.cosines().size() );
  CHECK( 2 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK( 1 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );
  CHECK_THAT( -1.      , WithinRel( pdf.cosines()[0] ) );
  CHECK_THAT(  0.999999, WithinRel( pdf.cosines()[1] ) );
  CHECK_THAT( 0.5, WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 0.5, WithinRel( pdf.values()[1] ) );

  CHECK( false == chunk.hasCdf() );
  CHECK_THROWS( chunk.cdf() );
}
