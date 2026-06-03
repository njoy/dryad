// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "njoy/psychic/TestStatus.hpp"

// other includes
#include <iostream>
#include <iomanip>

// convenience typedefs
using namespace njoy::psychic;

SCENARIO( "TestStatus" ) {

  CHECK( TestStatus::Skipped == ( TestStatus::Skipped && TestStatus::Skipped ) );
  CHECK( TestStatus::Success == ( TestStatus::Skipped && TestStatus::Success ) );
  CHECK( TestStatus::Warning == ( TestStatus::Skipped && TestStatus::Warning ) );
  CHECK( TestStatus::Fail    == ( TestStatus::Skipped && TestStatus::Fail ) );

  CHECK( TestStatus::Success == ( TestStatus::Success && TestStatus::Skipped ) );
  CHECK( TestStatus::Success == ( TestStatus::Success && TestStatus::Success ) );
  CHECK( TestStatus::Warning == ( TestStatus::Success && TestStatus::Warning ) );
  CHECK( TestStatus::Fail    == ( TestStatus::Success && TestStatus::Fail ) );

  CHECK( TestStatus::Warning == ( TestStatus::Warning && TestStatus::Skipped ) );
  CHECK( TestStatus::Warning == ( TestStatus::Warning && TestStatus::Success ) );
  CHECK( TestStatus::Warning == ( TestStatus::Warning && TestStatus::Warning ) );
  CHECK( TestStatus::Fail    == ( TestStatus::Warning && TestStatus::Fail ) );

  CHECK( TestStatus::Fail    == ( TestStatus::Fail && TestStatus::Skipped ) );
  CHECK( TestStatus::Fail    == ( TestStatus::Fail && TestStatus::Success ) );
  CHECK( TestStatus::Fail    == ( TestStatus::Fail && TestStatus::Warning ) );
  CHECK( TestStatus::Fail    == ( TestStatus::Fail && TestStatus::Fail ) );
} // SCENARIO
