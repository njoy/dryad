// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/TabulatedEnergyDistribution.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedEnergyDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedEnergyDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedEnergyDistribution",
    "An energy distribution defined by a pdf and cdf using tabulated data"
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
    "Initialise the energy distribution\n\n"
    "Arguments:\n"
    "    self           the energy distribution\n"
    "    energies       the energy values\n"
    "    values         the probability values\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions,\n"
    "                   see InterpolationType for all interpolation types\n"
    "    normalise      option to indicate whether or not to normalise\n"
    "                   all probability data (default: no normalisation)"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType, bool >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    python::arg( "normalise" ) = false,
    "Initialise the energy distribution\n\n"
    "Arguments:\n"
    "    self           the energy distribution\n"
    "    energies       the energy values\n"
    "    values         the probability values\n"
    "    interpolant    the interpolation type (default lin-lin),\n"
    "                   see InterpolationType for all interpolation types\n"
    "    normalise      option to indicate whether or not to normalise\n"
    "                   all probability data (default: no normalisation)"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The cosine values"
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
    "Arguments:\n"
    "    self      the distribution\n"
    "    energy    the energy value"
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
    python::arg( "tolerance" ) = ToleranceConvergence(),
    python::arg( "normalise" ) = false,
    "Linearise the distribution\n\n"
    "Arguments:\n"
    "    self        the angular distribution\n"
    "    tolerance   the linearisation tolerance\n"
    "    normalise   option to indicate whether or not to normalise\n"
    "                all probability data (default: no normalisation)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}
