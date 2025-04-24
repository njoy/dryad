// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/TabulatedEnergyDistributions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedEnergyDistributions( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedEnergyDistributions;
  using TabulatedEnergyDistribution = njoy::dryad::TabulatedEnergyDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedEnergyDistributions",
    "Energy distribution data given as tables"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >,
                  std::vector< TabulatedEnergyDistribution >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "grid" ), python::arg( "distributions" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the energy distributions\n\n"
    "Arguments:\n"
    "    self            the energy distribution table\n"
    "    grid            the grid values\n"
    "    distributions   the distributions\n"
    "    boundaries      the boundaries of the interpolation regions\n"
    "    interpolants    the interpolation types of the interpolation regions,\n"
    "                    see InterpolationType for all interpolation types"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< TabulatedEnergyDistribution >,
                  InterpolationType >(),
    python::arg( "grid" ), python::arg( "distributions" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the energy distributions\n\n"
    "Arguments:\n"
    "    self            the multiplicity table\n"
    "    grid            the grid values\n"
    "    distributions   the distributions\n"
    "    interpolant     the interpolation type (default lin-lin),\n"
    "                    see InterpolationType for all interpolation types"
  )
  .def_property_readonly(

    "grid",
    [] ( const Component& self ) -> decltype(auto)
       { return self.grid(); },
    "The grid values for which distributions are given"
  )
  .def_property_readonly(

    "distributions",
    [] ( const Component& self ) -> decltype(auto)
       { return self.distributions(); },
    "The associated distributions"
  )
  .def(

    "__call__",
    [] ( const Component& self, double value, double cosine ) -> decltype(auto)
       { return self( value, cosine ); },
    python::arg( "value" ), python::arg( "cosine" ),
    "Evaluate the energy distributions\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    value     the grid value\n"
    "    energy    the energy value"
  )
  .def_property_readonly(

    "average_energies",
    &Component::averageEnergies,
    "The average energy values"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the distribution\n\n"
    "Arguments:\n"
    "    self        the energy distributions\n"
    "    tolerance   the linearisation tolerance"
  );

  // add standard tabulated data definitions
  addStandardInterpolationTableDefinitions< Component >( component );
}
