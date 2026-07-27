// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/UniformEnergyDistributions.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapUniformEnergyDistributions( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::UniformEnergyDistributions;
  using UniformEnergyDistribution = njoy::dryad::UniformEnergyDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "UniformEnergyDistributions",
    "Energy distribution data given as uniform distributions\n\n"
    "Parameters\n"
    "----------\n"
    "    grid : list of float\n"
    "        the grid values\n"
    "    distributions : list of njoy.dryad.UniformEnergyDistribution\n"
    "        the associated distributions\n"
    "    boundaries : list of int\n"
    "        the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "        the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default LinearLinear\n"
    "        the interpolation type"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >,
                  std::vector< UniformEnergyDistribution >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "grid" ), python::arg( "distributions" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the energy distributions with multiple interpolation regions"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< UniformEnergyDistribution >,
                  InterpolationType >(),
    python::arg( "grid" ), python::arg( "distributions" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the energy distributions with a single interpolation region"
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
  .def_property_readonly(

    "average_energies",
    &Component::averageEnergies,
    "The average energy values"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
