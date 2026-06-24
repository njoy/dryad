// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/endf/write/resonances/lrf7/createParticlePairs.hpp"

// other includes
#include "njoy/constants.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunk();

SCENARIO( "createParticlePairs" ) {

  GIVEN( "valid data for a compound system" ) {

    std::string string = chunk();

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

      resonances::CompoundSystem compound( 1e-5, 1e+5,
                                           { { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,0+}" ),
                                                   neutron_pair, photon_pair, 0., 0, zero_radii },
                                                 { id::ChannelID( "n,Cu63->n,Cu63{1,1,0+}" ),
                                                   neutron_pair, neutron_pair, 0., -1, radii } },
                                               { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,0+}" ),
                                                   id::ChannelID( "n,Cu63->n,Cu63{1,1,0+}" ) },
                                                 { 2.216315e+3, 2.981944e+5 },
                                                 { { 1., 2. },
                                                   { 1.1, 2.1 } } },
                                               resonances::Formalism::ReichMoore,
                                               resonances::BoundaryCondition::Constant }, // 0+ spin group
                                             { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1-}" ),
                                                   neutron_pair, photon_pair, 0., 0, zero_radii },
                                                 { id::ChannelID( "n,Cu63->n,Cu63{0,1,1-}" ),
                                                   neutron_pair, neutron_pair, 0., 0, radii } },
                                               { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1-}" ),
                                                   id::ChannelID( "n,Cu63->n,Cu63{0,1,1-}" ) },
                                                 { -3.709301e+4, 3.282861e+5 },
                                                 { { 3., 4. },
                                                   { 3.1, 4.1 } } },
                                               resonances::Formalism::ReichMoore,
                                               resonances::BoundaryCondition::Constant }, // 1- spin group
                                             { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ),
                                                   neutron_pair, photon_pair, 0., 0, zero_radii },
                                                 { id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ),
                                                   neutron_pair, neutron_pair, 0., -1, radii },
                                                 { id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ),
                                                   neutron_pair, neutron_pair, 0., -1, radii } },
                                               { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1+}" ),
                                                   id::ChannelID( "n,Cu63->n,Cu63{1,1,1+}" ),
                                                   id::ChannelID( "n,Cu63->n,Cu63{1,2,1+}" ) },
                                                 { 3.811148e+3, 2.993903e+5 },
                                                 { { 5., 6. },
                                                   { 5.1, 6.1 },
                                                   { 5.2, 6.2 } } },
                                               resonances::Formalism::ReichMoore,
                                               resonances::BoundaryCondition::Constant }, // 1+ spin group
                                             { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,2-}" ),
                                                   neutron_pair, photon_pair, 0., 0, zero_radii },
                                                 { id::ChannelID( "n,Cu63->n,Cu63{0,2,2-}" ),
                                                   neutron_pair, neutron_pair, 0., 0, radii } },
                                               { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,2-}" ),
                                                   id::ChannelID( "n,Cu63->n,Cu63{0,2,2-}" ) },
                                                 { -5.334625e+4, 3.316735e+5 },
                                                 { { 7., 8. },
                                                   { 7.1, 8.1 } } },
                                               resonances::Formalism::ReichMoore,
                                               resonances::BoundaryCondition::Constant }, // 2- spin group
                                             { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,2+}" ),
                                                   neutron_pair, photon_pair, 0., 0, zero_radii },
                                                 { id::ChannelID( "n,Cu63->n,Cu63{1,1,2+}" ),
                                                   neutron_pair, neutron_pair, 0., -1, radii },
                                                 { id::ChannelID( "n,Cu63->n,Cu63{1,2,2+}" ),
                                                   neutron_pair, neutron_pair, 0., -1, radii } },
                                               { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,2+}" ),
                                                   id::ChannelID( "n,Cu63->n,Cu63{1,1,2+}" ),
                                                   id::ChannelID( "n,Cu63->n,Cu63{1,2,2+}" ) },
                                                 { 1.054117e+4, 2.989878e+5 },
                                                 { { 9., 10. },
                                                   { 9.1, 10.1 },
                                                   { 9.2, 10.2 } } },
                                               resonances::Formalism::ReichMoore,
                                               resonances::BoundaryCondition::Constant }, // 2+ spin group
                                             { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,3+}" ),
                                                   neutron_pair, photon_pair, 0., 0, zero_radii },
                                                 { id::ChannelID( "n,Cu63->n,Cu63{1,2,3+}" ),
                                                   neutron_pair, neutron_pair, 0., -1, radii } },
                                               { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,3+}" ),
                                                   id::ChannelID( "n,Cu63->n,Cu63{1,2,3+}" ) },
                                                 { 4.018230e+2, 3.006336e+5 },
                                                 { { 11., 12. },
                                                   { 11.1, 12.1 } } },
                                               resonances::Formalism::ReichMoore,
                                               resonances::BoundaryCondition::Constant } } ); // 3+ spin group

      THEN( "it can be converted to ENDF" ) {

        auto data = endf::write::resonances::lrf7::createParticlePairs( compound );

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
    " 0.000000+0 0.000000+0          2          0         24          42925 2151     \n"
    " 0.000000+0 6.338900+1 0.000000+0 2.900000+1 1.000000+0 0.000000+02925 2151     \n"
    " 0.000000+0-1.000000+0 1.000000+0 1.020000+2 0.000000+0 1.000000+02925 2151     \n"
    " 1.000000+0 6.238900+1 0.000000+0 2.900000+1 5.000000-1-1.500000+02925 2151     \n"
    " 0.000000+0 1.000000+0 1.000000+0 2.000000+0 0.000000+0 0.000000+02925 2151     \n";
}
