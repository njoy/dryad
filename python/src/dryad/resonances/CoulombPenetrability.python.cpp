// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/CoulombPenetrability.hpp"

#include "scion/math/horner.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapCoulombPenetrability( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::CoulombPenetrability;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CoulombPenetrability",
    "Coulomb penetrability functions\n\n"
    "Parameters\n"
    "----------\n"
    "    orbital_angular_momentum : int\n"
    "         the orbital angular momentum quantum number (l value)"
   );

  // wrap the component
  component
  .def(

    python::init< unsigned int >(),
    python::arg( "orbital_angular_momentum" ),
    "Initialise the Coulomb penetrability function"
  )
  .def_property_readonly(

    "orbital_angular_momentum",
    &Component::orbitalAngularMomentum,
    "The orbital angular momentum quantum number (l value)"
  )
  .def(

    "__call__",
    [] ( const Component& self, double ratio, double eta ) -> decltype(auto)
       { return self( ratio, eta ); },
    python::arg( "ratio" ), python::arg( "eta" ),
    "Evaluate the penetrability for given ratio and eta values\n\n"
    "Parameters\n"
    "----------\n"
    "    ratio : float\n"
    "         the ratio rho = k*a (wave number times channel radius)\n"
    "    eta : float\n"
    "         the Coulomb parameter"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
