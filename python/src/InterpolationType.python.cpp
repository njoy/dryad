// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/type-aliases.hpp"

// namespace aliases
namespace python = pybind11;

void wrapInterpolationType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "InterpolationType",
    "The interpolation types",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Histogram", Component::Histogram )
  .value( "LinearLinear", Component::LinearLinear )
  .value( "LinearLog", Component::LinearLog )
  .value( "LogLinear", Component::LogLinear )
  .value( "LogLog", Component::LogLog );
}
