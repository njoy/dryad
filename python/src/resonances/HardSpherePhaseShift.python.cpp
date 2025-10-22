// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/resonances/HardSpherePhaseShift.hpp"

#include "scion/math/horner.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapHardSpherePhaseShift( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::HardSpherePhaseShift;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "HardSpherePhaseShift",
    "Hard sphere phase shift functions"
   );

  // wrap the component
  component
  .def(

    python::init< unsigned int >(),
    python::arg( "orbital_momentum" ),
    "Initialise the hard sphere phase shift function\n\n"
    "Arguments:\n"
    "    self               the function\n"
    "    orbital_momentum   the value of the orbital momentum"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "orbital_angular_momentum",
    &Component::orbitalAngularMomentum,
    "The value of the orbital angular momentum"
  )
  .def(

    "__call__",
    [] ( const Component& self, double ratio ) -> decltype(auto)
       { return self( ratio ); },
    python::arg( "ratio" ),
    "Evaluate the phase shift for a given ratio value\n\n"
    "Arguments:\n"
    "    self    the phase shift function\n"
    "    ratio   the ratio value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
