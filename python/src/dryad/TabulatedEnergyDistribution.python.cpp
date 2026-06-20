// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/TabulatedEnergyDistribution.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedEnergyDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedEnergyDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedEnergyDistribution",
    "An energy distribution defined by a pdf and cdf using tabulated data\n\n"
    "Parameters\n"
    "----------\n"
    "    energies : list of float\n"
    "        the energy values\n"
    "    values : list of float\n"
    "        the probability values\n"
    "    boundaries : list of int\n"
    "        the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "        the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear\n"
    "        the interpolation type (default lin-lin)\n"
    "    pdf : njoy.dryad.TabulatedEnergyDistributionFunction\n"
    "        the probability distribution function\n"
    "    cdf : njoy.dryad.TabulatedEnergyDistributionFunction\n"
    "        the cumulative distribution function\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType >,
                  bool >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "normalise" ) = false,
    "Initialise the energy distribution with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType, bool >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    python::arg( "normalise" ) = false,
    "Initialise the energy distribution with a single interpolation zone"
  )
  .def(

    python::init< njoy::dryad::TabulatedEnergyDistributionFunction, bool >(),
    python::arg( "pdf" ), python::arg( "normalise" ) = false,
    "Initialise the energy distribution using a pdf"
  )
  .def(

    python::init< njoy::dryad::TabulatedEnergyDistributionFunction,
                  njoy::dryad::TabulatedEnergyDistributionFunction >(),
    python::arg( "pdf" ), python::arg( "cdf" ),
    "Initialise the energy distribution using a pdf and cdf"
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

    "boundaries",
    &Component::boundaries,
    "The boundaries of the interpolation regions"
  )
  .def_property_readonly(

    "interpolants",
    &Component::interpolants,
    "The interpolation types of the interpolation regions"
  )
  .def_property_readonly(

    "pdf",
    &Component::pdf,
    "The probability distribution function (pdf) of the distribution"
  )
  .def_property_readonly(

    "cdf",
    &Component::cdf,
    "The cumulative distribution function (cdf) of the distribution"
  )
  .def(

    "__call__",
    [] ( const Component& self, double energy ) -> decltype(auto)
       { return self( energy ); },
    python::arg( "energy" ),
    "Evaluate the pdf of the distribution for a given energy value\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy value"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution"
  )
  .def_property_readonly(

    "average_energy",
    &Component::averageEnergy,
    "The average energy defined by the distribution"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    python::arg( "normalise" ) = false,
    "Linearise the distribution\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 0.001\n"
    "        the linearisation tolerance\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
