// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/PolynomialMultiplicity.hpp"

// namespace aliases
namespace python = pybind11;

void wrapPolynomialMultiplicity( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::PolynomialMultiplicity;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "PolynomialMultiplicity",
    "A multiplicity given as a polynomial series"
  );

  // wrap the component
  component
  .def(

    python::init< double, double, std::vector< double > >(),
    python::arg( "lower" ), python::arg( "upper" ),
    python::arg( "coefficients" ),
    "Initialise the multiplicity table\n\n"
    "Arguments:\n"
    "    self           the multiplicity\n"
    "    lower          the lower limit of the domain\n"
    "    upper          the upper limit of the domain\n"
    "    coefficients   the coefficients of the polynomial series (from\n"
    "                   lowest to highest order coefficient)"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "lower_energy_limit",
    &Component::lowerEnergyLimit,
    "The lower energy limit"
  )
  .def_property_readonly(

    "upper_energy_limit",
    &Component::upperEnergyLimit,
    "The upper energy limit"
  )
  .def(

    "__call__",
    [] ( const Component& self, double energy ) -> decltype(auto)
       { return self( energy ); },
    python::arg( "energy" ),
    "Evaluate the multiplicity for a given energy value\n\n"
    "Arguments:\n"
    "    self      the multiplicity\n"
    "    energy    the energy value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard series data definitions
  addStandardSeriesDefinitions< Component >( component );
}
