// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/photoatomic/createTabulatedComptonProfile.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createTabulatedComptonProfile" ) {

  GIVEN( "instances of cdfs" ) {

    njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

    WHEN( "an instance of photoatomic ACE ComptonProfile" ) {

      id::ElectronSubshellID identifier( "1s1/2" );
      auto profile = table.comptonProfileBlock().value().comptonProfile( 1 );

      THEN( "a Compton profile can be derived" ) {

        auto chunk = format::ace::photoatomic::createTabulatedComptonProfile( identifier, profile );

        CHECK( id::ElectronSubshellID( "1s1/2" ) == chunk.subshellIdentifier() );

        CHECK( 31 == chunk.momentum().size() );
        CHECK( 31 == chunk.values().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 0.  , WithinRel( chunk.momentum().front() ) );
        CHECK_THAT( 100., WithinRel( chunk.momentum().back() ) );
        CHECK_THAT( 1.690581458877      , WithinRel( chunk.values().front() ) );
        CHECK_THAT( 5.17728126393395e-11, WithinRel( chunk.values().back() ) );
        CHECK( 30 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );

        auto pdf = chunk.pdf();
        CHECK_THAT( 0.  , WithinRel( pdf.lowerMomentumLimit() ) );
        CHECK_THAT( 100., WithinRel( pdf.upperMomentumLimit() ) );
        CHECK( 31 == pdf.momentum().size() );
        CHECK( 31 == pdf.values().size() );
        CHECK( 1 == pdf.boundaries().size() );
        CHECK( 1 == pdf.interpolants().size() );
        CHECK_THAT( 0.  , WithinRel( pdf.momentum().front() ) );
        CHECK_THAT( 100., WithinRel( pdf.momentum().back() ) );
        CHECK_THAT( 1.690581458877      , WithinRel( pdf.values().front() ) );
        CHECK_THAT( 5.17728126393395e-11, WithinRel( pdf.values().back() ) );
        CHECK( 30 == pdf.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == pdf.interpolants()[0] );

        auto cdf = chunk.cdf();
        CHECK_THAT( 0.  , WithinRel( cdf.lowerMomentumLimit() ) );
        CHECK_THAT( 100., WithinRel( cdf.upperMomentumLimit() ) );
        CHECK( 31 == cdf.momentum().size() );
        CHECK( 31 == cdf.values().size() );
        CHECK( 1 == cdf.boundaries().size() );
        CHECK( 1 == cdf.interpolants().size() );
        CHECK_THAT( 0.  , WithinRel( cdf.momentum().front() ) );
        CHECK_THAT( 100., WithinRel( cdf.momentum().back() ) );
        CHECK_THAT( 0., WithinRel( cdf.values().front() ) );
        CHECK_THAT( 1., WithinRel( cdf.values().back() ) );
        CHECK( 30 == cdf.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == cdf.interpolants()[0] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
