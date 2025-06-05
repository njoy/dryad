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
                  std::vector< InterpolationType > >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the energy distribution\n\n"
    "Arguments:\n"
    "    self           the energy distribution\n"
    "    energies       the energy values\n"
    "    values         the probability values\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions,\n"
    "                   see InterpolationType for all interpolation types"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "energies" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the energy distribution\n\n"
    "Arguments:\n"
    "    self           the energy distribution\n"
    "    energies       the energy values\n"
    "    values         the probability values\n"
    "    interpolant    the interpolation type (default lin-lin),\n"
    "                   see InterpolationType for all interpolation types"
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
  .def_property_readonly(

    "average_energy",
    &Component::averageEnergy,
    "The average energy defined by the distribution"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the distribution\n\n"
    "Arguments:\n"
    "    self        the energy distribution\n"
    "    tolerance   the linearisation tolerance"
  );
}
