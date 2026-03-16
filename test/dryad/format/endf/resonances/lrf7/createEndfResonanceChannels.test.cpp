// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfResonanceChannels.hpp"

// other includes
#include "njoy/constants.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

std::string chunk();

SCENARIO( "createEndfResonanceChannels" ) {

  GIVEN( "valid data for s spin group and particle pairs" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      auto photon = id::ParticleID::photon();
      auto neutron = id::ParticleID::neutron();
      auto proton = id::ParticleID::proton();
      auto cu63 = id::ParticleID( "Cu63" );
      auto cu64 = id::ParticleID( "Cu64[all]" );

      ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                Particle( cu64, 63.389 * njoy::constants::neutron_mass, 0, +1 ) );
      ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                 Particle( cu63, 62.389 * njoy::constants::neutron_mass, 1.5, -1 ) );

      ChannelRadii zero_radii( 0., 0. );
      ChannelRadii radii( 6.7, 6.7 );

      SpinGroup group( { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ),
                           neutron_pair, photon_pair, 0., 0, zero_radii },
                         { id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ),
                           neutron_pair, neutron_pair, 0., -1, radii },
                         { id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ),
                           neutron_pair, neutron_pair, 0., -1, radii } },
                       { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ),
                           id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ),
                           id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ) },
                         { 3.811148e+3, 2.993903e+5 },
                         { { 1., 2. },
                           { 1.1, 2.1 },
                           { 1.2, 2.2 } } },
                       Formalism::ReichMoore,
                       BoundaryCondition::ShiftFactor );

      njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs
      pairs( { 0., 1. }, { 63.389, 62.389 }, { 0., 0. }, { 29., 29. },
             { 1., 0.5 }, { 0., 1.5 }, { +1, +1 }, { +1, -1 },
             { 0., 0. }, { -1, 1 }, { 0, 0 }, { 102, 2 } );

      THEN( "it can be converted to ENDF" ) {

        auto data = format::endf::resonances::lrf7::createEndfResonanceChannels( group, pairs );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 2925, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+0 1.000000+0          0          0         18          32925 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0-1.000000+0 6.700000-1 6.700000-12925 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0-1.000000+0 6.700000-1 6.700000-12925 2151     \n";
}
