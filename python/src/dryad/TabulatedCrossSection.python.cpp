// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedCrossSection( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedCrossSection;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedCrossSection",
    "A cross section table\n\n"
    "Parameters\n"
    "----------\n"
    "    energies : list of float\n"
    "        the energy values\n"
    "    values : list of float\n"
    "        the cross section values\n"
    "    boundaries : list of int\n"
    "        the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "        the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear\n"
    "        the interpolation type (default lin-lin)\n"
    "    curate : bool, default False\n"
    "        flag to indicate whether or not to curate the data\n"
    "    threshold : float, optional\n"
    "        the optional threshold value (only used for Coulomb penetrability\n"
    "        interpolation, default: none)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >,
                  std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType >,
                  bool, std::optional< double > >(),
    python::arg( "energies" ),
    python::arg( "values" ),
    python::arg( "boundaries" ),
    python::arg( "interpolants" ),
    python::arg( "curate" ) = false,
    python::arg( "threshold" ) = std::nullopt,
    "Initialise the cross section table with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< double >,
                  InterpolationType,
                  bool,
                  std::optional< double > >(),
    python::arg( "energies" ),
    python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    python::arg( "curate" ) = false,
    python::arg( "threshold" ) = std::nullopt,
    "Initialise the cross section table with a single interpolation zone"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The cross section values"
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
  .def_property_readonly(

    "threshold",
    [] ( const Component& self ) -> decltype(auto)
       { return self.threshold(); },
    "The optional threshold value (required for Coulomb penetrability interpolation)"
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
