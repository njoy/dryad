// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/CoulombShiftFactor.hpp"

#include "scion/math/horner.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapCoulombShiftFactor( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::CoulombShiftFactor;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CoulombShiftFactor",
    "Coulomb shift factor functions\n\n"
    "The CoulombShiftFactor evaluates the Coulomb shift factor S_l(rho, eta)\n"
    "as a function of the ratio rho = k*a and the Coulomb parameter eta, where\n"
    "k is the wave number and a is the channel radius. The shift factor is used\n"
    "in R-matrix resonance theory for charged particle reactions.\n\n"
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
    "Initialise the Coulomb shift factor function with a single value"
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
    "Evaluate the shift factor for given ratio and eta values\n\n"
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
