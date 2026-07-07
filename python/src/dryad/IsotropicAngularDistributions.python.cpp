// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/IsotropicAngularDistributions.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapIsotropicAngularDistributions( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::IsotropicAngularDistributions;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IsotropicAngularDistributions",
    "All angular distributions are isotropic"
  );

  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the isotropic angular distributions"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
