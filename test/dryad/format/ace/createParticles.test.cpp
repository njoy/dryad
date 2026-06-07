// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/ace/createParticleDatabase.hpp"

// other includes
#include "ACEtk/fromFile.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"
#include "ACEtk/PhotoatomicTable.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

// convenience typedefs
using namespace njoy::dryad;

// include common test verification functions
#include "continuous/test_verification_functions.hpp"
#include "electroatomic/test_verification_functions.hpp"
#include "photoatomic/test_verification_functions.hpp"
#include "photonuclear/test_verification_functions.hpp"

SCENARIO( "createParticleDatabase" ) {

  GIVEN( "instances of ContinuousEnergyTable" ) {

    WHEN( "a Lib81 formatted table is given" ) {

      njoy::ACEtk::ContinuousEnergyTable table( njoy::ACEtk::fromFile( "1001.10c" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        id::ParticleID projectile( "n" );
        id::ParticleID target( "H1" );
        ParticleDatabase particles = format::ace::createParticleDatabase( projectile, target, table );
        continuous::lib81::h1::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of PhotoatomicTable" ) {

    WHEN( "an mcplib84 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.84p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        id::ParticleID projectile( "g" );
        id::ParticleID target( "H" );
        ParticleDatabase particles = format::ace::createParticleDatabase( projectile, target, table );
        photoatomic::mcplib84::h::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN

    WHEN( "an eprdata12 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.12p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H" );
        ParticleDatabase particles = format::ace::createParticleDatabase( projectile, target, table );
        electroatomic::eprdata12::h::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN

    WHEN( "an eprdata14 formatted table is given" ) {

      njoy::ACEtk::PhotoatomicTable table( njoy::ACEtk::fromFile( "1000.14p" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        id::ParticleID projectile( "e-" );
        id::ParticleID target( "H" );
        ParticleDatabase particles = format::ace::createParticleDatabase( projectile, target, table );
        electroatomic::eprdata14::h::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "instances of PhotonuclearTable" ) {

    WHEN( "an la150u formatted table is given" ) {

      njoy::ACEtk::PhotonuclearTable table( njoy::ACEtk::fromFile( "6012.24u" ) );

      THEN( "a ProjectileTarget can be derived" ) {

        id::ParticleID projectile( "g" );
        id::ParticleID target( "C12" );
        ParticleDatabase particles = format::ace::createParticleDatabase( projectile, target, table );
        photonuclear::la150u::c12::verifyParticleDatabase( particles );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
