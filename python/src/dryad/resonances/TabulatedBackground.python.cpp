// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/TabulatedBackground.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapTabulatedBackground( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::TabulatedBackground;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedBackground",
    "The energy values are given in eV and the background values are\n"
    "dimensionless complex values.\n\n"
    "Parameters\n"
    "----------\n"
    "    energies : list of float\n"
    "         the momentum values\n"
    "    values : list of complex\n"
    "         the background values\n"
    "    boundaries : list of int\n"
    "         the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "         the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear\n"
    "         the interpolation type (default lin-lin)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >,
                  std::vector< std::complex< double > >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the background function with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< std::complex< double > >,
                  InterpolationType >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the background function with a single interpolation zone"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The background values"
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
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy value"
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
