// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/resonances/lrf7/createResonanceParameters.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunkWithReducedWidthAmplitudes();
std::string chunkWithFullWidths();

SCENARIO( "createResonanceParameters" ) {

  GIVEN( "valid data for resonance parameters" ) {

    WHEN( "the data is given explicitly" ) {

      auto photon = id::ParticleID::photon();
      auto neutron = id::ParticleID::neutron();
      auto proton = id::ParticleID::proton();
      auto cu63 = id::ParticleID( "Cu63" );
      auto cu64 = id::ParticleID( "Cu64[all]" );

      resonances::ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                            Particle( cu64, 63.389 * njoy::constants::neutron_mass, 0, +1 ) );
      resonances::ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                             Particle( cu63, 62.389 * njoy::constants::neutron_mass, 1.5, -1 ) );

      resonances::ChannelRadii zero_radii( 0., 0. );
      resonances::ChannelRadii radii( 6.7, 6.7 );

      resonances::SpinGroup group( { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ),
                                       neutron_pair, photon_pair, 0., 0, zero_radii },
                                     { id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ),
                                       neutron_pair, neutron_pair, 0., -1, radii },
                                     { id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ),
                                       neutron_pair, neutron_pair, 0., -1, radii } },
                                   { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ),
                                       id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ),
                                       id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ) },
                                     { -3.811148e+3, 2.993903e+5 },
                                     { { 1., 2. },
                                       { 1.1, -2.1 },
                                       { 1.2, 2.2 } } },
                                   resonances::Formalism::ReichMoore,
                                   resonances::BoundaryCondition::ShiftFactor );

      THEN( "it can be converted to ENDF using reduced width amplitudes" ) {

        auto data = endf::write::resonances::lrf7::createResonanceParameters( group, true );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 2925, 2, 151 );

        CHECK( buffer == chunkWithReducedWidthAmplitudes() );
      } // THEN

      THEN( "it can be converted to ENDF using full widths" ) {

        auto data = endf::write::resonances::lrf7::createResonanceParameters( group, false );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 2925, 2, 151 );

        CHECK( buffer == chunkWithFullWidths() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkWithReducedWidthAmplitudes() {

  return
    " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
    "-3.811148+3 1.000000+0 1.100000+0 1.200000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.993903+5 2.000000+0-2.100000+0 2.200000+0 0.000000+0 0.000000+02925 2151     \n";
}

std::string chunkWithFullWidths() {

  return
    " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
    "-3.811148+3 2.000000+0 1.717206-3 2.043617-3 0.000000+0 0.000000+02925 2151     \n"
    " 2.993903+5 8.000000+0-2.69759350 2.96062416 0.000000+0 0.000000+02925 2151     \n";
}
