// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/SammyBackground.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapSammyBackground( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::SammyBackground;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "SammyBackground",
    "A channel background using the SAMMY parametrisation\n\n"
    "The SAMMY parametrisation of a channel background is a function\n"
    "of energy consisting of a quadratic polynomial and a logarithmic\n"
    "term. It is characterised by 7 parameters:\n"
    "  - 3 coefficients of the polymonial term (R0, R1 and R2)\n"
    "  - 2 constants for the logarithmic term (S0 and S1)\n"
    "  - 2 logarithmic singularity values (Ed and Eu, given in eV)\n"
   );

  // wrap the component
  component
  .def(

    python::init< std::array< double, 3 >,
                  std::array< double, 2 >,
                  double, double >(),
    python::arg( "polynomial_coefficients" ),
    python::arg( "logarithmic_coefficients" ),
    python::arg( "lower_singularity" ),
    python::arg( "upper_singularity" ),
    "Initialise the background function\n\n"
    "Parameters\n"
    "----------\n"
    "    polynomial_coefficients : list of float\n"
    "       the coefficients of the polymonial term (order 2)\n"
    "    logarithmic_coefficients : list of float\n"
    "       the coefficients of the logarithmic term (order 1)\n"
    "    lower_singularity : float\n"
    "       the lower logarithmic singularity values\n"
    "    upper_singularity : float\n"
    "       the upper logarithmic singularity values\n"
  )
  .def_property_readonly(

    "polynomial_coefficients",
    &Component::polynomialCoefficients,
    "The coefficients of the polynomial term"
  )
  .def_property_readonly(

    "logarithmic_coefficients",
    &Component::logarithmicCoefficients,
    "The coefficients of the logarithmic term"
  )
  .def_property_readonly(

    "lower_singularity",
    &Component::lowerSingularity,
    "The logarithmic singularity below the energy range"
  )
  .def_property_readonly(

    "upper_singularity",
    &Component::upperSingularity,
    "The logarithmic singularity above the energy range"
  )
  .def(

    "__call__",
    [] ( const Component& self, double energy ) -> decltype(auto)
       { return self( energy ); },
    python::arg( "energy" ),
    "Evaluate the background function for a given energy value\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
