// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/covariance/ScalingType.hpp"

// namespace aliases
namespace python = pybind11;

namespace covariance {

void wrapScalingType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::ScalingType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "ScalingType",
    "The variance scaling type",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Inverse",  Component::Inverse )
  .value( "Direct",   Component::Direct );
}

} // covariance namespace