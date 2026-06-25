// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/InterpolationType.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapInterpolationType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "InterpolationType",
    "The interpolation type for tabulated data",
    python::arithmetic()
  );

  // wrap the component
  component
  .value(

    "Histogram",
    Component::Histogram,
    "Constant or histogram interpolation"
  )
  .value(

    "LinearLinear",
    Component::LinearLinear,
    "y is linear in x"
  )
  .value(

    "LinearLog",
    Component::LinearLog,
    "y is linear in ln(x)"
  )
  .value(

    "LogLinear",
    Component::LogLinear,
    "ln(y) is linear in x"
  )
  .value(

    "LogLog",
    Component::LogLog,
    "ln(y) is linear in ln(x)"
  );
}

} // dryad namespace
