// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "dryad/format/gnds/covariance/createVarianceScaling.hpp"

// other includes
#include "pugixml.hpp"

// convenience typedefs
using namespace njoy::dryad;

void verifyFissionChunk( const covariance::VarianceScaling& );

SCENARIO( "createTabulatedMultiplicity" ) {

  GIVEN( "GNDS variance scaling node" ) {

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file( "n-009_F_019.endf.gnds-covar.xml" );
    pugi::xml_node scaling = document.child( "covarianceSuite" ).child( "covarianceSections" ).
                                      find_child_by_attribute( "covarianceSection", "label", "(z,n)" ).
                                      child( "mixed" ).child( "shortRangeSelfScalingVariance" );

    WHEN( "a single variance scaling node is given" ) {

      THEN( "it can be converted" ) {

        auto chunk = format::gnds::covariance::createVarianceScaling( scaling );

        CHECK( 12 == chunk.numberGroups() );

        CHECK( 13 == chunk.energies().size() );
        CHECK_THAT( 1.000000e-5, WithinRel( chunk.energies()[0] ) );
        CHECK_THAT( 1.158400e+5, WithinRel( chunk.energies()[1] ) );
        CHECK_THAT( 2.074600e+5, WithinRel( chunk.energies()[2] ) );
        CHECK_THAT( 3.000000e+5, WithinRel( chunk.energies()[3] ) );
        CHECK_THAT( 4.500000e+5, WithinRel( chunk.energies()[4] ) );
        CHECK_THAT( 6.000000e+5, WithinRel( chunk.energies()[5] ) );
        CHECK_THAT( 1.100000e+6, WithinRel( chunk.energies()[6] ) );
        CHECK_THAT( 1.500000e+6, WithinRel( chunk.energies()[7] ) );
        CHECK_THAT( 3.000000e+6, WithinRel( chunk.energies()[8] ) );
        CHECK_THAT( 6.000000e+6, WithinRel( chunk.energies()[9] ) );
        CHECK_THAT( 1.000000e+7, WithinRel( chunk.energies()[10] ) );
        CHECK_THAT( 1.400000e+7, WithinRel( chunk.energies()[11] ) );
        CHECK_THAT( 2.000000e+7, WithinRel( chunk.energies()[12] ) );

        CHECK( 12 == chunk.factors().size() );
        CHECK_THAT( 0.000000e+0, WithinRel( chunk.factors()[0] ) );
        CHECK_THAT( 2.223500e-6, WithinRel( chunk.factors()[1] ) );
        CHECK_THAT( 5.134300e-5, WithinRel( chunk.factors()[2] ) );
        CHECK_THAT( 1.469900e-5, WithinRel( chunk.factors()[3] ) );
        CHECK_THAT( 2.514800e-6, WithinRel( chunk.factors()[4] ) );
        CHECK_THAT( 4.884600e-6, WithinRel( chunk.factors()[5] ) );
        CHECK_THAT( 2.141300e-6, WithinRel( chunk.factors()[6] ) );
        CHECK_THAT( 1.365400e-6, WithinRel( chunk.factors()[7] ) );
        CHECK_THAT( 8.511600e-7, WithinRel( chunk.factors()[8] ) );
        CHECK_THAT( 3.476300e-7, WithinRel( chunk.factors()[9] ) );
        CHECK_THAT( 2.993200e-8, WithinRel( chunk.factors()[10] ) );
        CHECK_THAT( 4.138200e-9, WithinRel( chunk.factors()[11] ) );

        CHECK( covariance::ScalingType::Inverse == chunk.type() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
