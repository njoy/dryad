// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/TabulatedLegendreMoment.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedLegendreMoment( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedLegendreMoment;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedLegendreMoment",
    "A Legendre moment table\n\n"
    "Parameters\n"
    "----------\n"
    "    order : int\n"
    "        the order of the Legendre moment\n"
    "    energies : list of float\n"
    "        the energy values\n"
    "    values : list of float\n"
    "        the Legendre moment values\n"
    "    boundaries : list of int, optional\n"
    "        the boundaries of the interpolation regions\n"
    "    interpolants : list of InterpolationType, optional\n"
    "        the interpolation types of the interpolation regions\n"
    "    interpolant : InterpolationType, default=LinearLinear\n"
    "        the interpolation type for single-region tables\n"
    "    curate : bool, default=False\n"
    "        flag to indicate whether or not to curate the data"
  );

  // wrap the component
  component
  .def(

    python::init< std::size_t,
                  std::vector< double >,
                  std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType >,
                  bool >(),
    python::arg( "order" ), python::arg( "energies" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "curate" ) = false,
    "Initialise the Legendre moment table with multiple interpolation regions"
  )
  .def(

    python::init< std::size_t,
                  std::vector< double >,
                  std::vector< double >,
                  InterpolationType,
                  bool >(),
    python::arg( "order" ), python::arg( "energies" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    python::arg( "curate" ) = false,
    "Initialise the Legendre moment table with single interpolation type"
  )
  .def_property_readonly(

    "order",
    &Component::order,
    "The order of the Legendre moment"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The Legendre moment values"
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

} // dryad namespace
