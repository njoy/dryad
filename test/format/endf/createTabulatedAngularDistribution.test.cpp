// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/endf/createTabulatedAngularDistribution.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// includes for test result generation
// #include <iostream>
// #include <iomanip>
// #include "scion/integration/GaussLegendre/64.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyNeutronChunk1( const TabulatedAngularDistribution& );
void verifyNeutronChunk2( const TabulatedAngularDistribution&, bool );
void verifyElectronChunk( const TabulatedAngularDistribution&, bool );

SCENARIO( "createTabulatedAngularDistribution" ) {

  GIVEN( "ENDF MF6 LAW = 2 TabulatedDistribution for an isotropic distribution" ) {

    using DiscreteTwoBodyScattering = njoy::ENDFtk::section::Type< 6 >::DiscreteTwoBodyScattering;
    using TabulatedDistribution = DiscreteTwoBodyScattering::TabulatedDistribution;

    auto tape = njoy::ENDFtk::tree::fromFile( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 6, 51 ).parse< 6 >();
    auto distribution = std::get< DiscreteTwoBodyScattering >( section.reactionProduct( 1 ).distribution() );

    WHEN( "a single parsed MF6 LAW = 2 distribution is given" ) {

      THEN( "it can be converted" ) {

        auto table = std::get< TabulatedDistribution >( distribution.distributions()[0] );
        auto chunk1 = format::endf::createTabulatedAngularDistribution( table, false );
        auto chunk2 = format::endf::createTabulatedAngularDistribution( table, true );

        verifyNeutronChunk1( chunk1 );
        verifyNeutronChunk1( chunk2 );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "ENDF MF6 LAW = 2 TabulatedDistribution" ) {

    using DiscreteTwoBodyScattering = njoy::ENDFtk::section::Type< 6 >::DiscreteTwoBodyScattering;
    using TabulatedDistribution = DiscreteTwoBodyScattering::TabulatedDistribution;

    auto tape = njoy::ENDFtk::tree::fromFile( "n-017_Cl_035.endf" );
    auto section = tape.materials().front().section( 6, 51 ).parse< 6 >();
    auto distribution = std::get< DiscreteTwoBodyScattering >( section.reactionProduct( 1 ).distribution() );

    WHEN( "a single parsed MF6 LAW = 2 distribution is given" ) {

      THEN( "it can be converted" ) {

        auto table = std::get< TabulatedDistribution >( distribution.distributions()[1] );
        auto chunk1 = format::endf::createTabulatedAngularDistribution( table, false );
        auto chunk2 = format::endf::createTabulatedAngularDistribution( table, true );

        verifyNeutronChunk2( chunk1, false );
        verifyNeutronChunk2( chunk2, true );
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

        auto chunk1 = format::endf::createTabulatedAngularDistribution( distribution.distributions()[0], false );
        auto chunk2 = format::endf::createTabulatedAngularDistribution( distribution.distributions()[0], true );

        verifyElectronChunk( chunk1, false );
        verifyElectronChunk( chunk2, true );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyNeutronChunk1( const TabulatedAngularDistribution& chunk ) {

  // this section is isotropic and properly normalised
  // note: this is also a special case for interpolation type = 14
  //       with 2 y values that are equal

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

  decltype(auto) cdf = chunk.cdf();
  CHECK( false == cdf.isLinearised() );
  CHECK( 2 == cdf.numberPoints() );
  CHECK( 1 == cdf.numberRegions() );
  CHECK( 2 == cdf.cosines().size() );
  CHECK( 2 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK( 1 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LogLinear == cdf.interpolants()[0] );
  CHECK_THAT( -1., WithinRel( cdf.cosines()[0] ) );
  CHECK_THAT(  1., WithinRel( cdf.cosines()[1] ) );
  CHECK_THAT( 0. , WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 1. , WithinRel( cdf.values()[1] ) );
}

void verifyNeutronChunk2( const TabulatedAngularDistribution& chunk, bool normalise ) {

  // generate test result using Gauss-Legendre quadrature
  // njoy::scion::integration::GaussLegendre< 64, double > integrator{};
  // auto thing = chunk.pdf();
  // std::cout << std::setprecision(15) << integrator( thing, -1., 0.22 ) << ' '
  //                                    << integrator( thing, -1., 0.22 )
  //                                     + integrator( thing, 0.22 , .92 ) << ' '
  //                                    << integrator( thing, -1., 0.22 )
  //                                     + integrator( thing, 0.22 , .92 )
  //                                     + integrator( thing, .92, 1. ) << std::endl;

  double normalisation = normalise ? 1.00000373695875 : 1.;

  decltype(auto) pdf = chunk.pdf();
  CHECK( false == pdf.isLinearised() );
  CHECK( 4 == pdf.numberPoints() );
  CHECK( 1 == pdf.numberRegions() );
  CHECK( 4 == pdf.cosines().size() );
  CHECK( 4 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK( 3 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LogLinear == pdf.interpolants()[0] );
  CHECK_THAT( -1.00, WithinRel( pdf.cosines()[0] ) );
  CHECK_THAT(  0.22, WithinRel( pdf.cosines()[1] ) );
  CHECK_THAT(  0.92, WithinRel( pdf.cosines()[2] ) );
  CHECK_THAT(  1.00, WithinRel( pdf.cosines()[3] ) );
  CHECK_THAT(  0.480214 / normalisation, WithinRel( pdf.values()[0] ) );
  CHECK_THAT(  0.503342 / normalisation, WithinRel( pdf.values()[1] ) );
  CHECK_THAT(  0.520972 / normalisation, WithinRel( pdf.values()[2] ) );
  CHECK_THAT(  0.520795 / normalisation, WithinRel( pdf.values()[3] ) );

  decltype(auto) cdf = chunk.cdf();
  CHECK( false == cdf.isLinearised() );
  CHECK( 4 == cdf.numberPoints() );
  CHECK( 1 == cdf.numberRegions() );
  CHECK( 4 == cdf.cosines().size() );
  CHECK( 4 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK( 3 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LogLinear == cdf.interpolants()[0] );
  CHECK_THAT( -1.00, WithinRel( cdf.cosines()[0] ) );
  CHECK_THAT(  0.22, WithinRel( cdf.cosines()[1] ) );
  CHECK_THAT(  0.92, WithinRel( cdf.cosines()[2] ) );
  CHECK_THAT(  1.00, WithinRel( cdf.cosines()[3] ) );
  CHECK_THAT(  0. / normalisation, WithinRel( cdf.values()[0] ) );
  CHECK_THAT(  0.599858561382975 / normalisation, WithinRel( cdf.values()[1] ) );
  CHECK_THAT(  0.958333057359721 / normalisation, WithinRel( cdf.values()[2] ) );
  CHECK_THAT(  1.00000373695875  / normalisation, WithinRel( cdf.values()[3] ) );
}

void verifyElectronChunk( const TabulatedAngularDistribution& chunk, bool normalise ) {

  double normalisation = normalise ? 1.999999 / 2. : 1.;

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
  CHECK_THAT( 0.5 / normalisation, WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 0.5 / normalisation, WithinRel( pdf.values()[1] ) );

  decltype(auto) cdf = chunk.cdf();
  CHECK( true == cdf.isLinearised() );
  CHECK( 2 == cdf.numberPoints() );
  CHECK( 1 == cdf.numberRegions() );
  CHECK( 2 == cdf.cosines().size() );
  CHECK( 2 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK( 1 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
  CHECK_THAT( -1.      , WithinRel( cdf.cosines()[0] ) );
  CHECK_THAT(  0.999999, WithinRel( cdf.cosines()[1] ) );
  CHECK_THAT( 0. / normalisation, WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 1.999999 / 2. / normalisation, WithinRel( cdf.values()[1] ) );
}
