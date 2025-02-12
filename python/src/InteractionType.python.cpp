// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/InteractionType.hpp"

// namespace aliases
namespace python = pybind11;

void wrapInteractionType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::InteractionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "InteractionType",
    "The projectile-target interaction type",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Atomic",  Component::Atomic )
  .value( "Nuclear", Component::Nuclear );
}
