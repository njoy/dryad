// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/createTabulatedScatteringFunction.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyCoherentChunk( const TabulatedScatteringFunction& );
void verifyIncoherentChunk( const TabulatedScatteringFunction& );

SCENARIO( "createTabulatedScatteringFunction" ) {

  GIVEN( "instances of photoatomic ACE CoherentFormFactorBlock and "
         "IncoherentScatteringFunctionBlock" ) {

    njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );
    auto coherent = table.coherentFormFactorBlock();
    auto incoherent = table.incoherentScatteringFunctionBlock();

    WHEN( "a single CoherentFormFactorBlock is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::ace::createTabulatedScatteringFunction( coherent );

        verifyCoherentChunk( chunk );
      } // THEN
    } // WHEN

    WHEN( "a single IncoherentScatteringFunctionBlock is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::ace::createTabulatedScatteringFunction( incoherent );

        verifyIncoherentChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyCoherentChunk( const TabulatedScatteringFunction& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 90 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 90 == chunk.inverseLengths().size() );
  CHECK( 90 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 89 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(          0, WithinRel( chunk.inverseLengths()[0] ) );
  CHECK_THAT(      0.001, WithinRel( chunk.inverseLengths()[1] ) );
  CHECK_THAT(       1e+6, WithinRel( chunk.inverseLengths()[88] ) );
  CHECK_THAT(       1e+9, WithinRel( chunk.inverseLengths()[89] ) );
  CHECK_THAT(          1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT(          1, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 8.1829e-27, WithinRel( chunk.values()[88] ) );
  CHECK_THAT( 8.1829e-39, WithinRel( chunk.values()[89] ) );
}

void verifyIncoherentChunk( const TabulatedScatteringFunction& chunk ) {

  CHECK( true == chunk.isLinearised() );
  CHECK( 94 == chunk.numberPoints() );
  CHECK( 1 == chunk.numberRegions() );
  CHECK( 94 == chunk.inverseLengths().size() );
  CHECK( 94 == chunk.values().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 93 == chunk.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
  CHECK_THAT(          0, WithinRel( chunk.inverseLengths()[0] ) );
  CHECK_THAT(       1e-7, WithinRel( chunk.inverseLengths()[1] ) );
  CHECK_THAT(       1e+6, WithinRel( chunk.inverseLengths()[92] ) );
  CHECK_THAT(       1e+9, WithinRel( chunk.inverseLengths()[93] ) );
  CHECK_THAT(          0, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 4.4097e-13, WithinRel( chunk.values()[1] ) );
  CHECK_THAT(          1, WithinRel( chunk.values()[92] ) );
  CHECK_THAT(          1, WithinRel( chunk.values()[93] ) );
}
