// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "njoy/dryad/format/gendf/covariance/createAngularDistributionCovarianceDataFromFile.hpp"

// other includes

// typedefs
using namespace njoy::dryad;

SCENARIO( "createAngularDistributionCovarianceDataFromFile" ) {

    GIVEN( "a GENDF material" ) {

        WHEN( "constructing covariance matrices" ) {

            auto chunk = format::gendf::covariance::createAngularDistributionCovarianceDataFromFile(
                id::ParticleID( "n" ), id::ParticleID( "U238" ),
                ReferenceFrame::Laboratory, "n-092_U_238.angular_covariances.gendf" );
        
            THEN( "angular covariance matrix can be created and members can be tested" ) {

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
} // SCENARIo