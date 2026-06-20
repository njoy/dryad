// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/InteractionType.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapInteractionType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::InteractionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "InteractionType",
    "The projectile-target interaction type\n\n"
    "This enum is used to differentiate between how the projectile interacts with\n"
    "the target. We currently distinguish nuclear and atomic interactions.",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Nuclear", Component::Nuclear,
          "The projectile-target interaction is nuclear" )
  .value( "Atomic",  Component::Atomic,
          "The projectile-target interaction is atomic" );
}

} // dryad namespace
