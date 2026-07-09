// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/HardSpherePenetrabilityRatio.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapHardSpherePenetrabilityRatio( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::HardSpherePenetrabilityRatio;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "HardSpherePenetrabilityRatio",
    "Hard sphere penetrability ratio functions\n\n"
    "Parameters\n"
    "----------\n"
    "    numerator_orbital_angular_momentum : int\n"
    "        the orbital angular momentum quantum number for the penetrability\n"
    "        in the numerator of the ratio (l = 0 to 5)\n"
    "    denominator_orbital_angular_momentum : int\n"
    "        the orbital angular momentum quantum number for the penetrability\n"
    "        in the denominator of the ratio (l = 0 to 5)"
   );

  // wrap the component
  component
  .def(

    python::init< unsigned int, unsigned int >(),
    python::arg( "numerator_orbital_angular_momentum" ),
    python::arg( "denominator_orbital_angular_momentum" ),
    "Initialise the hard sphere penetrability ratio function"
  )
  .def_property_readonly(

    "numerator_orbital_angular_momentum",
    &Component::numeratorOrbitalAngularMomentum,
    "The orbital angular momentum quantum number of the numerator penetrability (l value)"
  )
  .def_property_readonly(

    "denominator_orbital_angular_momentum",
    &Component::denominatorOrbitalAngularMomentum,
    "The orbital angular momentum quantum number of the denominator penetrability (l value)"
  )
  .def(

    "__call__",
    [] ( const Component& self, double ratio ) -> decltype(auto)
       { return self( ratio ); },
    python::arg( "ratio" ),
    "Evaluate the penetrability for a given ratio value\n\n"
    "Parameters\n"
    "----------\n"
    "    ratio : float\n"
    "        the ratio rho = k*a (wave number times channel radius)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
