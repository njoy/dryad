// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/UniformDistributionType.hpp"

// namespace aliases
namespace python = pybind11;

void wrapUniformDistributionType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::UniformDistributionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "UniformDistributionType",
    "The uniform distribution type",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Discrete",  Component::Discrete )
  .value( "Interval", Component::Interval );
}
