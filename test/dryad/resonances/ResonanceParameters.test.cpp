// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/ResonanceParameters.hpp"

// other includes

// convenience typedefs
using namespace njoy;
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "ResonanceParameters" ) {

  GIVEN( "valid data for ResonanceParameters" ) {

    ParticlePair photon_pair(
        Particle( id::ParticleID::photon(), 0, 1, +1 ),
        Particle( id::ParticleID( "Cl36[all]" ),
                  35.65932 * constants::neutron_mass, 0, +1 ) );
    ParticlePair neutron_pair(
        Particle( id::ParticleID::neutron(), constants::neutron_mass, 0.5, +1 ),
        Particle( id::ParticleID( "Cl35" ),
                  34.66845 * constants::neutron_mass, 1.5, +1 ) );

    ChannelRadii zero_radii( 0., 0. );
    ChannelRadii resolved_radii( 4.822220, 3.667980 );

    SpinGroup spingroup( { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                             neutron_pair, photon_pair, 0., std::nullopt,
                             zero_radii, false },
                           { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                             neutron_pair, neutron_pair, 0., std::nullopt,
                             resolved_radii } },
                         { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                             id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) },
                           { 1. }, { { 2. }, { 3. } } },
                         Formalism::ReichMoore,
                         BoundaryCondition::ShiftFactor );

    CompoundSystem resolved( 1e-5, 1e+4, { spingroup } );

    ParticlePair capture_pair(
        Particle( id::ParticleID::photon(), 0, 1, +1 ),
        Particle( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 ) );
    ParticlePair elastic_pair(
        Particle( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 ),
        Particle( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 ) );

    ChannelRadii capture_radii( 0. );
    ChannelRadii unresolved_radii( 4.822220, 3.667980 );

    UnresolvedChannel capture( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                               elastic_pair, capture_pair,
                               0., std::nullopt, capture_radii );
    UnresolvedChannel elastic( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                               elastic_pair, elastic_pair,
                               0., std::nullopt, unresolved_radii );

    UnresolvedResonanceTable table(
        { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
          id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) },
        { TabulatedAverageWidths( { 1e+4, 1e+6 }, { 0.1, 0.4 } ),
          TabulatedAverageWidths( { 1e+4, 1e+6 }, { 1.1, 1.4 } ) },
        TabulatedLevelSpacing( { 1e+4, 1e+6 }, { 10., 40. } ) );

    UnresolvedSpinGroup unresolved_spingroup( { capture, elastic }, table );

    UnresolvedCompoundSystem unresolved( 1e+4, 1e+6,
                                         { unresolved_spingroup } );

    THEN( "ResonanceParameters can be constructed with resolved data only, without the unresolved argument" ) {

      ResonanceParameters chunk( { resolved } );

      CHECK( 1 == chunk.resolved().size() );
      CHECK( resolved == chunk.resolved()[0] );
      CHECK_THAT( 1e-5, WithinRel( chunk.resolved()[0].lowerEnergyLimit() ) );
      CHECK_THAT( 1e+4, WithinRel( chunk.resolved()[0].upperEnergyLimit() ) );

      CHECK( false == chunk.unresolved().has_value() );
    } // THEN

    THEN( "ResonanceParameters can be constructed with resolved data only, using an explicit nullopt" ) {

      ResonanceParameters chunk( { resolved }, std::nullopt );

      CHECK( 1 == chunk.resolved().size() );
      CHECK( resolved == chunk.resolved()[0] );

      CHECK( false == chunk.unresolved().has_value() );
    } // THEN

    THEN( "ResonanceParameters can be constructed with resolved and unresolved data" ) {

      ResonanceParameters chunk( { resolved }, unresolved );

      CHECK( 1 == chunk.resolved().size() );
      CHECK( resolved == chunk.resolved()[0] );

      CHECK( true == chunk.unresolved().has_value() );
      CHECK( unresolved == chunk.unresolved().value() );
      CHECK_THAT( 1e+4,
                  WithinRel( chunk.unresolved()->lowerEnergyLimit() ) );
      CHECK_THAT( 1e+6,
                  WithinRel( chunk.unresolved()->upperEnergyLimit() ) );

      // the resolved region ends where the unresolved region begins
      CHECK_THAT( chunk.resolved().back().upperEnergyLimit(),
                  WithinRel( chunk.unresolved()->lowerEnergyLimit() ) );
    } // THEN

    THEN( "ResonanceParameters can be constructed with multiple resolved compound systems" ) {

      CompoundSystem lower( 1e-5, 1e+3, { spingroup } );
      CompoundSystem upper( 1e+3, 1e+4, { spingroup } );

      ResonanceParameters chunk( { lower, upper }, unresolved );

      CHECK( 2 == chunk.resolved().size() );
      CHECK_THAT( 1e-5, WithinRel( chunk.resolved()[0].lowerEnergyLimit() ) );
      CHECK_THAT( 1e+3, WithinRel( chunk.resolved()[1].lowerEnergyLimit() ) );

      CHECK( true == chunk.unresolved().has_value() );
    } // THEN

    THEN( "ResonanceParameters can be constructed with unresolved data only" ) {

      ResonanceParameters chunk( {}, unresolved );

      CHECK( 0 == chunk.resolved().size() );

      CHECK( true == chunk.unresolved().has_value() );
      CHECK( unresolved == chunk.unresolved().value() );
    } // THEN

    WHEN( "the setters are used on an empty ResonanceParameters" ) {

      ResonanceParameters chunk;

      THEN( "the resolved data can be set" ) {

        chunk.resolved( { resolved } );

        CHECK( 1 == chunk.resolved().size() );
        CHECK( resolved == chunk.resolved()[0] );
        CHECK( false == chunk.unresolved().has_value() );
      } // THEN

      THEN( "the unresolved data can be overwritten" ) {

        UnresolvedResonanceTable other_table(
            { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
              id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) },
            { TabulatedAverageWidths( { 1e+4, 1e+6 }, { 0.1, 0.4 } ),
              TabulatedAverageWidths( { 1e+4, 1e+6 }, { 1.1, 1.4 } ) },
            TabulatedLevelSpacing( { 1e+4, 1e+6 }, { 20., 80. } ) );

        UnresolvedCompoundSystem other_unresolved(
            1e+4, 1e+6,
            { UnresolvedSpinGroup( { capture, elastic }, other_table ) } );

        chunk.unresolved( unresolved );
        chunk.unresolved( other_unresolved );

        CHECK( true == chunk.unresolved().has_value() );
        CHECK( other_unresolved == chunk.unresolved().value() );
        CHECK( unresolved != chunk.unresolved().value() );
      } // THEN
    } // WHEN

    WHEN( "two instances of ResonanceParameters are given" ) {

      // a resolved compound system with the resonance at 2 eV instead of 1 eV
      SpinGroup other_spingroup(
          { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
              neutron_pair, photon_pair, 0., std::nullopt,
              zero_radii, false },
            { id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
              neutron_pair, neutron_pair, 0., std::nullopt,
              resolved_radii } },
          { { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
              id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) },
            { 2. }, { { 2. }, { 3. } } },
          Formalism::ReichMoore,
          BoundaryCondition::ShiftFactor );

      CompoundSystem other_resolved( 1e-5, 1e+4, { other_spingroup } );

      // a resolved compound system with the same spin group but a different
      // upper energy limit
      CompoundSystem resolved_limits( 1e-5, 5e+3, { spingroup } );

      // an unresolved compound system with a different level spacing
      UnresolvedResonanceTable other_table(
          { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
            id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) },
          { TabulatedAverageWidths( { 1e+4, 1e+6 }, { 0.1, 0.4 } ),
            TabulatedAverageWidths( { 1e+4, 1e+6 }, { 1.1, 1.4 } ) },
          TabulatedLevelSpacing( { 1e+4, 1e+6 }, { 20., 80. } ) );

      UnresolvedCompoundSystem other_unresolved(
          1e+4, 1e+6,
          { UnresolvedSpinGroup( { capture, elastic }, other_table ) } );

      // an unresolved compound system with the same spin group but a
      // different upper energy limit
      UnresolvedCompoundSystem unresolved_limits( 1e+4, 5e+5,
                                                  { unresolved_spingroup } );

      ResonanceParameters left( { resolved }, unresolved );
      ResonanceParameters equal( { resolved }, unresolved );
      ResonanceParameters different_resolved( { other_resolved }, unresolved );
      ResonanceParameters different_unresolved( { resolved },
                                                other_unresolved );
      ResonanceParameters resolved_only( { resolved } );
      ResonanceParameters unresolved_only( {}, unresolved );
      ResonanceParameters empty;

      THEN( "they can be compared" ) {

        CHECK( true  == ( left == left ) );
        CHECK( true  == ( left == equal ) );
        CHECK( false == ( left == different_resolved ) );
        CHECK( false == ( left == different_unresolved ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true  == ( left != different_resolved ) );
        CHECK( true  == ( left != different_unresolved ) );
      } // THEN

      THEN( "the energy limits of the unresolved data take part in the comparison" ) {

        ResonanceParameters limits( { resolved }, unresolved_limits );

        CHECK( false == ( left == limits ) );
        CHECK( true  == ( left != limits ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
