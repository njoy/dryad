// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/createMultiplicity.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;
using Multiplicity = std::variant< int, TabulatedMultiplicity, PolynomialMultiplicity >;

void verifyConstantChunk( const Multiplicity& );
void verifyPolynomialChunk( const Multiplicity& );
void verifyTabulatedChunk( const Multiplicity& );

SCENARIO( "createMultiplicity" ) {

  GIVEN( "GNDS multiplicity node with a constant value" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "e-001_H_000.endf.gnds.xml" );
    pugi::xml_node multiplicity = document.child( "reactionSuite" ).child( "reactions" ).
                                           find_child_by_attribute( "reaction", "ENDF_MT", "527" ).
                                           child( "outputChannel" ).child( "products" ).
                                           find_child_by_attribute( "product", "pid", "e-" ).
                                           child( "multiplicity" );

    WHEN( "a single multiplicity node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createMultiplicity( multiplicity );

        verifyConstantChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS multiplicity node with a table" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-093_Np_237.endf.gnds.xml" );
    pugi::xml_node multiplicity = document.child( "reactionSuite" ).child( "reactions" ).
                                           find_child_by_attribute( "reaction", "ENDF_MT", "18" ).
                                           child( "outputChannel" ).child( "products" ).
                                           find_child_by_attribute( "product", "pid", "n" ).
                                           child( "multiplicity" );

    WHEN( "a single multiplicity node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createMultiplicity( multiplicity );

        verifyTabulatedChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "GNDS multiplicity node with a polynomial series" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-094_Pu_237.jeff33.gnds.xml" );
    pugi::xml_node multiplicity = document.child( "reactionSuite" ).child( "reactions" ).
                                           find_child_by_attribute( "reaction", "ENDF_MT", "18" ).
                                           child( "outputChannel" ).child( "products" ).
                                           find_child_by_attribute( "product", "pid", "n" ).
                                           child( "multiplicity" );

    WHEN( "a single multiplicity node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::createMultiplicity( multiplicity );

        verifyPolynomialChunk( chunk );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

void verifyConstantChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< int >( chunk ) );

  auto value = std::get< int >( chunk );
  CHECK( 1 == value );
}

void verifyTabulatedChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< TabulatedMultiplicity >( chunk ) );

  auto multiplicity = std::get< TabulatedMultiplicity >( chunk );
  CHECK( true == multiplicity.isLinearised() );
  CHECK( 6 == multiplicity.numberPoints() );
  CHECK( 1 == multiplicity.numberRegions() );
  CHECK( 6 == multiplicity.energies().size() );
  CHECK( 6 == multiplicity.values().size() );
  CHECK( 1 == multiplicity.boundaries().size() );
  CHECK( 1 == multiplicity.interpolants().size() );
  CHECK( 5 == multiplicity.boundaries()[0] );
  CHECK( InterpolationType::LinearLinear == multiplicity.interpolants()[0] );
  CHECK_THAT( 1.0e-5, WithinRel( multiplicity.energies()[0] ) );
  CHECK_THAT( 4.0e+6, WithinRel( multiplicity.energies()[1] ) );
  CHECK_THAT( 7.0e+6, WithinRel( multiplicity.energies()[2] ) );
  CHECK_THAT( 1.1e+7, WithinRel( multiplicity.energies()[3] ) );
  CHECK_THAT( 1.2e+7, WithinRel( multiplicity.energies()[4] ) );
  CHECK_THAT( 2.0e+7, WithinRel( multiplicity.energies()[5] ) );
  CHECK_THAT( 2.625000, WithinRel( multiplicity.values()[0] ) );
  CHECK_THAT( 3.224250, WithinRel( multiplicity.values()[1] ) );
  CHECK_THAT( 3.677437, WithinRel( multiplicity.values()[2] ) );
  CHECK_THAT( 4.324800, WithinRel( multiplicity.values()[3] ) );
  CHECK_THAT( 4.466900, WithinRel( multiplicity.values()[4] ) );
  CHECK_THAT( 5.520700, WithinRel( multiplicity.values()[5] ) );
}

void verifyPolynomialChunk( const Multiplicity& chunk ) {

  CHECK( true == std::holds_alternative< PolynomialMultiplicity >( chunk ) );

  auto multiplicity = std::get< PolynomialMultiplicity >( chunk );
  CHECK( 2 == multiplicity.coefficients().size() );
  CHECK( 1 == multiplicity.order() );

  CHECK_THAT( 1e-5, WithinRel( multiplicity.lowerEnergyLimit() ) );
  CHECK_THAT( 2e+7, WithinRel( multiplicity.upperEnergyLimit() ) );

  CHECK_THAT(   2.824, WithinRel( multiplicity.coefficients()[0] ) );
  CHECK_THAT( 1.42e-7, WithinRel( multiplicity.coefficients()[1] ) );
}
