// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/createEndfFile2Section151.hpp"

// other includes
#include "njoy/constants.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

std::string chunkSi29();
std::string chunkCu63();
std::string chunkCl35();
std::string chunkSr88();

SCENARIO( "createEndfFile2Section" ) {

  GIVEN( "valid data for a compound system - Si29" ) {

    // Si29 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - empty spin group that contribute only potential scattering

    std::string string = chunkSi29();

    WHEN( "the data is given explicitly" ) {

    auto photon = id::ParticleID::photon();
    auto neutron = id::ParticleID::neutron();
    auto si29 = id::ParticleID( "Si29" );
    auto si30 = id::ParticleID( "Si30[all]" );

    ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                              Particle( si30, 29.728 * njoy::constants::neutron_mass, 0, +1 ) );
    ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                               Particle( si29, 28.728 * njoy::constants::neutron_mass, 0.5, +1 ) );

    ChannelRadii zero_radii( 0., 0. );
    ChannelRadii radii( 4.221, 4.221 );

      CompoundSystem compound( 1e-5, 1.3e+6,
                               { { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                   { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                       id::ChannelID( "n,Si29->n,Si29{1,1,0-}" ) },
                                     { 3.740320e+5, 6.007182e+5 },
                                     { { 1., 2. },
                                       { 1.1, 2.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 0- spin group
                                 { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0+}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Si29->n,Si29{0,0,0+}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                   { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,0-}" ),
                                       id::ChannelID( "n,Si29->n,Si29{0,0,0+}" ) },
                                     { -2.041700e+6, 2.248487e+6 },
                                     { { 3., 4. },
                                       { 3.1, 4.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 0+ spin group
                                 { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
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
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 1- spin group
                                 { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,1+}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
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
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 1+ spin group
                                 { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Si29->n,Si29{1,1,2-}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                   { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2-}" ),
                                       id::ChannelID( "n,Si29->n,Si29{1,1,2-}" ) },
                                     { 3.883377e+4, 1.207629e+6 },
                                     { { 9., 10. },
                                       { 9.1, 10.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 2- spin group
                                 { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2+}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Si29->n,Si29{2,0,2+}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, radii },
                                     { id::ChannelID( "n,Si29->n,Si29{2,1,2+}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                   { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,2+}" ),
                                       id::ChannelID( "n,Si29->n,Si29{2,0,2+}" ),
                                       id::ChannelID( "n,Si29->n,Si29{2,1,2+}" ) } }, // empty table
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 2+ spin group
                                 { { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,3+}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Si29->n,Si29{2,1,3+}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, radii } },
                                   { { id::ChannelID( "n,Si29->g,Si30[all]{0,0,3+}" ),
                                       id::ChannelID( "n,Si29->n,Si29{2,1,3+}" ) },
                                     { 6.203529e+5 },
                                     { { 11. },
                                       { 11.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor } } ); // 3+ spin group

      ResonanceParameters parameters( { compound } );

      double awr = 28.728;

      THEN( "it can be converted to ENDF" ) {

        auto data = format::endf::createEndfFile2Section151( awr, parameters );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 1428, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a compound system - Cu63" ) {

    // Cu63 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - 2 channels, neutron only, constant boundary condition

    std::string string = chunkCu63();

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

      CompoundSystem compound( 1e-5, 1e+5,
                               { { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,0+}" ),
                                       neutron_pair, photon_pair, 0., 0, zero_radii },
                                     { id::ChannelID( "n,Cu63->n,Cu63{1,1,0+}" ),
                                       neutron_pair, neutron_pair, 0., -1, radii } },
                                   { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,0+}" ),
                                       id::ChannelID( "n,Cu63->n,Cu63{1,1,0+}" ) },
                                     { 2.216315e+3, 2.981944e+5 },
                                     { { 1., 2. },
                                       { 1.1, 2.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::Constant }, // 0+ spin group
                                 { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1-}" ),
                                       neutron_pair, photon_pair, 0., 0, zero_radii },
                                     { id::ChannelID( "n,Cu63->n,Cu63{0,1,1-}" ),
                                       neutron_pair, neutron_pair, 0., 0, radii } },
                                   { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,1-}" ),
                                       id::ChannelID( "n,Cu63->n,Cu63{0,1,1-}" ) },
                                     { -3.709301e+4, 3.282861e+5 },
                                     { { 3., 4. },
                                       { 3.1, 4.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::Constant }, // 1- spin group
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
                                   Formalism::ReichMoore,
                                   BoundaryCondition::Constant }, // 1+ spin group
                                 { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,2-}" ),
                                       neutron_pair, photon_pair, 0., 0, zero_radii },
                                     { id::ChannelID( "n,Cu63->n,Cu63{0,2,2-}" ),
                                       neutron_pair, neutron_pair, 0., 0, radii } },
                                   { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,2-}" ),
                                       id::ChannelID( "n,Cu63->n,Cu63{0,2,2-}" ) },
                                     { -5.334625e+4, 3.316735e+5 },
                                     { { 7., 8. },
                                       { 7.1, 8.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::Constant }, // 2- spin group
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
                                   Formalism::ReichMoore,
                                   BoundaryCondition::Constant }, // 2+ spin group
                                 { { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,3+}" ),
                                       neutron_pair, photon_pair, 0., 0, zero_radii },
                                     { id::ChannelID( "n,Cu63->n,Cu63{1,2,3+}" ),
                                       neutron_pair, neutron_pair, 0., -1, radii } },
                                   { { id::ChannelID( "n,Cu63->g,Cu64[all]{0,0,3+}" ),
                                       id::ChannelID( "n,Cu63->n,Cu63{1,2,3+}" ) },
                                     { 4.018230e+2, 3.006336e+5 },
                                     { { 11., 12. },
                                       { 11.1, 12.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::Constant } } ); // 3+ spin group

      ResonanceParameters parameters( { compound } );

      double awr = 62.389;

      THEN( "it can be converted to ENDF" ) {

        auto data = format::endf::createEndfFile2Section151( awr, parameters );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 2925, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a compound system - Cl35" ) {

    // Cl35 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - Z for n,gamma is set to 0.0 (should be 17.0)
    //                      - spin groups are not unique (1- and 2- occur
    //                        multiple times)
    // these only apply when reading the data

    std::string string = chunkCl35();

    WHEN( "the data is given explicitly" ) {

      auto photon = id::ParticleID::photon();
      auto neutron = id::ParticleID::neutron();
      auto proton = id::ParticleID::proton();
      auto cl35 = id::ParticleID( "Cl35" );
      auto cl35_e1 = id::ParticleID( "Cl35_e1" );
      auto cl36 = id::ParticleID( "Cl36[all]" );
      auto s35 = id::ParticleID( "S35" );

      ParticlePair photon_pair( Particle( photon, 0, 1, +1 ),
                                Particle( cl36, 35.65932 * njoy::constants::neutron_mass, 0, +1 ) );
      ParticlePair neutron_pair( Particle( neutron, njoy::constants::neutron_mass, 0.5, +1 ),
                                 Particle( cl35, 34.66845 * njoy::constants::neutron_mass, 1.5, +1 ) );
      ParticlePair proton_pair( Particle( proton, .9986235 * njoy::constants::neutron_mass, 0.5, +1 ),
                                Particle( s35, 34.66863 * njoy::constants::neutron_mass, 1.5, +1 ) );

      ChannelRadii zero_radii( 0., 0. );
      ChannelRadii radii1( 4.822220, 4.888750 );
      ChannelRadii radii2( 4.822220, 3.667980 );

      CompoundSystem compound( 1e-5, 1.2e+6,
                               { { { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, radii1 } },
                                   { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,0-}" ),
                                       id::ChannelID( "n,Cl35->n,Cl35{1,1,0-}" ) },
                                     { 2.239640e+4, 5.478545e+5 },
                                     { { 1., 2. },
                                       { 1.1, 2.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 0- spin group
                                 { { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
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
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 1- spingroup
                                 { { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
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
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 1+ spingroup
                                 { { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,2-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
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
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 2- spingroup
                                 { { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
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
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 2+ spin group
                                 { { { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,3-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
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
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor } } ); // 3- spin group

      ResonanceParameters parameters( { compound } );

      double awr = 34.66845;

      THEN( "it can be converted to ENDF" ) {

        auto data = format::endf::createEndfFile2Section151( awr, parameters );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 1725, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN


  GIVEN( "valid data for a compound system - Sr88" ) {

    // Sr88 ENDF/B-VIII.1 LRF=7 resonance evaluation
    // particular features: - Sammy parametrisation for channel background

    std::string string = chunkSr88();

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
      ChannelRadii different_radii( 7.1, 6.8 );

      CompoundSystem compound( 1e-5, 9.5e+5,
                               { { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, equal_radii,
                                       Kinematics::NonRelativistic,
                                       SammyBackground( { 0.45, 3.2e-7, 0. }, { 0.075, 0. }, 0., 9.55e+5 ) } },
                                   { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2-}" ),
                                       id::ChannelID( "n,Sr88->n,Sr88{1,1/2,1/2-}" ) },
                                     { 1.241000e+4, 8.331700e+5 },
                                     { { 1., 2. },
                                       { 1.1, 2.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 1/2- spin group
                                 { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2+}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Sr88->n,Sr88{0,1/2,1/2+}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, different_radii,
                                       Kinematics::NonRelativistic,
                                       SammyBackground( { -0.043, 2.8e-8, 0. }, { 0.01, 0. }, 0., 9.55e+5 ) } },
                                   { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,1/2+}" ),
                                       id::ChannelID( "n,Sr88->n,Sr88{0,1/2,1/2+}" ) },
                                     { 1.3840e+4, 9.4334e+5 },
                                     { { 3., 4. },
                                       { 3.1, 4.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 1/2+ spin group
                                 { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Sr88->n,Sr88{1,1/2,3/2-}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, equal_radii,
                                       Kinematics::NonRelativistic,
                                       SammyBackground( { 0.43, -1.8e-7, 0. }, { 0.22, 0. }, 0., 9.55e+5 ) } },
                                   { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2-}" ),
                                       id::ChannelID( "n,Sr88->n,Sr88{1,1/2,3/2-}" ) },
                                     { 1.8210e+4, 9.4823e+5 },
                                     { { 5., 6. },
                                       { 5.1, 6.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 3/2- spin group
                                 { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2+}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Sr88->n,Sr88{2,1/2,3/2+}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, equal_radii,
                                       Kinematics::NonRelativistic,
                                       SammyBackground( { -0.7, 2.3e-6, 0. }, { 0.041, 0. }, 0., 9.55e+5 ) } },
                                   { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,3/2+}" ),
                                       id::ChannelID( "n,Sr88->n,Sr88{2,1/2,3/2+}" ) },
                                     { 2.6653e+5, 8.7494e+5 },
                                     { { 7., 8. },
                                       { 7.1, 8.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 3/2+ spin group
                                 { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Sr88->n,Sr88{3,1/2,5/2-}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, equal_radii,
                                       Kinematics::NonRelativistic,
                                       SammyBackground( { 0.001, 4.6e-7, 0. }, { 0.24, 0. }, 0., 9.55e+5 ) } },
                                   { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2-}" ),
                                       id::ChannelID( "n,Sr88->n,Sr88{3,1/2,5/2-}" ) },
                                     { 4.0846e+5, 8.9944e+5 },
                                     { { 9., 10. },
                                       { 9.1, 10.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 5/2- spin group
                                 { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2+}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Sr88->n,Sr88{2,1/2,5/2+}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, equal_radii,
                                       Kinematics::NonRelativistic,
                                       SammyBackground( { -2.5, 3.3e-6, 0. }, { 0.0026, 0. }, 0., 9.55e+5 ) } },
                                   { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,5/2+}" ),
                                       id::ChannelID( "n,Sr88->n,Sr88{2,1/2,5/2+}" ) },
                                     { 4.0982e+5, 8.4961e+5 },
                                     { { 11., 12. },
                                       { 11.1, 12.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor }, // 5/2+ spin group
                                 { { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,7/2-}" ),
                                       neutron_pair, photon_pair, 0., std::nullopt, zero_radii },
                                     { id::ChannelID( "n,Sr88->n,Sr88{3,1/2,7/2-}" ),
                                       neutron_pair, neutron_pair, 0., std::nullopt, equal_radii,
                                       Kinematics::NonRelativistic,
                                       SammyBackground( { 0.001, 9e-8, 0. }, { 0.19, 0. }, 0., 9.55e+5 ) } },
                                   { { id::ChannelID( "n,Sr88->g,Sr89[all]{0,0,7/2-}" ),
                                       id::ChannelID( "n,Sr88->n,Sr88{3,1/2,7/2-}" ) },
                                     { 5.2884e+5, 9.4756e+5 },
                                     { { 13., 14. },
                                       { 13.1, 14.1 } } },
                                   Formalism::ReichMoore,
                                   BoundaryCondition::ShiftFactor } } ); // 7/2- spin group

      ResonanceParameters parameters( { compound } );

      double awr = 87.15;

      THEN( "it can be converted to ENDF" ) {

        auto data = format::endf::createEndfFile2Section151( awr, parameters );

        std::string buffer;
        auto output = std::back_inserter( buffer );
        data.print( output, 3837, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunkSi29() {

  return
    " 1.402900+4 2.872800+1          0          0          1          01428 2151     \n"
    " 1.402900+4 1.000000+0          0          0          1          01428 2151     \n"
    " 1.000000-5 1.300000+6          1          7          0          01428 2151     \n"
    " 0.000000+0 0.000000+0          1          3          7          01428 2151     \n"
    " 0.000000+0 0.000000+0          2          0         24          41428 2151     \n"
    " 0.000000+0 2.972800+1 0.000000+0 1.400000+1 1.000000+0 0.000000+01428 2151     \n"
    " 0.000000+0-1.000000+0 0.000000+0 1.020000+2 0.000000+0 1.000000+01428 2151     \n"
    " 1.000000+0 2.872800+1 0.000000+0 1.400000+1 5.000000-1 5.000000-11428 2151     \n"
    " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 0.000000+01428 2151     \n"
    "-0.000000+0-1.000000+0          0          0         12          21428 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21428 2151     \n"
    " 3.740320+5 1.000000+0 1.100000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 6.007182+5 2.000000+0 2.100000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 0.000000+0 1.000000+0          0          0         12          21428 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 2.000000+0 0.000000+0 0.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21428 2151     \n"
    "-2.041700+6 3.000000+0 3.100000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 2.248487+6 4.000000+0 4.100000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    "-1.000000+0 0.000000+0          0          0         18          31428 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 2.000000+0 1.000000+0 0.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21428 2151     \n"
    " 1.529411+4 5.000000+0 5.100000+0 5.200000+0 0.000000+0 0.000000+01428 2151     \n"
    " 1.240000+6 6.000000+0 6.100000+0 6.200000+0 0.000000+0 0.000000+01428 2151     \n"
    " 1.000000+0 0.000000+0          0          0         18          31428 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 2.000000+0 0.000000+0 1.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 2.000000+0 2.000000+0 1.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21428 2151     \n"
    " 3.842219+5 7.000000+0 7.100000+0 7.200000+0 0.000000+0 0.000000+01428 2151     \n"
    " 1.388859+6 8.000000+0 8.100000+0 8.200000+0 0.000000+0 0.000000+01428 2151     \n"
    "-2.000000+0 0.000000+0          0          0         12          21428 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21428 2151     \n"
    " 3.883377+4 9.000000+0 9.100000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 1.207629+6 1.000000+1 1.010000+1 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 2.000000+0 0.000000+0          0          0         18          31428 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 2.000000+0 2.000000+0 0.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 2.000000+0 2.000000+0 1.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 0.000000+0 0.000000+0          0          0          6          11428 2151     \n"
    " 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 3.000000+0 0.000000+0          0          0         12          21428 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    " 2.000000+0 2.000000+0 1.000000+0 0.000000+0 4.221000-1 4.221000-11428 2151     \n"
    " 0.000000+0 0.000000+0          0          1          6          11428 2151     \n"
    " 6.203529+5 1.100000+1 1.110000+1 0.000000+0 0.000000+0 0.000000+01428 2151     \n"
    "                                                                  1428 2  0     \n";
}

std::string chunkCu63() {

  return
    " 2.906300+4 6.238900+1          0          0          1          02925 2151     \n"
    " 2.906300+4 1.000000+0          0          0          1          02925 2151     \n"
    " 1.000000-5 1.000000+5          1          7          0          02925 2151     \n"
    " 0.000000+0 0.000000+0          1          3          6          02925 2151     \n"
    " 0.000000+0 0.000000+0          2          0         24          42925 2151     \n"
    " 0.000000+0 6.338900+1 0.000000+0 2.900000+1 1.000000+0 0.000000+02925 2151     \n"
    " 0.000000+0-1.000000+0 1.000000+0 1.020000+2 0.000000+0 1.000000+02925 2151     \n"
    " 1.000000+0 6.238900+1 0.000000+0 2.900000+1 5.000000-1-1.500000+02925 2151     \n"
    " 0.000000+0 1.000000+0 1.000000+0 2.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 0.000000+0 1.000000+0          0          0         12          22925 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0-1.000000+0 6.700000-1 6.700000-12925 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
    " 2.216315+3 1.000000+0 1.100000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.981944+5 2.000000+0 2.100000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    "-1.000000+0 0.000000+0          0          0         12          22925 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.000000+0 0.000000+0 1.000000+0 0.000000+0 6.700000-1 6.700000-12925 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
    "-3.709301+4 3.000000+0 3.100000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 3.282861+5 4.000000+0 4.100000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 1.000000+0 0.000000+0          0          0         18          32925 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0-1.000000+0 6.700000-1 6.700000-12925 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0-1.000000+0 6.700000-1 6.700000-12925 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
    " 3.811148+3 5.000000+0 5.100000+0 5.200000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.993903+5 6.000000+0 6.100000+0 6.200000+0 0.000000+0 0.000000+02925 2151     \n"
    "-2.000000+0 0.000000+0          0          0         12          22925 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.000000+0 0.000000+0 2.000000+0 0.000000+0 6.700000-1 6.700000-12925 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
    "-5.334625+4 7.000000+0 7.100000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 3.316735+5 8.000000+0 8.100000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.000000+0 0.000000+0          0          0         18          32925 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0-1.000000+0 6.700000-1 6.700000-12925 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0-1.000000+0 6.700000-1 6.700000-12925 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
    " 1.054117+4 9.000000+0 9.100000+0 9.200000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.989878+5 1.000000+1 1.010000+1 1.020000+1 0.000000+0 0.000000+02925 2151     \n"
    " 3.000000+0 0.000000+0          0          0         12          22925 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0-1.000000+0 6.700000-1 6.700000-12925 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          22925 2151     \n"
    " 4.018230+2 1.100000+1 1.110000+1 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    " 3.006336+5 1.200000+1 1.210000+1 0.000000+0 0.000000+0 0.000000+02925 2151     \n"
    "                                                                  2925 2  0     \n";
}

std::string chunkCl35() {

  return
    " 1.703500+4 3.466845+1          0          0          1          01725 2151     \n"
    " 1.703500+4 1.000000+0          0          0          1          01725 2151     \n"
    " 1.000000-5 1.200000+6          1          7          0          01725 2151     \n"
    " 0.000000+0 0.000000+0          1          3          6          01725 2151     \n"
    " 0.000000+0 0.000000+0          3          0         36          61725 2151     \n"
    " 0.000000+0 3.565932+1 0.000000+0 1.700000+1 1.000000+0 0.000000+01725 2151     \n"
    " 0.000000+0-1.000000+0 0.000000+0 1.020000+2 0.000000+0 1.000000+01725 2151     \n"
    " 1.000000+0 3.466845+1 0.000000+0 1.700000+1 5.000000-1 1.500000+01725 2151     \n"
    " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 0.000000+01725 2151     \n"
    " 9.986235-1 3.466863+1 1.000000+0 1.600000+1 5.000000-1 1.500000+01725 2151     \n"
    " 6.152200+5 1.000000+0 0.000000+0 6.000000+2 0.000000+0 0.000000+01725 2151     \n"
    "-0.000000+0-1.000000+0          0          0         12          21725 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01725 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21725 2151     \n"
    " 2.239640+4 1.000000+0 1.100000+0 0.000000+0 0.000000+0 0.000000+01725 2151     \n"
    " 5.478545+5 2.000000+0 2.100000+0 0.000000+0 0.000000+0 0.000000+01725 2151     \n"
    "-1.000000+0 0.000000+0          0          0         30          51725 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01725 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 3.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 3.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21725 2151     \n"
    " 4.250762+3 3.000000+0 3.100000+0 3.200000+0 3.300000+0 3.400000+01725 2151     \n"
    " 1.435502+6 4.000000+0 4.100000+0 4.200000+0 4.300000+0 4.400000+01725 2151     \n"
    " 1.000000+0 0.000000+0          0          0         18          31725 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01725 2151     \n"
    " 2.000000+0 0.000000+0 1.000000+0 0.000000+0 3.667980-1 4.822220-11725 2151     \n"
    " 3.000000+0 0.000000+0 1.000000+0 0.000000+0 3.667980-1 4.822220-11725 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21725 2151     \n"
    " 5.493200+4 5.000000+0 5.100000+0 5.200000+0 0.000000+0 0.000000+01725 2151     \n"
    " 1.205687+6 6.000000+0 6.100000+0 6.200000+0 0.000000+0 0.000000+01725 2151     \n"
    "-2.000000+0 0.000000+0          0          0         30          51725 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01725 2151     \n"
    " 2.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 3.000000+0 1.000000+0 1.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 3.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21725 2151     \n"
    "-3.369334+5 7.000000+0 7.100000+0 7.200000+0 7.300000+0 7.400000+01725 2151     \n"
    " 1.441365+6 8.000000+0 8.100000+0 8.200000+0 8.300000+0 8.400000+01725 2151     \n"
    " 2.000000+0 0.000000+0          0          0         18          31725 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01725 2151     \n"
    " 2.000000+0 0.000000+0 2.000000+0 0.000000+0 3.667980-1 4.822220-11725 2151     \n"
    " 3.000000+0 0.000000+0 2.000000+0 0.000000+0 3.667980-1 4.822220-11725 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21725 2151     \n"
    "-1.806500+2 9.000000+0 9.100000+0 9.200000+0 0.000000+0 0.000000+01725 2151     \n"
    " 7.563145+6 1.000000+1 1.010000+1 1.020000+1 0.000000+0 0.000000+01725 2151     \n"
    "-3.000000+0 0.000000+0          0          0         18          31725 2151     \n"
    " 1.000000+0 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+01725 2151     \n"
    " 2.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 3.000000+0 1.000000+0 2.000000+0 0.000000+0 4.888750-1 4.822220-11725 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          21725 2151     \n"
    " 1.635612+4 1.100000+1 1.110000+1 1.120000+1 0.000000+0 0.000000+01725 2151     \n"
    " 1.485128+6 1.200000+1 1.210000+1 1.220000+1 0.000000+0 0.000000+01725 2151     \n"
    "                                                                  1725 2  0     \n";
  }

  std::string chunkSr88() {

  return
    " 3.808800+4 8.715000+1          0          0          1          03837 2151     \n"
    " 3.808800+4 1.000000+0          0          0          1          03837 2151     \n"
    " 1.000000-5 9.500000+5          1          7          0          03837 2151     \n"
    " 0.000000+0 0.000000+0          1          3          7          03837 2151     \n"
    " 0.000000+0 0.000000+0          2          0         24          43837 2151     \n"
    " 0.000000+0 8.815046+1 0.000000+0 3.800000+1 1.000000+0 0.000000+03837 2151     \n"
    " 0.000000+0-1.000000+0 0.000000+0 1.020000+2 0.000000+0 1.000000+03837 2151     \n"
    " 1.000000+0 8.715046+1 0.000000+0 3.800000+1 5.000000-1 0.000000+03837 2151     \n"
    " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 1.000000+03837 2151     \n"
    "-5.000000-1 0.000000+0          1          0         12          23837 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 2.000000+0 1.000000+0 5.000000-1 0.000000+0 7.100000-1 7.100000-13837 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          23837 2151     \n"
    " 1.241000+4 1.000000+0 1.100000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 8.331700+5 2.000000+0 2.100000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 0.000000+0 0.000000+0          2          2          0          03837 2151     \n"
    " 0.000000+0 9.550000+5          0          0          5          03837 2151     \n"
    " 4.500000-1 3.200000-7 0.000000+0 7.500000-2 0.000000+0           3837 2151     \n"
    " 5.000000-1 0.000000+0          1          0         12          23837 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 2.000000+0 0.000000+0 5.000000-1 0.000000+0 6.800000-1 7.100000-13837 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          23837 2151     \n"
    " 1.384000+4 3.000000+0 3.100000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 9.433400+5 4.000000+0 4.100000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 0.000000+0 0.000000+0          2          2          0          03837 2151     \n"
    " 0.000000+0 9.550000+5          0          0          5          03837 2151     \n"
    "-4.300000-2 2.800000-8 0.000000+0 1.000000-2 0.000000+0           3837 2151     \n"
    "-1.500000+0 0.000000+0          1          0         12          23837 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 2.000000+0 1.000000+0 5.000000-1 0.000000+0 7.100000-1 7.100000-13837 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          23837 2151     \n"
    " 1.821000+4 5.000000+0 5.100000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 9.482300+5 6.000000+0 6.100000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 0.000000+0 0.000000+0          2          2          0          03837 2151     \n"
    " 0.000000+0 9.550000+5          0          0          5          03837 2151     \n"
    " 4.300000-1-1.800000-7 0.000000+0 2.200000-1 0.000000+0           3837 2151     \n"
    " 1.500000+0 0.000000+0          1          0         12          23837 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 2.000000+0 2.000000+0 5.000000-1 0.000000+0 7.100000-1 7.100000-13837 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          23837 2151     \n"
    " 2.665300+5 7.000000+0 7.100000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 8.749400+5 8.000000+0 8.100000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 0.000000+0 0.000000+0          2          2          0          03837 2151     \n"
    " 0.000000+0 9.550000+5          0          0          5          03837 2151     \n"
    "-7.000000-1 2.300000-6 0.000000+0 4.100000-2 0.000000+0           3837 2151     \n"
    "-2.500000+0 0.000000+0          1          0         12          23837 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 2.000000+0 3.000000+0 5.000000-1 0.000000+0 7.100000-1 7.100000-13837 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          23837 2151     \n"
    " 4.084600+5 9.000000+0 9.100000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 8.994400+5 1.000000+1 1.010000+1 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 0.000000+0 0.000000+0          2          2          0          03837 2151     \n"
    " 0.000000+0 9.550000+5          0          0          5          03837 2151     \n"
    " 1.000000-3 4.600000-7 0.000000+0 2.400000-1 0.000000+0           3837 2151     \n"
    " 2.500000+0 0.000000+0          1          0         12          23837 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 2.000000+0 2.000000+0 5.000000-1 0.000000+0 7.100000-1 7.100000-13837 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          23837 2151     \n"
    " 4.098200+5 1.100000+1 1.110000+1 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 8.496100+5 1.200000+1 1.210000+1 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 0.000000+0 0.000000+0          2          2          0          03837 2151     \n"
    " 0.000000+0 9.550000+5          0          0          5          03837 2151     \n"
    "-2.500000+0 3.300000-6 0.000000+0 2.600000-3 0.000000+0           3837 2151     \n"
    "-3.500000+0 0.000000+0          1          0         12          23837 2151     \n"
    " 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 2.000000+0 3.000000+0 5.000000-1 0.000000+0 7.100000-1 7.100000-13837 2151     \n"
    " 0.000000+0 0.000000+0          0          2         12          23837 2151     \n"
    " 5.288400+5 1.300000+1 1.310000+1 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 9.475600+5 1.400000+1 1.410000+1 0.000000+0 0.000000+0 0.000000+03837 2151     \n"
    " 0.000000+0 0.000000+0          2          2          0          03837 2151     \n"
    " 0.000000+0 9.550000+5          0          0          5          03837 2151     \n"
    " 1.000000-3 9.000000-8 0.000000+0 1.900000-1 0.000000+0           3837 2151     \n"
    "                                                                  3837 2  0     \n";
}