// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/covariance/ScalingType.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace covariance {

void wrapScalingType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::ScalingType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "ScalingType",
    "The variance scaling type\n\n"
    "This enum is used to differentiate variance scaling types. We currently\n"
    "distinguish two types of scaling: inverse and direct proportional.",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Inverse",  Component::Inverse,
          "The variance of group j is inversely proportional to the width of group j" )
  .value( "Direct",   Component::Direct,
          "The variance of group j is directly proportional to the width of group j" );
}

} // covariance namespace
} // dryad namespace
