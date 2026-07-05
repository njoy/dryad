// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/ShortCollisionTimeScatteringKernel.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapShortCollisionTimeScatteringKernel( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::ShortCollisionTimeScatteringKernel;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ShortCollisionTimeScatteringKernel",
    "Bragg edge data for a single temperature\n\n"
    "An S(a,b) scattering kernel using the short collision time approximation\n\n"
    "Parameters\n"
    "----------\n"
    "    moderator_temperature : float\n"
    "        the moderator temperature\n"
    "    effective_temperature : float\n"
    "        the effective temperature"
  );

  // wrap the component
  component
  .def(

    python::init< double, double >(),
    python::arg( "moderator_temperature" ),
    python::arg( "effective_temperature" ),
    "Initialise the scattering kernel"
  )
  .def_property_readonly(

    "moderator_temperature",
    &Component::moderatorTemperature,
    "The moderator temperature"
  )
  .def_property_readonly(

    "effective_temperature",
    &Component::effectiveTemperature,
    "The effective temperature"
  )
  .def(

    "__call__",
    [] ( const Component& self, double a, double b ) -> decltype(auto)
       { return self( a, b ); },
    python::arg( "a" ),
    python::arg( "b" ),
    "Evaluate the table for a given energy value\n\n"
    "Parameters\n"
    "----------\n"
    "    a : float\n"
    "        the momentum transfer value\n"
    "    b : float\n"
    "        the energy transfer value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
