// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/resonances/UnresolvedResonanceTable.hpp"

// other includes
#include "njoy/dryad/id/ChannelID.hpp"

// convenience typedefs
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "UnresolvedResonanceTable" ) {

  GIVEN( "valid data for an UnresolvedResonanceTable - ordered channels" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" )
    };
    std::vector< TabulatedAverageWidths > widths = {

      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } ),
      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } )
    };
    TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

    THEN( "an UnresolvedResonanceTable can be constructed and members can be queried" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( widths ),
                                      std::move( spacings ) );

      CHECK( 2 == table.numberChannels() );
      CHECK( 2 == table.channels().size() );
      CHECK( 2 == table.widths().size() );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );
      CHECK( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) == table.channels()[1] );

      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );
      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );
      CHECK( false == table.hasChannel( id::ChannelID( "n,U235->n,U235_e1{1,1/2,1/2+}" ) ) );

      // spacings
      TabulatedLevelSpacing expectedSpacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );
      CHECK( expectedSpacings == table.spacings() );

      // widths via vector access
      TabulatedAverageWidths expectedWidths0( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );

      // widths via channel lookup
      CHECK( expectedWidths0 == table.channelWidths( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );
      CHECK( expectedWidths1 == table.channelWidths( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an UnresolvedResonanceTable - unordered channels" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" )
    };
    std::vector< TabulatedAverageWidths > widths = {

      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } ),
      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } )
    };
    TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

    THEN( "the channels and widths are ordered on construction" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( widths ),
                                      std::move( spacings ) );

      CHECK( 2 == table.numberChannels() );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );
      CHECK( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) == table.channels()[1] );

      // verify the widths followed the channel permutation
      TabulatedAverageWidths expectedWidths0( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );

      CHECK( expectedWidths0 == table.channelWidths( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );
      CHECK( expectedWidths1 == table.channelWidths( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );

      // spacings should be unchanged
      TabulatedLevelSpacing expectedSpacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );
      CHECK( expectedSpacings == table.spacings() );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an UnresolvedResonanceTable - degrees of freedom" ) {

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

      CHECK( 2 == table.numberChannels() );

      TabulatedAverageWidths expectedWidths0( 1, { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( 2, { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an UnresolvedResonanceTable - mixed degrees of freedom" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
      id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" )
    };
    std::vector< TabulatedAverageWidths > widths = {

      TabulatedAverageWidths( 1, { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } ),
      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } )
    };
    TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

    THEN( "channels with and without degrees of freedom can be mixed" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( widths ),
                                      std::move( spacings ) );

      TabulatedAverageWidths expectedWidths0( 1, { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      TabulatedAverageWidths expectedWidths1( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths1 == table.widths()[1] );
    } // THEN
  } // GIVEN

  GIVEN( "valid data for an UnresolvedResonanceTable - a single channel" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" )
    };
    std::vector< TabulatedAverageWidths > widths = {

      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } )
    };
    TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

    THEN( "an UnresolvedResonanceTable can be constructed" ) {

      UnresolvedResonanceTable table( channels, widths, spacings );

      CHECK( 1 == table.numberChannels() );

      CHECK( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) == table.channels()[0] );
      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );

      TabulatedAverageWidths expectedWidths0( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } );
      CHECK( expectedWidths0 == table.widths()[0] );
      CHECK( expectedWidths0 == table.channelWidths( id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) ) );

      TabulatedLevelSpacing expectedSpacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );
      CHECK( expectedSpacings == table.spacings() );
    } // THEN
  } // GIVEN

  GIVEN( "valid data where channels share an (L, J) group but differ in channel spin" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{1,1/2,1/2-}" ),
      id::ChannelID( "n,U235->n,U235_e1{1,3/2,1/2-}" )
    };
    std::vector< TabulatedAverageWidths > widths = {

      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } ),
      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } )
    };
    TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

    THEN( "an UnresolvedResonanceTable can be constructed: channels in an (L, J) "
          "group may differ in channel spin s" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( widths ),
                                      std::move( spacings ) );

      CHECK( 2 == table.numberChannels() );
    } // THEN
  } // GIVEN

  GIVEN( "valid data where several channels share the same (L, J, parity) spin group" ) {

    std::vector< id::ChannelID > channels = {

      id::ChannelID( "n,U235->n,U235{1,1/2,1/2-}" ),
      id::ChannelID( "n,U235->n,U235_e1{1,3/2,1/2-}" ),
      id::ChannelID( "n,U235->n,U235_e1{1,1/2,1/2-}" )
    };
    std::vector< TabulatedAverageWidths > widths = {

      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } ),
      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } ),
      TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.31, 0.32, 0.33, 0.34 } )
    };
    TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

    THEN( "an UnresolvedResonanceTable can be constructed: any number of channels "
          "sharing the same (L, J, parity) may be combined, regardless of channel spin s" ) {

      UnresolvedResonanceTable table( std::move( channels ),
                                      std::move( widths ),
                                      std::move( spacings ) );

      CHECK( 3 == table.numberChannels() );
      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235{1,1/2,1/2-}" ) ) );
      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235_e1{1,3/2,1/2-}" ) ) );
      CHECK( true == table.hasChannel( id::ChannelID( "n,U235->n,U235_e1{1,1/2,1/2-}" ) ) );
    } // THEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of UnresolvedResonanceTable are given" ) {

      std::vector< id::ChannelID > channels = {

        id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
        id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" )
      };
      std::vector< TabulatedAverageWidths > widths = {

        TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } ),
        TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.21, 0.22, 0.23, 0.24 } )
      };
      TabulatedLevelSpacing spacings( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } );

      UnresolvedResonanceTable left( channels, widths, spacings );
      UnresolvedResonanceTable equal( channels, widths, spacings );

      UnresolvedResonanceTable different(
        { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) },
        { TabulatedAverageWidths( { 1., 2., 3., 4. }, { 0.11, 0.12, 0.13, 0.14 } ) },
        TabulatedLevelSpacing( { 1., 2., 3., 4. }, { 10., 11., 12., 13. } ) );

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

    std::vector< double > energies = { 1., 2., 3., 4. };
    std::vector< double > spacingValues = { 10., 11., 12., 13. };

    WHEN( "the number of channels and the number of average widths is inconsistent" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedResonanceTable(
          { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) },
          { TabulatedAverageWidths( energies, { 0.11, 0.12, 0.13, 0.14 } ),
            TabulatedAverageWidths( energies, { 0.21, 0.22, 0.23, 0.24 } ) },
          TabulatedLevelSpacing( energies, spacingValues ) ) );
      } // THEN
    } // WHEN

    WHEN( "the number of channels is zero" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedResonanceTable(
          {},
          {},
          TabulatedLevelSpacing( energies, spacingValues ) ) );
      } // THEN
    } // WHEN

    WHEN( "two channels share the same identifier" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( UnresolvedResonanceTable(
          { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ),
            id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) },
          { TabulatedAverageWidths( energies, { 0.11, 0.12, 0.13, 0.14 } ),
            TabulatedAverageWidths( energies, { 0.21, 0.22, 0.23, 0.24 } ) },
          TabulatedLevelSpacing( energies, spacingValues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a channel is requested that is not in the table" ) {

      UnresolvedResonanceTable table(
        { id::ChannelID( "n,U235->n,U235{0,1/2,1/2+}" ) },
        { TabulatedAverageWidths( energies, { 0.11, 0.12, 0.13, 0.14 } ) },
        TabulatedLevelSpacing( energies, spacingValues ) );

      THEN( "an exception is thrown by widths(channel)" ) {

        CHECK_THROWS( table.channelWidths( id::ChannelID( "n,U235->n,U235_e1{0,1/2,1/2+}" ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
