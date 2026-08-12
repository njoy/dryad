// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/UnresolvedCompoundSystem.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

void verifyChunk( const UnresolvedCompoundSystem& );

SCENARIO( "UnresolvedCompoundSystem" ) {

  GIVEN( "valid data for an UnresolvedCompoundSystem" ) {

    // particles
    Particle g( id::ParticleID::photon(), 0, 1, +1 );
    Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
    Particle p( id::ParticleID::proton(), 1.00727646662, 0.5, +1 );
    Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
    Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );
    Particle s35( id::ParticleID( "S35" ), 34.9690307578, 1.5, +1 );

    // particle pairs
    ParticlePair elasticPair( n, cl35 );
    ParticlePair capturePair( g, cl36 );
    ParticlePair protonPair( p, s35 );

    // Q values
    double elasticQ = 0.0;
    double captureQ = 0.0;
    double protonQ = 6.150729e+5;

    // boundary conditions
    std::optional< double > boundary = std::nullopt;

    // channel radii
    ChannelRadii radii( 4.822220, 3.667980 );
    ChannelRadii captureRadii( 0. );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // spin group 0: l = 0, J = 1+
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    UnresolvedChannel capture0( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                                elasticPair, capturePair,
                                captureQ, boundary, captureRadii );
    UnresolvedChannel elastic0( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                                elasticPair, elasticPair,
                                elasticQ, boundary, radii );

    UnresolvedResonanceTable table0(
        { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
          id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) },
        { TabulatedAverageWidths( { 1., 4. }, { 0.1, 0.4 } ),
          TabulatedAverageWidths( { 1., 4. }, { 1.1, 1.4 } ) },
        TabulatedLevelSpacing( { 1., 4. }, { 10., 40. } ) );

    UnresolvedSpinGroup spingroup0( { capture0, elastic0 }, table0 );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // spin group 1: l = 0, J = 2+
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    UnresolvedChannel capture1( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
                                elasticPair, capturePair,
                                captureQ, boundary, captureRadii );
    UnresolvedChannel elastic1( id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ),
                                elasticPair, elasticPair,
                                elasticQ, boundary, radii );

    UnresolvedResonanceTable table1(
        { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
          id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ) },
        { TabulatedAverageWidths( { 1., 3., 4. }, { 0.1, 0.3, 0.4 } ),
          TabulatedAverageWidths( { 1., 3., 4. }, { 1.1, 1.3, 1.4 } ) },
        TabulatedLevelSpacing( { 1., 3., 4. }, { 10., 30., 40. } ) );

    UnresolvedSpinGroup spingroup1( { capture1, elastic1 }, table1 );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // spin group 2: l = 1, J = 1-
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    UnresolvedChannel capture2( id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ),
                                elasticPair, capturePair,
                                captureQ, boundary, captureRadii );
    UnresolvedChannel elastic2( id::ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ),
                                elasticPair, elasticPair,
                                elasticQ, boundary, radii );
    UnresolvedChannel proton2( id::ChannelID( "n,Cl35->p,S35{1,1,1-}" ),
                               elasticPair, protonPair,
                               protonQ, boundary, radii );

    UnresolvedResonanceTable table2(
        { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ),
          id::ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ),
          id::ChannelID( "n,Cl35->p,S35{1,1,1-}" ) },
        { TabulatedAverageWidths( { 1., 2., 4. }, { 0.1, 0.2, 0.4 } ),
          TabulatedAverageWidths( { 1., 2., 4. }, { 1.1, 1.2, 1.4 } ),
          TabulatedAverageWidths( { 1., 2., 4. }, { 2.1, 2.2, 2.4 } ) },
        TabulatedLevelSpacing( { 1., 2., 4. }, { 10., 20., 40. } ) );

    UnresolvedSpinGroup spingroup2( { capture2, elastic2, proton2 }, table2 );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // spin group 3: l = 2, J = 1+
    //
    // note: this group has the same Jpi as spin group 0 but a different
    //       orbital angular momentum, which is allowed in the unresolved
    //       resonance region
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    UnresolvedChannel capture3( id::ChannelID( "n,Cl35->g,Cl36[all]{2,0,1+}" ),
                                elasticPair, capturePair,
                                captureQ, boundary, captureRadii );
    UnresolvedChannel elastic3( id::ChannelID( "n,Cl35->n,Cl35{2,1,1+}" ),
                                elasticPair, elasticPair,
                                elasticQ, boundary, radii );

    UnresolvedResonanceTable table3(
        { id::ChannelID( "n,Cl35->g,Cl36[all]{2,0,1+}" ),
          id::ChannelID( "n,Cl35->n,Cl35{2,1,1+}" ) },
        { TabulatedAverageWidths( { 1., 4. }, { 0.1, 0.4 } ),
          TabulatedAverageWidths( { 1., 4. }, { 1.1, 1.4 } ) },
        TabulatedLevelSpacing( { 1., 4. }, { 10., 40. } ) );

    UnresolvedSpinGroup spingroup3( { capture3, elastic3 }, table3 );

    THEN( "an UnresolvedCompoundSystem can be constructed - with ordered "
          "spin groups" ) {

      UnresolvedCompoundSystem chunk( 1., 4.,
                                      { spingroup2, spingroup0,
                                        spingroup3, spingroup1 } );

      verifyChunk( chunk );
    } // THEN

    THEN( "an UnresolvedCompoundSystem can be constructed - with unordered "
          "spin groups" ) {

      UnresolvedCompoundSystem chunk( 1., 4.,
                                      { spingroup0, spingroup1,
                                        spingroup2, spingroup3 } );

      verifyChunk( chunk );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of UnresolvedCompoundSystem are given" ) {

      // particles
      Particle g( id::ParticleID::photon(), 0, 1, +1 );
      Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
      Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
      Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );

      // particle pairs
      ParticlePair elasticPair( n, cl35 );
      ParticlePair capturePair( g, cl36 );

      // channel radii
      ChannelRadii radii( 4.822220, 3.667980 );
      ChannelRadii captureRadii( 0. );

      UnresolvedChannel capture0( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                                  elasticPair, capturePair,
                                  0., std::nullopt, captureRadii );
      UnresolvedChannel elastic0( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                                  elasticPair, elasticPair,
                                  0., std::nullopt, radii );

      UnresolvedResonanceTable table0(
          { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
            id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) },
          { TabulatedAverageWidths( { 1., 4. }, { 0.1, 0.4 } ),
            TabulatedAverageWidths( { 1., 4. }, { 1.1, 1.4 } ) },
          TabulatedLevelSpacing( { 1., 4. }, { 10., 40. } ) );

      UnresolvedSpinGroup spingroup0( { capture0, elastic0 }, table0 );

      UnresolvedChannel capture1( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
                                  elasticPair, capturePair,
                                  0., std::nullopt, captureRadii );
      UnresolvedChannel elastic1( id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ),
                                  elasticPair, elasticPair,
                                  0., std::nullopt, radii );

      UnresolvedResonanceTable table1(
          { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
            id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ) },
          { TabulatedAverageWidths( { 1., 4. }, { 0.1, 0.4 } ),
            TabulatedAverageWidths( { 1., 4. }, { 1.1, 1.4 } ) },
          TabulatedLevelSpacing( { 1., 4. }, { 10., 40. } ) );

      UnresolvedSpinGroup spingroup1( { capture1, elastic1 }, table1 );

      UnresolvedCompoundSystem left( 1., 4., { spingroup0 } );
      UnresolvedCompoundSystem equal( 1., 4., { spingroup0 } );
      UnresolvedCompoundSystem different( 1., 4., { spingroup1 } );

      // note: unlike the resolved CompoundSystem, the energy limits are
      //       part of the comparison
      UnresolvedCompoundSystem limits( 1., 3., { spingroup0 } );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );
        CHECK( false == ( left == limits ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
        CHECK( true == ( left != limits ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an UnresolvedCompoundSystem" ) {

    // particles
    Particle g( id::ParticleID::photon(), 0, 1, +1 );
    Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
    Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
    Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );

    // particle pairs
    ParticlePair elasticPair( n, cl35 );
    ParticlePair capturePair( g, cl36 );

    // channel radii
    ChannelRadii radii( 4.822220, 3.667980 );
    ChannelRadii captureRadii( 0. );

    UnresolvedChannel capture( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                               elasticPair, capturePair,
                               0., std::nullopt, captureRadii );
    UnresolvedChannel elastic( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                               elasticPair, elasticPair,
                               0., std::nullopt, radii );

    UnresolvedResonanceTable table(
        { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
          id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) },
        { TabulatedAverageWidths( { 1., 4. }, { 0.1, 0.4 } ),
          TabulatedAverageWidths( { 1., 4. }, { 1.1, 1.4 } ) },
        TabulatedLevelSpacing( { 1., 4. }, { 10., 40. } ) );

    UnresolvedSpinGroup spingroup( { capture, elastic }, table );
  } // GIVEN
} // SCENARIO

void verifyChunk( const UnresolvedCompoundSystem& chunk ) {

  // particles
  Particle g( id::ParticleID::photon(), 0, 1, +1 );
  Particle n( id::ParticleID::neutron(), 1.00866491574, 0.5, +1 );
  Particle p( id::ParticleID::proton(), 1.00727646662, 0.5, +1 );
  Particle cl36( id::ParticleID( "Cl36" ), 35.9683050031, 0, +1 );
  Particle cl35( id::ParticleID( "Cl35" ), 34.9688491981, 1.5, +1 );
  Particle s35( id::ParticleID( "S35" ), 34.9690307578, 1.5, +1 );

  // particle pairs
  ParticlePair elasticPair( n, cl35 );
  ParticlePair capturePair( g, cl36 );
  ParticlePair protonPair( p, s35 );

  // Q values
  double elasticQ = 0.0;
  double captureQ = 0.0;
  double protonQ = 6.150729e+5;

  // boundary conditions
  std::optional< double > boundary = std::nullopt;

  // channel radii
  ChannelRadii radii( 4.822220, 3.667980 );
  ChannelRadii captureRadii( 0. );

  // channels and tables for spin group 0 ( l = 0, J = 1+ )
  UnresolvedChannel capture0( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
                              elasticPair, capturePair,
                              captureQ, boundary, captureRadii );
  UnresolvedChannel elastic0( id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ),
                              elasticPair, elasticPair,
                              elasticQ, boundary, radii );

  UnresolvedResonanceTable table0(
      { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,1+}" ),
        id::ChannelID( "n,Cl35->n,Cl35{0,1,1+}" ) },
      { TabulatedAverageWidths( { 1., 4. }, { 0.1, 0.4 } ),
        TabulatedAverageWidths( { 1., 4. }, { 1.1, 1.4 } ) },
      TabulatedLevelSpacing( { 1., 4. }, { 10., 40. } ) );

  // channels and tables for spin group 1 ( l = 0, J = 2+ )
  UnresolvedChannel capture1( id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
                              elasticPair, capturePair,
                              captureQ, boundary, captureRadii );
  UnresolvedChannel elastic1( id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ),
                              elasticPair, elasticPair,
                              elasticQ, boundary, radii );

  UnresolvedResonanceTable table1(
      { id::ChannelID( "n,Cl35->g,Cl36[all]{0,0,2+}" ),
        id::ChannelID( "n,Cl35->n,Cl35{0,2,2+}" ) },
      { TabulatedAverageWidths( { 1., 3., 4. }, { 0.1, 0.3, 0.4 } ),
        TabulatedAverageWidths( { 1., 3., 4. }, { 1.1, 1.3, 1.4 } ) },
      TabulatedLevelSpacing( { 1., 3., 4. }, { 10., 30., 40. } ) );

  // channels and tables for spin group 2 ( l = 1, J = 1- )
  UnresolvedChannel capture2( id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ),
                              elasticPair, capturePair,
                              captureQ, boundary, captureRadii );
  UnresolvedChannel elastic2( id::ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ),
                              elasticPair, elasticPair,
                              elasticQ, boundary, radii );
  UnresolvedChannel proton2( id::ChannelID( "n,Cl35->p,S35{1,1,1-}" ),
                             elasticPair, protonPair,
                             protonQ, boundary, radii );

  UnresolvedResonanceTable table2(
      { id::ChannelID( "n,Cl35->g,Cl36[all]{1,0,1-}" ),
        id::ChannelID( "n,Cl35->n,Cl35{1,1,1-}" ),
        id::ChannelID( "n,Cl35->p,S35{1,1,1-}" ) },
      { TabulatedAverageWidths( { 1., 2., 4. }, { 0.1, 0.2, 0.4 } ),
        TabulatedAverageWidths( { 1., 2., 4. }, { 1.1, 1.2, 1.4 } ),
        TabulatedAverageWidths( { 1., 2., 4. }, { 2.1, 2.2, 2.4 } ) },
      TabulatedLevelSpacing( { 1., 2., 4. }, { 10., 20., 40. } ) );

  // channels and tables for spin group 3 ( l = 2, J = 1+ )
  UnresolvedChannel capture3( id::ChannelID( "n,Cl35->g,Cl36[all]{2,0,1+}" ),
                              elasticPair, capturePair,
                              captureQ, boundary, captureRadii );
  UnresolvedChannel elastic3( id::ChannelID( "n,Cl35->n,Cl35{2,1,1+}" ),
                              elasticPair, elasticPair,
                              elasticQ, boundary, radii );

  UnresolvedResonanceTable table3(
      { id::ChannelID( "n,Cl35->g,Cl36[all]{2,0,1+}" ),
        id::ChannelID( "n,Cl35->n,Cl35{2,1,1+}" ) },
      { TabulatedAverageWidths( { 1., 4. }, { 0.1, 0.4 } ),
        TabulatedAverageWidths( { 1., 4. }, { 1.1, 1.4 } ) },
      TabulatedLevelSpacing( { 1., 4. }, { 10., 40. } ) );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  // content verification
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  CHECK_THAT( 1., WithinRel( chunk.lowerEnergyLimit() ) );
  CHECK_THAT( 4., WithinRel( chunk.upperEnergyLimit() ) );

  auto reactions = chunk.reactions();

  CHECK( 3 == reactions.size() );
  CHECK( id::ReactionID( "n,Cl35->g,Cl36[all]" ) == reactions[0] );
  CHECK( id::ReactionID( "n,Cl35->n,Cl35"      ) == reactions[1] );
  CHECK( id::ReactionID( "n,Cl35->p,S35"       ) == reactions[2] );

  auto groups = chunk.spinGroups();

  // spin groups: sorted by ( J, parity, l ) so the expected order is
  //   1- ( l = 1 ), 1+ ( l = 0 ), 1+ ( l = 2 ), 2+ ( l = 0 )
  CHECK( 4 == groups.size() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 0: l = 1, J = 1-
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  auto spingroup = groups[0];

  CHECK( 1 == spingroup.totalAngularMomentum() );
  CHECK( -1 == spingroup.parity() );

  CHECK( 3 == spingroup.channels().size() );
  CHECK( capture2 == spingroup.channels()[0] );
  CHECK( elastic2 == spingroup.channels()[1] );
  CHECK( proton2 == spingroup.channels()[2] );

  CHECK( table2 == spingroup.resonanceTable() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 1: l = 0, J = 1+
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[1];

  CHECK( 1 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  CHECK( 2 == spingroup.channels().size() );
  CHECK( capture0 == spingroup.channels()[0] );
  CHECK( elastic0 == spingroup.channels()[1] );

  CHECK( table0 == spingroup.resonanceTable() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 2: l = 2, J = 1+
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[2];

  CHECK( 1 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  CHECK( 2 == spingroup.channels().size() );
  CHECK( capture3 == spingroup.channels()[0] );
  CHECK( elastic3 == spingroup.channels()[1] );

  CHECK( table3 == spingroup.resonanceTable() );

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // spin group 3: l = 0, J = 2+
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  spingroup = groups[3];

  CHECK( 2 == spingroup.totalAngularMomentum() );
  CHECK( +1 == spingroup.parity() );

  CHECK( 2 == spingroup.channels().size() );
  CHECK( capture1 == spingroup.channels()[0] );
  CHECK( elastic1 == spingroup.channels()[1] );

  CHECK( table1 == spingroup.resonanceTable() );

}
