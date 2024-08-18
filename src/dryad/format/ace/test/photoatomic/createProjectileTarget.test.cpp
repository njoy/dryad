// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/ace/photoatomic/createProjectileTarget.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "createProjectileTarget" ) {

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::photoatomic::createProjectileTarget( table );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "1000.84p" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::photoatomic::createProjectileTarget( table );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "1000.12p" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        ProjectileTarget H0 = format::ace::photoatomic::createProjectileTarget( table );

        CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
        CHECK( id::ParticleID( "1000.14p" ) == H0.targetIdentifier() );

        CHECK( InteractionType::Atomic == H0.interactionType() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
