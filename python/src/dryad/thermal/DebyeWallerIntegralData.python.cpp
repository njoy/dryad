// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/DebyeWallerIntegralData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapDebyeWallerIntegralData( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::DebyeWallerIntegralData;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "DebyeWallerIntegralData",
    "A Debye-Waller integral table\n\n"
    "Temperature values are assumed to be in K and the integral values are assumed to be in 1/eV.\n\n"
    "Parameters\n"
    "----------\n"
    "    temperatures : list of float\n"
    "        the temperature values\n"
    "    values : list of float\n"
    "        the intergal values"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >,
                  std::vector< double > >(),
    python::arg( "temperatures" ),
    python::arg( "values" ),
    "Initialise the Debye-Waller integral data"
  )
  .def_property_readonly(

    "temperatures",
    python::overload_cast<>( &Component::temperatures, python::const_ ),
    "The temperature values"
  )
  .def_property_readonly(

    "values",
    python::overload_cast<>( &Component::values, python::const_ ),
    "The integral values"
  )
  .def(

    "has_value",
    &Component::hasValue,
    python::arg( "temperature" ),
    "Return whether or not there is a Debye-Waller integral value for a given temperature\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "        the temperature"
  )
  .def(

    "value",
    &Component::value,
    python::arg( "temperature" ),
    "Return the Debye-Waller integral value for a given temperature\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "        the temperature"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
