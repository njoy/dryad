// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/write/resonances/rmatrix/insertRMatrix.hpp"

// other includes
#include "njoy/constants.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::format;

std::string chunkSi29();
std::string chunkCu63();
std::string chunkCl35();
std::string chunkSr88();

SCENARIO( "insertRMatrix" ) {

  GIVEN( "valid data for a compound system - Si29" ) {

    // Si29 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - empty spin group that contribute only potential scattering

    auto photon = id::ParticleID::photon();
    auto neutron = id::ParticleID::neutron();
    auto si29 = id::ParticleID( "Si29" );
    auto si30 = id::ParticleID( "Si30[all]" );

    resonances::ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                          Particle( si30, 29.728 * njoy::constants::neutron_mass, 0, +1 ) );
    resonances::ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                           Particle( si29, 28.728 * njoy::constants::neutron_mass, 0.5, +1 ) );

    resonances::ChannelRadii zero_radii( 0., 0. );
    resonances::ChannelRadii radii( 4.221, 4.221 );

    resonances::CompoundSystem compound( 1e-5, 1.3e+6,
                                         { { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                             { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ) },
                                               { 3.740320e+5, 6.007182e+5 },
                                               { { 1., 2. },
                                                 { 1.1, 2.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 0- spin group
                                           { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0+}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Si29->n,Si29{0,0,0+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                             { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{0,0,0+}" ) },
                                               { -2.041700e+6, 2.248487e+6 },
                                               { { 3., 4. },
                                                 { 3.1, 4.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 0+ spin group
                                           { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Si29->n,Si29{1,0,1-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii },
                                               { id::ChannelID( "n,Si29->n,Si29{1,1,1-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                             { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1-}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{1,0,1-}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{1,1,1-}" ) },
                                               { 1.529411e+4, 1.240000e+6 },
                                               { { 5., 6. },
                                                 { 5.1, 6.1 },
                                                 { 5.2, 6.2 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 1- spin group
                                           { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1+}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Si29->n,Si29{0,1,1+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii },
                                               { id::ChannelID( "n,Si29->n,Si29{2,1,1+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                             { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1+}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{0,1,1+}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{2,1,1+}" ) },
                                               { 3.842219e+5, 1.388859e+6 },
                                               { { 7., 8. },
                                                 { 7.1, 8.1 },
                                                 { 7.2, 8.2 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 1+ spin group
                                           { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Si29->n,Si29{1,1,2-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                             { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2-}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{1,1,2-}" ) },
                                               { 3.883377e+4, 1.207629e+6 },
                                               { { 9., 10. },
                                                 { 9.1, 10.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 2- spin group
                                           { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2+}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Si29->n,Si29{2,0,2+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii },
                                               { id::ChannelID( "n,Si29->n,Si29{2,1,2+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                             { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2+}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{2,0,2+}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{2,1,2+}" ) } }, // empty table
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 2+ spin group
                                           { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,3+}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Si29->n,Si29{2,1,3+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                             { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,3+}" ),
                                                 id::ChannelID( "n,Si29->n,Si29{2,1,3+}" ) },
                                               { 6.203529e+5 },
                                               { { 11. },
                                                 { 11.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor } } ); // 3+ spin group

    std::map< id::ReactionID, double > qvalues = {

      { id::ReactionID( "n,Si29->g,Si30[all]" ), 0. }, { id::ReactionID( "n,Si29->n,Si29" ), 0. }
    };

    gnds::write::Options options;

    THEN( "a spinGroup node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertRMatrix( parent, options, compound, qvalues, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkSi29() );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for a compound system - Cu63" ) {

    // Cu63 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - 2 channels, neutron only, constant boundary condition

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
                                                 neutron_pair, photon_pair, 0., 0, zero_radii, false },
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
                                                 neutron_pair, photon_pair, 0., 0, zero_radii, false },
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
                                                 neutron_pair, photon_pair, 0., 0, zero_radii, false },
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
                                                 neutron_pair, photon_pair, 0., 0, zero_radii, false },
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
                                                 neutron_pair, photon_pair, 0., 0, zero_radii, false },
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
                                                 neutron_pair, photon_pair, 0., 0, zero_radii, false },
                                               { id::ChannelID( "n,Cu63->n,Cu63{1,2,3+}" ),
                                                 neutron_pair, neutron_pair, 0., -1, radii } },
                                             { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,3+}" ),
                                                 id::ChannelID( "n,Cu63->n,Cu63{1,2,3+}" ) },
                                               { 4.018230e+2, 3.006336e+5 },
                                               { { 11., 12. },
                                                 { 11.1, 12.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::Constant } } ); // 3+ spin group

    std::map< id::ReactionID, double > qvalues = {

      { id::ReactionID( "n,Cu63->g,Cu64[all]" ), 0. }, { id::ReactionID( "n,Cu63->n,Cu63" ), 0. }
    };

    gnds::write::Options options;

    THEN( "an rmatrix node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertRMatrix( parent, options, compound, qvalues, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkCu63() );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for a compound system - Cl35" ) {

    // Cl35 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - Z for n,gamma is set to 0.0 (should be 17.0)
    //                      - spin groups are not unique (1- and 2- occur
    //                        multiple times)
    // these only apply when reading the data

    auto photon = id::ParticleID::photon();
    auto neutron = id::ParticleID::neutron();
    auto proton = id::ParticleID::proton();
    auto cl35 = id::ParticleID( "Cl35" );
    auto cl35_e1 = id::ParticleID( "Cl35_e1" );
    auto cl36 = id::ParticleID( "Cl36[all]" );
    auto s35 = id::ParticleID( "S35" );

    resonances::ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                          Particle( cl36, 35.65932 * njoy::constants::neutron_mass, 0, +1 ) );
    resonances::ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                           Particle( cl35, 34.66845 * njoy::constants::neutron_mass, 1.5, +1 ) );
    resonances::ParticlePair proton_pair( Particle( proton, .9986235 * njoy::constants::neutron_mass, 0.5, +1 ),
                                          Particle( s35, 34.66863 * njoy::constants::neutron_mass, 1.5, +1 ) );

    resonances::ChannelRadii zero_radii( 0., 0. );
    resonances::ChannelRadii radii1( 4.822220, 4.888750 );
    resonances::ChannelRadii radii2( 4.822220, 3.667980 );

    resonances::CompoundSystem compound( 1e-5, 1.2e+6,
                                         { { { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii1 } },
                                             { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ),
                                                 id::ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ) },
                                               { 2.239640e+4, 5.478545e+5 },
                                               { { 1., 2. },
                                                 { 1.1, 2.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 0- spin group
                                           { { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii1 },
                                               { id::ChannelID( "n,Cl35->n,Cl35{1,2,1-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii1 },
                                               { id::ChannelID( "n,Cl35->p,S35{1,1,1-}" ),
                                                 neutron_pair, proton_pair, 615220., std::nullopt, radii1 },
                                               { id::ChannelID( "n,Cl35->p,S35{1,2,1-}" ),
                                                 neutron_pair, proton_pair, 615220., std::nullopt, radii1 } },
                                             { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ),
                                                 id::ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ),
                                                 id::ChannelID( "n,Cl35->n,Cl35{1,2,1-}" ),
                                                 id::ChannelID( "n,Cl35->p,S35{1,1,1-}" ),
                                                 id::ChannelID( "n,Cl35->p,S35{1,2,1-}" ) },
                                               { 4.250762e+3, 1.435502e+6 },
                                               { { 3., 4. },
                                                 { 3.1, 4.1 },
                                                 { 3.2, 4.2 },
                                                 { 3.3, 4.3 },
                                                 { 3.4, 4.4 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 1- spingroup
                                           { { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii2 },
                                               { id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ),
                                                 neutron_pair, proton_pair, 615220., std::nullopt, radii2 } },
                                             { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                                                 id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                                                 id::ChannelID( "n,Cl35->p,S35{0,1,1+}" ) },
                                               { 5.493200e+4, 1.205687e+6 },
                                               { { 5., 6. },
                                                 { 5.1, 6.1 },
                                                 { 5.2, 6.2 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 1+ spingroup
                                           { { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,2-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Cl35->n,Cl35{1,1,2-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii1 },
                                               { id::ChannelID( "n,Cl35->n,Cl35{1,2,2-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii1 },
                                               { id::ChannelID( "n,Cl35->p,S35{1,1,2-}" ),
                                                 neutron_pair, proton_pair, 615220., std::nullopt, radii1 },
                                               { id::ChannelID( "n,Cl35->p,S35{1,2,2-}" ),
                                                 neutron_pair, proton_pair, 615220., std::nullopt, radii1 } },
                                             { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,2-}" ),
                                                 id::ChannelID( "n,Cl35->n,Cl35{1,1,2-}" ),
                                                 id::ChannelID( "n,Cl35->n,Cl35{1,2,2-}" ),
                                                 id::ChannelID( "n,Cl35->p,S35{1,1,2-}" ),
                                                 id::ChannelID( "n,Cl35->p,S35{1,2,2-}" ) },
                                               { -3.369334e+5, 1.441365e+6 },
                                               { { 7., 8. },
                                                 { 7.1, 8.1 },
                                                 { 7.2, 8.2 },
                                                 { 7.3, 8.3 },
                                                 { 7.4, 8.4 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 2- spingroup
                                           { { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii2 },
                                               { id::ChannelID( "n,Cl35->p,S35{0,2,2+}" ),
                                                 neutron_pair, proton_pair, 615220., std::nullopt, radii2 } },
                                             { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
                                                 id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ),
                                                 id::ChannelID( "n,Cl35->p,S35{0,2,2+}" ) },
                                               { -1.806500e+2, 7.563145e+6 },
                                               { { 9., 10. },
                                                 { 9.1, 10.1 },
                                                 { 9.2, 10.2 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 2+ spin group
                                           { { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,3-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Cl35->n,Cl35{1,2,3-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, radii1 },
                                               { id::ChannelID( "n,Cl35->p,S35{1,2,3-}" ),
                                                 neutron_pair, proton_pair, 615220., std::nullopt, radii1 } },
                                             { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,3-}" ),
                                                 id::ChannelID( "n,Cl35->n,Cl35{1,2,3-}" ),
                                                 id::ChannelID( "n,Cl35->p,S35{1,2,3-}" ) },
                                               { 1.635612e+4, 1.485128e+6 },
                                               { { 11., 12. },
                                                 { 11.1, 12.1 },
                                                 { 11.2, 12.2 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor } } ); // 3- spin group

    std::map< id::ReactionID, double > qvalues = {

      { id::ReactionID( "n,Cl35->g,Cl36[all]" ), 0. }, { id::ReactionID( "n,Cl35->n,Cl35" ), 0. },
      { id::ReactionID( "n,Cl35->p,S35" ), 615220. }
    };

    gnds::write::Options options;

    THEN( "an rmatrix node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertRMatrix( parent, options, compound, qvalues, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkCl35() );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for a compound system - Sr88" ) {

    // Sr88 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - Sammy parametrisation for channel background

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
    resonances::ChannelRadii different_radii( 7.1, 6.8 );

    resonances::CompoundSystem compound( 1e-5, 9.5e+5,
                                         { { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, equal_radii, true,
                                                 resonances::Kinematics::NonRelativistic,
                                                 resonances::SammyBackground( { 0.45, 3.2e-7, 0. }, { 0.075, 0. }, 0., 9.55e+5 ) } },
                                             { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                                                 id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ) },
                                               { 1.241000e+4, 8.331700e+5 },
                                               { { 1., 2. },
                                                 { 1.1, 2.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 1/2- spin group
                                           { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2+}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Sr88->n,Sr88{0,1/2,1/2+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, different_radii, true,
                                                 resonances::Kinematics::NonRelativistic,
                                                 resonances::SammyBackground( { -0.043, 2.8e-8, 0. }, { 0.01, 0. }, 0., 9.55e+5 ) } },
                                             { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2+}" ),
                                                 id::ChannelID( "n,Sr88->n,Sr88{0,1/2,1/2+}" ) },
                                               { 1.3840e+4, 9.4334e+5 },
                                               { { 3., 4. },
                                                 { 3.1, 4.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 1/2+ spin group
                                           { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Sr88->n,Sr88{1,1/2,3/2-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, equal_radii, true,
                                                 resonances::Kinematics::NonRelativistic,
                                                 resonances::SammyBackground( { 0.43, -1.8e-7, 0. }, { 0.22, 0. }, 0., 9.55e+5 ) } },
                                             { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2-}" ),
                                                 id::ChannelID( "n,Sr88->n,Sr88{1,1/2,3/2-}" ) },
                                               { 1.8210e+4, 9.4823e+5 },
                                               { { 5., 6. },
                                                 { 5.1, 6.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 3/2- spin group
                                           { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2+}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Sr88->n,Sr88{2,1/2,3/2+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, equal_radii, true,
                                                 resonances::Kinematics::NonRelativistic,
                                                 resonances::SammyBackground( { -0.7, 2.3e-6, 0. }, { 0.041, 0. }, 0., 9.55e+5 ) } },
                                             { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2+}" ),
                                                 id::ChannelID( "n,Sr88->n,Sr88{2,1/2,3/2+}" ) },
                                               { 2.6653e+5, 8.7494e+5 },
                                               { { 7., 8. },
                                                 { 7.1, 8.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 3/2+ spin group
                                           { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Sr88->n,Sr88{3,1/2,5/2-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, equal_radii, true,
                                                 resonances::Kinematics::NonRelativistic,
                                                 resonances::SammyBackground( { 0.001, 4.6e-7, 0. }, { 0.24, 0. }, 0., 9.55e+5 ) } },
                                             { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2-}" ),
                                                 id::ChannelID( "n,Sr88->n,Sr88{3,1/2,5/2-}" ) },
                                               { 4.0846e+5, 8.9944e+5 },
                                               { { 9., 10. },
                                                 { 9.1, 10.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 5/2- spin group
                                           { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2+}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Sr88->n,Sr88{2,1/2,5/2+}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, equal_radii, true,
                                                 resonances::Kinematics::NonRelativistic,
                                                 resonances::SammyBackground( { -2.5, 3.3e-6, 0. }, { 0.0026, 0. }, 0., 9.55e+5 ) } },
                                             { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2+}" ),
                                                 id::ChannelID( "n,Sr88->n,Sr88{2,1/2,5/2+}" ) },
                                               { 4.0982e+5, 8.4961e+5 },
                                               { { 11., 12. },
                                                 { 11.1, 12.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor }, // 5/2+ spin group
                                           { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,7/2-}" ),
                                                 neutron_pair, photon_pair, 0., std::nullopt, zero_radii, false },
                                               { id::ChannelID( "n,Sr88->n,Sr88{3,1/2,7/2-}" ),
                                                 neutron_pair, neutron_pair, 0., std::nullopt, equal_radii, true,
                                                 resonances::Kinematics::NonRelativistic,
                                                 resonances::SammyBackground( { 0.001, 9e-8, 0. }, { 0.19, 0. }, 0., 9.55e+5 ) } },
                                             { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,7/2-}" ),
                                                 id::ChannelID( "n,Sr88->n,Sr88{3,1/2,7/2-}" ) },
                                               { 5.2884e+5, 9.4756e+5 },
                                               { { 13., 14. },
                                                 { 13.1, 14.1 } } },
                                             resonances::Formalism::ReichMoore,
                                             resonances::BoundaryCondition::ShiftFactor } } ); // 7/2- spin group

    std::map< id::ReactionID, double > qvalues = {

      { id::ReactionID( "n,Sr88->g,Sr89[all]" ), 0. }, { id::ReactionID( "n,Sr88->n,Sr88" ), 0. }
    };

    gnds::write::Options options;

    THEN( "an rmatrix node can be inserted" ) {

      pugi::xml_document parent;
      auto node = gnds::write::resonances::rmatrix::insertRMatrix( parent, options, compound, qvalues, "eval" );

      std::ostringstream out;
      node.print( out, "  " );
      CHECK( out.str() == chunkSr88() );
    } // THEN
  } // GIVEN
} // SCENARIO

std::string chunkSi29() {

  return
    "<RMatrix label=\"eval\" approximation=\"ReichMoore\" boundaryCondition=\"EliminateShiftFunction\" reducedWidthAmplitudes=\"true\">\n"
    "  <PoPs name=\"particles\" version=\"1.0\" format=\"2.1\">\n"
    "    <gaugeBosons>\n"
    "      <gaugeBoson id=\"g\">\n"
    "        <mass>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"amu\" />\n"
    "        </mass>\n"
    "        <spin>\n"
    "          <fraction label=\"eval\" value=\"1\" unit=\"hbar\" />\n"
    "        </spin>\n"
    "        <parity>\n"
    "          <integer label=\"eval\" value=\"1\" />\n"
    "        </parity>\n"
    "        <charge>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "        </charge>\n"
    "      </gaugeBoson>\n"
    "    </gaugeBosons>\n"
    "    <baryons>\n"
    "      <baryon id=\"n\">\n"
    "        <mass>\n"
    "          <double label=\"eval\" value=\"1.00866491606\" unit=\"amu\" />\n"
    "        </mass>\n"
    "        <spin>\n"
    "          <fraction label=\"eval\" value=\"1/2\" unit=\"hbar\" />\n"
    "        </spin>\n"
    "        <parity>\n"
    "          <integer label=\"eval\" value=\"1\" />\n"
    "        </parity>\n"
    "        <charge>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "        </charge>\n"
    "      </baryon>\n"
    "    </baryons>\n"
    "    <chemicalElements>\n"
    "      <chemicalElement symbol=\"Si\" Z=\"14\" name=\"Silicon\">\n"
    "        <isotopes>\n"
    "          <isotope symbol=\"Si29\" A=\"29\">\n"
    "            <nuclides>\n"
    "              <nuclide id=\"Si29\">\n"
    "                <mass>\n"
    "                  <double label=\"eval\" value=\"28.97692570857\" unit=\"amu\" />\n"
    "                </mass>\n"
    "                <charge>\n"
    "                  <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "                </charge>\n"
    "                <nucleus id=\"si29\">\n"
    "                  <spin>\n"
    "                    <fraction label=\"eval\" value=\"1/2\" unit=\"hbar\" />\n"
    "                  </spin>\n"
    "                  <parity>\n"
    "                    <integer label=\"eval\" value=\"1\" />\n"
    "                  </parity>\n"
    "                  <charge>\n"
    "                    <double label=\"eval\" value=\"14\" unit=\"e\" />\n"
    "                  </charge>\n"
    "                </nucleus>\n"
    "              </nuclide>\n"
    "            </nuclides>\n"
    "          </isotope>\n"
    "          <isotope symbol=\"Si30\" A=\"30\">\n"
    "            <nuclides>\n"
    "              <nuclide id=\"Si30[all]\">\n"
    "                <mass>\n"
    "                  <double label=\"eval\" value=\"29.98559062463\" unit=\"amu\" />\n"
    "                </mass>\n"
    "                <charge>\n"
    "                  <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "                </charge>\n"
    "                <nucleus id=\"si30[all]\">\n"
    "                  <spin>\n"
    "                    <fraction label=\"eval\" value=\"0\" unit=\"hbar\" />\n"
    "                  </spin>\n"
    "                  <parity>\n"
    "                    <integer label=\"eval\" value=\"1\" />\n"
    "                  </parity>\n"
    "                  <charge>\n"
    "                    <double label=\"eval\" value=\"14\" unit=\"e\" />\n"
    "                  </charge>\n"
    "                </nucleus>\n"
    "              </nuclide>\n"
    "            </nuclides>\n"
    "          </isotope>\n"
    "        </isotopes>\n"
    "      </chemicalElement>\n"
    "    </chemicalElements>\n"
    "  </PoPs>\n"
    "  <resonanceReactions>\n"
    "    <resonanceReaction label=\"n,Si29->g,Si30[all]\" ejectile=\"g\" eliminated=\"true\">\n"
    "      <link href=\"/reactionSuite/reactions/reaction[@label='n,Si29->g,Si30[all]']\" />\n"
    "      <Q>\n"
    "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "          <axes>\n"
    "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
    "          </axes>\n"
    "        </constant1d>\n"
    "      </Q>\n"
    "    </resonanceReaction>\n"
    "    <resonanceReaction label=\"n,Si29->n,Si29\" ejectile=\"n\">\n"
    "      <link href=\"/reactionSuite/reactions/reaction[@label='n,Si29->n,Si29']\" />\n"
    "      <Q>\n"
    "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "          <axes>\n"
    "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
    "          </axes>\n"
    "        </constant1d>\n"
    "      </Q>\n"
    "    </resonanceReaction>\n"
    "  </resonanceReactions>\n"
    "  <spinGroups>\n"
    "    <spinGroup label=\"0-\" spin=\"0\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Si29->g,Si30[all]{0,0,0-}\" resonanceReaction=\"n,Si29->g,Si30[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{1,1,0-}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"1\" channelSpin=\"1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Si29->g,Si30[all]{0,0,0-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Si29->n,Si29{1,1,0-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            374032 1 1.1\n"
    "            600718.2 2 2.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"0+\" spin=\"0\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Si29->g,Si30[all]{0,0,0+}\" resonanceReaction=\"n,Si29->g,Si30[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{0,0,0+}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"0\" channelSpin=\"0\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Si29->g,Si30[all]{0,0,0-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Si29->n,Si29{0,0,0+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            -2041700 3 3.1\n"
    "            2248487 4 4.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"1-\" spin=\"1\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Si29->g,Si30[all]{0,0,1-}\" resonanceReaction=\"n,Si29->g,Si30[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{1,0,1-}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"1\" channelSpin=\"0\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{1,1,1-}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"1\" channelSpin=\"1\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"4\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Si29->g,Si30[all]{0,0,1-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Si29->n,Si29{1,0,1-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Si29->n,Si29{1,1,1-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            15294.11 5 5.1 5.2\n"
    "            1240000 6 6.1 6.2\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"1+\" spin=\"1\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Si29->g,Si30[all]{0,0,1+}\" resonanceReaction=\"n,Si29->g,Si30[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{0,1,1+}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"0\" channelSpin=\"1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{2,1,1+}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"2\" channelSpin=\"1\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"4\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Si29->g,Si30[all]{0,0,1+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Si29->n,Si29{0,1,1+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Si29->n,Si29{2,1,1+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            384221.9 7 7.1 7.2\n"
    "            1388859 8 8.1 8.2\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"2-\" spin=\"2\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Si29->g,Si30[all]{0,0,2-}\" resonanceReaction=\"n,Si29->g,Si30[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{1,1,2-}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"1\" channelSpin=\"1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Si29->g,Si30[all]{0,0,2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Si29->n,Si29{1,1,2-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            38833.77 9 9.1\n"
    "            1207629 10 10.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"2+\" spin=\"2\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Si29->g,Si30[all]{0,0,2+}\" resonanceReaction=\"n,Si29->g,Si30[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{2,0,2+}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"2\" channelSpin=\"0\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{2,1,2+}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"2\" channelSpin=\"1\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"0\" columns=\"4\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Si29->g,Si30[all]{0,0,2+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Si29->n,Si29{2,0,2+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Si29->n,Si29{2,1,2+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"3+\" spin=\"3\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Si29->g,Si30[all]{0,0,3+}\" resonanceReaction=\"n,Si29->g,Si30[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Si29->n,Si29{2,1,3+}\" resonanceReaction=\"n,Si29->n,Si29\" L=\"2\" channelSpin=\"1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.221\" domainMin=\"1e-05\" domainMax=\"1300000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"1\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Si29->g,Si30[all]{0,0,3+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Si29->n,Si29{2,1,3+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            620352.9 11 11.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "  </spinGroups>\n"
    "</RMatrix>\n";
}

std::string chunkCu63() {

  return
    "<RMatrix label=\"eval\" approximation=\"ReichMoore\" boundaryCondition=\"Given\" reducedWidthAmplitudes=\"true\">\n"
    "  <PoPs name=\"particles\" version=\"1.0\" format=\"2.1\">\n"
    "    <gaugeBosons>\n"
    "      <gaugeBoson id=\"g\">\n"
    "        <mass>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"amu\" />\n"
    "        </mass>\n"
    "        <spin>\n"
    "          <fraction label=\"eval\" value=\"1\" unit=\"hbar\" />\n"
    "        </spin>\n"
    "        <parity>\n"
    "          <integer label=\"eval\" value=\"1\" />\n"
    "        </parity>\n"
    "        <charge>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "        </charge>\n"
    "      </gaugeBoson>\n"
    "    </gaugeBosons>\n"
    "    <baryons>\n"
    "      <baryon id=\"n\">\n"
    "        <mass>\n"
    "          <double label=\"eval\" value=\"1.00866491606\" unit=\"amu\" />\n"
    "        </mass>\n"
    "        <spin>\n"
    "          <fraction label=\"eval\" value=\"1/2\" unit=\"hbar\" />\n"
    "        </spin>\n"
    "        <parity>\n"
    "          <integer label=\"eval\" value=\"1\" />\n"
    "        </parity>\n"
    "        <charge>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "        </charge>\n"
    "      </baryon>\n"
    "    </baryons>\n"
    "    <chemicalElements>\n"
    "      <chemicalElement symbol=\"Cu\" Z=\"29\" name=\"Copper\">\n"
    "        <isotopes>\n"
    "          <isotope symbol=\"Cu63\" A=\"63\">\n"
    "            <nuclides>\n"
    "              <nuclide id=\"Cu63\">\n"
    "                <mass>\n"
    "                  <double label=\"eval\" value=\"62.92959544807\" unit=\"amu\" />\n"
    "                </mass>\n"
    "                <charge>\n"
    "                  <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "                </charge>\n"
    "                <nucleus id=\"cu63\">\n"
    "                  <spin>\n"
    "                    <fraction label=\"eval\" value=\"3/2\" unit=\"hbar\" />\n"
    "                  </spin>\n"
    "                  <parity>\n"
    "                    <integer label=\"eval\" value=\"-1\" />\n"
    "                  </parity>\n"
    "                  <charge>\n"
    "                    <double label=\"eval\" value=\"29\" unit=\"e\" />\n"
    "                  </charge>\n"
    "                </nucleus>\n"
    "              </nuclide>\n"
    "            </nuclides>\n"
    "          </isotope>\n"
    "          <isotope symbol=\"Cu64\" A=\"64\">\n"
    "            <nuclides>\n"
    "              <nuclide id=\"Cu64[all]\">\n"
    "                <mass>\n"
    "                  <double label=\"eval\" value=\"63.93826036413\" unit=\"amu\" />\n"
    "                </mass>\n"
    "                <charge>\n"
    "                  <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "                </charge>\n"
    "                <nucleus id=\"cu64[all]\">\n"
    "                  <spin>\n"
    "                    <fraction label=\"eval\" value=\"0\" unit=\"hbar\" />\n"
    "                  </spin>\n"
    "                  <parity>\n"
    "                    <integer label=\"eval\" value=\"1\" />\n"
    "                  </parity>\n"
    "                  <charge>\n"
    "                    <double label=\"eval\" value=\"29\" unit=\"e\" />\n"
    "                  </charge>\n"
    "                </nucleus>\n"
    "              </nuclide>\n"
    "            </nuclides>\n"
    "          </isotope>\n"
    "        </isotopes>\n"
    "      </chemicalElement>\n"
    "    </chemicalElements>\n"
    "  </PoPs>\n"
    "  <resonanceReactions>\n"
    "    <resonanceReaction label=\"n,Cu63->g,Cu64[all]\" ejectile=\"g\" eliminated=\"true\">\n"
    "      <link href=\"/reactionSuite/reactions/reaction[@label='n,Cu63->g,Cu64[all]']\" />\n"
    "      <Q>\n"
    "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "          <axes>\n"
    "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
    "          </axes>\n"
    "        </constant1d>\n"
    "      </Q>\n"
    "    </resonanceReaction>\n"
    "    <resonanceReaction label=\"n,Cu63->n,Cu63\" ejectile=\"n\">\n"
    "      <link href=\"/reactionSuite/reactions/reaction[@label='n,Cu63->n,Cu63']\" />\n"
    "      <Q>\n"
    "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "          <axes>\n"
    "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
    "          </axes>\n"
    "        </constant1d>\n"
    "      </Q>\n"
    "    </resonanceReaction>\n"
    "  </resonanceReactions>\n"
    "  <spinGroups>\n"
    "    <spinGroup label=\"0+\" spin=\"0\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cu63->g,Cu64[all]{0,0,0+}\" resonanceReaction=\"n,Cu63->g,Cu64[all]\" L=\"0\" channelSpin=\"0\" boundaryConditionValue=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cu63->n,Cu63{1,1,0+}\" resonanceReaction=\"n,Cu63->n,Cu63\" L=\"1\" channelSpin=\"1\" boundaryConditionValue=\"-1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"6.7\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cu63->g,Cu64[all]{0,0,0+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cu63->n,Cu63{1,1,0+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            2216.315 1 1.1\n"
    "            298194.4 2 2.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"1-\" spin=\"1\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cu63->g,Cu64[all]{0,0,1-}\" resonanceReaction=\"n,Cu63->g,Cu64[all]\" L=\"0\" channelSpin=\"0\" boundaryConditionValue=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cu63->n,Cu63{0,1,1-}\" resonanceReaction=\"n,Cu63->n,Cu63\" L=\"0\" channelSpin=\"1\" boundaryConditionValue=\"0\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"6.7\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cu63->g,Cu64[all]{0,0,1-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cu63->n,Cu63{0,1,1-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            -37093.01 3 3.1\n"
    "            328286.1 4 4.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"1+\" spin=\"1\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cu63->g,Cu64[all]{0,0,1+}\" resonanceReaction=\"n,Cu63->g,Cu64[all]\" L=\"0\" channelSpin=\"0\" boundaryConditionValue=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cu63->n,Cu63{1,1,1+}\" resonanceReaction=\"n,Cu63->n,Cu63\" L=\"1\" channelSpin=\"1\" boundaryConditionValue=\"-1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"6.7\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cu63->n,Cu63{1,2,1+}\" resonanceReaction=\"n,Cu63->n,Cu63\" L=\"1\" channelSpin=\"2\" boundaryConditionValue=\"-1\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"6.7\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"4\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cu63->g,Cu64[all]{0,0,1+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cu63->n,Cu63{1,1,1+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Cu63->n,Cu63{1,2,1+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            3811.148 5 5.1 5.2\n"
    "            299390.3 6 6.1 6.2\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"2-\" spin=\"2\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cu63->g,Cu64[all]{0,0,2-}\" resonanceReaction=\"n,Cu63->g,Cu64[all]\" L=\"0\" channelSpin=\"0\" boundaryConditionValue=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cu63->n,Cu63{0,2,2-}\" resonanceReaction=\"n,Cu63->n,Cu63\" L=\"0\" channelSpin=\"2\" boundaryConditionValue=\"0\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"6.7\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cu63->g,Cu64[all]{0,0,2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cu63->n,Cu63{0,2,2-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            -53346.25 7 7.1\n"
    "            331673.5 8 8.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"2+\" spin=\"2\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cu63->g,Cu64[all]{0,0,2+}\" resonanceReaction=\"n,Cu63->g,Cu64[all]\" L=\"0\" channelSpin=\"0\" boundaryConditionValue=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cu63->n,Cu63{1,1,2+}\" resonanceReaction=\"n,Cu63->n,Cu63\" L=\"1\" channelSpin=\"1\" boundaryConditionValue=\"-1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"6.7\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cu63->n,Cu63{1,2,2+}\" resonanceReaction=\"n,Cu63->n,Cu63\" L=\"1\" channelSpin=\"2\" boundaryConditionValue=\"-1\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"6.7\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"4\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cu63->g,Cu64[all]{0,0,2+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cu63->n,Cu63{1,1,2+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Cu63->n,Cu63{1,2,2+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            10541.17 9 9.1 9.2\n"
    "            298987.8 10 10.1 10.2\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"3+\" spin=\"3\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cu63->g,Cu64[all]{0,0,3+}\" resonanceReaction=\"n,Cu63->g,Cu64[all]\" L=\"0\" channelSpin=\"0\" boundaryConditionValue=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cu63->n,Cu63{1,2,3+}\" resonanceReaction=\"n,Cu63->n,Cu63\" L=\"1\" channelSpin=\"2\" boundaryConditionValue=\"-1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"6.7\" domainMin=\"1e-05\" domainMax=\"100000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cu63->g,Cu64[all]{0,0,3+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cu63->n,Cu63{1,2,3+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            401.823 11 11.1\n"
    "            300633.6 12 12.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "  </spinGroups>\n"
    "</RMatrix>\n";
}

std::string chunkCl35() {

  return
    "<RMatrix label=\"eval\" approximation=\"ReichMoore\" boundaryCondition=\"EliminateShiftFunction\" reducedWidthAmplitudes=\"true\">\n"
    "  <PoPs name=\"particles\" version=\"1.0\" format=\"2.1\">\n"
    "    <gaugeBosons>\n"
    "      <gaugeBoson id=\"g\">\n"
    "        <mass>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"amu\" />\n"
    "        </mass>\n"
    "        <spin>\n"
    "          <fraction label=\"eval\" value=\"1\" unit=\"hbar\" />\n"
    "        </spin>\n"
    "        <parity>\n"
    "          <integer label=\"eval\" value=\"1\" />\n"
    "        </parity>\n"
    "        <charge>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "        </charge>\n"
    "      </gaugeBoson>\n"
    "    </gaugeBosons>\n"
    "    <baryons>\n"
    "      <baryon id=\"n\">\n"
    "        <mass>\n"
    "          <double label=\"eval\" value=\"1.00866491606\" unit=\"amu\" />\n"
    "        </mass>\n"
    "        <spin>\n"
    "          <fraction label=\"eval\" value=\"1/2\" unit=\"hbar\" />\n"
    "        </spin>\n"
    "        <parity>\n"
    "          <integer label=\"eval\" value=\"1\" />\n"
    "        </parity>\n"
    "        <charge>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "        </charge>\n"
    "      </baryon>\n"
    "      <baryon id=\"p\">\n"
    "        <mass>\n"
    "          <double label=\"eval\" value=\"1.007276488803\" unit=\"amu\" />\n"
    "        </mass>\n"
    "        <spin>\n"
    "          <fraction label=\"eval\" value=\"1/2\" unit=\"hbar\" />\n"
    "        </spin>\n"
    "        <parity>\n"
    "          <integer label=\"eval\" value=\"1\" />\n"
    "        </parity>\n"
    "        <charge>\n"
    "          <double label=\"eval\" value=\"1\" unit=\"e\" />\n"
    "        </charge>\n"
    "      </baryon>\n"
    "    </baryons>\n"
    "    <chemicalElements>\n"
    "      <chemicalElement symbol=\"S\" Z=\"16\" name=\"Sulfur\">\n"
    "        <isotopes>\n"
    "          <isotope symbol=\"S35\" A=\"35\">\n"
    "            <nuclides>\n"
    "              <nuclide id=\"S35\">\n"
    "                <mass>\n"
    "                  <double label=\"eval\" value=\"34.96903076887\" unit=\"amu\" />\n"
    "                </mass>\n"
    "                <charge>\n"
    "                  <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "                </charge>\n"
    "                <nucleus id=\"s35\">\n"
    "                  <spin>\n"
    "                    <fraction label=\"eval\" value=\"3/2\" unit=\"hbar\" />\n"
    "                  </spin>\n"
    "                  <parity>\n"
    "                    <integer label=\"eval\" value=\"1\" />\n"
    "                  </parity>\n"
    "                  <charge>\n"
    "                    <double label=\"eval\" value=\"16\" unit=\"e\" />\n"
    "                  </charge>\n"
    "                </nucleus>\n"
    "              </nuclide>\n"
    "            </nuclides>\n"
    "          </isotope>\n"
    "        </isotopes>\n"
    "      </chemicalElement>\n"
    "      <chemicalElement symbol=\"Cl\" Z=\"17\" name=\"Chlorine\">\n"
    "        <isotopes>\n"
    "          <isotope symbol=\"Cl35\" A=\"35\">\n"
    "            <nuclides>\n"
    "              <nuclide id=\"Cl35\">\n"
    "                <mass>\n"
    "                  <double label=\"eval\" value=\"34.96884920918\" unit=\"amu\" />\n"
    "                </mass>\n"
    "                <charge>\n"
    "                  <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "                </charge>\n"
    "                <nucleus id=\"cl35\">\n"
    "                  <spin>\n"
    "                    <fraction label=\"eval\" value=\"3/2\" unit=\"hbar\" />\n"
    "                  </spin>\n"
    "                  <parity>\n"
    "                    <integer label=\"eval\" value=\"1\" />\n"
    "                  </parity>\n"
    "                  <charge>\n"
    "                    <double label=\"eval\" value=\"17\" unit=\"e\" />\n"
    "                  </charge>\n"
    "                </nucleus>\n"
    "              </nuclide>\n"
    "            </nuclides>\n"
    "          </isotope>\n"
    "          <isotope symbol=\"Cl36\" A=\"36\">\n"
    "            <nuclides>\n"
    "              <nuclide id=\"Cl36[all]\">\n"
    "                <mass>\n"
    "                  <double label=\"eval\" value=\"35.96830501456\" unit=\"amu\" />\n"
    "                </mass>\n"
    "                <charge>\n"
    "                  <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "                </charge>\n"
    "                <nucleus id=\"cl36[all]\">\n"
    "                  <spin>\n"
    "                    <fraction label=\"eval\" value=\"0\" unit=\"hbar\" />\n"
    "                  </spin>\n"
    "                  <parity>\n"
    "                    <integer label=\"eval\" value=\"1\" />\n"
    "                  </parity>\n"
    "                  <charge>\n"
    "                    <double label=\"eval\" value=\"17\" unit=\"e\" />\n"
    "                  </charge>\n"
    "                </nucleus>\n"
    "              </nuclide>\n"
    "            </nuclides>\n"
    "          </isotope>\n"
    "        </isotopes>\n"
    "      </chemicalElement>\n"
    "    </chemicalElements>\n"
    "  </PoPs>\n"
    "  <resonanceReactions>\n"
    "    <resonanceReaction label=\"n,Cl35->g,Cl36[all]\" ejectile=\"g\" eliminated=\"true\">\n"
    "      <link href=\"/reactionSuite/reactions/reaction[@label='n,Cl35->g,Cl36[all]']\" />\n"
    "      <Q>\n"
    "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "          <axes>\n"
    "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
    "          </axes>\n"
    "        </constant1d>\n"
    "      </Q>\n"
    "    </resonanceReaction>\n"
    "    <resonanceReaction label=\"n,Cl35->n,Cl35\" ejectile=\"n\">\n"
    "      <link href=\"/reactionSuite/reactions/reaction[@label='n,Cl35->n,Cl35']\" />\n"
    "      <Q>\n"
    "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "          <axes>\n"
    "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
    "          </axes>\n"
    "        </constant1d>\n"
    "      </Q>\n"
    "    </resonanceReaction>\n"
    "    <resonanceReaction label=\"n,Cl35->p,S35\" ejectile=\"p\">\n"
    "      <link href=\"/reactionSuite/reactions/reaction[@label='n,Cl35->p,S35']\" />\n"
    "      <Q>\n"
    "        <constant1d label=\"eval\" value=\"615220\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "          <axes>\n"
    "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
    "          </axes>\n"
    "        </constant1d>\n"
    "      </Q>\n"
    "    </resonanceReaction>\n"
    "  </resonanceReactions>\n"
    "  <spinGroups>\n"
    "    <spinGroup label=\"0-\" spin=\"0\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cl35->g,Cl36[all]{1,0,0-}\" resonanceReaction=\"n,Cl35->g,Cl36[all]\" L=\"1\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->n,Cl35{1,1,0-}\" resonanceReaction=\"n,Cl35->n,Cl35\" L=\"1\" channelSpin=\"1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cl35->g,Cl36[all]{1,0,0-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cl35->n,Cl35{1,1,0-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            22396.4 1 1.1\n"
    "            547854.5 2 2.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"1-\" spin=\"1\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cl35->g,Cl36[all]{1,0,1-}\" resonanceReaction=\"n,Cl35->g,Cl36[all]\" L=\"1\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->n,Cl35{1,1,1-}\" resonanceReaction=\"n,Cl35->n,Cl35\" L=\"1\" channelSpin=\"1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->n,Cl35{1,2,1-}\" resonanceReaction=\"n,Cl35->n,Cl35\" L=\"1\" channelSpin=\"2\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->p,S35{1,1,1-}\" resonanceReaction=\"n,Cl35->p,S35\" L=\"1\" channelSpin=\"1\" columnIndex=\"4\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->p,S35{1,2,1-}\" resonanceReaction=\"n,Cl35->p,S35\" L=\"1\" channelSpin=\"2\" columnIndex=\"5\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"6\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cl35->g,Cl36[all]{1,0,1-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cl35->n,Cl35{1,1,1-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Cl35->n,Cl35{1,2,1-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"4\" name=\"n,Cl35->p,S35{1,1,1-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"5\" name=\"n,Cl35->p,S35{1,2,1-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            4250.762 3 3.1 3.2 3.3 3.4\n"
    "            1435502 4 4.1 4.2 4.3 4.4\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"1+\" spin=\"1\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cl35->g,Cl36[all]{0,0,1+}\" resonanceReaction=\"n,Cl35->g,Cl36[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->n,Cl35{0,1,1+}\" resonanceReaction=\"n,Cl35->n,Cl35\" L=\"0\" channelSpin=\"1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"3.66798\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->p,S35{0,1,1+}\" resonanceReaction=\"n,Cl35->p,S35\" L=\"0\" channelSpin=\"1\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"3.66798\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"4\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cl35->g,Cl36[all]{0,0,1+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cl35->n,Cl35{0,1,1+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Cl35->p,S35{0,1,1+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            54932 5 5.1 5.2\n"
    "            1205687 6 6.1 6.2\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"2-\" spin=\"2\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cl35->g,Cl36[all]{1,0,2-}\" resonanceReaction=\"n,Cl35->g,Cl36[all]\" L=\"1\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->n,Cl35{1,1,2-}\" resonanceReaction=\"n,Cl35->n,Cl35\" L=\"1\" channelSpin=\"1\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->n,Cl35{1,2,2-}\" resonanceReaction=\"n,Cl35->n,Cl35\" L=\"1\" channelSpin=\"2\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->p,S35{1,1,2-}\" resonanceReaction=\"n,Cl35->p,S35\" L=\"1\" channelSpin=\"1\" columnIndex=\"4\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->p,S35{1,2,2-}\" resonanceReaction=\"n,Cl35->p,S35\" L=\"1\" channelSpin=\"2\" columnIndex=\"5\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"6\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cl35->g,Cl36[all]{1,0,2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cl35->n,Cl35{1,1,2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Cl35->n,Cl35{1,2,2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"4\" name=\"n,Cl35->p,S35{1,1,2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"5\" name=\"n,Cl35->p,S35{1,2,2-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            -336933.4 7 7.1 7.2 7.3 7.4\n"
    "            1441365 8 8.1 8.2 8.3 8.4\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"2+\" spin=\"2\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cl35->g,Cl36[all]{0,0,2+}\" resonanceReaction=\"n,Cl35->g,Cl36[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->n,Cl35{0,2,2+}\" resonanceReaction=\"n,Cl35->n,Cl35\" L=\"0\" channelSpin=\"2\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"3.66798\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->p,S35{0,2,2+}\" resonanceReaction=\"n,Cl35->p,S35\" L=\"0\" channelSpin=\"2\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"3.66798\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"4\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cl35->g,Cl36[all]{0,0,2+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cl35->n,Cl35{0,2,2+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Cl35->p,S35{0,2,2+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            -180.65 9 9.1 9.2\n"
    "            7563145 10 10.1 10.2\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"3-\" spin=\"3\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Cl35->g,Cl36[all]{1,0,3-}\" resonanceReaction=\"n,Cl35->g,Cl36[all]\" L=\"1\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->n,Cl35{1,2,3-}\" resonanceReaction=\"n,Cl35->n,Cl35\" L=\"1\" channelSpin=\"2\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Cl35->p,S35{1,2,3-}\" resonanceReaction=\"n,Cl35->p,S35\" L=\"1\" channelSpin=\"2\" columnIndex=\"3\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.82222\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"4.88875\" domainMin=\"1e-05\" domainMax=\"1200000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"4\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Cl35->g,Cl36[all]{1,0,3-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Cl35->n,Cl35{1,2,3-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"3\" name=\"n,Cl35->p,S35{1,2,3-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            16356.12 11 11.1 11.2\n"
    "            1485128 12 12.1 12.2\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "  </spinGroups>\n"
    "</RMatrix>\n";
}

std::string chunkSr88() {

  return
    "<RMatrix label=\"eval\" approximation=\"ReichMoore\" boundaryCondition=\"EliminateShiftFunction\" reducedWidthAmplitudes=\"true\">\n"
    "  <PoPs name=\"particles\" version=\"1.0\" format=\"2.1\">\n"
    "    <gaugeBosons>\n"
    "      <gaugeBoson id=\"g\">\n"
    "        <mass>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"amu\" />\n"
    "        </mass>\n"
    "        <spin>\n"
    "          <fraction label=\"eval\" value=\"1\" unit=\"hbar\" />\n"
    "        </spin>\n"
    "        <parity>\n"
    "          <integer label=\"eval\" value=\"1\" />\n"
    "        </parity>\n"
    "        <charge>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "        </charge>\n"
    "      </gaugeBoson>\n"
    "    </gaugeBosons>\n"
    "    <baryons>\n"
    "      <baryon id=\"n\">\n"
    "        <mass>\n"
    "          <double label=\"eval\" value=\"1.00866491606\" unit=\"amu\" />\n"
    "        </mass>\n"
    "        <spin>\n"
    "          <fraction label=\"eval\" value=\"1/2\" unit=\"hbar\" />\n"
    "        </spin>\n"
    "        <parity>\n"
    "          <integer label=\"eval\" value=\"1\" />\n"
    "        </parity>\n"
    "        <charge>\n"
    "          <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "        </charge>\n"
    "      </baryon>\n"
    "    </baryons>\n"
    "    <chemicalElements>\n"
    "      <chemicalElement symbol=\"Sr\" Z=\"38\" name=\"Strontium\">\n"
    "        <isotopes>\n"
    "          <isotope symbol=\"Sr88\" A=\"88\">\n"
    "            <nuclides>\n"
    "              <nuclide id=\"Sr88\">\n"
    "                <mass>\n"
    "                  <double label=\"eval\" value=\"87.90561142049\" unit=\"amu\" />\n"
    "                </mass>\n"
    "                <charge>\n"
    "                  <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "                </charge>\n"
    "                <nucleus id=\"sr88\">\n"
    "                  <spin>\n"
    "                    <fraction label=\"eval\" value=\"0\" unit=\"hbar\" />\n"
    "                  </spin>\n"
    "                  <parity>\n"
    "                    <integer label=\"eval\" value=\"1\" />\n"
    "                  </parity>\n"
    "                  <charge>\n"
    "                    <double label=\"eval\" value=\"38\" unit=\"e\" />\n"
    "                  </charge>\n"
    "                </nucleus>\n"
    "              </nuclide>\n"
    "            </nuclides>\n"
    "          </isotope>\n"
    "          <isotope symbol=\"Sr89\" A=\"89\">\n"
    "            <nuclides>\n"
    "              <nuclide id=\"Sr89[all]\">\n"
    "                <mass>\n"
    "                  <double label=\"eval\" value=\"88.91427633655\" unit=\"amu\" />\n"
    "                </mass>\n"
    "                <charge>\n"
    "                  <double label=\"eval\" value=\"0\" unit=\"e\" />\n"
    "                </charge>\n"
    "                <nucleus id=\"sr89[all]\">\n"
    "                  <spin>\n"
    "                    <fraction label=\"eval\" value=\"0\" unit=\"hbar\" />\n"
    "                  </spin>\n"
    "                  <parity>\n"
    "                    <integer label=\"eval\" value=\"1\" />\n"
    "                  </parity>\n"
    "                  <charge>\n"
    "                    <double label=\"eval\" value=\"38\" unit=\"e\" />\n"
    "                  </charge>\n"
    "                </nucleus>\n"
    "              </nuclide>\n"
    "            </nuclides>\n"
    "          </isotope>\n"
    "        </isotopes>\n"
    "      </chemicalElement>\n"
    "    </chemicalElements>\n"
    "  </PoPs>\n"
    "  <resonanceReactions>\n"
    "    <resonanceReaction label=\"n,Sr88->g,Sr89[all]\" ejectile=\"g\" eliminated=\"true\">\n"
    "      <link href=\"/reactionSuite/reactions/reaction[@label='n,Sr88->g,Sr89[all]']\" />\n"
    "      <Q>\n"
    "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "          <axes>\n"
    "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
    "          </axes>\n"
    "        </constant1d>\n"
    "      </Q>\n"
    "    </resonanceReaction>\n"
    "    <resonanceReaction label=\"n,Sr88->n,Sr88\" ejectile=\"n\">\n"
    "      <link href=\"/reactionSuite/reactions/reaction[@label='n,Sr88->n,Sr88']\" />\n"
    "      <Q>\n"
    "        <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "          <axes>\n"
    "            <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <axis index=\"0\" label=\"Q\" unit=\"eV\" />\n"
    "          </axes>\n"
    "        </constant1d>\n"
    "      </Q>\n"
    "    </resonanceReaction>\n"
    "  </resonanceReactions>\n"
    "  <spinGroups>\n"
    "    <spinGroup label=\"1/2-\" spin=\"0.5\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Sr88->g,Sr89[all]{0,0,1/2-}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Sr88->n,Sr88{1,1/2,1/2-}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"1\" channelSpin=\"0.5\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <externalRMatrix type=\"SAMMY\">\n"
    "            <double label=\"constantExternalR\" value=\"0.45\" />\n"
    "            <double label=\"linearExternalR\" value=\"3.2e-07\" unit=\"1/eV\" />\n"
    "            <double label=\"quadraticExternalR\" value=\"0\" unit=\"1/eV**2\" />\n"
    "            <double label=\"constantLogarithmicCoefficient\" value=\"0.075\" />\n"
    "            <double label=\"linearLogarithmicCoefficient\" value=\"0\" unit=\"1/eV\" />\n"
    "            <double label=\"singularityEnergyBelow\" value=\"0\" unit=\"eV\" />\n"
    "            <double label=\"singularityEnergyAbove\" value=\"955000\" unit=\"eV\" />\n"
    "          </externalRMatrix>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Sr88->g,Sr89[all]{0,0,1/2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Sr88->n,Sr88{1,1/2,1/2-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            12410 1 1.1\n"
    "            833170 2 2.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"1/2+\" spin=\"0.5\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Sr88->g,Sr89[all]{0,0,1/2+}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Sr88->n,Sr88{0,1/2,1/2+}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"0\" channelSpin=\"0.5\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <hardSphereRadius>\n"
    "            <constant1d label=\"eval\" value=\"6.8\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </hardSphereRadius>\n"
    "          <externalRMatrix type=\"SAMMY\">\n"
    "            <double label=\"constantExternalR\" value=\"-0.043\" />\n"
    "            <double label=\"linearExternalR\" value=\"2.8e-08\" unit=\"1/eV\" />\n"
    "            <double label=\"quadraticExternalR\" value=\"0\" unit=\"1/eV**2\" />\n"
    "            <double label=\"constantLogarithmicCoefficient\" value=\"0.01\" />\n"
    "            <double label=\"linearLogarithmicCoefficient\" value=\"0\" unit=\"1/eV\" />\n"
    "            <double label=\"singularityEnergyBelow\" value=\"0\" unit=\"eV\" />\n"
    "            <double label=\"singularityEnergyAbove\" value=\"955000\" unit=\"eV\" />\n"
    "          </externalRMatrix>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Sr88->g,Sr89[all]{0,0,1/2+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Sr88->n,Sr88{0,1/2,1/2+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            13840 3 3.1\n"
    "            943340 4 4.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"3/2-\" spin=\"1.5\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Sr88->g,Sr89[all]{0,0,3/2-}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Sr88->n,Sr88{1,1/2,3/2-}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"1\" channelSpin=\"0.5\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <externalRMatrix type=\"SAMMY\">\n"
    "            <double label=\"constantExternalR\" value=\"0.43\" />\n"
    "            <double label=\"linearExternalR\" value=\"-1.8e-07\" unit=\"1/eV\" />\n"
    "            <double label=\"quadraticExternalR\" value=\"0\" unit=\"1/eV**2\" />\n"
    "            <double label=\"constantLogarithmicCoefficient\" value=\"0.22\" />\n"
    "            <double label=\"linearLogarithmicCoefficient\" value=\"0\" unit=\"1/eV\" />\n"
    "            <double label=\"singularityEnergyBelow\" value=\"0\" unit=\"eV\" />\n"
    "            <double label=\"singularityEnergyAbove\" value=\"955000\" unit=\"eV\" />\n"
    "          </externalRMatrix>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Sr88->g,Sr89[all]{0,0,3/2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Sr88->n,Sr88{1,1/2,3/2-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            18210 5 5.1\n"
    "            948230 6 6.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"3/2+\" spin=\"1.5\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Sr88->g,Sr89[all]{0,0,3/2+}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Sr88->n,Sr88{2,1/2,3/2+}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"2\" channelSpin=\"0.5\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <externalRMatrix type=\"SAMMY\">\n"
    "            <double label=\"constantExternalR\" value=\"-0.7\" />\n"
    "            <double label=\"linearExternalR\" value=\"2.3e-06\" unit=\"1/eV\" />\n"
    "            <double label=\"quadraticExternalR\" value=\"0\" unit=\"1/eV**2\" />\n"
    "            <double label=\"constantLogarithmicCoefficient\" value=\"0.041\" />\n"
    "            <double label=\"linearLogarithmicCoefficient\" value=\"0\" unit=\"1/eV\" />\n"
    "            <double label=\"singularityEnergyBelow\" value=\"0\" unit=\"eV\" />\n"
    "            <double label=\"singularityEnergyAbove\" value=\"955000\" unit=\"eV\" />\n"
    "          </externalRMatrix>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Sr88->g,Sr89[all]{0,0,3/2+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Sr88->n,Sr88{2,1/2,3/2+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            266530 7 7.1\n"
    "            874940 8 8.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"5/2-\" spin=\"2.5\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Sr88->g,Sr89[all]{0,0,5/2-}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Sr88->n,Sr88{3,1/2,5/2-}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"3\" channelSpin=\"0.5\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <externalRMatrix type=\"SAMMY\">\n"
    "            <double label=\"constantExternalR\" value=\"0.001\" />\n"
    "            <double label=\"linearExternalR\" value=\"4.6e-07\" unit=\"1/eV\" />\n"
    "            <double label=\"quadraticExternalR\" value=\"0\" unit=\"1/eV**2\" />\n"
    "            <double label=\"constantLogarithmicCoefficient\" value=\"0.24\" />\n"
    "            <double label=\"linearLogarithmicCoefficient\" value=\"0\" unit=\"1/eV\" />\n"
    "            <double label=\"singularityEnergyBelow\" value=\"0\" unit=\"eV\" />\n"
    "            <double label=\"singularityEnergyAbove\" value=\"955000\" unit=\"eV\" />\n"
    "          </externalRMatrix>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Sr88->g,Sr89[all]{0,0,5/2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Sr88->n,Sr88{3,1/2,5/2-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            408460 9 9.1\n"
    "            899440 10 10.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"5/2+\" spin=\"2.5\" parity=\"+1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Sr88->g,Sr89[all]{0,0,5/2+}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Sr88->n,Sr88{2,1/2,5/2+}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"2\" channelSpin=\"0.5\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <externalRMatrix type=\"SAMMY\">\n"
    "            <double label=\"constantExternalR\" value=\"-2.5\" />\n"
    "            <double label=\"linearExternalR\" value=\"3.3e-06\" unit=\"1/eV\" />\n"
    "            <double label=\"quadraticExternalR\" value=\"0\" unit=\"1/eV**2\" />\n"
    "            <double label=\"constantLogarithmicCoefficient\" value=\"0.0026\" />\n"
    "            <double label=\"linearLogarithmicCoefficient\" value=\"0\" unit=\"1/eV\" />\n"
    "            <double label=\"singularityEnergyBelow\" value=\"0\" unit=\"eV\" />\n"
    "            <double label=\"singularityEnergyAbove\" value=\"955000\" unit=\"eV\" />\n"
    "          </externalRMatrix>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Sr88->g,Sr89[all]{0,0,5/2+} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Sr88->n,Sr88{2,1/2,5/2+} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            409820 11 11.1\n"
    "            849610 12 12.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "    <spinGroup label=\"7/2-\" spin=\"3.5\" parity=\"-1\">\n"
    "      <channels>\n"
    "        <channel label=\"n,Sr88->g,Sr89[all]{0,0,7/2-}\" resonanceReaction=\"n,Sr88->g,Sr89[all]\" L=\"0\" channelSpin=\"0\" columnIndex=\"1\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"0\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "        </channel>\n"
    "        <channel label=\"n,Sr88->n,Sr88{3,1/2,7/2-}\" resonanceReaction=\"n,Sr88->n,Sr88\" L=\"3\" channelSpin=\"0.5\" columnIndex=\"2\">\n"
    "          <scatteringRadius>\n"
    "            <constant1d label=\"eval\" value=\"7.1\" domainMin=\"1e-05\" domainMax=\"950000\">\n"
    "              <axes>\n"
    "                <axis index=\"1\" label=\"incidentEnergy\" unit=\"eV\" />\n"
    "                <axis index=\"0\" label=\"radius\" unit=\"fm\" />\n"
    "              </axes>\n"
    "            </constant1d>\n"
    "          </scatteringRadius>\n"
    "          <externalRMatrix type=\"SAMMY\">\n"
    "            <double label=\"constantExternalR\" value=\"0.001\" />\n"
    "            <double label=\"linearExternalR\" value=\"9e-08\" unit=\"1/eV\" />\n"
    "            <double label=\"quadraticExternalR\" value=\"0\" unit=\"1/eV**2\" />\n"
    "            <double label=\"constantLogarithmicCoefficient\" value=\"0.19\" />\n"
    "            <double label=\"linearLogarithmicCoefficient\" value=\"0\" unit=\"1/eV\" />\n"
    "            <double label=\"singularityEnergyBelow\" value=\"0\" unit=\"eV\" />\n"
    "            <double label=\"singularityEnergyAbove\" value=\"955000\" unit=\"eV\" />\n"
    "          </externalRMatrix>\n"
    "        </channel>\n"
    "      </channels>\n"
    "      <resonanceParameters>\n"
    "        <table rows=\"2\" columns=\"3\">\n"
    "          <columnHeaders>\n"
    "            <column index=\"0\" name=\"incidentEnergy\" unit=\"eV\" />\n"
    "            <column index=\"1\" name=\"n,Sr88->g,Sr89[all]{0,0,7/2-} width\" unit=\"eV**(1/2)\" />\n"
    "            <column index=\"2\" name=\"n,Sr88->n,Sr88{3,1/2,7/2-} width\" unit=\"eV**(1/2)\" />\n"
    "          </columnHeaders>\n"
    "          <data>\n"
    "            528840 13 13.1\n"
    "            947560 14 14.1\n"
    "          </data>\n"
    "        </table>\n"
    "      </resonanceParameters>\n"
    "    </spinGroup>\n"
    "  </spinGroups>\n"
    "</RMatrix>\n";
}