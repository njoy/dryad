// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/atomic/ElectronSubshellConfiguration.hpp"

// namespace aliases
namespace python = pybind11;

namespace atomic {

void wrapElectronSubshellConfiguration( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::atomic::ElectronSubshellConfiguration;
  using RadiativeTransitionData = njoy::dryad::atomic::RadiativeTransitionData;
  using NonRadiativeTransitionData = njoy::dryad::atomic::NonRadiativeTransitionData;
  using ElectronSubshellID = njoy::dryad::id::ElectronSubshellID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ElectronSubshellConfiguration",
    "Electron subshell configuration information\n\n"
    "This class contains the following information for an electron subshell:\n"
    "  - the subshell identifier (K, L1, L2, L3, etc.)\n"
    "  - the subshell binding energy (in eV)\n"
    "  - the electron population, i.e. the number of electrons in the subshell\n"
    "    when the atom is neutral (given as a floating point number)\n"
    "  - the decay modes or transitions that can fill a hole in this shell"
  );

  // wrap the component
  component
  .def(

    python::init< ElectronSubshellID, double, double >(),
    python::arg( "id" ), python::arg( "energy" ), python::arg( "population" ),
    "Initialise the subshell configuration\n\n"
    "Arguments:\n"
    "    self           the subshell configuration data\n"
    "    id             the electron subshell identifier\n"
    "    energy         the electron subshell binding energy\n"
    "    population     the electron subshell population when the atom is neutral"
  )
  .def(

    python::init< ElectronSubshellID, double, double,
                  std::vector< RadiativeTransitionData >,
                  std::vector< NonRadiativeTransitionData > >(),
    python::arg( "id" ), python::arg( "energy" ), python::arg( "population" ),
    python::arg( "radiative" ), python::arg( "non_radiative" ),
    "Initialise the subshell configuration\n\n"
    "Arguments:\n"
    "    self           the subshell configuration data\n"
    "    id             the electron subshell identifier\n"
    "    energy         the electron subshell binding energy\n"
    "    population     the electron subshell population when the atom is neutral\n"
    "    radiative      the radiative transitions that are available\n"
    "    nonradiative   the non-radiative transitions that are available"
  )
  .def_property_readonly(

    "identifier",
    &Component::identifier,
    "The electron subshell identifier"
  )
  .def_property_readonly(

    "binding_energy",
    &Component::bindingEnergy,
    "The electron subshell binding energy"
  )
  .def_property_readonly(

    "population",
    &Component::population,
    "The electron subshell population when the atom is neutral"
  )
  .def_property_readonly(

    "number_radiative_transitions",
    &Component::numberRadiativeTransitions,
    "The number of available radiative transitions"
  )
  .def_property_readonly(

    "number_non_radiative_transitions",
    &Component::numberNonRadiativeTransitions,
    "The number of available non-radiative transitions"
  )
  .def_property_readonly(

    "number_transitions",
    &Component::numberTransitions,
    "The number of available transitions"
  )
  .def_property_readonly(

    "has_radiative_transitions",
    &Component::hasRadiativeTransitions,
    "Flag to indicate whether or not radiative transitions are available"
  )
  .def_property_readonly(

    "has_non_radiative_transitions",
    &Component::hasNonRadiativeTransitions,
    "Flag to indicate whether or not non-radiative transitions are available"
  )
  .def_property_readonly(

    "has_transitions",
    &Component::hasTransitions,
    "Flag to indicate whether or not transitions are available"
  )
  .def_property_readonly(

    "radiative_transitions",
    &Component::radiativeTransitions,
    "The data for all available radiative transitions to this subshell"
  )
  .def_property_readonly(

    "non_radiative_transitions",
    &Component::nonRadiativeTransitions,
    "The data for all available non-radiative transitions to this subshell"
  )
  .def_property_readonly(

    "total_radiative_probability",
    &Component::totalRadiativeProbability,
    "The total radiative probability"
  )
  .def_property_readonly(

    "total_non_radiative_probability",
    &Component::totalNonRadiativeProbability,
    "The total non-radiative probability"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // atomic namespace
