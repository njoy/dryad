// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/UnresolvedResonanceTable.hpp"
#include "njoy/dryad/id/ChannelID.hpp"


// other includes

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "UnresolvedResonanceTable" ) {

  GIVEN( "pre-built tabulated objects - ordered channels" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" )
    };
    std::vector< TabulatedAverageWidths > widths = {

      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } ),
      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } )
    };
    TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

    THEN( "an UnresolvedResonanceTable can be constructed from pre-built tabulated objects" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( widths ),
                                      std::move( spacings ) );

      CHECK( 2 == table.numberChannels() );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );
      CHECK( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) == table.channels()[1] );

      TabulatedAverageWidths expectedWidths0( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );

      TabulatedLevelSpacing expectedSpacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );
      CHECK( expectedSpacings == table.spacings() );

      // construction via either ctor should produce the same table
      UnresolvedResonanceTable rawTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                          id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                        { 1., 2., 3., 4. },
                                        { 10., 11., 12., 13. },
                                        { { 0.11, 0.12, 0.13, 0.14 },
                                          { 0.21, 0.22, 0.23, 0.24 } } );
      CHECK( rawTable == table );
    } // THEN
  } // GIVEN

  GIVEN( "pre-built tabulated objects - unordered channels" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" )
    };
    std::vector< TabulatedAverageWidths > widths = {

      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } ),
      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } )
    };
    TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

    THEN( "the channels and widths get sorted on construction" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( widths ),
                                      std::move( spacings ) );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );
      CHECK( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) == table.channels()[1] );

      CHECK( 0 == table.channelIndex( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ).value() );
      CHECK( 1 == table.channelIndex( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ).value() );

      TabulatedAverageWidths expectedWidths0( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );

      CHECK( expectedWidths0 == table.widths( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );
      CHECK( expectedWidths1 == table.widths( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );
    } // THEN
  } // GIVEN

  GIVEN( "pre-built tabulated objects with degrees of freedom" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" )
    };
    std::vector< TabulatedAverageWidths > widths = {

      TabulatedAverageWidths( 1, { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } ),
      TabulatedAverageWidths( 2, { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } )
    };
    TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

    THEN( "the degrees of freedom on the average widths are preserved" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( widths ),
                                      std::move( spacings ) );

      TabulatedAverageWidths expectedWidths0( 1, { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( 2, { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an UnresolvedResonanceTable involving multiple channels - fully ordered" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" )
    };
    std::vector< double > energies = { 1., 2., 3., 4. };
    std::vector< double > spacingValues = { 10., 11., 12., 13. };
    std::vector< std::vector< double > > widthValues = {

      { 0.11, 0.12, 0.13, 0.14 },
      { 0.21, 0.22, 0.23, 0.24 }
    };

    THEN( "an UnresolvedResonanceTable can be constructed" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( energies ),
                                      std::move( spacingValues ),
                                      std::move( widthValues ) );

      CHECK( 2 == table.numberChannels() );
      CHECK( 2 == table.channels().size() );
      CHECK( 2 == table.widths().size() );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );
      CHECK( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) == table.channels()[1] );

      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );
      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );
      CHECK( false == table.hasChannel( id::ChannelID( "n,U235->n,U235_e1{1,1/2,1/2+}" ) ) );

      CHECK( 0 == table.channelIndex( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ).value() );
      CHECK( 1 == table.channelIndex( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ).value() );

      // spacings
      TabulatedLevelSpacing expectedSpacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );
      CHECK( expectedSpacings == table.spacings() );

      // widths via vector access
      TabulatedAverageWidths expectedWidths0( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );

      // widths via channel lookup
      CHECK( expectedWidths0 == table.widths( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );
      CHECK( expectedWidths1 == table.widths( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an UnresolvedResonanceTable involving multiple channels - unordered" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" )
    };
    std::vector< double > energies = { 1., 2., 3., 4. };
    std::vector< double > spacingValues = { 10., 11., 12., 13. };
    std::vector< std::vector< double > > widthValues = {

      { 0.21, 0.22, 0.23, 0.24 },
      { 0.11, 0.12, 0.13, 0.14 }
    };

    THEN( "an UnresolvedResonanceTable can be constructed and the channels and widths will be ordered" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( energies ),
                                      std::move( spacingValues ),
                                      std::move( widthValues ) );

      CHECK( 2 == table.numberChannels() );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );
      CHECK( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) == table.channels()[1] );

      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );
      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );
      CHECK( false == table.hasChannel( id::ChannelID( "n,U235->n,U235_e1{1,1/2,1/2+}" ) ) );

      CHECK( 0 == table.channelIndex( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ).value() );
      CHECK( 1 == table.channelIndex( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ).value() );

      // verify the widths followed the permutation
      TabulatedAverageWidths expectedWidths0( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );

      CHECK( expectedWidths0 == table.widths( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );
      CHECK( expectedWidths1 == table.widths( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );

      // spacings should be unchanged
      TabulatedLevelSpacing expectedSpacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );
      CHECK( expectedSpacings == table.spacings() );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an UnresolvedResonanceTable with per-channel degrees of freedom" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" )
    };
    std::vector< double > energies = { 1., 2., 3., 4. };
    std::vector< double > spacingValues = { 10., 11., 12., 13. };
    std::vector< std::vector< double > > widthValues = {

      { 0.11, 0.12, 0.13, 0.14 },
      { 0.21, 0.22, 0.23, 0.24 }
    };
    std::vector< std::optional< int > > dofs = { 1, 2 };

    THEN( "the degrees of freedom are propagated into the average widths" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( energies ),
                                      std::move( spacingValues ),
                                      std::move( widthValues ),
                                      dofs );

      CHECK( 2 == table.numberChannels() );

      TabulatedAverageWidths expectedWidths0( 1, { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( 2, { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an UnresolvedResonanceTable with a partial dofs vector" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" )
    };
    std::vector< double > energies = { 1., 2., 3., 4. };
    std::vector< double > spacingValues = { 10., 11., 12., 13. };
    std::vector< std::vector< double > > widthValues = {

      { 0.11, 0.12, 0.13, 0.14 },
      { 0.21, 0.22, 0.23, 0.24 }
    };
    std::vector< std::optional< int > > dofs = { 1 };

    THEN( "channels beyond the supplied dofs use the default constructor" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( energies ),
                                      std::move( spacingValues ),
                                      std::move( widthValues ),
                                      dofs );

      TabulatedAverageWidths expectedWidths0( 1, { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an UnresolvedResonanceTable involving a single channel" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" )
    };
    std::vector< double > energies = { 1., 2., 3., 4. };
    std::vector< double > spacingValues = { 10., 11., 12., 13. };
    std::vector< std::vector< double > > widthValues = {

      { 0.11, 0.12, 0.13, 0.14 }
    };

    THEN( "an UnresolvedResonanceTable can be constructed" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( energies ),
                                      std::move( spacingValues ),
                                      std::move( widthValues ) );

      CHECK( 1 == table.numberChannels() );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );
      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );
      CHECK( 0 == table.channelIndex( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ).value() );

      TabulatedAverageWidths expectedWidths0( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths0 == table.widths( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );

      TabulatedLevelSpacing expectedSpacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );
      CHECK( expectedSpacings == table.spacings() );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of UnresolvedResonanceTable are given" ) {

      UnresolvedResonanceTable left( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                       id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                     { 1., 2., 3., 4. },
                                     { 10., 11., 12., 13. },
                                     { { 0.11, 0.12, 0.13, 0.14 },
                                       { 0.21, 0.22, 0.23, 0.24 } } );
      UnresolvedResonanceTable equal( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                        id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                      { 1., 2., 3., 4. },
                                      { 10., 11., 12., 13. },
                                      { { 0.11, 0.12, 0.13, 0.14 },
                                        { 0.21, 0.22, 0.23, 0.24 } } );
      UnresolvedResonanceTable different( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) },
                                          { 1., 2., 3., 4. },
                                          { 10., 11., 12., 13. },
                                          { { 0.11, 0.12, 0.13, 0.14 } } );

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

  GIVEN( "invalid data for an UnresolvedResonanceTable object" ) {

    WHEN( "the number of channels and rows of widthValues is inconsistent" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) },
                                                { 1., 2., 3., 4. },
                                                { 10., 11., 12., 13. },
                                                { { 0.11, 0.12, 0.13, 0.14 },
                                                  { 0.21, 0.22, 0.23, 0.24 } } ) );
      } // THEN
    } // WHEN

    WHEN( "the number of energies and number of widthValues per channel is inconsistent" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                                  id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                                { 1., 2., 3. },
                                                { 10., 11., 12. },
                                                { { 0.11, 0.12, 0.13, 0.14 },
                                                  { 0.21, 0.22, 0.23, 0.24 } } ) );
        CHECK_THROWS( UnresolvedResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                                  id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                                { 1., 2., 3., 4. },
                                                { 10., 11., 12., 13. },
                                                { { 0.11, 0.12, 0.13 },
                                                  { 0.21, 0.22, 0.23, 0.24 } } ) );
      } // THEN
    } // WHEN

    WHEN( "the number of energies and number of spacing values is inconsistent" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                                  id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                                { 1., 2., 3., 4. },
                                                { 10., 11., 12. },
                                                { { 0.11, 0.12, 0.13, 0.14 },
                                                  { 0.21, 0.22, 0.23, 0.24 } } ) );
      } // THEN
    } // WHEN

    WHEN( "the number of channels or energies is zero" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedResonanceTable( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
                                                  id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) },
                                                {},
                                                {},
                                                { { 0.11, 0.12, 0.13, 0.14 },
                                                  { 0.21, 0.22, 0.23, 0.24 } } ) );
        CHECK_THROWS( UnresolvedResonanceTable( {},
                                                { 1., 2., 3., 4. },
                                                { 10., 11., 12., 13. },
                                                { { 0.11, 0.12, 0.13, 0.14 },
                                                  { 0.21, 0.22, 0.23, 0.24 } } ) );
      } // THEN
    } // WHEN

    WHEN( "a channel is requested that is not in the table" ) {

      UnresolvedResonanceTable table( { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) },
                                      { 1., 2., 3., 4. },
                                      { 10., 11., 12., 13. },
                                      { { 0.11, 0.12, 0.13, 0.14 } } );

      THEN( "an exception is thrown by channelIndex() and widths(channel)" ) {

        CHECK_THROWS( table.channelIndex( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );
        CHECK_THROWS( table.widths( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
GIVEN( "valid data where channels share an (L, J) group but differ in channel spin" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{1,1/2,1/2-}" ),
      id::ChannelID( "n,U235->n,U235_e1{1,3/2,1/2-}" )
    };
    std::vector< double > energies = { 1., 2., 3., 4. };
    std::vector< double > spacingValues = { 10., 11., 12., 13. };
    std::vector< std::vector< double > > widthValues = {

      { 0.11, 0.12, 0.13, 0.14 },
      { 0.21, 0.22, 0.23, 0.24 }
    };

    THEN( "an UnresolvedResonanceTable can be constructed: channels in an (L, J) "
          "group may differ in channel spin s" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( energies ),
                                      std::move( spacingValues ),
                                      std::move( widthValues ) );

      CHECK( 2 == table.numberChannels() );
    } // THEN
  } // GIVEN
} // SCENARIO