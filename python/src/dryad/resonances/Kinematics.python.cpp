// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/resonances/Kinematics.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapKinematics( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::Kinematics;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "Kinematics",
    "The kinematics option",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "NonRelativistic", Component::NonRelativistic )
  .value( "Relativistic", Component::Relativistic );
}

} // resonances namespace
