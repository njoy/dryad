// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/covariance/createCrossSectionCovarianceData.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;
using namespace njoy::ENDFtk;

SCENARIO( "createCrossSectionCovarianceData" ) {

  GIVEN( "a GENDF material" ) {

    using GTape = njoy::ENDFtk::tree::GTape;
    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_235.covariances.gendf" );
    auto material = tape.materials().front();

    WHEN( "constructing covariance matrices" ) {

      id::ParticleID projectile( "n" );
      id::ParticleID target( "U235" );
      bool relative = true;

      auto chunk = gendf::read::covariance::createCrossSectionCovarianceData( projectile, target, relative, material );

      THEN( "covariance matrices can be created and members can be tested" ) {

        id::ReactionID mt1( "n,U235->total" );
        id::ReactionID mt2( "n,U235->n(0)" );
        id::ReactionID mt4( "n,U235->n(t)" );
        id::ReactionID mt5( "n,U235->anything" );
        id::ReactionID mt16( "n,U235->2n(t)" );
        id::ReactionID mt17( "n,U235->3n(t)" );
        id::ReactionID mt18( "n,U235->fission" );
        id::ReactionID mt51( "n,U235->n(1)" );
        id::ReactionID mt102( "n,U235->g(t)" );
        id::ReactionID lumped1( "n,U235->lumped1" );
        id::ReactionID lumped2( "n,U235->lumped2" );

        CHECK( true == chunk.has_value() );

        CHECK( 11 == chunk->numberReactions() );
        CHECK( 11 == chunk->reactionIdentifiers().size() );
        CHECK( mt102 == chunk->reactionIdentifiers()[0] );
        CHECK( mt2 == chunk->reactionIdentifiers()[1] );
        CHECK( mt51 == chunk->reactionIdentifiers()[2] );
        CHECK( mt4 == chunk->reactionIdentifiers()[3] );
        CHECK( mt16 == chunk->reactionIdentifiers()[4] );
        CHECK( mt17 == chunk->reactionIdentifiers()[5] );
        CHECK( mt1 == chunk->reactionIdentifiers()[6] );
        CHECK( mt5 == chunk->reactionIdentifiers()[7] );
        CHECK( mt18 == chunk->reactionIdentifiers()[8] );
        CHECK( lumped1 == chunk->reactionIdentifiers()[9] );
        CHECK( lumped2 == chunk->reactionIdentifiers()[10] );

        CHECK( 66 == chunk->numberCovarianceMatrices() );
        CHECK( 66 == chunk->covariances().size() );

        CHECK( true == chunk->hasCovarianceMatrix( mt1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, mt2 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, mt4 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, mt5 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, mt16 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, mt17 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, mt18 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, mt51 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, mt102 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt1, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( mt2 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt2, mt4 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt2, mt5 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt2, mt16 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt2, mt17 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt2, mt18 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt2, mt51 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt2, mt102 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt2, lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt2, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( mt4 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt4, mt5 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt4, mt16 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt4, mt17 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt4, mt18 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt4, mt51 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt4, mt102 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt4, lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt4, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( mt5 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt5, mt16 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt5, mt17 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt5, mt18 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt5, mt51 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt5, mt102 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt5, lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt5, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( mt16 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt16, mt17 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt16, mt18 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt16, mt51 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt16, mt102 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt16, lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt16, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( mt17 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt17, mt18 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt17, mt51 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt17, mt102 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt17, lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt17, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( mt18 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt18, mt51 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt18, mt102 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt18, lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt18, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( mt51 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt51, mt102 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt51, lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt51, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( mt102 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt102, lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( mt102, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( lumped1 ) );
        CHECK( true == chunk->hasCovarianceMatrix( lumped1, lumped2 ) );

        CHECK( true == chunk->hasCovarianceMatrix( lumped2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
