// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/medic/pruneCrossSection.hpp"

// other includes

// convenience typedefs
using namespace njoy::medic;
using namespace njoy::dryad;

TabulatedCrossSection createTabulatedCrossSection();

SCENARIO( "pruneCrossSection" ) {

  GIVEN( "a tabulated cross section data object" ) {

    THEN( "it can be pruned to a lower energy limit present in the energies (no jump)" ) {

      auto table = createTabulatedCrossSection();
      pruneCrossSection( 2., 6., table );

      CHECK( 6 == table.numberPoints() );
      CHECK( 2 == table.numberRegions() );
      CHECK( 6 == table.energies().size() );
      CHECK( 6 == table.values().size() );
      CHECK( 2 == table.boundaries().size() );
      CHECK( 2 == table.interpolants().size() );

      CHECK_THAT( 2., WithinRel( table.energies()[0] ) );
      CHECK_THAT( 3., WithinRel( table.energies()[1] ) );
      CHECK_THAT( 3., WithinRel( table.energies()[2] ) );
      CHECK_THAT( 4., WithinRel( table.energies()[3] ) );
      CHECK_THAT( 5., WithinRel( table.energies()[4] ) );
      CHECK_THAT( 6., WithinRel( table.energies()[5] ) );
      CHECK_THAT( 12., WithinRel( table.values()[0] ) );
      CHECK_THAT( 13., WithinRel( table.values()[1] ) );
      CHECK_THAT( 23., WithinRel( table.values()[2] ) );
      CHECK_THAT( 24., WithinRel( table.values()[3] ) );
      CHECK_THAT( 25., WithinRel( table.values()[4] ) );
      CHECK_THAT( 26., WithinRel( table.values()[5] ) );

      CHECK( 1 == table.boundaries()[0] );
      CHECK( 5 == table.boundaries()[1] );
      CHECK( InterpolationType::LinearLinear == table.interpolants()[0] );
      CHECK( InterpolationType::LogLog == table.interpolants()[1] );
    } // THEN

    THEN( "it can be pruned to a lower energy limit present in the energies (a jump)" ) {

      auto table = createTabulatedCrossSection();
      pruneCrossSection( 3., 6., table );

      CHECK( 4 == table.numberPoints() );
      CHECK( 1 == table.numberRegions() );
      CHECK( 4 == table.energies().size() );
      CHECK( 4 == table.values().size() );
      CHECK( 1 == table.boundaries().size() );
      CHECK( 1 == table.interpolants().size() );

      CHECK_THAT( 3., WithinRel( table.energies()[0] ) );
      CHECK_THAT( 4., WithinRel( table.energies()[1] ) );
      CHECK_THAT( 5., WithinRel( table.energies()[2] ) );
      CHECK_THAT( 6., WithinRel( table.energies()[3] ) );
      CHECK_THAT( 23., WithinRel( table.values()[0] ) );
      CHECK_THAT( 24., WithinRel( table.values()[1] ) );
      CHECK_THAT( 25., WithinRel( table.values()[2] ) );
      CHECK_THAT( 26., WithinRel( table.values()[3] ) );

      CHECK( 3 == table.boundaries()[0] );
      CHECK( InterpolationType::LogLog == table.interpolants()[0] );
    } // THEN

    THEN( "it can be pruned to a lower energy limit not present in the energies" ) {

      auto table = createTabulatedCrossSection();
      pruneCrossSection( 2.5, 6., table );

      CHECK( 6 == table.numberPoints() );
      CHECK( 2 == table.numberRegions() );
      CHECK( 6 == table.energies().size() );
      CHECK( 6 == table.values().size() );
      CHECK( 2 == table.boundaries().size() );
      CHECK( 2 == table.interpolants().size() );

      CHECK_THAT( 2.5, WithinRel( table.energies()[0] ) );
      CHECK_THAT( 3. , WithinRel( table.energies()[1] ) );
      CHECK_THAT( 3. , WithinRel( table.energies()[2] ) );
      CHECK_THAT( 4. , WithinRel( table.energies()[3] ) );
      CHECK_THAT( 5. , WithinRel( table.energies()[4] ) );
      CHECK_THAT( 6. , WithinRel( table.energies()[5] ) );
      CHECK_THAT( 12.5, WithinRel( table.values()[0] ) );
      CHECK_THAT( 13. , WithinRel( table.values()[1] ) );
      CHECK_THAT( 23. , WithinRel( table.values()[2] ) );
      CHECK_THAT( 24. , WithinRel( table.values()[3] ) );
      CHECK_THAT( 25. , WithinRel( table.values()[4] ) );
      CHECK_THAT( 26. , WithinRel( table.values()[5] ) );

      CHECK( 1 == table.boundaries()[0] );
      CHECK( 5 == table.boundaries()[1] );
      CHECK( InterpolationType::LinearLinear == table.interpolants()[0] );
      CHECK( InterpolationType::LogLog == table.interpolants()[1] );
    } // THEN

    THEN( "it can be pruned to an upper energy limit present in the energies" ) {

      auto table = createTabulatedCrossSection();
      pruneCrossSection( 1., 3., table );

      CHECK( 3 == table.numberPoints() );
      CHECK( 1 == table.numberRegions() );
      CHECK( 3 == table.energies().size() );
      CHECK( 3 == table.values().size() );
      CHECK( 1 == table.boundaries().size() );
      CHECK( 1 == table.interpolants().size() );

      CHECK_THAT( 1., WithinRel( table.energies()[0] ) );
      CHECK_THAT( 2., WithinRel( table.energies()[1] ) );
      CHECK_THAT( 3., WithinRel( table.energies()[2] ) );
      CHECK_THAT( 11., WithinRel( table.values()[0] ) );
      CHECK_THAT( 12., WithinRel( table.values()[1] ) );
      CHECK_THAT( 13., WithinRel( table.values()[2] ) );

      CHECK( 2 == table.boundaries()[0] );
      CHECK( InterpolationType::LinearLinear == table.interpolants()[0] );
    } // THEN

    THEN( "it can be pruned to an upper energy limit not present in the energies" ) {

      auto table = createTabulatedCrossSection();
      pruneCrossSection( 1., 2.5, table );

      CHECK( 3 == table.numberPoints() );
      CHECK( 1 == table.numberRegions() );
      CHECK( 3 == table.energies().size() );
      CHECK( 3 == table.values().size() );
      CHECK( 1 == table.boundaries().size() );
      CHECK( 1 == table.interpolants().size() );

      CHECK_THAT( 1. , WithinRel( table.energies()[0] ) );
      CHECK_THAT( 2. , WithinRel( table.energies()[1] ) );
      CHECK_THAT( 2.5, WithinRel( table.energies()[2] ) );
      CHECK_THAT( 11. , WithinRel( table.values()[0] ) );
      CHECK_THAT( 12. , WithinRel( table.values()[1] ) );
      CHECK_THAT( 12.5, WithinRel( table.values()[2] ) );

      CHECK( 2 == table.boundaries()[0] );
      CHECK( InterpolationType::LinearLinear == table.interpolants()[0] );
    } // THEN

    THEN( "it can be pruned" ) {

      auto table = createTabulatedCrossSection();
      pruneCrossSection( 1.5, 2.5, table );

      CHECK( 3 == table.numberPoints() );
      CHECK( 1 == table.numberRegions() );
      CHECK( 3 == table.energies().size() );
      CHECK( 3 == table.values().size() );
      CHECK( 1 == table.boundaries().size() );
      CHECK( 1 == table.interpolants().size() );

      CHECK_THAT( 1.5, WithinRel( table.energies()[0] ) );
      CHECK_THAT( 2. , WithinRel( table.energies()[1] ) );
      CHECK_THAT( 2.5, WithinRel( table.energies()[2] ) );
      CHECK_THAT( 11.5, WithinRel( table.values()[0] ) );
      CHECK_THAT( 12. , WithinRel( table.values()[1] ) );
      CHECK_THAT( 12.5, WithinRel( table.values()[2] ) );

      CHECK( 2 == table.boundaries()[0] );
      CHECK( InterpolationType::LinearLinear == table.interpolants()[0] );
    } // THEN
  } // GIVEN
} // SCENARIO

TabulatedCrossSection createTabulatedCrossSection() {

  return { { 1., 2., 3., 3., 4., 5., 6. }, { 11., 12., 13., 23., 24., 25., 26. },
           { 3, 6 }, { InterpolationType::LinearLinear, InterpolationType::LogLog } };
}