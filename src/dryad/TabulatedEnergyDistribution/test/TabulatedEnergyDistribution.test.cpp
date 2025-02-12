// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "dryad/TabulatedEnergyDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::dryad;

SCENARIO( "TabulatedEnergyDistribution" ) {

  GIVEN( "Legendre coefficients for a normalised expansion" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > energies = { 1., 2., 3., 4. };
      const std::vector< double > values = { 4., 3., 2., 1. };

      TabulatedEnergyDistribution chunk( std::move( energies ), std::move( values ) );

      THEN( "a TabulatedEnergyDistribution can be constructed and members can "
            "be tested" ) {

        auto pdf = chunk.pdf();
        CHECK_THAT(  1., WithinRel( pdf.lowerEnergyLimit() ) );
        CHECK_THAT(  4., WithinRel( pdf.upperEnergyLimit() ) );
        CHECK_THAT(  1., WithinRel( pdf.energies()[0] ) );
        CHECK_THAT(  2., WithinRel( pdf.energies()[1] ) );
        CHECK_THAT(  3., WithinRel( pdf.energies()[2] ) );
        CHECK_THAT(  4., WithinRel( pdf.energies()[3] ) );
        CHECK_THAT(  4., WithinRel( pdf.values()[0] ) );
        CHECK_THAT(  3., WithinRel( pdf.values()[1] ) );
        CHECK_THAT(  2., WithinRel( pdf.values()[2] ) );
        CHECK_THAT(  1., WithinRel( pdf.values()[3] ) );

        CHECK_THROWS( chunk.cdf() );
      } // THEN

      THEN( "a TabulatedEnergyDistribution can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.5, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.5, WithinRel( chunk( 3.5 ) ) );
      } // THEN

//! @todo implement linearisation
//      THEN( "a TabulatedEnergyDistribution can be linearised" ) {
//
//      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the energy and values vector are not of the same length" ) {

      THEN( "an exception is thrown" ) {

        const std::vector< double > energies = { 1., 4. };
        const std::vector< double > values = { 4., 3., 2., 1. };

        CHECK_THROWS( TabulatedEnergyDistribution( energies, values ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
