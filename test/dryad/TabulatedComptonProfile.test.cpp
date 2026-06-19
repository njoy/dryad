// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/TabulatedComptonProfile.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const TabulatedComptonProfile&, bool );

SCENARIO( "TabulatedComptonProfile" ) {

  GIVEN( "momentum and probabilities for a table" ) {

    WHEN( "the data is given explicitly" ) {

      const id::ElectronSubshellID identifier( "1s" );
      const std::vector< double > momentum = { 0., 1., 1.5, 2. };
      const std::vector< double > values = { 0., 1., 1.5, 2. };

      TabulatedComptonProfile chunk1( identifier, momentum, values, InterpolationType::LinearLinear, false );
      TabulatedComptonProfile chunk2( std::move( identifier ), std::move( momentum ),
                                      std::move( values ), InterpolationType::LinearLinear, true );

      verifyChunk( chunk1, false );
      verifyChunk( chunk2, true );

      chunk1.normalise();
      chunk2.normalise();

      verifyChunk( chunk1, true );
      verifyChunk( chunk2, true );
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of TabulatedComptonProfile are given" ) {

      TabulatedComptonProfile left( { "1s" }, { 0., 2. }, { 0.5, 0.5 } );
      TabulatedComptonProfile equal( { "1s" }, { 0., 2. }, { 0.5, 0.5 } );
      TabulatedComptonProfile unnormalised( { "1s" }, { 0., 2. }, { 1., 1. }, InterpolationType::LinearLinear, true );
      TabulatedComptonProfile different( { "2s" }, { 0., 2. }, { 0.25, 0.75 } );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( true == ( left == unnormalised ) ); // normalised under the hood, so equal
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( false == ( left != unnormalised ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the cosine and values vector are not of the same length" ) {

      THEN( "an exception is thrown" ) {

        const id::ElectronSubshellID identifier( "1s" );
        const std::vector< double > momentum = { 0., 2. };
        const std::vector< double > values = { 0., 0.5, 0.75, 1. };

        CHECK_THROWS( TabulatedComptonProfile( identifier, momentum, values ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyChunk( const TabulatedComptonProfile& chunk, bool normalise ) {

  double normalisation = normalise ? 2.0 : 1.0;

  CHECK( id::ElectronSubshellID( "1s1/2" ) == chunk.subshellIdentifier() );

  CHECK( 4 == chunk.momentum().size() );
  CHECK( 4 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.momentum()[0] ) );
  CHECK_THAT( 1.  , WithinRel( chunk.momentum()[1] ) );
  CHECK_THAT( 1.5 , WithinRel( chunk.momentum()[2] ) );
  CHECK_THAT( 2.  , WithinRel( chunk.momentum()[3] ) );
  CHECK_THAT( 0.  / normalisation, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1.  / normalisation, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 1.5 / normalisation, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 2.  / normalisation, WithinRel( chunk.values()[3] ) );
  CHECK( 3 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

  auto pdf = chunk.pdf();
  CHECK_THAT( 0., WithinRel( pdf.lowerMomentumLimit() ) );
  CHECK_THAT( 2., WithinRel( pdf.upperMomentumLimit() ) );
  CHECK( 4 == pdf.momentum().size() );
  CHECK( 4 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK_THAT( 0.  , WithinRel( pdf.momentum()[0] ) );
  CHECK_THAT( 1.  , WithinRel( pdf.momentum()[1] ) );
  CHECK_THAT( 1.5 , WithinRel( pdf.momentum()[2] ) );
  CHECK_THAT( 2.  , WithinRel( pdf.momentum()[3] ) );
  CHECK_THAT( 0.  / normalisation, WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 1.  / normalisation, WithinRel( pdf.values()[1] ) );
  CHECK_THAT( 1.5 / normalisation, WithinRel( pdf.values()[2] ) );
  CHECK_THAT( 2.  / normalisation, WithinRel( pdf.values()[3] ) );
  CHECK( 3 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );

  auto cdf = chunk.cdf();
  CHECK_THAT( 0., WithinRel( cdf.lowerMomentumLimit() ) );
  CHECK_THAT( 2., WithinRel( cdf.upperMomentumLimit() ) );
  CHECK( 4 == cdf.momentum().size() );
  CHECK( 4 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK_THAT( 0.  , WithinRel( cdf.momentum()[0] ) );
  CHECK_THAT( 1.  , WithinRel( cdf.momentum()[1] ) );
  CHECK_THAT( 1.5 , WithinRel( cdf.momentum()[2] ) );
  CHECK_THAT( 2.  , WithinRel( cdf.momentum()[3] ) );
  CHECK_THAT( 0.    / normalisation, WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 0.5   / normalisation, WithinRel( cdf.values()[1] ) );
  CHECK_THAT( 1.125 / normalisation, WithinRel( cdf.values()[2] ) );
  CHECK_THAT( 2.    / normalisation, WithinRel( cdf.values()[3] ) );
  CHECK( 3 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );

  CHECK_THAT( 2.0 / normalisation, WithinRel( pdf.integral() ) );

  // evaluation

  // values of x in the x grid
  CHECK_THAT( 0.  / normalisation, WithinRel( chunk( 0.  ) ) );
  CHECK_THAT( 1.  / normalisation, WithinRel( chunk( 1.  ) ) );
  CHECK_THAT( 1.5 / normalisation, WithinRel( chunk( 1.5 ) ) );
  CHECK_THAT( 2.  / normalisation, WithinRel( chunk( 2.  ) ) );

  // values of x outside the x grid
  CHECK_THAT( 0., WithinRel( chunk( -5. ) ) );
  CHECK_THAT( 0., WithinRel( chunk(  5. ) ) );

  // values of x inside the x grid
  CHECK_THAT( 0.5  / normalisation, WithinRel( chunk( 0.5 ) ) );
  CHECK_THAT( 1.75 / normalisation, WithinRel( chunk( 1.75 ) ) );

  // average momentum - always the mean value even for unnormalised distributions
  CHECK_THAT( 8. / 3. / 2., WithinRel( chunk.averageMomentum() ) );

  // linearisation
  auto linear = chunk.linearise();

  pdf = linear.pdf();
  CHECK_THAT( 0., WithinRel( pdf.lowerMomentumLimit() ) );
  CHECK_THAT( 2., WithinRel( pdf.upperMomentumLimit() ) );
  CHECK( 4 == pdf.momentum().size() );
  CHECK( 4 == pdf.values().size() );
  CHECK( 1 == pdf.boundaries().size() );
  CHECK( 1 == pdf.interpolants().size() );
  CHECK_THAT( 0.  , WithinRel( pdf.momentum()[0] ) );
  CHECK_THAT( 1.  , WithinRel( pdf.momentum()[1] ) );
  CHECK_THAT( 1.5 , WithinRel( pdf.momentum()[2] ) );
  CHECK_THAT( 2.  , WithinRel( pdf.momentum()[3] ) );
  CHECK_THAT( 0.  / normalisation, WithinRel( pdf.values()[0] ) );
  CHECK_THAT( 1.  / normalisation, WithinRel( pdf.values()[1] ) );
  CHECK_THAT( 1.5 / normalisation, WithinRel( pdf.values()[2] ) );
  CHECK_THAT( 2.  / normalisation, WithinRel( pdf.values()[3] ) );
  CHECK( 3 == pdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );

  cdf = linear.cdf();
  CHECK_THAT( 0., WithinRel( cdf.lowerMomentumLimit() ) );
  CHECK_THAT( 2., WithinRel( cdf.upperMomentumLimit() ) );
  CHECK( 4 == cdf.momentum().size() );
  CHECK( 4 == cdf.values().size() );
  CHECK( 1 == cdf.boundaries().size() );
  CHECK( 1 == cdf.interpolants().size() );
  CHECK_THAT( 0.  , WithinRel( cdf.momentum()[0] ) );
  CHECK_THAT( 1.  , WithinRel( cdf.momentum()[1] ) );
  CHECK_THAT( 1.5 , WithinRel( cdf.momentum()[2] ) );
  CHECK_THAT( 2.  , WithinRel( cdf.momentum()[3] ) );
  CHECK_THAT( 0.    / normalisation, WithinRel( cdf.values()[0] ) );
  CHECK_THAT( 0.5   / normalisation, WithinRel( cdf.values()[1] ) );
  CHECK_THAT( 1.125 / normalisation, WithinRel( cdf.values()[2] ) );
  CHECK_THAT( 2.    / normalisation, WithinRel( cdf.values()[3] ) );
  CHECK( 3 == cdf.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
}
