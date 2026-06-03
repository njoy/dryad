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
    "The test status",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Success", Component::Success )
  .value( "Warning", Component::Warning )
  .value( "Fail",    Component::Fail )
  .value( "Skipped", Component::Skipped );
}

} // psychic namespace
