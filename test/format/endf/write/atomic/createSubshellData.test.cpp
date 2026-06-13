// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/atomic/createSubshellData.hpp"

// other includes
#include "njoy/dryad/atomic/ElectronSubshellConfiguration.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk();
std::string chunkWithoutTransitions();

SCENARIO( "createSubshellData" ) {

  GIVEN( "valid data for a subshell configuration without transitions" ) {

    std::string string = chunkWithoutTransitions();

    WHEN( "the data is given explicitly" ) {

      id::ElectronSubshellID id( "L1" );
      double energy = 28.48;
      double population = 2.;

      atomic::ElectronSubshellConfiguration chunk( std::move( id ), std::move( energy ),
                                                   std::move( population ) );

      THEN( "it can be converted to ENDF" ) {

        auto data = endf::write::atomic::createSubshellData( chunk );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 800, 28, 533 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a subshell configuration with transitions" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      id::ElectronSubshellID id( "K" );
      double energy = 538;
      double population = 2.;
      std::vector< atomic::RadiativeTransitionData > radiative = {

        atomic::RadiativeTransitionData( id::ElectronSubshellID( "L2" ), 0.00190768, 523.09 ),
        atomic::RadiativeTransitionData( id::ElectronSubshellID( "L3" ), 0.00380027, 523.13 )
      };
      std::vector< atomic::NonRadiativeTransitionData > nonradiative = {

        atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L1" ), 0.178644, 478.82 ),
        atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L2" ), 0.116224, 493.86 ),
        atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L1" ), id::ElectronSubshellID( "L3" ), 0.230418, 493.9 ),
        atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L2" ), 0.0110822, 508.9 ),
        atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L2" ), id::ElectronSubshellID( "L3" ), 0.291115, 508.94 ),
        atomic::NonRadiativeTransitionData( id::ElectronSubshellID( "L3" ), id::ElectronSubshellID( "L3" ), 0.166809, 508.98 )
      };

      atomic::ElectronSubshellConfiguration chunk( std::move( id ), std::move( energy ),
                                                   std::move( population ),
                                                   std::move( radiative ),
                                                   std::move( nonradiative ) );

      THEN( "it can be converted to ENDF" ) {

        auto data = endf::write::atomic::createSubshellData( chunk );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 800, 28, 533 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+0 0.000000+0          0          0         54          8 80028533     \n"
    " 5.380000+2 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 80028533     \n"
    " 3.000000+0 0.000000+0 5.230900+2 1.907680-3 0.000000+0 0.000000+0 80028533     \n"
    " 4.000000+0 0.000000+0 5.231300+2 3.800270-3 0.000000+0 0.000000+0 80028533     \n"
    " 2.000000+0 2.000000+0 4.788200+2 1.786440-1 0.000000+0 0.000000+0 80028533     \n"
    " 2.000000+0 3.000000+0 4.938600+2 1.162240-1 0.000000+0 0.000000+0 80028533     \n"
    " 2.000000+0 4.000000+0 4.939000+2 2.304180-1 0.000000+0 0.000000+0 80028533     \n"
    " 3.000000+0 3.000000+0 5.089000+2 1.108220-2 0.000000+0 0.000000+0 80028533     \n"
    " 3.000000+0 4.000000+0 5.089400+2 2.911150-1 0.000000+0 0.000000+0 80028533     \n"
    " 4.000000+0 4.000000+0 5.089800+2 1.668090-1 0.000000+0 0.000000+0 80028533     \n";
}

std::string chunkWithoutTransitions() {
  return
    " 2.000000+0 0.000000+0          0          0          6          0 80028533     \n"
    " 2.848000+1 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 80028533     \n";
}
