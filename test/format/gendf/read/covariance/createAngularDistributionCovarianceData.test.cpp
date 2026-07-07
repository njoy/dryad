// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/format/gendf/read/covariance/createAngularDistributionCovarianceData.hpp"

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;
using namespace njoy::ENDFtk;

SCENARIO( "createAngularDistributionCovarianceData" ) {

    GIVEN( "a GENDF material" ) {

    using GTape = njoy::ENDFtk::tree::GTape;
    auto tape = njoy::ENDFtk::tree::fromFile< GTape >( "n-092_U_238.angular_covariances.gendf" );
    auto material = tape.materials().front();

        WHEN( "constructing covariance matrices" ) {

            id::ParticleID projectile( "n" );
            id::ParticleID target( "U238" );
            auto frame = ReferenceFrame::Laboratory;

            auto chunk = gendf::read::covariance::createAngularDistributionCovarianceData( projectile, target, frame, material );

            THEN( "angular distribution covariance matrix can be created and members tested" ) {

                id::ReactionID mt2( "n,U238->n(0)" );

                CHECK( true == chunk.has_value() );

                CHECK( 1 == chunk->numberReactions() );
                CHECK( 1 == chunk->reactionIdentifiers().size() );
                CHECK( mt2 == chunk->reactionIdentifiers()[0] );

                CHECK( 1 == chunk->numberCovarianceMatrices() );
                CHECK( 1 == chunk->covariances().size() );
                CHECK( true == chunk->hasCovarianceMatrix( mt2 ) );

            } // THEN
        } // WHEN
    } // GIVEN
} // SCENARIO