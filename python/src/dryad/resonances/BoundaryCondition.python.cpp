// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/resonances/BoundaryCondition.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapBoundaryCondition( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::BoundaryCondition;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "BoundaryCondition",
    "The boundary condition options",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "ShiftFactor", Component::ShiftFactor )
  .value( "Constant", Component::Constant );
}

} // resonances namespace
} // dryad namespace
