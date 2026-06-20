// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/UniformDistributionType.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapUniformDistributionType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::UniformDistributionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "UniformDistributionType",
    "The uniform distribution type\n\n"
    "This enum is used to differentiate uniform distribution types, either discrete\n"
    "values or intervals.",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Discrete",  Component::Discrete,
          "The uniform distribution is given for discrete values" )
  .value( "Interval", Component::Interval,
          "The uniform distribution is given for intervals" );
}

} // dryad namespace
