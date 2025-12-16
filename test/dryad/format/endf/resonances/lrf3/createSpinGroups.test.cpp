// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/dryad/format/endf/resonances/lrf3/createSpinGroups.hpp"

// other includes
#include "ENDFtk/tree/fromFile.hpp"

// convenience typedefs
using namespace njoy;
using namespace njoy::dryad;
using namespace njoy::dryad::resonances;

SCENARIO( "createChannelData" ) {

  GIVEN( "ENDF MF2 MT151 sections" ) {

    using Tape = njoy::ENDFtk::tree::Tape;
    auto tape = njoy::ENDFtk::tree::fromFile< Tape >( "n-013_Al_027.endf" );
    auto section = tape.materials().front().section( 2, 151 ).parse< 2, 151 >();
    auto parameters = std::get< njoy::ENDFtk::section::Type<2,151>::ReichMoore >(
                        section.isotopes().front().resonanceRanges().front().parameters() );

    WHEN( "a single parsed Reich-Moore l-value from MF2 MT151 is given" ) {

      THEN( "it can be converted" ) {

        id::ParticleID projectile = id::ParticleID::neutron();
        id::ParticleID target = id::ParticleID( "Al27" );
        int naps = 1;
        std::optional< dryad::resonances::TabulatedRadius > nro = std::nullopt;
        auto chunk = format::endf::resonances::lrf3::createSpinGroups( projectile, target,
                                                                       naps, nro, parameters );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

