// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/ReferenceFrame.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReferenceFrame( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::ReferenceFrame;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "ReferenceFrame",
    "The reference frame used to describe data",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Laboratory",   Component::Laboratory )
  .value( "CentreOfMass", Component::CentreOfMass );
}
