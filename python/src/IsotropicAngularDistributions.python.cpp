// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/IsotropicAngularDistributions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapIsotropicAngularDistributions( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::IsotropicAngularDistributions;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IsotropicAngularDistributions"
  );
}
