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
    "The angular distribution data is fully isotropic"
  );

  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self   the component"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // dryad namespace
