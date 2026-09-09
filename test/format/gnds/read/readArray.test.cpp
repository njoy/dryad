// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/format/gnds/read/readArray.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::format;

std::string chunk1();
std::string chunk2();
std::string chunk3();
std::string chunk5();
std::string chunk7();
std::string chunk8();
std::string chunk9();
std::string chunk10();
std::string chunk11();
std::string chunk12();

void verifyChunk1( const gnds::read::Array& );
void verifyChunk2( const gnds::read::Array& );
void verifyChunk3( const gnds::read::Array& );
void verifyChunk4( const gnds::read::Array& );
void verifyChunk5( const gnds::read::Array& );
void verifyChunk6( const gnds::read::Array& );
void verifyChunk7( const gnds::read::Array& );
void verifyChunk8( const gnds::read::Array& );
void verifyChunk9( const gnds::read::Array& );
void verifyChunk10( const gnds::read::Array& );
void verifyChunk11( const gnds::read::Array& );
void verifyChunk12( const gnds::read::Array& );

SCENARIO( "readArray" ) {

  GIVEN( "a GNDS array node - 1D - uncompressed" ) {

    pugi::xml_document document;
    document.load_string( chunk1().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk1( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 2D - uncompressed - row major" ) {

    pugi::xml_document document;
    document.load_string( chunk2().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk2( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 2D - uncompressed - column major" ) {

    pugi::xml_document document;
    document.load_string( chunk3().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk3( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 2D - diagonal compression - main diagonal only" ) {

    pugi::xml_document document;
    document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node gridded = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                      find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                      child( "mixed" ).child( "shortRangeSelfScalingVariance" ).
                                      child( "gridded2d" );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = gridded.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk4( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 2D - diagonal compression - banded" ) {

    pugi::xml_document document;
    document.load_string( chunk5().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk5( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 2D - lower triangular - row major" ) {

    pugi::xml_document document;
    document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node gridded = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                      find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                      child( "mixed" ).find_child_by_attribute( "covarianceMatrix", "label", "1" ).
                                      child( "gridded2d" );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = gridded.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk6( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 2D - upper triangular - anti-symmetric" ) {

    pugi::xml_document document;
    document.load_string( chunk7().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk7( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 2D - flattened" ) {

    pugi::xml_document document;
    document.load_string( chunk8().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk8( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 3D - flattened" ) {

    pugi::xml_document document;
    document.load_string( chunk9().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk9( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 3D - lower triangular symmetric" ) {

    pugi::xml_document document;
    document.load_string( chunk10().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk10( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 3D - lower triangular anti-symmetric" ) {

    pugi::xml_document document;
    document.load_string( chunk11().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk11( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a GNDS array node - 4D - lower triangular symmetric" ) {

    pugi::xml_document document;
    document.load_string( chunk12().c_str() );

    WHEN( "a single GNDS array node" ) {

      pugi::xml_node array = document.child( "array" );

      THEN( "it can be converted" ) {

        auto chunk = gnds::read::readArray( array );

        verifyChunk12( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "incorrect nodes are given" ) {

    pugi::xml_document document;
    document.load_string( chunk1().c_str() );

    pugi::xml_node values = document.child( "array" ).child( "values" );
    pugi::xml_node undefined = document.child( "undefined" );

    THEN( "exceptions are thrown" ) {

      CHECK_THROWS( gnds::read::readArray( values ) );                        // wrong node
      CHECK_THROWS( gnds::read::readArray( document.child( "undefined" ) ) ); // undefined node
    } // THEN
  } // WHEN
} // SCENARIO

std::string chunk1() {

  return "<array shape=\"3\">\n"
         "  <values>1 2 3</values>\n"
         "</array>\n";
}

void verifyChunk1( const gnds::read::Array& chunk ) {

  CHECK( 1 == chunk.shape.size() );
  CHECK( 3 == chunk.shape[0] );
  CHECK( 3 == chunk.values.size() );

  CHECK_THAT( 1., WithinRel( chunk.values[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.values[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[2] ) );
}

std::string chunk2() {

  return "<array shape=\"2,3\">\n"
         "  <values>1 2 3\n"
         "          4 5 6</values>\n"
         "</array>\n";
}

void verifyChunk2( const gnds::read::Array& chunk ) {

  CHECK( 2 == chunk.shape.size() );
  CHECK( 2 == chunk.shape[0] );
  CHECK( 3 == chunk.shape[1] );
  CHECK( 6 == chunk.values.size() );

  CHECK_THAT( 1., WithinRel( chunk.values[0 * 3 + 0] ) );
  CHECK_THAT( 2., WithinRel( chunk.values[0 * 3 + 1] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[0 * 3 + 2] ) );
  CHECK_THAT( 4., WithinRel( chunk.values[1 * 3 + 0] ) );
  CHECK_THAT( 5., WithinRel( chunk.values[1 * 3 + 1] ) );
  CHECK_THAT( 6., WithinRel( chunk.values[1 * 3 + 2] ) );
}

std::string chunk3() {

  return "<array shape=\"2,3\" storageOrder=\"column-major\">\n"
         "  <values>1 2 3\n"
         "          4 5 6</values>\n"
         "</array>\n";
}

void verifyChunk3( const gnds::read::Array& chunk ) {

  CHECK( 2 == chunk.shape.size() );
  CHECK( 2 == chunk.shape[0] );
  CHECK( 3 == chunk.shape[1] );
  CHECK( 6 == chunk.values.size() );

  CHECK_THAT( 1., WithinRel( chunk.values[0 * 3 + 0] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[0 * 3 + 1] ) );
  CHECK_THAT( 5., WithinRel( chunk.values[0 * 3 + 2] ) );
  CHECK_THAT( 2., WithinRel( chunk.values[1 * 3 + 0] ) );
  CHECK_THAT( 4., WithinRel( chunk.values[1 * 3 + 1] ) );
  CHECK_THAT( 6., WithinRel( chunk.values[1 * 3 + 2] ) );
}

void verifyChunk4( const gnds::read::Array& chunk ) {

  CHECK( 2 == chunk.shape.size() );
  CHECK( 12 == chunk.shape[0] );
  CHECK( 12 == chunk.shape[1] );
  CHECK( 144 == chunk.values.size() );

  for ( unsigned int i = 0; i < 12; ++i ) {

    for ( unsigned int j = 0; j < 12; ++j ) {

      if ( i != j ) {

        CHECK( 0. == chunk.values[i * 12 + j] );
      }
    }
  }

  CHECK_THAT( 0        , WithinRel( chunk.values[ 0 * 12 +  0] ) );
  CHECK_THAT( 2.2235e-6, WithinRel( chunk.values[ 1 * 12 +  1] ) );
  CHECK_THAT( 5.1343e-5, WithinRel( chunk.values[ 2 * 12 +  2] ) );
  CHECK_THAT( 1.4699e-5, WithinRel( chunk.values[ 3 * 12 +  3] ) );
  CHECK_THAT( 2.5148e-6, WithinRel( chunk.values[ 4 * 12 +  4] ) );
  CHECK_THAT( 4.8846e-6, WithinRel( chunk.values[ 5 * 12 +  5] ) );
  CHECK_THAT( 2.1413e-6, WithinRel( chunk.values[ 6 * 12 +  6] ) );
  CHECK_THAT( 1.3654e-6, WithinRel( chunk.values[ 7 * 12 +  7] ) );
  CHECK_THAT( 8.5116e-7, WithinRel( chunk.values[ 8 * 12 +  8] ) );
  CHECK_THAT( 3.4763e-7, WithinRel( chunk.values[ 9 * 12 +  9] ) );
  CHECK_THAT( 2.9932e-8, WithinRel( chunk.values[10 * 12 + 10] ) );
  CHECK_THAT( 4.1382e-9, WithinRel( chunk.values[11 * 12 + 11] ) );
}

std::string chunk5() {

  return "<array shape=\"4,4\" compression=\"diagonal\">"
         "  <values label=\"startingIndices\">0 0 0 1</values>\n"
         "  <values>1 3 5 7 2 4 6</values>\n"
         "</array>\n";
}

void verifyChunk5( const gnds::read::Array& chunk ) {

  CHECK( 2 == chunk.shape.size() );
  CHECK( 4 == chunk.shape[0] );
  CHECK( 4 == chunk.shape[1] );
  CHECK( 16 == chunk.values.size() );

  CHECK_THAT( 1., WithinRel( chunk.values[0 * 4 + 0] ) );
  CHECK_THAT( 2., WithinRel( chunk.values[0 * 4 + 1] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 * 4 + 2] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 * 4 + 3] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[1 * 4 + 0] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[1 * 4 + 1] ) );
  CHECK_THAT( 4., WithinRel( chunk.values[1 * 4 + 2] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[1 * 4 + 3] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[2 * 4 + 0] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[2 * 4 + 1] ) );
  CHECK_THAT( 5., WithinRel( chunk.values[2 * 4 + 2] ) );
  CHECK_THAT( 6., WithinRel( chunk.values[2 * 4 + 3] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[3 * 4 + 0] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[3 * 4 + 1] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[3 * 4 + 2] ) );
  CHECK_THAT( 7., WithinRel( chunk.values[3 * 4 + 3] ) );
}

void verifyChunk6( const gnds::read::Array& chunk ) {

  CHECK( 6 == chunk.shape[0] );
  CHECK( 6 == chunk.shape[1] );
  CHECK( 36 == chunk.values.size() );

  CHECK_THAT( 0., WithinRel( chunk.values[0 + 0 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 1 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 2 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 3 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 4 * 6] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[1 + 0 * 6] ) );
  CHECK_THAT( 1.251800e-2, WithinRel( chunk.values[1 + 1 * 6] ) );
  CHECK_THAT( 1.372900e-2, WithinRel( chunk.values[1 + 2 * 6] ) );
  CHECK_THAT( 3.462100e-3, WithinRel( chunk.values[1 + 3 * 6] ) );
  CHECK_THAT( 4.176900e-3, WithinRel( chunk.values[1 + 4 * 6] ) );
  CHECK_THAT( 3.404000e-3, WithinRel( chunk.values[1 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[2 + 0 * 6] ) );
  CHECK_THAT( 1.372900e-2, WithinRel( chunk.values[2 + 1 * 6] ) );
  CHECK_THAT( 1.557300e-2, WithinRel( chunk.values[2 + 2 * 6] ) );
  CHECK_THAT( 5.634300e-3, WithinRel( chunk.values[2 + 3 * 6] ) );
  CHECK_THAT( 5.288200e-3, WithinRel( chunk.values[2 + 4 * 6] ) );
  CHECK_THAT( 3.863500e-3, WithinRel( chunk.values[2 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[3 + 0 * 6] ) );
  CHECK_THAT( 3.462100e-3, WithinRel( chunk.values[3 + 1 * 6] ) );
  CHECK_THAT( 5.634300e-3, WithinRel( chunk.values[3 + 2 * 6] ) );
  CHECK_THAT( 8.970100e-3, WithinRel( chunk.values[3 + 3 * 6] ) );
  CHECK_THAT( 4.898600e-3, WithinRel( chunk.values[3 + 4 * 6] ) );
  CHECK_THAT( 1.896700e-3, WithinRel( chunk.values[3 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[4 + 0 * 6] ) );
  CHECK_THAT( 4.176900e-3, WithinRel( chunk.values[4 + 1 * 6] ) );
  CHECK_THAT( 5.288200e-3, WithinRel( chunk.values[4 + 2 * 6] ) );
  CHECK_THAT( 4.898600e-3, WithinRel( chunk.values[4 + 3 * 6] ) );
  CHECK_THAT( 3.694600e-3, WithinRel( chunk.values[4 + 4 * 6] ) );
  CHECK_THAT( 1.726800e-3, WithinRel( chunk.values[4 + 5 * 6] ) );

  CHECK_THAT( 0., WithinRel( chunk.values[5 + 0 * 6] ) );
  CHECK_THAT( 3.404000e-3, WithinRel( chunk.values[5 + 1 * 6] ) );
  CHECK_THAT( 3.863500e-3, WithinRel( chunk.values[5 + 2 * 6] ) );
  CHECK_THAT( 1.896700e-3, WithinRel( chunk.values[5 + 3 * 6] ) );
  CHECK_THAT( 1.726800e-3, WithinRel( chunk.values[5 + 4 * 6] ) );
  CHECK_THAT( 1.144800e-3, WithinRel( chunk.values[5 + 5 * 6] ) );
}

std::string chunk7() {

  return "<array shape=\"3,3\" symmetry=\"upper\" permutation=\"-1\">"
         "  <values>-1 2 1</values>\n"
         "</array>\n";
}

void verifyChunk7( const gnds::read::Array& chunk ) {

  CHECK( 2 == chunk.shape.size() );
  CHECK( 3 == chunk.shape[0] );
  CHECK( 3 == chunk.shape[1] );
  CHECK( 9 == chunk.values.size() );

  CHECK_THAT(  0., WithinRel( chunk.values[0 * 3 + 0] ) );
  CHECK_THAT( -1., WithinRel( chunk.values[0 * 3 + 1] ) );
  CHECK_THAT(  2., WithinRel( chunk.values[0 * 3 + 2] ) );
  CHECK_THAT(  1., WithinRel( chunk.values[1 * 3 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 3 + 1] ) );
  CHECK_THAT(  1., WithinRel( chunk.values[1 * 3 + 2] ) );
  CHECK_THAT( -2., WithinRel( chunk.values[2 * 3 + 0] ) );
  CHECK_THAT( -1., WithinRel( chunk.values[2 * 3 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 3 + 2] ) );
}

std::string chunk8() {

  return "<array shape=\"5,5\" compression=\"flattened\">"
         "  <values label=\"starts\">0 12 21 24</values>\n"
         "  <values label=\"lengths\">7 7 1 1</values>\n"
         "  <values>1 -1 0 -3 0 -2 5 4 6 4 -4 0 2 7 8 -5</values>\n"
         "</array>\n";
}

void verifyChunk8( const gnds::read::Array& chunk ) {

  CHECK( 2 == chunk.shape.size() );
  CHECK( 5 == chunk.shape[0] );
  CHECK( 5 == chunk.shape[1] );
  CHECK( 25 == chunk.values.size() );

  CHECK_THAT(  1., WithinRel( chunk.values[0 * 5 + 0] ) );
  CHECK_THAT( -1., WithinRel( chunk.values[0 * 5 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[0 * 5 + 2] ) );
  CHECK_THAT( -3., WithinRel( chunk.values[0 * 5 + 3] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[0 * 5 + 4] ) );
  CHECK_THAT( -2., WithinRel( chunk.values[1 * 5 + 0] ) );
  CHECK_THAT(  5., WithinRel( chunk.values[1 * 5 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 5 + 2] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 5 + 3] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 5 + 4] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 5 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 5 + 1] ) );
  CHECK_THAT(  4., WithinRel( chunk.values[2 * 5 + 2] ) );
  CHECK_THAT(  6., WithinRel( chunk.values[2 * 5 + 3] ) );
  CHECK_THAT(  4., WithinRel( chunk.values[2 * 5 + 4] ) );
  CHECK_THAT( -4., WithinRel( chunk.values[3 * 5 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[3 * 5 + 1] ) );
  CHECK_THAT(  2., WithinRel( chunk.values[3 * 5 + 2] ) );
  CHECK_THAT(  7., WithinRel( chunk.values[3 * 5 + 3] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[3 * 5 + 4] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[4 * 5 + 0] ) );
  CHECK_THAT(  8., WithinRel( chunk.values[4 * 5 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[4 * 5 + 2] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[4 * 5 + 3] ) );
  CHECK_THAT( -5., WithinRel( chunk.values[4 * 5 + 4] ) );
}

std::string chunk9() {

  return "<array shape=\"2,2,2\" compression=\"flattened\">"
         "  <values label=\"starts\">0 5</values>\n"
         "  <values label=\"lengths\">2 3</values>\n"
         "  <values>1 2 3 4 5</values>\n"
         "</array>\n";
}

void verifyChunk9( const gnds::read::Array& chunk ) {

  CHECK( 3 == chunk.shape.size() );
  CHECK( 2 == chunk.shape[0] );
  CHECK( 2 == chunk.shape[1] );
  CHECK( 2 == chunk.shape[2] );
  CHECK( 8 == chunk.values.size() );

  CHECK_THAT( 1., WithinRel( chunk.values[0 * 4 + 0 * 2 + 0] ) );
  CHECK_THAT( 2., WithinRel( chunk.values[0 * 4 + 0 * 2 + 1] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 * 4 + 1 * 2 + 0] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[0 * 4 + 1 * 2 + 1] ) );
  CHECK_THAT( 0., WithinRel( chunk.values[1 * 4 + 0 * 2 + 0] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[1 * 4 + 0 * 2 + 1] ) );
  CHECK_THAT( 4., WithinRel( chunk.values[1 * 4 + 1 * 2 + 0] ) );
  CHECK_THAT( 5., WithinRel( chunk.values[1 * 4 + 1 * 2 + 1] ) );
}

std::string chunk10() {

  return "<array shape=\"3,3,3\" symmetry=\"lower\">"
         "  <values>1 2 3 4 5 6 7 8 9 10</values>\n"
         "</array>\n";
}

void verifyChunk10( const gnds::read::Array& chunk ) {

  CHECK( 3 == chunk.shape.size() );
  CHECK( 3 == chunk.shape[0] );
  CHECK( 3 == chunk.shape[1] );
  CHECK( 3 == chunk.shape[2] );
  CHECK( 27 == chunk.values.size() );

  CHECK_THAT(  1., WithinRel( chunk.values[0 * 9 + 0 * 3 + 0] ) );
  CHECK_THAT(  2., WithinRel( chunk.values[0 * 9 + 0 * 3 + 1] ) );
  CHECK_THAT(  5., WithinRel( chunk.values[0 * 9 + 0 * 3 + 2] ) );
  CHECK_THAT(  2., WithinRel( chunk.values[0 * 9 + 1 * 3 + 0] ) );
  CHECK_THAT(  3., WithinRel( chunk.values[0 * 9 + 1 * 3 + 1] ) );
  CHECK_THAT(  6., WithinRel( chunk.values[0 * 9 + 1 * 3 + 2] ) );
  CHECK_THAT(  5., WithinRel( chunk.values[0 * 9 + 2 * 3 + 0] ) );
  CHECK_THAT(  6., WithinRel( chunk.values[0 * 9 + 2 * 3 + 1] ) );
  CHECK_THAT(  8., WithinRel( chunk.values[0 * 9 + 2 * 3 + 2] ) );
  CHECK_THAT(  2., WithinRel( chunk.values[1 * 9 + 0 * 3 + 0] ) );
  CHECK_THAT(  3., WithinRel( chunk.values[1 * 9 + 0 * 3 + 1] ) );
  CHECK_THAT(  6., WithinRel( chunk.values[1 * 9 + 0 * 3 + 2] ) );
  CHECK_THAT(  3., WithinRel( chunk.values[1 * 9 + 1 * 3 + 0] ) );
  CHECK_THAT(  4., WithinRel( chunk.values[1 * 9 + 1 * 3 + 1] ) );
  CHECK_THAT(  7., WithinRel( chunk.values[1 * 9 + 1 * 3 + 2] ) );
  CHECK_THAT(  6., WithinRel( chunk.values[1 * 9 + 2 * 3 + 0] ) );
  CHECK_THAT(  7., WithinRel( chunk.values[1 * 9 + 2 * 3 + 1] ) );
  CHECK_THAT(  9., WithinRel( chunk.values[1 * 9 + 2 * 3 + 2] ) );
  CHECK_THAT(  5., WithinRel( chunk.values[2 * 9 + 0 * 3 + 0] ) );
  CHECK_THAT(  6., WithinRel( chunk.values[2 * 9 + 0 * 3 + 1] ) );
  CHECK_THAT(  8., WithinRel( chunk.values[2 * 9 + 0 * 3 + 2] ) );
  CHECK_THAT(  6., WithinRel( chunk.values[2 * 9 + 1 * 3 + 0] ) );
  CHECK_THAT(  7., WithinRel( chunk.values[2 * 9 + 1 * 3 + 1] ) );
  CHECK_THAT(  9., WithinRel( chunk.values[2 * 9 + 1 * 3 + 2] ) );
  CHECK_THAT(  8., WithinRel( chunk.values[2 * 9 + 2 * 3 + 0] ) );
  CHECK_THAT(  9., WithinRel( chunk.values[2 * 9 + 2 * 3 + 1] ) );
  CHECK_THAT( 10., WithinRel( chunk.values[2 * 9 + 2 * 3 + 2] ) );
}

std::string chunk11() {

  return "<array shape=\"3,3,3\" symmetry=\"lower\" permutation=\"-1\">"
         "  <values>1</values>\n"
         "</array>\n";
}

void verifyChunk11( const gnds::read::Array& chunk ) {

  CHECK( 3 == chunk.shape.size() );
  CHECK( 3 == chunk.shape[0] );
  CHECK( 3 == chunk.shape[1] );
  CHECK( 3 == chunk.shape[2] );
  CHECK( 27 == chunk.values.size() );

  CHECK_THAT(  0., WithinRel( chunk.values[0 * 9 + 0 * 3 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[0 * 9 + 0 * 3 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[0 * 9 + 0 * 3 + 2] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[0 * 9 + 1 * 3 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[0 * 9 + 1 * 3 + 1] ) );
  CHECK_THAT( -1., WithinRel( chunk.values[0 * 9 + 1 * 3 + 2] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[0 * 9 + 2 * 3 + 0] ) );
  CHECK_THAT(  1., WithinRel( chunk.values[0 * 9 + 2 * 3 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[0 * 9 + 2 * 3 + 2] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 9 + 0 * 3 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 9 + 0 * 3 + 1] ) );
  CHECK_THAT(  1., WithinRel( chunk.values[1 * 9 + 0 * 3 + 2] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 9 + 1 * 3 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 9 + 1 * 3 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 9 + 1 * 3 + 2] ) );
  CHECK_THAT( -1., WithinRel( chunk.values[1 * 9 + 2 * 3 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 9 + 2 * 3 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[1 * 9 + 2 * 3 + 2] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 9 + 0 * 3 + 0] ) );
  CHECK_THAT( -1., WithinRel( chunk.values[2 * 9 + 0 * 3 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 9 + 0 * 3 + 2] ) );
  CHECK_THAT(  1., WithinRel( chunk.values[2 * 9 + 1 * 3 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 9 + 1 * 3 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 9 + 1 * 3 + 2] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 9 + 2 * 3 + 0] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 9 + 2 * 3 + 1] ) );
  CHECK_THAT(  0., WithinRel( chunk.values[2 * 9 + 2 * 3 + 2] ) );
}

std::string chunk12() {

  return "<array shape=\"2,2,2,2\" symmetry=\"lower\">"
         "  <values>1 2 3 4 5</values>\n"
         "</array>\n";
}

void verifyChunk12( const gnds::read::Array& chunk ) {

  CHECK( 4 == chunk.shape.size() );
  CHECK( 2 == chunk.shape[0] );
  CHECK( 2 == chunk.shape[1] );
  CHECK( 2 == chunk.shape[2] );
  CHECK( 2 == chunk.shape[3] );
  CHECK( 16 == chunk.values.size() );

  CHECK_THAT( 1., WithinRel( chunk.values[0 * 8 + 0 * 4 + 0 * 2 + 0] ) );
  CHECK_THAT( 2., WithinRel( chunk.values[0 * 8 + 0 * 4 + 0 * 2 + 1] ) );
  CHECK_THAT( 2., WithinRel( chunk.values[0 * 8 + 0 * 4 + 1 * 2 + 0] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[0 * 8 + 0 * 4 + 1 * 2 + 1] ) );
  CHECK_THAT( 2., WithinRel( chunk.values[0 * 8 + 1 * 4 + 0 * 2 + 0] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[0 * 8 + 1 * 4 + 0 * 2 + 1] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[0 * 8 + 1 * 4 + 1 * 2 + 0] ) );
  CHECK_THAT( 4., WithinRel( chunk.values[0 * 8 + 1 * 4 + 1 * 2 + 1] ) );
  CHECK_THAT( 2., WithinRel( chunk.values[1 * 8 + 0 * 4 + 0 * 2 + 0] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[1 * 8 + 0 * 4 + 0 * 2 + 1] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[1 * 8 + 0 * 4 + 1 * 2 + 0] ) );
  CHECK_THAT( 4., WithinRel( chunk.values[1 * 8 + 0 * 4 + 1 * 2 + 1] ) );
  CHECK_THAT( 3., WithinRel( chunk.values[1 * 8 + 1 * 4 + 0 * 2 + 0] ) );
  CHECK_THAT( 4., WithinRel( chunk.values[1 * 8 + 1 * 4 + 0 * 2 + 1] ) );
  CHECK_THAT( 4., WithinRel( chunk.values[1 * 8 + 1 * 4 + 1 * 2 + 0] ) );
  CHECK_THAT( 5., WithinRel( chunk.values[1 * 8 + 1 * 4 + 1 * 2 + 1] ) );
}
