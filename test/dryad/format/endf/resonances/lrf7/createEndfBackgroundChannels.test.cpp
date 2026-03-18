// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfBackgroundChannels.hpp"

// other includes
#include "njoy/constants.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

std::string chunk();

SCENARIO( "createEndfBackgroundChannels" ) {

  GIVEN( "valid data for a spin group with background elements" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      auto photon = id::ParticleID::photon();
      auto neutron = id::ParticleID::neutron();
      auto sr88 = id::ParticleID( "Sr88" );
      auto sr89 = id::ParticleID( "Sr89[all]" );

      ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                Particle( sr89, 88.15046 * njoy::constants::neutron_mass, 0, +1 ) );
      ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                 Particle( sr88, 87.15046 * njoy::constants::neutron_mass, 0, +1 ) );

      ChannelRadii zero_radii( 0., 0. );
      ChannelRadii equal_radii( 7.1, 7.1 );

      SpinGroup group( { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                           neutron_pair, photon_pair, 0., 0, zero_radii },
                         { id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ),
                           neutron_pair, neutron_pair, 0., -1, equal_radii,
                           Kinematics::NonRelativistic,
                           SammyBackground( { 0.45, 3.2e-7, 0. }, { 0.075, 0. }, 0., 9.55e+5 ) } },
                       { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                           id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ) },
                         { 1.241000e+4, 8.331700e+5 },
                         { { 1., 2. },
                           { 1.1, 2.1 } } },
                       Formalism::ReichMoore,
                       BoundaryCondition::ShiftFactor );

      THEN( "it can be converted to ENDF" ) {

        auto data = format::endf::resonances::lrf7::createEndfBackgroundChannels( group );

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
