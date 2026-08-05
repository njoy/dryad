// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/resonances/lrf7/createBackgroundChannels.hpp"

// other includes
#include "njoy/constants.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk();

SCENARIO( "createBackgroundChannels" ) {

  GIVEN( "valid data for a spin group with background elements" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      auto photon = id::ParticleID::photon();
      auto neutron = id::ParticleID::neutron();
      auto sr88 = id::ParticleID( "Sr88" );
      auto sr89 = id::ParticleID( "Sr89[all]" );

      resonances::ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                            Particle( sr89, 88.15046 * njoy::constants::neutron_mass, 0, +1 ) );
      resonances::ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                             Particle( sr88, 87.15046 * njoy::constants::neutron_mass, 0, +1 ) );

      resonances::ChannelRadii zero_radii( 0., 0. );
      resonances::ChannelRadii equal_radii( 7.1, 7.1 );

      resonances::SpinGroup group( { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                                       neutron_pair, photon_pair, 0., 0, zero_radii, false },
                                     { id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ),
                                       neutron_pair, neutron_pair, 0., -1, equal_radii, true,
                                       resonances::Kinematics::NonRelativistic,
                                       resonances::SammyBackground( { 0.45, 3.2e-7, 0. }, { 0.075, 0. }, 0., 9.55e+5 ) } },
                                   { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                                       id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ) },
                                     { 1.241000e+4, 8.331700e+5 },
                                     { { 1., 2. },
                                       { 1.1, 2.1 } } },
                                   resonances::Formalism::ReichMoore,
                                   resonances::BoundaryCondition::ShiftFactor );

      THEN( "it can be converted to ENDF" ) {

        auto data = endf::write::resonances::lrf7::createBackgroundChannels( group );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 3837, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {

  return
    " 0.000000+0 0.000000+0          2          2          0          03837 2151     \n"
    " 0.000000+0 9.550000+5          0          0          5          03837 2151     \n"
    " 4.500000-1 3.200000-7 0.000000+0 7.500000-2 0.000000+0           3837 2151     \n";
}
