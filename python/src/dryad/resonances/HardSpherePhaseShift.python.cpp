// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/HardSpherePhaseShift.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapHardSpherePhaseShift( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::HardSpherePhaseShift;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "HardSpherePhaseShift",
    "Hard sphere phase shift functions\n\n"
    "Parameters\n"
    "----------\n"
    "    orbital_angular_momentum : int\n"
    "         the orbital angular momentum quantum number (l = 0 to 5)"
   );

  // wrap the component
  component
  .def(

    python::init< unsigned int >(),
    python::arg( "orbital_angular_momentum" ),
    "Initialise the hard sphere phase shift function"
  )
  .def_property_readonly(

    "orbital_angular_momentum",
    &Component::orbitalAngularMomentum,
    "The orbital angular momentum quantum number (l value)"
  )
  .def(

    "__call__",
    [] ( const Component& self, double ratio ) -> decltype(auto)
       { return self( ratio ); },
    python::arg( "ratio" ),
    "Evaluate the phase shift for a given ratio value\n\n"
    "Parameters\n"
    "----------\n"
    "    ratio : float\n"
    "         the ratio rho = k*a (wave number times channel radius)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
