// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/ReactionCategory.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapReactionCategory( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ReactionCategory;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "ReactionCategory",
    "The reaction category\n\n"
    "This enum is used to differentiate reaction categories in the ProjectileTarget.\n"
    "We currently have two categories: primary and summation.",
    python::arithmetic()
  );

  // wrap the component
  component
  .value(

    "Primary",
    Component::Primary,
    "A primary independent reaction that contributes to the total cross section"
  )
  .value(

    "Summation",
    Component::Summation,
    "A summation reaction with or without reaction products that does not count towards the total cross section"
  );
}

} // dryad namespace
