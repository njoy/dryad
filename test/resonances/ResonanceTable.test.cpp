// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/resonances/ResonanceTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "ResonanceTable" ) {

  GIVEN( "valid data for a ResonanceTable involving multiple channels" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" )
    };
    std::vector< double > energies = { 1., 2., 3., 4. };
    std::vector< std::vector< double > > amplitudes = {

      { 11., 12., 13., 14. },
      { 21., 22., 23., 24. }
    };

    THEN( "a ResonanceTable can be constructed" ) {

      ResonanceTable table( std::move( channels ), std::move( energies ),
                            std::move( amplitudes ) );

      CHECK( 2 == table.numberChannels() );
      CHECK( 4 == table.numberResonances() );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );
      CHECK( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) == table.channels()[1] );

      CHECK_THAT( 1., WithinRel( table.energies()[0] ) );
      CHECK_THAT( 2., WithinRel( table.energies()[1] ) );
      CHECK_THAT( 3., WithinRel( table.energies()[2] ) );
      CHECK_THAT( 4., WithinRel( table.energies()[3] ) );

      CHECK_THAT( 11., WithinRel( table.reducedWidthAmplitudes()[0][0] ) );
      CHECK_THAT( 12., WithinRel( table.reducedWidthAmplitudes()[0][1] ) );
      CHECK_THAT( 13., WithinRel( table.reducedWidthAmplitudes()[0][2] ) );
      CHECK_THAT( 14., WithinRel( table.reducedWidthAmplitudes()[0][3] ) );
      CHECK_THAT( 21., WithinRel( table.reducedWidthAmplitudes()[1][0] ) );
      CHECK_THAT( 22., WithinRel( table.reducedWidthAmplitudes()[1][1] ) );
      CHECK_THAT( 23., WithinRel( table.reducedWidthAmplitudes()[1][2] ) );
      CHECK_THAT( 24., WithinRel( table.reducedWidthAmplitudes()[1][3] ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for a ResonanceTable involving a single channels" ) {

    id::ChannelID channel( "n,U235->n,U235{0,1/2,1/2+}" );
    std::vector< double > energies = { 1., 2., 3., 4. };
    std::vector< double > amplitudes = { 11., 12., 13., 14. };

    THEN( "a ResonanceTable can be constructed" ) {

      ResonanceTable table( std::move( channel ), std::move( energies ),
                            std::move( amplitudes ) );

      CHECK( 1 == table.numberChannels() );
      CHECK( 4 == table.numberResonances() );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );

      CHECK_THAT( 1., WithinRel( table.energies()[0] ) );
      CHECK_THAT( 2., WithinRel( table.energies()[1] ) );
      CHECK_THAT( 3., WithinRel( table.energies()[2] ) );
      CHECK_THAT( 4., WithinRel( table.energies()[3] ) );

      CHECK_THAT( 11., WithinRel( table.reducedWidthAmplitudes()[0][0] ) );
      CHECK_THAT( 12., WithinRel( table.reducedWidthAmplitudes()[0][1] ) );
      CHECK_THAT( 13., WithinRel( table.reducedWidthAmplitudes()[0][2] ) );
      CHECK_THAT( 14., WithinRel( table.reducedWidthAmplitudes()[0][3] ) );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ResonanceTable are given" ) {

      ResonanceTable left( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                             id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                           { 1., 2., 3., 4. },
                           { { 11., 12., 13., 14. },
                             { 21., 22., 23., 24. } } );
      ResonanceTable equal( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                              id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                            { 1., 2., 3., 4. },
                            { { 11., 12., 13., 14. },
                              { 21., 22., 23., 24. } } );
      ResonanceTable different( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                { 1., 2., 3. },
                                { 11., 12., 13. } );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an ResonanceTable object" ) {

    WHEN( "the number of channels and column is inconsistent" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) },
                                      { 1., 2., 3., 4. },
                                      { { 11., 12., 13., 14. },
                                        { 21., 22., 23., 24. } } ) );
      } // THEN
    } // WHEN

    WHEN( "the energies are not sorted" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                        id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                      { 1., 3., 2., 4. },
                                      { { 11., 12., 13., 14. },
                                        { 21., 22., 23., 24. } } ) );
      } // THEN
    } // WHEN

    WHEN( "the energies are not unique" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                        id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                      { 1., 2., 2., 4. },
                                      { { 11., 12., 13., 14. },
                                        { 21., 22., 23., 24. } } ) );
      } // THEN
    } // WHEN

    WHEN( "the number of energies and number of amplitudes is inconsistent" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                        id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                      { 1., 2., 3. },
                                      { { 11., 12., 13., 14. },
                                        { 21., 22., 23., 24. } } ) );
        CHECK_THROWS( ResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                        id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                      { 1., 2., 3., 4. },
                                      { { 11., 12., 13. },
                                        { 21., 22., 23., 24. } } ) );
      } // THEN
    } // WHEN

    WHEN( "the number of channels or resonances is zero" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                        id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                      {},
                                      { { 11., 12., 13., 14. },
                                        { 21., 22., 23., 24. } } ) );
        CHECK_THROWS( ResonanceTable( {},
                                      { 1., 2., 3., 4. },
                                      { { 11., 12., 13., 14. },
                                        { 21., 22., 23., 24. } } ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
