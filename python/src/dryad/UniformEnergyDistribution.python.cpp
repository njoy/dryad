// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/UniformEnergyDistribution.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapUniformEnergyDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::UniformEnergyDistribution;
  using UniformDistributionType = njoy::dryad::UniformDistributionType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "UniformEnergyDistribution",
    "A uniform or equally probable energy distribution\n\n"
    "Parameters\n"
    "----------\n"
    "    energies : list of float\n"
    "        the energy values\n"
    "    type : njoy.dryad.UniformDistributionType\n"
    "        the uniform distribution type"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, UniformDistributionType >(),
    python::arg( "energies" ), python::arg( "type" ),
    "Initialise the energy distribution"
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

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
