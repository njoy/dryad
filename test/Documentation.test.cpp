// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/Documentation.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

void verifyChunk( const Documentation& );

SCENARIO( "Documentation" ) {

  GIVEN( "valid metadata" ) {

    WHEN( "the data is given explicitly" ) {

      std::optional< double > awr = 15.8619530;
      std::optional< int > library = 0;
      std::optional< std::pair< int, int > > version = std::make_pair( 8, 1 );
      std::optional< std::string > description =
        "  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n"
        " NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n"
        "---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n"
        "----- ATOMIC RELAXATION DATA                                      \n"
        "------ ENDF-6                                                     \n"
        "==================================================================\n"
        "The Livermore Evaluated Atomic Data Library (EADL) in the         \n"
        "ENDF-6 Format. Translated from the Livermore ENDL format          \n"
        "to the ENDF-6 Format.                                             \n"
        "==================================================================\n";

      Documentation chunk( std::move( awr ), std::move( library ),
                           std::move( version ), std::move( description ) );

      THEN( "Documentation can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "setter functions" ) {

    WHEN( "an instance of Documentation is given" ) {

      Documentation chunk( 15.8619530, 0, std::make_pair( 8, 1 ),
                           "  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n"
                           " NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n"
                           "---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n"
                           "----- ATOMIC RELAXATION DATA                                      \n"
                           "------ ENDF-6                                                     \n"
                           "==================================================================\n"
                           "The Livermore Evaluated Atomic Data Library (EADL) in the         \n"
                           "ENDF-6 Format. Translated from the Livermore ENDL format          \n"
                           "to the ENDF-6 Format.                                             \n"
                           "==================================================================\n" );

      THEN( "the awr can be changed" ) {

        double newawr = 25.;
        double original = 15.8619530;

        chunk.awr( newawr );

        CHECK( newawr == chunk.awr() );

        chunk.awr( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the library can be changed" ) {

        int newlibrary = 1;
        int original = 0;

        chunk.library( newlibrary );

        CHECK( newlibrary == chunk.library() );

        chunk.library( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the version can be changed" ) {

        std::optional< std::pair< int, int > > newversion = std::nullopt;
        std::optional< std::pair< int, int > > original = std::make_pair( 8, 1 );

        chunk.version( newversion );

        CHECK( newversion == chunk.version() );

        chunk.version( original );

        verifyChunk( chunk );
      } // THEN

      THEN( "the description can be changed" ) {

        std::string newdescription =
            "Something different                                               \n";
        std::string original =
            "  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n"
            " NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n"
            "---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n"
            "----- ATOMIC RELAXATION DATA                                      \n"
            "------ ENDF-6                                                     \n"
            "==================================================================\n"
            "The Livermore Evaluated Atomic Data Library (EADL) in the         \n"
            "ENDF-6 Format. Translated from the Livermore ENDL format          \n"
            "to the ENDF-6 Format.                                             \n"
            "==================================================================\n";

        chunk.description( newdescription );

        CHECK( newdescription == chunk.description() );

        chunk.description( original );

        verifyChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of Documentation are given" ) {

      Documentation left( 15.8619530, 0, std::make_pair( 8, 1 ),
                          "  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n"
                          " NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n"
                          "---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n"
                          "----- ATOMIC RELAXATION DATA                                      \n"
                          "------ ENDF-6                                                     \n"
                          "==================================================================\n"
                          "The Livermore Evaluated Atomic Data Library (EADL) in the         \n"
                          "ENDF-6 Format. Translated from the Livermore ENDL format          \n"
                          "to the ENDF-6 Format.                                             \n"
                          "==================================================================\n" );
      Documentation equal( 15.8619530, 0, std::make_pair( 8, 1 ),
                           "  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n"
                           " NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n"
                           "---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n"
                           "----- ATOMIC RELAXATION DATA                                      \n"
                           "------ ENDF-6                                                     \n"
                           "==================================================================\n"
                           "The Livermore Evaluated Atomic Data Library (EADL) in the         \n"
                           "ENDF-6 Format. Translated from the Livermore ENDL format          \n"
                           "to the ENDF-6 Format.                                             \n"
                           "==================================================================\n" );
      Documentation different( 15.8619530, 0, std::make_pair( 8, 1 ),
                               "this is different                                                 \n" );

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
} // SCENARIO

void verifyChunk( const Documentation& chunk ) {

  std::string description =
    "  8-O -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen                       \n"
    " NDS-IAEA-224         DIST-AUG24 REV1-NOV23            20240830   \n"
    "---- ENDF/B-VIII.1    MATERIAL  800         REVISION 1            \n"
    "----- ATOMIC RELAXATION DATA                                      \n"
    "------ ENDF-6                                                     \n"
    "==================================================================\n"
    "The Livermore Evaluated Atomic Data Library (EADL) in the         \n"
    "ENDF-6 Format. Translated from the Livermore ENDL format          \n"
    "to the ENDF-6 Format.                                             \n"
    "==================================================================\n";

  CHECK( 15.8619530 == chunk.awr() );
  CHECK( 0 == chunk.library() );
  CHECK( 8 == chunk.version()->first );
  CHECK( 1 == chunk.version()->second );
  CHECK( description == chunk.description() );
}
