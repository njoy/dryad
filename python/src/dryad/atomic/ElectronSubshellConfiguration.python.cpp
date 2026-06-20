// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/atomic/ElectronSubshellConfiguration.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
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
    "  - the decay modes or transitions that can fill a hole in this shell\n\n"
    "If there are transitions defined, the transition probabilities can be\n"
    "normalised to 1 upon construction. Transitions are always sorted at\n"
    "construction time (by originating shell for radiative transitions and\n"
    "by originating and emitting shell for non-radiative transitions).\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ElectronSubshellID  \n"
    "           the electron subshell identifier\n"
    "    energy : float     \n"
    "           the electron subshell binding energy\n"
    "    population : float  \n"
    "           the electron subshell population when the atom is neutral\n"
    "    radiative : list of RadiativeTransitionData, default [] \n"
    "           the radiative transitions that are available (default: an empty list)\n"
    "    nonradiative : list of NonRadiativeTransitionData, default [] \n"
    "           the non-radiative transitions that are available (default: an empty list)\n"
    "    normalise : bool, default false  \n"
    "           option to indicate whether or not to normalise all probability data (default: no normalisation)\n\n"
  );

  // wrap the component
  component
  .def(

    python::init< ElectronSubshellID, double, double,
                  std::vector< RadiativeTransitionData >,
                  std::vector< NonRadiativeTransitionData >,
                  bool >(),
    python::arg( "id" ), python::arg( "energy" ), python::arg( "population" ),
    python::arg( "radiative" ) = std::vector< RadiativeTransitionData >{},
    python::arg( "non_radiative" ) = std::vector< NonRadiativeTransitionData >{},
    python::arg( "normalise" ) = false,
    "Initialise the electron subshell configuration"
  )
  .def_property(

    "identifier",
    python::overload_cast<>( &Component::identifier, python::const_ ),
    python::overload_cast< ElectronSubshellID >( &Component::identifier ),
    "The electron subshell identifier"
  )
  .def_property(

    "binding_energy",
    python::overload_cast<>( &Component::bindingEnergy, python::const_ ),
    python::overload_cast< double >( &Component::bindingEnergy ),
    "The electron subshell binding energy"
  )
  .def_property(

    "population",
    python::overload_cast<>( &Component::population, python::const_ ),
    python::overload_cast< double >( &Component::population ),
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
  .def(

    "has_radiative_transition",
    &Component::hasRadiativeTransition,
    python::arg( "originating_shell" ),
    "Return whether or not a given radiative transition is present\n\n"
    "Parameters\n"
    "----------\n"
    "    originating_shell : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the subshell from which the\n"
    "         vacancy filling electron originated\n"
  )
  .def(

    "has_non_radiative_transition",
    &Component::hasNonRadiativeTransition,
    python::arg( "originating_shell" ),
    python::arg( "emitting_shell" ),
    "Return whether or not a given non-radiative transition is present\n\n"
    "Parameters\n"
    "----------\n"
    "    originating_shell : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the subshell from which the\n"
    "         vacancy filling electron originated\n"
    "    emitting_shell : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the subshell from which the emitted electron originated\n"
  )
  .def(

    "radiative_transition",
    &Component::radiativeTransition,
    python::arg( "originating_shell" ),
    "Return the requested radiative transition\n\n"
    "Parameters\n"
    "----------\n"
    "    originating_shell : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the subshell from which the\n"
    "         vacancy filling electron originated\n"
  )
  .def(

    "non_radiative_transition",
    &Component::nonRadiativeTransition,
    python::arg( "originating_shell" ),
    python::arg( "emitting_shell" ),
    "Return the requested non-radiative transition\n\n"
    "Parameters\n"
    "----------\n"
    "    originating_shell : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the subshell from which the\n"
    "         vacancy filling electron originated\n"
    "    emitting_shell : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the subshell from which the emitted electron originated\n"
  )
  .def_property(

    "radiative_transitions",
    python::overload_cast<>( &Component::radiativeTransitions, python::const_ ),
    python::overload_cast< std::vector< RadiativeTransitionData > >( &Component::radiativeTransitions ),
    "The available radiative transitions to this subshell"
  )
  .def_property(

    "non_radiative_transitions",
    python::overload_cast<>( &Component::nonRadiativeTransitions, python::const_ ),
    python::overload_cast< std::vector< NonRadiativeTransitionData > >( &Component::nonRadiativeTransitions ),
    "The available non-radiative transitions to this subshell"
  )
  .def_property_readonly(

    "total_radiative_probability",
    &Component::totalRadiativeProbability,
    "The total radiative probability"
  )
  .def(

    "radiative_probability",
    &Component::radiativeProbability,
    python::arg( "first" ),
    python::arg( "last" ),
    "The radiative probability for transitions originating from a range of subshells\n\n"
    "Parameters\n"
    "----------\n"
    "    first : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the first subshell in the range\n"
    "    last : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the last subshell in the range (included)"
  )
  .def_property_readonly(

    "total_non_radiative_probability",
    &Component::totalNonRadiativeProbability,
    "The total non-radiative probability"
  )
  .def(

    "non_radiative_probability",
    &Component::nonRadiativeProbability,
    python::arg( "first" ),
    python::arg( "last" ),
    "The non-radiative probability for transitions originating from a range of subshells\n\n"
    "Parameters\n"
    "----------\n"
    "    first : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the first subshell in the range\n"
    "    last : njoy.dryad.id.ElectronSubshellID\n"
    "         the identifier of the last subshell in the range (included)"
  )
  .def_property_readonly(

    "average_radiative_energy",
    python::overload_cast<>( &Component::averageRadiativeEnergy, python::const_ ),
    "The average radiative energy"
  )
  .def_property_readonly(

    "average_non_radiative_energy",
    python::overload_cast<>( &Component::averageNonRadiativeEnergy, python::const_ ),
    "The average non-radiative energy"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the transition probabilities"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // atomic namespace
} // dryad namespace
