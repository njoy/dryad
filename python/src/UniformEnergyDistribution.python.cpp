// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/UniformEnergyDistribution.hpp"

// namespace aliases
namespace python = pybind11;

void wrapUniformEnergyDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::UniformEnergyDistribution;
  using UniformDistributionType = njoy::dryad::UniformDistributionType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "UniformEnergyDistribution",
    "A uniform or equally probably energy distribution"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, UniformDistributionType >(),
    python::arg( "energies" ), python::arg( "type" ),
    "Initialise the energy distribution\n\n"
    "Arguments:\n"
    "    self       the energy distribution\n"
    "    energies   the energy values\n"
    "    type       the uniform distribution type"
  )
  .def_property_readonly(

    "type",
    [] ( const Component& self ) { return self.type(); },
    "The distribution type"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy values for the distribution"
  )
  .def_property_readonly(

    "number_energies",
    &Component::numberEnergies,
    "The number of discrete energies or intervals"
  )
  .def_property_readonly(

    "average_energy",
    &Component::averageEnergy,
    "The average energy defined by the distribution"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}
