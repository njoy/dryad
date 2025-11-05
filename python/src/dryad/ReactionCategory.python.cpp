// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/ReactionCategory.hpp"

// namespace aliases
namespace python = pybind11;

void wrapReactionCategory( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ReactionCategory;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "ReactionCategory",
    "The reaction category",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Primary",   Component::Primary )
  .value( "Summation", Component::Summation );
}
