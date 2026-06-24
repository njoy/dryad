// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <optional>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/TabulatedAverageWidths.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapTabulatedAverageWidths( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::TabulatedAverageWidths;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedAverageWidths",
    "A table of average widths"
  );

  // wrap the component
  component
  .def(

    python::init< int,
                  std::vector< double >,
                  std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg("dof"), python::arg( "energies" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the average width table\n\n"
    "Arguments:\n"
    "    self           the average width table\n"
    "    dof            the degrees of freedom\n"
    "    energies       the energy values\n"
    "    values         the average width values\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions,\n"
    "                   see InterpolationType for all interpolation types"
  )
  .def(

    python::init< int,
                  std::vector< double >,
                  std::vector< double >,
                  InterpolationType >(),
    python::arg("dof"), python::arg( "energies" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the average width table\n\n"
    "Arguments:\n"
    "    self           the average width table\n"
    "    dof            the degrees of freedom\n"
    "    energies       the energy values\n"
    "    values         the average width values\n"
    "    interpolant    the interpolation type (default lin-lin),\n"
    "                   see InterpolationType for all interpolation types"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< double >,
                  InterpolationType >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the average width table\n\n"
    "Arguments:\n"
    "    self           the average width table\n"
    "    energies       the energy values\n"
    "    values         the average width  values\n"
    "    interpolant    the interpolation type (default lin-lin),\n"
    "                   see InterpolationType for all interpolation types"
  )
  .def_property(
    "degrees_of_freedom",
    python::overload_cast<>( &Component::degreesOfFreedom, python::const_ ),
    python::overload_cast< std::optional< int > >( &Component::degreesOfFreedom ),
    "The degrees of freedom"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The average width values"
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
    "Evaluate the table for a given energy value\n\n"
    "Arguments:\n"
    "    self      the average width table\n"
    "    energy    the energy value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
