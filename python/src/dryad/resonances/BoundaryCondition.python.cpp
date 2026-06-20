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
    "The boundary condition options for resonance reconstruction\n\n"
    "This enum differentiates between boundary condition options in resonance\n"
    "reconstruction calculations.\n\n"
    "Values\n"
    "------\n"
    "    ShiftFactor : 1\n"
    "         eliminate the energy dependent shift factor (L = iP)\n"
    "    Constant : 2\n"
    "         use a constant boundary condition",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "ShiftFactor", Component::ShiftFactor,
          "Eliminate energy dependent shift factor so L = iP" )
  .value( "Constant", Component::Constant,
          "Use constant boundary condition" );
}

} // resonances namespace
} // dryad namespace
