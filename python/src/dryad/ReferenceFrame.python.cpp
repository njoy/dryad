// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/ReferenceFrame.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapReferenceFrame( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ReferenceFrame;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "ReferenceFrame",
    "The reference frame type\n\n"
    "This enum is used to differentiate reference frames for distribution data\n"
    "in the ProjectileTarget. We currently distinguish two different frames:\n"
    "centre of mass or laboratory.",
    python::arithmetic()
  );

  // wrap the component
  component
  .value(

    "Laboratory",
    Component::Laboratory,
    "The data is given in the laboratory frame of reference"
  )
  .value(

    "CentreOfMass",
    Component::CentreOfMass,
    "The data is given in the centre of mass frame of reference"
  );
}

} // dryad namespace
