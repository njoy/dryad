// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/TabulatedEnergyDistributionFunction.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedEnergyDistributionFunction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedEnergyDistributionFunction;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedEnergyDistributionFunction",
    "An energy distribution function using tabulated data\n\n"
    "Parameters\n"
    "----------\n"
    "    energies : list of float\n"
    "         the energy values\n"
    "    values : list of float\n"
    "         the probability values\n"
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

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the energy distribution function with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the energy distribution function with a single interpolation zone"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The probability values"
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
    "Evaluate the distribution for a given energy value\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "         the energy value"
  )
  .def_property_readonly(

    "integral",
    [] ( const Component& self ) { return self.integral(); },
    "The integral of the distribution function over its domain"
  )
  .def_property_readonly(

    "mean",
    [] ( const Component& self ) { return self.mean(); },
    "The mean value of the distribution function over its domain"
  )
  .def_property_readonly(

    "cumulative_integral",
    [] ( const Component& self ) { return self.cumulativeIntegral(); },
    "The cumulative integral of the distribution function over its domain"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution function"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
