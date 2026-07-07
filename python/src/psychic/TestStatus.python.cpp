// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/psychic/TestStatus.hpp"

// namespace aliases
namespace python = pybind11;

namespace psychic {

void wrapTestStatus( python::module& module ) {

  // type aliases
  using Component = njoy::psychic::TestStatus;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "TestStatus",
    "Test status enumeration\n\n"
    "This enum is used to differentiate between various test states. Four different\n"
    "states are distinguished: skipped, success, pass with warnings, and failed.",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Success", Component::Success, "The test passes successfully without issues" )
  .value( "Warning", Component::Warning, "The test passed but there are issues" )
  .value( "Fail",    Component::Fail,    "The test fails" )
  .value( "Skipped", Component::Skipped, "The test has been skipped" );
}

} // psychic namespace
