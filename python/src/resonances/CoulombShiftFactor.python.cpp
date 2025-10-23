// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/resonances/CoulombShiftFactor.hpp"

#include "scion/math/horner.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapCoulombShiftFactor( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::CoulombShiftFactor;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CoulombShiftFactor",
    "Coulomb shift factor functions"
   );

  // wrap the component
  component
  .def(

    python::init< unsigned int >(),
    python::arg( "orbital_momentum" ),
    "Initialise the Coulomb shift factor function\n\n"
    "Arguments:\n"
    "    self                       the function\n"
    "    orbital_angular_momentum   the value of the orbital momentum"
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
    [] ( const Component& self, double ratio, double eta ) -> decltype(auto)
       { return self( ratio, eta ); },
    python::arg( "ratio" ), python::arg( "eta" ),
    "Evaluate the shift factor for a given ratio and eta value\n\n"
    "Arguments:\n"
    "    self    the shift factor function\n"
    "    ratio   the ratio value\n"
    "    eta     the eta value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
