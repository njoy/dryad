// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/atomic/TransitionType.hpp"

// namespace aliases
namespace python = pybind11;

namespace atomic {

void wrapTransitionType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::atomic::TransitionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "TransitionType",
    "The type of transition in an atomic relaxation",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Radiative",    Component::Radiative )
  .value( "NonRadiative", Component::NonRadiative );
}

} // namespace atomic
