// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/ReactionType.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReactionType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ReactionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "ReactionType",
    "The reaction type",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Primary",   Component::Primary )
  .value( "Summation", Component::Summation );
}
